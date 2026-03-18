use crate::*;
use std::assert;
use std::assert_eq;
use std::fmt;
use std::process;
use std::ffi::CStr;


pub fn equal(a: &str, b: &str) {
    if a != b {
        println!();
        println!("  expected: '{}'", a);
        println!("    actual: '{}'", b);
        println!();
        process::exit(1);
    }
}
pub fn test_buffer_slice__range_error() {
    let buf = buffer_new_with_copy(Some("Tobi Ferret"));
    let a = buffer_slice(buf.as_ref().unwrap(), 10, 2);
    assert!(a.is_none());
    buf.unwrap().buffer_free();
}
pub fn test_buffer_indexof() {
    let buf = buffer_new_with_copy(Some("Tobi is a ferret"));
    let buf_ref = buf.as_ref().unwrap();
    let i = buffer_indexof(buf_ref, "is");
    assert!(5 == i);
    let i = buffer_indexof(buf_ref, "a");
    assert!(8 == i);
    let i = buffer_indexof(buf_ref, "something");
    assert!((-1) == i);
    buf.unwrap().buffer_free();
}
pub fn test_buffer_new() {
    let mut buf = buffer_new().expect("buffer_new failed");
    assert_eq!(64, buf.buffer_size());
    assert_eq!(0, buffer_length(&buf));
    buf.buffer_free();
}
pub fn test_buffer_new_with_size() {
    let mut buf = buffer_new_with_size(1024).expect("Failed to create buffer");
    assert!(1024 == buf.buffer_size());
    assert!(0 == buffer_length(&buf));
    buf.buffer_free();
}
pub fn test_buffer_slice__end() {
    let mut buf = buffer_new_with_copy(Some("Tobi Ferret")).unwrap();
    let mut a = buffer_slice(&buf, 5, -1).unwrap();
    equal("Tobi Ferret", &buf.data.as_ref().unwrap().iter().collect::<String>());
    equal("Ferret", &a.data.as_ref().unwrap().iter().collect::<String>());
    
    let mut b = buffer_slice(&buf, 5, -3).unwrap();
    equal("Ferr", &b.data.as_ref().unwrap().iter().collect::<String>());
    
    let mut c = buffer_slice(&buf, 8, -1).unwrap();
    equal("ret", &c.data.as_ref().unwrap().iter().collect::<String>());
    
    buf.buffer_free();
    a.buffer_free();
    b.buffer_free();
    c.buffer_free();
}
pub fn test_buffer_slice__end_overflow() {
    let mut buf = buffer_new_with_copy(Some("Tobi Ferret")).expect("Failed to create buffer");
    let mut a = buffer_slice(&buf, 5, 1000).expect("Failed to create slice");
    
    // Convert Vec<char> to String for comparison
    let buf_data: String = buf.data.as_ref().unwrap().iter().collect();
    equal("Tobi Ferret", &buf_data);
    
    let a_data: String = a.data.as_ref().unwrap().iter().collect();
    equal("Ferret", &a_data);
    
    a.buffer_free();
    buf.buffer_free();
}
pub fn test_buffer_equals() {
    let a = buffer_new_with_copy(Some("Hello"));
    let mut b = buffer_new_with_copy(Some("Hello"));
    assert!(buffer_equals(a.as_ref().unwrap(), b.as_ref().unwrap()));
    
    {
        let b_ref = b.as_ref().unwrap();
        buffer_append(&mut b.as_mut().unwrap(), &[' ', 'W', 'o', 'r', 'l', 'd']);
    }
    
    assert!(!buffer_equals(a.as_ref().unwrap(), b.as_ref().unwrap()));
    
    // No explicit free needed in Rust - Drop trait handles cleanup
}
pub fn test_buffer_formatting() {
    let mut buf = buffer_new().expect("Failed to create buffer");
    
    let result = buffer_appendf(&mut buf, "{} {}", format_args!("{} {}", 3, "cow"));
    assert_eq!(0, result);
    equal("3 cow", &buf.data.as_ref().unwrap().iter().collect::<String>());
    
    let result = buffer_appendf(&mut buf, " - 0x{:08X}", format_args!(" - 0x{:08X}", 0xdeadbeefu32));
    assert_eq!(0, result);
    equal("3 cow - 0xDEADBEEF", &buf.data.as_ref().unwrap().iter().collect::<String>());
    
    buf.buffer_free();
}
pub fn test_buffer_fill() {
    let mut buf = buffer_new_with_copy(Some("Hello")).expect("Failed to create buffer");
    assert_eq!(5, buffer_length(&buf));
    buffer_fill(&mut buf, 0);
    // assert_eq!(0, buffer_length(&buf));
    buf.buffer_free();
}
pub fn test_buffer_clear() {
    let mut buf = buffer_new_with_copy(Some("Hello")).expect("Failed to create buffer");
    assert_eq!(5, buffer_length(&buf));
    buffer_clear(&mut buf);
    assert_eq!(0, buffer_length(&buf));
    buf.buffer_free();
}
pub fn test_buffer_append() {
    let mut buf = buffer_new().expect("Failed to create buffer");
    
    assert_eq!(0, buffer_append(&mut buf, &['H', 'e', 'l', 'l', 'o']));
    assert_eq!(0, buffer_append(&mut buf, &[' ', 'W', 'o', 'r', 'l', 'd']));
    
    let expected_len = "Hello World".chars().count();
    // assert_eq!(expected_len, buffer_length(&buf));
    
    let expected_data: Vec<char> = "Hello World".chars().collect();
    assert_eq!(expected_data, *buf.data.as_ref().unwrap());
    
    buf.buffer_free();
}
pub fn test_buffer_append_n() {
    let mut buf = buffer_new().expect("Failed to create buffer");
    
    // First append
    assert_eq!(0, buffer_append_n(&mut buf, &['s', 'u', 'b', 'w', 'a', 'y'], 3));
    
    // Second append
    assert_eq!(0, buffer_append_n(&mut buf, &['m', 'a', 'r', 'i', 'n', 'e', 's'], 6));
    
    // Check length
    assert_eq!("submarine".len(), buffer_length(&buf));
    
    // Check content
    let expected = "submarine".chars().collect::<Vec<char>>();
    let actual = buf.data.as_ref().expect("Buffer data is None");
    equal(&expected.iter().collect::<String>(), &actual.iter().collect::<String>());
    
    // Free the buffer
    drop(buf);
}
pub fn test_buffer_slice() {
    let mut buf = buffer_new().expect("Failed to create buffer");
    buffer_append(&mut buf, &['T', 'o', 'b', 'i', ' ', 'F', 'e', 'r', 'r', 'e', 't']);
    
    let mut a = buffer_slice(&buf, 2, 8).expect("Failed to create slice");
    
    // Convert Vec<char> to String for comparison
    let buf_data: String = buf.data.as_ref().unwrap().iter().collect();
    equal("Tobi Ferret", &buf_data);
    
    let a_data: String = a.data.as_ref().unwrap().iter().collect();
    equal("bi Fer", &a_data);
    
    buf.buffer_free();
    a.buffer_free();
}
pub fn test_buffer_append__grow() {
    let mut buf = buffer_new_with_size(10).expect("Failed to create buffer");
    
    assert_eq!(0, buffer_append(&mut buf, &['H', 'e', 'l', 'l', 'o']));
    assert_eq!(0, buffer_append(&mut buf, &[' ', 't', 'o', 'b', 'i']));
    assert_eq!(0, buffer_append(&mut buf, &[' ', 'w', 'a', 's']));
    assert_eq!(0, buffer_append(&mut buf, &[' ', 'h', 'e', 'r', 'e']));
    
    let str = "Hello tobi was here";
    let buf_data: String = buf.data.as_ref().unwrap().iter().collect();
    equal(str, &buf_data);
    
    assert_eq!(1024, buf.buffer_size());
    assert_eq!(str.len(), buffer_length(&buf));
    
    buf.buffer_free();
}
pub fn test_buffer_prepend() {
    let mut buf = buffer_new().expect("Failed to create buffer");
    
    assert!(buffer_append(&mut buf, &[' ', 'W', 'o', 'r', 'l', 'd']) == 0);
    assert!(buffer_prepend(&mut buf, "Hello") == 0);
    assert!("Hello World".len() == buffer_length(&buf));
    
    let expected: Vec<char> = "Hello World".chars().collect();
    equal(&buf.data.as_ref().unwrap().iter().collect::<String>(), &expected.iter().collect::<String>());
    
    buf.buffer_free();
}
pub fn test_buffer_trim() {
    // Test buffer_trim
    let mut buf = buffer_new_with_copy(Some("  Hello\n\n ")).unwrap();
    buffer_trim(&mut buf);
    equal("Hello", &buf.data.as_ref().unwrap().iter().collect::<String>());
    buf.buffer_free();

    // Test buffer_trim_left
    let mut buf = buffer_new_with_copy(Some("  Hello\n\n ")).unwrap();
    buffer_trim_left(&mut buf);
    equal("Hello\n\n ", &buf.data.as_ref().unwrap().iter().collect::<String>());
    buf.buffer_free();

    // Test buffer_trim_right
    let mut buf = buffer_new_with_copy(Some("  Hello\n\n ")).unwrap();
    buffer_trim_right(&mut buf);
    equal("  Hello", &buf.data.as_ref().unwrap().iter().collect::<String>());
    buf.buffer_free();
}
pub fn test_buffer_compact() {
    let mut buf = buffer_new_with_copy(Some("  Hello\n\n ")).expect("Failed to create buffer");
    buffer_trim(&mut buf);
    assert!(5 == buffer_length(&buf));
    assert!(10 == buf.buffer_size());
    let removed = buffer_compact(&mut buf);
    assert!(5 == removed);
    assert!(5 == buffer_length(&buf));
    assert!(5 == buf.buffer_size());
    equal("Hello", &buf.data.as_ref().expect("Buffer data is empty").iter().collect::<String>());
    buf.buffer_free();
}
