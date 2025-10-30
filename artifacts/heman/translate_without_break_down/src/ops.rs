use crate::*;
use std::assert;
use std::f32;
use rand::Rng;
use std::cmp::max;
use std::cmp::min;
use rayon::prelude::*;

pub fn heman_get_num_threads() -> i32 {
    extern "C" {
        fn omp_get_max_threads() -> i32;
    }
    unsafe { omp_get_max_threads() }
}
pub fn qselect(v: &mut [f32], k: usize) -> f32 {
    let len = v.len();
    if len == 1 {
        return v[0];
    }

    let mut st = 0;
    for i in 0..len - 1 {
        if v[i] > v[len - 1] {
            continue;
        }
        v.swap(i, st);
        st += 1;
    }

    v.swap(len - 1, st);

    match k.cmp(&st) {
        std::cmp::Ordering::Equal => v[st],
        std::cmp::Ordering::Less => qselect(&mut v[0..st], k),
        std::cmp::Ordering::Greater => qselect(&mut v[st..], k - st),
    }
}
pub fn heman_ops_accumulate(dst: &mut HemanImageS, src: &HemanImageS) {
    assert!(dst.nbands == src.nbands);
    assert!(dst.width == src.width);
    assert!(dst.height == src.height);
    
    let size = dst.height * dst.width;
    
    if let (Some(sdata), Some(ddata)) = (&src.data, &mut dst.data) {
        for i in 0..size {
            ddata[i as usize] += sdata[i as usize];
        }
    }
}
pub fn heman_ops_stitch_vertical(images: &[HemanImage], count: i32) -> HemanImage {
    assert!(count > 0);
    let first_image = images[0].as_ref().expect("First image must exist");
    let width = first_image.width;
    let height = first_image.height;
    let nbands = first_image.nbands;

    for i in 1..count {
        let image = images[i as usize].as_ref().expect("Image must exist");
        assert!(image.width == width);
        assert!(image.height == height);
        assert!(image.nbands == nbands);
    }

    let mut result = heman_image_create(width, height * count, nbands);
    let result_inner = result.as_mut().expect("Result image must exist");
    let size = (width * height) * nbands;
    let mut dst_idx = 0;

    for tile in 0..count {
        let tile_image = images[tile as usize].as_ref().expect("Tile image must exist");
        let src_data = tile_image.data.as_ref().expect("Tile data must exist");
        let dst_data = result_inner.data.as_mut().expect("Result data must exist");

        let dst_slice = &mut dst_data[dst_idx as usize..(dst_idx + size) as usize];
        dst_slice.copy_from_slice(&src_data[..size as usize]);
        dst_idx += size;
    }

    result
}

pub fn heman_ops_normalize_f32(source: HemanImage, minv: f32, maxv: f32) -> HemanImage {
    // Unwrap the source image safely
    let source = match source {
        Some(s) => s,
        None => return None,
    };

    // Create result image with same dimensions
    let mut result = match heman_image_create(source.width, source.height, source.nbands) {
        Some(r) => r,
        None => return None,
    };

    // Get source and destination data as mutable slices
    let src_data = match source.data {
        Some(ref data) => data,
        None => return None,
    };
    let dst_data = match result.data {
        Some(ref mut data) => data,
        None => return None,
    };

    // Calculate normalization parameters
    let scale = 1.0f32 / (maxv - minv);
    let size = (source.height * source.width * source.nbands) as usize;

    // Perform normalization
    for i in 0..size {
        let v = (src_data[i] - minv) * scale;
        dst_data[i] = v.clamp(0.0, 1.0); // Equivalent to the ternary operation in C
    }

    Some(result)
}
pub fn heman_ops_max(imga: &HemanImageS, imgb: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(imga.width == imgb.width);
    assert!(imga.height == imgb.height);
    assert!(imga.nbands == imgb.nbands);
    
    let mut result = heman_image_create(imga.width, imga.height, imga.nbands)?;
    
    let size = (imga.height * imga.width) * imga.nbands;
    let srca = imga.data.as_ref()?;
    let srcb = imgb.data.as_ref()?;
    
    if let Some(result_data) = result.data.as_mut() {
        for i in 0..size {
            let srca_val = srca[i as usize];
            let srcb_val = srcb[i as usize];
            result_data[i as usize] = if srca_val > srcb_val { srca_val } else { srcb_val };
        }
    }
    
    Some(result)
}
pub fn heman_ops_step(hmap: &HemanImageS, threshold: f32) -> HemanImage {
    assert!(hmap.nbands == 1, "Input image must have exactly 1 band");
    
    let mut result = heman_image_create(hmap.width, hmap.height, 1);
    if let Some(ref mut result) = result {
        let size = hmap.height * hmap.width;
        let src = hmap.data.as_ref().expect("Input image data is None");
        let dst = result.data.as_mut().expect("Result image data is None");
        
        for (i, &val) in src.iter().enumerate().take(size as usize) {
            dst[i] = if val >= threshold { 1.0 } else { 0.0 };
        }
    }
    
    result
}

pub fn heman_ops_sweep(hmap: HemanImage) -> HemanImage {
    // Unwrap the HemanImage (Option<Box<HemanImageS>>) safely
    let hmap = match hmap {
        Some(h) => h,
        None => return None,
    };

    // Check assertion (nbands == 1)
    assert!(hmap.nbands == 1, "Input image must have exactly 1 band");

    // Create result image
    let mut result = match heman_image_create(hmap.height, 1, 1) {
        Some(r) => r,
        None => return None,
    };

    // Get mutable access to result data
    let dst = match &mut result.data {
        Some(d) => d,
        None => return None,
    };

    // Get source data
    let src = match &hmap.data {
        Some(s) => s,
        None => return None,
    };

    let invw = 1.0f32 / hmap.width as f32;
    let mut dst_idx = 0;
    let mut src_idx = 0;

    for _y in 0..hmap.height {
        let mut acc = 0.0f32;
        
        for _x in 0..hmap.width {
            acc += src[src_idx];
            src_idx += 1;
        }

        dst[dst_idx] = acc * invw;
        dst_idx += 1;
    }

    Some(result)
}
pub fn heman_ops_warp_core(
    img: &HemanImageS,
    secondary: Option<&mut HemanImageS>,
    seed: i32,
    octaves: i32,
) -> Option<Box<HemanImageS>> {
    let mut ctx: Option<Box<OsnContext>> = None;
    open_simplex_noise(seed as i64, &mut ctx).ok()?;

    let width = img.width;
    let height = img.height;
    let nbands = img.nbands;
    let mut result = heman_image_create(width, height, nbands);
    let mut result2 = if let Some(sec) = &secondary {
        heman_image_create(width, height, sec.nbands)
    } else {
        None
    };

    let invw = 1.0 / width as f32;
    let invh = 1.0 / height as f32;
    let inv = if invw > invh { invh } else { invw };
    let aspect = width as f32 / height as f32;
    let gain = 0.6;
    let lacunarity = 2.0;
    let initial_amplitude = 0.05;
    let initial_frequency = 8.0;

    // Process each pixel in parallel (using rayon for parallel iteration)
    if let Some(ref mut res) = result.as_mut() {
        (0..height).into_iter().for_each(|y| {
            let dst_start = (y * width * nbands) as usize;
            let dst_slice = &mut res.data.as_mut().unwrap()[dst_start..dst_start + (width * nbands) as usize];

            for x in 0..width {
                let mut a = initial_amplitude;
                let mut f = initial_frequency;

                if nbands == 4 {
                    if let Some(src) = heman_image_texel(img, x, y) {
                        let elev = 1.0 - src[3];
                        a *= elev.powf(4.0);
                    }
                }

                let s = x as f32 * inv;
                let t = y as f32 * inv;
                let mut u = x as f32 * invw;
                let mut v = y as f32 * invh;

                for _ in 0..octaves {
                    if let Some(ref ctx_inner) = ctx {
                        u += a * open_simplex_noise2(ctx_inner, s as f64 * f as f64, t as f64 * f as f64) as f32;
                        v += aspect * (a * open_simplex_noise2(ctx_inner, (s as f64 * f as f64) + 0.5, t as f64 * f as f64) as f32);
                    }
                    a *= gain;
                    f *= lacunarity;
                }

                let i = std::cmp::max(0, std::cmp::min(width - 1, (u * width as f32) as i32));
                let j = std::cmp::max(0, std::cmp::min(height - 1, (v * height as f32) as i32));

                if let Some(src) = heman_image_texel(img, i, j) {
                    for n in 0..nbands {
                        dst_slice[(x * nbands + n) as usize] = src[n as usize];
                    }
                }

                // Handle secondary image with direct vector access
                if let Some(sec) = secondary.as_ref() {
                    if let Some(ref mut res2) = result2.as_mut() {
                        if let Some(src) = heman_image_texel(sec, x, y) {
                            let idx2 = (j as usize) * (width as usize) * (sec.nbands as usize) + 
                                        (i as usize) * (sec.nbands as usize);
                            let end_idx = idx2 + sec.nbands as usize;
                            let slice = &mut res2.data.as_mut().unwrap()[idx2..end_idx];
                            slice.copy_from_slice(src);
                        }
                    }
                }
            }
        });
    }

    open_simplex_noise_free(ctx);

    if let Some(sec) = secondary {
        if let Some(mut res2) = result2 {
            sec.data = res2.data.take();
        }
    }

    result
}
pub fn heman_ops_warp(img: &HemanImageS, seed: i32, octaves: i32) -> Option<Box<HemanImageS>> {
    heman_ops_warp_core(img, None, seed, octaves)
}
pub fn copy_row(src: &HemanImageS, dst: &mut HemanImageS, dstx: i32, y: i32) {
    let width = src.width;
    
    if src.nbands == 1 {
        for x in 0..width {
            if let Some(srcp) = heman_image_texel(src, x, y) {
                let srcp_idx = 0;
                if let Some(dst_data) = dst.data.as_mut() {
                    let dst_idx = ((y * dst.width + dstx + x) * dst.nbands) as usize;
                    if dst_idx < dst_data.len() {
                        dst_data[dst_idx] = srcp[srcp_idx];
                    }
                }
            }
        }
        return;
    }

    for x in 0..width {
        if let Some(srcp) = heman_image_texel(src, x, y) {
            let mut srcp_idx = 0;
            if let Some(dst_data) = dst.data.as_mut() {
                let mut dst_idx = ((y * dst.width + dstx + x) * dst.nbands) as usize;
                let mut nbands = src.nbands;
                while nbands > 0 {
                    if dst_idx < dst_data.len() && srcp_idx < srcp.len() {
                        dst_data[dst_idx] = srcp[srcp_idx];
                    }
                    srcp_idx += 1;
                    dst_idx += 1;
                    nbands -= 1;
                }
            }
        }
    }
}
pub fn _match(mask: &HemanImageS, mask_color: HemanColor, invert_mask: bool, pixel_index: usize) -> bool {
    // Get the pixel data from the mask
    let mcolor = match &mask.data {
        Some(data) => {
            let start = pixel_index * 3;
            // Ensure we don't go out of bounds
            if start + 2 >= data.len() {
                return false;
            }
            &data[start..start+3]
        },
        None => return false,
    };

    // Convert mask color components to u8
    let r1 = (mcolor[0] * 255.0) as u8;
    let g1 = (mcolor[1] * 255.0) as u8;
    let b1 = (mcolor[2] * 255.0) as u8;

    // Extract components from mask_color (HemanColor)
    let r2 = (mask_color >> 16) as u8;
    let g2 = ((mask_color >> 8) & 0xff) as u8;
    let b2 = (mask_color & 0xff) as u8;

    // Compare colors
    let retval = (r1 == r2) && (g1 == g2) && (b1 == b2);

    // Apply inversion if needed
    if invert_mask {
        !retval
    } else {
        retval
    }
}
pub fn heman_ops_stitch_horizontal(images: &[HemanImage], count: i32) -> HemanImage {
    assert!(count > 0);
    let first_image = images[0].as_ref().unwrap();
    let width = first_image.width;
    let height = first_image.height;
    let nbands = first_image.nbands;

    for i in 1..count as usize {
        let image = images[i].as_ref().unwrap();
        assert!(image.width == width);
        assert!(image.height == height);
        assert!(image.nbands == nbands);
    }

    let mut result = heman_image_create(width * count, height, nbands).unwrap();

    for y in 0..height {
        for tile in 0..count as usize {
            copy_row(
                images[tile].as_ref().unwrap(),
                &mut *result,
                (tile as i32) * width,
                y,
            );
        }
    }

    Some(result)
}
pub fn heman_ops_stairstep<'a>(
    hmap: &'a mut HemanImageS,
    nsteps: i32,
    mask: Option<&'a HemanImageS>,
    mask_color: HemanColor,
    invert_mask: bool,
    offset: f32,
) -> &'a mut HemanImageS {
    // Assertions (converted to Rust's debug_assert!)
    debug_assert!(hmap.nbands == 1);
    debug_assert!(mask.map_or(true, |m| m.nbands == 3));

    let size = (hmap.height * hmap.width) as usize;
    let src = hmap.data.as_mut().expect("hmap.data must be Some");

    // Find min and max values
    let (minv, maxv) = src.iter().enumerate().fold(
        (f32::INFINITY, f32::NEG_INFINITY),
        |(mut minv, mut maxv), (i, &val)| {
            if mask.map_or(true, |m| _match(m, mask_color, invert_mask, i)) {
                minv = minv.min(val);
                maxv = maxv.max(val);
            }
            (minv, maxv)
        },
    );

    let range = maxv - minv;

    // Process each pixel
    for (i, pixel) in src.iter_mut().enumerate().take(size) {
        if mask.map_or(true, |m| _match(m, mask_color, invert_mask, i)) {
            let mut e = *pixel - minv;
            e /= range;
            e = (e * nsteps as f32).floor() / nsteps as f32;
            e = (e * range) + minv;
            *pixel = e + offset;
        } else {
            *pixel += offset;
        }
    }

    hmap
}
pub fn heman_ops_laplacian(heightmap: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(heightmap.nbands == 1);
    let width = heightmap.width;
    let height = heightmap.height;
    let mut result = heman_image_create(width, height, 1)?;
    
    let maxx = width - 1;
    let maxy = height - 1;
    
    // Get mutable reference to the result's data
    let result_data = match result.data.as_mut() {
        Some(data) => data,
        None => return None,
    };

    for y in 0..height {
        let y1 = if y + 1 > maxy { maxy } else { y + 1 };
        let dst_start = (y * width) as usize;
        let dst_end = dst_start + width as usize;
        let dst_row = &mut result_data[dst_start..dst_end];
        
        for x in 0..width {
            let x1 = if x + 1 > maxx { maxx } else { x + 1 };
            
            let p = heman_image_texel(&heightmap, x, y).and_then(|v| v.first())?;
            let px = heman_image_texel(&heightmap, x1, y).and_then(|v| v.first())?;
            let py = heman_image_texel(&heightmap, x, y1).and_then(|v| v.first())?;
            
            dst_row[x as usize] = (p - px).powi(2) + (p - py).powi(2);
        }
    }
    
    Some(result)
}
pub fn heman_ops_extract_mask(
    source: &HemanImageS,
    color: HemanColor,
    invert: bool,
) -> Option<Box<HemanImageS>> {
    assert!(source.nbands == 3);
    let inv = 1.0f32 / 255.0f32;
    let r = ((color >> 16) as f32) * inv;
    let g = (((color >> 8) & 0xff) as f32) * inv;
    let b = ((color & 0xff) as f32) * inv;
    let height = source.height;
    let width = source.width;

    let mut result = heman_image_create(width, height, 1)?;
    
    if let (Some(src_data), Some(dst_data)) = (&source.data, &mut result.data) {
        // Convert to mutable slices for parallel processing
        let src_slice = src_data.as_slice();
        let dst_slice = unsafe { std::slice::from_raw_parts_mut(dst_data.as_mut_ptr(), (width * height) as usize) };

        // Process each row in parallel
        dst_slice.par_chunks_mut(width as usize).enumerate().for_each(|(y, row)| {
            let y = y as i32;
            let src_start = (y * width * 3) as usize;

            for x in 0..width as usize {
                let src_idx = src_start + (x * 3);
                
                let val = (src_slice[src_idx] == r)
                    && (src_slice[src_idx + 1] == g)
                    && (src_slice[src_idx + 2] == b);

                let val_f32 = if val { 1.0 } else { 0.0 };
                let final_val = if invert { val_f32 } else { 1.0 - val_f32 };
                row[x] = final_val;
            }
        });
    }

    Some(result)
}
pub fn heman_ops_replace_color(
    source: &HemanImageS,
    color: HemanColor,
    texture: &HemanImageS,
) -> Option<Box<HemanImageS>> {
    // Assertions converted to debug_assert! (only active in debug builds)
    debug_assert!(source.nbands == 3);
    debug_assert!(texture.nbands == 3);
    let height = source.height;
    let width = source.width;
    debug_assert!(texture.width == width);
    debug_assert!(texture.height == height);

    let inv = 1.0f32 / 255.0f32;
    let r = ((color >> 16) as f32) * inv;
    let g = (((color >> 8) & 0xff) as f32) * inv;
    let b = ((color & 0xff) as f32) * inv;

    // Create result image
    let mut result = heman_image_create(width, height, 3)?;

    if let (Some(source_data), Some(texture_data), Some(result_data)) = (
        source.data.as_ref(),
        texture.data.as_ref(),
        result.data.as_mut(),
    ) {
        // Parallel processing using rayon
        result_data
            .par_chunks_mut(3)
            .zip(source_data.par_chunks(3))
            .zip(texture_data.par_chunks(3))
            .for_each(|((dst, src), tex)| {
                if (src[0] == r) && (src[1] == g) && (src[2] == b) {
                    dst[0] = tex[0];
                    dst[1] = tex[1];
                    dst[2] = tex[2];
                } else {
                    dst[0] = src[0];
                    dst[1] = src[1];
                    dst[2] = src[2];
                }
            });
    }

    Some(result)
}
pub fn heman_ops_merge_political(
    hmap: &HemanImageS,
    cmap: &HemanImageS,
    ocean: HemanColor,
) -> Option<Box<HemanImageS>> {
    // Assertions (lines 3-4)
    assert!(hmap.nbands == 1, "hmap must have 1 band");
    assert!(cmap.nbands == 3, "cmap must have 3 bands");

    // Create result image (line 5)
    let mut result = heman_image_create(hmap.width, hmap.height, 4)?;
    let result = result.as_mut();

    // Get data references (lines 6-11)
    let pheight = hmap.data.as_ref().unwrap();
    let pcolour = cmap.data.as_ref().unwrap();
    let pmerged = result.data.as_mut().unwrap();

    // Calculate ocean color components (lines 12-15)
    let inv = 1.0f32 / 255.0f32;
    let oceanr = ((ocean >> 16) as f32) * inv;
    let oceang = (((ocean >> 8) & 0xff) as f32) * inv;
    let oceanb = ((ocean & 0xff) as f32) * inv;

    // Calculate size (line 16)
    let size = (hmap.height * hmap.width) as usize;

    // Find min and max height (lines 17-23)
    let (minh, maxh) = pheight.iter().fold((1000.0f32, -1000.0f32), |(min, max), &h| {
        (min.min(h), max.max(h))
    });

    // Process each pixel (lines 25-53)
    let mut pheight_idx = 0;
    let mut pcolour_idx = 0;
    let mut pmerged_idx = 0;

    for _ in 0..size {
        let h = pheight[pheight_idx];
        pheight_idx += 1;

        if h < 0.0 {
            // Ocean case (lines 30-38)
            pmerged[pmerged_idx] = oceanr;
            pmerged_idx += 1;
            pmerged[pmerged_idx] = oceang;
            pmerged_idx += 1;
            pmerged[pmerged_idx] = oceanb;
            pmerged_idx += 1;
            pcolour_idx += 3;
        } else {
            // Land case (lines 40-50)
            pmerged[pmerged_idx] = pcolour[pcolour_idx];
            pcolour_idx += 1;
            pmerged_idx += 1;
            pmerged[pmerged_idx] = pcolour[pcolour_idx];
            pcolour_idx += 1;
            pmerged_idx += 1;
            pmerged[pmerged_idx] = pcolour[pcolour_idx];
            pcolour_idx += 1;
            pmerged_idx += 1;
        }

        // Normalized height (lines 51-52)
        pmerged[pmerged_idx] = (h - minh) / (maxh - minh);
        pmerged_idx += 1;
    }

    Some(Box::new(result.clone()))
}
pub fn heman_ops_percentiles<'a>(
    hmap: &'a mut HemanImageS,
    nsteps: i32,
    mask: Option<&'a HemanImageS>,
    mask_color: HemanColor,
    invert_mask: bool,
    offset: f32,
) -> &'a mut HemanImageS {
    // Assertions (lines 3-4)
    assert!(hmap.nbands == 1);
    if let Some(mask) = mask {
        assert!(mask.nbands == 3);
    }

    let size = hmap.height * hmap.width;
    let src = hmap.data.as_mut().expect("hmap.data is None");
    let mut src_idx = 0;
    let mut minv: f32 = 1000.0;
    let mut maxv: f32 = -1000.0;
    let mut npixels: usize = 0;

    // First pass: find min/max and count pixels (lines 11-19)
    for i in 0..size as usize {
        if mask.is_none() || _match(mask.unwrap(), mask_color, invert_mask, i) {
            let val = src[i + src_idx];
            minv = minv.min(val);
            maxv = maxv.max(val);
            npixels += 1;
        }
    }

    // Second pass: collect values (lines 21-30)
    let mut vals = Vec::with_capacity(npixels);
    npixels = 0;
    for i in 0..size as usize {
        if mask.is_none() || _match(mask.unwrap(), mask_color, invert_mask, i) {
            vals.push(src[i + src_idx]);
            npixels += 1;
        }
    }

    // Calculate percentiles (lines 32-37)
    let mut percentiles = Vec::with_capacity(nsteps as usize);
    for tier in 0..nsteps {
        let k = (tier * npixels as i32) / nsteps;
        let height = qselect(&mut vals, k as usize);
        percentiles.push(height);
    }

    // Apply percentiles with offset (lines 39-57)
    src_idx = 0;
    for i in 0..size as usize {
        let mut e = src[src_idx];
        if mask.is_none() || _match(mask.unwrap(), mask_color, invert_mask, i) {
            for tier in (0..nsteps).rev() {
                if e > percentiles[tier as usize] {
                    e = percentiles[tier as usize];
                    break;
                }
            }
        }
        src[src_idx] = e + offset;
        src_idx += 1;
    }

    hmap
}
pub fn heman_ops_warp_points(
    img: &HemanImageS,
    seed: i32,
    octaves: i32,
    pts: &mut HemanPoints,
) -> Option<Box<HemanImageS>> {
    let width = img.width;
    let height = img.height;
    let mut mapping = heman_distance_identity_cpcf(width, height);
    
    let retval = {
        let mapping_ref = mapping.as_mut()?;
        heman_ops_warp_core(img, Some(mapping_ref), seed, octaves)
    };

    if let Some(pts_box) = pts.as_mut() {
        let src = pts_box.data.as_mut()?;
        let mut src_idx = 0usize;
        for _ in 0..pts_box.width {
            let x = src[0 + src_idx];
            let y = src[1 + src_idx];
            let mapping_ref = mapping.as_ref()?;
            let i = (x * mapping_ref.width as f32) as i32;
            let j = (y * mapping_ref.height as f32) as i32;

            if i < 0 || i >= mapping_ref.width || j < 0 || j >= mapping_ref.height {
                src_idx += pts_box.nbands as usize;
                continue;
            }

            if let Some(texel) = heman_image_texel(mapping_ref, i, j) {
                src[0 + src_idx] = texel[0] / mapping_ref.width as f32;
                src[1 + src_idx] = texel[1] / mapping_ref.height as f32;
            }
            src_idx += pts_box.nbands as usize;
        }
    }

    heman_image_destroy(mapping);
    retval
}
pub fn heman_ops_emboss(img: &HemanImageS, mode: i32) -> Option<Box<HemanImageS>> {
    let seed = 1;
    let octaves = 4;
    let mut ctx: Option<Box<OsnContext>> = None;
    open_simplex_noise(seed as i64, &mut ctx).unwrap();

    let width = img.width;
    let height = img.height;
    assert!(img.nbands == 1);

    let mut result = heman_image_create(width, height, 1)?;

    let invw = 1.0 / width as f32;
    let invh = 1.0 / height as f32;
    let inv = if invw > invh { invh } else { invw };
    let gain = 0.6;
    let lacunarity = 2.0;
    let land_amplitude = 0.0005;
    let land_frequency = 256.0;
    let ocean_amplitude = 0.5;
    let ocean_frequency = 1.0;

    // Initialize data if not present
    if result.data.is_none() {
        result.data = Some(vec![0.0; (width * height) as usize]);
    }
    let data = result.data.as_mut().unwrap();

    for y in 0..height {
        let row_start = (y * width) as usize;
        for x in 0..width {
            let z = *heman_image_texel(img, x, y)?.first()?;
            let mut z = z;

            if z > 0.0 && mode == 1 {
                let s = x as f32 * inv;
                let t = y as f32 * inv;
                let mut a = land_amplitude;
                let mut f = land_frequency;
                for _ in 0..octaves {
                    z += a * open_simplex_noise2(ctx.as_ref().unwrap(), s as f64 * f as f64, t as f64 * f as f64) as f32;
                    a *= gain;
                    f *= lacunarity;
                }
            } else if z <= 0.0 && mode == -1 {
                z = if z > -0.1 { z } else { -0.1 };
                let soften = f32::abs(z);
                let s = x as f32 * inv;
                let t = y as f32 * inv;
                let mut a = ocean_amplitude;
                let mut f = ocean_frequency;
                for _ in 0..octaves {
                    z += soften * (a * open_simplex_noise2(ctx.as_ref().unwrap(), s as f64 * f as f64, t as f64 * f as f64) as f32);
                    a *= gain;
                    f *= lacunarity;
                }
            }

            data[row_start + x as usize] = z;
        }
    }

    open_simplex_noise_free(ctx);
    Some(result)
}
pub fn heman_ops_sobel(img: HemanImage, rgb: HemanColor) -> HemanImage {
    // Unwrap the image safely
    let img = match img {
        Some(img) => img,
        None => return None,
    };

    let width = img.width;
    let height = img.height;
    assert!(img.nbands == 3);

    let mut result = match heman_image_create(width, height, 3) {
        Some(result) => result,
        None => return None,
    };

    let gray = match heman_color_to_grayscale(Some(img.clone())) {
        Some(gray) => gray,
        None => return None,
    };

    let inv = 1.0f32 / 255.0f32;
    let edge_rgb = KmVec3 {
        x: ((rgb >> 16) as f32) * inv,
        y: (((rgb >> 8) & 0xff) as f32) * inv,
        z: ((rgb & 0xff) as f32) * inv,
    };

    // Collect all processed rows first
    let processed_rows: Vec<Vec<f32>> = (0..height).into_par_iter().map(|y| {
        let mut dst_row = Vec::with_capacity(width as usize * 3);
        let mut src_row = Vec::with_capacity(width as usize * 3);

        // Get source and destination data
        if let (Some(result_data), Some(img_data)) = (&result.data, &img.data) {
            let dst_start = (y * width * 3) as usize;
            let src_start = (y * width * 3) as usize;

            dst_row.extend_from_slice(&result_data[dst_start..dst_start + (width * 3) as usize]);
            src_row.extend_from_slice(&img_data[src_start..src_start + (width * 3) as usize]);
        }

        for x in 0..width {
            let xm1 = if x - 1 > 0 { x - 1 } else { 0 };
            let xp1 = if x + 1 > width - 1 { width - 1 } else { x + 1 };
            let ym1 = if y - 1 > 0 { y - 1 } else { 0 };
            let yp1 = if y + 1 > height - 1 { height - 1 } else { y + 1 };

            let t00 = heman_image_texel(&gray, xm1, ym1).unwrap()[0];
            let t10 = heman_image_texel(&gray, x, ym1).unwrap()[0];
            let t20 = heman_image_texel(&gray, xp1, ym1).unwrap()[0];
            let t01 = heman_image_texel(&gray, xm1, y).unwrap()[0];
            let t21 = heman_image_texel(&gray, xp1, y).unwrap()[0];
            let t02 = heman_image_texel(&gray, xm1, yp1).unwrap()[0];
            let t12 = heman_image_texel(&gray, x, yp1).unwrap()[0];
            let t22 = heman_image_texel(&gray, xp1, yp1).unwrap()[0];

            let gx = ((t00 + (2.0 * t01) + t02) - t20 - (2.0 * t21) - t22);
            let gy = ((t00 + (2.0 * t10) + t20) - t02 - (2.0 * t12) - t22);
            let is_edge = (gx * gx + gy * gy) > 1e-5;

            let src_vec = KmVec3 {
                x: src_row[x as usize * 3],
                y: src_row[x as usize * 3 + 1],
                z: src_row[x as usize * 3 + 2],
            };

            let mut dst_vec = KmVec3 {
                x: dst_row[x as usize * 3],
                y: dst_row[x as usize * 3 + 1],
                z: dst_row[x as usize * 3 + 2],
            };

            kmVec3Lerp(&mut dst_vec, &src_vec, &edge_rgb, if is_edge { 1.0 } else { 0.0 });

            dst_row[x as usize * 3] = dst_vec.x;
            dst_row[x as usize * 3 + 1] = dst_vec.y;
            dst_row[x as usize * 3 + 2] = dst_vec.z;
        }

        dst_row
    }).collect();

    // Write back all processed rows sequentially
    if let Some(result_data) = &mut result.data {
        for (y, row) in processed_rows.into_iter().enumerate() {
            let dst_start = (y as i32 * width * 3) as usize;
            result_data[dst_start..dst_start + (width * 3) as usize].copy_from_slice(&row);
        }
    }

    heman_image_destroy(Some(gray));
    Some(result)
}
