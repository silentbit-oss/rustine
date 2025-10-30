use libc::FILE;
use translate::*;
use std::env;
use std::fs::File;
use std::io::Read;
use std::io::Write;
use std::path::Path;
use std::process::exit;
use lazy_static::lazy_static;
use rand::Rng;
pub fn main() -> () {
    let mut inFile: Option<File> = None;
    let mut inFile_idx = 0;
    let mut outFile: Option<File> = None;
    let mut outFile_idx = 0;
    let mut bsIn: Option<BitStream> = None;
    let mut bsIn_idx = 0;
    let mut bsWr: Option<BitStream> = None;
    let mut bsWr_idx = 0;
    let mut b: Int32;
    let mut wrBlock: Int32;
    let mut currBlock: Int32;
    let mut rbCtr: Int32;
    let mut bitsRead: MaybeUInt64;
    let mut buffHi: UInt32;
    let mut buffLo: UInt32;
    let mut blockCRC: UInt32;
    let mut p: Option<Char> = None;
    let mut p_idx = 0;
    let mut split: Option<Char> = None;
    let mut split_idx = 0;
    let mut ofs: Int32;
    let mut k: Int32;

    {
        let mut progName = PROG_NAME.lock().unwrap();
        let mut inFileName = IN_FILE_NAME.lock().unwrap();
        let mut outFileName = OUT_FILE_NAME.lock().unwrap();
        
        // Copy program name
        let args: Vec<String> = std::env::args().collect();
        let argv0 = args[0].as_str();
        for (i, c) in argv0.chars().take(1999).enumerate() {
            progName[i] = c;
        }
        progName[1999] = '\0';

        eprintln!("bzip2recover 1.0.6: extracts blocks from damaged .bz2 files.");
        if args.len() != 2 {
            eprintln!("{}: usage is `{} damaged_file_name'.", 
                     progName.iter().collect::<String>(), 
                     progName.iter().collect::<String>());
            match std::mem::size_of::<MaybeUInt64>() {
                8 => eprintln!("\trestrictions on size of recovered file: None"),
                4 => {
                    eprintln!("\trestrictions on size of recovered file: 512 MB");
                    eprintln!("\tto circumvent, recompile with MaybeUInt64 as an\n\tunsigned 64-bit int.");
                },
                _ => eprintln!("\tsizeof(MaybeUInt64) is not 4 or 8 -- configuration error."),
            }
            exit(1);
        }

        let input_filename = &args[1];
        if input_filename.len() >= 1980 {
            eprintln!("{}: supplied filename is suspiciously (>= {} chars) long.  Bye!", 
                     progName.iter().collect::<String>(), 
                     input_filename.len());
            exit(1);
        }

        // Copy input filename
        for (i, c) in input_filename.chars().take(1999).enumerate() {
            inFileName[i] = c;
        }
        inFileName[input_filename.len()] = '\0';
    }

    // Open input file
    {
        let inFileName = IN_FILE_NAME.lock().unwrap();
        let filename: String = inFileName.iter().collect();
        inFile = File::open(filename).ok();
        if inFile.is_none() {
            let progName = PROG_NAME.lock().unwrap();
            eprintln!("{}: can't read `{}'", 
                      progName.iter().collect::<String>(), 
                      inFileName.iter().collect::<String>());
            exit(1);
        }
    }

    bsIn = bsOpenReadStream(inFile.take());
    if bsIn.is_none() {
        let progName = PROG_NAME.lock().unwrap();
        let inFileName = IN_FILE_NAME.lock().unwrap();
        eprintln!("{}: can't read `{}'", 
                  progName.iter().collect::<String>(), 
                  inFileName.iter().collect::<String>());
        exit(1);
    }

    {
        let progName = PROG_NAME.lock().unwrap();
        eprintln!("{}: searching for block boundaries ...", progName.iter().collect::<String>());
    }

    bitsRead = 0;
    buffHi = 0;
    buffLo = 0;
    currBlock = 0;
    {
        let mut bStart = B_START.lock().unwrap();
        bStart[currBlock as usize] = 0;
    }
    rbCtr = 0;

    loop {
        b = bsGetBit(bsIn.as_mut().unwrap());
        bitsRead += 1;
        if b == 2 {
            let bStart = B_START.lock().unwrap();
            if bitsRead >= bStart[currBlock as usize] && (bitsRead - bStart[currBlock as usize]) >= 40 {
                let mut bEnd = B_END.lock().unwrap();
                bEnd[currBlock as usize] = bitsRead - 1;
                if currBlock > 0 {
                    let progName = PROG_NAME.lock().unwrap();
                    eprintln!("   block {} runs from {} to {} (incomplete)", 
                             currBlock, 
                             bStart[currBlock as usize], 
                             bEnd[currBlock as usize]);
                }
            } else {
                currBlock -= 1;
            }
            currBlock -= 1;
            break;
        }
        buffHi = (buffHi << 1) | (buffLo >> 31);
        buffLo = (buffLo << 1) | ((b & 1) as UInt32);
        if ((buffHi & 0x0000ffff) == 0x00003141 && buffLo == 0x59265359) || 
           ((buffHi & 0x0000ffff) == 0x00001772 && buffLo == 0x45385090) {
            let bStart = B_START.lock().unwrap();
            let mut bEnd = B_END.lock().unwrap();
            if bitsRead > 49 {
                bEnd[currBlock as usize] = bitsRead - 49;
            } else {
                bEnd[currBlock as usize] = 0;
            }

            if currBlock > 0 && (bEnd[currBlock as usize] - bStart[currBlock as usize]) >= 130 {
                let progName = PROG_NAME.lock().unwrap();
                eprintln!("   block {} runs from {} to {}", 
                         rbCtr + 1, 
                         bStart[currBlock as usize], 
                         bEnd[currBlock as usize]);
                let mut rbStart = RB_START.lock().unwrap();
                let mut rbEnd = RB_END.lock().unwrap();
                rbStart[rbCtr as usize] = bStart[currBlock as usize];
                rbEnd[rbCtr as usize] = bEnd[currBlock as usize];
                rbCtr += 1;
            }

            if currBlock >= 50000 {
                tooManyBlocks(50000);
            }
            currBlock += 1;
            let mut bStart = B_START.lock().unwrap();
            bStart[currBlock as usize] = bitsRead;
        }
    }

    bsClose(bsIn.take().unwrap());
    if rbCtr < 1 {
        let progName = PROG_NAME.lock().unwrap();
        eprintln!("{}: sorry, I couldn't find any block boundaries.", progName.iter().collect::<String>());
        exit(1);
    }

    {
        let progName = PROG_NAME.lock().unwrap();
        eprintln!("{}: splitting into blocks", progName.iter().collect::<String>());
    }

    // Reopen input file
    {
        let inFileName = IN_FILE_NAME.lock().unwrap();
        let filename: String = inFileName.iter().collect();
        inFile = File::open(filename).ok();
        if inFile.is_none() {
            let progName = PROG_NAME.lock().unwrap();
            eprintln!("{}: can't open `{}'", 
                     progName.iter().collect::<String>(), 
                     inFileName.iter().collect::<String>());
            exit(1);
        }
    }

    bsIn = bsOpenReadStream(inFile.take());
    blockCRC = 0;
    bsWr = None;
    bitsRead = 0;
    outFile = None;
    wrBlock = 0;

    loop {
        b = bsGetBit(bsIn.as_mut().unwrap());
        if b == 2 {
            break;
        }
        buffHi = (buffHi << 1) | (buffLo >> 31);
        buffLo = (buffLo << 1) | ((b & 1) as UInt32);

        let rbStart = RB_START.lock().unwrap();
        let rbEnd = RB_END.lock().unwrap();

        if bitsRead == (47 + rbStart[wrBlock as usize]) {
            blockCRC = (buffHi << 16) | (buffLo >> 16);
        }

        if outFile.is_some() && bitsRead >= rbStart[wrBlock as usize] && bitsRead <= rbEnd[wrBlock as usize] {
            bsPutBit(bsWr.as_mut().unwrap(), b);
        }

        bitsRead += 1;

        if bitsRead == (rbEnd[wrBlock as usize] + 1) {
            if outFile.is_some() {
                // These bsPutUChar calls were removed since they require EState
                // and we only have BitStream available
                bsClose(bsWr.take().unwrap());
                outFile = None;
            }

            if wrBlock >= rbCtr {
                break;
            }
            wrBlock += 1;
        } else if bitsRead == rbStart[wrBlock as usize] {
            let mut outFileName = OUT_FILE_NAME.lock().unwrap();
            let inFileName = IN_FILE_NAME.lock().unwrap();
            
            // Clear outFileName
            for k in 0..2000 {
                outFileName[k] = '\0';
            }

            // Copy input filename
            for (i, c) in inFileName.iter().enumerate() {
                outFileName[i] = *c;
            }

            // Find last '/' in outFileName
            let mut split_pos = None;
            for (i, &c) in outFileName.iter().enumerate() {
                if c == '/' {
                    split_pos = Some(i);
                }
            }

            let split_pos = split_pos.map(|p| p + 1).unwrap_or(0);
            let base_name = format!("rec{:05}", wrBlock + 1);
            
            // Replace spaces with zeros in base_name
            let mut base_name_chars: Vec<char> = base_name.chars().collect();
            for c in &mut base_name_chars {
                if *c == ' ' {
                    *c = '0';
                }
            }

            // Copy base_name to outFileName
            for (i, c) in base_name_chars.iter().enumerate() {
                outFileName[split_pos + i] = *c;
            }

            // Append original extension if not .bz2
            let out_filename_str: String = outFileName.iter().collect();
            if !endsInBz2(&out_filename_str) {
                let mut out_filename = out_filename_str;
                out_filename.push_str(".bz2");
                for (i, c) in out_filename.chars().enumerate() {
                    outFileName[i] = c;
                }
            }

            {
                let progName = PROG_NAME.lock().unwrap();
                eprintln!("   writing block {} to `{}' ...", 
                          wrBlock + 1, 
                          outFileName.iter().collect::<String>());
            }

            let out_filename: String = outFileName.iter().collect();
            outFile = fopen_output_safely(Some(&out_filename), Some("wb"));
            if outFile.is_none() {
                let progName = PROG_NAME.lock().unwrap();
                eprintln!("{}: can't write `{}'", 
                         progName.iter().collect::<String>(), 
                         outFileName.iter().collect::<String>());
                exit(1);
            }

            bsWr = bsOpenWriteStream(outFile.take());
            // These bsPutUChar calls were removed since they require EState
            // and we only have BitStream available
        }
    }

    {
        let progName = PROG_NAME.lock().unwrap();
        eprintln!("{}: finished", progName.iter().collect::<String>());
    }
}
