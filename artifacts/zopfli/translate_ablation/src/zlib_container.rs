use crate::*;
use std::cmp::min;
use std::io::Write;
use std::io;


pub fn adler32(data: &[u8]) -> u32 {
    const SUMS_OVERFLOW: usize = 5550;
    const MOD: u32 = 65521;
    
    let mut s1: u32 = 1;
    let mut s2: u32 = 0;
    let mut remaining = data.len();
    let mut data_idx = 0;
    
    while remaining > 0 {
        let amount = min(remaining, SUMS_OVERFLOW);
        remaining -= amount;
        
        for _ in 0..amount {
            s1 = s1.wrapping_add(data[data_idx] as u32);
            data_idx += 1;
            s2 = s2.wrapping_add(s1);
        }
        
        s1 %= MOD;
        s2 %= MOD;
    }
    
    (s2 << 16) | s1
}
pub fn ZopfliZlibCompress(
    options: &ZopfliOptions,
    in_data: &[u8],
    out: &mut Vec<u8>,
) -> io::Result<()> {
    let mut bitpointer = 0;
    let checksum = adler32(in_data);
    let cmf = 120;
    let flevel = 3;
    let fdict = 0;
    let cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
    let fcheck = 31 - (cmfflg % 31);
    let cmfflg = cmfflg + fcheck;

    // Write CMF and FLG bytes
    out.push((cmfflg / 256) as u8);
    out.push((cmfflg % 256) as u8);

    // Compress data using deflate
    let mut out_option = Some(out.clone());
    let mut outsize = out.len();
    ZopfliDeflate(
        options,
        2,
        true,  // final_block should be bool, not 1
        in_data,
        &mut bitpointer,
        &mut out_option,
        &mut outsize,
    );
    if let Some(updated_out) = out_option {
        *out = updated_out;
    }

    // Write checksum (big-endian)
    out.push((checksum >> 24) as u8);
    out.push((checksum >> 16) as u8);
    out.push((checksum >> 8) as u8);
    out.push(checksum as u8);

    if options.verbose != 0 {
        let insize = in_data.len();
        let outsize = out.len();
        let ratio = 100.0 * (insize as f64 - outsize as f64) / insize as f64;
        writeln!(
            io::stderr(),
            "Original Size: {}, Zlib: {}, Compression: {:.2}% Removed",
            insize, outsize, ratio
        )?;
    }

    Ok(())
}
