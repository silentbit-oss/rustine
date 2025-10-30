use crate::*;
use rand::Rng;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use std::f32;
use std::sync::Arc;
use std::sync::Mutex;
use rayon::prelude::*;


pub fn sphere(u: f32, v: f32, r: f32, dst: &mut KmVec3) {
    dst.x = (r * v.sin()) * u.cos();
    dst.y = r * v.cos();
    dst.z = (r * (-v.sin())) * u.sin();
}

pub fn helper_heman_generate_island_heightmap_2(
    width: i32,
    noisetex: &HemanImageS,
    data: &mut [f32],
    data_idx: usize,
    invh: f32,
    invw: f32,
    y: i32,
    heightmap: &HemanImageS,
) {
    let dst_start = data_idx + (y as usize * width as usize);
    let dst = &mut data[dst_start..dst_start + width as usize];
    
    for x in 0..width {
        let mut n = [0.0; 3];
        let u = x as f32 * invw;
        let v = y as f32 * invh;
        
        heman_image_sample(noisetex, u, v, &mut n);
        
        let mut z;
        {
            let mut z_slice = [0.0];
            heman_image_sample(heightmap, u, v, &mut z_slice);
            z = z_slice[0];
        }
        
        if z > 0.0 {
            let influence = z;
            let new_u = u + influence * n[1];
            let new_v = v + influence * n[2];
            
            {
                let mut z_slice = [0.0];
                heman_image_sample(heightmap, new_u, new_v, &mut z_slice);
                z = z_slice[0];
            }
            
            z += (6.0 * influence) * n[0];
        }
        
        dst[x as usize] = z;
    }
}

pub fn helper_heman_generate_archipelago_heightmap_2(
    width: i32,
    noisetex: &HemanImageS,
    data: &mut [f32],
    data_idx: usize,
    invh: f32,
    invw: f32,
    y: i32,
    heightmap: &HemanImageS,
) {
    let dst_start = data_idx + (y * width) as usize;
    let dst_slice = &mut data[dst_start..dst_start + width as usize];
    
    for x in 0..width {
        let mut n = [0.0; 3];
        let u = x as f32 * invw;
        let v = y as f32 * invh;
        
        heman_image_sample(noisetex, u, v, &mut n);
        
        let mut z;
        {
            let mut z_buf = [0.0; 1];
            heman_image_sample(heightmap, u, v, &mut z_buf);
            z = z_buf[0];
        }
        
        if z > 0.0 {
            let influence = z;
            let new_u = u + influence * n[1];
            let new_v = v + influence * n[2];
            
            {
                let mut z_buf = [0.0; 1];
                heman_image_sample(heightmap, new_u, new_v, &mut z_buf);
                z = z_buf[0];
            }
            
            z += (6.0 * influence) * n[0];
        }
        
        dst_slice[x as usize] = z;
    }
}
pub fn helper_heman_generate_archipelago_political_2_1(
    width: i32,
    sdf: &HemanImageS,
    noisetex: &HemanImageS,
    data: &mut [f32],
    invw: f32,
    invh: f32,
    y: i32,
) {
    let dst_start = (y * width) as usize;
    let dst_slice = &mut data[dst_start..dst_start + width as usize];
    let mut dst_idx = 0;

    for x in 0..width {
        let mut n = [0.0; 3];
        let mut u = x as f32 * invw;
        let mut v = y as f32 * invh;

        heman_image_sample(noisetex, u, v, &mut n);
        let mut z;
        {
            let mut z_temp = [0.0];
            heman_image_sample(sdf, u, v, &mut z_temp);
            z = z_temp[0];
        }

        if z > 0.0 {
            let influence = z;
            u += influence * n[1];
            v += influence * n[2];
            {
                let mut z_temp = [0.0];
                heman_image_sample(sdf, u, v, &mut z_temp);
                z = z_temp[0];
            }
            z += (6.0 * influence) * n[0];
        }

        dst_slice[dst_idx] = z;
        dst_idx += 1;
    }
}

pub fn helper_heman_generate_island_heightmap_1(
    width: i32,
    noisetex: &HemanImageS,
    data: &mut [f32],
    data_idx: usize,
    invh: f32,
    invw: f32,
    hh: i32,
    hw: i32,
    y: i32,
) {
    let vv = (y - hh) as f32 * invh;
    let dst_start = data_idx + (y * width) as usize;
    let dst_slice = &mut data[dst_start..dst_start + width as usize];

    for (dst_idx, x) in (0..width).enumerate() {
        let mut n = [0.0f32; 3];
        let v = y as f32 * invh;
        let u = x as f32 * invw;
        heman_image_sample(noisetex, u, v, &mut n);

        let mut u = (x - hw) as f32 * invw;
        let mut v = vv;
        u += n[1];
        v += n[2];

        let m = 0.707 - (u * u + v * v).sqrt();
        let m = m + n[0];
        dst_slice[dst_idx] = if m < SEALEVEL { 0.0 } else { 1.0 };
    }
}

pub fn helper_heman_generate_archipelago_heightmap_1(
    width: i32,
    noiseamt: f32,
    noisetex: &HemanImageS,
    data: &mut [f32],
    data_idx: usize,
    invh: f32,
    invw: f32,
    hh: i32,
    hw: i32,
    y: i32,
) {
    let vv = (y - hh) as f32 * invh;
    let dst_start = data_idx + (y * width) as usize;
    let dst_slice = &mut data[dst_start..dst_start + width as usize];
    
    for x in 0..width {
        let mut n = [0.0f32; 3];
        let v = y as f32 * invh;
        let mut u = x as f32 * invw;
        
        heman_image_sample(noisetex, u, v, &mut n);
        
        u = (x - hw) as f32 * invw;
        let v = vv;
        let u = u + noiseamt * n[1];
        let v = v + noiseamt * n[2];
        
        let m = dst_slice[x as usize];
        let m = m + noiseamt * n[0];
        dst_slice[x as usize] = if m < SEALEVEL { 0.0 } else { 1.0 };
    }
}

pub fn heman_internal_generate_rock_noise(width: i32, height: i32, seed: i64) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed, &mut ctx) {
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
pub fn heman_generate_rock_heightmap(width: i32, height: i32, seed: i64) -> Option<Box<HemanImageS>> {
    let noisetex = heman_internal_generate_rock_noise(width, height, seed)?;
    let mut heightmap = heman_image_create(width, height, 1)?;
    
    // Safe unwrap since we just created heightmap and it has data
    let data = heightmap.as_mut().data.as_mut().unwrap();
    
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let hh = height / 2;
    let hw = width / 2;

    for y in 0..height {
        let vv = (y - hh) as f32 * invh;
        let dst_start = (y * width) as usize;
        
        for x in 0..width {
            let v = y as f32 * invh;
            let u = x as f32 * invw;
            let mut n = [0.0f32];
            heman_image_sample(&noisetex, u, v, &mut n);
            
            let u = (x - hw) as f32 * invw;
            let v = vv;
            let r = 0.3 + n[0];
            
            let idx = dst_start + x as usize;
            if (u * u + v * v) > (r * r) {
                data[idx] = 0.0;
                continue;
            }
            
            let z = ((r * r - u * u) - v * v).sqrt();
            data[idx] = z;
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
    let pts_width = pts.as_ref().unwrap().width;
    let pts_nbands = pts.as_ref().unwrap().nbands;

    for _ in 0..pts_width {
        let x = src[src_idx];
        src_idx += 1;
        let y = src[src_idx];
        src_idx += 1;
        let mut strength = DEFAULT_STRENGTH;
        if pts_nbands == 3 {
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

                if let Some(texel) = heman_image_texel(target, i, j) {
                    if let Some(texel) = texel.first() {
                        let texel = *texel;
                        let d2 = ((i - ix) * (i - ix)) + ((j - iy) * (j - iy));
                        let dist = 1.0 - ((d2 as f32).sqrt() / radius as f32);
                        let new_val = strength * dist;
                        if texel <= new_val {
                            if let Some(data) = &mut target.data {
                                let idx = (j * w + i) as usize;
                                if idx < data.len() {
                                    data[idx] = new_val;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

pub fn helper_heman_generate_planet_heightmap_1(
    width: i32,
    ctx: &OsnContext,
    result: &mut HemanImageS,
    scalex: f32,
    scaley: f32,
    invh: f32,
    y: i32,
) {
    // Get mutable reference to the data vector, panicking if it's None
    let data = result.data.as_mut().expect("HemanImageS.data is None");
    
    // Calculate starting index for this row
    let start_idx = (y * width) as usize;
    let dst = &mut data[start_idx..start_idx + width as usize];
    
    let mut dst_idx = 0;
    let mut p = KmVec3 { x: 0.0, y: 0.0, z: 0.0 };
    let mut v = y as f32 * invh;
    let s = 0.95;
    
    // Calculate antarctic influence
    let temp = (10.0 * (v - s)) / s;
    let antarctic_influence = if temp > -0.5 { temp } else { -0.5 };
    
    v = f32::abs(v - 0.5);
    v = 1.5 * (0.5 - v);
    let equatorial_influence = v * v;
    
    v = y as f32 * scaley;
    
    for x in 0..width {
        let u = x as f32 * scalex;
        let mut freq = 1.0;
        let mut amp = 1.0;
        let mut h = antarctic_influence + equatorial_influence;
        
        for _oct in 0..6 {
            sphere(u, v, freq, &mut p);
            h += amp * open_simplex_noise3(ctx, p.x as f64, p.y as f64, p.z as f64) as f32;
            amp *= 0.5;
            freq *= 2.0;
        }
        
        dst[dst_idx] = h;
        dst_idx += 1;
    }
}

pub fn heman_generate_planet_heightmap(width: i32, height: i32, seed: i64) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed, &mut ctx) {
        return None;
    }

    let mut result = match heman_image_create(width, height, 1) {
        Some(img) => img,
        None => return None,
    };

    let scalex = (2.0f32 * 3.1415926535) / width as f32;
    let scaley = 3.1415926535 / height as f32;
    let invh = 1.0f32 / height as f32;

    // Parallel iteration using Rayon (assuming it's available)
    // If Rayon is not available, use a regular for loop
    for y in 0..height {
        if let Some(ref ctx_ref) = ctx {
            helper_heman_generate_planet_heightmap_1(
                width,
                ctx_ref,
                &mut result,
                scalex,
                scaley,
                invh,
                y,
            );
        }
    }

    open_simplex_noise_free(ctx);
    Some(result)
}
pub fn heman_internal_generate_island_noise(width: i32, height: i32, seed: i32) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    if let Err(_) = open_simplex_noise(seed as i64, &mut ctx) {
        return None;
    }

    let img = heman_image_create(width, height, 3);
    if img.is_none() {
        open_simplex_noise_free(ctx);
        return None;
    }

    let mut img = img.unwrap();
    let data = img.data.as_mut().unwrap();

    let invh = 1.0f32 / if width > height { width as f32 } else { height as f32 };
    let invw = invh; // Same as invh in original C code

    let freqs = [4.0, 16.0, 32.0, 64.0, 128.0];
    let ampls = [0.2, 0.1, 0.05, 0.025, 0.0125];

    for y in 0..height {
        let v = y as f32 * invh;
        let row_start = (y * width * 3) as usize;

        for x in 0..width {
            let u = x as f32 * invw;
            let pixel_start = row_start + (x * 3) as usize;

            // First channel
            data[pixel_start] = (ampls[0] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[0]) as f64, (v * freqs[0]) as f64) as f32 +
                               ampls[1] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[1]) as f64, (v * freqs[1]) as f64) as f32 +
                               ampls[2] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[2]) as f64, (v * freqs[2]) as f64) as f32);

            // Second channel
            data[pixel_start + 1] = (ampls[3] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[3]) as f64, (v * freqs[3]) as f64) as f32 +
                                  ampls[4] * open_simplex_noise2(ctx.as_ref().unwrap(), (u * freqs[4]) as f64, (v * freqs[4]) as f64) as f32);

            // Third channel (with offset u)
            let u_offset = u + 0.5;
            data[pixel_start + 2] = (ampls[3] * open_simplex_noise2(ctx.as_ref().unwrap(), (u_offset * freqs[3]) as f64, (v * freqs[3]) as f64) as f32 +
                                  ampls[4] * open_simplex_noise2(ctx.as_ref().unwrap(), (u_offset * freqs[4]) as f64, (v * freqs[4]) as f64) as f32);
        }
    }

    open_simplex_noise_free(ctx);
    Some(img)
}
pub fn heman_generate_archipelago_political_2(
    width: i32,
    height: i32,
    ocean: u32,  // Changed from HemanColor to u32 to avoid ambiguity
    seed: i32,
    political: &HemanImageS,
    invert: bool,
) -> HemanImage {
    // Line 3: Extract coastmask
    let coastmask = heman_ops_extract_mask(political, ocean, invert);
    let coastmask = match coastmask {
        Some(mask) => mask,
        None => return None,
    };

    // Line 4: Create SDF from coastmask
    let sdf = heman_distance_create_sdf(&coastmask);
    let sdf = match sdf {
        Some(sdf) => sdf,
        None => return None,
    };

    // Line 5: Destroy coastmask (drop in Rust)
    drop(coastmask);

    // Line 6: Create elevation image
    let elevation = heman_image_create(width, height, 1);
    let mut elevation = match elevation {
        Some(elev) => elev,
        None => return None,
    };

    // Line 7: Generate noise texture
    let noisetex = heman_internal_generate_island_noise(width, height, seed);
    let noisetex = match noisetex {
        Some(tex) => tex,
        None => return None,
    };

    // Line 8-11: Prepare data and inverse dimensions
    let data = match &mut elevation.data {
        Some(d) => d,
        None => return None,
    };
    let invw = 1.0 / width as f32;
    let invh = 1.0 / height as f32;

    // Line 12-16: Parallel processing (using rayon for parallelism)
    // Split the data into mutable chunks for parallel processing
    data.par_chunks_mut(width as usize).enumerate().for_each(|(y, chunk)| {
        helper_heman_generate_archipelago_political_2_1(
            width,
            &sdf,
            &noisetex,
            chunk,
            invw,
            invh,
            y as i32,
        );
    });

    // Line 18-19: Destroy temporary images (drop in Rust)
    drop(noisetex);
    drop(sdf);

    // Line 20: Return elevation
    Some(elevation)
}
pub fn heman_generate_archipelago_political_3(
    width: i32,
    height: i32,
    colors: &[u32],  // Changed from HemanColor to u32 to avoid ambiguity
    ncolors: i32,
    ocean: u32,      // Changed from HemanColor to u32 to avoid ambiguity
    seed: i32,
    political: &HemanImageS,
) -> HemanImage {
    // Create elevations vector
    let mut elevations: Vec<HemanImage> = (0..ncolors)
        .map(|cindex| {
            heman_generate_archipelago_political_2(
                width,
                height,
                colors[cindex as usize],
                seed,
                political,
                true,
            )
        })
        .collect();

    // Create and clear elevation image
    let mut elevation = match heman_image_create(width, height, 1) {
        Some(img) => *img,
        None => return None,
    };
    heman_image_clear(&mut elevation, 0.0);

    // Process each elevation
    for cindex in 0..ncolors {
        if let Some(current_elevation) = elevations[cindex as usize].as_ref() {
            let elevation_data = elevation.data.as_mut().unwrap();
            let current_data = current_elevation.data.as_ref().unwrap();
            
            // Split elevation_data into mutable chunks for parallel processing
            elevation_data.par_chunks_mut(width as usize).enumerate().for_each(|(y, dst_slice)| {
                let src_start = y * width as usize;
                let src_slice = &current_data[src_start..src_start + width as usize];
                
                for (dst, src) in dst_slice.iter_mut().zip(src_slice.iter()) {
                    if *src > *dst {
                        *dst = *src;
                    }
                }
            });
        }
        
        // Destroy the elevation after processing
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

    if let Some(ocean_elev) = ocean_elevation.as_ref() {
        let elevation_data = elevation.data.as_mut().unwrap();
        let ocean_data = ocean_elev.data.as_ref().unwrap();
        
        // Split elevation_data into mutable chunks for parallel processing
        elevation_data.par_chunks_mut(width as usize).enumerate().for_each(|(y, dst_slice)| {
            let src_start = y * width as usize;
            let src_slice = &ocean_data[src_start..src_start + width as usize];
            
            for (dst, src) in dst_slice.iter_mut().zip(src_slice.iter()) {
                if *src < 0.0 {
                    *dst = *src;
                }
            }
        });
    }

    heman_image_destroy(ocean_elevation);
    Some(Box::new(elevation))
}
pub fn heman_generate_archipelago_political_1(
    width: i32,
    height: i32,
    points: HemanPoints,
    colors: Option<&[u32]>,
    ocean: u32,
    seed: i32,
) -> HemanImage {
    // Create and clear the contour image
    let mut contour = match heman_image_create(width, height, 3) {
        Some(img) => *img,
        None => return None,
    };
    heman_image_clear(&mut contour, 0.0);

    // Draw contour and colored points
    if let Some(ref pts) = &points {
        heman_draw_contour_from_points(&mut contour, &points, ocean, 0.40, 0.41, 1);
        if let Some(colors) = colors {
            heman_draw_colored_points(&mut contour, pts, colors);
        }
    }

    // Create CPCF and warp it
    let contour_clone = contour.clone();
    let contour_box = Some(Box::new(contour_clone));
    let cf = heman_distance_create_cpcf(contour_box);
    let warped_cpcf = match cf.as_ref().map(|c| &**c) {
        Some(cf_img) => match heman_ops_warp(cf_img, seed, 4) {
            Some(img) => img,
            None => return None,
        },
        None => return None,
    };

    // Generate political map and clean up
    let political = heman_color_from_cpcf(Some(warped_cpcf.clone()), Some(Box::new(contour)));
    
    // Explicit cleanup
    heman_image_destroy(Some(warped_cpcf));
    heman_image_destroy(cf);
    
    political
}
pub fn heman_generate_archipelago_political(
    width: i32,
    height: i32,
    points: HemanPoints,
    colors: Option<&[u32]>,
    ocean: u32,
    seed: i32,
    elevation: &mut HemanImage,
    political: &mut HemanImage,
    elevation_mode: i32,
) {
    let ncolors = if elevation_mode != 0 {
        points.as_ref().unwrap().width
    } else {
        0
    };

    *political = heman_generate_archipelago_political_1(
        width, height, points, colors, ocean, seed,
    );

    if elevation_mode == 0 {
        *elevation = heman_generate_archipelago_political_2(
            width,
            height,
            ocean,
            seed,
            political.as_ref().unwrap(),
            false,
        );
    } else {
        *elevation = heman_generate_archipelago_political_3(
            width,
            height,
            colors.unwrap(),
            ncolors,
            ocean,
            seed,
            political.as_ref().unwrap(),
        );
    }
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
    if open_simplex_noise(seed as i64, &mut ctx).is_err() {
        return None;
    }

    let mut img = heman_image_create(width, height, 1)?;
    let data = img.data.as_mut()?;
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let mut ampl = amplitude;
    let mut freq = frequency;

    // Initialize data with zeros (equivalent to memset)
    data.fill(0.0);

    let mut remaining_octaves = octaves;
    while remaining_octaves > 0 {
        remaining_octaves -= 1;

        // Parallel processing of rows (equivalent to OpenMP parallel for)
        let ctx_ref = ctx.as_ref()?;
        let data_mutex = Mutex::new(&mut *data);
        (0..height).into_par_iter().for_each(|y| {
            let v = y as f32 * invh;
            let row_start = (y * width) as usize;
            let row_end = row_start + width as usize;
            
            let mut data_guard = data_mutex.lock().unwrap();
            let row_data = &mut data_guard[row_start..row_end];
            
            for x in 0..width {
                let u = x as f32 * invw;
                let idx = (x) as usize;
                row_data[idx] += ampl * open_simplex_noise2(ctx_ref, u as f64 * freq as f64, v as f64 * freq as f64) as f32;
            }
        });

        ampl *= gain;
        freq *= lacunarity;
    }

    open_simplex_noise_free(ctx);
    Some(img)
}
pub fn heman_generate_island_heightmap(width: i32, height: i32, seed: i32) -> HemanImage {
    let noisetex = heman_internal_generate_island_noise(width, height, seed);
    let coastmask = heman_image_create(width, height, 1);
    
    match (noisetex.as_ref(), coastmask.as_ref()) {
        (Some(noisetex_ref), Some(coastmask_ref)) => {
            let mut coastmask_data = coastmask_ref.data.as_ref().expect("coastmask data should exist").clone();
            let invh = 1.0f32 / height as f32;
            let invw = 1.0f32 / width as f32;
            let hh = height / 2;
            let hw = width / 2;

            // Parallel iteration over height (similar to OpenMP)
            (0..height).into_par_iter().for_each(|y| {
                let mut data = coastmask_data.clone();
                helper_heman_generate_island_heightmap_1(
                    width,
                    noisetex_ref,
                    &mut data,
                    0, // data_idx is 0 since we're working with the full slice
                    invh,
                    invw,
                    hh,
                    hw,
                    y,
                );
            });

            let heightmap = heman_distance_create_sdf(coastmask_ref);
            heman_image_destroy(coastmask);

            let result = heman_image_create(width, height, 1);

            match heightmap.as_ref().zip(result.as_ref()) {
                Some((heightmap_ref, result_ref)) => {
                    let mut result_data = result_ref.data.as_ref().expect("result data should exist").clone();

                    // Parallel iteration over height for second pass
                    (0..height).into_par_iter().for_each(|y| {
                        let mut data = result_data.clone();
                        helper_heman_generate_island_heightmap_2(
                            width,
                            noisetex_ref,
                            &mut data,
                            0, // data_idx is 0 since we're working with the full slice
                            invh,
                            invw,
                            y,
                            heightmap_ref,
                        );
                    });

                    heman_image_destroy(noisetex);
                    heman_image_destroy(heightmap);
                    result
                }
                _ => {
                    heman_image_destroy(noisetex);
                    heman_image_destroy(heightmap);
                    None
                }
            }
        }
        _ => {
            heman_image_destroy(noisetex);
            heman_image_destroy(coastmask);
            None
        }
    }
}

pub fn heman_generate_archipelago_heightmap(
    width: i32,
    height: i32,
    points: &HemanPoints,
    noiseamt: f32,
    seed: i32,
) -> HemanImage {
    let noisetex = heman_internal_generate_island_noise(width, height, seed);
    let mut coastmask = match heman_image_create(width, height, 1) {
        Some(img) => *img,
        None => return None,
    };
    heman_image_clear(&mut coastmask, 0.0);
    heman_internal_draw_seeds(&mut coastmask, points, 1);

    let data = coastmask.data.as_mut().unwrap();
    let data_idx = 0;
    let invh = 1.0f32 / height as f32;
    let invw = 1.0f32 / width as f32;
    let hh = height / 2;
    let hw = width / 2;

    // First parallel loop
    for y in 0..height {
        helper_heman_generate_archipelago_heightmap_1(
            width,
            noiseamt,
            noisetex.as_ref().unwrap(),
            data,
            data_idx,
            invh,
            invw,
            hh,
            hw,
            y,
        );
    }

    let heightmap = heman_distance_create_sdf(&coastmask);
    let mut result = match heman_image_create(width, height, 1) {
        Some(img) => *img,
        None => {
            heman_image_destroy(noisetex);
            heman_image_destroy(heightmap);
            return None;
        }
    };

    let result_data = result.data.as_mut().unwrap();
    let result_data_idx = 0;

    // Second parallel loop
    for y in 0..height {
        helper_heman_generate_archipelago_heightmap_2(
            width,
            noisetex.as_ref().unwrap(),
            result_data,
            result_data_idx,
            invh,
            invw,
            y,
            heightmap.as_ref().unwrap(),
        );
    }

    heman_image_destroy(noisetex);
    heman_image_destroy(heightmap);
    Some(Box::new(result))
}
