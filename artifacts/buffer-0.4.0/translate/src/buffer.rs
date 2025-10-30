use crate::*;
use std::vec::Vec;
use std::cmp::Ordering;
use std::char;
use std::fmt;
use std::ptr;
use std::ffi::CStr;
use std::fmt::Write;
use std::os::raw::c_char;


pub fn buffer_new_with_size(n: usize) -> Option<BufferT> {
    let mut alloc = vec![0 as char; n + 1];
    let data = alloc.clone();

    Some(BufferT {
        len: n,
        alloc: Some(alloc),
        data: Some(data),
    })
}

pub fn buffer_new_with_string_length(str: Option<Vec<char>>, len: usize) -> Option<BufferT> {
    let alloc = str;
    let data = alloc.clone();

    Some(BufferT {
        len,
        alloc,
        data,
    })
}
impl BufferT {
    pub fn buffer_size(&self) -> usize {
        self.len
    }
}
pub fn buffer_length(self_: &BufferT) -> usize {
    match &self_.data {
        Some(data) => data.len(),
        None => 0,
    }
}
impl BufferT {
    pub fn buffer_free(&mut self) {
        // In Rust, memory is automatically managed by the ownership system
        // The `alloc` and `data` fields are Option<Vec<char>>, which will be dropped automatically
        // No explicit free is needed in safe Rust
        self.alloc = Option::None;
        self.data = Option::None;
        // The BufferT itself will be dropped when it goes out of scope
    }
}

pub fn buffer_equals(self_: &BufferT, other: &BufferT) -> bool {
    match (&self_.data, &other.data) {
        (Some(self_data), Some(other_data)) => self_data == other_data,
        _ => false,
    }
}
pub fn buffer_indexof(self_: &BufferT, str_: &str) -> isize {
    // Convert the data Vec<char> to a String for searching
    let haystack = match &self_.data {
        Some(data) => data.iter().collect::<String>(),
        None => return -1,
    };

    // Use str::find to locate the substring (equivalent to strstr)
    match haystack.find(str_) {
        Some(pos) => pos as isize,
        None => -1,
    }
}

pub fn buffer_fill(buffer_t: &mut BufferT, c: i32) {
    if let Some(data) = &mut buffer_t.data {
        for byte in data.iter_mut() {
            *byte = c as u8 as char;
        }
    }
}

pub fn buffer_trim_left(buffer_t: &mut BufferT) {
    if let Some(data) = &mut buffer_t.data {
        while let Some(&c) = data.first() {
            if !c.is_whitespace() {
                break;
            }
            data.remove(0);
        }
    }
}

pub fn buffer_print(buffer_t: &BufferT) {
    let len = buffer_t.len;
    print!("\n ");
    
    if let Some(alloc) = &buffer_t.alloc {
        for i in 0..len {
            print!(" {:02x}", alloc[i] as u8);
            if ((i + 1) % 8) == 0 {
                print!("\n ");
            }
        }
    }
    
    println!();
}

pub fn buffer_resize(buffer_t: &mut BufferT, n: usize) -> i32 {
    // Calculate the new size aligned to 1024 bytes
    let n = (n + (1024 - 1)) & (!(1024 - 1));
    buffer_t.len = n;

    // Resize the allocation
    if let Some(alloc) = &mut buffer_t.alloc {
        alloc.resize(n + 1, '\0');
        buffer_t.data = Some(alloc.clone());
    } else {
        // Equivalent to realloc(NULL, size) - create new allocation
        let mut new_alloc = Vec::with_capacity(n + 1);
        new_alloc.resize(n + 1, '\0');
        buffer_t.alloc = Some(new_alloc.clone());
        buffer_t.data = Some(new_alloc);
    }

    // Ensure null termination
    if let Some(alloc) = &mut buffer_t.alloc {
        if alloc.len() > n {
            alloc[n] = '\0';
        }
    }

    0 // Success
}
pub fn buffer_new() -> Option<BufferT> {
    buffer_new_with_size(64)
}

pub fn buffer_new_with_string(str: Option<Vec<char>>) -> Option<BufferT> {
    // Convert Option<Vec<char>> to Option<&[char]> for length calculation
    let len = str.as_ref().map_or(0, |s| s.len());
    buffer_new_with_string_length(str, len)
}

pub fn buffer_new_with_copy(str: Option<&str>) -> Option<BufferT> {
    // Check if input string is None (equivalent to NULL in C)
    let str = str?;

    // Calculate length using Rust's len() method (equivalent to strlen)
    let len = str.len();

    // Create a new buffer with the calculated size
    let mut self_ = buffer_new_with_size(len)?;

    // Convert the input string to a Vec<char> for copying
    let src: Vec<char> = str.chars().collect();

    // Copy the string data into the buffer's alloc field
    if let Some(alloc) = &mut self_.alloc {
        alloc.extend(src);
    }

    // Set data to point to alloc (clone the reference)
    self_.data = self_.alloc.clone();

    Some(self_)
}

pub fn buffer_prepend(buffer_t: &mut BufferT, str: &str) -> i32 {
    let len = str.len();
    let prev = match &buffer_t.data {
        Some(data) => data.len(),
        None => 0,
    };
    let needed = len + prev;

    if buffer_t.len > needed {
        // Skip resizing if there's enough capacity
    } else {
        let ret = buffer_resize(buffer_t, needed);
        if ret == -1 {
            return -1;
        }
    }

    // Move existing data to make space for new string
    if let Some(data) = &mut buffer_t.data {
        // Ensure we have enough capacity
        if data.len() < needed {
            return -1;
        }

        // Move existing data to the right by `len` bytes
        unsafe {
            ptr::copy(
                data.as_ptr(),
                data.as_mut_ptr().add(len),
                prev,
            );
        }

        // Copy new string to the beginning
        for (i, c) in str.chars().enumerate() {
            if i >= data.len() {
                break;
            }
            data[i] = c;
        }
    } else {
        // If there was no data, just copy the new string
        buffer_t.data = Some(str.chars().collect());
    }

    0
}

pub fn buffer_append_n(buffer_t: &mut BufferT, str: &[char], len: usize) -> i32 {
    // Calculate previous length of data
    let prev = match &buffer_t.data {
        Some(data) => data.len(),
        None => 0,
    };

    let needed = len + prev;

    // Check if current allocation is sufficient
    if buffer_t.len > needed {
        if let Some(data) = &mut buffer_t.data {
            // Append the new characters
            data.extend(str.iter().take(len));
        }
        return 0;
    }

    // Resize the buffer if needed
    let ret = buffer_resize(buffer_t, needed);
    if ret == -1 {
        return -1;
    }

    // Append the new characters after successful resize
    if let Some(data) = &mut buffer_t.data {
        data.extend(str.iter().take(len));
    }
    
    0
}
pub fn buffer_append(buffer_t: &mut BufferT, str: &[char]) -> i32 {
    buffer_append_n(buffer_t, str, str.len())
}

pub fn buffer_slice(buf: &BufferT, from: usize, to: isize) -> Option<BufferT> {
    // Get the length of the data (equivalent to strlen in C)
    let len = buf.data.as_ref()?.len();

    // Handle negative 'to' index (C's inclusive end index)
    let to = if to < 0 {
        len - (!to as usize)  // Equivalent to C's ~to (bitwise NOT)
    } else {
        to as usize
    };

    // Check for invalid range
    if to < from {
        return None;
    }

    // Clamp 'to' to maximum length (Rust slices are exclusive, so no +1 needed)
    let to = std::cmp::min(to, len);

    // Calculate slice length
    let n = to - from;

    // Create new buffer with the calculated size
    let mut self_ = buffer_new_with_size(n)?;

    // Copy the slice (equivalent to memcpy in C)
    if let (Some(src_data), Some(dest_data)) = (buf.data.as_ref(), self_.data.as_mut()) {
        dest_data[..n].copy_from_slice(&src_data[from..to]);
    }

    Some(self_)
}

pub fn buffer_compact(self_: &mut BufferT) -> isize {
    let len = buffer_length(self_);
    let rem = self_.len - len;
    
    // Create a new Vec<char> with capacity len + 1, initialized to zeros
    let mut buf = vec!['\0'; len + 1];
    
    // Copy data from self_.data to buf if it exists
    if let Some(data) = &self_.data {
        if data.len() >= len {
            buf[..len].copy_from_slice(&data[..len]);
        } else {
            // If data is shorter than len, copy what we can
            buf[..data.len()].copy_from_slice(&data[..]);
        }
    }
    
    // Replace alloc and data with the new buffer
    self_.alloc = Some(buf.clone());
    self_.data = Some(buf);
    self_.len = len;
    
    rem as isize
}
pub fn buffer_clear(buffer_t: &mut BufferT) {
    buffer_fill(buffer_t, 0);
}

pub fn buffer_trim_right(buffer_t: &mut BufferT) {
    let len = buffer_length(buffer_t);
    if len == 0 {
        return;
    }

    let mut i = len - 1;
    while let Some(&c) = buffer_t.data.as_ref().and_then(|data| data.get(i)) {
        if c.is_whitespace() {
            if let Some(data) = &mut buffer_t.data {
                data[i] = '\0';
            }
            if i == 0 {
                break;
            }
            i -= 1;
        } else {
            break;
        }
    }
}

pub fn buffer_appendf(self_: &mut BufferT, format: &str, args: fmt::Arguments) -> i32 {
    // Get current length
    let length = buffer_length(self_);
    
    // Calculate required space
    let required = fmt::format(args).len();
    
    // Resize buffer
    if buffer_resize(self_, length + required) == -1 {
        return -1;
    }
    
    // Format into buffer
    if let Some(data) = &mut self_.data {
        let dst_idx = length;
        let formatted = fmt::format(args);
        let bytes = formatted.len();
        
        // Ensure we have enough space
        if dst_idx + bytes > data.len() {
            return -1;
        }
        
        // Copy formatted string into buffer
        data[dst_idx..dst_idx + bytes].copy_from_slice(formatted.chars().collect::<Vec<_>>().as_slice());
        
        // Return success (0) or failure (-1)
        if bytes < 0 { -1 } else { 0 }
    } else {
        -1
    }
}

// Helper macro to create fmt::Arguments
#[macro_export]
macro_rules! buffer_appendf {
    ($self:expr, $($arg:tt)*) => {
        buffer_appendf($self, format_args!($($arg)*))
    };
}
pub fn buffer_trim(buffer_t: &mut BufferT) {
    buffer_trim_left(buffer_t);
    buffer_trim_right(buffer_t);
}
