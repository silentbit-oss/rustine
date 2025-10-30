use crate::*;

pub fn swap(a: &mut i32, b: &mut i32) {
    let t = *a;
    *a = *b;
    *b = t;
}
pub fn partition(arr: &mut [i32], low: usize, high: usize) -> usize {
    // Ensure the array slice is not empty and indices are valid
    if arr.is_empty() || low > high || high >= arr.len() {
        panic!("Invalid array bounds in partition");
    }

    let pivot = arr[high];
    let mut i = low as i32 - 1;  // Using i32 to handle potential underflow before bounds check

    for j in low..high {
        if arr[j] <= pivot {
            i += 1;
            // Convert i back to usize only after verifying it's non-negative
            if i >= 0 {
                let i_usize = i as usize;
                // Use split_at_mut to safely get mutable references to both elements
                if i_usize < j {
                    let (left, right) = arr.split_at_mut(j);
                    swap(&mut left[i_usize], &mut right[0]);
                } else if i_usize > j {
                    let (left, right) = arr.split_at_mut(i_usize);
                    swap(&mut right[0], &mut left[j]);
                }
                // If i_usize == j, no swap needed
            }
        }
    }

    // Final swap with pivot
    let final_pos = (i + 1) as usize;
    if final_pos < high {
        let (left, right) = arr.split_at_mut(high);
        swap(&mut left[final_pos], &mut right[0]);
    } else if final_pos > high {
        let (left, right) = arr.split_at_mut(final_pos);
        swap(&mut right[0], &mut left[high]);
    }
    // If final_pos == high, no swap needed

    final_pos
}
pub fn quickSort(arr: &mut [i32], low: usize, high: usize) {
    if low < high {
        let i = partition(arr, low, high);
        quickSort(arr, low, i.saturating_sub(1)); // Use saturating_sub to prevent underflow
        quickSort(arr, i + 1, high);
    }
}
