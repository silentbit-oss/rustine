use crate::*;
use std::assert;

pub fn makedata(key: i32) -> Option<Box<Mydata>> {
    let p = Box::new(Mydata { key });
    Some(p)
}

pub fn compare_func(d1: Option<&Mydata>, d2: Option<&Mydata>) -> i32 {
    // Use assert! macro to check for null pointers (None in Rust)
    assert!(d1.is_some(), "d1 is NULL");
    assert!(d2.is_some(), "d2 is NULL");

    // Unwrap safely since we've asserted they're Some
    let p1 = d1.unwrap();
    let p2 = d2.unwrap();

    if p1.key == p2.key {
        0
    } else if p1.key > p2.key {
        1
    } else {
        -1
    }
}
pub fn destroy_func(d: Option<Box<Mydata>>) {
    // Rust's Option<T> replaces NULL checks, Box<T> handles heap allocation
    // The assert in C is replaced by unwrapping the Option
    let p = d.expect("d should not be null");  // This will panic if d is None, similar to assert
    
    // In Rust, the Box will be automatically dropped (freed) when it goes out of scope
    // No explicit free needed - Rust's ownership system handles memory deallocation
}

pub fn print_func(d: Option<&Mydata>) {
    // Check for NULL equivalent (None in Rust)
    assert!(d.is_some(), "d cannot be null");
    
    // Unwrap safely since we've asserted it's Some
    let p = d.unwrap();
    
    // Use println! macro as Rust's equivalent to printf
    println!("{}", p.key);
}

pub fn print_char_func(d: Option<&Mydata>) {
    // Check for NULL equivalent (None)
    assert!(d.is_some(), "d should not be NULL");
    
    // Unwrap safely since we've asserted it's Some
    let p = d.unwrap();
    
    // Print the character (key & 127) using Rust's println!
    println!("{}", (p.key & 127) as u8 as char);
}
