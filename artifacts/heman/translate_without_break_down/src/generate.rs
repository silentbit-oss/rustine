use crate::*;
use rand::Rng;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use libm::sqrtf;
use std::sync::Arc;
use rayon::prelude::*;
pub fn sphere(u: f32, v: f32, r: f32, dst: &mut KmVec3) {
    dst.x = (r * v.sin()) * u.cos();
    dst.y = r * v.cos();
    dst.z = (r * (-v.sin())) * u.sin();
}

pub fn heman_internal_generate_rock_noise(width: i32, height: i32, seed: i32) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed as i64, &mut ctx) {
        return None;
    }

    let mut img = heman_image_create(width, height, 1);
    if img.is_none() {
        open_simplex_noise_free(ctx);
        return None;
    }

    let img_inner = img.as_mut().unwrap();
    let data = img_inner.data.as_mut().unwrap();
    
    let invh = 1.0 / (if width > height { width } else { height }) as f32;
    let invw = 1.0 / (if width > height { width } else { height }) as f32;
    let freqs = [2.0, 4.0, 16.0];
    let ampls = [0.2, 0.05, 0.01];

    for y in 0..height {
        let v = y as f32 * invh;
        let row_start = (y * width) as usize;
        
        for x in 0..width {
            let u = x as f32 * invw;
            let idx = row_start + x as usize;
            
            let noise = ampls[0] * open_simplex_noise2(ctx.as_ref().unwrap(), 
                                (u * freqs[0]) as f64, 
                                (v * freqs[0]) as f64) as f32
                       + ampls[1] * open_simplex_noise2(ctx.as_ref().unwrap(), 
                                (u * freqs[1]) as f64, 
                                (v * freqs[1]) as f64) as f32
                       + ampls[2] * open_simplex_noise2(ctx.as_ref().unwrap(), 
                                (u * freqs[2]) as f64, 
                                (v * freqs[2]) as f64) as f32;
            
            data[idx] = noise;
        }
    }

    open_simplex_noise_free(ctx);
    img
}
pub fn heman_generate_rock_heightmap(width: i32, height: i32, seed: i32) -> Option<Box<HemanImageS>> {
    let noisetex = heman_internal_generate_rock_noise(width, height, seed)?;
    let mut heightmap = heman_image_create(width, height, 1)?;
    
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let hh = height / 2;
    let hw = width / 2;

    // Get the data reference separately from heightmap operations
    let data = heightmap.as_mut().data.as_mut()?;
    
    for y in 0..height {
        let vv = (y - hh) as f32 * invh;
        let dst_start = (y * width) as usize;
        let dst_end = dst_start + width as usize;
        let dst_slice = &mut data[dst_start..dst_end];

        for x in 0..width {
            let v = y as f32 * invh;
            let u = x as f32 * invw;
            let mut n = [0.0f32];
            
            // Sample from the noise texture instead of heightmap
            heman_image_sample(noisetex.as_ref(), u, v, &mut n);
            
            let u = (x - hw) as f32 * invw;
            let v = vv;
            let r = 0.3 + n[0];

            let idx = x as usize;
            if (u * u + v * v) > (r * r) {
                dst_slice[idx] = 0.0;
                continue;
            }

            let z = ((r * r - u * u - v * v).max(0.0)).sqrt();
            dst_slice[idx] = z;
        }
    }

    heman_image_destroy(Some(noisetex));
    Some(heightmap)
}
pub fn heman_internal_draw_seeds(target: &mut HemanImageS, pts: &HemanPoints, filterd: i32) {
    
    let radius = target.width / filterd;
    let fwidth = (radius * 2) + 1;
    let src = match &pts.as_ref().unwrap().data {
        Some(data) => data,
        None => return,
    };
    let mut src_idx = 0;
    let w = target.width;
    let h = target.height;
    
    for _ in 0..pts.as_ref().unwrap().width {
        let x = src[src_idx];
        src_idx += 1;
        let y = src[src_idx];
        src_idx += 1;
        let mut strength = DEFAULT_STRENGTH;
        if pts.as_ref().unwrap().nbands == 3 {
            strength = src[src_idx];
            src_idx += 1;
        }
        strength = SEALEVEL + (strength * 0.1);
        let ix = (x * w as f32) as i32;
        let iy = (y * h as f32) as i32;
        let ii = ix - radius;
        let jj = iy - radius;
        
        for kj in 0..fwidth {
            for ki in 0..fwidth {
                let i = ii + ki;
                let j = jj + kj;
                if i < 0 || i >= w || j < 0 || j >= h {
                    continue;
                }
                
                let texel = match heman_image_texel(target, i, j) {
                    Some(texel) => texel,
                    None => continue,
                };
                let texel = &mut target.data.as_mut().unwrap()[(j * w + i) as usize];
                let d2 = ((i - ix) * (i - ix)) + ((j - iy) * (j - iy));
                let dist = 1.0 - (sqrtf(d2 as f32) / radius as f32);
                *texel = if *texel > strength * dist { *texel } else { strength * dist };
            }
        }
    }
}
pub fn heman_internal_generate_island_noise(width: i32, height: i32, seed: i64) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if open_simplex_noise(seed, &mut ctx).is_err() {
        return None;
    }

    let img = heman_image_create(width, height, 3);
    if img.is_none() {
        open_simplex_noise_free(ctx);
        return None;
    }

    let mut img = img.unwrap();
    let data = img.data.as_mut().unwrap();

    let invh = 1.0 / (if width > height { width } else { height }) as f32;
    let invw = 1.0 / (if width > height { width } else { height }) as f32;
    let freqs = [4.0, 16.0, 32.0, 64.0, 128.0];
    let ampls = [0.2, 0.1, 0.05, 0.025, 0.0125];

    for y in 0..height {
        let v = y as f32 * invh;
        let dst_start = (y * width * 3) as usize;
        
        for x in 0..width {
            let u = x as f32 * invw;
            let dst_idx = dst_start + (x * 3) as usize;

            data[dst_idx] = ampls[0] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[0]) as f64, (v * freqs[0]) as f64) as f32 +
                           ampls[1] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[1]) as f64, (v * freqs[1]) as f64) as f32 +
                           ampls[2] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[2]) as f64, (v * freqs[2]) as f64) as f32;

            data[dst_idx + 1] = ampls[3] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[3]) as f64, (v * freqs[3]) as f64) as f32 +
                               ampls[4] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[4]) as f64, (v * freqs[4]) as f64) as f32;

            let u_shifted = u + 0.5;
            data[dst_idx + 2] = ampls[3] * open_simplex_noise2(ctx.as_ref().unwrap(), (u_shifted * freqs[3]) as f64, (v * freqs[3]) as f64) as f32 +
                               ampls[4] * open_simplex_noise2(ctx.as_ref().unwrap(), (u_shifted * freqs[4]) as f64, (v * freqs[4]) as f64) as f32;
        }
    }

    open_simplex_noise_free(ctx);
    Some(img)
}
pub fn heman_generate_archipelago_political_2(
    width: i32,
    height: i32,
    ocean: HemanColor,
    seed: i64,
    political: &HemanImageS,
    invert: bool,
) -> HemanImage {
    // Step 1: Create coastmask
    let coastmask = match heman_ops_extract_mask(political, ocean, invert) {
        Some(img) => img,
        None => return None,
    };

    // Step 2: Create SDF from coastmask
    let sdf = match heman_distance_create_sdf(&coastmask) {
        Some(img) => img,
        None => {
            heman_image_destroy(Some(coastmask));
            return None;
        }
    };

    // Clean up coastmask as we don't need it anymore
    heman_image_destroy(Some(coastmask));

    // Step 3: Create elevation image
    let mut elevation = match heman_image_create(width, height, 1) {
        Some(img) => img,
        None => {
            heman_image_destroy(Some(sdf));
            return None;
        }
    };

    // Step 4: Generate noise texture
    let noisetex = match heman_internal_generate_island_noise(width, height, seed) {
        Some(img) => img,
        None => {
            heman_image_destroy(Some(sdf));
            heman_image_destroy(Some(elevation));
            return None;
        }
    };

    // Get mutable access to elevation data
    let elevation_data = match &mut elevation.data {
        Some(data) => data,
        None => {
            heman_image_destroy(Some(sdf));
            heman_image_destroy(Some(elevation));
            heman_image_destroy(Some(noisetex));
            return None;
        }
    };

    let invw = 1.0 / width as f32;
    let invh = 1.0 / height as f32;

    // Process each pixel
    for y in 0..height {
        for x in 0..width {
            let u = x as f32 * invw;
            let v = y as f32 * invh;
            
            let mut n = [0.0; 3];
            heman_image_sample(&noisetex, u, v, &mut n);
            
            let mut z_arr = [0.0; 1];
            heman_image_sample(&sdf, u, v, &mut z_arr);
            let mut z = z_arr[0];
            
            if z > 0.0 {
                let influence = z;
                let new_u = u + influence * n[1];
                let new_v = v + influence * n[2];
                heman_image_sample(&sdf, new_u, new_v, &mut z_arr);
                z = z_arr[0];
                z += (6.0 * influence) * n[0];
            }
            
            let idx = (y * width + x) as usize;
            elevation_data[idx] = z;
        }
    }

    // Clean up temporary resources
    heman_image_destroy(Some(noisetex));
    heman_image_destroy(Some(sdf));

    Some(elevation)
}

pub fn heman_generate_archipelago_political_3(
    width: i32,
    height: i32,
    colors: &[HemanColor],
    ncolors: i32,
    ocean: HemanColor,
    seed: i64,
    political: &HemanImageS,
) -> HemanImage {
    // Create a vector to store elevations
    let mut elevations: Vec<HemanImage> = Vec::with_capacity(ncolors as usize);
    
    // Generate elevations for each color
    for cindex in 0..ncolors {
        let elevation = heman_generate_archipelago_political_2(
            width,
            height,
            colors[cindex as usize],
            seed,
            political,
            true,
        );
        elevations.push(elevation);
    }

    // Create and clear the output elevation image
    let mut elevation = match heman_image_create(width, height, 1) {
        Some(img) => *img,
        None => return None,
    };
    heman_image_clear(&mut elevation, 0.0);

    // Process each elevation layer
    for cindex in 0..ncolors {
        if let Some(elev_img) = &elevations[cindex as usize] {
            for y in 0..height {
                let dst_start = (y * width) as usize;
                let dst_end = dst_start + width as usize;
                let dst_slice = &mut elevation.data.as_mut().unwrap()[dst_start..dst_end];
                
                let src_start = (y * width) as usize;
                let src_slice = &elev_img.data.as_ref().unwrap()[src_start..src_start + width as usize];
                
                for x in 0..width as usize {
                    if src_slice[x] > dst_slice[x] {
                        dst_slice[x] = src_slice[x];
                    }
                }
            }
        }
        heman_image_destroy(elevations[cindex as usize].take());
    }

    // Process ocean elevation
    let ocean_elevation = heman_generate_archipelago_political_2(
        width,
        height,
        ocean,
        seed,
        political,
        false,
    );

    if let Some(ocean_img) = &ocean_elevation {
        for y in 0..height {
            let dst_start = (y * width) as usize;
            let dst_end = dst_start + width as usize;
            let dst_slice = &mut elevation.data.as_mut().unwrap()[dst_start..dst_end];
            
            let src_start = (y * width) as usize;
            let src_slice = &ocean_img.data.as_ref().unwrap()[src_start..src_start + width as usize];
            
            for x in 0..width as usize {
                if src_slice[x] < 0.0 {
                    dst_slice[x] = src_slice[x];
                }
            }
        }
    }

    heman_image_destroy(ocean_elevation);
    Some(Box::new(elevation))
}
pub fn heman_generate_archipelago_political_1(
    width: i32,
    height: i32,
    points: &HemanPoints,
    colors: &[HemanColor],
    ocean: HemanColor,
    seed: i32,
) -> HemanImage {
    // Create and clear the contour image
    let mut contour = match heman_image_create(width, height, 3) {
        Some(c) => c,
        None => return None,
    };
    heman_image_clear(&mut *contour, 0.0);

    // Draw contour and colored points
    heman_draw_contour_from_points(&mut *contour, points, ocean, 0.40, 0.41, 1);
    heman_draw_colored_points(&mut *contour, points, colors);

    // Create distance field and warp it
    let cf = heman_distance_create_cpcf(Some(&*contour));
    let warped_cpcf = match heman_ops_warp(&*cf.as_ref().unwrap(), seed, 4) {
        Some(w) => w,
        None => {
            heman_image_destroy(cf);
            return None;
        }
    };

    // Generate political map and clean up
    let political = heman_color_from_cpcf(Some(&*warped_cpcf), Some(&*contour));
    
    // Explicitly drop the intermediate images
    heman_image_destroy(Some(warped_cpcf));
    heman_image_destroy(cf);
    
    political
}
pub fn heman_generate_archipelago_political(
    width: i32,
    height: i32,
    points: &HemanPoints,
    colors: &[HemanColor],
    ocean: HemanColor,
    seed: i32,
    elevation: &mut HemanImage,
    political: &mut HemanImage,
    elevation_mode: i32,
) {
    *political = heman_generate_archipelago_political_1(
        width, height, points, colors, ocean, seed,
    );

    let political_ref = political.as_ref().unwrap().as_ref();
    
    *elevation = if elevation_mode == 0 {
        heman_generate_archipelago_political_2(
            width,
            height,
            ocean,
            seed as i64,
            political_ref,
            false,
        )
    } else {
        let ncolors = points.as_ref().unwrap().width;
        heman_generate_archipelago_political_3(
            width,
            height,
            colors,
            ncolors,
            ocean,
            seed as i64,
            political_ref,
        )
    };
}
pub fn heman_generate_simplex_fbm(
    width: i32,
    height: i32,
    frequency: f32,
    amplitude: f32,
    octaves: i32,
    lacunarity: f32,
    gain: f32,
    seed: i32,
) -> Option<Box<HemanImageS>> {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed as i64, &mut ctx) {
        return None;
    }

    let mut img = heman_image_create(width, height, 1)?;
    let data = match img.data.as_mut() {
        Some(d) => d,
        None => return None,
    };
    
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let mut ampl = amplitude;
    let mut freq = frequency;

    // Initialize data with zeros (equivalent to memset)
    for val in data.iter_mut() {
        *val = 0.0;
    }

    let mut remaining_octaves = octaves;
    while remaining_octaves > 0 {
        remaining_octaves -= 1;

        for y in 0..height {
            let v = y as f32 * invh;
            let row_start = (y * width) as usize;
            
            for x in 0..width {
                let u = x as f32 * invw;
                let idx = row_start + x as usize;
                if let Some(ctx_ref) = &ctx {
                    data[idx] += ampl * open_simplex_noise2(
                        ctx_ref,
                        (u * freq) as f64,
                        (v * freq) as f64,
                    ) as f32;
                }
            }
        }

        ampl *= gain;
        freq *= lacunarity;
    }

    open_simplex_noise_free(ctx);
    Some(img)
}
pub fn heman_generate_island_heightmap(width: i32, height: i32, seed: i64) -> Option<Box<HemanImageS>> {
    let noisetex = heman_internal_generate_island_noise(width, height, seed)?;
    let noisetex_ref = noisetex.as_ref();
    
    let mut coastmask = heman_image_create(width, height, 1)?;
    let coastmask_ref = coastmask.as_mut();
    let data = coastmask_ref.data.as_mut().unwrap();
    
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let hh = height / 2;
    let hw = width / 2;

    // First parallel processing block
    data.par_chunks_mut(width as usize).enumerate().for_each(|(y, row)| {
        let vv = (y as i32 - hh) as f32 * invh;
        
        for x in 0..width {
            let mut n = [0.0f32; 3];
            let v = y as f32 * invh;
            let u = x as f32 * invw;
            heman_image_sample(noisetex_ref, u, v, &mut n);
            
            let u = (x - hw) as f32 * invw;
            let v = vv;
            let u = u + n[1];
            let v = v + n[2];
            let m = 0.707 - ((u * u) + (v * v)).sqrt();
            let m = m + n[0];
            
            row[x as usize] = if m < SEALEVEL { 0.0 } else { 1.0 };
        }
    });

    let heightmap = heman_distance_create_sdf(coastmask_ref)?;
    let heightmap_ref = heightmap.as_ref();
    
    let mut result = heman_image_create(width, height, 1)?;
    let result_ref = result.as_mut();
    let result_data = result_ref.data.as_mut().unwrap();

    // Second parallel processing block
    result_data.par_chunks_mut(width as usize).enumerate().for_each(|(y, row)| {
        for x in 0..width {
            let mut n = [0.0f32; 3];
            let u = x as f32 * invw;
            let v = y as f32 * invh;
            heman_image_sample(noisetex_ref, u, v, &mut n);
            
            let mut z_buf = [0.0f32; 1];
            heman_image_sample(heightmap_ref, u, v, &mut z_buf);
            let mut z = z_buf[0];
            
            if z > 0.0 {
                let influence = z;
                let u = u + influence * n[1];
                let v = v + influence * n[2];
                heman_image_sample(heightmap_ref, u, v, &mut z_buf);
                z = z_buf[0];
                z += (6.0 * influence) * n[0];
            }
            
            row[x as usize] = z;
        }
    });

    Some(result)
}

pub fn heman_generate_planet_heightmap(width: i32, height: i32, seed: i32) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed as i64, &mut ctx) {
        return None;
    }

    let result = heman_image_create(width, height, 1);
    if result.is_none() {
        open_simplex_noise_free(ctx);
        return None;
    }

    let mut result = result.unwrap();
    let scalex = (2.0f32 * PI) / width as f32;
    let scaley = PI / height as f32;
    let invh = 1.0f32 / height as f32;

    for y in 0..height {
        let dst_start = (y * width) as usize;
        let dst_slice = if let Some(ref mut data) = result.data {
            &mut data[dst_start..dst_start + width as usize]
        } else {
            open_simplex_noise_free(ctx);
            return None;
        };

        let mut p = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
        let v = y as f32 * invh;
        let s = 0.95;
        let antarctic_influence = if (10.0 * (v - s) / s) > -0.5 {
            (10.0 * (v - s) / s)
        } else {
            -0.5
        };
        let mut v = (v - 0.5).abs();
        v = 1.5 * (0.5 - v);
        let equatorial_influence = v * v;
        let v = y as f32 * scaley;

        for x in 0..width {
            let u = x as f32 * scalex;
            let mut freq = 1.0;
            let mut amp = 1.0;
            let mut h = antarctic_influence + equatorial_influence;

            for _oct in 0..6 {
                sphere(u, v, freq, &mut p);
                h += amp * open_simplex_noise3(
                    ctx.as_ref().unwrap(),
                    p.x as f64,
                    p.y as f64,
                    p.z as f64,
                ) as f32;
                amp *= 0.5;
                freq *= 2.0;
            }

            dst_slice[x as usize] = h;
        }
    }

    open_simplex_noise_free(ctx);
    Some(result)
}
pub fn heman_generate_archipelago_heightmap(
    width: i32,
    height: i32,
    points: &HemanPoints,
    noiseamt: f32,
    seed: i64,
) -> HemanImage {
    let noisetex = heman_internal_generate_island_noise(width, height, seed);
    let mut coastmask = heman_image_create(width, height, 1);
    heman_image_clear(coastmask.as_deref_mut().expect("Failed to create coastmask"), 0.0);
    heman_internal_draw_seeds(coastmask.as_deref_mut().expect("Failed to create coastmask"), points, 1);

    let invh = 1.0 / height as f32;
    let invw = 1.0 / width as f32;
    let hh = height / 2;
    let hw = width / 2;

    // First parallel processing block
    {
        let coastmask_ref = coastmask.as_deref_mut().unwrap();
        let data = coastmask_ref.data.as_mut().expect("No data in coastmask");
        let data_slice = data.as_mut_slice();
        data_slice.par_chunks_mut(width as usize).enumerate().for_each(|(y_index, row)| {
            let y = y_index as i32;
            let vv = (y - hh) as f32 * invh;
            for x in 0..width {
                let mut n = [0.0; 3];
                let v = y as f32 * invh;
                let u = x as f32 * invw;
                heman_image_sample(noisetex.as_deref().unwrap(), u, v, &mut n);

                let u = (x - hw) as f32 * invw;
                let v = vv;
                let u_noised = u + noiseamt * n[1];
                let v_noised = v + noiseamt * n[2];

                let idx = x as usize;
                let m = row[idx] + noiseamt * n[0];
                row[idx] = if m < SEALEVEL { 0.0 } else { 1.0 };
            }
        });
    }

    let heightmap = heman_distance_create_sdf(coastmask.as_deref().expect("coastmask is None"));
    heman_image_destroy(coastmask);

    let mut result = heman_image_create(width, height, 1);
    
    // Second parallel processing block
    {
        let result_ref = result.as_deref_mut().expect("Failed to create result image");
        let result_data = result_ref.data.as_mut().expect("No data in result");
        let result_slice = result_data.as_mut_slice();
        let noisetex_ref = noisetex.as_deref().expect("noisetex is None");
        let heightmap_ref = heightmap.as_deref().expect("heightmap is None");

        result_slice.par_chunks_mut(width as usize).enumerate().for_each(|(y_index, row)| {
            let y = y_index as i32;
            for x in 0..width {
                let mut n = [0.0; 3];
                let u = x as f32 * invw;
                let v = y as f32 * invh;
                heman_image_sample(noisetex_ref, u, v, &mut n);

                let mut z_arr = [0.0; 1];
                heman_image_sample(heightmap_ref, u, v, &mut z_arr);
                let mut z = z_arr[0];

                if z > 0.0 {
                    let influence = z;
                    let u_noised = u + influence * n[1];
                    let v_noised = v + influence * n[2];
                    heman_image_sample(heightmap_ref, u_noised, v_noised, &mut z_arr);
                    z = z_arr[0];
                    z += (6.0 * influence) * n[0];
                }

                row[x as usize] = z;
            }
        });
    }

    heman_image_destroy(noisetex);
    heman_image_destroy(heightmap);
    result
}
