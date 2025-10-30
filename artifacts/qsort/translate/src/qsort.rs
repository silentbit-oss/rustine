use crate::*;

pub fn swap(a: &mut i32, b: &mut i32) {
    let t = *a;
    *a = *b;
    *b = t;
}
pub fn partition(arr: &mut [i32], low: usize, high: usize) -> usize {
    let pivot = arr[high];
    let mut i = low as i32 - 1;

    for j in low..high {
        if arr[j] <= pivot {
            i += 1;
            // Use separate scopes to avoid overlapping mutable borrows
            {
                let (a, b) = arr.split_at_mut(j);
                swap(&mut a[i as usize], &mut b[0]);
            }
        }
    }

    let final_pos = (i + 1) as usize;
    {
        let (a, b) = arr.split_at_mut(high);
        swap(&mut a[final_pos], &mut b[0]);
    }

    final_pos
}
pub fn quickSort(arr: &mut [i32], low: usize, high: usize) {
    if low < high {
        let i = partition(arr, low, high);
        quickSort(arr, low, i.saturating_sub(1)); // Use saturating_sub to prevent underflow
        quickSort(arr, i + 1, high);
    }
}
