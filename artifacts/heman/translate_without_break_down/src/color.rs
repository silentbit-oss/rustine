use crate::*;
use lazy_static::lazy_static;
use std::assert;
use rand::Rng;
use std::f32::consts::E;

pub fn smoothstep(edge0: f32, edge1: f32, x: f32) -> f32 {
    let t = ((x - edge0) / (edge1 - edge0)).clamp(0.0, 1.0);
    t * t * (3.0 - 2.0 * t)
}

lazy_static! {
    pub static ref _GAMMA: std::sync::Mutex<f32> = std::sync::Mutex::new(0.0);
}

pub fn heman_color_set_gamma(g: f32) {
    let mut gamma = _GAMMA.lock().unwrap();
    *gamma = g;
}
pub fn heman_color_from_grayscale(grayscale: HemanImage) -> HemanImage {
    // Unwrap the Option<Box<HemanImageS>> to access the inner data
    let grayscale = grayscale.unwrap();
    
    // Assert that the input image has exactly 1 band (grayscale)
    assert!(grayscale.nbands == 1, "Input image must be grayscale (1 band)");
    
    let w = grayscale.width;
    let h = grayscale.height;
    let mut result = heman_image_create(w, h, 3).unwrap(); // Create new 3-band image
    
    let size = w * h;
    let src = grayscale.data.as_ref().unwrap(); // Get source data
    
    // Get mutable access to destination data
    let dst = result.data.as_mut().unwrap();
    
    // Iterate through each pixel in the source image
    for i in 0..size {
        let v = src[i as usize]; // Get grayscale value
        
        // Write the same value to all 3 color channels (R, G, B)
        let base_idx = (i * 3) as usize;
        dst[base_idx] = v;
        dst[base_idx + 1] = v;
        dst[base_idx + 2] = v;
    }
    
    Some(result) // Return the new color image
}

pub fn heman_color_to_grayscale(colorimg: HemanImage) -> HemanImage {
    // Unwrap the Option<Box<HemanImageS>> to access the inner data
    let colorimg = match colorimg {
        Some(img) => img,
        None => return None,
    };

    // Check that the input image has exactly 3 color bands (RGB)
    assert!(colorimg.nbands == 3, "Input image must have 3 color bands (RGB)");

    let w = colorimg.width;
    let h = colorimg.height;
    let result = heman_image_create(w, h, 1);
    
    // Early return if image creation failed
    let mut result = match result {
        Some(img) => img,
        None => return None,
    };

    let size = w * h;
    
    // Get mutable access to the destination data
    if let Some(dst) = &mut result.data {
        // Get immutable access to the source data
        if let Some(src) = &colorimg.data {
            // Iterate over each pixel (3 source values per pixel)
            for i in 0..size {
                let src_idx = (i * 3) as usize;
                let r = src[src_idx];
                let g = src[src_idx + 1];
                let b = src[src_idx + 2];
                
                // Calculate grayscale value using standard weights
                dst[i as usize] = (0.299 * r) + (0.587 * g) + (0.114 * b);
            }
        }
    }

    Some(result)
}

pub fn heman_internal_rg(cfield: HemanImage) -> HemanImage {
    // Unwrap the Option<Box<HemanImageS>> to access the inner data
    let cfield = match cfield {
        Some(boxed) => boxed,
        None => return None,
    };

    // Assert that nbands == 2 as in the C code
    assert!(cfield.nbands == 2, "Input image must have exactly 2 bands");

    let w = cfield.width;
    let h = cfield.height;
    
    // Create target image with 3 bands
    let mut target = match heman_image_create(w, h, 3) {
        Some(t) => t,
        None => return None,
    };

    // Get mutable references to the data vectors
    let src_data = match cfield.data {
        Some(ref data) => data,
        None => return None,
    };
    let dst_data = match target.data {
        Some(ref mut data) => data,
        None => return None,
    };

    let size = (w * h) as usize;
    let mut src_idx = 0;
    let mut dst_idx = 0;

    for _ in 0..size {
        // Read u and v from source, dividing by width/height as in C code
        let u = src_data[src_idx] / w as f32;
        src_idx += 1;
        let v = src_data[src_idx] / h as f32;
        src_idx += 1;

        // Write u, v, and 0 to destination
        dst_data[dst_idx] = u;
        dst_idx += 1;
        dst_data[dst_idx] = v;
        dst_idx += 1;
        dst_data[dst_idx] = 0.0;
        dst_idx += 1;
    }

    Some(target)
}
pub fn heman_color_apply_gradient(
    heightmap: &HemanImageS,
    minheight: f32,
    maxheight: f32,
    gradient: &HemanImageS,
) -> Option<Box<HemanImageS>> {
    assert!(heightmap.nbands == 1);
    assert!(gradient.height == 1);
    assert!(gradient.nbands == 3);

    let w = heightmap.width;
    let h = heightmap.height;
    let mut result = heman_image_create(w, h, 3)?;
    let result = result.as_mut();

    let size = (result.height * result.width) as usize;
    let dst = result.data.as_mut().unwrap(); // We can unwrap here as we just created the image
    let mut dst_idx = 0;

    let src = heightmap.data.as_ref()?;
    let mut src_idx = 0;

    let scale = 1.0f32 / (maxheight - minheight);

    for _ in 0..size {
        let val = (src[src_idx as usize] - minheight) * scale;
        let u = val.clamp(0.0, 1.0);

        let dst_slice = &mut dst[dst_idx as usize..dst_idx as usize + 3];
        heman_image_sample(gradient, u, 0.5, dst_slice);

        dst_idx += 3;
        src_idx += 1;
    }

    Some(Box::new(result.clone()))
}
pub fn heman_color_create_gradient(
    width: i32,
    num_colors: i32,
    cp_locations: &[i32],
    cp_values: &[HemanColor],
) -> HemanImage {
    assert!(width > 0 && num_colors >= 2);
    assert_eq!(cp_locations[0], 0);
    assert_eq!(cp_locations[num_colors as usize - 1], width - 1);

    let gamma = *_GAMMA.lock().unwrap();
    let inv = 1.0 / 255.0;
    let mut f32colors = Vec::with_capacity((num_colors * 3) as usize);

    for rgb in cp_values.iter().take(num_colors as usize) {
        let r = (((rgb >> 16) as f32) * inv).powf(gamma);
        let g = ((((rgb >> 8) & 0xff) as f32) * inv).powf(gamma);
        let b = (((rgb & 0xff) as f32) * inv).powf(gamma);
        f32colors.extend_from_slice(&[r, g, b]);
    }

    let mut result = heman_image_create(width, 1, 3);
    let mut index0 = 0;
    let mut index1 = 1;
    let invgamma = 1.0 / gamma;

    if let Some(ref mut result_data) = result.as_mut().and_then(|r| r.data.as_mut()) {
        let mut dst_idx = 0;
        let mut x = 0;

        while x < width {
            let loc0 = cp_locations[index0];
            let loc1 = cp_locations[index1];
            let t = if loc0 == loc1 {
                0.0
            } else {
                let t_val = (x - loc0) as f32 / (loc1 - loc0) as f32;
                if t_val >= 1.0 {
                    x -= 1;
                    index0 += 1;
                    index1 = if (index1 + 1) > (num_colors - 1).try_into().unwrap() {
                        (num_colors - 1).try_into().unwrap()
                    } else {
                        index1 + 1
                    };
                    continue;
                }
                t_val
            };

            let r0 = f32colors[index0 * 3];
            let g0 = f32colors[index0 * 3 + 1];
            let b0 = f32colors[index0 * 3 + 2];
            let r1 = f32colors[index1 * 3];
            let g1 = f32colors[index1 * 3 + 1];
            let b1 = f32colors[index1 * 3 + 2];
            let invt = 1.0 - t;
            let r = (r0 * invt + r1 * t).powf(invgamma);
            let g = (g0 * invt + g1 * t).powf(invgamma);
            let b = (b0 * invt + b1 * t).powf(invgamma);

            result_data[dst_idx] = r;
            result_data[dst_idx + 1] = g;
            result_data[dst_idx + 2] = b;
            dst_idx += 3;
            x += 1;
        }
    }

    result
}
pub fn heman_color_from_cpcf(
    cfield: Option<&HemanImageS>,
    texture: Option<&HemanImageS>,
) -> Option<Box<HemanImageS>> {
    // Check if texture is None (equivalent to NULL check in C)
    let texture = match texture {
        Some(t) => t,
        None => return heman_internal_rg(cfield.cloned().map(Box::new)),
    };

    let cfield = cfield.expect("cfield must not be None");
    
    // Assertions translated to Rust's debug_assert!
    debug_assert!(cfield.nbands == 2, "cfield must have 2 bands");
    debug_assert!(
        texture.nbands == 3 || texture.nbands == 4,
        "texture must have 3 or 4 bands"
    );
    debug_assert!(
        cfield.width == texture.width,
        "cfield and texture must have same width"
    );
    debug_assert!(
        cfield.height == texture.height,
        "cfield and texture must have same height"
    );

    let w = cfield.width;
    let h = cfield.height;
    let mut target = heman_image_create(w, h, texture.nbands).expect("Failed to create image");
    let dst = target.data.as_mut().expect("Target data must exist");
    let mut dst_idx = 0;

    let src = cfield.data.as_ref().expect("Source data must exist");
    let mut src_idx = 0;

    let size = (w * h) as usize;
    for _ in 0..size {
        let u = src[src_idx];
        src_idx += 1;
        let v = src[src_idx];
        src_idx += 1;

        let texel = heman_image_texel(texture, u as i32, v as i32).expect("Failed to get texel");
        let mut texel_idx = 0;

        for _ in 0..texture.nbands {
            dst[dst_idx] = texel[texel_idx];
            texel_idx += 1;
            dst_idx += 1;
        }
    }

    Some(target)
}
