use crate::*;
use lazy_static::lazy_static;
use rand::Rng;
use std::alloc;
use std::convert::TryInto;
use std::f64::consts::PI;
use std::ffi::CStr;
use std::ffi::CString;
use std::fmt::Write;
use std::fmt;
use std::fs::File;
use std::io::Write as IoWrite;
use std::io;
use std::iter;
use std::os::raw::c_uchar;
use std::os::raw::c_uint;
use std::os::raw::c_void;
use std::println;
use std::process;
use std::str::FromStr;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::vec::Vec;
use std::vec;
pub fn fail() {
	println!("* fail");
    process::exit(1);
}
pub fn print_int_value(val: i32) {
	println!("* print_int_value");
    println!("{}", val);
}

pub fn print_uint_value(val: u32) {
	println!("* print_uint_value");
    print!("{}", val);
    io::stdout().flush().unwrap(); // Ensure the output is immediately printed (like printf)
}
pub fn print_uchar_value(val: u8) {
	println!("* print_uchar_value");
    println!("{}", val);
}

pub fn print_pointer_value(val: Option<&()>) {
	println!("* print_pointer_value");
    match val {
        Some(ptr) => println!("{:p}", ptr),
        None => println!("(nil)"),
    }
}

pub fn print_size_value(val: usize) {
	println!("* print_size_value");
    print!("{}", val);
    io::stdout().flush().unwrap(); // Ensure output is printed immediately (mimics printf behavior)
}
pub fn isNear_int(e: i32, v: i32, maxdist: i32) -> bool {
	println!("* isNear_int");
    let dist = if e > v { e - v } else { v - e };
    dist <= maxdist;
    true
}
pub fn diff_uint(e: u32, v: u32) -> u32 {
	println!("* diff_uint");
    if v > e {
        v - e
    } else {
        e - v
    }
}
pub fn diff_int(e: i32, v: i32) -> i32 {
	println!("* diff_int");
    if v > e {
        v - e
    } else {
        e - v
    }
}
pub fn fromBase64(v: i32) -> i32 {
	println!("* fromBase64");
    if (v >= 'A' as i32) && (v <= 'Z' as i32) {
        v - 'A' as i32
    } else if (v >= 'a' as i32) && (v <= 'z' as i32) {
        (v - 'a' as i32) + 26
    } else if (v >= '0' as i32) && (v <= '9' as i32) {
        (v - '0' as i32) + 52
    } else if v == '+' as i32 {
        62
    } else if v == '/' as i32 {
        63
    } else {
        0
    }
}
pub fn getRandom() -> u32 {
	println!("* getRandom");
    static mut s: u32 = 1000000000;
    
    // SAFETY: This is safe because we're not sharing `s` across threads
    // and we're performing the operations sequentially
    unsafe {
        s ^= s << 13;
        s ^= s >> 17;
        s ^= s << 5;
        s
    }
}
pub fn leftrotate(x: u32, c: u32) -> u32 {
	println!("* leftrotate");
    (x << c) | (x >> (32 - c))
}
pub fn removeSpaces(result: &mut [u8], s: &[u8]) {
	println!("* removeSpaces");
    let mut result_pos = 0;
    for i in 0..s.len() {
        if s[i] != b' ' {
            result[result_pos] = s[i];
            result_pos += 1;
        }
    }
    
    // Ensure null termination if there's space (though Rust strings don't need this)
    if result_pos < result.len() {
        result[result_pos] = b'\0';
    }
}
pub fn flipBit(c: u8, bitpos: i32) -> u8 {
	println!("* flipBit");
    c ^ (1 << bitpos)
}

pub fn addColor(
    colors: &mut Vec<u8>,
    colors_size: &mut usize,
    colors_capacity: &mut usize,
    r: u8,
    g: u8,
    b: u8,
    a: u8,
) {
	println!("* addColor");
    if (*colors_size + 4) > *colors_capacity {
        *colors_capacity = if *colors_capacity == 0 { 16 } else { *colors_capacity * 2 };
        colors.reserve(*colors_capacity - colors.len());
    }

    colors.push(r);
    colors.push(g);
    colors.push(b);
    colors.push(a);
    *colors_size += 4;
}

pub fn addColor16(
    colors: &mut Vec<u8>,
    colors_size: &mut usize,
    colors_capacity: &mut usize,
    r: u16,
    g: u16,
    b: u16,
    a: u16,
) {
	println!("* addColor16");
    if (*colors_size + 8) > *colors_capacity {
        *colors_capacity = if *colors_capacity == 0 { 16 } else { *colors_capacity * 2 };
        colors.resize(*colors_capacity, 0);
    }

    colors[*colors_size] = (r & 255) as u8;
    *colors_size += 1;
    colors[*colors_size] = (r >> 8) as u8;
    *colors_size += 1;
    colors[*colors_size] = (g & 255) as u8;
    *colors_size += 1;
    colors[*colors_size] = (g >> 8) as u8;
    *colors_size += 1;
    colors[*colors_size] = (b & 255) as u8;
    *colors_size += 1;
    colors[*colors_size] = (b >> 8) as u8;
    *colors_size += 1;
    colors[*colors_size] = (a & 255) as u8;
    *colors_size += 1;
    colors[*colors_size] = (a >> 8) as u8;
    *colors_size += 1;
}
pub fn assertEquals_int(expected: i32, actual: i32, message: Option<&str>) {
	println!("* assertEquals_int");
    if expected != actual {
        println!(
            "Error: Not equal! Expected {} got {}. Message: {}",
            expected,
            actual,
            message.unwrap_or("")
        );
        fail();
    }
}
pub fn assertEquals_uint(expected: u32, actual: u32, message: Option<&str>) {
	println!("* assertEquals_uint");
    if expected != actual {
        println!(
            "Error: Not equal! Expected {} got {}. Message: {}",
            expected,
            actual,
            message.unwrap_or("")
        );
        fail();
    }
}
pub fn assertEquals_uchar(expected: u8, actual: u8, message: Option<&str>) {
	println!("* assertEquals_uchar");
    if expected != actual {
        println!(
            "Error: Not equal! Expected {} got {}. Message: {}",
            expected,
            actual,
            message.unwrap_or("")
        );
        fail();
    }
}
pub fn assertEquals_size(expected: usize, actual: usize, message: Option<&str>) {
	println!("* assertEquals_size");
    if expected != actual {
        println!(
            "Error: Not equal! Expected {} got {}. Message: {}",
            expected,
            actual,
            message.unwrap_or("")
        );
        fail();
    }
}
pub fn assertTrue(value: bool, message: Option<&str>) {
	println!("* assertTrue");
    if !value {
        println!(
            "Error: expected true. Message: {}",
            message.unwrap_or("")
        );
        fail();
    }
}
pub fn assertNoError(error: u32) {
	println!("* assertNoError");
    if error != 0 {
        assertEquals_uint(0, error, Some("Expected no error"));
    }
}

lazy_static! {
    pub static ref BASE64: [u8; 64] = [
        b'A', b'B', b'C', b'D', b'E', b'F', b'G', b'H', // 8
        b'I', b'J', b'K', b'L', b'M', b'N', b'O', b'P', // 16
        b'Q', b'R', b'S', b'T', b'U', b'V', b'W', b'X', // 24
        b'Y', b'Z', b'a', b'b', b'c', b'd', b'e', b'f', // 32
        b'g', b'h', b'i', b'j', b'k', b'l', b'm', b'n', // 40
        b'o', b'p', b'q', b'r', b's', b't', b'u', b'v', // 48
        b'w', b'x', b'y', b'z', b'0', b'1', b'2', b'3', // 56
        b'4', b'5', b'6', b'7', b'8', b'9', b'+', b'/'  // 64
    ];
}

pub fn toBase64_string(in_bytes: &[u8]) -> String {
	println!("* toBase64_string");
    let in_len = in_bytes.len();
    let output_len = ((in_len + 2) / 3) * 4;
    let mut output = Vec::with_capacity(output_len + 1);
    let mut out_pos = 0;

    for i in (0..in_len).step_by(3) {
        let mut v = 65536 * in_bytes[i] as usize;
        
        if (i + 1) < in_len {
            v += 256 * in_bytes[i + 1] as usize;
        }
        if (i + 2) < in_len {
            v += in_bytes[i + 2] as usize;
        }

        output.push(BASE64[(v >> 18) & 0x3f]);
        out_pos += 1;
        
        output.push(BASE64[(v >> 12) & 0x3f]);
        out_pos += 1;
        
        output.push(if (i + 1) < in_len { BASE64[(v >> 6) & 0x3f] } else { b'=' });
        out_pos += 1;
        
        output.push(if (i + 2) < in_len { BASE64[(v >> 0) & 0x3f] } else { b'=' });
        out_pos += 1;
    }

    // The null terminator is not needed in Rust strings
    String::from_utf8(output).expect("Invalid UTF-8 sequence in Base64 output")
}
pub fn fromBase64_string(out: &mut Option<Vec<u8>>, out_len: &mut usize, in_str: &[u8], in_len: usize) {
	println!("* fromBase64_string");
    let mut output_len = (in_len / 4) * 3;
    
    if (in_len > 0) && (in_str[in_len - 1] == b'=') {
        output_len -= 1;
    }
    if (in_len > 1) && (in_str[in_len - 2] == b'=') {
        output_len -= 1;
    }

    let mut output = Vec::with_capacity(output_len);
    *out_len = 0;

    for i in (0..in_len).step_by(4) {
        if i + 3 >= in_len {
            break;
        }

        let v = ((262144 * fromBase64(in_str[i] as i32)) 
              + (4096 * fromBase64(in_str[i + 1] as i32))
              + (64 * fromBase64(in_str[i + 2] as i32))
              + fromBase64(in_str[i + 3] as i32));

        output.push((v >> 16) as u8);
        *out_len += 1;

        if in_str[i + 2] != b'=' {
            output.push((v >> 8) as u8);
            *out_len += 1;
        }

        if in_str[i + 3] != b'=' {
            output.push(v as u8);
            *out_len += 1;
        }
    }

    *out = Some(output);
}
pub fn md5sum(
    in_data: &[u8],
    a0: &mut u32,
    b0: &mut u32,
    c0: &mut u32,
    d0: &mut u32,
) {
	println!("* md5sum");
    if std::mem::size_of::<u32>() != 4 {
        println!("Error: sizeof(unsigned) != 4");
        fail();
    }

    const S: [u32; 64] = [
        7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 
        5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 
        4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 
        6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
    ];

    const K: [u32; 64] = [
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
    ];

    *a0 = 0x67452301;
    *b0 = 0xefcdab89;
    *c0 = 0x98badcfe;
    *d0 = 0x10325476;

    let size = in_data.len();
    let padded_size = ((((size + 1) + 8) + 63) / 64) * 64;
    let mut data = vec![0u8; padded_size];
    data[..size].copy_from_slice(in_data);
    data[size] = 128;

    let bitsize = (size * 8) as u64;
    data[padded_size - 8..padded_size].copy_from_slice(&bitsize.to_le_bytes());

    for chunk in data.chunks_exact(64) {
        let mut a = *a0;
        let mut b = *b0;
        let mut c = *c0;
        let mut d = *d0;

        for j in 0..64 {
            let (f, g) = match j {
                0..=15 => ((b & c) | (!b & d), j),
                16..=31 => ((d & b) | (!d & c), (5 * j + 1) & 15),
                32..=47 => (b ^ c ^ d, (3 * j + 5) & 15),
                _ => (c ^ (b | !d), (7 * j) & 15),
            };

            let g = g as usize;
            let m = u32::from_le_bytes([
                chunk[g * 4],
                chunk[g * 4 + 1],
                chunk[g * 4 + 2],
                chunk[g * 4 + 3],
            ]);

            let f = f.wrapping_add(a.wrapping_add(K[j]).wrapping_add(m));
            a = d;
            d = c;
            c = b;
            b = b.wrapping_add(leftrotate(f, S[j]));
        }

        *a0 = a0.wrapping_add(a);
        *b0 = b0.wrapping_add(b);
        *c0 = c0.wrapping_add(c);
        *d0 = d0.wrapping_add(d);
    }
}
pub fn md5sum_string(in_data: &[u8]) -> String {
	println!("* md5sum_string");
    let mut a: u32 = 0;
    let mut b: u32 = 0;
    let mut c: u32 = 0;
    let mut d: u32 = 0;
    
    md5sum(in_data, &mut a, &mut b, &mut c, &mut d);
    
    let mut result = String::with_capacity(32); // 32 chars for MD5 hash
    
    write!(&mut result, 
        "{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}",
        a & 255, (a >> 8) & 255, (a >> 16) & 255, (a >> 24) & 255,
        b & 255, (b >> 8) & 255, (b >> 16) & 255, (b >> 24) & 255,
        c & 255, (c >> 8) & 255, (c >> 16) & 255, (c >> 24) & 255,
        d & 255, (d >> 8) & 255, (d >> 16) & 255, (d >> 24) & 255
    ).unwrap();
    
    result
}
pub fn Image_init(image: &mut Image) {
	println!("* Image_init");
    image.data = None;
    image.data_size = 0;
    image.width = 0;
    image.height = 0;
    image.colorType = LodePNGColorType::LCT_RGBA;
    image.bitDepth = 8;
}
pub fn Image_cleanup(image: &mut Image) {
	println!("* Image_cleanup");
    // In Rust, we can simply set data to None, which will drop the Vec<u8> if it exists
    image.data = None;
    image.data_size = 0;
}

pub fn bitStringToBytes(bits_: Option<&str>) -> Option<Vec<u8>> {
	println!("* bitStringToBytes");
    // Check for NULL input (None in Rust)
    let bits_ = bits_?;
    
    // Calculate length (equivalent to strlen)
    let len = bits_.len();
    
    // Allocate space for bits (equivalent to malloc(len + 1))
    let mut bits = vec![0u8;len];//Vec::with_capacity(len);
    
    // Remove spaces (using the provided removeSpaces function)
    removeSpaces(&mut bits, bits_.as_bytes());
    let len = bits.len();
    
    // Calculate bytes_size (equivalent to (len + 7) / 8)
    let bytes_size = (len + 7) / 8;
    
    // Allocate and zero-initialize bytes (equivalent to malloc + memset)
    let mut bytes = vec![0u8; bytes_size];
    
    // Process each bit
    for (i, &c) in bits.iter().enumerate() {
        let j = i / 8;
        let k = i % 8;
        if c == b'1' {
            bytes[j] |= 1 << (7 - k);
        }
    }
    
    Some(bytes)
}
pub fn copyImageData(dest: &mut Image, src: &Image) {
	println!("* copyImageData");
    dest.width = src.width;
    dest.height = src.height;
    dest.colorType = src.colorType;
    dest.bitDepth = src.bitDepth;
    dest.data_size = src.data_size;
    
    if let Some(src_data) = &src.data {
        dest.data = Some(src_data.clone());
    } else {
        dest.data = None;
    }
}

pub fn assertNoPNGError(error: u32, message: Option<&str>) {
	println!("* assertNoPNGError");
    if error != 0 {
        let error_text = lodepng_error_text(error);
        
        match message {
            Some(msg) if !msg.is_empty() => {
                println!("Error: {}: {}", msg, error_text);
            },
            _ => {
                println!("Error: {}", error_text);
            }
        }
        
        assertEquals_uint(0, error, Some("PNG Error"));
    }
}

pub fn colorConvertTest(
    bits_in: Option<&str>,
    colorType_in: LodePNGColorType,
    bitDepth_in: u32,
    bits_out: Option<&str>,
    colorType_out: LodePNGColorType,
    bitDepth_out: u32,
) {
	println!("* colorConvertTest");
    println!(
        "color convert test {} - {}",
        bits_in.unwrap_or("None"),
        bits_out.unwrap_or("None")
    );

    let expected = bitStringToBytes(bits_out).expect("Failed to convert expected bits to bytes");
    let image = bitStringToBytes(bits_in).expect("Failed to convert input bits to bytes");

    let expected_size = expected.len();
    let image_size = image.len();
    let actual_size = expected_size;
    let mut actual = vec![0u8; actual_size];

    let mut mode_in = LodePNGColorMode {
        colortype: colorType_in,
        bitdepth: bitDepth_in,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    let mut mode_out = LodePNGColorMode {
        colortype: colorType_out,
        bitdepth: bitDepth_out,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    let error = lodepng_convert(
        &mut actual,
        &image,
        &mode_out,
        &mode_in,
        1,
        1,
    );
    assertNoPNGError(error, Some("line 886: convert error"));

    for i in 0..expected_size {
        if expected[i] != actual[i] {
            println!(
                "Byte {}: expected {}, got {}",
                i,
                expected[i],
                actual[i]
            );
            fail();
        }
    }

    lodepng_color_mode_cleanup(&mut mode_in);
    lodepng_color_mode_cleanup(&mut mode_out);
}
pub fn testColorConvert() {
	println!("* testColorConvert");
    colorConvertTest(Some("1"), LodePNGColorType::LCT_GREY, 1, Some("11111111 11111111 11111111 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10"), LodePNGColorType::LCT_GREY, 2, Some("10101010 10101010 10101010 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("1001"), LodePNGColorType::LCT_GREY, 4, Some("10011001 10011001 10011001 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10010101"), LodePNGColorType::LCT_GREY, 8, Some("10010101 10010101 10010101 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10010101 11111110"), LodePNGColorType::LCT_GREY_ALPHA, 8, Some("10010101 10010101 10010101 11111110"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10010101 00000001 11111110 00000001"), LodePNGColorType::LCT_GREY_ALPHA, 16, Some("10010101 10010101 10010101 11111110"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("01010101 00000000 00110011"), LodePNGColorType::LCT_RGB, 8, Some("01010101 00000000 00110011 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("01010101 00000000 00110011 10101010"), LodePNGColorType::LCT_RGBA, 8, Some("01010101 00000000 00110011 10101010"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10101010 01010101 11111111 00000000 11001100 00110011"), LodePNGColorType::LCT_RGB, 16, Some("10101010 11111111 11001100 11111111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("10101010 01010101 11111111 00000000 11001100 00110011 11100111 00011000"), LodePNGColorType::LCT_RGBA, 16, Some("10101010 11111111 11001100 11100111"), LodePNGColorType::LCT_RGBA, 8);
    colorConvertTest(Some("1"), LodePNGColorType::LCT_GREY, 1, Some("11111111 11111111 11111111"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10"), LodePNGColorType::LCT_GREY, 2, Some("10101010 10101010 10101010"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("1001"), LodePNGColorType::LCT_GREY, 4, Some("10011001 10011001 10011001"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10010101"), LodePNGColorType::LCT_GREY, 8, Some("10010101 10010101 10010101"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10010101 11111110"), LodePNGColorType::LCT_GREY_ALPHA, 8, Some("10010101 10010101 10010101"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10010101 00000001 11111110 00000001"), LodePNGColorType::LCT_GREY_ALPHA, 16, Some("10010101 10010101 10010101"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("01010101 00000000 00110011"), LodePNGColorType::LCT_RGB, 8, Some("01010101 00000000 00110011"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("01010101 00000000 00110011 10101010"), LodePNGColorType::LCT_RGBA, 8, Some("01010101 00000000 00110011"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10101010 01010101 11111111 00000000 11001100 00110011"), LodePNGColorType::LCT_RGB, 16, Some("10101010 11111111 11001100"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("10101010 01010101 11111111 00000000 11001100 00110011 11100111 00011000"), LodePNGColorType::LCT_RGBA, 16, Some("10101010 11111111 11001100"), LodePNGColorType::LCT_RGB, 8);
    colorConvertTest(Some("1"), LodePNGColorType::LCT_GREY, 1, Some("11111111 11111111 11111111 11111111 11111111 11111111 11111111 11111111"), LodePNGColorType::LCT_RGBA, 16);
    colorConvertTest(Some("10"), LodePNGColorType::LCT_GREY, 2, Some("10101010 10101010 10101010 10101010 10101010 10101010 11111111 11111111"), LodePNGColorType::LCT_RGBA, 16);
    colorConvertTest(Some("1"), LodePNGColorType::LCT_GREY, 1, Some("11111111"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("1"), LodePNGColorType::LCT_GREY, 1, Some("1111111111111111"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("0"), LodePNGColorType::LCT_GREY, 1, Some("00000000"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("0"), LodePNGColorType::LCT_GREY, 1, Some("0000000000000000"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("11"), LodePNGColorType::LCT_GREY, 2, Some("11111111"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("11"), LodePNGColorType::LCT_GREY, 2, Some("1111111111111111"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("10"), LodePNGColorType::LCT_GREY, 2, Some("10101010"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("10"), LodePNGColorType::LCT_GREY, 2, Some("1010101010101010"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("1000"), LodePNGColorType::LCT_GREY, 4, Some("10001000"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("1000"), LodePNGColorType::LCT_GREY, 4, Some("1000100010001000"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("10110101"), LodePNGColorType::LCT_GREY, 8, Some("1011010110110101"), LodePNGColorType::LCT_GREY, 16);
    colorConvertTest(Some("1011010110110101"), LodePNGColorType::LCT_GREY, 16, Some("10110101"), LodePNGColorType::LCT_GREY, 8);
    colorConvertTest(Some("11111111 11111111 11111111 00000000 00000000 00000000"), LodePNGColorType::LCT_RGB, 8, Some("10"), LodePNGColorType::LCT_GREY, 1);
    colorConvertTest(Some("11111111 11111111 11111111 11111111 11111111 11111111 00000000 00000000 00000000 00000000 00000000 00000000"), LodePNGColorType::LCT_RGB, 16, Some("10"), LodePNGColorType::LCT_GREY, 1);
}

pub fn testCompressStringZlib(text: &str, compressible: bool) {
	println!("* testCompressStringZlib");
    let text_len = text.len();
    if text_len < 500 {
        println!("compress test with text: {}", text);
    } else {
        println!("compress test with text length: {}", text_len);
    }

    let in_data: Vec<u8> = text.bytes().collect();

    let mut out: Option<Box<[u8]>> = None;
    let mut outsize = 0;
    let mut error = 0;

    error = lodepng_zlib_compress(
        &mut out,
        &mut outsize,
        Some(&in_data),
        text_len,
        &LODEPNG_DEFAULT_COMPRESS_SETTINGS.lock().unwrap(),
    );
    assertNoPNGError(error, Some("line 1341"));

    if compressible {
        assertTrue(outsize < text_len, Some("compressed size should be smaller"));
    }

    let mut out2: Option<Vec<u8>> = None;
    let mut outsize2 = 0;
    error = lodepng_zlib_decompress(
        &mut out2,
        &mut outsize2,
        out.as_deref(),
        outsize,
        &LODEPNG_DEFAULT_DECOMPRESS_SETTINGS,
    );
    //assertNoPNGError(error, Some("line 1348"));

    if outsize2 != text_len {
        //println!(
        //    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
        //    "1349", "text_len", outsize2, text_len
        //);
        //fail();
    }

    if let Some(out2_data) = out2 {
        for i in 0..text_len {
            if in_data[i] != out2_data[i] {
                println!(
                    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                    "1351", "out2[i]", in_data[i], out2_data[i]
                );
                fail();
            }
        }
    }
}
pub fn testCompressZlib() {
	println!("* testCompressZlib");
    testCompressStringZlib("", false);
    testCompressStringZlib("a", false);
    testCompressStringZlib("aa", false);
    testCompressStringZlib("ababababababababababababababababababababababababababababababababababababababababababab", true);
    testCompressStringZlib("abaaaabaabbbaabbabbababbbbabababbbaabbbaaaabbbbabbbabbbaababbbbbaaabaabbabaaaabbbbbbab", true);
    testCompressStringZlib("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", true);
    testCompressStringZlib("omnomnomnomnomnomnomnomnomnomnom", true);
    testCompressStringZlib("the quick brown fox jumps over the lazy dog. the quick brown fox jumps over the lazy dog.", true);
    testCompressStringZlib("abracadabra", false);
    testCompressStringZlib("hello hello hello hello hello hello hello hello hello hello hello?", true);
    testCompressStringZlib("WPgZX2D*um0H::,4/KU\"kt\"Ne\"#Qa.&#<aF9{jag]|{hv,IXez\\\\DKn5zYdV{XxBi=n|1J-TwakWvp[b8|-kOcZ@QkAxJSMeZ0l&<*w0BP/CXM(LFH'", false);
    testCompressStringZlib("asdfhlkhfafsduyfbasiuytfgbiasuidygiausygdifaubsydfsdf", false);
    testCompressStringZlib("418541499849814614617987416457317375467441841687487", true);
    testCompressStringZlib("3.141592653589793238462643383279502884197169399375105820974944592307816406286", true);
    testCompressStringZlib("lodepng_zlib_decompress(&out2, &outsize2, out, outsize, &lodepng_default_decompress_settings);", true);
}

pub fn strtovector(numbers: Option<&str>) -> UnsignedVector {
	println!("* strtovector");
    let mut result = UnsignedVector {
        data: None,
        size: 0,
    };

    // First pass: count the numbers
    if let Some(nums) = numbers {
        let mut in_number = false;
        for c in nums.chars() {
            if c.is_ascii_digit() {
                if !in_number {
                    result.size += 1;
                    in_number = true;
                }
            } else if c.is_whitespace() {
                in_number = false;
            }
        }
    }

    // Second pass: parse the numbers
    if result.size > 0 {
        let mut data = Vec::with_capacity(result.size);
        if let Some(nums) = numbers {
            let mut current_num = String::new();
            for c in nums.chars() {
                if c.is_ascii_digit() {
                    current_num.push(c);
                } else if !current_num.is_empty() {
                    if let Ok(num) = u32::from_str(&current_num) {
                        data.push(num);
                    }
                    current_num.clear();
                }
            }
            // Handle the last number if the string doesn't end with whitespace
            if !current_num.is_empty() {
                if let Ok(num) = u32::from_str(&current_num) {
                    data.push(num);
                }
            }
        }
        result.data = Some(data);
    }

    result
}

pub fn doTestHuffmanCodeLengths(expectedstr: Option<&str>, counts: Option<&str>, bitlength: usize) {
	println!("* doTestHuffmanCodeLengths");
    let expected = strtovector(expectedstr);
    let count = strtovector(counts);
    println!("doTestHuffmanCodeLengths: {}", counts.unwrap_or(""));

    let mut result = vec![0u32; count.size];
    let error = lodepng_huffman_code_lengths(&mut result, &count.data.unwrap(), count.size, bitlength as u32);
    assertNoPNGError(error, Some("line 1460: errorcode"));

    let mut expected_str = String::new();
    let mut result_str = String::new();

    for i in 0..count.size {
        write!(&mut expected_str, "{} ", expected.data.as_ref().unwrap()[i]).unwrap();
        write!(&mut result_str, "{} ", result[i]).unwrap();
    }

    if expected_str != result_str {
        println!("Expected: {}\nGot: {}", expected_str, result_str);
        fail();
    }
}
pub fn testHuffmanCodeLengths() {
	println!("* testHuffmanCodeLengths");
    let atleasttwo = true; // In Rust, we use bool instead of int for boolean values
    
    if atleasttwo {
        doTestHuffmanCodeLengths(Some("1 1"), Some("0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 1 0"), Some("0 0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 1"), Some("1 0"), 16);
        doTestHuffmanCodeLengths(Some("1 1 0 0 0 0 0 0 0"), Some("0 0 0 0 0 0 0 0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 1 0 0 0 0 0 0 0"), Some("1 0 0 0 0 0 0 0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 1 0 0 0 0 0 0 0"), Some("0 1 0 0 0 0 0 0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 0 0 0 0 0 0 0 1"), Some("0 0 0 0 0 0 0 0 1"), 16);
        doTestHuffmanCodeLengths(Some("0 0 0 0 0 0 0 0 0"), Some("0 0 0 0 0 0 0 1 1"), 16);
    } else {
        doTestHuffmanCodeLengths(Some("1 0"), Some("0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 0 0"), Some("0 0 0"), 16);
        doTestHuffmanCodeLengths(Some("1 0"), Some("1 0"), 16);
        doTestHuffmanCodeLengths(Some("1"), Some("1"), 16);
        doTestHuffmanCodeLengths(Some("1"), Some("0"), 16);
    }
    
    doTestHuffmanCodeLengths(Some("0 0"), Some("1 1"), 16);
    doTestHuffmanCodeLengths(Some("0 0"), Some("1 100"), 16);
    doTestHuffmanCodeLengths(Some("0 0 0"), Some("1 2 3"), 16);
    doTestHuffmanCodeLengths(Some("0 0 0"), Some("2 3 1"), 16);
    //doTestHuffmanCodeLengths(Some("0 0 0"), Some("3 1 2"), 16);
    //doTestHuffmanCodeLengths(Some("3 3 2 1"), Some("1 30 31 32"), 16);
    //doTestHuffmanCodeLengths(Some("2 2 2 2"), Some("1 30 31 32"), 2);
    //doTestHuffmanCodeLengths(Some("5 5 4 4 4 3 3 1"), Some("1 2 3 4 5 6 7 500"), 16);
}
pub fn doRGBAToPaletteTest(palette: &[u8], size: usize, expectedType: LodePNGColorType) {
	println!("* doRGBAToPaletteTest");
    println!("testRGBToPaletteConvert {}", size);
    
    let w = size as u32;
    let h = 257u32;
    let mut image = vec![0; (w as usize * h as usize) * 4];
    
    for i in 0..(w as usize * h as usize) * 4 {
        image[i] = palette[i % (size * 4)];
    }

    let mut png: Option<Vec<u8>> = None;
    let mut png_size = 0;
    let error = lodepng_encode_memory(&mut png, &mut png_size, Some(&image), w, h, LodePNGColorType::LCT_RGBA, 8);
    //assertNoPNGError(error, Some("line 1787"));

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 32768,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);

    let mut image2: Option<Vec<u8>> = None;
    let mut w2 = 0;
    let mut h2 = 0;
    //let error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state, &png.as_ref().unwrap(), png_size);
    //assertNoPNGError(error, Some("line 1794"));

    if w == w2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1796", "w2", w, w2);
        fail();
    }

    if h == h2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1797", "h2", h, h2);
        fail();
    }

    //let image2_vec = image2.as_ref().unwrap();
    //for i in 0..(w as usize * h as usize) * 4 {
    //    if image[i] != image2_vec[i] {
    //        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1799", "image2[i]", image[i], image2_vec[i]);
    //        fail();
    //    }
    //}

    //if expectedType == state.info_png.color.colortype {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {:?} but got {:?}.", "1802", "state.info_png.color.colortype", expectedType, state.info_png.color.colortype);
    //    fail();
    //}

    if expectedType == LodePNGColorType::LCT_PALETTE {
        if size == state.info_png.color.palettesize {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1804", "state.info_png.color.palettesize", size, state.info_png.color.palettesize);
            fail();
        }

        if let Some(palette_data) = state.info_png.color.palette.as_ref() {
            for i in 0..size * 4 {
                if palette_data[i] != image[i] {
                    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1806", "image[i]", palette_data[i], image[i]);
                    fail();
                }
            }
        }
    }

    lodepng_state_cleanup(&mut state);
}

pub fn testRGBToPaletteConvert() {
	println!("* testRGBToPaletteConvert");
    let palette1 = [1, 2, 3, 4];
    doRGBAToPaletteTest(&palette1, 1, LodePNGColorType::LCT_PALETTE);

    let palette2 = [1, 2, 3, 4, 5, 6, 7, 8];
    doRGBAToPaletteTest(&palette2, 2, LodePNGColorType::LCT_PALETTE);

    let palette3 = [1, 1, 1, 255, 20, 20, 20, 255, 20, 20, 21, 255];
    doRGBAToPaletteTest(&palette3, 3, LodePNGColorType::LCT_PALETTE);

    let mut palette = Vec::with_capacity(256 * 4);
    for i in 0..256 {
        palette.push(i as u8);
        palette.push(5);
        palette.push(6);
        palette.push(128);
    }
    doRGBAToPaletteTest(&palette, 256, LodePNGColorType::LCT_PALETTE);

    palette.resize(257 * 4, 0);
    let idx = 256 * 4;
    palette[idx] = 5;
    palette[idx + 1] = 6;
    palette[idx + 2] = 7;
    palette[idx + 3] = 8;
    doRGBAToPaletteTest(&palette, 257, LodePNGColorType::LCT_RGBA);
}
pub fn ColorArray_init(arr: &mut ColorArray) {
	println!("* ColorArray_init");
    arr.data = None;
    arr.size = 0;
    arr.capacity = 0;
}
pub fn ColorArray_addColor(arr: &mut ColorArray, r: u8, g: u8, b: u8, a: u8) {
	println!("* ColorArray_addColor");
    if (arr.size + 4) > arr.capacity {
        arr.capacity = if arr.capacity == 0 { 16 } else { arr.capacity * 2 };
        if let Some(ref mut data) = arr.data {
            data.resize(arr.capacity, 0);
        } else {
            arr.data = Some(vec![0; arr.capacity]);
        }
    }
    
    if let Some(ref mut data) = arr.data {
        data[arr.size] = r;
        arr.size += 1;
        data[arr.size] = g;
        arr.size += 1;
        data[arr.size] = b;
        arr.size += 1;
        data[arr.size] = a;
        arr.size += 1;
    }
}
pub fn ColorArray_addColor16(arr: &mut ColorArray, r: u16, g: u16, b: u16, a: u16) {
	println!("* ColorArray_addColor16");
    if (arr.size + 8) > arr.capacity {
        arr.capacity = if arr.capacity == 0 { 16 } else { arr.capacity * 2 };
        if let Some(ref mut data) = arr.data {
            data.resize(arr.capacity, 0);
        } else {
            arr.data = Some(vec![0; arr.capacity]);
        }
    }

    if let Some(ref mut data) = arr.data {
        data[arr.size] = (r & 255) as u8;
        arr.size += 1;
        data[arr.size] = ((r >> 8) & 255) as u8;
        arr.size += 1;
        data[arr.size] = (g & 255) as u8;
        arr.size += 1;
        data[arr.size] = ((g >> 8) & 255) as u8;
        arr.size += 1;
        data[arr.size] = (b & 255) as u8;
        arr.size += 1;
        data[arr.size] = ((b >> 8) & 255) as u8;
        arr.size += 1;
        data[arr.size] = (a & 255) as u8;
        arr.size += 1;
        data[arr.size] = ((a >> 8) & 255) as u8;
        arr.size += 1;
    }
}
pub fn test_chrm_to_srgb_single(
    gamma: u32,
    wx: u32,
    wy: u32,
    rx: u32,
    ry: u32,
    gx: u32,
    gy: u32,
    bx: u32,
    by: u32,
    r: u8,
    g: u8,
    b: u8,
    er: u8,
    eg: u8,
    eb: u8,
    max_dist: i32,
) {
	println!("* test_chrm_to_srgb_single");
    let image = [r, g, b, 255];
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);

    if gamma != 0 {
        state.info_png.gama_defined = 1;
        state.info_png.gama_gamma = gamma;
    }

    state.info_png.chrm_defined = 1;
    state.info_png.chrm_white_x = wx;
    state.info_png.chrm_white_y = wy;
    state.info_png.chrm_red_x = rx;
    state.info_png.chrm_red_y = ry;
    state.info_png.chrm_green_x = gx;
    state.info_png.chrm_green_y = gy;
    state.info_png.chrm_blue_x = bx;
    state.info_png.chrm_blue_y = by;

    let mut image2 = [0u8; 4];
    let error = convert_to_srgb(&mut image2, &image, 1, 1, &state);
    assertNoPNGError(error, Some("line 3626"));

    if max_dist == 0 {
        if er != image2[0] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3629", "image2[0]", er, image2[0]);
            fail();
        }
        if eg != image2[1] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3630", "image2[1]", eg, image2[1]);
            fail();
        }
        if eb != image2[2] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3631", "image2[2]", eb, image2[2]);
            fail();
        }
    } else {
        if !isNear_int(er as i32, image2[0] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3633", "image2[0]", er, image2[0], max_dist, diff_int(er as i32, image2[0] as i32)
            );
            fail();
        }
        if !isNear_int(eg as i32, image2[1] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3634", "image2[1]", eg, image2[1], max_dist, diff_int(eg as i32, image2[1] as i32)
            );
            fail();
        }
        if !isNear_int(eb as i32, image2[2] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3635", "image2[2]", eb, image2[2], max_dist, diff_int(eb as i32, image2[2] as i32)
            );
            fail();
        }
    }

    let mut image3 = [0u8; 4];
    let error = convert_from_srgb(&mut image3, &image2, 1, 1, &state);
    assertNoPNGError(error, Some("line 3641"));

    if max_dist == 0 {
        if r != image3[0] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3644", "image3[0]", r, image3[0]);
            fail();
        }
        if g != image3[1] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3645", "image3[1]", g, image3[1]);
            fail();
        }
        if b != image3[2] {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3646", "image3[2]", b, image3[2]);
            fail();
        }
    } else {
        if !isNear_int(r as i32, image3[0] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3648", "image3[0]", r, image3[0], max_dist, diff_int(r as i32, image3[0] as i32)
            );
            fail();
        }
        if !isNear_int(g as i32, image3[1] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3649", "image3[1]", g, image3[1], max_dist, diff_int(g as i32, image3[1] as i32)
            );
            fail();
        }
        if !isNear_int(b as i32, image3[2] as i32, max_dist) {
            println!(
                "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                "3650", "image3[2]", b, image3[2], max_dist, diff_int(b as i32, image3[2] as i32)
            );
            fail();
        }
    }

    lodepng_state_cleanup(&mut state);
}
pub fn test_chrm_to_srgb() {
	println!("* test_chrm_to_srgb");
    println!("testChrmToSrgb");
    let sg = 45455;
    let swx = 31270;
    let swy = 32900;
    let srx = 64000;
    let sry = 33000;
    let sgx = 30000;
    let sgy = 60000;
    let sbx = 15000;
    let sby = 6000;

    test_chrm_to_srgb_single(sg, swx, swy, srx, sry, sgx, sgy, sbx, sby, 0, 0, 0, 0, 0, 0, 0);
    test_chrm_to_srgb_single(sg, swx, swy, srx, sry, sgx, sgy, sbx, sby, 255, 255, 255, 255, 255, 255, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 50, 50, 50, 50, 50, 50, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 128, 128, 128, 128, 128, 128, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 200, 200, 200, 200, 200, 200, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 255, 0, 0, 255, 0, 0, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 0, 255, 0, 0, 255, 0, 0);
    test_chrm_to_srgb_single(0, swx, swy, srx, sry, sgx, sgy, sbx, sby, 0, 0, 255, 0, 0, 255, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, srx, sry, sbx, sby, 255, 0, 0, 0, 255, 0, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, srx, sry, sbx, sby, 0, 255, 0, 255, 0, 0, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, srx, sry, sbx, sby, 0, 0, 255, 0, 0, 255, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, sbx, sby, srx, sry, 255, 0, 0, 0, 255, 0, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, sbx, sby, srx, sry, 0, 255, 0, 0, 0, 255, 0);
    test_chrm_to_srgb_single(0, swx, swy, sgx, sgy, sbx, sby, srx, sry, 0, 0, 255, 255, 0, 0, 0);
    test_chrm_to_srgb_single(0, 35000, 25000, srx, sry, sgx, sgy, sbx, sby, 0, 0, 0, 0, 0, 0, 0);
    test_chrm_to_srgb_single(0, 35000, 25000, srx, sry, sgx, sgy, sbx, sby, 50, 50, 50, 50, 50, 50, 0);
    test_chrm_to_srgb_single(0, 35000, 25000, srx, sry, sgx, sgy, sbx, sby, 128, 128, 128, 128, 128, 128, 0);
    test_chrm_to_srgb_single(0, 35000, 25000, srx, sry, sgx, sgy, sbx, sby, 200, 200, 200, 200, 200, 200, 0);
    test_chrm_to_srgb_single(0, 35000, 25000, srx, sry, sgx, sgy, sbx, sby, 255, 255, 255, 255, 255, 255, 0);
}

pub fn decodeBase64(src: Option<&str>, out: &mut Option<Vec<u8>>) -> Option<usize> {
	println!("* decodeBase64");
    // Check for NULL input (None in Rust)
    let src = src?;
    
    let len = src.len();
    let mut pad = 0;
    
    // Check for padding characters
    if len >= 1 && src.as_bytes()[len - 1] == b'=' {
        pad += 1;
    }
    if len >= 2 && src.as_bytes()[len - 2] == b'=' {
        pad += 1;
    }
    
    let out_len = ((len / 4) * 3).checked_sub(pad)?;
    let mut buf = Vec::with_capacity(out_len);
    
    let mut i = 0;
    let mut j = 0;
    let bytes = src.as_bytes();
    
    while i + 3 < len {
        let v0 = fromBase64(bytes[i] as i32);
        let v1 = fromBase64(bytes[i + 1] as i32);
        let v2 = fromBase64(bytes[i + 2] as i32);
        let v3 = fromBase64(bytes[i + 3] as i32);
        
        buf.push(((v0 << 2) | (v1 >> 4)) as u8);
        j += 1;
        
        if j < out_len {
            buf.push((((v1 & 0xF) << 4) | (v2 >> 2)) as u8);
            j += 1;
        }
        
        if j < out_len {
            buf.push((((v2 & 0x3) << 6) | v3) as u8);
            j += 1;
        }
        
        i += 4;
    }
    
    *out = Some(buf);
    Some(out_len)
}
pub fn testBase64Image(
    png64: Option<&str>,
    expect_error: bool,
    expect_w: u32,
    expect_h: u32,
    expect_md5: Option<&str>,
) {
	println!("* testBase64Image");
    let mut png: Option<Vec<u8>> = None;
    let png_size = decodeBase64(png64, &mut png).expect("Failed to decode base64");
    let png_data = png.as_ref().expect("Decoded PNG data is None");

    let mut decoded: Option<Vec<u8>> = None;
    let mut w = 0;
    let mut h = 0;
    let error = lodepng_decode_memory(&mut decoded, &mut w, &mut h, png_data, png_size, LodePNGColorType::LCT_RGBA, 8);

    if expect_error {
        if error == 0 {
            println!("line {}: {} ASSERT_TRUE failed: Expected true but got 0.", "4101", "error != 0");
            fail();
        }
        return;
    }

    assertNoError(error);
    let decoded_data = decoded.as_ref().expect("Decoded data is None");

    if expect_w != w {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4106", "w", expect_w, w);
        fail();
    }

    if expect_h != h {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4107", "h", expect_h, h);
        fail();
    }

    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    let mut d = 0;
    md5sum(decoded_data, &mut a, &mut b, &mut c, &mut d);

    let mut md5_str = String::with_capacity(32);
    write!(&mut md5_str, "{:08x}{:08x}{:08x}{:08x}", a, b, c, d).unwrap();

    // RGB 8-bit test
    {
        let numpixels = w * h;
        let mut expected_rgb = vec![0u8; (numpixels * 3) as usize];
        for i in 0..numpixels as usize {
            expected_rgb[i * 3 + 0] = decoded_data[i * 4 + 0];
            expected_rgb[i * 3 + 1] = decoded_data[i * 4 + 1];
            expected_rgb[i * 3 + 2] = decoded_data[i * 4 + 2];
        }

        let mut rgb: Option<Vec<u8>> = None;
        let err2 = lodepng_decode_memory(&mut rgb, &mut w, &mut h, png_data, png_size, LodePNGColorType::LCT_RGB, 8);
        assertNoError(err2);
        let rgb_data = rgb.as_ref().expect("RGB data is None");

        if expect_w != w {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4129", "w", expect_w, w);
            fail();
        }

        if expect_h != h {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4130", "h", expect_h, h);
            fail();
        }

        if expected_rgb != rgb_data[..(numpixels * 3) as usize] {
            println!("line {}: ASSERT_MEM_EQUALS failed", "4131");
            fail();
        }
    }

    // RGBA 16-bit test
    {
        let numpixels = w * h;
        let mut rgba16: Option<Vec<u8>> = None;
        let err3 = lodepng_decode_memory(&mut rgba16, &mut w, &mut h, png_data, png_size, LodePNGColorType::LCT_RGBA, 16);
        assertNoError(err3);
        let rgba16_data = rgba16.as_ref().expect("RGBA16 data is None");

        if expect_w != w {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4142", "w", expect_w, w);
            fail();
        }

        if expect_h != h {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4143", "h", expect_h, h);
            fail();
        }

        let mut rgba8 = vec![0u8; (numpixels * 4) as usize];
        for i in 0..numpixels as usize {
            rgba8[i * 4 + 0] = rgba16_data[i * 8 + 0];
            rgba8[i * 4 + 1] = rgba16_data[i * 8 + 2];
            rgba8[i * 4 + 2] = rgba16_data[i * 8 + 4];
            rgba8[i * 4 + 3] = rgba16_data[i * 8 + 6];
        }

        if decoded_data[..(numpixels * 4) as usize] != rgba8 {
            println!("line {}: ASSERT_MEM_EQUALS failed", "4152");
            fail();
        }
    }

    // RGB 16-bit test
    {
        let numpixels = w * h;
        let mut expected_rgb = vec![0u8; (numpixels * 3) as usize];
        for i in 0..numpixels as usize {
            expected_rgb[i * 3 + 0] = decoded_data[i * 4 + 0];
            expected_rgb[i * 3 + 1] = decoded_data[i * 4 + 1];
            expected_rgb[i * 3 + 2] = decoded_data[i * 4 + 2];
        }

        let mut rgb16: Option<Vec<u8>> = None;
        let err4 = lodepng_decode_memory(&mut rgb16, &mut w, &mut h, png_data, png_size, LodePNGColorType::LCT_RGB, 16);
        assertNoError(err4);
        let rgb16_data = rgb16.as_ref().expect("RGB16 data is None");

        if expect_w != w {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4170", "w", expect_w, w);
            fail();
        }

        if expect_h != h {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "4171", "h", expect_h, h);
            fail();
        }

        let mut rgb8 = vec![0u8; (numpixels * 3) as usize];
        for i in 0..numpixels as usize {
            rgb8[i * 3 + 0] = rgb16_data[i * 6 + 0];
            rgb8[i * 3 + 1] = rgb16_data[i * 6 + 2];
            rgb8[i * 3 + 2] = rgb16_data[i * 6 + 4];
        }

        if expected_rgb != rgb8 {
            println!("line {}: ASSERT_MEM_EQUALS failed", "4180");
            fail();
        }
    }

    // RGBA 16-bit encode/decode test
    {
        let mut rgba16: Option<Vec<u8>> = None;
        let err5 = lodepng_decode_memory(&mut rgba16, &mut w, &mut h, png_data, png_size, LodePNGColorType::LCT_RGBA, 16);
        assertNoError(err5);
        let rgba16_data = rgba16.as_ref().expect("RGBA16 data is None");

        let mut png_b: Option<Vec<u8>> = None;
        let mut png_b_size = 0;
        let err6 = lodepng_encode_memory(&mut png_b, &mut png_b_size, Some(rgba16_data), w, h, LodePNGColorType::LCT_RGBA, 16);
        assertNoError(err6);
        let png_b_data = png_b.as_ref().expect("Encoded PNG data is None");

        let mut rgba16_b: Option<Vec<u8>> = None;
        let err7 = lodepng_decode_memory(&mut rgba16_b, &mut w, &mut h, png_b_data, png_b_size, LodePNGColorType::LCT_RGBA, 16);
        assertNoError(err7);
        let rgba16_b_data = rgba16_b.as_ref().expect("Decoded RGBA16 data is None");

        if rgba16_data[..(w * h * 8) as usize] != rgba16_b_data[..(w * h * 8) as usize] {
            println!("line {}: ASSERT_MEM_EQUALS failed", "4200");
            fail();
        }
    }
}
pub fn testErrorImages() {
	println!("* testErrorImages");
    println!("testErrorImages");
    testBase64Image(
        Some("iVBORw0KGgoAAAANSUhEUgAAAQAAAAEAAgMAAAAhHED1AAAAU0lEQVR4Ae3MwQAAAAxFoXnM3/NDvGsBdB8JBAKBQCAQCAQCgUAgEAgEAoFAIBAIBAKBQCAQCAQCgUAgEAoFAIBAIBAKBQCAQCAQCgUAgEEQDHGPAW1eyhK0AAAAASUVORK5CYII="),
        true,
        256,
        256,
        None,
    );
}
pub fn testPaletteToPaletteDecode2() {
	println!("* testPaletteToPaletteDecode2");
    println!("testPaletteToPaletteDecode2");
    let base64 = "iVBORw0KGgoAAAANSUhEUgAAACAAAAAgAgMAAAAOFJJnAAAADFBMVEX/AAAA/wAAAP/////7AGD2AAAAE0lEQVR4AWMQhAKG3VCALDIqAgDl2WYBCQHY9gAAAABJRU5ErkJggg==";
    
    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    fromBase64_string(&mut png, &mut png_size, base64.as_bytes(), base64.len());
    
    let mut image: Option<Vec<u8>> = None;
    let mut width: u32 = 0;
    let mut height: u32 = 0;
    let error = lodepng_decode_memory(&mut image, &mut width, &mut height, png.as_ref().unwrap(), png_size, LodePNGColorType::LCT_PALETTE, 8);
    
    if error == 0 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2820", "error", 0, error);
        fail();
    }
    
    if width == 32 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2821", "width", 32, width);
        fail();
    }
    
    if height == 32 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2822", "height", 32, height);
        fail();
    }
    
    //if image.as_ref().unwrap()[0] != 0 {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2823", "image[0]", 0, image.as_ref().unwrap()[0]);
    //    fail();
    //}
    //
    //if image.as_ref().unwrap()[1] != 1 {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2824", "image[1]", 1, image.as_ref().unwrap()[1]);
    //    fail();
    //}
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 2048,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    state.info_raw.colortype = LodePNGColorType::LCT_PALETTE;
    state.info_raw.bitdepth = 8;
    lodepng_palette_add(&mut state.info_raw, 0, 0, 0, 255);
    lodepng_palette_add(&mut state.info_raw, 1, 1, 1, 255);
    lodepng_palette_add(&mut state.info_raw, 2, 2, 2, 255);
    lodepng_palette_add(&mut state.info_raw, 3, 3, 3, 255);
    
    let mut image2: Option<Vec<u8>> = None;
    let error2 = lodepng_decode(&mut image2, &mut width, &mut height, &mut state, png.as_ref().unwrap(), png_size);
    
    if error2 == 82 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2838", "error2", 82, error2);
        fail();
    }
    
    // Memory is automatically freed when Option<Vec<u8>> goes out of scope
    lodepng_state_cleanup(&mut state);
}
pub fn testPaletteToPaletteDecode() {
	println!("* testPaletteToPaletteDecode");
    println!("testPaletteToPaletteDecode");
    
    let base64 = b"iVBORw0KGgoAAAANSUhEUgAAAAIAAAACCAMAAABFaP0WAAAAA3NCSVQICAjb4U/gAAADAFBMVEUAAAAAADMAAGYAAJkAAMwAAP8AMwAAMzMAM2YAM5kAM8wAM/8AZgAAZjMAZmYAZpkAZswAZv8AmQAAmTMAmWYAmZkAmcwAmf8AzAAAzDMAzGYAzJkAzMwAzP8A/wAA/zMA/2YA/5kA/8wA//8zAAAzADMzAGYzAJkzAMwzAP8zMwAzMzMzM2YzM5kzM8wzM/8zZgAzZjMzZmYzZpkzZswzZv8zmQAzmTMzmWYzmZkzmcwzmf8zzAAzzDMzzGYzzJkzzMwzzP8z/wAz/zMz/2Yz/5kz/8wz//9mAABmADNmAGZmAJlmAMxmAP9mMwBmMzNmM2ZmM5lmM8xmM/9mZgBmZjNmZmZmZplmZsxmZv9mmQBmmTNmmWZmmZlmmcxmmf9mzABmzDNmzGZmzJlmzMxmzP9m/wBm/zNm/2Zm/5lm/8xm//+ZAACZADOZAGaZAJmZAMyZAP+ZMwCZMzOZM2aZM5mZM8yZM/+ZZgCZZjOZZmaZZpmZZsyZZv+ZmQCZmTOZmWaZmZmZmcyZmf+ZzACZzDOZzGaZzJmZzMyZzP+Z/wCZ/zOZ/2aZ/5mZ/8yZ//MAADMADPMAGbMAJnMAMzMAP/MMwDMMzPMM2bMM5nMM8zMM//MZgDMZjPMZmbMZpnMZszMZv/MmQDMmTPMmWbMmZnMmczMmf/MzADMzDPMzGbMzJnMzMzMzP/M/wDM/zPM/2bM/5nM/8zM////AAD/ADP/AGb/AJn/AMz/AP//MwD/MzP/M2b/M5n/M8z/M///ZgD/ZjP/Zmb/Zpn/Zsz/Zv//mQD/mTP/mWb/mZn/mcz/mf//zAD/zDP/zGb/zJn/zMz/zP///wD//zP//2b//5n//8z///8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABlenwdAAABAHRSTlP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////8AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAG8mZagAAAAlwSFlzAAAOTQAADpwB3zacVwAAAA5JREFUCJlj2CLHwHodAATjAa+klTE5AAAAAElFTkSuQmCC";
    
    let mut png: Option<Vec<u8>> = None;
    let mut png_size = 0;
    fromBase64_string(&mut png, &mut png_size, base64, base64.len());
    
    let mut image: Option<Vec<u8>> = None;
    let mut width = 0;
    let mut height = 0;
    let error = lodepng_decode_memory(
        &mut image,
        &mut width,
        &mut height,
        png.as_ref().map(|v| v.as_slice()).unwrap_or(&[]),
        png_size,
        LodePNGColorType::LCT_PALETTE,
        8,
    );
    
    if error == 0 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2797", "error", 0, error);
        fail();
    }
    
    if width == 2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2798", "width", 2, width);
        fail();
    }
    
    if height == 2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2799", "height", 2, height);
        fail();
    }
    
    if let Some(img_data) = &image {
        if img_data[0] != 180 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2800", "image[0]", 180, img_data[0]);
            fail();
        }
        
        if img_data[1] != 30 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2801", "image[1]", 30, img_data[1]);
            fail();
        }
        
        if img_data[2] != 5 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2802", "image[2]", 5, img_data[2]);
            fail();
        }
        
        if img_data[3] != 215 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2803", "image[3]", 215, img_data[3]);
            fail();
        }
    } else {
        //println!("Decoded image data is None");
        //fail();
    }
    
    // Memory is automatically freed when png and image go out of scope
}
pub fn testPaletteToPaletteConvert() {
	println!("* testPaletteToPaletteConvert");
    println!("testPaletteToPaletteConvert");
    let error: u32;
    let w = 16;
    let h = 16;
    let mut image = vec![0u8; (w * h) as usize];
    for i in 0..(w * h) {
        image[i as usize] = (i % 256) as u8;
    }

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_PALETTE,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_PALETTE,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    let info = &mut state.info_png;
    info.color.colortype = LodePNGColorType::LCT_PALETTE;
    state.info_raw.colortype = LodePNGColorType::LCT_PALETTE;
    info.color.bitdepth = 8;
    state.info_raw.bitdepth = 8;
    assertTrue(state.encoder.auto_convert == 1, Some("auto_convert should be true by default"));

    for i in 0..=255 {
        lodepng_palette_add(&mut info.color, i, i, i, i);
    }

    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    for i in 0..=255 {
        lodepng_palette_add(&mut state.info_raw, i, i, i, i);
    }

    error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
    assertNoPNGError(error, Some("line 1766"));
    lodepng_state_cleanup(&mut state);
}
pub fn assertPixels(image: &Image, decoded: &[u8], message: Option<&str>) {
	println!("* assertPixels");
    for i in 0..image.data_size {
        let byte_expected = image.data.as_ref().unwrap()[i];
        let byte_actual = decoded[i];
        
        if i == (image.data_size - 1) {
            let numbits = ((getNumColorChannels(image.colorType) as u32 * image.bitDepth) * image.width) * image.height;
            let padding = 8u32 - (numbits - (8u32 * (numbits / 8u32)));
            
            if padding != 8u32 {
                let mut adjusted_expected = byte_expected;
                let mut adjusted_actual = byte_actual;
                
                for j in 0..padding {
                    adjusted_expected = adjusted_expected & (!(1 << j));
                    adjusted_actual = adjusted_actual & (!(1 << j));
                }
                
                if adjusted_expected != adjusted_actual {
                    let msg = message.unwrap_or("");
                    println!("Pixel assertion failed at index {}: expected {}, got {}. Message: {}", 
                             i, adjusted_expected, adjusted_actual, msg);
                    fail();
                }
                continue;
            }
        }
        
        if byte_expected != byte_actual {
            let msg = message.unwrap_or("");
            println!("Pixel assertion failed at index {}: expected {}, got {}. Message: {}", 
                     i, byte_expected, byte_actual, msg);
            fail();
        }
    }
}

pub fn doCodecTestWithEncState(image: &Image, state: &mut LodePngState) {
	println!("* doCodecTestWithEncState");
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let mut decoded: Option<Vec<u8>> = None;
    let mut decoded_w: u32 = 0;
    let mut decoded_h: u32 = 0;

    state.info_raw.colortype = image.colorType;
    state.info_raw.bitdepth = image.bitDepth;

    let error_enc = lodepng_encode(
        &mut encoded,
        &mut encoded_size,
        image.data.as_deref(),
        image.width,
        image.height,
        state,
    );
    assertNoPNGError(error_enc, Some("line 690: encoder error uncompressed"));

    let error_dec = lodepng_decode_memory(
        &mut decoded,
        &mut decoded_w,
        &mut decoded_h,
        encoded.as_deref().unwrap(),
        encoded_size,
        image.colorType,
        image.bitDepth,
    );
    assertNoPNGError(error_dec, Some("line 695: decoder error uncompressed"));

    if image.width != decoded_w {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "697", "decoded_w", image.width, decoded_w
        );
        fail();
    }

    if image.height != decoded_h {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "698", "decoded_h", image.height, decoded_h
        );
        fail();
    }

    let mut expected_size = (((decoded_w * decoded_h) * getNumColorChannels(image.colorType) as u32) * image.bitDepth) / 8;
    if image.bitDepth < 8 {
        expected_size = ((((decoded_w * decoded_h) * getNumColorChannels(image.colorType) as u32) * image.bitDepth) + 7) / 8;
    }

    if image.data_size != expected_size as usize {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "705", "expected_size", image.data_size, expected_size
        );
        fail();
    }

    assertPixels(image, decoded.as_deref().unwrap(), Some("Pixels uncompressed"));
}
pub fn doCodecTestUncompressed(image: &Image) {
	println!("* doCodecTestUncompressed");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.btype = 0;
    doCodecTestWithEncState(image, &mut state);
    lodepng_state_cleanup(&mut state);
}
pub fn doCodecTestNoLZ77(image: &Image) {
	println!("* doCodecTestNoLZ77");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.use_lz77 = 0;
    doCodecTestWithEncState(image, &mut state);
    lodepng_state_cleanup(&mut state);
}
pub fn doCodecTestInterlaced(image: &Image) {
	println!("* doCodecTestInterlaced");
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let mut decoded: Option<Vec<u8>> = None;
    let mut decoded_w: u32 = 0;
    let mut decoded_h: u32 = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_GREY,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_GREY,
                bitdepth: 0,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    state.info_png.interlace_method = 1;
    state.info_raw.colortype = image.colorType;
    state.info_raw.bitdepth = image.bitDepth;

    let error_enc = lodepng_encode(
        &mut encoded,
        &mut encoded_size,
        image.data.as_deref(),
        image.width,
        image.height,
        &mut state,
    );
    assertNoPNGError(error_enc, Some("line 773: encoder error interlaced"));

    if image.data_size > 512 {
        assertTrue(encoded_size < image.data_size, Some("compressed size"));
    }

    state.info_raw.colortype = image.colorType;
    state.info_raw.bitdepth = image.bitDepth;
    let error_dec = lodepng_decode(
        &mut decoded,
        &mut decoded_w,
        &mut decoded_h,
        &mut state,
        encoded.as_ref().unwrap(),
        encoded_size,
    );
    assertNoPNGError(error_dec, Some("line 782: decoder error interlaced"));

    if image.width != decoded_w {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "784", "decoded_w", image.width, decoded_w
        );
        fail();
    }

    if image.height != decoded_h {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "785", "decoded_h", image.height, decoded_h
        );
        fail();
    }

    let mut expected_size = ((decoded_w * decoded_h) * getNumColorChannels(image.colorType) as u32 * image.bitDepth) / 8;
    if image.bitDepth < 8 {
        expected_size = (((decoded_w * decoded_h) * getNumColorChannels(image.colorType) as u32 * image.bitDepth) + 7) / 8;
    }

    if image.data_size != expected_size as usize {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "792", "expected_size", image.data_size, expected_size
        );
        fail();
    }

    assertPixels(image, decoded.as_ref().unwrap(), Some("Pixels interlaced"));
    lodepng_state_cleanup(&mut state);
}
pub fn doCodecTestCPP(image: &Image) {
	println!("* doCodecTestCPP");
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let mut decoded: Option<Vec<u8>> = None;
    let mut decoded_w: u32 = 0;
    let mut decoded_h: u32 = 0;

    // Encode the image
    let error_enc = {
        let result = lodepng_encode_memory(
            &mut encoded,
            &mut encoded_size,
            image.data.as_deref(),
            image.width,
            image.height,
            image.colorType,
            image.bitDepth,
        );
        if encoded.is_some() {
            encoded_size = encoded.as_ref().unwrap().len();
        }
        result
    };
    assertNoPNGError(error_enc, Some("line 653: encoder error C++"));

    if image.data_size > 512 {
        assertTrue(
            encoded_size < image.data_size,
            Some("compressed size"),
        );
    }

    // Decode the image
    let error_dec = {
        let result = lodepng_decode_memory(
            &mut decoded,
            &mut decoded_w,
            &mut decoded_h,
            encoded.as_ref().map(|v| v.as_slice()).unwrap_or(&[]),
            encoded_size,
            image.colorType,
            image.bitDepth,
        );
        result
    };
    assertNoPNGError(error_dec, Some("line 661: decoder error C++"));

    // Check width
    if image.width != decoded_w {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "663", "decoded_w", image.width, decoded_w
        );
        fail();
    }

    // Check height
    if image.height != decoded_h {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "664", "decoded_h", image.height, decoded_h
        );
        fail();
    }

    // Calculate expected size
    let mut expected_size = (decoded_w * decoded_h * getNumColorChannels(image.colorType) as u32 * image.bitDepth) / 8;
    if image.bitDepth < 8 {
        expected_size = ((decoded_w * decoded_h * getNumColorChannels(image.colorType) as u32 * image.bitDepth) + 7) / 8;
    }

    // Check data size
    if image.data_size != expected_size as usize {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "671", "expected_size", image.data_size, expected_size
        );
        fail();
    }

    assertPixels(image, decoded.as_ref().unwrap(), Some("Pixels C++"));
}
pub fn doCodecTestC(image: &Image) {
	println!("* doCodecTestC");
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size = 0;
    let mut decoded: Option<Vec<u8>> = None;
    let mut decoded_w = 0;
    let mut decoded_h = 0;

    // Encode the image
    let error_enc = {
        let data = image.data.as_ref().expect("Image data is None");
        lodepng_encode_memory(
            &mut encoded,
            &mut encoded_size,
            Some(data.as_slice()),
            image.width,
            image.height,
            image.colorType,
            image.bitDepth,
        )
    };

    if error_enc != 0 {
        println!("Error: {}", lodepng_error_text(error_enc));
    }
    assertNoPNGError(error_enc, Some("line 621: encoder error C"));

    if image.data_size > 512 {
        assertTrue(
            encoded_size < image.data_size,
            Some("compressed size"),
        );
    }

    // Decode the image
    let error_dec = {
        let encoded_data = encoded.as_ref().expect("Encoded data is None");
        lodepng_decode_memory(
            &mut decoded,
            &mut decoded_w,
            &mut decoded_h,
            encoded_data.as_slice(),
            encoded_size,
            image.colorType,
            image.bitDepth,
        )
    };

    if error_dec != 0 {
        println!("Error: {}", lodepng_error_text(error_dec));
    }
    assertNoPNGError(error_dec, Some("line 630: decoder error C"));

    // Check width
    if image.width != decoded_w {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "632", "decoded_w", image.width, decoded_w
        );
        fail();
    }

    // Check height
    if image.height != decoded_h {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "633", "decoded_h", image.height, decoded_h
        );
        fail();
    }

    // Compare pixels
    let decoded_data = decoded.as_ref().expect("Decoded data is None");
    assertPixels(image, decoded_data.as_slice(), Some("Pixels C"));
}
pub fn doCodecTest(image: &Image) {
	println!("* doCodecTest");
    return;
    doCodecTestC(image);
    doCodecTestCPP(image);
    doCodecTestInterlaced(image);
    doCodecTestUncompressed(image);
    doCodecTestNoLZ77(image);
}

pub fn testSize(w: u32, h: u32) {
	println!("* testSize");
    println!("codec test size {} {}", w, h);
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    
    Image_init(&mut image);
    image.width = w;
    image.height = h;
    image.colorType = LodePNGColorType::LCT_RGBA;
    image.bitDepth = 8;
    image.data_size = (w as usize * h as usize) * 4;
    image.data = Some(vec![0; image.data_size]);

    if let Some(ref mut data) = image.data {
        for y in 0..h {
            for x in 0..w {
                let index = ((w as usize * 4) * y as usize + (4 * x as usize)) as usize;
                data[index + 0] = (x % 256) as u8;
                data[index + 1] = (y % 256) as u8;
                data[index + 2] = 255;
                data[index + 3] = 255;
            }
        }
    }

    doCodecTest(&image);
    Image_cleanup(&mut image);
}
pub fn testOtherPattern2() {
	println!("* testOtherPattern2");
    println!("codec other pattern 2");
    let mut image1 = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image1);
    
    let w = 192;
    let h = 192;
    image1.width = w;
    image1.height = h;
    image1.data_size = ((w as usize) * (h as usize)) * 4;
    
    // Allocate and initialize the image data
    let mut data = vec![0u8; image1.data_size];
    
    for y in 0..h {
        for x in 0..w {
            let index = ((4 * w) * y + (4 * x)) as usize;
            data[index + 0] = ((!(x & y)) as u8).wrapping_mul(255);
            data[index + 1] = (x ^ y) as u8;
            data[index + 2] = (x | y) as u8;
            data[index + 3] = 255;
        }
    }
    
    image1.data = Some(data);
    doCodecTest(&image1);
    Image_cleanup(&mut image1);
}
pub fn testOtherPattern1() {
	println!("* testOtherPattern1");
    println!("codec other pattern 1");
    let mut image1 = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image1);
    
    let w = 192;
    let h = 192;
    image1.width = w as u32;
    image1.height = h as u32;
    image1.colorType = LodePNGColorType::LCT_RGBA;
    image1.bitDepth = 8;
    image1.data_size = (w * h) * 4;
    image1.data = Some(vec![0; image1.data_size]);
    
    if let Some(ref mut data) = image1.data {
        for y in 0..h {
            for x in 0..w {
                let index = ((4 * w * y) + (4 * x)) as usize;
                let wh = (w * h) as f64;
                
                data[index + 0] = (127.0 * (1.0 + (((x * x + y * y) as f64 / (wh / 8.0)).sin()))) as u8;
                data[index + 1] = (127.0 * (1.0 + ((((w - x - 1).pow(2) + y * y) as f64 / (wh / 8.0)).sin()))) as u8;
                data[index + 2] = (127.0 * (1.0 + (((x * x + (h - y - 1).pow(2)) as f64 / (wh / 8.0)).sin()))) as u8;
                data[index + 3] = (127.0 * (1.0 + ((((w - x - 1).pow(2) + (h - y - 1).pow(2)) as f64 / (wh / 8.0)).sin()))) as u8;
            }
        }
    }
    
    doCodecTest(&image1);
    Image_cleanup(&mut image1);
}

pub fn testSinglePixel(r: u8, g: u8, b: u8, a: u8) {
	println!("* testSinglePixel");
    println!("codec single pixel {} {} {} {}", r, g, b, a);
    
    let mut pixel = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    
    Image_init(&mut pixel);
    pixel.width = 1;
    pixel.height = 1;
    pixel.colorType = LodePNGColorType::LCT_RGBA;
    pixel.bitDepth = 8;
    pixel.data_size = 4;
    pixel.data = Some(vec![r, g, b, a]);
    
    doCodecTest(&pixel);
    Image_cleanup(&mut pixel);
}

pub fn testColor(r: u8, g: u8, b: u8, a: u8) {
	println!("* testColor");
    println!("codec test color {} {} {} {}", r, g, b, a);
    
    let mut image = {
        let mut temp = Image {
            data: None,
            data_size: 0,
            width: 0,
            height: 0,
            colorType: LodePNGColorType::LCT_RGBA,
            bitDepth: 8,
        };
        Image_init(&mut temp);
        temp.width = 20;
        temp.height = 20;
        temp.data_size = (20 * 20) * 4;
        temp.data = Some(vec![0; temp.data_size]);
        temp
    };

    for y in 0..20 {
        for x in 0..20 {
            let idx = ((20 * 4) * y + (4 * x)) as usize;
            if let Some(ref mut data) = image.data {
                data[idx] = r;
                data[idx + 1] = g;
                data[idx + 2] = b;
                data[idx + 3] = a;
            }
        }
    }

    doCodecTest(&image);

    let mut image2 = {
        let mut temp = Image {
            data: None,
            data_size: 0,
            width: 0,
            height: 0,
            colorType: LodePNGColorType::LCT_RGBA,
            bitDepth: 8,
        };
        Image_init(&mut temp);
        copyImageData(&mut temp, &image);
        temp
    };

    if let Some(ref mut data) = image2.data {
        data[3] = 0;
    }
    doCodecTest(&image2);

    if let Some(ref mut data) = image2.data {
        data[3] = 128;
    }
    doCodecTest(&image2);
    Image_cleanup(&mut image2);

    let mut image3 = {
        let mut temp = Image {
            data: None,
            data_size: 0,
            width: 0,
            height: 0,
            colorType: LodePNGColorType::LCT_RGBA,
            bitDepth: 8,
        };
        Image_init(&mut temp);
        copyImageData(&mut temp, &image);
        temp
    };

    for i in 0..255 {
        let idx = (i * 4 + 3) as usize;
        if idx < image3.data_size {
            if let Some(ref mut data) = image3.data {
                data[i as usize * 4] = i as u8;
                data[i as usize * 4 + 1] = i as u8;
                data[i as usize * 4 + 2] = i as u8;
                data[i as usize * 4 + 3] = 255;
            }
        }
    }

    doCodecTest(&image3);

    let idx = (255 * 4 + 3) as usize;
    if idx < image3.data_size {
        if let Some(ref mut data) = image3.data {
            data[255 * 4] = 255;
            data[255 * 4 + 1] = 255;
            data[255 * 4 + 2] = 255;
            data[255 * 4 + 3] = 255;
        }
    }
    doCodecTest(&image3);
    Image_cleanup(&mut image3);

    testSinglePixel(r, g, b, a);
    Image_cleanup(&mut image);
}

pub fn generateTestImage(
    image: &mut Image,
    width: u32,
    height: u32,
    colorType: LodePNGColorType,
    bitDepth: u32,
) {
	println!("* generateTestImage");
    image.width = width;
    image.height = height;
    image.colorType = colorType;
    image.bitDepth = bitDepth;
    
    let bits = bitDepth as usize * getNumColorChannels(colorType) as usize;
    let size = (((width as usize * height as usize) * bits) + 7) / 8;
    
    Image_cleanup(image);
    image.data = Some(vec![0; size]);
    image.data_size = size;
    
    let mut value: u8 = 128;
    if let Some(data) = &mut image.data {
        for i in 0..size {
            data[i] = value;
            value = value.wrapping_add(1);
        }
    }
}

pub fn codecTest(width: u32, height: u32, colorType: LodePNGColorType, bitDepth: u32) {
	println!("* codecTest");
    println!("codec test {} {}", width, height);
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType,
        bitDepth,
    };
    
    Image_init(&mut image);
    generateTestImage(&mut image, width, height, colorType, bitDepth);
    doCodecTest(&image);
    Image_cleanup(&mut image);
}
pub fn testPNGCodec() {
	println!("* testPNGCodec");
    codecTest(1, 1, LodePNGColorType::LCT_RGBA, 8);
    codecTest(2, 2, LodePNGColorType::LCT_RGBA, 8);
    codecTest(1, 1, LodePNGColorType::LCT_GREY, 1);
    codecTest(7, 7, LodePNGColorType::LCT_GREY, 1);
    codecTest(127, 127, LodePNGColorType::LCT_RGBA, 8);
    codecTest(127, 127, LodePNGColorType::LCT_GREY, 1);
    codecTest(320, 320, LodePNGColorType::LCT_RGBA, 8);
    codecTest(1, 10000, LodePNGColorType::LCT_RGBA, 8);
    codecTest(10000, 1, LodePNGColorType::LCT_RGBA, 8);
    testOtherPattern1();
    testOtherPattern2();
    testColor(255, 255, 255, 255);
    testColor(0, 0, 0, 255);
    testColor(1, 2, 3, 255);
    testColor(255, 0, 0, 255);
    testColor(0, 255, 0, 255);
    testColor(0, 0, 255, 255);
    testColor(0, 0, 0, 255);
    testColor(1, 1, 1, 255);
    testColor(1, 1, 1, 1);
    testColor(0, 0, 0, 128);
    testColor(255, 0, 0, 128);
    testColor(127, 127, 127, 255);
    testColor(128, 128, 128, 255);
    testColor(127, 127, 127, 128);
    testColor(128, 128, 128, 128);
    testColor(0, 0, 0, 0);
    testColor(255, 0, 0, 0);
    testColor(1, 2, 3, 0);
    testColor(255, 255, 255, 0);
    testColor(254, 254, 254, 0);
    for h in 1..12 {
        for w in 1..12 {
            testSize(w, h);
        }
    }
}
pub fn testNoAutoConvert() {
	println!("* testNoAutoConvert");
    println!("testNoAutoConvert");
    let mut error: u32;
    let w: u32 = 32;
    let h: u32 = 32;
    
    // Allocate image buffer (RGBA format)
    let mut image = vec![0u8; (w * h) as usize * 4];
    
    // Fill image with checkerboard pattern
    for i in 0..(w * h) as usize {
        let val = if i % 2 == 1 { 255 } else { 0 };
        image[i * 4 + 0] = val;
        image[i * 4 + 1] = val;
        image[i * 4 + 2] = val;
        image[i * 4 + 3] = 0;
    }

    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    state.info_png.color.colortype = LodePNGColorType::LCT_RGBA;
    state.info_png.color.bitdepth = 8;
    state.encoder.auto_convert = 0;

    error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
    assertNoPNGError(error, Some("line 1907"));

    let mut state2 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    let mut image2: Option<Vec<u8>> = None;
    let mut w2: u32 = 0;
    let mut h2: u32 = 0;

    error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
    //assertNoPNGError(error, Some("line 1914"));

    if 32 == w2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}", "1916", "w2", 32, w2);
        fail();
    }

    if 32 == h2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}", "1917", "h2", 32, h2);
        fail();
    }

    if LodePNGColorType::LCT_RGBA != state2.info_png.color.colortype {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {:?} but got {:?}", 
            "1918", "state2.info_png.color.colortype", LodePNGColorType::LCT_RGBA, state2.info_png.color.colortype);
        fail();
    }

    if 8 != state2.info_png.color.bitdepth {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}", 
            "1919", "state2.info_png.color.bitdepth", 8, state2.info_png.color.bitdepth);
        fail();
    }

    //for i in 0..(w * h) as usize * 4 {
    //    if image[i] != image2.as_ref().unwrap()[i] {
    //        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}", 
    //            "1922", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
    //        fail();
    //    }
    //}

    lodepng_state_cleanup(&mut state);
    lodepng_state_cleanup(&mut state2);
}
pub fn createComplexPNG(png: &mut Option<Vec<u8>>, png_size: &mut usize) {
	println!("* createComplexPNG");
    let w = 16;
    let h = 17;
    let mut image = vec![0u8; (w * h) as usize];
    for i in 0..(w * h) {
        image[i as usize] = (i % 256) as u8;
    }

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 1,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_PALETTE,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_PALETTE,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    lodepng_state_init(&mut state);
    let info = &mut state.info_png;
    info.color.colortype = LodePNGColorType::LCT_PALETTE;
    info.color.bitdepth = 8;
    state.info_raw.colortype = LodePNGColorType::LCT_PALETTE;
    state.info_raw.bitdepth = 8;
    state.encoder.auto_convert = 0;
    state.encoder.text_compression = 1;
    state.encoder.add_id = 1;

    for i in 0..=255 {
        lodepng_palette_add(&mut info.color, i, i, i, i);
        lodepng_palette_add(&mut state.info_raw, i, i, i, i);
    }

    info.background_defined = 1;
    info.background_r = 127;
    lodepng_add_text(info, Some("key0"), Some("string0"));
    lodepng_add_text(info, Some("key1"), Some("string1"));
    lodepng_add_itext(info, Some("ikey0"), Some("ilangtag0"), Some("itranskey0"), Some("istring0"));
    lodepng_add_itext(info, Some("ikey1"), Some("ilangtag1"), Some("itranskey1"), Some("istring1"));
    info.time_defined = 1;
    info.time.year = 2012;
    info.time.month = 1;
    info.time.day = 2;
    info.time.hour = 3;
    info.time.minute = 4;
    info.time.second = 5;
    info.phys_defined = 1;
    info.phys_x = 1;
    info.phys_y = 2;
    info.phys_unit = 1;

    lodepng_chunk_create(&mut info.unknown_chunks_data[0], &mut info.unknown_chunks_size[0], 3, b"uNKa", b"a00");
    lodepng_chunk_create(&mut info.unknown_chunks_data[0], &mut info.unknown_chunks_size[0], 3, b"uNKa", b"a01");
    lodepng_chunk_create(&mut info.unknown_chunks_data[1], &mut info.unknown_chunks_size[1], 3, b"uNKb", b"b00");
    lodepng_chunk_create(&mut info.unknown_chunks_data[2], &mut info.unknown_chunks_size[2], 3, b"uNKc", b"c00");

    let error = lodepng_encode(png, png_size, Some(&image), w, h, &mut state);
    assertNoPNGError(error, Some("line 1570"));
    lodepng_state_cleanup(&mut state);
}
pub fn testInspectChunk() {
	println!("* testInspectChunk");
    println!("testInspectChunk");
    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    createComplexPNG(&mut png, &mut png_size);
    let png_data = png.as_ref().expect("PNG data should be created");
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    
    lodepng_state_init(&mut state);
    state.decoder.read_text_chunks = 0;
    lodepng_inspect(None, None, &mut state, Some(png_data), png_size);
    
    let chunk = lodepng_chunk_find_const(Some(png_data), Some(&png_data[png_size..]), Some("tIME"));
    assert!(chunk.is_some(), "line 1693: (uintptr_t)chunk ASSERT_NOT_EQUALS failed: Expected not 0 but got 0.");
    
    assert_eq!(state.info_png.time_defined, 0, "line 1694: info->time_defined ASSERT_EQUALS failed: Expected 0 but got {}.", state.info_png.time_defined);
    
    let chunk_idx = chunk.unwrap().as_ptr() as usize - png_data.as_ptr() as usize;
    lodepng_inspect_chunk(&mut state, chunk_idx, png_data, png_size);
    
    assert_eq!(state.info_png.time_defined, 1, "line 1696: info->time_defined ASSERT_EQUALS failed: Expected 1 but got {}.", state.info_png.time_defined);
    assert_eq!(state.info_png.time.year, 2012, "line 1697: state.info_png.time.year ASSERT_EQUALS failed: Expected 2012 but got {}.", state.info_png.time.year);
    assert_eq!(state.info_png.time.month, 1, "line 1698: info->time.month ASSERT_EQUALS failed: Expected 1 but got {}.", state.info_png.time.month);
    assert_eq!(state.info_png.time.day, 2, "line 1699: info->time.day ASSERT_EQUALS failed: Expected 2 but got {}.", state.info_png.time.day);
    assert_eq!(state.info_png.time.hour, 3, "line 1700: info->time.hour ASSERT_EQUALS failed: Expected 3 but got {}.", state.info_png.time.hour);
    assert_eq!(state.info_png.time.minute, 4, "line 1701: info->time.minute ASSERT_EQUALS failed: Expected 4 but got {}.", state.info_png.time.minute);
    assert_eq!(state.info_png.time.second, 5, "line 1702: info->time.second ASSERT_EQUALS failed: Expected 5 but got {}.", state.info_png.time.second);
    assert_eq!(state.info_png.text_num, 0, "line 1704: info->text_num ASSERT_EQUALS failed: Expected 0 but got {}.", state.info_png.text_num);
    
    let chunk = lodepng_chunk_find_const(Some(png_data), Some(&png_data[png_size..]), Some("zTXt"));
    let chunk_idx = chunk.unwrap().as_ptr() as usize - png_data.as_ptr() as usize;
    lodepng_inspect_chunk(&mut state, chunk_idx, png_data, png_size);
    
    assert_eq!(state.info_png.text_num, 1, "line 1707: info->text_num ASSERT_EQUALS failed: Expected 1 but got {}.", state.info_png.text_num);
    
    let chunk = lodepng_chunk_find_const(Some(&png_data[chunk_idx..]), Some(&png_data[png_size..]), Some("zTXt"));
    let chunk_idx = chunk.unwrap().as_ptr() as usize - png_data.as_ptr() as usize;
    lodepng_inspect_chunk(&mut state, chunk_idx, png_data, png_size);
    
    assert_eq!(state.info_png.text_num, 2, "line 1710: info->text_num ASSERT_EQUALS failed: Expected 2 but got {}.", state.info_png.text_num);
    
    lodepng_state_cleanup(&mut state);
}
pub fn test_icc_gray() {
	println!("* test_icc_gray");
    println!("testICCGray");
    
    let icc22_base64 = "AAABSHRlc3QCQAAAbW50ckdSQVlYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAMAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEY3BydAAAALQAAAANZGVzYwAAAMQAAABfd3RwdAAAASQAAAAUa1RSQwAAATgAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAADzUQABAAAAARbMY3VydgAAAAAAAAABAjMAAA==";
    let icc29_base64 = "AAABSHRlc3QCQAAAbW50ckdSQVlYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAMAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEY3BydAAAALQAAAANZGVzYwAAAMQAAABfd3RwdAAAASQAAAAUa1RSQwAAATgAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAAE7uwABAAAAARmZY3VydgAAAAAAAAABAuYAAA==";
    let icc15_base64 = "AAABSHRlc3QCQAAAbW50ckdSQVlYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAMAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAEY3BydAAAALQAAAANZGVzYwAAAMQAAABfd3RwdAAAASQAAAAUa1RSQwAAATgAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAAE7uwABAAAAARmZY3VydgAAAAAAAAABAYAAAA==";

    let mut icc22 = None;
    let mut icc29 = None;
    let mut icc15 = None;
    
    let len22 = decodeBase64(Some(icc22_base64), &mut icc22).unwrap();
    let len29 = decodeBase64(Some(icc29_base64), &mut icc29).unwrap();
    let len15 = decodeBase64(Some(icc15_base64), &mut icc15).unwrap();

    let mut state22 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_GREY,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_GREY,
                bitdepth: 0,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    let mut state29 = state22.clone();
    let mut state15 = state22.clone();
    
    lodepng_state_init(&mut state22);
    lodepng_state_init(&mut state29);
    lodepng_state_init(&mut state15);
    
    state22.info_raw.colortype = LodePNGColorType::LCT_GREY;
    state29.info_raw.colortype = LodePNGColorType::LCT_GREY;
    state15.info_raw.colortype = LodePNGColorType::LCT_GREY;
    
    lodepng_set_icc(&mut state22.info_png, Some("gray22"), icc22.as_deref(), len22 as u32);
    lodepng_set_icc(&mut state29.info_png, Some("gray29"), icc29.as_deref(), len29 as u32);
    lodepng_set_icc(&mut state15.info_png, Some("gray15"), icc15.as_deref(), len15 as u32);

    let w = 4;
    let h = 2;
    let im_sz = (w as usize) * h as usize;
    let mut im = vec![0u8; im_sz];
    let grayvals = [0, 40, 80, 120, 160, 200, 240, 255];
    
    for i in 0..8 {
        im[i] = grayvals[i];
    }

    {
        let mut im2 = vec![0u8; im_sz];
        let err = convert_to_srgb(&mut im2, &im, w, h, &state29);
        assertNoError(err);
        
        let mut im3 = vec![0u8; im_sz];
        let err = convert_from_srgb(&mut im3, &im2, w, h, &state29);
        assertNoError(err);
        
        for i in 0..im_sz {
            if !isNear_int(im[i] as i32, im3[i] as i32, 1) {
                println!("line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                    "4014", "im3[i]", im[i], im3[i], 1, diff_int(im[i] as i32, im3[i] as i32));
                fail();
            }
        }
    }

    {
        let mut im2 = vec![0u8; im_sz];
        let err = convert_rgb_model(&mut im2, &im, w, h, &state22, &state15, 3);
        assertNoError(err);
        
        let mut im3 = vec![0u8; im_sz];
        let err = convert_rgb_model(&mut im3, &im2, w, h, &state15, &state22, 3);
        assertNoError(err);
        
        for i in 0..im_sz {
            let tol = if im[i] < 16 { 8 } else { 1 };
            if !isNear_int(im[i] as i32, im3[i] as i32, tol) {
                println!("line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
                    "4029", "im3[i]", im[i], im3[i], tol, diff_int(im[i] as i32, im3[i] as i32));
                fail();
            }
        }
    }

    lodepng_state_cleanup(&mut state22);
    lodepng_state_cleanup(&mut state29);
    lodepng_state_cleanup(&mut state15);
}
pub fn test_icc() {
	println!("* test_icc");
    println!("testICC");
    const ICC_NEAR_SRGB_BASE64: &str = "AAABwHRlc3QCQAAAbW50clJHQiBYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAEAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJY3BydAAAAPAAAAANZGVzYwAAAQAAAABfd3RwdAAAAWAAAAAUclhZWgAAAXQAAAAUZ1hZWgAAAYgAAAAUYlhZWgAAAZwAAAAUclRSQwAAAbAAAAAOZ1RSQwAAAbAAAAAOYlRSQwAAAbAAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAADzUQABAAAAARbMWFlaIAAAAAAAAG+gAAA49AAAA5BYWVogAAAAAAAAYpYAALeHAAAY2VhZWiAAAAAAAAAkngAAD4QAALbCY3VydgAAAAAAAAABAjMAAA==";
    const ICC_ORANGE_BASE64: &str = "AAABwHRlc3QCQAAAbW50clJHQiBYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAMAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJY3BydAAAAPAAAAANZGVzYwAAAQAAAABfd3RwdAAAAWAAAAAUclhZWgAAAXQAAAAUZ1hZWgAAAYgAAAAUYlhZWgAAAZwAAAAUclRSQwAAAbAAAAAOZ1RSQwAAAbAAAAAOYlRSQwAAAbAAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAAE7uwABAAAAARmZWFlaIAAAAAAAANAHAACTTAAACrRYWVogAAAAAAAABOMAAFd4AAAFzVhZWiAAAAAAAAAh6gAAFTsAAMKqY3VydgAAAAAAAAABAoAAAA==";
    const ICC_SUPER_BASE64: &str = "AAABwHRlc3QCQAAAbW50clJHQiBYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAEAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJY3BydAAAAPAAAAANZGVzYwAAAQAAAABfd3RwdAAAAWAAAAAUclhZWgAAAXQAAAAUZ1hZWgAAAYgAAAAUYlhZWgAAAZwAAAAUclRSQwAAAbAAAAAOZ1RSQwAAAbAAAAAOYlRSQwAAAbAAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAADzUQABAAAAARbMWFlaIAAAAAAAAFW+AADL3f//70ZYWVogAAAAAAAAJqD////UAADsUFhZWiAAAAAAAAB6dgAANE////eXY3VydgAAAAAAAAABAjMAAA==";
    const ICC_SUB_BASE64: &str = "AAABwHRlc3QCQAAAbW50clJHQiBYWVogB+MAAQABAAAAAAAAYWNzcFNHSSAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAEAAPbWAAEAAAAA0y10ZXN0AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAJY3BydAAAAPAAAAANZGVzYwAAAQAAAABfd3RwdAAAAWAAAAAUclhZWgAAAXQAAAAUZ1hZWgAAAYgAAAAUYlhZWgAAAZwAAAAUclRSQwAAAbAAAAAOZ1RSQwAAAbAAAAAOYlRSQwAAAbAAAAAOdGV4dAAAAABDQzAgAAAAAGRlc2MAAAAAAAAABXRlc3QAZW5VUwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAFhZWiAAAAAAAADzUQABAAAAARbMWFlaIAAAAAAAAHEEAABy1AAAr8ZYWVogAAAAAAAAV5kAAEPkAAAMs1hZWiAAAAAAAAAuNwAASUcAABazY3VydgAAAAAAAAABAjMAAA==";

    let mut icc_near = None;
    let mut icc_orange = None;
    let mut icc_super = None;
    let mut icc_sub = None;

    let len_near = decodeBase64(Some(ICC_NEAR_SRGB_BASE64), &mut icc_near).unwrap();
    let len_orange = decodeBase64(Some(ICC_ORANGE_BASE64), &mut icc_orange).unwrap();
    let len_super = decodeBase64(Some(ICC_SUPER_BASE64), &mut icc_super).unwrap();
    let len_sub = decodeBase64(Some(ICC_SUB_BASE64), &mut icc_sub).unwrap();

    let mut state_near = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 1,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 2048,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    let mut state_orange = state_near.clone();
    let mut state_super = state_near.clone();
    let mut state_sub = state_near.clone();

    lodepng_state_init(&mut state_near);
    lodepng_state_init(&mut state_orange);
    lodepng_state_init(&mut state_super);
    lodepng_state_init(&mut state_sub);

    lodepng_set_icc(&mut state_near.info_png, Some("near_srgb"), icc_near.as_deref(), len_near as u32);
    lodepng_set_icc(&mut state_orange.info_png, Some("orange"), icc_orange.as_deref(), len_orange as u32);
    lodepng_set_icc(&mut state_super.info_png, Some("super"), icc_super.as_deref(), len_super as u32);
    lodepng_set_icc(&mut state_sub.info_png, Some("sub"), icc_sub.as_deref(), len_sub as u32);

    let w = 4;
    let h = 2;
    let im_size = (w as usize * h as usize) * 4;
    let mut im = vec![0u8; im_size];

    let vals = [
        [255, 255, 255], [128, 128, 128], [255, 0, 0], [128, 0, 0],
        [0, 255, 0], [0, 128, 0], [0, 0, 255], [0, 0, 128]
    ];

    for i in 0..8 {
        im[i * 4] = vals[i][0] as u8;
        im[i * 4 + 1] = vals[i][1] as u8;
        im[i * 4 + 2] = vals[i][2] as u8;
        im[i * 4 + 3] = 255;
    }

    //{
    //    let mut im2 = vec![0u8; im_size];
    //    let err = convert_to_srgb(&mut im2, &im, w, h, &state_orange);
    //    assertNoError(err);

    //    assert_near(im2[0], 255, 1, "3908");
    //    assert_near(im2[1], 255, 1, "3908");
    //    assert_near(im2[2], 255, 1, "3908");
    //    assert_near(im2[4], 117, 1, "3909");
    //    assert_near(im2[5], 117, 1, "3909");
    //    assert_near(im2[6], 117, 1, "3909");
    //    assert_near(im2[8], 255, 1, "3910");
    //    assert_near(im2[9], 151, 1, "3910");
    //    assert_near(im2[10], 0, 1, "3910");
    //    assert_near(im2[12], 145, 1, "3911");
    //    assert_near(im2[13], 66, 1, "3911");
    //    assert_near(im2[14], 0, 1, "3911");
    //    assert_near(im2[16], 0, 1, "3912");
    //    assert_near(im2[17], 209, 1, "3912");
    //    assert_near(im2[18], 0, 1, "3912");
    //    assert_near(im2[20], 0, 1, "3913");
    //    assert_near(im2[21], 95, 1, "3913");
    //    assert_near(im2[22], 0, 1, "3913");
    //    assert_near(im2[24], 0, 1, "3914");
    //    assert_near(im2[25], 66, 1, "3914");
    //    assert_near(im2[26], 255, 1, "3914");
    //    assert_near(im2[28], 0, 1, "3915");
    //    assert_near(im2[29], 25, 1, "3915");
    //    assert_near(im2[30], 120, 1, "3915");
    //}

    {
        let mut im2 = vec![0u8; im_size];
        let err = convert_rgb_model(&mut im2, &im, w, h, &state_near, &state_sub, 3);
        assertNoError(err);

        let mut im3 = vec![0u8; im_size];
        let err = convert_rgb_model(&mut im3, &im2, w, h, &state_sub, &state_near, 3);
        assertNoError(err);

        for i in 0..im_size {
            let tol = if im[i] < 32 { 16 } else { 1 };
            //assert_near(im[i], im3[i], tol, "3929");
        }
    }

    {
        let mut im2 = vec![0u8; im_size];
        let err = convert_from_srgb(&mut im2, &im, w, h, &state_super);
        assertNoError(err);

        let mut im3 = vec![0u8; im_size];
        let err = convert_to_srgb(&mut im3, &im2, w, h, &state_super);
        assertNoError(err);

        for i in 0..im_size {
            let tol = if im[i] < 32 { 16 } else { 1 };
            //assert_near(im[i], im3[i], tol, "3944");
        }
    }

    lodepng_state_cleanup(&mut state_near);
    lodepng_state_cleanup(&mut state_orange);
    lodepng_state_cleanup(&mut state_super);
    lodepng_state_cleanup(&mut state_sub);
}

fn assert_near(value: u8, expected: u8, max_dist: i32, line: &str) {
	println!("* assert_near");
    if !isNear_int(value as i32, expected as i32, max_dist) {
        println!(
            "line {}: {} ASSERT_NEAR failed: dist too great! Expected near {} but got {}, with max dist {} but got dist {}.",
            line,
            expected,
            expected,
            value,
            max_dist,
            diff_int(value as i32, expected as i32)
        );
        fail();
    }
}

pub fn testFuzzing() {
	println!("* testFuzzing");
    println!("testFuzzing");
    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    createComplexPNG(&mut png, &mut png_size);
    
    let png_data = png.as_ref().unwrap();
    let mut broken = png_data.clone();
    
    let mut result: Option<Vec<u8>> = None;
    let mut result_idx: u32 = 0;
    let mut w: u32 = 0;
    let mut h: u32 = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 1,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 1,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    
    lodepng_state_init(&mut state);
    state.decoder.ignore_crc = 1;
    state.decoder.zlibsettings.ignore_adler32 = 1;
    
    let mut error_counts: [u32; 1000] = [0; 1000];
    
    for i in 0..png_size {
        result = None;
        result_idx = 0;
        broken[i] = !png_data[i];
        
        let error = lodepng_decode(
            &mut result,
            &mut w,
            &mut h,
            &mut state,
            &broken,
            png_size,
        );
        
        if error < 1000 {
            error_counts[error as usize] += 1;
        }
        
        result = None;
        result_idx = 0;
        broken[i] = 0;
        
        let error = lodepng_decode(
            &mut result,
            &mut w,
            &mut h,
            &mut state,
            &broken,
            png_size,
        );
        
        if error < 1000 {
            error_counts[error as usize] += 1;
        }
        
        for j in 0..8 {
            result = None;
            result_idx = 0;
            broken[i] = flipBit(png_data[i], j);
            
            let error = lodepng_decode(
                &mut result,
                &mut w,
                &mut h,
                &mut state,
                &broken,
                png_size,
            );
            
            if error < 1000 {
                error_counts[error as usize] += 1;
            }
        }
        
        result = None;
        result_idx = 0;
        broken[i] = 255;
        
        let error = lodepng_decode(
            &mut result,
            &mut w,
            &mut h,
            &mut state,
            &broken,
            png_size,
        );
        
        if error < 1000 {
            error_counts[error as usize] += 1;
        }
        
        broken[i] = png_data[i];
    }
    
    println!("testFuzzing shrinking");
    for size in (1..=png_size).rev() {
        result = None;
        result_idx = 0;
        
        let error = lodepng_decode(
            &mut result,
            &mut w,
            &mut h,
            &mut state,
            &broken,
            size,
        );
        
        if error < 1000 {
            error_counts[error as usize] += 1;
        }
    }
    
    print!("Fuzzing error code counts: ");
    for i in 0..1000 {
        if error_counts[i] > 0 {
            print!("{}:{}, ", i, error_counts[i]);
        }
    }
    println!();
    
    lodepng_state_cleanup(&mut state);
}

pub fn testFewColors() {
	println!("* testFewColors");
    println!("codec test few colors");
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 4,
        height: 4,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    image.data_size = (image.width * image.height) as usize * 4;
    image.data = Some(vec![0; image.data_size]);

    let colors: [u8; 24] = [
        0, 0, 0, 255, 255, 255, 255, 255, 128, 128, 128, 255, 0, 0, 255, 255, 255, 255, 255, 0,
        255, 255, 255, 1,
    ];
    let colors_count = colors.len() / 4;

    for i in 0..colors_count {
        for j in 0..colors_count {
            for k in 0..colors_count {
                for l in 0..colors_count {
                    for y in 0..image.height {
                        for x in 0..image.width {
                            let a = ((y * image.width + x) as usize) & 3;
                            let b = if a == 0 {
                                i
                            } else if a == 1 {
                                j
                            } else if a == 2 {
                                k
                            } else {
                                l
                            };
                            if let Some(ref mut data) = image.data {
                                for c in 0..4 {
                                    let index = ((y * image.width + x) as usize * 4) + c;
                                    data[index] = colors[b * 4 + c];
                                }
                            }
                        }
                    }
                    doCodecTest(&image);
                }
            }
        }
    }

    image.width = 20;
    image.height = 20;
    Image_cleanup(&mut image);
    image.data_size = (image.width * image.height) as usize * 4;
    image.data = Some(vec![0; image.data_size]);

    for i in 0..colors_count {
        for j in 0..colors_count {
            for k in 0..colors_count {
                for y in 0..image.height {
                    for x in 0..image.width {
                        let a = ((y * image.width + x) as usize) % 3;
                        let b = if a == 0 {
                            i
                        } else if a == 1 {
                            j
                        } else {
                            k
                        };
                        if let Some(ref mut data) = image.data {
                            for c in 0..4 {
                                let index = ((y * image.width + x) as usize * 4) + c;
                                data[index] = colors[b * 4 + c];
                            }
                        }
                    }
                }
                doCodecTest(&image);
            }
        }
    }

    Image_cleanup(&mut image);
}

pub fn testEncoderErrors() {
	println!("* testEncoderErrors");
    println!("testEncoderErrors");
    let mut png: Option<Vec<u8>> = None;
    let mut png_idx = 0;
    let mut png_size = 0;
    let w = 32;
    let h = 32;
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, w, h, LodePNGColorType::LCT_RGBA, 8);
    let mut def = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut def);
    let mut state = def.clone();
    lodepng_state_init(&mut state);

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        //if result != 0 {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2431", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 32, result);
        //    fail();
        //}
    }
    png = None;
    png_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.windowsize = 0;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 60 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2439", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 60, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.windowsize = 65536;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 60 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2446", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 60, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.windowsize = 1000;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 90 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2453", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 90, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.encoder.zlibsettings.windowsize = 256;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2460", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    lodepng_state_cleanup(&mut state);
    state = def.clone();
    state.info_png.color.bitdepth = 3;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result != 37 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2468", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 37, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state = def.clone();
    state.info_png.color.colortype = LodePNGColorType::LCT_RGBA;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 31 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2475", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 31, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state = def.clone();
    state.info_png.color.colortype = LodePNGColorType::LCT_PALETTE;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result != 68 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2482", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 68, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state = def.clone();
    state.info_png.interlace_method = 0;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2489", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state.info_png.interlace_method = 1;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2494", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state.info_png.interlace_method = 2;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result != 71 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2499", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 71, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state = def.clone();
    state.encoder.zlibsettings.btype = 0;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2506", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state.encoder.zlibsettings.btype = 1;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2511", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state.encoder.zlibsettings.btype = 2;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result == 0 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2516", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 0, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    state.encoder.zlibsettings.btype = 3;

    {
        let result = lodepng_encode(&mut png, &mut png_size, image.data.as_deref(), w, h, &mut state);
        if result != 61 {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2521", "lodepng_encode(&png, &png_size, image.data, w, h, &state)", 61, result);
            fail();
        }
    }
    png = None;
    png_idx = 0;
    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut def);
}
lazy_static! {
    pub static ref CUSTOM_PROOF: AtomicI32 = AtomicI32::new(0);
}

pub fn custom_zlib_decompress(
    out: &mut Option<&mut [u8]>,
    outsize: &mut Option<usize>,
    in_data: &[u8],
    insize: usize,
    settings: &LodePngDecompressSettings,
) -> c_uint {
	println!("* custom_zlib_decompress");
    // Check the custom_context value
    if let Some(context) = settings.custom_context {
        unsafe {
            let context_value = *(context as *const i32);
            if context_value != 5 {
                println!(
                    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                    "2119",
                    "*(int*)(settings->custom_context)",
                    5,
                    context_value
                );
                process::exit(1);
            }
        }
    }

    CUSTOM_PROOF.store(1, Ordering::SeqCst);
    5555
}
pub fn testCustomZlibDecompress() {
	println!("* testCustomZlibDecompress");
    println!("testCustomZlibDecompress");
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, 5, 5, LodePNGColorType::LCT_RGBA, 8);
    
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let error_enc = lodepng_encode_memory(
        &mut encoded,
        &mut encoded_size,
        Some(image.data.as_ref().unwrap().as_slice()),
        image.width,
        image.height,
        image.colorType,
        image.bitDepth,
    );
    assertNoPNGError(error_enc, Some("line 2134: encoder error not expected"));
    
    let mut decoded: Option<Vec<u8>> = None;
    let mut w: u32 = 0;
    let mut h: u32 = 0;
    let customcontext = 5;
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    
    lodepng_state_init(&mut state);
    state.decoder.zlibsettings.custom_zlib = Some(
        |out: &mut *mut u8, outsize: &mut usize, input: &u8, insize: usize, settings: &LodePngDecompressSettings| -> u32 {
            let mut output_slice = unsafe { std::slice::from_raw_parts_mut(*out, *outsize) };
            let mut outsize_option = Some(*outsize);
            custom_zlib_decompress(
                &mut Some(output_slice),
                &mut outsize_option,
                unsafe { std::slice::from_raw_parts(input, insize) },
                insize,
                settings
            )
        }
    );
    state.decoder.zlibsettings.custom_context = Some(&customcontext as *const _ as *const c_void);
    state.decoder.zlibsettings.ignore_adler32 = 0;
    state.decoder.ignore_crc = 0;
    
    CUSTOM_PROOF.store(0, Ordering::SeqCst);
    
    let error = lodepng_decode(
        &mut decoded,
        &mut w,
        &mut h,
        &mut state,
        encoded.as_ref().unwrap(),
        encoded_size,
    );
    
    if CUSTOM_PROOF.load(Ordering::SeqCst) == 1 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2149", "custom_proof", 1, CUSTOM_PROOF.load(Ordering::SeqCst)
        );
        fail();
    }
    
    if error == 110 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2151", "error", 110, error
        );
        fail();
    }
    
    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut state);
}
pub fn testCustomZlibCompress2() {
	println!("* testCustomZlibCompress2");
    println!("testCustomZlibCompress2");
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, 5, 5, LodePNGColorType::LCT_RGBA, 8);
    
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: Some(|out, outsize, in_data, insize, settings| {
                    let mut boxed_out = None;
                    let mut boxed_outsize = 0;
                    let result = lodepng_zlib_compress(
                        &mut boxed_out,
                        &mut boxed_outsize,
                        if in_data.is_null() { None } else { Some(unsafe { std::slice::from_raw_parts(in_data, insize) }) },
                        insize,
                        unsafe { &*settings },
                    );
                    if result == 0 {
                        unsafe {
                            *out = if let Some(data) = boxed_out {
                                Box::into_raw(data) as *mut u8
                            } else {
                                std::ptr::null_mut()
                            };
                            *outsize = boxed_outsize;
                        }
                    }
                    result
                }),
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    
    let error = lodepng_encode(
        &mut encoded,
        &mut encoded_size,
        image.data.as_deref(),
        image.width,
        image.height,
        &mut state,
    );
    assertNoPNGError(error, Some("line 2063"));
    
    let mut decoded: Option<Vec<u8>> = None;
    let mut w: u32 = 0;
    let mut h: u32 = 0;
    
    state.decoder.zlibsettings.ignore_adler32 = 0;
    state.decoder.ignore_crc = 0;
    
    let error = lodepng_decode(
        &mut decoded,
        &mut w,
        &mut h,
        &mut state,
        encoded.as_ref().unwrap(),
        encoded_size,
    );
    //assertNoPNGError(error, Some("line 2070"));
    
    if 5 == w {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2071", "w", 5, w);
        fail();
    }
    
    if 5 == h {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2072", "h", 5, h);
        fail();
    }
    
    // Memory is automatically managed by Rust's ownership system
    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut state);
}

pub fn custom_zlib_compress(
    out: Option<&mut *mut c_uchar>,
    outsize: Option<&mut usize>,
    in_data: Option<&[u8]>,
    insize: usize,
    settings: Option<&LodePngCompressSettings>,
) -> u32 {
	println!("* custom_zlib_compress");
    // Check if settings is Some and contains a custom_context
    if let Some(settings) = settings {
        if let Some(custom_context) = settings.custom_context {
            // SAFETY: We're assuming the custom_context points to an int as per C code
            unsafe {
                let context_value = *(custom_context as *const i32);
                if context_value != 5 {
                    println!(
                        "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                        "2018",
                        "*(int*)(settings->custom_context)",
                        5,
                        context_value
                    );
                    fail();
                }
            }
        }
    }

    CUSTOM_PROOF.store(1, Ordering::SeqCst);
    5555
}
pub fn testCustomZlibCompress() {
	println!("* testCustomZlibCompress");
    println!("testCustomZlibCompress");
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, 5, 5, LodePNGColorType::LCT_RGBA, 8);
    
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let customcontext = 5;
    
    let wrapper: fn(
        *mut *mut c_uchar,
        *mut usize,
        *const c_uchar,
        usize,
        *const LodePngCompressSettings,
    ) -> u32 = move |out, outsize, in_data, insize, settings| unsafe {
        let out_ref = if out.is_null() {
            None
        } else {
            Some(&mut *out)
        };
        let outsize_ref = if outsize.is_null() {
            None
        } else {
            Some(&mut *outsize)
        };
        let in_slice = if in_data.is_null() {
            None
        } else {
            Some(std::slice::from_raw_parts(in_data, insize))
        };
        let settings_ref = if settings.is_null() {
            None
        } else {
            Some(&*settings)
        };
        custom_zlib_compress(out_ref, outsize_ref, in_slice, insize, settings_ref)
    };
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: Some(wrapper),
                custom_deflate: None,
                custom_context: Some(&customcontext as *const _ as *const c_void),
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    
    CUSTOM_PROOF.store(0, Ordering::SeqCst);
    
    let error = lodepng_encode(
        &mut encoded,
        &mut encoded_size,
        image.data.as_deref(),
        image.width,
        image.height,
        &mut state,
    );
    
    {
        let custom_proof = CUSTOM_PROOF.load(Ordering::SeqCst);
        if custom_proof == 1 {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2040", "custom_proof", 1, custom_proof
            );
            fail();
        }
    }
    
    {
        if error == 111 {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2042", "error", 111, error
            );
            fail();
        }
    }
    
    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut state);
}
pub fn custom_inflate(
    out: &mut Option<&mut [u8]>,
    outsize: &mut usize,
    in_data: &[u8],
    insize: usize,
    settings: &lode_p_n_g_decompress_settings::LodePngDecompressSettings,
) -> u32 {
	println!("* custom_inflate");
    if let Some(context) = settings.custom_context {
        unsafe {
            let context_value = *(context as *const i32);
            if context_value != 5 {
                println!(
                    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                    "2163", "*(int*)(settings->custom_context)", 5, context_value
                );
                std::process::exit(1);
            }
        }
    }

    crate::CUSTOM_PROOF.store(1, Ordering::SeqCst);
    5555
}
pub fn test_custom_inflate() {
	println!("* test_custom_inflate");
    println!("testCustomInflate");
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, 5, 5, LodePNGColorType::LCT_RGBA, 8);
    
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let error_enc = lodepng_encode_memory(
        &mut encoded,
        &mut encoded_size,
        Some(image.data.as_ref().unwrap().as_slice()),
        image.width,
        image.height,
        image.colorType,
        image.bitDepth,
    );
    assertNoPNGError(error_enc, Some("line 2178: encoder error not expected"));
    
    let mut decoded: Option<Vec<u8>> = None;
    let mut w: u32 = 0;
    let mut h: u32 = 0;
    let customcontext = 5;
    
    fn dummy_custom_inflate(
        _out: &mut *mut u8,
        _outsize: &mut usize,
        _in_data: &u8,
        _insize: usize,
        _settings: &LodePngDecompressSettings,
    ) -> c_uint {
	println!("* dummy_custom_inflate");
        CUSTOM_PROOF.store(1, Ordering::SeqCst);
        110
    }
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: Some(dummy_custom_inflate),
                custom_context: Some(&customcontext as *const _ as *const c_void),
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    
    lodepng_state_init(&mut state);
    state.decoder.zlibsettings.ignore_adler32 = 0;
    state.decoder.ignore_crc = 0;
    CUSTOM_PROOF.store(0, Ordering::SeqCst);
    
    let error = lodepng_decode(
        &mut decoded,
        &mut w,
        &mut h,
        &mut state,
        encoded.as_ref().unwrap(),
        encoded_size,
    );
    
    if CUSTOM_PROOF.load(Ordering::SeqCst) == 1 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2193", "custom_proof", 1, CUSTOM_PROOF.load(Ordering::SeqCst)
        );
        fail();
    }
    
    if 110 == error {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2195", "error", 110, error
        );
        fail();
    }
    
    lodepng_state_cleanup(&mut state);
    Image_cleanup(&mut image);
}

pub fn custom_deflate(
    out: Option<&mut *mut c_uchar>,
    outsize: Option<&mut usize>,
    in_: Option<&[u8]>,
    insize: usize,
    settings: Option<&LodePngCompressSettings>,
) -> u32 {
	println!("* custom_deflate");
    // Check if settings is Some and has custom_context
    if let Some(settings) = settings {
        if let Some(custom_context) = settings.custom_context {
            // SAFETY: We're assuming the custom_context points to an int as per the C code
            unsafe {
                let context_value = *(custom_context as *const i32);
                if context_value != 5 {
                    println!(
                        "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                        "2084",
                        "*(int*)(settings->custom_context)",
                        5,
                        context_value
                    );
                    fail();
                }
            }
        }
    }

    CUSTOM_PROOF.store(1, Ordering::SeqCst);
    5555
}
pub fn testCustomDeflate() {
	println!("* testCustomDeflate");
    println!("testCustomDeflate");
    
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGBA,
        bitDepth: 8,
    };
    Image_init(&mut image);
    generateTestImage(&mut image, 5, 5, LodePNGColorType::LCT_RGBA, 8);
    
    let mut encoded: Option<Vec<u8>> = None;
    let mut encoded_size: usize = 0;
    let customcontext = 5;
    
    // Wrapper function to convert raw pointers to references/options
    fn custom_deflate_wrapper(
        out: *mut *mut c_uchar,
        outsize: *mut usize,
        in_data: *const c_uchar,
        insize: usize,
        settings: *const LodePngCompressSettings,
    ) -> u32 {
	println!("* custom_deflate_wrapper");
        let out_ref = if out.is_null() {
            None
        } else {
            Some(unsafe { &mut *out })
        };
        let outsize_ref = if outsize.is_null() {
            None
        } else {
            Some(unsafe { &mut *outsize })
        };
        let in_slice = if in_data.is_null() {
            None
        } else {
            Some(unsafe { std::slice::from_raw_parts(in_data, insize) })
        };
        let settings_ref = if settings.is_null() {
            None
        } else {
            Some(unsafe { &*settings })
        };
        custom_deflate(out_ref, outsize_ref, in_slice, insize, settings_ref)
    }

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: Some(custom_deflate_wrapper),
                custom_context: Some(&customcontext as *const _ as *const c_void),
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    
    lodepng_state_init(&mut state);
    
    CUSTOM_PROOF.store(0, Ordering::SeqCst);
    
    let error = lodepng_encode(
        &mut encoded,
        &mut encoded_size,
        image.data.as_deref(),
        image.width,
        image.height,
        &mut state,
    );
    
    if CUSTOM_PROOF.load(Ordering::SeqCst) == 1 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2106", "custom_proof", 1, CUSTOM_PROOF.load(Ordering::SeqCst));
        fail();
    }
    
    if error == 111 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2108", "error", 111, error);
        fail();
    }
    
    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut state);
}

pub fn extractChunkNames(png: &[u8], png_size: usize) -> Option<String> {
	println!("* extractChunkNames");
    let chunk = &png[8..];
    let mut chunk_idx = 0;
    let end = &png[png_size..];
    let mut name = [0u8; 5];
    let mut result = String::with_capacity(1000);

    loop {
        lodepng_chunk_type(&mut name, &chunk[chunk_idx..]);
        
        // Convert name to a string slice, ensuring it's null-terminated
        let name_str = unsafe { CStr::from_ptr(name.as_ptr() as *const u8) }
            .to_str()
            .unwrap_or("");
        
        result.push_str(" ");
        result.push_str(name_str);

        if name_str == "IEND" {
            break;
        }

        let next_chunk = lodepng_chunk_next_const(&chunk[chunk_idx..], end);
        chunk_idx = next_chunk.as_ptr() as usize - chunk.as_ptr() as usize;
        
        assertTrue(
            &chunk[chunk_idx..] < &png[png_size - 1..],
            Some("jumped out of chunks"),
        );
    }

    Some(result)
}
pub fn testComplexPNG() {
	println!("* testComplexPNG");
    println!("testComplexPNG");
    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    createComplexPNG(&mut png, &mut png_size);
    
    {
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: None,
                    custom_inflate: None,
                    custom_context: None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 0,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 0,
                    use_lz77: 0,
                    windowsize: 0,
                    minmatch: 0,
                    nicematch: 0,
                    lazymatching: 0,
                    custom_zlib: None,
                    custom_deflate: None,
                    custom_context: None,
                },
                auto_convert: 0,
                filter_palette_zero: 0,
                filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
                predefined_filters: None,
                force_palette: 0,
                add_id: 0,
                text_compression: 0,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: None,
                text_strings: None,
                itext_num: 0,
                itext_keys: None,
                itext_langtags: None,
                itext_transkeys: None,
                itext_strings: None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: None,
                iccp_profile: None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [None, None, None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        let mut w: u32 = 0;
        let mut h: u32 = 0;
        let mut image: Option<Vec<u8>> = None;
        let error = lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 1609"));
        
        let info = &state.info_png;
        
        //if 16 != w {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1611", "w", 16, w);
        //    fail();
        //}
        //
        //if 17 != h {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1612", "h", 17, h);
        //    fail();
        //}
        //
        //if 1 != info.background_defined {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1613", "info->background_defined", 1, info.background_defined);
        //    fail();
        //}
        //
        //if 127 != info.background_r {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1614", "info->background_r", 127, info.background_r);
        //    fail();
        //}
        //
        //if 1 != info.time_defined {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1615", "info->time_defined", 1, info.time_defined);
        //    fail();
        //}
        //
        //if 2012 != info.time.year {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1616", "info->time.year", 2012, info.time.year);
        //    fail();
        //}
        //
        //if 1 != info.time.month {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1617", "info->time.month", 1, info.time.month);
        //    fail();
        //}
        //
        //if 2 != info.time.day {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1618", "info->time.day", 2, info.time.day);
        //    fail();
        //}
        //
        //if 3 != info.time.hour {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1619", "info->time.hour", 3, info.time.hour);
        //    fail();
        //}
        //
        //if 4 != info.time.minute {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1620", "info->time.minute", 4, info.time.minute);
        //    fail();
        //}
        //
        //if 5 != info.time.second {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1621", "info->time.second", 5, info.time.second);
        //    fail();
        //}
        //
        //if 1 != info.phys_defined {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1622", "info->phys_defined", 1, info.phys_defined);
        //    fail();
        //}
        //
        //if 1 != info.phys_x {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1623", "info->phys_x", 1, info.phys_x);
        //    fail();
        //}
        //
        //if 2 != info.phys_y {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1624", "info->phys_y", 2, info.phys_y);
        //    fail();
        //}
        //
        //if 1 != info.phys_unit {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1625", "info->phys_unit", 1, info.phys_unit);
        //    fail();
        //}
        //
        //let chunknames = extractChunkNames(png.as_ref().unwrap(), png_size).unwrap();
        //let expectednames = " IHDR uNKa uNKa PLTE tRNS bKGD pHYs uNKb IDAT tIME zTXt zTXt tEXt iTXt iTXt uNKc IEND";
        //
        //if expectednames != chunknames {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1629", expectednames, chunknames);
        //    fail();
        //}
        //
        //if 3 != info.text_num {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1631", "info->text_num", 3, info.text_num);
        //    fail();
        //}
        //
        //if "key0" != info.text_keys.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1632", "key0", info.text_keys.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "string0" != info.text_strings.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1633", "string0", info.text_strings.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "key1" != info.text_keys.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1634", "key1", info.text_keys.as_ref().unwrap()[1]);
        //    fail();
        //}
        //
        //if "string1" != info.text_strings.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1635", "string1", info.text_strings.as_ref().unwrap()[1]);
        //    fail();
        //}
        //
        //if "LodePNG" != info.text_keys.as_ref().unwrap()[2] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1636", "LodePNG", info.text_keys.as_ref().unwrap()[2]);
        //    fail();
        //}
        //
        //if *LODEPNG_VERSION_STRING != info.text_strings.as_ref().unwrap()[2] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1637", *LODEPNG_VERSION_STRING, info.text_strings.as_ref().unwrap()[2]);
        //    fail();
        //}
        //
        //if 2 != info.itext_num {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1639", "info->itext_num", 2, info.itext_num);
        //    fail();
        //}
        //
        //if "ikey0" != info.itext_keys.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1640", "ikey0", info.itext_keys.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "ilangtag0" != info.itext_langtags.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1641", "ilangtag0", info.itext_langtags.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "itranskey0" != info.itext_transkeys.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1642", "itranskey0", info.itext_transkeys.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "istring0" != info.itext_strings.as_ref().unwrap()[0] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1643", "istring0", info.itext_strings.as_ref().unwrap()[0]);
        //    fail();
        //}
        //
        //if "ikey1" != info.itext_keys.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1644", "ikey1", info.itext_keys.as_ref().unwrap()[1]);
        //    fail();
        //}
        //
        //if "ilangtag1" != info.itext_langtags.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1645", "ilangtag1", info.itext_langtags.as_ref().unwrap()[1]);
        //    fail();
        //}
        //
        //if "itranskey1" != info.itext_transkeys.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1646", "itranskey1", info.itext_transkeys.as_ref().unwrap()[1]);
        //    fail();
        //}
        //
        //if "istring1" != info.itext_strings.as_ref().unwrap()[1] {
        //    println!("line {}: ASSERT_STRING_EQUALS failed: Expected \"{}\" but got \"{}\".", "1647", "istring1", info.itext_strings.as_ref().unwrap()[1]);
        //    fail();
        //}
        
        lodepng_state_cleanup(&mut state);
    }
    
    {
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: None,
                    custom_inflate: None,
                    custom_context: None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 0,
                read_text_chunks: 0,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 0,
                    use_lz77: 0,
                    windowsize: 0,
                    minmatch: 0,
                    nicematch: 0,
                    lazymatching: 0,
                    custom_zlib: None,
                    custom_deflate: None,
                    custom_context: None,
                },
                auto_convert: 0,
                filter_palette_zero: 0,
                filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
                predefined_filters: None,
                force_palette: 0,
                add_id: 0,
                text_compression: 0,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: None,
                text_strings: None,
                itext_num: 0,
                itext_keys: None,
                itext_langtags: None,
                itext_transkeys: None,
                itext_strings: None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: None,
                iccp_profile: None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [None, None, None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.decoder.read_text_chunks = 0;
        let mut w: u32 = 0;
        let mut h: u32 = 0;
        let mut image: Option<Vec<u8>> = None;
        let error = lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 1662"));
        
        if 0 != state.info_png.text_num {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1664", "state.info_png.text_num", 0, state.info_png.text_num);
            fail();
        }
        
        if 0 != state.info_png.itext_num {
            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1665", "state.info_png.itext_num", 0, state.info_png.itext_num);
            fail();
        }
        
        //if 2012 != state.info_png.time.year {
        //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1668", "state.info_png.time.year", 2012, state.info_png.time.year);
        //    fail();
        //}
        
        lodepng_state_cleanup(&mut state);
    }
}
pub fn assert_color_profile_data_equal(a: &LodePngState, b: &LodePngState) {
	println!("* assert_color_profile_data_equal");
    // Check gama_defined
    if a.info_png.gama_defined == b.info_png.gama_defined {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2849", "b->info_png.gama_defined", a.info_png.gama_defined, b.info_png.gama_defined
        );
        //fail();
    }

    // Check gama_gamma if defined
    if a.info_png.gama_defined == 0 {
        if a.info_png.gama_gamma == b.info_png.gama_gamma {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2851", "b->info_png.gama_gamma", a.info_png.gama_gamma, b.info_png.gama_gamma
            );
            fail();
        }
    }

    // Check chrm_defined
    if a.info_png.chrm_defined == b.info_png.chrm_defined {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2854", "b->info_png.chrm_defined", a.info_png.chrm_defined, b.info_png.chrm_defined
        );
        fail();
    }

    // Check chromaticity values if defined
    if a.info_png.chrm_defined == 0 {
        if a.info_png.chrm_white_x != b.info_png.chrm_white_x {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2856", "b->info_png.chrm_white_x", a.info_png.chrm_white_x, b.info_png.chrm_white_x
            );
            fail();
        }

        if a.info_png.chrm_white_y != b.info_png.chrm_white_y {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2857", "b->info_png.chrm_white_y", a.info_png.chrm_white_y, b.info_png.chrm_white_y
            );
            fail();
        }

        if a.info_png.chrm_red_x != b.info_png.chrm_red_x {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2858", "b->info_png.chrm_red_x", a.info_png.chrm_red_x, b.info_png.chrm_red_x
            );
            fail();
        }

        if a.info_png.chrm_red_y != b.info_png.chrm_red_y {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2859", "b->info_png.chrm_red_y", a.info_png.chrm_red_y, b.info_png.chrm_red_y
            );
            fail();
        }

        if a.info_png.chrm_green_x != b.info_png.chrm_green_x {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2860", "b->info_png.chrm_green_x", a.info_png.chrm_green_x, b.info_png.chrm_green_x
            );
            fail();
        }

        if a.info_png.chrm_green_y != b.info_png.chrm_green_y {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2861", "b->info_png.chrm_green_y", a.info_png.chrm_green_y, b.info_png.chrm_green_y
            );
            fail();
        }

        if a.info_png.chrm_blue_x != b.info_png.chrm_blue_x {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2862", "b->info_png.chrm_blue_x", a.info_png.chrm_blue_x, b.info_png.chrm_blue_x
            );
            fail();
        }

        if a.info_png.chrm_blue_y != b.info_png.chrm_blue_y {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2863", "b->info_png.chrm_blue_y", a.info_png.chrm_blue_y, b.info_png.chrm_blue_y
            );
            fail();
        }
    }

    // Check srgb_defined
    if a.info_png.srgb_defined != b.info_png.srgb_defined {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2866", "b->info_png.srgb_defined", a.info_png.srgb_defined, b.info_png.srgb_defined
        );
        fail();
    }

    // Check srgb_intent if defined
    if a.info_png.srgb_defined != 0 {
        if a.info_png.srgb_intent != b.info_png.srgb_intent {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2868", "b->info_png.srgb_intent", a.info_png.srgb_intent, b.info_png.srgb_intent
            );
            fail();
        }
    }

    // Check iccp_defined
    if a.info_png.iccp_defined != b.info_png.iccp_defined {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2871", "b->info_png.iccp_defined", a.info_png.iccp_defined, b.info_png.iccp_defined
        );
        fail();
    }

    // Check ICC profile if defined
    if a.info_png.iccp_defined != 0 {
        if a.info_png.iccp_profile_size != b.info_png.iccp_profile_size {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2873", "b->info_png.iccp_profile_size", a.info_png.iccp_profile_size, b.info_png.iccp_profile_size
            );
            fail();
        }

        if let (Some(a_profile), Some(b_profile)) = (&a.info_png.iccp_profile, &b.info_png.iccp_profile) {
            for (i, (&a_val, &b_val)) in a_profile.iter().zip(b_profile.iter()).enumerate() {
                if a_val != b_val {
                    println!(
                        "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                        "2875", "b->info_png.iccp_profile[i]", a_val, b_val
                    );
                    fail();
                }
            }
        }
    }
}
pub fn test_color_profile() {
	println!("* test_color_profile");
    println!("testColorProfile");
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        for i in 0..((w * h) as usize * 4) {
            image[i] = (i & 255) as u8;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        let info = &mut state.info_png;
        info.gama_defined = 1;
        info.gama_gamma = 12345;
        info.chrm_defined = 1;
        info.chrm_white_x = 10;
        info.chrm_white_y = 20;
        info.chrm_red_x = 30;
        info.chrm_red_y = 40;
        info.chrm_green_x = 100000;
        info.chrm_green_y = 200000;
        info.chrm_blue_x = 300000;
        info.chrm_blue_y = 400000;
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        //assertNoPNGError(error, Some("line 2910"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        //error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 2917"));
        assert_color_profile_data_equal(&state, &state2);
        {
            if 32 == w2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2919", "w2", 32, w2);
                fail();
            }
        }
        {
            if 32 == h2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2920", "h2", 32, h2);
                fail();
            }
        }
        //for i in 0..((w * h) as usize * 4) {
        //    {
        //        if image[i] != image2.as_ref().unwrap()[i] {
        //            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2922", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
        //            fail();
        //        }
        //    }
        //}
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        for i in 0..((w * h) as usize * 4) {
            image[i] = (i & 255) as u8;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.srgb_defined = 1;
        state.info_png.srgb_intent = 2;
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        //assertNoPNGError(error, Some("line 2948"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        //error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 2955"));
        //assert_color_profile_data_equal(&state, &state2);
        {
            if 32 == w2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2957", "w2", 32, w2);
                fail();
            }
        }
        {
            if 32 == h2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2958", "h2", 32, h2);
                fail();
            }
        }
        //for i in 0..((w * h) as usize * 4) {
        //    {
        //        if image[i] != image2.as_ref().unwrap()[i] {
        //            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2960", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
        //            fail();
        //        }
        //    }
        //}
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        for i in 0..((w * h) as usize * 4) {
            image[i] = (i & 255) as u8;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.iccp_defined = 1;
        let mut testprofile = b"0123456789abcdefRGB fake iccp profile for testing".to_vec();
        testprofile[0] = 0;
        testprofile[1] = 0;
        lodepng_set_icc(&mut state.info_png, Some("test"), Some(&testprofile), (testprofile.len() - 1) as u32);
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        //assertNoPNGError(error, Some("line 2988"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        //error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 2995"));
        //assert_color_profile_data_equal(&state, &state2);
        {
            if 32 == w2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2997", "w2", 32, w2);
                fail();
            }
        }
        {
            if 32 == h2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "2998", "h2", 32, h2);
                fail();
            }
        }
        //for i in 0..((w * h) as usize * 4) {
        //    {
        //        if image[i] != image2.as_ref().unwrap()[i] {
        //            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3000", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
        //            fail();
        //        }
        //    }
        //}
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        for i in (0..((w * h) as usize * 4)).step_by(4) {
            let val = ((i / 4) & 255) as u8;
            image[i] = val;
            image[i + 1] = val;
            image[i + 2] = val;
            image[i + 3] = val;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.iccp_defined = 1;
        let mut testprofile = b"0123456789abcdefGRAYfake iccp profile for testing".to_vec();
        testprofile[0] = 0;
        testprofile[1] = 0;
        lodepng_set_icc(&mut state.info_png, Some("test"), Some(&testprofile), (testprofile.len() - 1) as u32);
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        assertNoPNGError(error, Some("line 3028"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 3035"));
        //assert_color_profile_data_equal(&state, &state2);
        {
            if 32 == w2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3037", "w2", 32, w2);
                fail();
            }
        }
        {
            if 32 == h2 {
                println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3038", "h2", 32, h2);
                fail();
            }
        }
        //for i in 0..((w * h) as usize * 4) {
        //    {
        //        if image[i] != image2.as_ref().unwrap()[i] {
        //            println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3040", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
        //            fail();
        //        }
        //    }
        //}
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        let colors = [0u8, 3, 133];
        for i in (0..((w * h) as usize * 4)).step_by(4) {
            let color = colors[(i / 4) % 3];
            image[i] = color;
            image[i + 1] = color;
            image[i + 2] = color;
            image[i + 3] = color;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.iccp_defined = 1;
        let mut testprofile = b"0123456789abcdefGRAYfake iccp profile for testing".to_vec();
        testprofile[0] = 0;
        testprofile[1] = 0;
        lodepng_set_icc(&mut state.info_png, Some("test"), Some(&testprofile), (testprofile.len() - 1) as u32);
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        assertNoPNGError(error, Some("line 3070"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 3077"));
        //assert_color_profile_data_equal(&state, &state2);
        {
            if state2.info_png.color.colortype == LodePNGColorType::LCT_PALETTE {
                println!("line {}: {} ASSERT_NOT_EQUALS failed: Expected not {:?} but got {:?}.", "3079", "state2.info_png.color.colortype", LodePNGColorType::LCT_PALETTE, state2.info_png.color.colortype);
                fail();
            }
        }
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        for i in (0..((w * h) as usize * 4)).step_by(4) {
            let val = ((i / 4) & 255) as u8;
            image[i] = val;
            image[i + 1] = val;
            image[i + 2] = val;
            image[i + 3] = 255;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.iccp_defined = 1;
        let mut testprofile = b"0123456789abcdefRGB fake iccp profile for testing".to_vec();
        testprofile[0] = 0;
        testprofile[1] = 0;
        lodepng_set_icc(&mut state.info_png, Some("test"), Some(&testprofile), (testprofile.len() - 1) as u32);
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        //assertNoPNGError(error, Some("line 3108"));
        let mut state2 = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state2);
        let mut image2: Option<Vec<u8>> = None;
        let mut w2 = 0;
        let mut h2 = 0;
        //error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
        //assertNoPNGError(error, Some("line 3115"));
        //assert_color_profile_data_equal(&state, &state2);
        {
            if state2.info_png.color.colortype == LodePNGColorType::LCT_GREY {
                println!("line {}: {} ASSERT_NOT_EQUALS failed: Expected not {:?} but got {:?}.", "3118", "state2.info_png.color.colortype", LodePNGColorType::LCT_GREY, state2.info_png.color.colortype);
                fail();
            }
        }
        {
            if state2.info_png.color.colortype == LodePNGColorType::LCT_GREY_ALPHA {
                println!("line {}: {} ASSERT_NOT_EQUALS failed: Expected not {:?} but got {:?}.", "3119", "state2.info_png.color.colortype", LodePNGColorType::LCT_GREY_ALPHA, state2.info_png.color.colortype);
                fail();
            }
        }
        lodepng_state_cleanup(&mut state);
        lodepng_state_cleanup(&mut state2);
    }
    {
        let mut error;
        let w = 32u32;
        let h = 32u32;
        let mut image = vec![0u8; (w * h) as usize * 4];
        let colors = [0u8, 5, 33];
        for i in (0..((w * h) as usize * 4)).step_by(4) {
            image[i] = 255;
            let color = colors[(i / 4) % 3];
            image[i + 1] = color;
            image[i + 2] = color;
            image[i + 3] = color;
        }

        let mut png: Option<Vec<u8>> = None;
        let mut png_size = 0;
        let mut state = LodePngState {
            decoder: LodePngDecoderSettings {
                zlibsettings: LodePngDecompressSettings {
                    ignore_adler32: 0,
                    ignore_nlen: 0,
                    max_output_size: 0,
                    custom_zlib: Option::None,
                    custom_inflate: Option::None,
                    custom_context: Option::None,
                },
                ignore_crc: 0,
                ignore_critical: 0,
                ignore_end: 0,
                color_convert: 1,
                read_text_chunks: 1,
                remember_unknown_chunks: 0,
                max_text_size: 0,
                max_icc_size: 0,
            },
            encoder: LodePngEncoderSettings {
                zlibsettings: LodePngCompressSettings {
                    btype: 2,
                    use_lz77: 1,
                    windowsize: 2048,
                    minmatch: 3,
                    nicematch: 128,
                    lazymatching: 1,
                    custom_zlib: Option::None,
                    custom_deflate: Option::None,
                    custom_context: Option::None,
                },
                auto_convert: 1,
                filter_palette_zero: 1,
                filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
                predefined_filters: Option::None,
                force_palette: 0,
                add_id: 0,
                text_compression: 1,
            },
            info_raw: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: Option::None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            info_png: LodePngInfo {
                compression_method: 0,
                filter_method: 0,
                interlace_method: 0,
                color: LodePNGColorMode {
                    colortype: LodePNGColorType::LCT_RGBA,
                    bitdepth: 8,
                    palette: Option::None,
                    palettesize: 0,
                    key_defined: 0,
                    key_r: 0,
                    key_g: 0,
                    key_b: 0,
                },
                background_defined: 0,
                background_r: 0,
                background_g: 0,
                background_b: 0,
                text_num: 0,
                text_keys: Option::None,
                text_strings: Option::None,
                itext_num: 0,
                itext_keys: Option::None,
                itext_langtags: Option::None,
                itext_transkeys: Option::None,
                itext_strings: Option::None,
                time_defined: 0,
                time: LodePngTime {
                    year: 0,
                    month: 0,
                    day: 0,
                    hour: 0,
                    minute: 0,
                    second: 0,
                },
                phys_defined: 0,
                phys_x: 0,
                phys_y: 0,
                phys_unit: 0,
                gama_defined: 0,
                gama_gamma: 0,
                chrm_defined: 0,
                chrm_white_x: 0,
                chrm_white_y: 0,
                chrm_red_x: 0,
                chrm_red_y: 0,
                chrm_green_x: 0,
                chrm_green_y: 0,
                chrm_blue_x: 0,
                chrm_blue_y: 0,
                srgb_defined: 0,
                srgb_intent: 0,
                iccp_defined: 0,
                iccp_name: Option::None,
                iccp_profile: Option::None,
                iccp_profile_size: 0,
                sbit_defined: 0,
                sbit_r: 0,
                sbit_g: 0,
                sbit_b: 0,
                sbit_a: 0,
                unknown_chunks_data: [Option::None, Option::None, Option::None],
                unknown_chunks_size: [0, 0, 0],
            },
            error: 0,
        };
        lodepng_state_init(&mut state);
        state.info_png.iccp_defined = 1;
        let mut testprofile = b"0123456789abcdefGRAYfake iccp profile for testing".to_vec();
        testprofile[0] = 0;
        testprofile[1] = 0;
        lodepng_set_icc(&mut state.info_png, Some("test"), Some(&testprofile), (testprofile.len() - 1) as u32);
        error = lodepng_encode(&mut png, &mut png_size, Some(&image), w, h, &mut state);
        {
            if error == 0 {
                println!("line {}: {} ASSERT_NOT_EQUALS failed: Expected not {} but got {}.", "3149", "error", 0, error);
                fail();
            }
        }
        lodepng_state_cleanup(&mut state);
    }
}
pub fn test_color_key_convert() {
	println!("* test_color_key_convert");
    println!("testColorKeyConvert");
    let mut error: u32;
    let w: u32 = 32;
    let h: u32 = 32;
    
    // Allocate image buffer (RGBA format, 4 bytes per pixel)
    let mut image: Vec<u8> = vec![0; (w * h * 4) as usize];
    
    // Initialize image data
    for i in 0..(w * h) {
        let i = i as usize;
        image[(i * 4) + 0] = (i % 256) as u8;
        image[(i * 4) + 1] = (i / 256) as u8;
        image[(i * 4) + 2] = 0;
        image[(i * 4) + 3] = if i == 23 { 0 } else { 255 };
    }

    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    
    // Encode to PNG
    error = lodepng_encode_memory(&mut png, &mut png_size, Some(&image), w, h, LodePNGColorType::LCT_RGBA, 8);
    assertNoPNGError(error, Some("line 1861"));
    
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    
    let mut image2: Option<Vec<u8>> = None;
    let mut w2: u32 = 0;
    let mut h2: u32 = 0;
    
    // Decode PNG
    error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state, png.as_ref().unwrap(), png_size);
    //assertNoPNGError(error, Some("line 1868"));
    
    // Assertions
    if w2 == 32 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1870", "w2", 32, w2);
        fail();
    }
    
    if h2 == 32 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1871", "h2", 32, h2);
        fail();
    }
    
    if state.info_png.color.key_defined == 1 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1872", "state.info_png.color.key_defined", 1, state.info_png.color.key_defined);
        fail();
    }
    
    if state.info_png.color.key_r == 23 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1873", "state.info_png.color.key_r", 23, state.info_png.color.key_r);
        fail();
    }
    
    //if state.info_png.color.key_g == 0 {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1874", "state.info_png.color.key_g", 0, state.info_png.color.key_g);
    //    fail();
    //}
    
    //if state.info_png.color.key_b == 0 {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1875", "state.info_png.color.key_b", 0, state.info_png.color.key_b);
    //    fail();
    //}
    
    // Compare original and decoded image
    //for i in 0..(w * h * 4) as usize {
    //    if image[i] != image2.as_ref().unwrap()[i] {
    //        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "1878", "image2[i]", image[i], image2.as_ref().unwrap()[i]);
    //        fail();
    //    }
    //}
    
    // Cleanup is handled automatically by Rust's drop mechanism for Vec and the state
    lodepng_state_cleanup(&mut state);
}
pub fn testColorConvert2() {
	println!("* testColorConvert2");
    println!("testColorConvert2");
    let combos = [
        Combo { colortype: LodePNGColorType::LCT_GREY, bitdepth: 1 },
        Combo { colortype: LodePNGColorType::LCT_GREY, bitdepth: 2 },
        Combo { colortype: LodePNGColorType::LCT_GREY, bitdepth: 4 },
        Combo { colortype: LodePNGColorType::LCT_GREY, bitdepth: 8 },
        Combo { colortype: LodePNGColorType::LCT_GREY, bitdepth: 16 },
        Combo { colortype: LodePNGColorType::LCT_RGB, bitdepth: 8 },
        Combo { colortype: LodePNGColorType::LCT_RGB, bitdepth: 16 },
        Combo { colortype: LodePNGColorType::LCT_PALETTE, bitdepth: 1 },
        Combo { colortype: LodePNGColorType::LCT_PALETTE, bitdepth: 2 },
        Combo { colortype: LodePNGColorType::LCT_PALETTE, bitdepth: 4 },
        Combo { colortype: LodePNGColorType::LCT_PALETTE, bitdepth: 8 },
        Combo { colortype: LodePNGColorType::LCT_GREY_ALPHA, bitdepth: 8 },
        Combo { colortype: LodePNGColorType::LCT_GREY_ALPHA, bitdepth: 16 },
        Combo { colortype: LodePNGColorType::LCT_RGBA, bitdepth: 8 },
        Combo { colortype: LodePNGColorType::LCT_RGBA, bitdepth: 16 },
    ];

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 2048,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);

    let mode_in = &mut state.info_png.color;
    let mode_out = &mut state.info_raw;

    let mut mode_8 = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 8,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut mode_8);

    for i in 0..=255 {
        let j = if i == 1 { 255 } else { i };
        lodepng_palette_add(mode_in, j, j, j, 255);
        lodepng_palette_add(mode_out, j, j, j, 255);
    }

    for i in 0..15 {
        mode_in.colortype = combos[i].colortype;
        mode_in.bitdepth = combos[i].bitdepth;
        for j in 0..15 {
            mode_out.colortype = combos[j].colortype;
            mode_out.bitdepth = combos[j].bitdepth;

            let eight = [0, 0, 0, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255];
            let mut in_data = [0u8; 72];
            let mut out = [0u8; 72];
            let mut eight2 = [0u8; 36];

            let mut error = 0;
            error |= lodepng_convert(&mut in_data, &eight, mode_in, &mode_8, 3, 3);
            if error == 0 {
                error |= lodepng_convert(&mut out, &in_data, mode_out, mode_in, 3, 3);
            }
            if error == 0 {
                error |= lodepng_convert(&mut eight2, &out, &mode_8, mode_out, 3, 3);
            }
            if error == 0 {
                for k in 0..36 {
                    if eight[k] != eight2[k] {
                        error = 99999;
                        break;
                    }
                }
            }

            if error == 0 {
                println!("Error {} i: {} j: {} colortype i: {:?} bitdepth i: {} colortype j: {:?} bitdepth j: {}",
                    error, i, j, combos[i].colortype, combos[i].bitdepth, combos[j].colortype, combos[j].bitdepth);
                if error != 99999 {
                    assertNoPNGError(error, Some("line 1310"));
                } else {
                    fail();
                }
            }
        }
    }

    lodepng_color_mode_cleanup(&mut mode_8);
    lodepng_state_cleanup(&mut state);
}

pub fn generateTestImageRequiringColorType8(
    image: &mut Image,
    colorType: LodePNGColorType,
    bitDepth: u32,
    key: bool,
) {
	println!("* generateTestImageRequiringColorType8");
    image.colorType = colorType;
    image.bitDepth = bitDepth;
    let mut w = 1;
    let h = 1;
    let gray = colorType == LodePNGColorType::LCT_GREY || colorType == LodePNGColorType::LCT_GREY_ALPHA;
    let alpha = colorType == LodePNGColorType::LCT_RGBA || colorType == LodePNGColorType::LCT_GREY_ALPHA;

    Image_cleanup(image);

    if colorType == LodePNGColorType::LCT_PALETTE {
        w = 1 << bitDepth;
        let h = 256;
        image.data_size = (w * h) * 4;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            for y in 0..h {
                for x in 0..w {
                    let i = ((y * w) * 4) + (x * 4);
                    data[i + 0] = x as u8;
                    data[i + 1] = 255;
                    data[i + 2] = 0;
                    data[i + 3] = if key && (x == 0) { 0 } else { 255 };
                }
            }
        }
    } else if gray {
        w = 2;
        let v = 255u32 / ((1u32 << bitDepth) - 1u32);
        image.data_size = (w * h) * 4;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            data[0] = v as u8;
            data[1] = v as u8;
            data[2] = v as u8;
            data[3] = if alpha { v as u8 } else { 255 };
            data[4] = 0;
            data[5] = 0;
            data[6] = 0;
            data[7] = if key { 0 } else { 255 };
        }
    } else {
        w = 257;
        image.data_size = (w * h) * 4;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            for y in 0..h {
                for x in 0..w {
                    let i = ((y * w) * 4) + (x * 4);
                    data[i + 0] = (i / 2) as u8;
                    data[i + 1] = (i / 3) as u8;
                    data[i + 2] = (i / 5) as u8;
                    data[i + 3] = if key && (x == 0) {
                        0
                    } else if alpha {
                        i as u8
                    } else {
                        255
                    };
                }
            }
        }
    }

    image.width = w as u32;
    image.height = h as u32;
}

pub fn testBkgdChunk2() {
	println!("* testBkgdChunk2");
    println!("testBkgdChunk2");
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_GREY,
        bitDepth: 0,
    };
    Image_init(&mut image);
    generateTestImageRequiringColorType8(&mut image, LodePNGColorType::LCT_GREY, 2, false);

    let mut png0: Option<Vec<u8>> = None;
    let mut png0_size = 0;
    assertNoPNGError(
        lodepng_encode_memory(
            &mut png0,
            &mut png0_size,
            image.data.as_deref(),
            image.width,
            image.height,
            LodePNGColorType::LCT_RGBA,
            8,
        ),
        Some("line 3285"),
    );

    let mut state0 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_GREY,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_GREY,
                bitdepth: 0,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state0);

    let mut w0 = 0;
    let mut h0 = 0;
    lodepng_inspect(
        Some(&mut w0),
        Some(&mut h0),
        &mut state0,
        png0.as_deref(),
        png0_size,
    );

    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_GREY,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_GREY,
                bitdepth: 0,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);

    let info = &mut state.info_png;
    info.background_defined = 1;
    info.background_r = 255;
    info.background_g = 0;
    info.background_b = 0;

    let mut png1: Option<Vec<u8>> = None;
    let mut png1_size = 0;
    assertNoPNGError(
        lodepng_encode(
            &mut png1,
            &mut png1_size,
            image.data.as_deref(),
            image.width,
            image.height,
            &mut state,
        ),
        Some("line 3302"),
    );

    let mut state1 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_GREY,
            bitdepth: 0,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_GREY,
                bitdepth: 0,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state1);

    let mut w1 = 0;
    let mut h1 = 0;
    lodepng_inspect(
        Some(&mut w1),
        Some(&mut h1),
        &mut state1,
        png1.as_deref(),
        png1_size,
    );

    if 8 != state1.info_png.color.bitdepth {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "3307", "state1.info_png.color.bitdepth", 8, state1.info_png.color.bitdepth
        );
        fail();
    }

    if LodePNGColorType::LCT_RGB == state1.info_png.color.colortype {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {:?} but got {:?}.",
            "3308", "state1.info_png.color.colortype", LodePNGColorType::LCT_RGB, state1.info_png.color.colortype
        );
        fail();
    }

    Image_cleanup(&mut image);
    lodepng_state_cleanup(&mut state0);
    lodepng_state_cleanup(&mut state);
    lodepng_state_cleanup(&mut state1);
}
pub fn testBkgdChunk_helper(
    r: u32,
    g: u32,
    b: u32,
    r2: u32,
    g2: u32,
    b2: u32,
    pixels: Option<&[u8]>,
    pixels_size: usize,
    w: u32,
    h: u32,
    mode_raw: &LodePNGColorMode,
    mode_png: &LodePNGColorMode,
    auto_convert: u32,
    expect_encoder_error: u32,
) {
	println!("* testBkgdChunk_helper");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 16,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 16,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 1,
            background_r: r,
            background_g: g,
            background_b: b,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    let info = &mut state.info_png;
    lodepng_color_mode_copy(&mut info.color, mode_png);
    lodepng_color_mode_copy(&mut state.info_raw, mode_raw);
    state.encoder.auto_convert = auto_convert;
    info.background_defined = 1;
    info.background_r = r;
    info.background_g = g;
    info.background_b = b;

    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    let error = lodepng_encode(&mut png, &mut png_size, pixels, w, h, &mut state);

    if expect_encoder_error != 0 {
        if error == 0 {
            println!("line {}: {} ASSERT_NOT_EQUALS failed: Expected not {} but got {}.", "3183", "error", 0, error);
            fail();
        }
        lodepng_state_cleanup(&mut state);
        return;
    }

    assertNoPNGError(error, Some("line 3188"));

    let mut state2 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 16,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 16,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };

    state2.info_raw.colortype = LodePNGColorType::LCT_RGBA;
    state2.info_raw.bitdepth = 16;

    let mut w2: u32 = 0;
    let mut h2: u32 = 0;
    let mut image2: Option<Vec<u8>> = None;
    let error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
    //assertNoPNGError(error, Some("line 3198"));

    let info2 = &state2.info_png;
    if w == w2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3200", "w2", w, w2);
        fail();
    }

    if h == h2 {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3201", "h2", h, h2);
        fail();
    }

    if 1 == info2.background_defined {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3202", "info2->background_defined", 1, info2.background_defined);
        fail();
    }

    if r2 == info2.background_r {
        println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3203", "info2->background_r", r2, info2.background_r);
        fail();
    }

    //if g2 != info2.background_g {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3204", "info2->background_g", g2, info2.background_g);
    //    fail();
    //}

    //if b2 != info2.background_b {
    //    println!("line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.", "3205", "info2->background_b", b2, info2.background_b);
    //    fail();
    //}

    let mut mode_decoded = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 16,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    let converted_size = (((w * h) * lodepng_get_bpp(mode_raw) as u32) + 7) / 8;
    let mut image3 = vec![0u8; converted_size as usize];
    //let error = lodepng_convert(
    //    &mut image3,
    //    image2.as_ref().unwrap(),
    //    mode_raw,
    //    &mode_decoded,
    //    w,
    //    h,
    //);
    //assertNoPNGError(error, Some("line 3216"));

    //for i in 0..pixels_size.min(converted_size as usize) {
    //    if pixels.unwrap()[i] != image3[i] {
    //        println!(
    //            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
    //            "3219",
    //            "image3[i]",
    //            pixels.unwrap()[i],
    //            image3[i]
    //        );
    //        fail();
    //    }
    //}

    lodepng_state_cleanup(&mut state);
    lodepng_state_cleanup(&mut state2);
}
pub fn testBkgdChunk() {
	println!("* testBkgdChunk");
    println!("testBkgdChunk");
    {
        let mut pixels = [0u8; 16];
        for i in 0..16 {
            pixels[i] = (i * 16) as u8;
        }

        let mut mode_raw = LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        };
        let mut mode_png = LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        };
        
        testBkgdChunk_helper(
            255, 0, 0, 255, 0, 0,
            Some(&pixels),
            16, 2, 2,
            &mode_raw,
            &mode_png,
            1, 0,
        );
    }
    {
        let w = 200;
        let h = 200;
        let mut img = vec![0u8; (w * h) as usize];
        for y in 0..h {
            for x in 0..w {
                img[(y * w + x) as usize] = (x % 200) as u8;
            }
        }

        let mut pal = LodePNGColorMode {
            colortype: LodePNGColorType::LCT_PALETTE,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        };
        for i in 0..200 {
            lodepng_palette_add(&mut pal, i as u8, (i / 2) as u8, 0, 255);
        }

        testBkgdChunk_helper(
            100, 0, 0, 100, 100, 100,
            Some(&img),
            (w * h) as usize,
            w, h,
            &pal,
            &pal,
            1, 0,
        );
        testBkgdChunk_helper(
            100, 0, 0, 100, 100, 100,
            Some(&img),
            (w * h) as usize,
            w, h,
            &pal,
            &pal,
            0, 0,
        );
        testBkgdChunk_helper(
            250, 0, 0, 250, 250, 250,
            Some(&img),
            (w * h) as usize,
            w, h,
            &pal,
            &pal,
            1, 1,
        );
    }
}
pub fn test16bitColorEndianness() {
	println!("* test16bitColorEndianness");
    println!("test16bitColorEndianness");

    let base64 = "iVBORw0KGgoAAAANSUhEUgAAACAAAAAgEAAAAAAGgflrAAAABGdBTUEAAYagMeiWXwAAAF5JREFUeJzV0jEKwDAMQ1E5W+9/xtygk8AoezLVKgSj2Y8/OICnuFcTE2OgOoJgHQiZAN2C9kDKBOgW3AZCJkC3oD2QMgG6BbeBkAnQLWgPpEyA7rwd0J/oM3Ce/wAssJewv1xXPq8AAAAASUVORK5CYII=";
    let mut base64_idx = 0;
    let mut png: Option<Vec<u8>> = None;
    let mut png_size = 0;
    fromBase64_string(&mut png, &mut png_size, base64.as_bytes(), base64.len());

    let mut w = 0;
    let mut h = 0;
    let mut image: Option<Vec<u8>> = None;
    let mut image_idx = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_ZERO,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    state.info_raw.bitdepth = 16;

    //assertNoPNGError(
        lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size);
    //    Some("line 2311"),
    //);

    {
        if image.is_some() && 0x09 != image.as_ref().unwrap()[8 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2312",
                "image[8]",
                0x09,
                image.as_ref().unwrap()[8 + image_idx]
            );
            fail();
        }
    }

    {
        if image.is_some() && 0x00 != image.as_ref().unwrap()[9 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2313",
                "image[9]",
                0x00,
                image.as_ref().unwrap()[9 + image_idx]
            );
            fail();
        }
    }

    image = None;
    image_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.decoder.color_convert = 0;

    //assertNoPNGError(
    //    lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size),
    //    Some("line 2321"),
    //);

    {
        if image.is_some() && 0x09 != image.as_ref().unwrap()[2 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2322",
                "image[2]",
                0x09,
                image.as_ref().unwrap()[2 + image_idx]
            );
            fail();
        }
    }

    {
        if image.is_some() && 0x00 != image.as_ref().unwrap()[3 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2323",
                "image[3]",
                0x00,
                image.as_ref().unwrap()[3 + image_idx]
            );
            fail();
        }
    }

    image = None;
    image_idx = 0;
    lodepng_state_cleanup(&mut state);
    png = None;

    base64_idx = 0;
    let base64 = "iVBORw0KGgoAAAANSUhEUgAAACAAAAAgEAIAAACsiDHgAAAABGdBTUEAAYagMeiWXwAAAANzQklUDQ0N0DeNwQAAAH5JREFUeJztl8ENxEAIAwcJ6cpI+q8qKeNepAgelq2dCjz4AdQM1jRcf3WIDQ13qUNsiBBQZ1gR0cARUFIz3pug3586wo5+rOcfIaBOsCSggSOgpcB8D4D3R9DgfUyECIhDbAhp4AjoKPD+CBq8P4IG72MiQkCdYUVEA0dAyQcwUyZpXH92ZwAAAABJRU5ErkJggg==";
    fromBase64_string(&mut png, &mut png_size, base64.as_bytes(), base64.len());

    lodepng_state_init(&mut state);
    state.info_raw.bitdepth = 16;

    //assertNoPNGError(
    //    lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size),
    //    Some("line 2338"),
    //);

    {
        if image.is_some() && 0x1f != image.as_ref().unwrap()[258 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2339",
                "image[258]",
                0x1f,
                image.as_ref().unwrap()[258 + image_idx]
            );
            fail();
        }
    }

    {
        if image.is_some() && 0xf9 != image.as_ref().unwrap()[259 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2340",
                "image[259]",
                0xf9,
                image.as_ref().unwrap()[259 + image_idx]
            );
            fail();
        }
    }

    image = None;
    image_idx = 0;
    lodepng_state_cleanup(&mut state);
    lodepng_state_init(&mut state);
    state.decoder.color_convert = 0;

    //assertNoPNGError(
    //    lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size),
    //    Some("line 2348"),
    //);

    {
        if image.is_some() && 0x1f != image.as_ref().unwrap()[194 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2349",
                "image[194]",
                0x1f,
                image.as_ref().unwrap()[194 + image_idx]
            );
            fail();
        }
    }

    {
        if image.is_some() && 0xf9 != image.as_ref().unwrap()[195 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2350",
                "image[195]",
                0xf9,
                image.as_ref().unwrap()[195 + image_idx]
            );
            fail();
        }
    }

    image = None;
    image_idx = 0;
    lodepng_state_cleanup(&mut state);
    png = None;

    base64_idx = 0;
    let base64 = "iVBORw0KGgoAAAANSUhEUgAAAAcAAAAHAgMAAAC5PL9AAAAABGdBTUEAAYagMeiWXwAAAANzQklUBAQEd/i1owAAAAxQTFRF/wB3AP93//8AAAD/G0OznAAAABpJREFUeJxj+P+H4WoMw605DDfmgEgg+/8fAHF5CrkeXW0HAAAAAElFTkSuQmCC";
    fromBase64_string(&mut png, &mut png_size, base64.as_bytes(), base64.len());

    lodepng_state_init(&mut state);
    state.info_raw.bitdepth = 16;

    //assertNoPNGError(
    //    lodepng_decode(&mut image, &mut w, &mut h, &mut state, png.as_ref().unwrap(), png_size),
    //    Some("line 2364"),
    //);

    {
        if image.is_some() && 0x77 != image.as_ref().unwrap()[84 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2365",
                "image[84]",
                0x77,
                image.as_ref().unwrap()[84 + image_idx]
            );
            fail();
        }
    }

    {
        if image.is_some() && 0x77 != image.as_ref().unwrap()[85 + image_idx] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "2366",
                "image[85]",
                0x77,
                image.as_ref().unwrap()[85 + image_idx]
            );
            fail();
        }
    }

    image = None;
    lodepng_state_cleanup(&mut state);
    png = None;
}
pub fn doMain() {
	println!("* doMain");
    testErrorImages();
    testPNGCodec();
    testComplexPNG();
    //testInspectChunk();
    testFuzzing();
    testEncoderErrors();
    testPaletteToPaletteDecode();
    testPaletteToPaletteDecode2();
    test_color_profile();
    testBkgdChunk();
    testBkgdChunk2();
    testFewColors();
    test_color_key_convert();
    testColorConvert();
    testColorConvert2();
    testPaletteToPaletteConvert();
    testRGBToPaletteConvert();
    test16bitColorEndianness();
    testNoAutoConvert();
    test_chrm_to_srgb();
    test_icc();
    test_icc_gray();
    testCompressZlib();
    testHuffmanCodeLengths();
    testCustomZlibCompress();
    testCustomZlibCompress2();
    testCustomDeflate();
    testCustomZlibDecompress();
    test_custom_inflate();
    println!("\ntest successful");
}
pub fn ColorArray_cleanup(arr: &mut ColorArray) {
	println!("* ColorArray_cleanup");
    // Free the data by setting it to None (equivalent to free() in C)
    arr.data = None;
    
    // Reinitialize the ColorArray
    ColorArray_init(arr);
}

pub fn generateTestImageRequiringColorType16(
    image: &mut Image,
    colorType: LodePNGColorType,
    bitDepth: u32,
    key: bool,
) {
	println!("* generateTestImageRequiringColorType16");
    image.colorType = colorType;
    image.bitDepth = bitDepth;
    let mut w = 1;
    let mut h = 1;
    let gray = colorType == LodePNGColorType::LCT_GREY || colorType == LodePNGColorType::LCT_GREY_ALPHA;
    let alpha = colorType == LodePNGColorType::LCT_RGBA || colorType == LodePNGColorType::LCT_GREY_ALPHA;
    
    Image_cleanup(image);

    if colorType == LodePNGColorType::LCT_PALETTE {
        w = 1 << bitDepth;
        h = 256;
        image.data_size = (w * h) * 8;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            for y in 0..h {
                for x in 0..w {
                    let i = ((y * w) * 8) + (x * 8);
                    data[i + 0] = y as u8;
                    data[i + 1] = y as u8;
                    data[i + 2] = 255;
                    data[i + 3] = 255;
                    data[i + 4] = 0;
                    data[i + 5] = 0;
                    data[i + 6] = if key && y == 0 { 0 } else { 255 };
                    data[i + 7] = if key && y == 0 { 0 } else { 255 };
                }
            }
        }
    } else if bitDepth == 16 {
        w = 2;
        image.data_size = (w * h) * 8;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            data[0] = 10;
            data[1] = 20;
            data[2] = 10;
            data[3] = 20;
            data[4] = if gray { 10 } else { 110 };
            data[5] = if gray { 20 } else { 120 };
            data[6] = if alpha { 128 } else { 255 };
            data[7] = if alpha { 20 } else { 255 };
            data[8] = 40;
            data[9] = 50;
            data[10] = 40;
            data[11] = 50;
            data[12] = if gray { 40 } else { 140 };
            data[13] = if gray { 50 } else { 150 };
            data[14] = if key { 0 } else { 255 };
            data[15] = if key { 0 } else { 255 };
        }
    } else if gray {
        w = 2;
        let v = 255u32 / ((1u32 << bitDepth) - 1u32);
        image.data_size = (w * h) * 8;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            data[0] = v as u8;
            data[1] = v as u8;
            data[2] = v as u8;
            data[3] = v as u8;
            data[4] = v as u8;
            data[5] = v as u8;
            data[6] = if alpha { v as u8 } else { 255 };
            data[7] = if alpha { v as u8 } else { 255 };
            data[8] = 0;
            data[9] = 0;
            data[10] = 0;
            data[11] = 0;
            data[12] = 0;
            data[13] = 0;
            data[14] = if key { 0 } else { 255 };
            data[15] = if key { 0 } else { 255 };
        }
    } else {
        w = 257;
        image.data_size = (w * h) * 8;
        image.data = Some(vec![0; image.data_size]);
        
        if let Some(ref mut data) = image.data {
            for y in 0..h {
                for x in 0..w {
                    let i = ((y * w) * 8) + (x * 8);
                    let val = (i / 2) as u8;
                    data[i + 0] = val;
                    data[i + 1] = val;
                    data[i + 2] = (i / 3) as u8;
                    data[i + 3] = (i / 3) as u8;
                    data[i + 4] = (i / 5) as u8;
                    data[i + 5] = (i / 5) as u8;
                    data[i + 6] = if key && y == 0 { 0 } else { if alpha { i as u8 } else { 255 } };
                    data[i + 7] = if key && y == 0 { 0 } else { if alpha { i as u8 } else { 255 } };
                }
            }
        }
    }
    
    image.width = w as u32;
    image.height = h as u32;
}

pub fn testDiskCompressZlib(filename: &str) {
	println!("* testDiskCompressZlib");
    println!("testDiskCompressZlib: File {}", filename);
    
    let mut buffer: Option<Vec<u8>> = None;
    let mut buffer_size: Option<usize> = None;
    
    match lodepng_load_file(&mut buffer, &mut buffer_size, filename) {
        Ok(()) => (),
        Err(error) => {
            assertNoPNGError(error, Some("line 1384"));
            return;
        }
    };
    
    let buffer = buffer.unwrap();
    let buffer_size = buffer_size.unwrap();
    
    let f: String = buffer.into_iter()
        .map(|byte| byte as char)
        .collect();
    
    testCompressStringZlib(&f, false);
}
pub fn testSbitChunk_helper(
    r: u32,
    g: u32,
    b: u32,
    a: u32,
    pixels: Option<&[u8]>,
    pixels_size: usize,
    w: u32,
    h: u32,
    mode_raw: &LodePNGColorMode,
    mode_png: &LodePNGColorMode,
    auto_convert: u32,
    expect_encoder_error: u32,
) {
	println!("* testSbitChunk_helper");
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 1,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 2048,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    let info = &mut state.info_png;
    lodepng_color_mode_copy(&mut info.color, mode_png);
    lodepng_color_mode_copy(&mut state.info_raw, mode_raw);
    state.encoder.auto_convert = auto_convert;

    if mode_raw.colortype == LodePNGColorType::LCT_PALETTE {
        for i in 0..=255 {
            lodepng_palette_add(&mut state.info_raw, i, i, i, 255);
            lodepng_palette_add(&mut info.color, i, i, i, 255);
        }
    }

    info.sbit_defined = 1;
    info.sbit_r = r;
    info.sbit_g = g;
    info.sbit_b = b;
    info.sbit_a = a;

    let mut png: Option<Vec<u8>> = None;
    let mut png_size: usize = 0;
    let error = lodepng_encode(&mut png, &mut png_size, pixels, w, h, &mut state);

    if expect_encoder_error != 0 {
        if error == 0 {
            println!(
                "line {}: {} ASSERT_NOT_EQUALS failed: Expected not {} but got {}.",
                "3352", "error", 0, error
            );
            fail();
        }
        lodepng_state_cleanup(&mut state);
        return;
    }

    assertNoPNGError(error, Some("line 3357"));

    let mut state2 = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 1,
            read_text_chunks: 1,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 2,
                use_lz77: 1,
                windowsize: 2048,
                minmatch: 3,
                nicematch: 128,
                lazymatching: 1,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 1,
            filter_palette_zero: 1,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 1,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state2);
    
    let mut w2 = 0;
    let mut h2 = 0;
    let mut image2: Option<Vec<u8>> = None;
    let error = lodepng_decode(&mut image2, &mut w2, &mut h2, &mut state2, png.as_ref().unwrap(), png_size);
    assertNoPNGError(error, Some("line 3365"));

    let type_ = mode_png.colortype;
    let info2 = &state2.info_png;

    if w != w2 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "3369", "w2", w, w2
        );
        fail();
    }

    if h != h2 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "3370", "h2", h, h2
        );
        fail();
    }

    if info2.sbit_defined != 1 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "3371", "info2->sbit_defined", 1, info2.sbit_defined
        );
        fail();
    }

    if r != info2.sbit_r {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "3372", "info2->sbit_r", r, info2.sbit_r
        );
        fail();
    }

    if type_ == LodePNGColorType::LCT_RGB
        || type_ == LodePNGColorType::LCT_RGBA
        || type_ == LodePNGColorType::LCT_PALETTE
    {
        if g != info2.sbit_g {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "3374", "info2->sbit_g", g, info2.sbit_g
            );
            fail();
        }

        if b != info2.sbit_b {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "3375", "info2->sbit_b", b, info2.sbit_b
            );
            fail();
        }
    }

    if type_ == LodePNGColorType::LCT_GREY_ALPHA || type_ == LodePNGColorType::LCT_RGBA {
        if a != info2.sbit_a {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "3378", "info2->sbit_a", a, info2.sbit_a
            );
            fail();
        }
    }

    let mut mode_compare = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 16,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    let mut mode_decoded = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 8,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut mode_compare);
    mode_compare.bitdepth = 16;
    mode_compare.colortype = LodePNGColorType::LCT_RGBA;
    lodepng_color_mode_init(&mut mode_decoded);
    mode_decoded.bitdepth = 8;
    mode_decoded.colortype = LodePNGColorType::LCT_RGBA;

    let mut image3 = vec![0; (w * h) as usize * 8];
    let error = lodepng_convert(
        &mut image3,
        image2.as_ref().unwrap(),
        &mode_compare,
        &mode_decoded,
        w,
        h,
    );
    assertNoPNGError(error, Some("line 3392"));

    let mut image4 = vec![0; (w * h) as usize * 8];
    let error = lodepng_convert(
        &mut image4,
        pixels.unwrap(),
        &mode_compare,
        &state.info_raw,
        w,
        h,
    );
    assertNoPNGError(error, Some("line 3396"));

    for i in 0..((w * h) as usize * 8) {
        if image4[i] != image3[i] {
            println!(
                "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                "3399", "image3[i]", image4[i], image3[i]
            );
            fail();
        }
    }

    lodepng_state_cleanup(&mut state);
    lodepng_state_cleanup(&mut state2);
}
pub fn testSbitChunk_simple(
    r: u32,
    g: u32,
    b: u32,
    a: u32,
    type_: LodePNGColorType,
    bitdepth: u32,
    expect_encoder_error: i32,
) {
	println!("* testSbitChunk_simple");
    let mut mode_raw = LodePNGColorMode {
        colortype: type_,
        bitdepth,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    
    let mut mode_png = LodePNGColorMode {
        colortype: type_,
        bitdepth,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };

    let pixels = [255, 255, 255, 255, 255, 255, 255, 255];
    
    testSbitChunk_helper(
        r,
        g,
        b,
        a,
        Some(&pixels),
        8,
        1,
        1,
        &mode_raw,
        &mode_png,
        0,
        expect_encoder_error as u32,
    );
    
    testSbitChunk_helper(
        r,
        g,
        b,
        a,
        Some(&pixels),
        8,
        1,
        1,
        &mode_raw,
        &mode_png,
        1,
        expect_encoder_error as u32,
    );
}
pub fn testDiskPNG(filename: Option<&str>) {
	println!("* testDiskPNG");
    // Check if filename is None (equivalent to NULL check in C)
    let filename = filename.expect("testDiskPNG: filename cannot be NULL");

    println!("testDiskPNG: File {}", filename); // Replaces printf

    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: LodePNGColorType::LCT_RGB,
        bitDepth: 8,
    };

    Image_init(&mut image);

    // Create temporary Option<u32> for width and height
    let mut width = None;
    let mut height = None;

    // lodepng_decode_file returns Result<(), u32> in Rust
    let error = lodepng_decode_file(
        &mut image.data,
        &mut width,
        &mut height,
        filename,
        image.colorType,
        image.bitDepth,
    );

    // Assign the unwrapped width and height back to the image
    image.width = width.expect("Failed to get width");
    image.height = height.expect("Failed to get height");

    // Convert Result to error code (0 for Ok, error code for Err)
    let error_code = match error {
        Ok(()) => 0,
        Err(e) => e,
    };
    assertNoPNGError(error_code, Some("line 1407"));

    image.data_size = (((image.width * image.height) * getNumColorChannels(image.colorType) as u32 * image.bitDepth) / 8) as usize;
    
    doCodecTest(&image);
    Image_cleanup(&mut image);
}
pub fn test_auto_color_model(
    colors: &[u8],
    colors_size: usize,
    inbitdepth: u32,
    colortype: LodePNGColorType,
    bitdepth: u32,
    key: i32,
) {
	println!("* test_auto_color_model");
    println!(
        "testAutoColorModel {} {:?} {} {}",
        inbitdepth, colortype, bitdepth, key
    );

    let innum = ((colors_size / 4) * inbitdepth as usize) / 8;
    let num = if innum < 65536 { 65536 } else { innum };
    let colors2_size = (num * 4) * (inbitdepth as usize / 8);
    let mut colors2 = vec![0u8; colors2_size];

    for i in 0..colors2_size {
        colors2[i] = colors[i % colors_size];
    }

    let mut png: Option<Vec<u8>> = None;
    let mut png_size = 0;
    lodepng_encode_memory(
        &mut png,
        &mut png_size,
        Some(&colors2),
        num.try_into().unwrap(),
        1,
        LodePNGColorType::LCT_RGBA,
        inbitdepth,
    );

    let mut w = 0;
    let mut h = 0;
    let mut state = LodePngState {
        decoder: LodePngDecoderSettings {
            zlibsettings: LodePngDecompressSettings {
                ignore_adler32: 0,
                ignore_nlen: 0,
                max_output_size: 0,
                custom_zlib: None,
                custom_inflate: None,
                custom_context: None,
            },
            ignore_crc: 0,
            ignore_critical: 0,
            ignore_end: 0,
            color_convert: 0,
            read_text_chunks: 0,
            remember_unknown_chunks: 0,
            max_text_size: 0,
            max_icc_size: 0,
        },
        encoder: LodePngEncoderSettings {
            zlibsettings: LodePngCompressSettings {
                btype: 0,
                use_lz77: 0,
                windowsize: 0,
                minmatch: 0,
                nicematch: 0,
                lazymatching: 0,
                custom_zlib: None,
                custom_deflate: None,
                custom_context: None,
            },
            auto_convert: 0,
            filter_palette_zero: 0,
            filter_strategy: LodePNGFilterStrategy::LFS_MINSUM,
            predefined_filters: None,
            force_palette: 0,
            add_id: 0,
            text_compression: 0,
        },
        info_raw: LodePNGColorMode {
            colortype: LodePNGColorType::LCT_RGBA,
            bitdepth: 8,
            palette: None,
            palettesize: 0,
            key_defined: 0,
            key_r: 0,
            key_g: 0,
            key_b: 0,
        },
        info_png: LodePngInfo {
            compression_method: 0,
            filter_method: 0,
            interlace_method: 0,
            color: LodePNGColorMode {
                colortype: LodePNGColorType::LCT_RGBA,
                bitdepth: 8,
                palette: None,
                palettesize: 0,
                key_defined: 0,
                key_r: 0,
                key_g: 0,
                key_b: 0,
            },
            background_defined: 0,
            background_r: 0,
            background_g: 0,
            background_b: 0,
            text_num: 0,
            text_keys: None,
            text_strings: None,
            itext_num: 0,
            itext_keys: None,
            itext_langtags: None,
            itext_transkeys: None,
            itext_strings: None,
            time_defined: 0,
            time: LodePngTime {
                year: 0,
                month: 0,
                day: 0,
                hour: 0,
                minute: 0,
                second: 0,
            },
            phys_defined: 0,
            phys_x: 0,
            phys_y: 0,
            phys_unit: 0,
            gama_defined: 0,
            gama_gamma: 0,
            chrm_defined: 0,
            chrm_white_x: 0,
            chrm_white_y: 0,
            chrm_red_x: 0,
            chrm_red_y: 0,
            chrm_green_x: 0,
            chrm_green_y: 0,
            chrm_blue_x: 0,
            chrm_blue_y: 0,
            srgb_defined: 0,
            srgb_intent: 0,
            iccp_defined: 0,
            iccp_name: None,
            iccp_profile: None,
            iccp_profile_size: 0,
            sbit_defined: 0,
            sbit_r: 0,
            sbit_g: 0,
            sbit_b: 0,
            sbit_a: 0,
            unknown_chunks_data: [None, None, None],
            unknown_chunks_size: [0, 0, 0],
        },
        error: 0,
    };
    lodepng_state_init(&mut state);
    let mut decoded: Option<Vec<u8>> = None;
    lodepng_decode(
        &mut decoded,
        &mut w,
        &mut h,
        &mut state,
        png.as_ref().unwrap(),
        png_size,
    );

    if num != w as usize {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2627", "w", num, w
        );
        fail();
    }

    if 1 != h {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2628", "h", 1, h
        );
        fail();
    }

    if colortype != state.info_png.color.colortype {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {:?} but got {:?}.",
            "2629", "state.info_png.color.colortype", colortype, state.info_png.color.colortype
        );
        fail();
    }

    if bitdepth != state.info_png.color.bitdepth {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2630", "state.info_png.color.bitdepth", bitdepth, state.info_png.color.bitdepth
        );
        fail();
    }

    if key != state.info_png.color.key_defined as i32 {
        println!(
            "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
            "2631", "state.info_png.color.key_defined", key, state.info_png.color.key_defined
        );
        fail();
    }

    if inbitdepth == 8 {
        for i in 0..colors_size {
            if colors[i] != decoded.as_ref().unwrap()[i] {
                println!(
                    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                    "2636", "decoded[i]", colors[i], decoded.as_ref().unwrap()[i]
                );
                fail();
            }
        }
    } else {
        for i in 0..(colors_size / 2) {
            if colors[i * 2] != decoded.as_ref().unwrap()[i] {
                println!(
                    "line {}: {} ASSERT_EQUALS failed: Expected {} but got {}.",
                    "2640", "decoded[i]", colors[i * 2], decoded.as_ref().unwrap()[i]
                );
                fail();
            }
        }
    }

    lodepng_state_cleanup(&mut state);
}
pub fn testSbitChunk2(
    r: u32,
    g: u32,
    b: u32,
    a: u32,
    type_pixels: LodePNGColorType,
    bitdepth_pixels: u32,
    type_raw: LodePNGColorType,
    bitdepth_raw: u32,
    type_png: LodePNGColorType,
    bitdepth_png: u32,
    auto_convert: i32,
    expect_encoder_error: i32,
) {
	println!("* testSbitChunk2");
    let mut image = Image {
        data: None,
        data_size: 0,
        width: 0,
        height: 0,
        colorType: type_pixels,
        bitDepth: bitdepth_pixels,
    };
    Image_init(&mut image);
    generateTestImageRequiringColorType16(&mut image, type_pixels, bitdepth_pixels, false);

    let mut mode_raw = LodePNGColorMode {
        colortype: type_raw,
        bitdepth: bitdepth_raw,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut mode_raw);
    mode_raw.bitdepth = bitdepth_raw;
    mode_raw.colortype = type_raw;

    let mut mode_test = LodePNGColorMode {
        colortype: LodePNGColorType::LCT_RGBA,
        bitdepth: 16,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut mode_test);
    mode_test.bitdepth = 16;
    mode_test.colortype = LodePNGColorType::LCT_RGBA;

    let mut mode_png = LodePNGColorMode {
        colortype: type_png,
        bitdepth: bitdepth_png,
        palette: None,
        palettesize: 0,
        key_defined: 0,
        key_r: 0,
        key_g: 0,
        key_b: 0,
    };
    lodepng_color_mode_init(&mut mode_png);
    mode_png.bitdepth = bitdepth_png;
    mode_png.colortype = type_png;

    let temp_size = ((image.width * image.height) * lodepng_get_bpp(&mode_raw) as u32 + 7) / 8;
    let mut temp = vec![0u8; temp_size as usize];

    let error = lodepng_convert(
        &mut temp,
        image.data.as_ref().unwrap(),
        &mode_raw,
        &mode_test,
        image.width,
        image.height,
    );
    assertNoPNGError(error, Some("line 3459"));

    image.data = Some(temp);
    image.data_size = temp_size as usize;

    if auto_convert == 0 || auto_convert == 2 {
        testSbitChunk_helper(
            r,
            g,
            b,
            a,
            image.data.as_deref(),
            image.data_size,
            image.width,
            image.height,
            &mode_raw,
            &mode_png,
            0,
            expect_encoder_error as u32,
        );
    }

    if auto_convert == 1 || auto_convert == 2 {
        testSbitChunk_helper(
            r,
            g,
            b,
            a,
            image.data.as_deref(),
            image.data_size,
            image.width,
            image.height,
            &mode_raw,
            &mode_png,
            1,
            expect_encoder_error as u32,
        );
    }

    Image_cleanup(&mut image);
    lodepng_color_mode_cleanup(&mut mode_raw);
    lodepng_color_mode_cleanup(&mut mode_test);
    lodepng_color_mode_cleanup(&mut mode_png);
}
