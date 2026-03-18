use crate::*;
use std::io;

pub fn ZopfliCompress(
    options: &ZopfliOptions,
    output_type: ZopfliFormat,
    in_data: Option<&[u8]>,
    out: &mut Vec<u8>,
) -> io::Result<()> {
    match output_type {
        ZopfliFormat::ZOPFLI_FORMAT_GZIP => {
            ZopfliGzipCompress(options, in_data, out)
        }
        ZopfliFormat::ZOPFLI_FORMAT_ZLIB => {
            if let Some(data) = in_data {
                ZopfliZlibCompress(options, data, out)
            } else {
                Err(io::Error::new(io::ErrorKind::InvalidInput, "Input data is None"))
            }
        }
        ZopfliFormat::ZOPFLI_FORMAT_DEFLATE => {
            let mut bp = 0u8;
            let mut outsize = 0usize;
            let mut out_wrapper = Some(out.clone());
            if let Some(data) = in_data {
                ZopfliDeflate(
                    options,
                    2,
                    true,
                    data,
                    &mut bp,
                    &mut out_wrapper,
                    &mut outsize,
                );
                if let Some(updated_out) = out_wrapper {
                    *out = updated_out;
                }
                Ok(())
            } else {
                Err(io::Error::new(io::ErrorKind::InvalidInput, "Input data is None"))
            }
        }
        _ => {
            panic!("Invalid output type");
        }
    }
}
