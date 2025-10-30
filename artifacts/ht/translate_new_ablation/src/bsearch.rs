use crate::*;
use std::cmp::Ordering;


pub fn cmp(a: &Item, b: &Item) -> Ordering {
    match (&a.key, &b.key) {
        (Some(key_a), Some(key_b)) => key_a.cmp(key_b),
        (Some(_), None) => Ordering::Greater,
        (None, Some(_)) => Ordering::Less,
        (None, None) => Ordering::Equal,
    }
}
