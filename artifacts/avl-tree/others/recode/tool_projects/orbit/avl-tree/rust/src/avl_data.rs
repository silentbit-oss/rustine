/*
 * Example Data Type for AVL Tree
 * Translated from C implementation by xieqing
 */

use std::cmp::Ordering;
use std::fmt;

// Example Data Structure

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct MyData {
    pub key: i32,
}

// Functions

pub fn makedata(key: i32) -> MyData {
    MyData { key }
}

pub fn compare_func(d1: &MyData, d2: &MyData) -> Ordering {
    d1.key.cmp(&d2.key)
}

pub fn destroy_func(_d: MyData) {
    // In Rust, memory is automatically freed when the value goes out of scope
    // This function exists for API compatibility with the C version
}

pub fn print_func(d: &MyData) {
    print!("{}", d.key);
}

pub fn print_char_func(d: &MyData) {
    print!("{}", (d.key & 127) as u8 as char);
}

// Trait Implementations

impl Ord for MyData {
    fn cmp(&self, other: &Self) -> Ordering {
        self.key.cmp(&other.key)
    }
}

impl PartialOrd for MyData {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

impl fmt::Display for MyData {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.key)
    }
}
