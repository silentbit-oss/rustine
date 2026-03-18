use crate::*;

pub fn print_array(p: Option<&[f64]>, size: usize) {
	println!("\n* print_array");
    // Check if the slice is None (equivalent to NULL pointer check in C)
    if let Some(arr) = p {
        for i in 0..size {
            if i > 0 {
                print!(", ");
            }
            print!("{:.1}", arr[i]);
        }
        println!();
    }
}
