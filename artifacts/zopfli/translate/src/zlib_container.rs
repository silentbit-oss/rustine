use crate::*;
use std::io;
use std::io::Write;

pub fn adler32(data: &[u8]) -> u32 {
    let mut data_idx = 0;
    const SUMS_OVERFLOW: usize = 5550;
    let mut s1: u32 = 1;
    let mut s2: u32 = 0; // Equivalent to (1 >> 16) in C since 1 is u32
    
    let mut size = data.len();
    while size > 0 {
        let amount = if size > SUMS_OVERFLOW {
            SUMS_OVERFLOW
        } else {
            size
        };
        size -= amount;
        
        for _ in 0..amount {
            s1 = s1.wrapping_add(data[data_idx] as u32);
            data_idx += 1;
            s2 = s2.wrapping_add(s1);
        }
        
        s1 %= 65521;
        s2 %= 65521;
    }
    
    (s2 << 16) | s1
}
pub fn ZopfliZlibCompress(
    options: &ZopfliOptions,
    in_data: &[u8],
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    let mut bitpointer = 0;
    let checksum = adler32(in_data);
    let cmf = 120;
    let flevel = 3;
    let fdict = 0;
    let cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
    let fcheck = 31 - (cmfflg % 31);
    let cmfflg = cmfflg + fcheck;

    // Helper function to append bytes to the output
    fn append_byte(out: &mut Option<Vec<u8>>, outsize: &mut usize, byte: u8) {
        if out.is_none() {
            *out = Some(Vec::new());
        }
        if let Some(vec) = out {
            vec.push(byte);
            *outsize += 1;
        }
    }

    // Write CMF and FLG bytes
    append_byte(out, outsize, (cmfflg / 256) as u8);
    append_byte(out, outsize, (cmfflg % 256) as u8);

    // Perform the deflate compression
    ZopfliDeflate(options, 2, true, in_data, in_data.len(), &mut bitpointer, out, outsize);

    // Write checksum bytes
    append_byte(out, outsize, (checksum >> 24) as u8);
    append_byte(out, outsize, (checksum >> 16) as u8);
    append_byte(out, outsize, (checksum >> 8) as u8);
    append_byte(out, outsize, checksum as u8);

    if options.verbose != 0 {
        let compression_ratio = 100.0 * (in_data.len() as f64 - *outsize as f64) / in_data.len() as f64;
        writeln!(
            io::stderr(),
            "Original Size: {}, Zlib: {}, Compression: {:.2}% Removed",
            in_data.len(),
            *outsize,
            compression_ratio
        ).unwrap();
    }
}
