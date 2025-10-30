use crate::*;
use std::fs::File;
use std::io::BufWriter;
use std::io::Write;
use std::assert;
use rand::Rng;
use std::path::Path;


pub fn heman_export_ply(img: &HemanImageS, filename: &str) -> std::io::Result<()> {
    assert!(img.nbands == 1, "Image must have exactly 1 band");
    
    let fout = File::create(filename)?;
    let mut writer = BufWriter::new(fout);
    
    let ncols = img.width - 1;
    let nrows = img.height - 1;
    let ncells = ncols * nrows;
    let nverts = img.width * img.height;
    
    // Write PLY header
    writeln!(
        writer,
        "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex {}\nproperty float32 x\nproperty float32 y\nproperty float32 z\nelement face {}\nproperty list int32 int32 vertex_indices\nend_header",
        nverts, ncells
    )?;
    
    let invw = 2.0f32 / img.width as f32;
    let invh = 2.0f32 / img.height as f32;
    
    // Write vertices
    for j in 0..img.height {
        for i in 0..img.width {
            let x = -1.0 + (i as f32 * invw);
            let y = -1.0 + (j as f32 * invh);
            let z = match heman_image_texel(img, i, j) {
                Some(texel) => texel[0],
                None => 0.0, // Default value if texel is None
            };
            
            writer.write_all(&x.to_le_bytes())?;
            writer.write_all(&y.to_le_bytes())?;
            writer.write_all(&z.to_le_bytes())?;
        }
    }
    
    // Write faces
    for j in 0..nrows {
        let mut p = j * img.width;
        for _ in 0..ncols {
            let face = [
                4i32.to_le_bytes(),
                p.to_le_bytes(),
                (p + 1).to_le_bytes(),
                (p + img.width + 1).to_le_bytes(),
                (p + img.width).to_le_bytes(),
            ];
            
            for bytes in &face {
                writer.write_all(bytes)?;
            }
            
            p += 1;
        }
    }
    
    Ok(())
}

pub fn heman_export_u8(source: HemanImage, minv: f32, maxv: f32, outp: Option<&mut [heman_byte]>) {
    // Early return if any required parameter is None
    let Some(source) = source else { return };
    let Some(data) = &source.data else { return };
    let Some(outp) = outp else { return };

    let scale = 1.0f32 / (maxv - minv);
    let size = (source.height * source.width * source.nbands) as usize;

    // Ensure output slice has enough capacity
    if outp.len() < size {
        return;
    }

    for i in 0..size {
        let v = (255.0f32 * (data[i] - minv)) * scale;
        outp[i] = v.clamp(0.0, 255.0) as heman_byte;
    }
}
pub fn heman_export_with_colors_ply(
    hmap: &HemanImageS,
    colors: &HemanImageS,
    filename: &str,
) -> Result<(), std::io::Error> {
    let width = hmap.width;
    let height = hmap.height;
    assert!(hmap.nbands == 1);
    assert!(colors.nbands == 3);
    assert!(colors.width == width);
    assert!(colors.height == height);

    let mut fout = BufWriter::new(File::create(Path::new(filename))?);
    
    let ncols = hmap.width - 1;
    let nrows = hmap.height - 1;
    let ncells = ncols * nrows;
    let nverts = hmap.width * hmap.height;

    let mut colordata = vec![0u8; (width * height * 3) as usize];
    heman_export_u8(Some(Box::new(colors.clone())), 0.0, 1.0, Some(&mut colordata));

    writeln!(
        fout,
        "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex {}\nproperty float32 x\nproperty float32 y\nproperty float32 z\nproperty uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\nelement face {}\nproperty list int32 int32 vertex_indices\nend_header",
        nverts, ncells
    )?;

    let invw = 2.0f32 / width as f32;
    let invh = 2.0f32 / height as f32;
    let mut pcolor_idx = 0;

    for j in 0..height {
        for i in 0..width {
            let vert = [
                -1.0 + (i as f32 * invw),
                -1.0 + (j as f32 * invh),
                *heman_image_texel(hmap, i, j).unwrap().first().unwrap(),
            ];
            // Convert each f32 to bytes and write
            for &v in &vert {
                fout.write_all(&v.to_ne_bytes())?;
            }
            fout.write_all(&colordata[pcolor_idx as usize..(pcolor_idx + 3) as usize])?;
            pcolor_idx += 3;
            fout.write_all(&[255])?;
        }
    }

    let mut face = [0i32; 5];
    face[0] = 4;
    for j in 0..nrows {
        let mut p = j * width;
        for _ in 0..ncols {
            face[1] = p;
            face[2] = p + 1;
            face[3] = (p + hmap.width) + 1;
            face[4] = p + hmap.width;
            // Convert each i32 to bytes and write
            for &f in &face {
                fout.write_all(&f.to_ne_bytes())?;
            }
            p += 1;
        }
    }

    Ok(())
}
