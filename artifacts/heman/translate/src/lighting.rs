use crate::*;
use lazy_static::lazy_static;
use std::assert;
use std::f32;
use rayon::prelude::*;
use std::f32::consts::FRAC_PI_2;
use rand::Rng;
use std::sync::Mutex;


lazy_static! {
    pub static ref _OCCLUSION_SCALE: std::sync::Mutex<f32> = std::sync::Mutex::new(1.0f32);
}

pub fn heman_lighting_set_occlusion_scale(s: f32) {
    let mut occlusion_scale = _OCCLUSION_SCALE.lock().unwrap();
    *occlusion_scale = s;
}

pub fn azimuth_slope(a: &KmVec3, b: &KmVec3) -> f32 {
    let mut d = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    kmVec3Subtract(&mut d, a, b);
    let x = kmVec3Length(Some(&d));
    let y = b.z - a.z;
    y / x
}
pub fn helper_heman_lighting_compute_normals_1(
    y_ref: &mut i32,
    heightmap: &HemanImageS,
    width: i32,
    invh: f32,
    invw: f32,
    maxx: i32,
    maxy: i32,
    normals: &mut [KmVec3],
) {
    let y = *y_ref;
    let v = y as f32 * invh;
    let y1 = if (y + 1) > maxy { maxy } else { y + 1 };
    
    let mut p = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut px = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut py = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    
    let n_start = (y * width) as usize;
    let n_slice = &mut normals[n_start..n_start + width as usize];
    
    for (n_idx, x) in (0..width).enumerate() {
        let u = x as f32 * invw;
        let x1 = if (x + 1) > maxx { maxx } else { x + 1 };
        
        // Get height values
        let z_p = heman_image_texel(heightmap, x, y).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let z_px = heman_image_texel(heightmap, x1, y).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let z_py = heman_image_texel(heightmap, x, y1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        
        // Set points
        p.x = u;
        p.y = v;
        p.z = z_p;
        
        px.x = u + invw;
        px.y = v;
        px.z = z_px;
        
        py.x = u;
        py.y = v + invh;
        py.z = z_py;
        
        // Calculate vectors and normal
        let px_copy = px.clone();
        let py_copy = py.clone();
        kmVec3Subtract(&mut px, &px_copy, &p);
        kmVec3Subtract(&mut py, &py_copy, &p);
        
        let px_copy = px.clone();
        let py_copy = py.clone();
        kmVec3Cross(&mut n_slice[n_idx], &px_copy, &py_copy);
        
        let normal_copy = n_slice[n_idx].clone();
        kmVec3Normalize(Some(&mut n_slice[n_idx]), Some(&normal_copy));
        n_slice[n_idx].y *= -1.0;
    }
    
    *y_ref = y;
}
pub fn heman_lighting_compute_normals(heightmap: &HemanImageS) -> HemanImage {
    assert!(heightmap.nbands == 1);
    let width = heightmap.width;
    let height = heightmap.height;
    let mut result = heman_image_create(width, height, 3);
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let maxx = width - 1;
    let maxy = height - 1;
    
    if let Some(ref mut result_box) = result {
        if let Some(ref mut normals_vec) = result_box.data {
            let normals: &mut [KmVec3] = unsafe {
                std::slice::from_raw_parts_mut(
                    normals_vec.as_mut_ptr() as *mut KmVec3,
                    normals_vec.len() / 3,
                )
            };

            // Parallel processing using rayon
            (0..height).into_par_iter().for_each(|y| {
                let mut y_mut = y;
                let normals_slice = unsafe {
                    std::slice::from_raw_parts_mut(
                        normals.as_ptr() as *mut KmVec3,
                        normals.len(),
                    )
                };
                helper_heman_lighting_compute_normals_1(
                    &mut y_mut,
                    heightmap,
                    width,
                    invh,
                    invw,
                    maxx,
                    maxy,
                    normals_slice,
                );
            });
        }
    }

    result
}
pub fn compute_occlusion(thispt: KmVec3, horizonpt: KmVec3) -> f32 {
    let mut direction = KmVec3 {
        x: 0.0,
        y: 0.0,
        z: 0.0,
    };
    
    kmVec3Subtract(&mut direction, &horizonpt, &thispt);
    let direction_copy = direction.clone();
    kmVec3Normalize(Some(&mut direction), Some(&direction_copy));
    
    let dot = kmVec3Dot(Some(&direction), Some(&KM_VEC3_POS_Z)).unwrap_or(0.0);
    let clamped_dot = if dot > 0.0 { dot } else { 0.0 };
    
    (clamped_dot.atan() * (2.0 / std::f32::consts::PI))
}

pub fn helper_helper_horizon_scan_1_1(
    i_ref: &mut i32,
    j_ref: &mut i32,
    thispt_ref: &mut KmVec3,
    horizonpt_ref: &mut KmVec3,
    stack_top_ref: &mut i32,
    heightmap: &HemanImageS,
    result: &mut HemanImageS,
    dx: i32,
    dy: i32,
    pathlen: i32,
    cellw: f32,
    cellh: f32,
    convex_hull: &mut [KmVec3],
) {
    let mut i = *i_ref;
    let mut j = *j_ref;
    let mut thispt = thispt_ref.clone();
    let mut horizonpt = horizonpt_ref.clone();
    let mut stack_top = *stack_top_ref;

    thispt.x = i as f32 * cellw;
    thispt.y = j as f32 * cellh;
    thispt.z = *heman_image_texel(heightmap, i, j).unwrap().first().unwrap();

    while stack_top > 0 {
        let s1 = azimuth_slope(&thispt, &convex_hull[stack_top as usize]);
        let s2 = azimuth_slope(&thispt, &convex_hull[(stack_top - 1) as usize]);
        if s1 >= s2 {
            break;
        }
        stack_top -= 1;
    }

    horizonpt = convex_hull[stack_top as usize].clone();
    stack_top += 1;
    assert!(stack_top < pathlen);
    convex_hull[stack_top as usize] = thispt.clone();
    let occlusion = compute_occlusion(thispt.clone(), horizonpt.clone());

    {
        let texel = heman_image_texel(result, i, j).unwrap();
        let mut data = texel.to_vec();
        data[0] += (1.0f32 / 16.0f32) * occlusion;
        result.data = Some(data);
    }

    i += dx;
    j += dy;

    *i_ref = i;
    *j_ref = j;
    *thispt_ref = thispt;
    *horizonpt_ref = horizonpt;
    *stack_top_ref = stack_top;
}

pub fn helper_horizon_scan_1(
    heightmap: &HemanImageS,
    result: &mut HemanImageS,
    startpts: &[i32],
    dx: i32,
    dy: i32,
    w: i32,
    h: i32,
    pathlen: i32,
    cellw: f32,
    cellh: f32,
    hull_buffer: &mut [KmVec3],
    sweep: i32,
) {
    let convex_hull_start = (sweep * pathlen) as usize;
    let convex_hull = &mut hull_buffer[convex_hull_start..(convex_hull_start + pathlen as usize)];

    let p_start = (sweep * 2) as usize;
    let p = &startpts[p_start..(p_start + 2)];

    let mut p_idx = 0;
    let mut i = p[0 + p_idx];
    let mut j = p[1 + p_idx];

    let mut thispt = KmVec3 {
        x: i as f32 * cellw,
        y: j as f32 * cellh,
        z: {
            let x_coord = i.clamp(0, w - 1);
            let y_coord = j.clamp(0, h - 1);
            match heman_image_texel(heightmap, x_coord, y_coord) {
                Some(texel) => texel[0],
                None => 0.0,
            }
        },
    };

    let mut stack_top = 0;
    convex_hull[0] = thispt.clone();

    i += dx;
    j += dy;

    while i >= 0 && i < w && j >= 0 && j < h {
        let mut horizonpt = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        helper_helper_horizon_scan_1_1(
            &mut i,
            &mut j,
            &mut thispt,
            &mut horizonpt,
            &mut stack_top,
            heightmap,
            result,
            dx,
            dy,
            pathlen,
            cellw,
            cellh,
            convex_hull,
        );
    }
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
            if (x >= 0 && x < w) && (y >= 0 && y < h) {
                continue;
            }
            startpts[p_idx] = if sx < 0 { (w - x) - 1 } else { x };
            p_idx += 1;
            startpts[p_idx] = if sy < 0 { (h - y) - 1 } else { y };
            p_idx += 1;
        }
    }

    assert!(nsweeps == (p_idx / 2).try_into().unwrap());
    let mut pathlen = 0;
    let mut i = startpts[0];
    let mut j = startpts[1];
    loop {
        i += dx;
        j += dy;
        pathlen += 1;
        if !((i >= 0 && i < w) && (j >= 0 && j < h)) {
            break;
        }
    }

    let occlusion_scale = *_OCCLUSION_SCALE.lock().unwrap();
    let cell_dim = occlusion_scale / (if w > h { w } else { h }) as f32;
    let cellw = cell_dim;
    let cellh = cell_dim;
    let mut hull_buffer = vec![KmVec3 { x: 0.0, y: 0.0, z: 0.0 }; (pathlen * nsweeps) as usize];

    // Parallel processing would typically use rayon or similar in Rust
    for sweep in 0..nsweeps {
        helper_horizon_scan_1(
            heightmap,
            result,
            startpts,
            dx,
            dy,
            w,
            h,
            pathlen,
            cellw,
            cellh,
            &mut hull_buffer,
            sweep,
        );
    }
}
pub fn heman_lighting_compute_occlusion(heightmap: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(heightmap.nbands == 1);
    let width = heightmap.width;
    let height = heightmap.height;
    let mut result = heman_image_create(width, height, 1).expect("Failed to create image");
    
    if let Some(ref mut result_data) = result.as_mut().data {
        result_data.fill(0.0);
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
        horizon_scan(heightmap, result.as_mut(), &mut startpts, dx, dy);
    }

    if let Some(ref mut result_data) = result.as_mut().data {
        for val in result_data.iter_mut() {
            *val = 1.0 - *val;
            assert!(*val >= 0.0 && *val <= 1.0);
        }
    }

    Some(result)
}
pub fn helper_heman_lighting_apply_1(
    y_ref: &mut i32,
    albedo: Option<&HemanImageS>,
    occlusion: f32,
    diffuse: f32,
    diffuse_softening: f32,
    width: i32,
    normals: &HemanImageS,
    occ: &HemanImageS,
    colors: &mut [KmVec3],
    invgamma: f32,
    L: &KmVec3,
) {
    let y = *y_ref;
    let color_slice = &mut colors[(y * width) as usize..];
    
    for x in 0..width {
        let color_idx = x as usize;
        let color = &mut color_slice[color_idx];
        
        let N_data = heman_image_texel(normals, x, y).expect("Failed to get normal texel");
        let mut N = KmVec3 {
            x: N_data[0],
            y: N_data[1],
            z: N_data[2],
        };
        
        let N_copy = N.clone();
        kmVec3Lerp(&mut N, &N_copy, &KM_VEC3_POS_Z, diffuse_softening);
        
        let df = 1.0 - (diffuse * (1.0 - kmClamp(kmVec3Dot(Some(&N), Some(L)).unwrap(), 0.0, 1.0)));
        
        let occ_texel = heman_image_texel(occ, x, y).expect("Failed to get occlusion texel");
        let of = 1.0 - (occlusion * (1.0 - occ_texel[0]));
        
        if let Some(albedo_img) = albedo {
            let albedo_texel = heman_image_texel(albedo_img, x, y).expect("Failed to get albedo texel");
            *color = KmVec3 {
                x: albedo_texel[0],
                y: albedo_texel[1],
                z: albedo_texel[2],
            };
        } else {
            *color = KmVec3 { x: 1.0, y: 1.0, z: 1.0 };
        }
        
        let gamma = *_GAMMA.lock().unwrap();
        color.x = color.x.powf(gamma);
        color.y = color.y.powf(gamma);
        color.z = color.z.powf(gamma);
        
        let color_copy = color.clone();
        kmVec3Scale(color, &color_copy, df * of);
        
        color.x = color.x.powf(invgamma);
        color.y = color.y.powf(invgamma);
        color.z = color.z.powf(invgamma);
    }
    
    *y_ref = y;
}
lazy_static! {
    pub static ref _GAMMA: std::sync::Mutex<f32> = std::sync::Mutex::new(0.0);
}

pub fn heman_lighting_apply(
    heightmap: &HemanImageS,
    albedo: Option<&HemanImageS>,
    occlusion: f32,
    diffuse: f32,
    diffuse_softening: f32,
    light_position: Option<&[f32]>,
) -> Option<Box<HemanImageS>> {
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

    let default_pos = [-0.5f32, 0.5f32, 1.0f32];
    let light_pos = light_position.unwrap_or(&default_pos);

    let colors = unsafe {
        std::slice::from_raw_parts_mut(
            final_img.data.as_mut()?.as_mut_ptr() as *mut KmVec3,
            (width * height) as usize
        )
    };

    let invgamma = 1.0f32 / *_GAMMA.lock().unwrap();
    let mut L = KmVec3 {
        x: light_pos[0],
        y: light_pos[1],
        z: light_pos[2],
    };
    let L_copy = L.clone();
    kmVec3Normalize(Some(&mut L), Some(&L_copy));

    for y in 0..height {
        let mut y = y;
        helper_heman_lighting_apply_1(
            &mut y,
            albedo,
            occlusion,
            diffuse,
            diffuse_softening,
            width,
            normals.as_ref(),
            occ.as_ref(),
            colors,
            invgamma,
            &L,
        );
    }

    heman_image_destroy(Some(normals));
    heman_image_destroy(Some(occ));
    Some(final_img)
}
