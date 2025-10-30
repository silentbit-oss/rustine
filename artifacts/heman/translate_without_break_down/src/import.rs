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

    // Calculate scale factor and total size
    let scale = (maxval - minval) / 255.0f32;
    let size = (height * width * nbands) as usize;

    // Ensure we have enough data in source
    if source.len() < size {
        return None;
    }

    // Process the data
    if let Some(ref mut data) = result.data {
        for i in 0..size {
            let v = (f32::from(source[i]) * scale) + minval;
            // Clamp the value between minval and maxval
            data[i] = if v < minval {
                minval
            } else if v > maxval {
                maxval
            } else {
                v
            };
        }
    }

    Some(result)
}
