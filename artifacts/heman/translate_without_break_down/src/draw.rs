use crate::*;
use rand::Rng;
use std::assert;
use rayon::iter::IntoParallelIterator;
use rayon::iter::ParallelIterator;
use rayon::prelude::*;

pub fn heman_draw_points(target: &mut HemanImageS, pts: &HemanPoints, val: f32) {
    // Unwrap the points data safely
    let src = match &pts.as_ref().unwrap().data {
        Some(data) => data,
        None => return,
    };

    let mut src_idx: usize = 0;
    let width = pts.as_ref().unwrap().width;
    let nbands = pts.as_ref().unwrap().nbands as usize;

    for _ in 0..width {
        let x = src[0 + src_idx];
        let y = src[1 + src_idx];
        src_idx += nbands;

        let i = (x * target.width as f32) as i32;
        let j = (y * target.height as f32) as i32;

        // Check bounds (Rust uses exclusive upper bound)
        if i < 0 || i >= target.width || j < 0 || j >= target.height {
            continue;
        }

        // First get the texel slice immutably to calculate position
        let texel_slice = heman_image_texel(target, i, j).unwrap();
        let start = (j * target.width + i) as usize * target.nbands as usize;
        
        // Then mutate the data if available
        if let Some(texel) = target.data.as_mut() {
            // Update all bands
            for c in start..start + target.nbands as usize {
                texel[c] = val;
            }
        }
    }
}
pub fn heman_draw_colored_points(
    target: &mut HemanImageS,
    pts: &HemanPoints,
    colors: &[HemanColor],
) {
    assert!((target.nbands == 3) || (target.nbands == 4));
    let src = pts.as_ref().unwrap().data.as_ref().unwrap();
    let mut src_idx = 0;
    let inv = 1.0f32 / 255.0f32;
    
    for k in 0..pts.as_ref().unwrap().width {
        let x = src[0 + src_idx];
        let y = src[1 + src_idx];
        src_idx += pts.as_ref().unwrap().nbands as usize;
        
        let i = (x * target.width as f32) as i32;
        let j = (y * target.height as f32) as i32;
        
        if i < 0 || i >= target.width || j < 0 || j >= target.height {
            continue;
        }
        
        // Calculate the texel offset first
        let texel_offset = match heman_image_texel(target, i, j) {
            Some(texel) => {
                let data_ptr = target.data.as_ref().unwrap().as_ptr() as usize;
                (texel.as_ptr() as usize - data_ptr) / std::mem::size_of::<f32>()
            }
            None => continue,
        };
        
        // Now we can safely mutate the data
        let rgb = colors[k as usize];
        let data = target.data.as_mut().unwrap();
        
        data[texel_offset] = ((rgb >> 16) & 0xff) as f32 * inv;
        data[texel_offset + 1] = ((rgb >> 8) & 0xff) as f32 * inv;
        data[texel_offset + 2] = (rgb & 0xff) as f32 * inv;
        
        if target.nbands == 4 {
            data[texel_offset + 3] = (rgb >> 24) as f32 * inv;
        }
    }
}
pub fn heman_draw_colored_circles(
    target: &mut HemanImageS,
    pts: &HemanImageS,
    radius: i32,
    colors: &[HemanColor],
) {
    let fwidth = (radius * 2) + 1;
    let radius2 = radius * radius;
    let src = pts.data.as_ref().expect("Points data is None");
    let mut src_idx = 0;
    let inv = 1.0f32 / 255.0f32;
    let w = target.width;
    let h = target.height;

    for k in 0..pts.width {
        let x = src[0 + src_idx as usize];
        let y = src[1 + src_idx as usize];
        src_idx += pts.nbands;

        let ii = (x * w as f32) as i32 - radius;
        let jj = (y * h as f32) as i32 - radius;

        for kj in 0..fwidth {
            for ki in 0..fwidth {
                let i = ii + ki;
                let j = jj + kj;

                let xw = (x * w as f32) as i32;
                let yh = (y * h as f32) as i32;
                let r2 = ((i - xw) * (i - xw)) + ((j - yh) * (j - yh));

                if r2 > radius2 {
                    continue;
                }

                if let Some(texel) = heman_image_texel(target, i, j) {
                    let mut texel_idx = 0;
                    let rgb = colors[k as usize];
                    
                    if let Some(data) = target.data.as_mut() {
                        data[texel_idx as usize] = ((rgb >> 16) as f32) * inv;
                        texel_idx += 1;
                        data[texel_idx as usize] = (((rgb >> 8) & 0xff) as f32) * inv;
                        texel_idx += 1;
                        data[texel_idx as usize] = ((rgb & 0xff) as f32) * inv;
                    }
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

    let pts = match pts {
        Some(p) => p,
        None => return,
    };

    let src = match &pts.data {
        Some(d) => d,
        None => return,
    };

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

                if let Some(texel) = heman_image_texel(target, i, j) {
                    let texel = match &mut target.data {
                        Some(d) => d,
                        None => continue,
                    };

                    let texel_idx = (j * w * target.nbands + i * target.nbands) as usize;
                    let splat_val = gaussian_splat[(kj * fwidth + ki) as usize];

                    for c in 0..target.nbands {
                        if let Some(texel_c) = texel.get_mut(texel_idx + c as usize) {
                            *texel_c += splat_val;
                        }
                    }
                }
            }
        }
    }
}
pub fn heman_draw_contour_from_points(
    target: &mut HemanImageS,
    coords: &HemanPoints,
    rgb: HemanColor,
    mind: f32,
    maxd: f32,
    filterd: i32,
) {
    assert!((target.nbands == 3) || (target.nbands == 4));
    let width = target.width;
    let height = target.height;
    
    let mut seed = heman_image_create(width, height, 1).expect("Failed to create seed image");
    heman_image_clear(seed.as_mut(), 0.0);
    heman_internal_draw_seeds(seed.as_mut(), coords, filterd);

    let inv = 1.0f32 / 255.0f32;
    let r = ((rgb >> 16) & 0xff) as f32 * inv;
    let g = ((rgb >> 8) & 0xff) as f32 * inv;
    let b = (rgb & 0xff) as f32 * inv;
    let mut a = 1.0f32;
    if target.nbands == 4 {
        a = ((rgb >> 24) as f32) * inv;
    }

    // Precompute values for the parallel loop
    let nbands = target.nbands as usize;
    let row_stride = (width as usize) * nbands;
    let is_4band = target.nbands == 4;
    let seed_ref = seed.as_ref(); // immutable reference to the seed image

    // Get the entire data vector as a mutable slice
    let data_slice = target.data.as_mut().unwrap().as_mut_slice();

    // Use rayon to process rows in parallel
    data_slice
        .par_chunks_mut(row_stride)
        .enumerate()
        .for_each(|(y_idx, row)| {
            let y = y_idx as i32;
            for x in 0..width {
                // Get the distance value at (x,y) from the seed image
                let dist = heman_image_texel(seed_ref, x, y)
                    .and_then(|texel| texel.first())
                    .copied()
                    .unwrap_or(0.0);

                if dist > mind && dist < maxd {
                    let idx = (x as usize) * nbands;
                    row[idx] = r;
                    row[idx + 1] = g;
                    row[idx + 2] = b;
                    if is_4band {
                        row[idx + 3] = a;
                    }
                }
            }
        });

    // Destroy the seed image
    heman_points_destroy(Some(seed));
}
