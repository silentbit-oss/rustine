use crate::*;

pub fn cmp(a: &Item, b: &Item) -> std::cmp::Ordering {
    match (&a.key, &b.key) {
        (Some(key_a), Some(key_b)) => key_a.cmp(key_b),
        (Some(_), None) => std::cmp::Ordering::Greater,
        (None, Some(_)) => std::cmp::Ordering::Less,
        (None, None) => std::cmp::Ordering::Equal,
    }
}
