use crate::*;
use std::assert;
use std::f32;
use rand::Rng;
use std::f32::consts::E;
use std::sync::Arc;
use std::sync::Mutex;
use rayon::prelude::*;
pub fn heman_get_num_threads() -> i32 {
    std::thread::available_parallelism()
        .map(|n| n.get() as i32)
        .unwrap_or(1)
}
pub fn helper_heman_ops_merge_political_1(
    pheight_idx_ref: &mut u32,
    pcolour_idx_ref: &mut u32,
    pmerged_idx_ref: &mut u32,
    pheight: &[f32],
    pcolour: &[f32],
    pmerged: &mut [f32],
    oceanr: f32,
    oceang: f32,
    oceanb: f32,
    minh: f32,
    maxh: f32,
) {
    let mut pheight_idx = *pheight_idx_ref;
    let mut pcolour_idx = *pcolour_idx_ref;
    let mut pmerged_idx = *pmerged_idx_ref;

    let h = pheight[pheight_idx as usize];
    pheight_idx += 1;

    if h < 0.0 {
        pmerged[pmerged_idx as usize] = oceanr;
        pmerged_idx += 1;
        pmerged[pmerged_idx as usize] = oceang;
        pmerged_idx += 1;
        pmerged[pmerged_idx as usize] = oceanb;
        pmerged_idx += 1;
        pcolour_idx += 3;
    } else {
        pmerged[pmerged_idx as usize] = pcolour[pcolour_idx as usize];
        pcolour_idx += 1;
        pmerged_idx += 1;
        pmerged[pmerged_idx as usize] = pcolour[pcolour_idx as usize];
        pcolour_idx += 1;
        pmerged_idx += 1;
        pmerged[pmerged_idx as usize] = pcolour[pcolour_idx as usize];
        pcolour_idx += 1;
        pmerged_idx += 1;
    }

    pmerged[pmerged_idx as usize] = (h - minh) / (maxh - minh);
    pmerged_idx += 1;

    *pheight_idx_ref = pheight_idx;
    *pcolour_idx_ref = pcolour_idx;
    *pmerged_idx_ref = pmerged_idx;
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
        std::cmp::Ordering::Less => qselect(&mut v[..st], k),
        std::cmp::Ordering::Greater => qselect(&mut v[st + 1..], k - st - 1),
    }
}
pub fn heman_ops_accumulate(dst: &mut HemanImageS, src: &HemanImageS) {
    // Use assert_eq! for equality checks (equivalent to C's assert)
    assert_eq!(dst.nbands, src.nbands);
    assert_eq!(dst.width, src.width);
    assert_eq!(dst.height, src.height);
    
    let size = dst.height * dst.width;
    
    // Safely access the data vectors (using Option's as_ref() and as_mut())
    let sdata = src.data.as_ref().expect("Source data is None");
    let ddata = dst.data.as_mut().expect("Destination data is None");
    
    // Iterate through the data using zip() for parallel iteration
    for (d, s) in ddata.iter_mut().zip(sdata.iter()) {
        *d += s;
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
    let size = (width * height) * nbands;
    let result_inner = result.as_mut().expect("Result image must exist");
    
    let mut dst_idx = 0;
    for tile in 0..count {
        let tile_image = images[tile as usize].as_ref().expect("Tile image must exist");
        let tile_data = tile_image.data.as_ref().expect("Tile data must exist");
        let result_data = result_inner.data.as_mut().expect("Result data must exist");
        
        let dst_slice = &mut result_data[dst_idx as usize..(dst_idx + size) as usize];
        dst_slice.copy_from_slice(&tile_data[..size as usize]);
        
        dst_idx += size;
    }

    result
}

pub fn heman_ops_normalize_f32(source: HemanImage, minv: f32, maxv: f32) -> HemanImage {
    // Check if source exists and has data
    let source = match source {
        Some(s) => s,
        None => return None,
    };

    // Create result image with same dimensions
    let mut result = match heman_image_create(source.width, source.height, source.nbands) {
        Some(r) => r,
        None => return None,
    };

    // Get source and destination data
    let src_data = match source.data {
        Some(data) => data,
        None => return None,
    };
    let dst_data = match result.data.as_mut() {
        Some(data) => data,
        None => return None,
    };

    // Calculate scale factor
    let scale = 1.0f32 / (maxv - minv);
    let size = (source.height * source.width) * source.nbands;

    // Normalize each value
    for i in 0..size {
        let v = (src_data[i as usize] - minv) * scale;
        dst_data[i as usize] = v.clamp(0.0, 1.0);
    }

    Some(result)
}

pub fn heman_ops_max(imga: HemanImage, imgb: HemanImage) -> HemanImage {
    // Unwrap the Option<Box<HemanImageS>> to access the inner struct
    let imga = imga.unwrap();
    let imgb = imgb.unwrap();

    // Assert dimensions match (using Rust's assert! macro)
    assert!(imga.width == imgb.width);
    assert!(imga.height == imgb.height);
    assert!(imga.nbands == imgb.nbands);

    // Create result image with same dimensions
    let mut result = heman_image_create(imga.width, imga.height, imga.nbands).unwrap();
    
    // Calculate total elements
    let size = (imga.height * imga.width) * imga.nbands;
    
    // Get references to the data vectors
    let srca = imga.data.as_ref().unwrap();
    let srcb = imgb.data.as_ref().unwrap();
    let dst = result.data.as_mut().unwrap();

    // Perform element-wise max operation
    for i in 0..size as usize {
        dst[i] = if srca[i] > srcb[i] { srca[i] } else { srcb[i] };
    }

    Some(result)
}
pub fn heman_ops_step(hmap: &HemanImageS, threshold: f32) -> HemanImage {
    assert!(hmap.nbands == 1, "Input image must have exactly 1 band");
    
    let mut result = heman_image_create(hmap.width, hmap.height, 1);
    if let Some(ref mut result) = result {
        let size = hmap.height * hmap.width;
        let src = hmap.data.as_ref().expect("Input image data is missing");
        let dst = result.data.as_mut().expect("Output image data is missing");
        
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

    // Assert nbands == 1 as in original C code
    assert!(hmap.nbands == 1, "Input image must have exactly 1 band");

    // Create result image using the translated heman_image_create function
    let mut result = match heman_image_create(hmap.height, 1, 1) {
        Some(r) => r,
        None => return None,
    };

    // Get mutable access to result's data
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
pub fn helper_helper_heman_ops_warp_core_1_1(
    dst_idx_ref: &mut u32,
    img: &HemanImageS,
    secondary: Option<&HemanImageS>,
    octaves: i32,
    ctx: &OsnContext,
    width: i32,
    height: i32,
    nbands: i32,
    result2: Option<&mut HemanImageS>,
    invw: f32,
    invh: f32,
    inv: f32,
    aspect: f32,
    gain: f32,
    lacunarity: f32,
    initial_amplitude: f32,
    initial_frequency: f32,
    y: i32,
    dst: &mut [f32],
    x: i32,
) {
    let mut dst_idx = *dst_idx_ref;
    let mut a = initial_amplitude;
    let mut f = initial_frequency;
    let mut src_idx = 0;

    if nbands == 4 {
        if let Some(texel) = heman_image_texel(img, x, y) {
            let elev = 1.0 - texel[3];
            a *= elev.powf(4.0);
        }
    }

    let s = x as f32 * inv;
    let t = y as f32 * inv;
    let mut u = x as f32 * invw;
    let mut v = y as f32 * invh;

    for _ in 0..octaves {
        u += a * open_simplex_noise2(ctx, s as f64 * f as f64, t as f64 * f as f64) as f32;
        v += aspect * a * open_simplex_noise2(ctx, (s as f64 * f as f64) + 0.5, t as f64 * f as f64) as f32;
        a *= gain;
        f *= lacunarity;
    }

    let i = (0.0 as f32).max((width - 1) as f32).min(u * width as f32) as i32;
    let j = (0.0 as f32).max((height - 1) as f32).min(v * height as f32) as i32;

    if let Some(texel) = heman_image_texel(img, i, j) {
        for n in 0..nbands {
            dst[dst_idx as usize] = texel[n as usize];
            src_idx += 1;
            dst_idx += 1;
        }
    }

    if let Some(secondary_img) = secondary {
        if let Some(result2_img) = result2 {
            if let Some(texel) = heman_image_texel(secondary_img, x, y) {
                // Get mutable access to the result image's data directly
                if let Some(data) = &mut result2_img.data {
                    let idx = (j * result2_img.width + i) as usize * result2_img.nbands as usize;
                    for n in 0..secondary_img.nbands {
                        if (idx + n as usize) < data.len() {
                            data[idx + n as usize] = texel[n as usize];
                        }
                        src_idx += 1;
                    }
                }
            }
        }
    }

    *dst_idx_ref = dst_idx;
}
pub fn helper_heman_ops_warp_core_1(
    img: &HemanImageS,
    secondary: Option<&HemanImageS>,
    octaves: i32,
    ctx: &OsnContext,
    width: i32,
    height: i32,
    nbands: i32,
    result: &mut HemanImageS,
    mut result2: Option<&mut HemanImageS>,
    invw: f32,
    invh: f32,
    inv: f32,
    aspect: f32,
    gain: f32,
    lacunarity: f32,
    initial_amplitude: f32,
    initial_frequency: f32,
    y: i32,
) {
    // Get mutable reference to result's data, handling the Option
    if let Some(data) = &mut result.data {
        // Calculate the starting index for this row
        let start_idx = (y * width * nbands) as usize;
        // Get mutable slice for the current row
        let dst = &mut data[start_idx..start_idx + (width * nbands) as usize];
        
        let mut dst_idx = 0u32;
        
        // Iterate over each x coordinate in the row
        for x in 0..width {
            helper_helper_heman_ops_warp_core_1_1(
                &mut dst_idx,
                img,
                secondary,
                octaves,
                ctx,
                width,
                height,
                nbands,
                result2.as_deref_mut(),
                invw,
                invh,
                inv,
                aspect,
                gain,
                lacunarity,
                initial_amplitude,
                initial_frequency,
                y,
                dst,
                x,
            );
        }
    }
}
pub fn heman_ops_warp_core(
    img: &HemanImageS,
    secondary: Option<&mut HemanImageS>,
    seed: i32,
    octaves: i32,
) -> HemanImage {
    let mut ctx: Option<Box<OsnContext>> = None;
    open_simplex_noise(seed as i64, &mut ctx).unwrap();

    let width = img.width;
    let height = img.height;
    let nbands = img.nbands;
    let mut result = heman_image_create(width, height, nbands);
    let mut result2 = if let Some(secondary) = secondary.as_ref() {
        heman_image_create(width, height, secondary.nbands)
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

    // Parallel iteration using rayon
    (0..height).into_iter().for_each(|y| {
        helper_heman_ops_warp_core_1(
            img,
            secondary.as_ref().map(|s| &**s),
            octaves,
            ctx.as_ref().unwrap(),
            width,
            height,
            nbands,
            result.as_mut().unwrap().as_mut(),
            result2.as_mut().map(|r| r.as_mut()),
            invw,
            invh,
            inv,
            aspect,
            gain,
            lacunarity,
            initial_amplitude,
            initial_frequency,
            y,
        );
    });

    open_simplex_noise_free(ctx);

    if let Some(secondary) = secondary {
        if let Some(mut result2) = result2 {
            secondary.data = result2.as_mut().data.take();
        }
    }

    result
}
pub fn heman_ops_warp(img: &HemanImageS, seed: i32, octaves: i32) -> HemanImage {
    heman_ops_warp_core(img, None, seed, octaves)
}
pub fn copy_row(src: &HemanImageS, dst: &mut HemanImageS, dstx: i32, y: i32) {
    let width = src.width;
    
    if src.nbands == 1 {
        for x in 0..width {
            let srcp = heman_image_texel(src, x, y).unwrap();
            let srcp_idx = 0;
            let dstp = heman_image_texel(dst, dstx + x, y).unwrap();
            let dstp_idx = 0;
            // Since we're working with slices, we need to get mutable access
            // We'll use a separate scope to limit the mutable borrow
            {
                let dstp_mut = &mut dst.data.as_mut().unwrap()[dstp_idx..dstp_idx+1];
                dstp_mut[0] = srcp[srcp_idx];
            }
        }
        return;
    }

    for x in 0..width {
        let srcp = heman_image_texel(src, x, y).unwrap();
        let mut srcp_idx = 0;
        let dstp = heman_image_texel(dst, dstx + x, y).unwrap();
        let mut dstp_idx = 0;
        let mut nbands = src.nbands;
        
        while nbands > 0 {
            // Again, use a separate scope for mutable access
            {
                let dstp_mut = &mut dst.data.as_mut().unwrap()[dstp_idx..dstp_idx+1];
                dstp_mut[0] = srcp[srcp_idx];
            }
            srcp_idx += 1;
            dstp_idx += 1;
            nbands -= 1;
        }
    }
}
pub fn _match(mask: &HemanImageS, mask_color: u32, invert_mask: bool, pixel_index: usize) -> bool {
    // Get the pixel data from the mask
    let mcolor = match &mask.data {
        Some(data) => {
            let start = pixel_index * 3;
            &data[start..start + 3]
        }
        None => return false, // Return false if no data is available
    };

    // Extract RGB components from the mask pixel
    let r1 = (mcolor[0] * 255.0) as u8;
    let g1 = (mcolor[1] * 255.0) as u8;
    let b1 = (mcolor[2] * 255.0) as u8;

    // Extract RGB components from the mask_color
    let r2 = (mask_color >> 16) as u8;
    let g2 = (mask_color >> 8) as u8;
    let b2 = mask_color as u8;

    // Compare the colors
    let retval = (r1 == r2) && (g1 == g2) && (b1 == b2);

    // Apply inversion if needed
    if invert_mask {
        !retval
    } else {
        retval
    }
}
pub fn heman_ops_stitch_horizontal(images: &[Arc<HemanImageS>]) -> HemanImage {
    assert!(!images.is_empty(), "count must be greater than 0");
    let width = images[0].width;
    let height = images[0].height;
    let nbands = images[0].nbands;
    
    // Verify all images have same dimensions
    for img in images.iter().skip(1) {
        assert!(img.width == width, "all images must have same width");
        assert!(img.height == height, "all images must have same height");
        assert!(img.nbands == nbands, "all images must have same number of bands");
    }

    let mut result = heman_image_create(width * images.len() as i32, height, nbands);
    if let Some(ref mut result) = result {
        let result_mutex = std::sync::Mutex::new(result);
        // Use parallel iterator for height rows
        (0..height).into_par_iter().for_each(|y| {
            for (tile, img) in images.iter().enumerate() {
                let dstx = (tile as i32) * width;
                let mut result_guard = result_mutex.lock().unwrap();
                // Safe because:
                // 1. Each thread operates on a different y coordinate
                // 2. The result image is protected by mutex
                unsafe {
                    copy_row(img, &mut *result_guard, dstx, y);
                }
            }
        });
    }

    result
}
pub fn heman_ops_stairstep<'a>(
    hmap: &'a mut HemanImageS,
    nsteps: i32,
    mask: Option<&HemanImageS>,
    mask_color: u32,
    invert_mask: bool,
    offset: f32,
) -> &'a mut HemanImageS {
    // Assertions (lines 3-4)
    assert!(hmap.nbands == 1);
    if let Some(mask) = mask {
        assert!(mask.nbands == 3);
    }

    let size = (hmap.height * hmap.width) as usize;
    let src = hmap.data.as_mut().expect("hmap.data must be Some");

    // Find min and max values (lines 8-17)
    let (minv, maxv) = {
        let mut minv: f32 = 1000.0;
        let mut maxv: f32 = -1000.0;

        for i in 0..size {
            if mask.is_none() || _match(mask.unwrap(), mask_color, invert_mask, i) {
                let val = src[i];
                minv = minv.min(val);
                maxv = maxv.max(val);
            }
        }

        (minv, maxv)
    };

    let range = maxv - minv;

    // Process each pixel (lines 20-32)
    for i in 0..size {
        let mut e = src[i];
        
        if mask.is_none() || _match(mask.unwrap(), mask_color, invert_mask, i) {
            e -= minv;
            e /= range;
            e = f32::floor(e * nsteps as f32) / nsteps as f32;
            e = (e * range) + minv;
        }
        
        src[i] = e + offset;
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
    
    // Process each row in parallel (equivalent to OpenMP parallel for)
    let result_data = if let Some(ref mut result) = result.data {
        result
    } else {
        return None;
    };

    for y in 0..height {
        let y1 = if (y + 1) > maxy { maxy } else { y + 1 };
        
        let dst_start = (y * width) as usize;
        let dst_end = dst_start + width as usize;
        let dst_row = &mut result_data[dst_start..dst_end];
        
        for x in 0..width {
            let x1 = if (x + 1) > maxx { maxx } else { x + 1 };
            
            let p = heman_image_texel(&heightmap, x, y).and_then(|v| v.first())?;
            let px = heman_image_texel(&heightmap, x1, y).and_then(|v| v.first())?;
            let py = heman_image_texel(&heightmap, x, y1).and_then(|v| v.first())?;
            
            dst_row[x as usize] = ((p - px) * (p - px)) + ((p - py) * (p - py));
        }
    }
    
    Some(result)
}
pub fn heman_ops_extract_mask(
    source: &HemanImageS,
    color: u32,  // Changed from HemanColor to u32 to avoid ambiguity
    invert: bool,
) -> Option<Box<HemanImageS>> {
    // Assert that the source image has 3 bands (RGB)
    assert!(source.nbands == 3, "Source image must have 3 bands (RGB)");

    let inv = 1.0f32 / 255.0f32;
    let r = ((color >> 16) as f32) * inv;
    let g = (((color >> 8) & 0xff) as f32) * inv;
    let b = ((color & 0xff) as f32) * inv;

    let height = source.height;
    let width = source.width;

    // Create result image with 1 band (grayscale)
    let mut result = match heman_image_create(width, height, 1) {
        Some(img) => img,
        None => return None,
    };

    // Get source data safely
    let src_data = source.data.as_ref()?;
    let dst_data = result.data.as_mut()?;

    // Parallel processing over rows (equivalent to OpenMP parallel for)
    dst_data.par_chunks_mut(width as usize).enumerate().for_each(|(y, dst_row)| {
        let src_row_start = (y as i32 * width * 3) as usize;

        for x in 0..width {
            let src_idx = src_row_start + (x * 3) as usize;
            let dst_idx = x as usize;

            let val = (src_data[src_idx] == r)
                && (src_data[src_idx + 1] == g)
                && (src_data[src_idx + 2] == b);

            let final_val = if invert { 
                if val { 1.0 } else { 0.0 }  // Fixed bool to f32 conversion
            } else { 
                1.0 - if val { 1.0 } else { 0.0 }  // Fixed bool to f32 conversion
            };
            dst_row[dst_idx] = final_val;
        }
    });

    Some(result)
}
pub fn heman_ops_replace_color(
    source: &HemanImageS,
    color: u32,  // Changed from HemanColor to u32 to avoid ambiguity
    texture: &HemanImageS,
) -> Option<Box<HemanImageS>> {  // Changed return type to match HemanImage
    // Assertions (converted to Rust's assert!)
    assert!(source.nbands == 3, "Source image must have 3 bands");
    assert!(texture.nbands == 3, "Texture image must have 3 bands");
    let height = source.height;
    let width = source.width;
    assert!(texture.width == width, "Texture width must match source width");
    assert!(texture.height == height, "Texture height must match source height");

    // Color decomposition
    let inv = 1.0f32 / 255.0f32;
    let r = ((color >> 16) as f32) * inv;
    let g = (((color >> 8) & 0xff) as f32) * inv;
    let b = ((color & 0xff) as f32) * inv;

    // Create result image
    let mut result = heman_image_create(width, height, 3).expect("Failed to create result image");
    let result_data = result.as_mut().data.as_mut().expect("Failed to get result data");

    // Get source and texture data
    let source_data = source.data.as_ref().expect("Failed to get source data");
    let texture_data = texture.data.as_ref().expect("Failed to get texture data");

    // Process each pixel
    for y in 0..height {
        for x in 0..width {
            let src_idx = ((y * width + x) * 3) as usize;
            let dst_idx = src_idx;  // Same layout as source
            let tex_idx = src_idx;  // Same layout as source

            if source_data[src_idx] == r
                && source_data[src_idx + 1] == g
                && source_data[src_idx + 2] == b
            {
                // Replace with texture
                result_data[dst_idx] = texture_data[tex_idx];
                result_data[dst_idx + 1] = texture_data[tex_idx + 1];
                result_data[dst_idx + 2] = texture_data[tex_idx + 2];
            } else {
                // Copy from source
                result_data[dst_idx] = source_data[src_idx];
                result_data[dst_idx + 1] = source_data[src_idx + 1];
                result_data[dst_idx + 2] = source_data[src_idx + 2];
            }
        }
    }

    Some(result)  // Wrapped in Some to match return type
}
pub fn heman_ops_percentiles<'a>(
    hmap: &'a mut HemanImage,
    nsteps: i32,
    mask: &'a HemanImage,
    mask_color: u32,
    invert_mask: bool,
    offset: f32,
) -> &'a mut HemanImage {
    // Assertions
    assert!(hmap.as_ref().unwrap().nbands == 1);
    if let Some(m) = mask {
        assert!(m.nbands == 3);
    }

    let hmap_s = hmap.as_mut().unwrap();
    let size = hmap_s.height * hmap_s.width;
    let src = hmap_s.data.as_mut().unwrap();
    let mut src_idx = 0;
    let mut minv: f32 = 1000.0;
    let mut maxv: f32 = -1000.0;
    let mut npixels: usize = 0;

    // First pass: find min/max and count valid pixels
    for i in 0..size as usize {
        if mask.is_none() || _match(mask.as_ref().unwrap(), mask_color, invert_mask, i) {
            let val = src[i + src_idx];
            minv = minv.min(val);
            maxv = maxv.max(val);
            npixels += 1;
        }
    }

    // Second pass: collect values
    let mut vals = Vec::with_capacity(npixels);
    npixels = 0;
    for i in 0..size as usize {
        if mask.is_none() || _match(mask.as_ref().unwrap(), mask_color, invert_mask, i) {
            vals.push(src[i + src_idx]);
            npixels += 1;
        }
    }

    // Calculate percentiles
    let mut percentiles = Vec::with_capacity(nsteps as usize);
    for tier in 0..nsteps {
        let k = (tier as usize * npixels) / nsteps as usize;
        let mut vals_copy = vals.clone();
        let height = qselect(&mut vals_copy, k);
        percentiles.push(height);
    }

    // Apply percentiles with offset
    for i in 0..size as usize {
        let mut e = src[src_idx];
        if mask.is_none() || _match(mask.as_ref().unwrap(), mask_color, invert_mask, i) {
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
pub fn heman_ops_merge_political(
    hmap: &HemanImageS,
    cmap: &HemanImageS,
    ocean: color::HemanColor,
) -> HemanImage {
    // Assertions (lines 3-4)
    assert!(hmap.nbands == 1, "hmap must have 1 band");
    assert!(cmap.nbands == 3, "cmap must have 3 bands");

    // Create result image (line 5)
    let mut result = heman_image_create(hmap.width, hmap.height, 4).expect("Failed to create image");

    // Get data references (lines 6-11)
    let pheight = hmap.data.as_deref().expect("hmap has no data");
    let pcolour = cmap.data.as_deref().expect("cmap has no data");
    let pmerged = result.data.as_deref_mut().expect("result has no data");

    // Calculate ocean color components (lines 12-15)
    let inv = 1.0f32 / 255.0f32;
    let oceanr = ((ocean >> 16) as f32) * inv;
    let oceang = (((ocean >> 8) & 0xff) as f32) * inv;
    let oceanb = ((ocean & 0xff) as f32) * inv;

    // Find min and max height (lines 16-23)
    let size = (hmap.height * hmap.width) as usize;
    let mut minh = 1000.0f32;
    let mut maxh = -1000.0f32;
    
    for i in 0..size {
        let height = pheight[i];
        minh = minh.min(height);
        maxh = maxh.max(height);
    }

    // Process each pixel (lines 25-28)
    let mut pheight_idx = 0;
    let mut pcolour_idx = 0;
    let mut pmerged_idx = 0;
    
    for _ in 0..size {
        helper_heman_ops_merge_political_1(
            &mut pheight_idx,
            &mut pcolour_idx,
            &mut pmerged_idx,
            pheight,
            pcolour,
            pmerged,
            oceanr,
            oceang,
            oceanb,
            minh,
            maxh,
        );
    }

    Some(result)
}
pub fn helper_heman_ops_sobel_1(
    img: &HemanImageS,
    width: i32,
    height: i32,
    result: &mut HemanImageS,
    gray: &HemanImageS,
    edge_rgb: &KmVec3,
    y: i32,
) {
    // Get mutable references to the data slices
    let dst_slice = if let Some(ref mut data) = result.data {
        data.chunks_exact_mut(3).skip((y * width) as usize)
    } else {
        return;
    };

    let src_slice = if let Some(ref data) = img.data {
        data.chunks_exact(3).skip((y * width) as usize)
    } else {
        return;
    };

    // Iterate over each pixel in the row
    for (x, (dst, src)) in dst_slice.zip(src_slice).enumerate().take(width as usize) {
        let x = x as i32;
        // Calculate neighbor indices with boundary checks
        let xm1 = if x - 1 > 0 { x - 1 } else { 0 };
        let xp1 = if x + 1 > width - 1 { width - 1 } else { x + 1 };
        let ym1 = if y - 1 > 0 { y - 1 } else { 0 };
        let yp1 = if y + 1 > height - 1 { height - 1 } else { y + 1 };

        // Get texture values with safety checks
        let t00 = heman_image_texel(gray, xm1, ym1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t10 = heman_image_texel(gray, x, ym1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t20 = heman_image_texel(gray, xp1, ym1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t01 = heman_image_texel(gray, xm1, 0).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t21 = heman_image_texel(gray, xp1, 0).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t02 = heman_image_texel(gray, xm1, yp1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t12 = heman_image_texel(gray, x, yp1).and_then(|v| v.first()).copied().unwrap_or(0.0);
        let t22 = heman_image_texel(gray, xp1, yp1).and_then(|v| v.first()).copied().unwrap_or(0.0);

        // Calculate gradients
        let gx = ((t00 + (2.0 * t01) + t02) - t20 - (2.0 * t21) - t22);
        let gy = ((t00 + (2.0 * t10) + t20) - t02 - (2.0 * t12) - t22);
        let is_edge = if ((gx * gx) + (gy * gy)) > 1e-5 { 1.0 } else { 0.0 };

        // Convert slices to KmVec3
        let src_vec = KmVec3 {
            x: src[0],
            y: src[1],
            z: src[2],
        };
        let mut dst_vec = KmVec3 {
            x: dst[0],
            y: dst[1],
            z: dst[2],
        };

        // Perform the lerp operation
        kmVec3Lerp(&mut dst_vec, &src_vec, edge_rgb, is_edge);

        // Write back the result
        dst[0] = dst_vec.x;
        dst[1] = dst_vec.y;
        dst[2] = dst_vec.z;
    }
}

pub fn helper_heman_ops_emboss_1(
    img: &HemanImageS,
    mode: i32,
    octaves: i32,
    ctx: &OsnContext,
    width: i32,
    result: &mut HemanImageS,
    inv: f32,
    gain: f32,
    lacunarity: f32,
    land_amplitude: f32,
    land_frequency: f32,
    ocean_amplitude: f32,
    ocean_frequency: f32,
    y: i32,
) {
    let dst_start = (y * width) as usize;
    let dst_slice = match &mut result.data {
        Some(data) => &mut data[dst_start..dst_start + width as usize],
        None => return,
    };

    for x in 0..width {
        let z = match heman_image_texel(img, x, y) {
            Some(texel) => texel[0],
            None => continue,
        };

        let mut z = z;
        if z > 0.0 && mode == 1 {
            let s = x as f32 * inv;
            let t = y as f32 * inv;
            let mut a = land_amplitude;
            let mut f = land_frequency;
            for _ in 0..octaves {
                z += a * open_simplex_noise2(ctx, s as f64 * f as f64, t as f64 * f as f64) as f32;
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
                z += soften * (a * open_simplex_noise2(ctx, s as f64 * f as f64, t as f64 * f as f64) as f32);
                a *= gain;
                f *= lacunarity;
            }
        }

        dst_slice[x as usize] = z;
    }
}

pub fn heman_ops_warp_points(
    img: &HemanImageS,
    seed: i32,
    octaves: i32,
    pts: &mut HemanPoints,
) -> HemanImage {
    let width = img.width;
    let height = img.height;
    let mut mapping = heman_distance_identity_cpcf(width, height);

    // Need to take mutable reference of mapping's inner data for heman_ops_warp_core
    let retval = {
        let mapping_ref = mapping.as_mut().map(|b| &mut **b);
        heman_ops_warp_core(img, mapping_ref, seed, octaves)
    };

    if let Some(pts_box) = pts.as_mut() {
        if let Some(src) = pts_box.data.as_mut() {
            let mut src_idx = 0;
            for _ in 0..pts_box.width {
                let x = src[0 + src_idx];
                let y = src[1 + src_idx];
                
                if let Some(mapping_box) = mapping.as_ref() {
                    let i = (x * mapping_box.width as f32) as i32;
                    let j = (y * mapping_box.height as f32) as i32;

                    if i >= 0 && i < mapping_box.width && j >= 0 && j < mapping_box.height {
                        if let Some(texel) = heman_image_texel(mapping_box, i, j) {
                            src[0 + src_idx] = texel[0] / mapping_box.width as f32;
                            src[1 + src_idx] = texel[1] / mapping_box.height as f32;
                        }
                    }
                }
                src_idx += pts_box.nbands as usize;
            }
        }
    }

    heman_image_destroy(mapping);
    retval
}
pub fn heman_ops_emboss(img: &HemanImageS, mode: i32) -> HemanImage {
    let seed = 1;
    let octaves = 4;
    let mut ctx: Option<Box<OsnContext>> = None;
    open_simplex_noise(seed as i64, &mut ctx).unwrap();
    let width = img.width;
    let height = img.height;
    assert!(img.nbands == 1);
    let mut result = heman_image_create(width, height, 1);
    let invw = 1.0 / width as f32;
    let invh = 1.0 / height as f32;
    let inv = if invw > invh { invh } else { invw };
    let gain = 0.6;
    let lacunarity = 2.0;
    let land_amplitude = 0.0005;
    let land_frequency = 256.0;
    let ocean_amplitude = 0.5;
    let ocean_frequency = 1.0;

    if let Some(ref mut result) = result {
        for y in 0..height {
            helper_heman_ops_emboss_1(
                img,
                mode,
                octaves,
                ctx.as_ref().unwrap(),
                width,
                result,
                inv,
                gain,
                lacunarity,
                land_amplitude,
                land_frequency,
                ocean_amplitude,
                ocean_frequency,
                y,
            );
        }
    }

    open_simplex_noise_free(ctx);
    result
}
pub fn heman_ops_sobel(img: &HemanImageS, rgb: u32) -> Option<Box<HemanImageS>> {
    let width = img.width;
    let height = img.height;
    assert!(img.nbands == 3);
    
    let result_box = heman_image_create(width, height, 3);
    let gray = heman_color_to_grayscale(Some(Box::new(img.clone())));
    
    let inv = 1.0f32 / 255.0f32;
    let edge_rgb = KmVec3 {
        x: ((rgb >> 16) as f32) * inv,
        y: (((rgb >> 8) & 0xff) as f32) * inv,
        z: ((rgb & 0xff) as f32) * inv,
    };

    let result_arc = match result_box {
        Some(boxed) => {
            let image = *boxed;
            Some(Arc::new(Mutex::new(image)))
        }
        None => None,
    };

    if let Some(result_arc) = &result_arc {
        let gray_ref = gray.as_ref().unwrap();
        (0..height).into_par_iter().for_each(|y| {
            let result_arc_clone = Arc::clone(result_arc);
            let mut result_guard = result_arc_clone.lock().unwrap();
            helper_heman_ops_sobel_1(
                img,
                width,
                height,
                &mut *result_guard,
                gray_ref,
                &edge_rgb,
                y,
            );
        });
    }

    heman_image_destroy(gray);

    match result_arc {
        Some(arc) => {
            let mutex = Arc::try_unwrap(arc).ok().unwrap();
            let image = mutex.into_inner().unwrap();
            Some(Box::new(image))
        }
        None => None,
    }
}
