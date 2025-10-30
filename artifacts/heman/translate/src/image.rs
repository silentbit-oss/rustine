use crate::*;
use std::assert;

pub fn heman_image_create(width: i32, height: i32, nbands: i32) -> HemanImage {
    // Calculate total number of elements needed
    let total_elements = (width * height * nbands) as usize;
    
    // Create the data vector with uninitialized capacity (equivalent to malloc)
    let data = if total_elements > 0 {
        Some(vec![0.0; total_elements]) // Initialize with zeros for safety
    } else {
        None
    };

    // Create and return the Boxed HemanImageS
    Some(Box::new(HemanImageS {
        width,
        height,
        nbands,
        data,
    }))
}
pub fn heman_image_info(img: &HemanImageS, width: &mut i32, height: &mut i32, nbands: &mut i32) {
    *width = img.width;
    *height = img.height;
    *nbands = img.nbands;
}
pub fn heman_image_data(img: &HemanImageS) -> Option<&Vec<f32>> {
    img.data.as_ref()
}
pub fn heman_image_array(img: &HemanImage, data: &mut Option<Vec<f32>>, nfloats: &mut i32) {
    if let Some(img) = img {
        *data = img.data.clone();
        *nfloats = (img.width * img.height) * img.nbands;
    } else {
        *data = None;
        *nfloats = 0;
    }
}
pub fn heman_image_texel(img: &HemanImageS, x: i32, y: i32) -> Option<&[f32]> {
    // Calculate the offset in the data vector
    let offset = ((y * img.width) * img.nbands) + (x * img.nbands);
    
    // Get a reference to the data vector if it exists
    if let Some(data) = &img.data {
        // Check if the calculated offset is within bounds
        if offset >= 0 && (offset + img.nbands) <= data.len() as i32 {
            Some(&data[offset as usize..(offset + img.nbands) as usize])
        } else {
            None
        }
    } else {
        None
    }
}
pub fn heman_image_clear(img: &mut HemanImageS, value: f32) {
    let size = (img.width * img.height) * img.nbands;
    if let Some(dst) = &mut img.data {
        for dst_idx in 0..size as usize {
            dst[dst_idx] = value;
        }
    }
}
pub fn heman_image_destroy(img: HemanImage) {
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // and the Vec inside will also be automatically deallocated.
    // No explicit free is needed thanks to Rust's ownership model.
    // The function takes ownership of the Box and does nothing,
    // letting Rust's drop mechanism handle the cleanup.
}
pub fn heman_image_sample(img: &HemanImageS, u: f32, v: f32, result: &mut [f32]) {
    let mut result_idx = 0;
    
    // Calculate x coordinate with bounds checking
    let x_unclamped = (img.width as f32 * u).round() as i32;
    let x = x_unclamped.clamp(0, img.width - 1);
    
    // Calculate y coordinate with bounds checking
    let y_unclamped = (img.height as f32 * v).round() as i32;
    let y = y_unclamped.clamp(0, img.height - 1);
    
    // Get the texel data
    if let Some(data) = heman_image_texel(img, x, y) {
        let mut data_idx = 0;
        
        // Copy each band's value to the result
        for _ in 0..img.nbands {
            if result_idx < result.len() && data_idx < data.len() {
                result[result_idx] = data[data_idx];
                data_idx += 1;
                result_idx += 1;
            } else {
                break;
            }
        }
    }
}

pub fn heman_image_extract_alpha(img: HemanImage) -> HemanImage {
    // Unwrap the Option<Box<HemanImageS>> to access the inner data
    let img = match img {
        Some(img) => img,
        None => return None,
    };

    // Check that the image has exactly 4 bands (RGBA)
    assert!(img.nbands == 4, "Input image must have 4 bands (RGBA)");

    // Create a new single-channel image with the same dimensions
    let mut retval = match heman_image_create(img.width, img.height, 1) {
        Some(retval) => retval,
        None => return None,
    };

    // Calculate the total number of pixels
    let size = (img.width * img.height) as usize;

    // Get references to the source and destination data
    let src_data = match img.data {
        Some(ref data) => data,
        None => return None,
    };
    let dst_data = match retval.data {
        Some(ref mut data) => data,
        None => return None,
    };

    // Extract the alpha channel (every 4th element starting from index 3)
    for (dst_idx, src_idx) in (0..size).map(|i| (i, i * 4 + 3)) {
        dst_data[dst_idx] = src_data[src_idx];
    }

    Some(retval)
}
pub fn heman_image_extract_rgb(img: &HemanImageS) -> Option<Box<HemanImageS>> {
    // Assert that the input image has exactly 4 bands (RGBA)
    assert!(img.nbands == 4, "Input image must have 4 bands (RGBA)");

    // Create a new image with 3 bands (RGB)
    let mut retval = heman_image_create(img.width, img.height, 3)?;
    
    // Get mutable access to the return value's data
    if let Some(dst_data) = &mut retval.data {
        let size = (img.width * img.height) as usize;
        let src_data = img.data.as_ref()?;
        
        // Iterate over each pixel (src_idx tracks position in source RGBA data)
        for (src_idx, dst_idx) in (0..src_data.len()).step_by(4).zip((0..dst_data.len()).step_by(3)) {
            // Copy RGB components (skip alpha)
            dst_data[dst_idx] = src_data[src_idx];
            dst_data[dst_idx + 1] = src_data[src_idx + 1];
            dst_data[dst_idx + 2] = src_data[src_idx + 2];
        }
    }

    Some(retval)
}
