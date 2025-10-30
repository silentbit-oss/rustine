use crate::*;
use rand::Rng;
use std::mem;
use std::f32::consts::SQRT_2;

pub fn randhash(seed: u32) -> u32 {
    let mut i = (seed ^ 12345391u32).wrapping_mul(2654435769u32);
    i ^= (i << 6) ^ (i >> 26);
    i = i.wrapping_mul(2654435769u32);
    i += (i << 5) ^ (i >> 12);
    i
}
pub fn heman_points_destroy(img: HemanPoints) {
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // and the Vec inside HemanImageS will also be automatically dropped.
    // No explicit free is needed as Rust's ownership system handles memory deallocation.
    // The Option wrapper allows for the case where img is None (equivalent to NULL in C).
    // Simply dropping the Box is sufficient.
}

pub fn randhashf(seed: u32, a: f32, b: f32) -> f32 {
    ((b - a) * randhash(seed) as f32) / (4294967295.0) + a
}

pub fn heman_points_create(xy: Option<&[f32]>, npoints: i32, nbands: i32) -> HemanPoints {
    // Check if input slice is None (equivalent to NULL check in C)
    let xy = match xy {
        Some(slice) => slice,
        None => return None,
    };

    // Calculate total bytes needed (same calculation as in C)
    let nbytes = (mem::size_of::<f32>() * npoints as usize) * nbands as usize;

    // Verify the input slice has enough data
    if xy.len() * mem::size_of::<f32>() < nbytes {
        return None;
    }

    // Create the image structure
    let img = Box::new(HemanImageS {
        width: npoints,
        height: 1,
        nbands,
        data: Some(xy[..nbytes / mem::size_of::<f32>()].to_vec()),
    });

    Some(img)
}

pub fn heman_points_from_grid(width: f32, height: f32, cellsize: f32, jitter: f32) -> HemanPoints {
    let cols = (width / cellsize) as i32;
    let rows = (height / cellsize) as i32;
    let ncells = cols * rows;
    let mut result = heman_image_create(ncells, 1, 2);
    
    if let Some(ref mut result) = result {
        if let Some(ref mut data) = result.data {
            let rscale = (2.0 * jitter) / 32767.0;
            let mut rng = rand::thread_rng();

            for j in 0..rows {
                let dst_start = (j * cols * 2) as usize;
                let y = (cellsize * 0.5) + (cellsize * j as f32);
                let mut x = cellsize * 0.5;

                for i in 0..cols {
                    let rx = (rng.gen_range(0..=32767) as f32 * rscale) - jitter;
                    let ry = (rng.gen_range(0..=32767) as f32 * rscale) - jitter;
                    
                    let idx = dst_start + (i * 2) as usize;
                    data[idx] = x + rx;
                    data[idx + 1] = y + ry;
                    x += cellsize;
                }
            }
        }
    }

    result
}

pub fn sample_annulus(radius: f32, center: KmVec2, seedptr: &mut u32) -> KmVec2 {
    let mut seed = *seedptr;
    let rscale = 1.0f32 / 4294967295.0f32;
    let mut r = KmVec2 { x: 0.0, y: 0.0 };

    loop {
        r.x = (4.0 * rscale) * (randhash(seed) as f32) - 2.0;
        seed += 1;
        r.y = (4.0 * rscale) * (randhash(seed) as f32) - 2.0;
        seed += 1;
        
        let r2 = kmVec2LengthSq(Some(&r));
        if r2 > 1.0 && r2 <= 4.0 {
            break;
        }
    }

    *seedptr = seed;
    let mut scaled_r = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Scale(&mut scaled_r, &r, radius);
    let mut result = KmVec2 { x: 0.0, y: 0.0 };
    kmVec2Add(&mut result, &scaled_r, &center);
    result
}
pub fn heman_points_from_poisson(width: f32, height: f32, radius: f32) -> HemanPoints {
    let maxattempts = 30;
    let rscale = 1.0 / 4294967295.0;
    let mut seed = 0;
    let rvec = KmVec2 {
        x: radius,
        y: radius,
    };
    let r2 = radius * radius;
    let cellsize = radius / SQRT_2;
    let invcell = 1.0 / cellsize;
    let ncols = (width * invcell).ceil() as i32;
    let nrows = (height * invcell).ceil() as i32;
    let maxcol = ncols - 1;
    let maxrow = nrows - 1;
    let ncells = ncols * nrows;
    let mut grid = vec![-1; ncells as usize];
    let mut actives = vec![0; ncells as usize];
    let mut nactives = 0;
    let mut result = heman_image_create(ncells, 1, 2);
    let samples = if let Some(ref mut res) = result {
        unsafe { std::mem::transmute::<&mut [f32], &mut [KmVec2]>(res.data.as_mut().unwrap()) }
    } else {
        return None;
    };
    let mut nsamples = 0;
    let mut pt = KmVec2 {
        x: (width * randhash(seed) as f32) * rscale,
        y: (height * randhash(seed + 1) as f32) * rscale,
    };
    seed += 2;
    
    let grid_index = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
    grid[grid_index as usize] = nsamples;
    actives[nactives as usize] = nsamples;
    nactives += 1;
    samples[nsamples as usize] = pt.clone();
    nsamples += 1;

    while nsamples < ncells {
        let aindex = if randhashf(seed, 0.0, nactives as f32) > (nactives - 1) as f32 {
            nactives - 1
        } else {
            randhashf(seed + 1, 0.0, nactives as f32) as i32
        };
        seed += 2;
        let sindex = actives[aindex as usize];
        let mut found = false;

        for _attempt in 0..maxattempts {
            pt = sample_annulus(radius, samples[sindex as usize].clone(), &mut seed);
            if pt.x < 0.0 || pt.x >= width || pt.y < 0.0 || pt.y >= height {
                continue;
            }

            let mut minj = pt.clone();
            let mut maxj = pt.clone();
            {
                let temp_maxj = maxj.clone();
                kmVec2Add(&mut maxj, &temp_maxj, &rvec);
            }
            {
                let temp_minj = minj.clone();
                kmVec2Subtract(&mut minj, &temp_minj, &rvec);
            }
            {
                let temp_minj = minj.clone();
                kmVec2Scale(&mut minj, &temp_minj, invcell);
            }
            {
                let temp_maxj = maxj.clone();
                kmVec2Scale(&mut maxj, &temp_maxj, invcell);
            }

            minj.x = 0.0_f32.max((minj.x as i32).min(maxcol) as f32);
            maxj.x = 0.0_f32.max((maxj.x as i32).min(maxcol) as f32);
            minj.y = 0.0_f32.max((minj.y as i32).min(maxrow) as f32);
            maxj.y = 0.0_f32.max((maxj.y as i32).min(maxrow) as f32);

            let mut reject = false;
            let mut j = KmVec2 { x: 0.0, y: 0.0 };
            j.y = minj.y;
            while j.y <= maxj.y && !reject {
                j.x = minj.x;
                while j.x <= maxj.x && !reject {
                    let entry = grid[(j.y as i32 * ncols + j.x as i32) as usize];
                    if entry > -1 && entry != sindex {
                        let mut delta = KmVec2 { x: 0.0, y: 0.0 };
                        kmVec2Subtract(&mut delta, &samples[entry as usize], &pt);
                        if kmVec2LengthSq(Some(&delta)) < r2 {
                            reject = true;
                        }
                    }
                    j.x += 1.0;
                }
                j.y += 1.0;
            }

            if reject {
                continue;
            }
            found = true;
            break;
        }

        if found {
            let grid_index = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
            grid[grid_index as usize] = nsamples;
            actives[nactives as usize] = nsamples;
            nactives += 1;
            samples[nsamples as usize] = pt.clone();
            nsamples += 1;
        } else {
            nactives -= 1;
            if nactives <= 0 {
                break;
            }
            actives[aindex as usize] = actives[nactives as usize];
        }
    }

    if let Some(ref mut res) = result {
        res.width = nsamples;
    }
    result
}
pub fn heman_points_from_density(density: &HemanImageS, minradius: f32, maxradius: f32) -> HemanPoints {
    assert!(density.nbands == 1);
    let width = 1.0;
    let height = 1.0;
    let maxattempts = 30;
    let rscale = 1.0 / 4294967295.0;
    let mut seed = 0;
    let mut rvec = KmVec2 {
        x: maxradius,
        y: maxradius,
    };
    let cellsize = maxradius / SQRT_2;
    let invcell = 1.0 / cellsize;
    let ncols = (width * invcell).ceil() as i32;
    let nrows = (height * invcell).ceil() as i32;
    let maxcol = ncols - 1;
    let maxrow = nrows - 1;
    let ncells = ncols * nrows;
    let ntexels = (cellsize * density.width as f32) as i32;
    let gcapacity = ntexels * ntexels;
    
    let mut grid = vec![0; (ncells * gcapacity) as usize];
    let mut ngrid = vec![0; ncells as usize];
    let mut actives = vec![0; ncells as usize];
    let mut nactives = 0;
    let maxsamples = ncells * gcapacity;
    let mut result = heman_image_create(maxsamples, 1, 2).unwrap();
    let samples = unsafe { std::slice::from_raw_parts_mut(result.data.as_mut().unwrap().as_mut_ptr() as *mut KmVec2, maxsamples as usize) };
    let mut nsamples = 0;

    let mut pt = KmVec2 {
        x: (width * randhash(seed) as f32) * rscale,
        y: (height * randhash(seed + 1) as f32) * rscale,
    };
    seed += 2;
    
    actives[nactives as usize] = nsamples;
    nactives += 1;
    let gindex = ((pt.x * invcell) as i32) + (ncols * ((pt.y * invcell) as i32));
    grid[(gcapacity * gindex + ngrid[gindex as usize]) as usize] = nsamples;
    ngrid[gindex as usize] += 1;
    samples[nsamples as usize] = pt.clone();
    nsamples += 1;

    while nsamples < maxsamples {
        let aindex = if randhashf(seed, 0.0, nactives as f32) > (nactives - 1) as f32 {
            nactives - 1
        } else {
            randhashf(seed + 1, 0.0, nactives as f32) as i32
        };
        seed += 2;
        let sindex = actives[aindex as usize];
        let mut found = false;
        let mut attempt = 0;
        let mut pt_new = KmVec2 { x: 0.0, y: 0.0 };

        while attempt < maxattempts && !found {
            pt_new = sample_annulus(maxradius, samples[sindex as usize].clone(), &mut seed);
            if pt_new.x < 0.0 || pt_new.x >= width || pt_new.y < 0.0 || pt_new.y >= height {
                attempt += 1;
                continue;
            }

            let mut minj = pt_new.clone();
            let mut maxj = pt_new.clone();
            {
                let temp_maxj = maxj.clone();
                kmVec2Add(&mut maxj, &temp_maxj, &rvec);
            }
            {
                let temp_minj = minj.clone();
                kmVec2Subtract(&mut minj, &temp_minj, &rvec);
            }
            {
                let temp_minj = minj.clone();
                kmVec2Scale(&mut minj, &temp_minj, invcell);
            }
            {
                let temp_maxj = maxj.clone();
                kmVec2Scale(&mut maxj, &temp_maxj, invcell);
            }

            minj.x = 0.0_f32.max(minj.x.min(maxcol as f32));
            maxj.x = 0.0_f32.max(maxj.x.min(maxcol as f32));
            minj.y = 0.0_f32.max(minj.y.min(maxrow as f32));
            maxj.y = 0.0_f32.max(maxj.y.min(maxrow as f32));

            let mut reject = false;
            let mut densityval: f32 = 0.0;
            heman_image_sample(density, pt_new.x, pt_new.y, &mut [densityval]);
            densityval = densityval.sqrt();
            let mindist = maxradius - (densityval * (maxradius - minradius));
            let r2 = mindist * mindist;

            let mut j = KmVec2 { x: 0.0, y: 0.0 };
            j.y = minj.y.floor();
            while j.y <= maxj.y.ceil() && !reject {
                j.x = minj.x.floor();
                while j.x <= maxj.x.ceil() && !reject {
                    let cell_idx = (j.y as i32 * ncols + j.x as i32) as usize;
                    for g in 0..ngrid[cell_idx] {
                        let entry = grid[(gcapacity * cell_idx as i32 + g) as usize];
                        if entry != sindex {
                            let mut delta = KmVec2 { x: 0.0, y: 0.0 };
                            kmVec2Subtract(&mut delta, &samples[entry as usize], &pt_new);
                            if kmVec2LengthSq(Some(&delta)) < r2 {
                                reject = true;
                                break;
                            }
                        }
                    }
                    j.x += 1.0;
                }
                j.y += 1.0;
            }

            if !reject {
                found = true;
                pt = pt_new;
            }
            attempt += 1;
        }

        if found {
            let gindex = ((pt.x * invcell) as i32) + (ncols * ((pt.y * invcell) as i32));
            if ngrid[gindex as usize] >= gcapacity {
                found = false;
            } else {
                actives[nactives as usize] = nsamples;
                nactives += 1;
                grid[(gcapacity * gindex + ngrid[gindex as usize]) as usize] = nsamples;
                ngrid[gindex as usize] += 1;
                samples[nsamples as usize] = pt.clone();
                nsamples += 1;
            }
        }

        if !found {
            nactives -= 1;
            if nactives <= 0 {
                break;
            }
            actives[aindex as usize] = actives[nactives as usize];
        }
    }

    result.width = nsamples;
    Some(result)
}
