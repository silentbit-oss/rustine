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
    let alloc = vec![0 as char; n + 1];
    let data = Vec::new();

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
        if c == 0 {
            data.clear();
        }
    }
    if c == 0 {
        buffer_t.len = 0;
    }
}

pub fn buffer_trim_left(buffer_t: &mut BufferT) {
    if let Some(data) = &mut buffer_t.data {
        let mut i = 0;
        while i < data.len() && data[i].is_whitespace() {
            i += 1;
        }
        data.drain(0..i);
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
    buffer_t.len = n; // This is the capacity without the null terminator.

    // Ensure the data vector has at least capacity for n+1 chars (including null terminator)
    if let Some(data) = &mut buffer_t.data {
        let current_capacity = data.capacity();
        if current_capacity < n + 1 {
            data.reserve_exact(n + 1 - current_capacity);
        }
    } else {
        let mut data = Vec::with_capacity(n + 1);
        buffer_t.data = Some(data);
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
    let str = str?;
    let len = str.len();

    let mut self_ = buffer_new_with_size(len)?;

    // Convert the input string to a Vec<char>
    let src: Vec<char> = str.chars().collect();

    if let Some(alloc) = &mut self_.alloc {
        // Copy the characters from src into the beginning of alloc
        let to_copy = std::cmp::min(alloc.len(), src.len());
        for i in 0..to_copy {
            alloc[i] = src[i];
        }
        // Now set data to be the first `len` characters of alloc (without the null terminator)
        self_.data = Some(alloc[0..len].to_vec());
    }

    Some(self_)
}

pub fn buffer_prepend(buffer_t: &mut BufferT, str: &str) -> i32 {
    let new_chars: Vec<char> = str.chars().collect();
    let len = new_chars.len();
    let prev = match &buffer_t.data {
        Some(data) => data.len(),
        None => 0,
    };
    let needed = len + prev;

    if buffer_t.len < needed {
        let ret = buffer_resize(buffer_t, needed);
        if ret == -1 {
            return -1;
        }
    }

    let mut new_data = Vec::with_capacity(needed);
    new_data.extend(new_chars);
    if let Some(data) = &buffer_t.data {
        new_data.extend(data);
    }
    buffer_t.data = Some(new_data);

    0
}

pub fn buffer_append_n(buffer_t: &mut BufferT, str: &[char], len: usize) -> i32 {
    let current_len = buffer_t.data.as_ref().map(|v| v.len()).unwrap_or(0);
    let needed = current_len + len;

    // Check if current allocation is sufficient (buffer_t.len is the capacity without null)
    if buffer_t.len > needed {
        if let Some(data) = &mut buffer_t.data {
            data.extend(&str[0..len]);
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
        data.extend(&str[0..len]);
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
        dest_data.extend(src_data[from..to].iter());
    }

    Some(self_)
}

pub fn buffer_compact(self_: &mut BufferT) -> isize {
    let len = buffer_length(self_);
    let rem = self_.len - len;
    
    // Create a new Vec<char> with length `len` (without extra null)
    let mut new_buf = vec!['\0'; len];
    
    // Copy data from self_.data to new_buf
    if let Some(data) = &self_.data {
        new_buf[..len].copy_from_slice(&data[..len]);
    }
    
    // Replace alloc and data with the new buffer
    self_.alloc = Some(new_buf.clone());
    self_.data = Some(new_buf);
    self_.len = len;
    
    rem as isize
}
pub fn buffer_clear(buffer_t: &mut BufferT) {
    buffer_fill(buffer_t, 0);
}

pub fn buffer_trim_right(buffer_t: &mut BufferT) {
    if let Some(data) = &mut buffer_t.data {
        let mut new_len = data.len();
        while new_len > 0 {
            let c = data[new_len - 1];
            if c.is_whitespace() {
                new_len -= 1;
            } else {
                break;
            }
        }
        data.truncate(new_len);
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
    
    let length2 = buffer_length(self_);

    // Format into buffer
    if let Some(data) = &mut self_.data {
        let dst_idx = length;
        let formatted = fmt::format(args);
        let bytes = formatted.len();
        
        // Ensure we have enough space
        if dst_idx + bytes > data.capacity() {
            return -1;
        }
        
        data.resize(dst_idx + bytes, '\0');
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
