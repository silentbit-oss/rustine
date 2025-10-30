use crate::*;
use rand::Rng;
use std::assert;
use rayon::prelude::*;


pub fn heman_draw_points(target: &mut HemanImageS, pts: &HemanPoints, val: f32) {
    // Unwrap the points data safely
    let Some(pts) = pts.as_ref() else { return };
    let Some(src) = pts.data.as_ref() else { return };
    
    let mut src_idx = 0;
    for _ in 0..pts.width {
        // Get x and y coordinates
        let x = src[0 + src_idx];
        let y = src[1 + src_idx];
        src_idx += pts.nbands as usize;
        
        // Calculate pixel coordinates
        let i = (x * target.width as f32) as i32;
        let j = (y * target.height as f32) as i32;
        
        // Check bounds
        if i < 0 || i >= target.width || j < 0 || j >= target.height {
            continue;
        }
        
        // Get texel data
        if let Some(texel) = heman_image_texel(target, i, j) {
            // Create mutable slice for writing
            if let Some(target_data) = target.data.as_mut() {
                let texel_start = (j * target.width + i) as usize * target.nbands as usize;
                let texel_end = texel_start + target.nbands as usize;
                
                // Write value to all bands
                for c in texel_start..texel_end {
                    target_data[c] = val;
                }
            }
        }
    }
}
pub fn heman_draw_colored_points(
    target: &mut HemanImageS,
    pts: &HemanImageS,
    colors: &[u32],
) {
    assert!((target.nbands == 3) || (target.nbands == 4));
    let src = pts.data.as_ref().expect("pts.data is None");
    let mut src_idx = 0;
    let inv = 1.0f32 / 255.0f32;
    
    let target_data = target.data.as_mut().expect("target.data is None");
    
    for k in 0..pts.width {
        let x = src[0 + src_idx as usize];
        let y = src[1 + src_idx as usize];
        src_idx += pts.nbands;
        
        let i = (x * target.width as f32) as i32;
        let j = (y * target.height as f32) as i32;
        
        if i < 0 || i >= target.width || j < 0 || j >= target.height {
            continue;
        }
        
        let idx = (j * target.width + i) as usize * target.nbands as usize;
        let rgb = colors[k as usize];
        
        target_data[idx] = ((rgb >> 16) & 0xff) as f32 * inv;
        target_data[idx + 1] = ((rgb >> 8) & 0xff) as f32 * inv;
        target_data[idx + 2] = (rgb & 0xff) as f32 * inv;
        
        if target.nbands == 4 {
            target_data[idx + 3] = (rgb >> 24) as f32 * inv;
        }
    }
}
pub fn heman_draw_colored_circles(
    target: &mut HemanImageS,
    pts: &HemanImageS,
    radius: i32,
    colors: &[u32],
) {
    let fwidth = (radius * 2) + 1;
    let radius2 = radius * radius;
    let src = pts.data.as_ref().unwrap();
    let mut src_idx = 0;
    let inv = 1.0f32 / 255.0f32;
    let w = target.width;
    let h = target.height;

    for k in 0..pts.width {
        let x = src[0 + src_idx];
        let y = src[1 + src_idx];
        src_idx += pts.nbands as usize;
        let ii = (x * w as f32) as i32 - radius;
        let jj = (y * h as f32) as i32 - radius;

        for kj in 0..fwidth {
            for ki in 0..fwidth {
                let i = ii + ki;
                let j = jj + kj;
                let dx = i as f32 - (x * w as f32);
                let dy = j as f32 - (y * h as f32);
                let r2 = (dx * dx + dy * dy) as i32;

                if r2 > radius2 {
                    continue;
                }

                if let Some(texel) = heman_image_texel(target, i, j) {
                    let mut texel_idx = 0;
                    let rgb = colors[k as usize];
                    target.data.as_mut().unwrap()[texel_idx] = ((rgb >> 16) as f32) * inv;
                    texel_idx += 1;
                    target.data.as_mut().unwrap()[texel_idx] = (((rgb >> 8) & 0xff) as f32) * inv;
                    texel_idx += 1;
                    target.data.as_mut().unwrap()[texel_idx] = ((rgb & 0xff) as f32) * inv;
                }
            }
        }
    }
}

pub fn heman_draw_splats(
    target: &mut HemanImageS,
    pts: &HemanPoints,
    radius: i32,
    blend_mode: i32,
) {
    let fwidth = (radius * 2) + 1;
    let mut gaussian_splat = vec![0.0; (fwidth * fwidth) as usize];
    generate_gaussian_splat(&mut gaussian_splat, fwidth as usize);

    let pts = pts.as_ref().expect("pts should not be None");
    let src = pts.data.as_ref().expect("pts.data should not be None");
    let mut src_idx = 0;
    let w = target.width;
    let h = target.height;

    for _ in 0..pts.width {
        let x = src[src_idx];
        src_idx += 1;
        let y = src[src_idx];
        src_idx += 1;

        let ii = (x * w as f32) as i32 - radius;
        let jj = (y * h as f32) as i32 - radius;

        for kj in 0..fwidth {
            for ki in 0..fwidth {
                let i = ii + ki;
                let j = jj + kj;

                if i < 0 || i >= w || j < 0 || j >= h {
                    continue;
                }

                let texel = heman_image_texel(target, i, j)
                    .expect("texel should not be None");
                let splat_value = gaussian_splat[(kj * fwidth + ki) as usize];

                let target_data = target.data.as_mut().expect("target.data should not be None");
                let mut texel_idx = 0;
                for _ in 0..target.nbands {
                    target_data[texel_idx] += splat_value;
                    texel_idx += 1;
                }
            }
        }
    }
}
pub fn heman_draw_contour_from_points(
    target: &mut HemanImageS,
    coords: &HemanPoints,
    rgb: u32,  // Changed from HemanColor to u32 to resolve ambiguity
    mind: f32,
    maxd: f32,
    filterd: i32,
) {
    assert!((target.nbands == 3) || (target.nbands == 4));
    let width = target.width;
    let height = target.height;
    let mut seed = heman_image_create(width, height, 1).expect("Failed to create seed image");
    heman_image_clear(&mut seed, 0.0);
    heman_internal_draw_seeds(&mut seed, coords, filterd);

    let inv = 1.0f32 / 255.0f32;
    let r = ((rgb >> 16) & 0xff) as f32 * inv;
    let g = ((rgb >> 8) & 0xff) as f32 * inv;
    let b = (rgb & 0xff) as f32 * inv;
    let mut a = 1.0f32;
    if target.nbands == 4 {
        a = (rgb >> 24) as f32 * inv;
    }

    // Get mutable reference to data outside the closure
    let data = target.data.as_mut().expect("No data in target image");
    
    // Parallel iteration over y using rayon with mutable access
    data.par_chunks_mut((width * target.nbands) as usize).enumerate().for_each(|(y, dst_slice)| {
        let y = y as i32;
        let mut dst_idx = 0;
        for x in 0..width {
            let dist = heman_image_texel(&seed, x, y)
                .expect("Failed to get texel")
                .first()
                .copied()
                .unwrap_or(0.0);

            if (dist > mind) && (dist < maxd) {
                dst_slice[dst_idx] = r;
                dst_slice[dst_idx + 1] = g;
                dst_slice[dst_idx + 2] = b;
                if target.nbands == 4 {
                    dst_slice[dst_idx + 3] = a;
                }
            }
            dst_idx += target.nbands as usize;
        }
    });

    heman_points_destroy(Some(seed));
}
