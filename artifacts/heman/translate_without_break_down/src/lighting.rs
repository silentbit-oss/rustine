use crate::*;
use lazy_static::lazy_static;
use std::assert;
use std::f32;
use std::sync::Mutex;
use rand::Rng;
use crate::km_vec3::KmVec3;


pub fn heman_lighting_set_occlusion_scale(s: f32) {
    let mut _occlusion_scale = _OCCLUSION_SCALE.lock().unwrap();
    *_occlusion_scale = s;
}

pub fn azimuth_slope(a: KmVec3, b: KmVec3) -> f32 {
    let mut d = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Subtract(&mut d, &a, &b);
    let x = kmVec3Length(Some(&d));
    let y = b.z - a.z;
    y / x
}
pub fn compute_occlusion(thispt: KmVec3, horizonpt: KmVec3) -> f32 {
    let mut direction = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    
    kmVec3Subtract(&mut direction, &horizonpt, &thispt);
    let mut normalized_direction = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Normalize(Some(&mut normalized_direction), Some(&direction));
    
    let dot = kmVec3Dot(Some(&normalized_direction), Some(&KM_VEC3_POS_Z)).unwrap_or(0.0);
    f32::atan(if dot > 0.0 { dot } else { 0.0 }) * 0.63661977236
}
pub fn horizon_scan(
    heightmap: &HemanImageS,
    result: &mut HemanImageS,
    startpts: &mut [i32],
    dx: i32,
    dy: i32,
) {
    let w = heightmap.width;
    let h = heightmap.height;
    let sx = (dx > 0) as i32 - (dx < 0) as i32;
    let sy = (dy > 0) as i32 - (dy < 0) as i32;
    let ax = dx.abs();
    let ay = dy.abs();
    let nsweeps = ((ay * w) + (ax * h)) - ((ax + ay) - 1);
    let mut p_idx = 0;

    for x in -ax..(w - ax) {
        for y in -ay..(h - ay) {
            if x >= 0 && x < w && y >= 0 && y < h {
                continue;
            }
            startpts[p_idx] = if sx < 0 { (w - x) - 1 } else { x };
            p_idx += 1;
            startpts[p_idx] = if sy < 0 { (h - y) - 1 } else { y };
            p_idx += 1;
        }
    }

    assert!(nsweeps == (p_idx / 2) as i32);
    let mut pathlen = 0;
    let mut i = startpts[0];
    let mut j = startpts[1];
    loop {
        i += dx;
        j += dy;
        pathlen += 1;
        if !(i >= 0 && i < w && j >= 0 && j < h) {
            break;
        }
    }

    let occlusion_scale = *_OCCLUSION_SCALE.lock().unwrap();
    let divisor = if w > h { w } else { h } as f32;
    let cellw = occlusion_scale / divisor;
    let cellh = occlusion_scale / divisor;
    let mut hull_buffer = vec![KmVec3 { x: 0.0, y: 0.0, z: 0.0 }; (pathlen * nsweeps) as usize];

    for sweep in 0..nsweeps {
        let convex_hull = &mut hull_buffer[(sweep * pathlen) as usize..((sweep + 1) * pathlen) as usize];
        let p = &startpts[(sweep * 2) as usize..];
        let mut p_idx = 0;
        let mut i = p[p_idx];
        let mut j = p[p_idx + 1];
        let mut thispt = KmVec3 {
            x: i as f32 * cellw,
            y: j as f32 * cellh,
            z: {
                let x_clamped = 0.max((w - 1).min(i));
                let y_clamped = 0.max((h - 1).min(j));
                heman_image_texel(heightmap, x_clamped, y_clamped).map_or(0.0, |v| v[0])
            },
        };
        let mut stack_top = 0;
        convex_hull[stack_top] = thispt.clone();
        i += dx;
        j += dy;

        while i >= 0 && i < w && j >= 0 && j < h {
            thispt = KmVec3 {
                x: i as f32 * cellw,
                y: j as f32 * cellh,
                z: heman_image_texel(heightmap, i, j).map_or(0.0, |v| v[0]),
            };

            while stack_top > 0 {
                let s1 = azimuth_slope(thispt.clone(), convex_hull[stack_top].clone());
                let s2 = azimuth_slope(thispt.clone(), convex_hull[stack_top - 1].clone());
                if s1 >= s2 {
                    break;
                }
                stack_top -= 1;
            }

            let horizonpt = convex_hull[stack_top].clone();
            stack_top += 1;
            assert!(stack_top < pathlen as usize);
            convex_hull[stack_top] = thispt.clone();
            let occlusion = compute_occlusion(thispt.clone(), horizonpt);
            if let Some(texel) = heman_image_texel(result, i, j) {
                unsafe {
                    *(texel.as_ptr() as *mut f32) += (1.0 / 16.0) * occlusion;
                }
            }
            i += dx;
            j += dy;
        }
    }
}

pub fn heman_lighting_compute_occlusion(heightmap: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(heightmap.nbands == 1);
    let width = heightmap.width;
    let height = heightmap.height;
    
    let mut result = match heman_image_create(width, height, 1) {
        Some(img) => img,
        None => return None,
    };
    
    // Initialize result data with zeros
    if let Some(ref mut data) = result.data {
        data.fill(0.0);
    }

    const SCANS: [i32; 32] = [
        1, 0, 0, 1, -1, 0, 0, -1, 
        1, 1, -1, -1, 1, -1, -1, 1, 
        2, 1, 2, -1, -2, 1, -2, -1, 
        1, 2, 1, -2, -1, 2, -1, -2
    ];

    let max_dim = kmMax(width as f32, height as f32) as usize;
    let mut startpts = vec![0; 2 * 3 * max_dim];

    for i in 0..16 {
        let dx = SCANS[i * 2];
        let dy = SCANS[i * 2 + 1];
        horizon_scan(heightmap, &mut result, &mut startpts, dx, dy);
    }

    if let Some(ref mut data) = result.data {
        for val in data.iter_mut() {
            *val = 1.0 - *val;
            assert!(*val >= 0.0 && *val <= 1.0);
        }
    }

    Some(result)
}
pub fn heman_lighting_compute_normals(heightmap: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(heightmap.nbands == 1);
    let width = heightmap.width;
    let height = heightmap.height;
    let mut result = heman_image_create(width, height, 3)?;
    
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let maxx = width - 1;
    let maxy = height - 1;
    
    if let Some(result_data) = result.data.as_mut() {
        let normals: &mut [KmVec3] = unsafe {
            std::slice::from_raw_parts_mut(
                result_data.as_mut_ptr() as *mut KmVec3,
                (width * height) as usize
            )
        };
        
        for y in 0..height {
            let v = y as f32 * invh;
            let y1 = if (y + 1) > maxy { maxy } else { y + 1 };
            
            let row_start = (y * width) as usize;
            let row_end = row_start + width as usize;
            let row_normals = &mut normals[row_start..row_end];
            
            for x in 0..width {
                let u = x as f32 * invw;
                let x1 = if (x + 1) > maxx { maxx } else { x + 1 };
                
                let p_z = heman_image_texel(heightmap, x, y)
                    .and_then(|texel| texel.first())
                    .copied()
                    .unwrap_or(0.0);
                
                let px_z = heman_image_texel(heightmap, x1, y)
                    .and_then(|texel| texel.first())
                    .copied()
                    .unwrap_or(0.0);
                
                let py_z = heman_image_texel(heightmap, x, y1)
                    .and_then(|texel| texel.first())
                    .copied()
                    .unwrap_or(0.0);
                
                let p = KmVec3 { x: u, y: v, z: p_z };
                let mut px = KmVec3 { x: u + invw, y: v, z: px_z };
                let mut py = KmVec3 { x: u, y: v + invh, z: py_z };
                
                // Create temporary copies for subtraction
                let px_copy = px.clone();
                let py_copy = py.clone();
                
                kmVec3Subtract(&mut px, &px_copy, &p);
                kmVec3Subtract(&mut py, &py_copy, &p);
                
                let n = &mut row_normals[x as usize];
                kmVec3Cross(n, &px, &py);
                
                // Create a temporary reference for normalization
                let n_copy = n.clone();
                kmVec3Normalize(Some(n), Some(&n_copy));
                n.y *= -1.0;
            }
        }
    }
    
    Some(result)
}
pub fn heman_lighting_apply(
    heightmap: Option<&HemanImageS>,
    albedo: Option<&HemanImageS>,
    occlusion: f32,
    diffuse: f32,
    diffuse_softening: f32,
    light_position: Option<&[f32]>,
) -> Option<Box<HemanImageS>> {
    // Check for NULL equivalent (None in Rust)
    let heightmap = heightmap?;
    assert!(heightmap.nbands == 1);
    
    let width = heightmap.width;
    let height = heightmap.height;
    let mut final_img = heman_image_create(width, height, 3)?;
    let normals = heman_lighting_compute_normals(heightmap)?;
    let occ = heman_lighting_compute_occlusion(heightmap)?;

    if let Some(albedo) = albedo {
        assert!(albedo.nbands == 3);
        assert!(albedo.width == width);
        assert!(albedo.height == height);
    }

    lazy_static! {
        static ref DEFAULT_POS: [f32; 3] = [-0.5f32, 0.5f32, 1.0f32];
    }

    let light_pos = match light_position {
        Some(pos) => pos,
        None => &DEFAULT_POS[..],
    };
    let gamma_val = *_GAMMA.lock().unwrap();
    let invgamma = 1.0f32 / gamma_val;

    let mut L = KmVec3 {
        x: light_pos[0],
        y: light_pos[1],
        z: light_pos[2],
    };
    let L_in = L.clone();
    kmVec3Normalize(Some(&mut L), Some(&L_in));

    // Process each pixel
    for y in 0..height {
        for x in 0..width {
            let mut N = heman_image_texel(&normals, x, y)
                .map(|data| KmVec3 { x: data[0], y: data[1], z: data[2] })
                .unwrap();
            
            let N_in = N.clone();
            kmVec3Lerp(&mut N, &N_in, &KM_VEC3_POS_Z, diffuse_softening);
            
            let dot = kmVec3Dot(Some(&N), Some(&L)).unwrap_or(0.0);
            let df = 1.0 - (diffuse * (1.0 - kmClamp(dot, 0.0, 1.0)));
            let occ_val = heman_image_texel(&occ, x, y).map(|v| v[0]).unwrap_or(0.0);
            let of = 1.0 - (occlusion * (1.0 - occ_val));

            let mut color = if let Some(albedo) = albedo {
                heman_image_texel(albedo, x, y)
                    .map(|data| KmVec3 { x: data[0], y: data[1], z: data[2] })
                    .unwrap_or(KmVec3 { x: 1.0, y: 1.0, z: 1.0 })
            } else {
                KmVec3 { x: 1.0, y: 1.0, z: 1.0 }
            };

            // Apply gamma correction
            color.x = color.x.powf(gamma_val);
            color.y = color.y.powf(gamma_val);
            color.z = color.z.powf(gamma_val);

            let color_in = color.clone();
            kmVec3Scale(&mut color, &color_in, df * of);

            // Apply inverse gamma correction
            color.x = color.x.powf(invgamma);
            color.y = color.y.powf(invgamma);
            color.z = color.z.powf(invgamma);

            // Store the result in final image
            if let Some(data) = &mut final_img.data {
                let idx = ((y * width + x) * 3) as usize;
                if idx + 2 < data.len() {
                    data[idx] = color.x;
                    data[idx + 1] = color.y;
                    data[idx + 2] = color.z;
                }
            }
        }
    }

    heman_image_destroy(Some(normals));
    heman_image_destroy(Some(occ));
    Some(final_img)
}
