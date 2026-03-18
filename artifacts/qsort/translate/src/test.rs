use crate::*;

pub fn test_quickSort() {
    let mut arr1 = [12, 11, 13, 5, 6, 7];
    let expected1 = [5, 6, 7, 11, 12, 13];
    let n1 = arr1.len();
    quickSort(&mut arr1, 0, n1 - 1);
    for i in 0..n1 {
        assert_eq!(arr1[i], expected1[i]);
    }

    let mut arr2 = [3, 3, 3, 3, 3, 3];
    let expected2 = [3, 3, 3, 3, 3, 3];
    let n2 = arr2.len();
    quickSort(&mut arr2, 0, n2 - 1);
    for i in 0..n2 {
        assert_eq!(arr2[i], expected2[i]);
    }

    let mut arr3 = [1, 2, 3, 4, 5, 6];
    let expected3 = [1, 2, 3, 4, 5, 6];
    let n3 = arr3.len();
    quickSort(&mut arr3, 0, n3 - 1);
    for i in 0..n3 {
        assert_eq!(arr3[i], expected3[i]);
    }

    let mut arr4 = [42];
    let expected4 = [42];
    let n4 = arr4.len();
    quickSort(&mut arr4, 0, n4 - 1);
    assert_eq!(arr4[0], expected4[0]);

    let arr5: [i32; 0] = [];
    let n5 = arr5.len();
    quickSort(&mut [], 0, n5.saturating_sub(1));
    assert_eq!(n5, 0);
}
