use crate::*;
use std::assert;

pub fn heman_image_create(width: i32, height: i32, nbands: i32) -> HemanImage {
    // Calculate total number of elements needed
    let total_elements = (width * height * nbands) as usize;
    
    // Create a new HemanImageS with the given parameters
    let img = Box::new(HemanImageS {
        width,
        height,
        nbands,
        data: Some(vec![0.0; total_elements]), // Initialize with zeros
    });

    Some(img) // Return as HemanImage (Option<Box<HemanImageS>>)
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
    let size = (img.width * img.height * img.nbands) as usize;
    if let Some(dst) = &mut img.data {
        for dst_idx in 0..size {
            dst[dst_idx] = value;
        }
    }
}
pub fn heman_image_destroy(img: HemanImage) {
    // The Box will be automatically dropped (freed) when it goes out of scope,
    // and the Vec inside HemanImageS will also be automatically dropped.
    // No explicit free needed in Rust thanks to RAII.
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
    let img = img.unwrap();
    
    // Check the assertion (nbands == 4)
    assert!(img.nbands == 4, "Input image must have 4 bands (RGBA)");
    
    // Create a new image with 1 band (alpha channel)
    let mut retval = heman_image_create(img.width, img.height, 1).unwrap();
    
    let size = img.width * img.height;
    let src = img.data.as_ref().unwrap(); // Safe unwrap since data is Option<Vec<f32>>
    let mut src_idx = 0;
    
    let dst = retval.data.as_mut().unwrap(); // Safe unwrap since data is Option<Vec<f32>>
    let mut dst_idx = 0;
    
    for _ in 0..size {
        src_idx += 3; // Skip RGB channels (indices 0,1,2)
        dst[dst_idx as usize] = src[src_idx as usize]; // Copy alpha channel (index 3)
        src_idx += 1; // Move to next pixel's R channel
        dst_idx += 1; // Move to next destination pixel
    }
    
    Some(retval)
}
pub fn heman_image_extract_rgb(img: &HemanImageS) -> Option<Box<HemanImageS>> {
    assert!(img.nbands == 4, "Input image must have 4 bands (RGBA)");
    
    let width = img.width;
    let height = img.height;
    let retval = heman_image_create(width, height, 3);
    
    let size = (width * height) as usize;
    let src = img.data.as_ref()?;
    let dst = match retval.as_ref() {
        Some(img) => img.data.as_ref(),
        None => return None,
    };
    let mut dst = dst?.clone();
    
    let mut src_idx = 0;
    let mut dst_idx = 0;
    
    for _ in 0..size {
        dst[dst_idx] = src[src_idx];
        src_idx += 1;
        dst_idx += 1;
        
        dst[dst_idx] = src[src_idx];
        src_idx += 1;
        dst_idx += 1;
        
        dst[dst_idx] = src[src_idx];
        src_idx += 1;
        dst_idx += 1;
        
        src_idx += 1; // Skip alpha channel
    }
    
    Some(Box::new(HemanImageS {
        width,
        height,
        nbands: 3,
        data: Some(dst),
    }))
}
