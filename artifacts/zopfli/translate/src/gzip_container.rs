use crate::*;
use std::io;
use std::io::Write;

pub fn CRC(data: Option<&[u8]>) -> Option<u32> {
    // Check for None (equivalent to NULL check in C)
    let data = data?;

    let mut data_idx = 0;
    let mut result = 0xffffffffu32;
    
    for &byte in data {
        result = CRC32_TABLE[((result ^ u32::from(byte)) & 0xff) as usize] ^ (result >> 8);
        data_idx += 1;
    }

    Some(result ^ 0xffffffffu32)
}

pub fn ZopfliGzipCompress(
    options: &ZopfliOptions,
    in_data: &[u8],
    insize: usize,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let crcvalue = CRC(Some(in_data)).unwrap_or(0);
    let mut bp = 0;

    // Helper function to append bytes with dynamic resizing
    fn append_byte(out: &mut Option<Vec<u8>>, outsize: &mut usize, byte: u8) {
        if out.is_none() {
            *out = Some(Vec::new());
        }
        if let Some(vec) = out {
            if *outsize == vec.capacity() {
                vec.reserve(1.max(vec.capacity() * 2));
            }
            vec.push(byte);
            *outsize += 1;
        }
    }

    // Gzip header
    append_byte(out, outsize, 31);  // ID1
    append_byte(out, outsize, 139); // ID2
    append_byte(out, outsize, 8);   // CM
    append_byte(out, outsize, 0);   // FLG
    append_byte(out, outsize, 0);   // MTIME (4 bytes)
    append_byte(out, outsize, 0);
    append_byte(out, outsize, 0);
    append_byte(out, outsize, 0);
    append_byte(out, outsize, 2);   // XFL
    append_byte(out, outsize, 3);   // OS

    // Deflate the data
    ZopfliDeflate(options, 2, true, in_data, insize, &mut bp, out, outsize);

    // CRC32 and ISIZE (input size modulo 2^32)
    append_byte(out, outsize, (crcvalue % 256) as u8);
    append_byte(out, outsize, ((crcvalue >> 8) % 256) as u8);
    append_byte(out, outsize, ((crcvalue >> 16) % 256) as u8);
    append_byte(out, outsize, ((crcvalue >> 24) % 256) as u8);
    append_byte(out, outsize, (insize % 256) as u8);
    append_byte(out, outsize, ((insize >> 8) % 256) as u8);
    append_byte(out, outsize, ((insize >> 16) % 256) as u8);
    append_byte(out, outsize, ((insize >> 24) % 256) as u8);

    if options.verbose != 0 {
        let compression_ratio = 100.0 * (insize as f64 - *outsize as f64) / insize as f64;
        writeln!(
            io::stderr(),
            "Original Size: {}, Gzip: {}, Compression: {:.2}% Removed",
            insize,
            *outsize,
            compression_ratio
        ).unwrap();
    }
}
