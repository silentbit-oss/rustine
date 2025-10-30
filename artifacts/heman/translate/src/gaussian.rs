use crate::*;

pub fn generate_gaussian_row(target: &mut [i32], fwidth: usize) {
    assert!(fwidth > 0, "fwidth must be greater than 0");
    let mut tmp = vec![0; fwidth]; // Allocate and initialize temporary vector
    
    // Initialize first element
    target[0] = 1;
    tmp[0] = 1;
    
    // Initialize remaining elements to 0
    for col in 1..fwidth {
        target[col] = 0;
        tmp[col] = 0;
    }
    
    for row in 1..fwidth {
        for col in 1..=row {
            target[col] = tmp[col] + tmp[col - 1];
        }
        
        for col in 1..=row {
            tmp[col] = target[col];
        }
    }
}
pub fn generate_gaussian_splat(target: &mut [f32], fwidth: usize) {
    // Allocate a Vec for gaussian_row instead of using malloc
    let mut gaussian_row = vec![0; fwidth];
    
    // Call the dependency function with the mutable slice
    generate_gaussian_row(&mut gaussian_row, fwidth);
    
    let shift = 1 << (fwidth - 1);
    let scale = 1.0 / ((shift * shift) as f32);
    
    let mut gptr_idx = 0;
    for j in 0..fwidth {
        for i in 0..fwidth {
            // Safe array access with bounds checking
            target[gptr_idx] = (gaussian_row[i] * gaussian_row[j]) as f32 * scale;
            gptr_idx += 1;
        }
    }
    
    // No need for explicit free - Vec is automatically dropped when out of scope
}
