use libc::FILE;
use translate_without_break_down::*;
use std::env;
use std::io;
use std::fs::File;
use std::path::Path;
use lazy_static::lazy_static;
use std::io::Write;
pub fn main() -> io::Result<()> {
    // Initialize variables
    let mut bs_in: Option<BitStream> = None;
    let mut bs_wr: Option<BitStream> = None;
    let mut b: Int32;
    let mut wr_block: Int32 = 0;
    let mut curr_block: Int32 = 0;
    let mut rb_ctr: Int32 = 0;
    let mut bits_read: MaybeUInt64 = 0;
    let mut buff_hi: UInt32 = 0;
    let mut buff_lo: UInt32 = 0;
    let mut block_crc: UInt32 = 0;

    // Set program name
    {
        let mut prog_name = PROG_NAME.lock().unwrap();
        let argv0 = std::env::args().next().unwrap_or_default();
        let src = argv0.chars().take(1999).collect::<String>();
        for (i, c) in src.chars().enumerate() {
            prog_name[i] = c;
        }
        prog_name[src.len()] = '\0';
    }

    eprintln!("bzip2recover 1.0.6: extracts blocks from damaged .bz2 files.");

    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        let prog_name = PROG_NAME.lock().unwrap();
        eprintln!("{}: usage is `{} damaged_file_name'.", 
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>(),
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>());
        
        match std::mem::size_of::<MaybeUInt64>() {
            8 => eprintln!("\trestrictions on size of recovered file: None"),
            4 => {
                eprintln!("\trestrictions on size of recovered file: 512 MB");
                eprintln!("\tto circumvent, recompile with MaybeUInt64 as an\n\tunsigned 64-bit int.");
            },
            _ => eprintln!("\tsizeof(MaybeUInt64) is not 4 or 8 -- configuration error."),
        }
        std::process::exit(1);
    }

    let input_file = &args[1];
    if input_file.len() >= 1980 {
        let prog_name = PROG_NAME.lock().unwrap();
        eprintln!("{}: supplied filename is suspiciously (>= {} chars) long. Bye!",
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>(),
                 input_file.len());
        std::process::exit(1);
    }

    {
        let mut in_file_name = IN_FILE_NAME.lock().unwrap();
        for (i, c) in input_file.chars().enumerate() {
            in_file_name[i] = c;
        }
        in_file_name[input_file.len()] = '\0';
    }

    // Phase 1: Find block boundaries
    let in_file = File::open(input_file)?;
    bs_in = bs_open_read_stream(Some(in_file));
    if bs_in.is_none() {
        let prog_name = PROG_NAME.lock().unwrap();
        let in_file_name = IN_FILE_NAME.lock().unwrap();
        eprintln!("{}: can't read `{}'",
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>(),
                 in_file_name.iter().take_while(|&&c| c != '\0').collect::<String>());
        std::process::exit(1);
    }

    let prog_name = PROG_NAME.lock().unwrap();
    eprintln!("{}: searching for block boundaries ...",
             prog_name.iter().take_while(|&&c| c != '\0').collect::<String>());

    bits_read = 0;
    buff_hi = 0;
    buff_lo = 0;
    curr_block = 0;
    {
        let mut b_start = B_START.lock().unwrap();
        b_start[0] = 0;
    }

    rb_ctr = 0;
    loop {
        b = bsGetBit(bs_in.as_mut().unwrap());
        bits_read += 1;
        if b == 2 {
            {
                let b_start = B_START.lock().unwrap();
                if bits_read >= b_start[curr_block as usize] && (bits_read - b_start[curr_block as usize]) >= 40 {
                    let mut b_end = B_END.lock().unwrap();
                    b_end[curr_block as usize] = bits_read - 1;
                    if curr_block > 0 {
                        eprintln!("   block {} runs from {} to {} (incomplete)", 
                                curr_block, b_start[curr_block as usize], b_end[curr_block as usize]);
                    }
                } else {
                    curr_block -= 1;
                }
            }
            curr_block -= 1;
            break;
        }
        buff_hi = (buff_hi << 1) | (buff_lo >> 31);
        buff_lo = (buff_lo << 1) | ((b as UInt32) & 1);
        if ((buff_hi & 0x0000ffff) == 0x00003141 && buff_lo == 0x59265359) ||
           ((buff_hi & 0x0000ffff) == 0x00001772 && buff_lo == 0x45385090) {
            {
                let mut b_end = B_END.lock().unwrap();
                if bits_read > 49 {
                    b_end[curr_block as usize] = bits_read - 49;
                } else {
                    b_end[curr_block as usize] = 0;
                }
            }
            
            {
                let b_start = B_START.lock().unwrap();
                let b_end = B_END.lock().unwrap();
                if curr_block > 0 && (b_end[curr_block as usize] - b_start[curr_block as usize]) >= 130 {
                    eprintln!("   block {} runs from {} to {}", 
                             rb_ctr + 1, b_start[curr_block as usize], b_end[curr_block as usize]);
                    let mut rb_start = RB_START.lock().unwrap();
                    let mut rb_end = RB_END.lock().unwrap();
                    rb_start[rb_ctr as usize] = b_start[curr_block as usize];
                    rb_end[rb_ctr as usize] = b_end[curr_block as usize];
                    rb_ctr += 1;
                }
            }
            
            if curr_block >= 50000 {
                tooManyBlocks(50000);
            }
            curr_block += 1;
            {
                let mut b_start = B_START.lock().unwrap();
                b_start[curr_block as usize] = bits_read;
            }
        }
    }

    bsClose(bs_in.take().unwrap());
    if rb_ctr < 1 {
        let prog_name = PROG_NAME.lock().unwrap();
        eprintln!("{}: sorry, I couldn't find any block boundaries.",
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>());
        std::process::exit(1);
    }

    let prog_name = PROG_NAME.lock().unwrap();
    eprintln!("{}: splitting into blocks",
             prog_name.iter().take_while(|&&c| c != '\0').collect::<String>());

    // Phase 2: Split into blocks
    let in_file = File::open(input_file)?;
    bs_in = bs_open_read_stream(Some(in_file));
    if bs_in.is_none() {
        let prog_name = PROG_NAME.lock().unwrap();
        let in_file_name = IN_FILE_NAME.lock().unwrap();
        eprintln!("{}: can't open `{}'",
                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>(),
                 in_file_name.iter().take_while(|&&c| c != '\0').collect::<String>());
        std::process::exit(1);
    }

    block_crc = 0;
    bs_wr = None;
    bits_read = 0;
    wr_block = 0;

    loop {
        b = bsGetBit(bs_in.as_mut().unwrap());
        if b == 2 {
            break;
        }
        buff_hi = (buff_hi << 1) | (buff_lo >> 31);
        buff_lo = (buff_lo << 1) | ((b as UInt32) & 1);
        
        {
            let rb_start = RB_START.lock().unwrap();
            if bits_read == (47 + rb_start[wr_block as usize]) {
                block_crc = (buff_hi << 16) | (buff_lo >> 16);
            }
        }

        {
            let rb_start = RB_START.lock().unwrap();
            let rb_end = RB_END.lock().unwrap();
            if bs_wr.is_some() && bits_read >= rb_start[wr_block as usize] && bits_read <= rb_end[wr_block as usize] {
                bsPutBit(bs_wr.as_mut().unwrap(), b);
            }
        }

        bits_read += 1;
        
        {
            let rb_end = RB_END.lock().unwrap();
            if bits_read == (rb_end[wr_block as usize] + 1) {
                if bs_wr.is_some() {
                    let bs = bs_wr.as_mut().unwrap();
                    // Write the block footer directly using bit operations
                    for byte in &[0x17, 0x72, 0x45, 0x38, 0x50, 0x90] {
                        for i in (0..8).rev() {
                            bsPutBit(bs, ((byte >> i) & 1) as Int32);
                        }
                    }
                    // Write the CRC
                    for i in (0..32).rev() {
                        bsPutBit(bs, ((block_crc >> i) & 1) as Int32);
                    }
                    bsClose(bs_wr.take().unwrap());
                }
                
                if wr_block >= rb_ctr {
                    break;
                }
                wr_block += 1;
            } else {
                let rb_start = RB_START.lock().unwrap();
                if bits_read == rb_start[wr_block as usize] {
                    let mut out_file_name = OUT_FILE_NAME.lock().unwrap();
                    for k in 0..2000 {
                        out_file_name[k] = '\0';
                    }

                    let in_file_name = IN_FILE_NAME.lock().unwrap();
                    let in_file_str: String = in_file_name.iter().take_while(|&&c| c != '\0').collect();
                    for (i, c) in in_file_str.chars().enumerate() {
                        out_file_name[i] = c;
                    }

                    let split_pos = out_file_name.iter().rposition(|&c| c == '/').map_or(0, |pos| pos + 1);
                    let split = &mut out_file_name[split_pos..];

                    let rec_str = format!("rec{:05}", wr_block + 1);
                    for (i, c) in rec_str.chars().enumerate() {
                        if i < split.len() {
                            split[i] = if c == ' ' { '0' } else { c };
                        }
                    }

                    let out_file_name = OUT_FILE_NAME.lock().unwrap();
                    let out_file_str: String = out_file_name.iter().take_while(|&&c| c != '\0').collect();
                    let mut output_path = Path::new(&out_file_str).to_path_buf();
                    if !endsInBz2(&out_file_name[..]) {
                        output_path.set_extension("bz2");
                    }

                    eprintln!("   writing block {} to `{}' ...", wr_block + 1, output_path.display());
                    let out_file = fopen_output_safely(Some(&output_path), "wb");
                    if out_file.is_none() {
                        let prog_name = PROG_NAME.lock().unwrap();
                        eprintln!("{}: can't write `{}'",
                                 prog_name.iter().take_while(|&&c| c != '\0').collect::<String>(),
                                 output_path.display());
                        std::process::exit(1);
                    }

                    bs_wr = bs_open_write_stream(out_file);
                    if let Some(bs) = bs_wr.as_mut() {
                        // Write the block header directly using bit operations
                        for byte in &[0x42, 0x5a, 0x68, 0x30 + 9, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59] {
                            for i in (0..8).rev() {
                                bsPutBit(bs, ((byte >> i) & 1) as Int32);
                            }
                        }
                    }
                }
            }
        }
    }

    let prog_name = PROG_NAME.lock().unwrap();
    eprintln!("{}: finished",
             prog_name.iter().take_while(|&&c| c != '\0').collect::<String>());

    Ok(())
}
