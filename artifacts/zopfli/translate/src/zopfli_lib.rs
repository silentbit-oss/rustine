use crate::*;

pub fn ZopfliCompress(
    options: &ZopfliOptions,
    output_type: ZopfliFormat,
    in_data: &[u8],
    insize: usize,
    out: &mut Option<Vec<u8>>,
    outsize: &mut usize,
) {
    match output_type {
        ZopfliFormat::Gzip => {
            ZopfliGzipCompress(options, in_data, insize, out, outsize);
        }
        ZopfliFormat::Zlib => {
            ZopfliZlibCompress(options, in_data, out, outsize);
        }
        ZopfliFormat::Deflate => {
            let mut bp = 0;
            ZopfliDeflate(options, 2, true, in_data, insize, &mut bp, out, outsize);
        }
        _ => {
            panic!("Invalid output format specified");
        }
    }
}
