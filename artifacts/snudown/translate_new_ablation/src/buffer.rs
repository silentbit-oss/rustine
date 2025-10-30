use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use std::alloc::realloc;
use std::fmt;
use std::io::Write;
use std::ptr::NonNull;
pub fn bufrelease(buf: Option<Box<Buf>>) {
    // In Rust, we use Option<Box<T>> to represent a nullable pointer to heap-allocated data
    if let Some(buf) = buf {
        // The Box will be automatically dropped (freed) when it goes out of scope
        // The inner Vec<u8> (if present in data) will also be automatically dropped
        // No explicit free needed - Rust's ownership system handles it
    }
    // If buf is None, nothing happens (like the NULL check in C)
}
pub fn bufgrow(buf: &mut Buf, neosz: usize) -> Result<(), BufErrorT> {
    assert!(buf.unit > 0);
    
    if neosz > (1024 * 1024 * 16) {
        return Err(BufErrorT::BUF_ENOMEM);
    }
    
    if buf.asize >= neosz {
        return Ok(());
    }
    
    let mut neoasz = buf.asize + buf.unit;
    while neoasz < neosz {
        neoasz += buf.unit;
    }
    
    // Resize the Vec instead of manual reallocation
    match &mut buf.data {
        Some(vec) => {
            vec.try_reserve_exact(neoasz - vec.capacity()).map_err(|_| BufErrorT::BUF_ENOMEM)?;
            vec.resize(neoasz, 0);
        }
        None => {
            let mut new_vec = Vec::with_capacity(neoasz);
            new_vec.resize(neoasz, 0);
            buf.data = Some(new_vec);
        }
    }
    
    buf.asize = neoasz;
    Ok(())
}

#[derive(Debug)]
pub enum BufError {
    Enomem,
}
pub fn bufputc(buf: &mut Buf, c: i32) {
    // Convert C's assert to Rust's debug_assert (only active in debug builds)
    debug_assert!(buf.unit != 0, "buf.unit must not be zero");

    // Check if we need to grow the buffer
    if (buf.size + 1) > buf.asize {
        if bufgrow(buf, buf.size + 1).is_err() {
            return;
        }
    }

    // Safely write the byte to the buffer
    if let Some(data) = &mut buf.data {
        // Convert i32 to u8 (assuming c is a byte value)
        data[buf.size] = c as u8;
        buf.size += 1;
    }
}

pub fn bufnew(unit: usize) -> Option<Box<Buf>> {
    let mut buf = Box::new(Buf {
        data: None,
        size: 0,
        asize: 0,
        unit,
    });
    
    Some(buf)
}
pub fn bufput(buf: &mut Buf, data: &[u8], len: usize) {
    assert!(buf.unit > 0);  // Equivalent to C's assert(buf && buf->unit)
    
    if (buf.size + len) > buf.asize {
        if bufgrow(buf, buf.size + len).is_err() {
            return;
        }
    }
    
    if let Some(buf_data) = &mut buf.data {
        buf_data[buf.size..buf.size + len].copy_from_slice(&data[..len]);
        buf.size += len;
    }
}
pub fn buftruncate(buf: &mut Buf, size: usize) -> Result<(), crate::BufErrorT> {
    if buf.size < size {
        return Err(crate::BufErrorT::BUF_EINVALIDIDX);
    }
    buf.size = size;
    Ok(())
}
pub fn bufputs(buf: &mut Buf, str: &str) {
    bufput(buf, str.as_bytes(), str.len());
}
pub fn bufprefix(buf: &Buf, prefix: &str) -> i32 {
    // Assert equivalent in Rust - panic if condition is not met
    assert!(buf.unit != 0, "buf.unit must not be zero");

    // Get the data as a slice if it exists, otherwise return 0 (empty buffer)
    let data = match &buf.data {
        Some(d) => d,
        None => return 0,
    };

    // Iterate through the buffer and prefix
    for (i, &byte) in data.iter().take(buf.size).enumerate() {
        // Get the corresponding prefix byte if it exists
        match prefix.as_bytes().get(i) {
            Some(&p_byte) => {
                if byte != p_byte {
                    return (byte as i32) - (p_byte as i32);
                }
            }
            None => return 0,
        }
    }

    0
}
pub fn bufreset(buf: &mut Buf) {
    if let Some(data) = buf.data.take() {
        // The Vec<u8> will be dropped here automatically
    }
    buf.size = 0;
    buf.asize = 0;
}
pub fn bufslurp(buf: &mut Buf, len: usize) {
    assert!(buf.data.is_some() && buf.unit != 0);
    if len >= buf.size {
        buf.size = 0;
        return;
    }
    buf.size -= len;
    if let Some(data) = &mut buf.data {
        data.copy_within(len..(len + buf.size), 0);
    }
}
pub fn bufcstr(buf: &mut Buf) -> Option<&str> {
    // Equivalent to C's assert(buf && buf->unit)
    assert!(buf.unit != 0, "buf unit must not be zero");

    // First check if we can return early with existing null-terminated data
    let can_return_early = if buf.size < buf.asize {
        buf.data.as_ref().map_or(false, |data| {
            data.get(buf.size) == Some(&0)
        })
    } else {
        false
    };

    if can_return_early {
        return buf.data.as_ref().and_then(|data| {
            std::str::from_utf8(&data[..buf.size]).ok()
        });
    }

    // If not null-terminated, try to grow buffer and add null terminator
    let required_size = buf.size + 1;
    if (required_size <= buf.asize) || bufgrow(buf, required_size).is_ok() {
        if let Some(data) = &mut buf.data {
            if buf.size < data.len() {
                data[buf.size] = 0;
                return std::str::from_utf8(&data[..buf.size]).ok();
            }
        }
    }

    None
}

pub fn bufprintf(buf: &mut Buf, fmt: &str, args: fmt::Arguments) {
    // Check assertions (equivalent to C's assert)
    assert!(buf.unit > 0, "buf unit must be positive");

    // First attempt to write without growing
    let initial_size = buf.size;
    let available = buf.asize.checked_sub(initial_size).unwrap_or(0);
    
    // Create a writer that writes into the buffer
    let mut writer = BufWriter {
        buf,
        position: initial_size,
        initial_size,
    };

    // First attempt to write
    if let Err(e) = writer.write_fmt(args) {
        if e.kind() != std::io::ErrorKind::WriteZero {
            return;
        }
        
        // Need to grow the buffer
        let formatted_len = format_args!("{}", args).to_string().len();
        let new_size = initial_size + formatted_len;
        
        if bufgrow(writer.buf, new_size + 1).is_err() {
            return;
        }
        
        // Reset writer with new buffer size
        let mut writer = BufWriter {
            buf: writer.buf,
            position: initial_size,
            initial_size,
        };
        
        if writer.write_fmt(args).is_err() {
            return;
        }
    }
    
    // Update the buffer size
    buf.size = writer.position;
}

// Helper struct to implement Write for our buffer
struct BufWriter<'a> {
    buf: &'a mut Buf,
    position: usize,
    initial_size: usize,
}

impl<'a> Write for BufWriter<'a> {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let available = self.buf.asize - self.position;
        let write_len = buf.len().min(available);
        
        if write_len > 0 {
            if let Some(data) = &mut self.buf.data {
                data[self.position..self.position + write_len].copy_from_slice(&buf[..write_len]);
                self.position += write_len;
                Ok(write_len)
            } else {
                Err(std::io::ErrorKind::WriteZero.into())
            }
        } else {
            Err(std::io::ErrorKind::WriteZero.into())
        }
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}
