use crate::*;
use rand::Rng;


pub fn heman_import_u8(
    width: i32,
    height: i32,
    nbands: i32,
    source: Option<&[heman_byte]>,
    minval: f32,
    maxval: f32,
) -> HemanImage {
    // Check for NULL equivalent (None in Rust)
    let source = match source {
        Some(s) => s,
        None => return None,
    };

    // Create the result image
    let mut result = match heman_image_create(width, height, nbands) {
        Some(r) => r,
        None => return None,
    };

    // Calculate scale and size
    let scale = (maxval - minval) / 255.0f32;
    let size = (height * width * nbands) as usize;

    // Get mutable access to the data vector
    if let Some(ref mut data) = result.data {
        // Ensure the data vector has enough capacity
        if data.len() < size {
            data.resize(size, 0.0);
        }

        // Process each byte in the source
        for i in 0..size {
            if i >= source.len() {
                break; // Prevent out-of-bounds access
            }

            let v = (f32::from(source[i]) * scale) + minval;
            // Clamp the value between minval and maxval
            data[i] = v.clamp(minval, maxval);
        }
    }

    Some(result)
}
