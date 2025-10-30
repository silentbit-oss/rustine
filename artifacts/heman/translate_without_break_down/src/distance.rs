use crate::*;
use std::f32;
use std::f32::INFINITY as INF;
use std::f32::consts::SQRT_2;
use libm::sqrtf;
use std::sync::Arc;
use std::sync::Mutex;
use rayon::prelude::*;
pub fn edt(f: &[f32], d: &mut [f32], z: &mut [f32], w: &mut [u16], n: usize) {
    let mut k = 0;
    let mut s;
    
    w[0] = 0;
    z[0] = -INF;
    z[1] = INF;
    
    for q in 1..n {
        s = ((f[q] + (q * q) as f32) - (f[w[k] as usize] + (w[k] * w[k]) as f32)) 
            / ((2 * q) - (2 * w[k] as usize)) as f32;
        
        while s <= z[k] {
            k -= 1;
            s = ((f[q] + (q * q) as f32) - (f[w[k] as usize] + (w[k] * w[k]) as f32)) 
                / ((2 * q) - (2 * w[k] as usize)) as f32;
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
    let cf = match cf {
        Some(cf) => cf,
        None => return None,
    };

    // Check that the coordinate field has exactly 2 bands
    assert!(cf.nbands == 2, "Coordinate field input must have 2 bands.");

    // Create output image with 1 band
    let mut udf = heman_image_create(cf.width, cf.height, 1);
    let udf = match udf.as_mut() {
        Some(udf) => udf,
        None => return None,
    };

    // Get mutable references to the data vectors
    let dptr = match &mut udf.data {
        Some(data) => data,
        None => return None,
    };
    let sptr = match &cf.data {
        Some(data) => data,
        None => return None,
    };

    let scale = 1.0f32 / ((cf.width * cf.width + cf.height * cf.height) as f32).sqrt();
    let mut dptr_idx = 0;
    let mut sptr_idx = 0;

    for y in 0..cf.height {
        for x in 0..cf.width {
            let u = sptr[sptr_idx];
            sptr_idx += 1;
            let v = sptr[sptr_idx];
            sptr_idx += 1;

            let dx = u - x as f32;
            let dy = v - y as f32;
            let dist = (dx * dx + dy * dy).sqrt() * scale;

            dptr[dptr_idx] = dist;
            dptr_idx += 1;
        }
    }

    Some(udf.clone())
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
    let ff = std::sync::Arc::new(std::sync::Mutex::new(vec![0.0f32; size]));
    let dd = std::sync::Arc::new(std::sync::Mutex::new(vec![0.0f32; size]));
    let zz = std::sync::Arc::new(std::sync::Mutex::new(vec![0.0f32; (height + 1) * (width + 1)]));
    let ww = std::sync::Arc::new(std::sync::Mutex::new(vec![0u16; size]));

    // First parallel loop over x
    {
        let data = std::sync::Arc::new(std::sync::Mutex::new(sdf.data.as_mut().unwrap()));
        (0..width).into_par_iter().for_each(|x| {
            let ff = ff.clone();
            let dd = dd.clone();
            let zz = zz.clone();
            let ww = ww.clone();
            let data = data.clone();
            let mut ff = ff.lock().unwrap();
            let mut dd = dd.lock().unwrap();
            let mut zz = zz.lock().unwrap();
            let mut ww = ww.lock().unwrap();
            let mut data = data.lock().unwrap();

            let f = &mut ff[(height * x)..(height * (x + 1))];
            let d = &mut dd[(height * x)..(height * (x + 1))];
            let z = &mut zz[((height + 1) * x)..((height + 1) * (x + 1))];
            let w = &mut ww[(height * x)..(height * (x + 1))];

            for y in 0..height {
                f[y] = data[y * width + x];
            }

            edt(f, d, z, w, height);

            for y in 0..height {
                data[y * width + x] = d[y];
            }
        });
    }

    // Second parallel loop over y
    {
        let data = std::sync::Arc::new(std::sync::Mutex::new(sdf.data.as_mut().unwrap()));
        (0..height).into_par_iter().for_each(|y| {
            let ff = ff.clone();
            let dd = dd.clone();
            let zz = zz.clone();
            let ww = ww.clone();
            let data = data.clone();
            let mut ff = ff.lock().unwrap();
            let mut dd = dd.lock().unwrap();
            let mut zz = zz.lock().unwrap();
            let mut ww = ww.lock().unwrap();
            let mut data = data.lock().unwrap();

            let f = &mut ff[(width * y)..(width * (y + 1))];
            let d = &mut dd[(width * y)..(width * (y + 1))];
            let z = &mut zz[((width + 1) * y)..((width + 1) * (y + 1))];
            let w = &mut ww[(width * y)..(width * (y + 1))];

            for x in 0..width {
                f[x] = data[y * width + x];
            }

            edt(f, d, z, w, width);

            for x in 0..width {
                data[y * width + x] = d[x];
            }
        });
    }

    // Buffers are automatically dropped when they go out of scope
}
pub fn transform_to_coordfield(sdf: &mut HemanImageS, cf: &mut HemanImageS) {
    let width = sdf.width as usize;
    let height = sdf.height as usize;
    let size = width * height;

    // Process columns in parallel
    {
        // Create read-only snapshots of input data
        let sdf_data_read = sdf.data.as_ref().unwrap().clone();
        let cf_data_read = cf.data.as_ref().unwrap().clone();
        
        // Create temporary buffers for output
        let mut sdf_temp = vec![0.0f32; size];
        let mut cf_temp = vec![0.0f32; size * 2];
        
        let columns: Vec<_> = (0..width).into_par_iter().map(|x| {
            // Per-thread buffers
            let mut ff_col = vec![0.0f32; height];
            let mut dd_col = vec![0.0f32; height];
            let mut zz_col = vec![0.0f32; height + 1];
            let mut ww_col = vec![0u16; height];
            let mut pl1 = vec![0.0f32; height * 2];
            let mut pl2 = vec![0.0f32; height * 2];
            
            // Read column data from snapshots
            for y in 0..height {
                ff_col[y] = sdf_data_read[y * width + x];
                pl1[y * 2] = cf_data_read[2 * (y * width + x)];
                pl1[y * 2 + 1] = cf_data_read[2 * (y * width + x) + 1];
            }
            
            // Process column
            edt_with_payload(&ff_col, &mut dd_col, &mut zz_col, &mut ww_col, height, &pl1, &mut pl2);
            
            // Return results for this column
            (x, dd_col, pl2)
        }).collect();
        
        // Write results to temporary buffers
        for (x, dd_col, pl2) in columns {
            for y in 0..height {
                sdf_temp[y * width + x] = dd_col[y];
                cf_temp[2 * (y * width + x)] = pl2[2 * y];
                cf_temp[2 * (y * width + x) + 1] = pl2[2 * y + 1];
            }
        }
        
        // Copy results from temporary buffers to images
        sdf.data.as_mut().unwrap().copy_from_slice(&sdf_temp);
        cf.data.as_mut().unwrap().copy_from_slice(&cf_temp);
    }

    // Process rows in parallel
    {
        // Create read-only snapshots of updated data
        let sdf_data_read = sdf.data.as_ref().unwrap().clone();
        let cf_data_read = cf.data.as_ref().unwrap().clone();
        
        // Create temporary buffers for output
        let mut sdf_temp = vec![0.0f32; size];
        let mut cf_temp = vec![0.0f32; size * 2];
        
        // Process rows using contiguous mutable slices
        sdf_temp.par_chunks_exact_mut(width)
            .zip(cf_temp.par_chunks_exact_mut(2 * width))
            .enumerate()
            .for_each(|(y, (sdf_row, cf_row))| {
                // Per-thread buffers
                let mut ff_row = vec![0.0f32; width];
                let mut dd_row = vec![0.0f32; width];
                let mut zz_row = vec![0.0f32; width + 1];
                let mut ww_row = vec![0u16; width];
                let mut pl1 = vec![0.0f32; width * 2];
                let mut pl2 = vec![0.0f32; width * 2];
                
                // Read row data from snapshots
                for x in 0..width {
                    ff_row[x] = sdf_data_read[y * width + x];
                    pl1[x * 2] = cf_data_read[2 * (y * width + x)];
                    pl1[x * 2 + 1] = cf_data_read[2 * (y * width + x) + 1];
                }
                
                // Process row
                edt_with_payload(&ff_row, &mut dd_row, &mut zz_row, &mut ww_row, width, &pl1, &mut pl2);
                
                // Write results to row slices
                for x in 0..width {
                    sdf_row[x] = dd_row[x];
                    cf_row[2 * x] = pl2[2 * x];
                    cf_row[2 * x + 1] = pl2[2 * x + 1];
                }
            });
        
        // Copy results from temporary buffers to images
        sdf.data.as_mut().unwrap().copy_from_slice(&sdf_temp);
        cf.data.as_mut().unwrap().copy_from_slice(&cf_temp);
    }
}

pub fn heman_distance_create_df(src: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(src.nbands == 1, "Distance field input must have only 1 band.");
    
    let mut positive = heman_image_create(src.width, src.height, 1)?;
    let size = (src.height * src.width) as usize;
    
    {
        let pptr = positive.data.as_mut().unwrap();
        let sptr = src.data.as_ref().unwrap();
        
        for i in 0..size {
            pptr[i] = if sptr[i] != 0.0 { 0.0 } else { INF };
        }
    }
    
    transform_to_distance(&mut positive);
    
    let inv = 1.0f32 / src.width as f32;
    {
        let pptr = positive.data.as_mut().unwrap();
        for i in 0..size {
            pptr[i] = f32::sqrt(pptr[i]) * inv;
        }
    }
    
    Some(positive)
}
pub fn heman_distance_create_sdf(src: &HemanImageS) -> Option<Box<HemanImageS>> {
    // Check that the input image has exactly 1 band (assert equivalent)
    assert!(src.nbands == 1, "Distance field input must have only 1 band.");

    // Create positive and negative distance fields
    let mut positive = heman_image_create(src.width, src.height, 1)?;
    let mut negative = heman_image_create(src.width, src.height, 1)?;

    // Get mutable references to the inner images
    let positive = positive.as_mut();
    let negative = negative.as_mut();

    let size = (src.height * src.width) as usize;
    
    // Initialize positive and negative distance fields
    {
        let src_data = src.data.as_ref()?;
        let pos_data = &mut positive.data.as_mut()?;
        let neg_data = &mut negative.data.as_mut()?;

        for i in 0..size {
            let val = src_data[i];
            pos_data[i] = if val != 0.0 { INF } else { 0.0 };
            neg_data[i] = if val != 0.0 { 0.0 } else { INF };
        }
    }

    // Transform both fields to distance fields
    transform_to_distance(positive);
    transform_to_distance(negative);

    // Combine the distance fields
    let inv = 1.0 / src.width as f32;
    {
        let pos_data = &mut positive.data.as_mut()?;
        let neg_data = negative.data.as_ref()?;

        for i in 0..size {
            let pos_val = pos_data[i];
            let neg_val = neg_data[i];
            pos_data[i] = (f32::sqrt(pos_val) - f32::sqrt(neg_val)) * inv;
        }
    }

    // Destroy the negative image (Rust's drop will handle this automatically)
    heman_image_destroy(Some(Box::new(negative.clone())));

    Some(Box::new(positive.clone()))
}

pub fn heman_distance_create_cpcf(src: Option<&HemanImageS>) -> HemanImage {
    // Check if src is None (equivalent to NULL check in C)
    let src = match src {
        Some(s) => s,
        None => return None,
    };

    // Create negative image (handles Option automatically through heman_image_create)
    let mut negative = match heman_image_create(src.width, src.height, 1) {
        Some(n) => *n, // Unwrap the Box
        None => return None,
    };

    let size = src.height * src.width;
    let mut nptr_idx = 0;
    let mut sptr_idx = 0;

    // Get mutable references to the data vectors
    if let Some(nptr) = &mut negative.data {
        if let Some(sptr) = &src.data {
            for _ in 0..size {
                let mut val = 0.0;
                for _ in 0..src.nbands {
                    val += sptr[sptr_idx];
                    sptr_idx += 1;
                }

                nptr[nptr_idx] = if val != 0.0 { 0.0 } else { INF };
                nptr_idx += 1;
            }
        }
    }

    // Create coordfield (handles Option automatically through heman_distance_identity_cpcf)
    let mut coordfield = match heman_distance_identity_cpcf(src.width, src.height) {
        Some(c) => *c, // Unwrap the Box
        None => return None,
    };

    // Perform transformation
    transform_to_coordfield(&mut negative, &mut coordfield);

    // Destroy negative image (Rust's drop will handle this automatically)
    heman_image_destroy(Some(Box::new(negative)));

    Some(Box::new(coordfield))
}
