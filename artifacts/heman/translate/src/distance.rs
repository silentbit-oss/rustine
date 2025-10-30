use crate::*;
use std::assert;
use std::f32;
use std::f32::consts::PI;
use std::f32::consts::SQRT_2;
use std::sync::Arc;
use rayon::prelude::*;
use std::convert::TryInto;
pub fn edt(f: &[f32], d: &mut [f32], z: &mut [f32], w: &mut [u16], n: usize) {
    let mut k = 0;
    let mut s;
    
    // Initialize first elements
    w[0] = 0;
    z[0] = -INF;
    z[1] = INF;
    
    // First loop
    for q in 1..n {
        s = ((f[q] + (q * q) as f32) - (f[w[k] as usize] + (w[k] * w[k]) as f32)) 
            / ((2 * q) as f32 - (2 * w[k]) as f32);
        
        while s <= z[k] {
            k -= 1;
            s = ((f[q] + (q * q) as f32) - (f[w[k] as usize] + (w[k] * w[k]) as f32)) 
                / ((2 * q) as f32 - (2 * w[k]) as f32);
        }
        
        k += 1;
        w[k] = q as u16;
        z[k] = s;
        z[k + 1] = INF;
    }
    
    // Second loop
    k = 0;
    for q in 0..n {
        while z[k + 1] < q as f32 {
            k += 1;
        }
        
        d[q] = ((q - w[k] as usize) * (q - w[k] as usize)) as f32 + f[w[k] as usize];
    }
}

pub fn edt_with_payload(
    f: &[f32],
    d: &mut [f32],
    z: &mut [f32],
    w: &mut [u16],
    n: usize,
    payload_in: &[f32],
    payload_out: &mut [f32],
) {
    let mut k = 0;
    let mut s;
    w[0] = 0;
    z[0] = -INF;
    z[1] = INF;

    for q in 1..n {
        s = ((f[q] + (q as f32 * q as f32)) - (f[w[k] as usize] + (w[k] as f32 * w[k] as f32)))
            / ((2.0 * q as f32) - (2.0 * w[k] as f32));
        
        while s <= z[k] {
            k -= 1;
            s = ((f[q] + (q as f32 * q as f32)) - (f[w[k] as usize] + (w[k] as f32 * w[k] as f32)))
                / ((2.0 * q as f32) - (2.0 * w[k] as f32));
        }

        k += 1;
        w[k] = q as u16;
        z[k] = s;
        z[k + 1] = INF;
    }

    k = 0;
    for q in 0..n {
        while z[k + 1] < q as f32 {
            k += 1;
        }

        d[q] = ((q as f32 - w[k] as f32) * (q as f32 - w[k] as f32)) + f[w[k] as usize];
        payload_out[q * 2] = payload_in[w[k] as usize * 2];
        payload_out[(q * 2) + 1] = payload_in[(w[k] as usize * 2) + 1];
    }
}
pub fn heman_distance_from_cpcf(cf: HemanImage) -> HemanImage {
    let cf_inner = cf.as_ref().unwrap();
    assert!(cf_inner.nbands == 2, "Coordinate field input must have 2 bands.");
    
    let mut udf = heman_image_create(cf_inner.width, cf_inner.height, 1);
    let udf_inner = udf.as_ref().unwrap();
    
    let scale = 1.0f32 / ((cf_inner.width * cf_inner.width + cf_inner.height * cf_inner.height) as f32).sqrt();
    
    let mut dptr_idx = 0;
    let mut sptr_idx = 0;
    
    let cf_data = cf_inner.data.as_ref().unwrap();
    let udf_data_mut = udf.as_mut().unwrap().data.as_mut().unwrap();
    
    for y in 0..cf_inner.height {
        for x in 0..cf_inner.width {
            let u = cf_data[sptr_idx];
            sptr_idx += 1;
            let v = cf_data[sptr_idx];
            sptr_idx += 1;
            
            let dx = u - x as f32;
            let dy = v - y as f32;
            let dist = (dx * dx + dy * dy).sqrt() * scale;
            
            udf_data_mut[dptr_idx] = dist;
            dptr_idx += 1;
        }
    }
    
    udf
}
pub fn heman_distance_identity_cpcf(width: i32, height: i32) -> HemanImage {
    let mut retval = heman_image_create(width, height, 2);
    
    if let Some(ref mut image) = retval {
        if let Some(ref mut cdata) = image.data {
            let mut cdata_idx = 0;
            for y in 0..height {
                for x in 0..width {
                    cdata[cdata_idx] = x as f32;
                    cdata_idx += 1;
                    cdata[cdata_idx] = y as f32;
                    cdata_idx += 1;
                }
            }
        }
    }
    
    retval
}
pub fn transform_to_distance(sdf: &mut HemanImageS) {
    let width = sdf.width as usize;
    let height = sdf.height as usize;
    let size = width * height;

    // Initialize buffers with zeros (equivalent to calloc)
    let ff = vec![0.0f32; size];
    let dd = vec![0.0f32; size];
    let zz = vec![0.0f32; (height + 1) * (width + 1)];
    let ww = vec![0u16; size];

    // Wrap buffers in Arc<Mutex<...>> for shared mutable access
    let ff = std::sync::Arc::new(std::sync::Mutex::new(ff));
    let dd = std::sync::Arc::new(std::sync::Mutex::new(dd));
    let zz = std::sync::Arc::new(std::sync::Mutex::new(zz));
    let ww = std::sync::Arc::new(std::sync::Mutex::new(ww));
    let sdf_arc = std::sync::Arc::new(std::sync::Mutex::new(sdf));

    // Process columns in parallel
    (0..width).into_par_iter().for_each(|x| {
        let ff = ff.clone();
        let dd = dd.clone();
        let zz = zz.clone();
        let ww = ww.clone();
        let sdf = sdf_arc.clone();

        let mut ff = ff.lock().unwrap();
        let mut dd = dd.lock().unwrap();
        let mut zz = zz.lock().unwrap();
        let mut ww = ww.lock().unwrap();
        let mut sdf = sdf.lock().unwrap();

        let f = &mut ff[x * height..(x + 1) * height];
        let d = &mut dd[x * height..(x + 1) * height];
        let z = &mut zz[x * (height + 1)..(x + 1) * (height + 1)];
        let w = &mut ww[x * height..(x + 1) * height];

        if let Some(ref data) = sdf.data {
            for y in 0..height {
                f[y] = data[y * width + x];
            }
        }

        edt(f, d, z, w, height);

        if let Some(ref mut data) = sdf.data {
            for y in 0..height {
                data[y * width + x] = d[y];
            }
        }
    });

    // Process rows in parallel
    (0..height).into_par_iter().for_each(|y| {
        let ff = ff.clone();
        let dd = dd.clone();
        let zz = zz.clone();
        let ww = ww.clone();
        let sdf = sdf_arc.clone();

        let mut ff = ff.lock().unwrap();
        let mut dd = dd.lock().unwrap();
        let mut zz = zz.lock().unwrap();
        let mut ww = ww.lock().unwrap();
        let mut sdf = sdf.lock().unwrap();

        let f = &mut ff[y * width..(y + 1) * width];
        let d = &mut dd[y * width..(y + 1) * width];
        let z = &mut zz[y * (width + 1)..(y + 1) * (width + 1)];
        let w = &mut ww[y * width..(y + 1) * width];

        if let Some(ref data) = sdf.data {
            for x in 0..width {
                f[x] = data[y * width + x];
            }
        }

        edt(f, d, z, w, width);

        if let Some(ref mut data) = sdf.data {
            for x in 0..width {
                data[y * width + x] = d[x];
            }
        }
    });
}
pub fn helper_transform_to_coordfield_1(
    width_ref: &mut i32,
    x_ref: &mut i32,
    sdf: &mut HemanImageS,
    cf: &mut HemanImageS,
    height: i32,
    ff: &mut [f32],
    dd: &mut [f32],
    zz: &mut [f32],
    ww: &mut [u16],
) {
    let width = *width_ref;
    let x = *x_ref;
    
    // Allocate and initialize pl1 and pl2 with zeros
    let mut pl1 = vec![0.0; (height * 2).try_into().unwrap()];
    let mut pl2 = vec![0.0; (height * 2).try_into().unwrap()];
    
    // Calculate offsets
    let height_usize = height.try_into().unwrap();
    let x_usize: usize = x.try_into().unwrap();
    let f = &mut ff[(height_usize * x_usize)..];
    let d = &mut dd[(height_usize * x_usize)..];
    let z = &mut zz[((height_usize + 1) * x_usize)..];
    let w = &mut ww[(height_usize * x_usize)..];
    
    // Access image data safely
    if let Some(sdf_data) = &sdf.data {
        if let Some(cf_data) = &cf.data {
            for y in 0..height {
                let y_usize: usize = y.try_into().unwrap();
                let idx: usize = (y * width + x).try_into().unwrap();
                
                // Read from sdf and cf
                f[y_usize] = sdf_data[idx];
                pl1[y_usize * 2] = cf_data[idx * 2];
                pl1[y_usize * 2 + 1] = cf_data[idx * 2 + 1];
            }
        }
    }
    
    // Call EDT function
    edt_with_payload(
        f,
        d,
        z,
        w,
        height_usize,
        &pl1,
        &mut pl2,
    );
    
    // Write back results
    if let Some(sdf_data) = &mut sdf.data {
        if let Some(cf_data) = &mut cf.data {
            for y in 0..height {
                let y_usize: usize = y.try_into().unwrap();
                let idx: usize = (y * width + x).try_into().unwrap();
                
                // Write to sdf and cf
                sdf_data[idx] = d[y_usize];
                cf_data[idx * 2] = pl2[y_usize * 2];
                cf_data[idx * 2 + 1] = pl2[y_usize * 2 + 1];
            }
        }
    }
    
    // Update references (though they weren't modified)
    *width_ref = width;
    *x_ref = x;
}
pub fn helper_transform_to_coordfield_2(
    width_ref: &mut i32,
    y_ref: &mut i32,
    sdf: &mut HemanImage,
    cf: &mut HemanImage,
    ff: &mut [f32],
    dd: &mut [f32],
    zz: &mut [f32],
    ww: &mut [u16],
) {
    let width = *width_ref;
    let y = *y_ref;
    let width_usize = width.try_into().unwrap();
    
    // Initialize pl1 and pl2 with zeros (equivalent to calloc)
    let mut pl1 = vec![0.0f32; width_usize * 2];
    let mut pl2 = vec![0.0f32; width_usize * 2];
    
    // Calculate slice offsets
    let f_start = (width * y) as usize;
    let f_end = f_start + width_usize;
    let f = &mut ff[f_start..f_end];
    
    let d_start = (width * y) as usize;
    let d_end = d_start + width_usize;
    let d = &mut dd[d_start..d_end];
    
    let z_start = ((width + 1) * y) as usize;
    let z_end = z_start + (width_usize + 1);
    let z = &mut zz[z_start..z_end];
    
    let w_start = (width * y) as usize;
    let w_end = w_start + width_usize;
    let w = &mut ww[w_start..w_end];
    
    // Process first loop
    if let Some(sdf_data) = &sdf.as_ref().unwrap().data {
        if let Some(cf_data) = &cf.as_ref().unwrap().data {
            for x in 0..width_usize {
                f[x] = sdf_data[(y as usize * width_usize) + x];
                pl1[x * 2] = cf_data[2 * ((y as usize * width_usize) + x) + 0];
                pl1[(x * 2) + 1] = cf_data[2 * ((y as usize * width_usize) + x) + 1];
            }
        }
    }
    
    // Call edt_with_payload
    edt_with_payload(f, d, z, w, width_usize, &pl1, &mut pl2);
    
    // Process second loop
    if let Some(sdf_data) = &mut sdf.as_mut().unwrap().data {
        if let Some(cf_data) = &mut cf.as_mut().unwrap().data {
            for x in 0..width_usize {
                sdf_data[(y as usize * width_usize) + x] = d[x];
                cf_data[2 * ((y as usize * width_usize) + x) + 0] = pl2[2 * x];
                cf_data[2 * ((y as usize * width_usize) + x) + 1] = pl2[(2 * x) + 1];
            }
        }
    }
    
    // Update references
    *width_ref = width;
    *y_ref = y;
}
pub fn transform_to_coordfield(sdf: &mut HemanImage, cf: &mut HemanImage) {
    // Extract width and height from sdf (assuming it's Some)
    let sdf_inner = sdf.as_ref().unwrap();
    let width = sdf_inner.width;
    let height = sdf_inner.height;
    let size = (width * height) as usize;

    // Allocate buffers initialized to zero (equivalent to calloc)
    let mut ff = vec![0.0f32; size];
    let mut dd = vec![0.0f32; size];
    let mut zz = vec![0.0f32; ((height + 1) * (width + 1)) as usize];
    let mut ww = vec![0u16; size];

    // First loop (x-axis)
    for x in 0..width {
        let mut w = width as i32;
        let mut x_val = x as i32;
        let sdf_inner = sdf.as_mut().unwrap();
        let cf_inner = cf.as_mut().unwrap();
        helper_transform_to_coordfield_1(
            &mut w,
            &mut x_val,
            sdf_inner,
            cf_inner,
            height as i32,
            &mut ff,
            &mut dd,
            &mut zz,
            &mut ww,
        );
    }

    // Second loop (y-axis)
    for y in 0..height {
        let mut w = width as i32;
        let mut y_val = y as i32;
        helper_transform_to_coordfield_2(
            &mut w,
            &mut y_val,
            sdf,
            cf,
            &mut ff,
            &mut dd,
            &mut zz,
            &mut ww,
        );
    }

    // Buffers are automatically dropped when they go out of scope
}
pub fn heman_distance_create_df(src: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(src.nbands == 1, "Distance field input must have only 1 band.");
    
    let mut positive = heman_image_create(src.width, src.height, 1)?;
    let positive = positive.as_mut();
    let size = (src.height * src.width) as usize;
    
    {
        let pptr = positive.data.as_mut()?;
        let sptr = src.data.as_ref()?;
        
        for i in 0..size {
            pptr[i] = if sptr[i] != 0.0 { 0.0 } else { INF };
        }
    }
    
    transform_to_distance(positive);
    
    let inv = 1.0f32 / src.width as f32;
    {
        let pptr = positive.data.as_mut()?;
        
        for i in 0..size {
            pptr[i] = f32::sqrt(pptr[i]) * inv;
        }
    }
    
    Some(Box::new(positive.clone()))
}
pub fn heman_distance_create_sdf(src: &HemanImageS) -> Option<Box<HemanImageS>> {
    // Assert that the input image has only 1 band
    assert!(src.nbands == 1, "Distance field input must have only 1 band.");

    // Create positive and negative distance fields
    let mut positive = heman_image_create(src.width, src.height, 1)?;
    let mut negative = heman_image_create(src.width, src.height, 1)?;

    // Get mutable references to the image data
    let positive = positive.as_mut();
    let negative = negative.as_mut();
    let size = (src.height * src.width) as usize;

    // Initialize positive and negative distance fields
    {
        let pdata = positive.data.as_mut().unwrap();
        let ndata = negative.data.as_mut().unwrap();
        let sdata = src.data.as_ref().unwrap();

        for i in 0..size {
            pdata[i] = if sdata[i] != 0.0 { INF } else { 0.0 };
            ndata[i] = if sdata[i] != 0.0 { 0.0 } else { INF };
        }
    }

    // Transform both fields to distance fields
    transform_to_distance(positive);
    transform_to_distance(negative);

    // Combine the distance fields
    let inv = 1.0f32 / src.width as f32;
    {
        let pdata = positive.data.as_mut().unwrap();
        let ndata = negative.data.as_ref().unwrap();

        for i in 0..size {
            pdata[i] = (f32::sqrt(pdata[i]) - f32::sqrt(ndata[i])) * inv;
        }
    }

    // Clean up and return
    heman_image_destroy(Some(Box::new(negative.clone())));
    Some(Box::new(positive.clone()))
}

pub fn heman_distance_create_cpcf(src: HemanImage) -> HemanImage {
    // Unwrap the source image or return None if it's None
    let src_inner = match src {
        Some(ref s) => s,
        None => return None,
    };

    // Create negative image with same dimensions but 1 band
    let mut negative = heman_image_create(src_inner.width, src_inner.height, 1);
    let negative_inner = match negative.as_mut() {
        Some(n) => n,
        None => return None,
    };

    let size = src_inner.height * src_inner.width;
    let nptr = negative_inner.data.as_mut().unwrap(); // Safe because we just created it
    let sptr = src_inner.data.as_ref().unwrap(); // Safe because we checked src is Some

    // Process each pixel
    for i in 0..size {
        let mut val = 0.0;
        let mut sptr_idx = (i * src_inner.nbands) as usize;
        
        // Sum all bands
        for _ in 0..src_inner.nbands {
            val += sptr[sptr_idx];
            sptr_idx += 1;
        }

        // Store in negative image
        let nptr_idx = i as usize;
        nptr[nptr_idx] = if val != 0.0 { 0.0 } else { INF };
    }

    // Create coordinate field and transform
    let mut coordfield = heman_distance_identity_cpcf(src_inner.width, src_inner.height);
    transform_to_coordfield(&mut negative, &mut coordfield);
    
    // Explicitly drop negative to make borrow checker happy
    heman_image_destroy(negative);
    
    coordfield
}
