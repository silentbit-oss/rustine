use crate::*;
use rand::Rng;
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
    // and the Vec inside HemanImageS will also be automatically deallocated.
    // No explicit free is needed - Rust's ownership system handles it.
    // The function takes ownership of the Box through HemanPoints (Option<Box<HemanImageS>>)
    // and it will be dropped at the end of the function.
}

pub fn randhashf(seed: u32, a: f32, b: f32) -> f32 {
    ((b - a) * randhash(seed) as f32 / 4294967295.0) + a
}
pub fn heman_points_create(xy: Option<&[f32]>, npoints: i32, nbands: i32) -> HemanPoints {
    // Check if input slice is None (equivalent to NULL check in C)
    let xy = match xy {
        Some(slice) => slice,
        None => return None,
    };

    // Calculate required bytes (though in Rust we'll work with Vec capacity directly)
    let nbytes = (std::mem::size_of::<f32>() * npoints as usize) * nbands as usize;
    
    // Create new HemanImageS with the given parameters
    let mut img = Box::new(HemanImageS {
        width: npoints,
        height: 1,
        nbands,
        data: Some(Vec::with_capacity(nbytes / std::mem::size_of::<f32>())),
    });

    // Copy data if the input slice has the correct length
    if let Some(data) = &mut img.data {
        if xy.len() * std::mem::size_of::<f32>() == nbytes {
            data.extend_from_slice(xy);
        } else {
            // If length doesn't match, return None (like malloc failure in C)
            return None;
        }
    }

    Some(img)
}

pub fn heman_points_from_grid(width: f32, height: f32, cellsize: f32, jitter: f32) -> HemanPoints {
    let cols = (width / cellsize) as i32;
    let rows = (height / cellsize) as i32;
    let ncells = cols * rows;
    let mut result = heman_image_create(ncells, 1, 2);
    
    let rscale = (2.0 * jitter) / 32767.0;
    let mut rng = rand::thread_rng();

    if let Some(ref mut result) = result {
        if let Some(ref mut data) = result.data {
            for j in 0..rows {
                let dst_idx_start = (j * cols * 2) as usize;
                let y = (cellsize * 0.5) + (cellsize * j as f32);
                let mut x = cellsize * 0.5;

                for i in 0..cols {
                    let rx = (rng.gen::<i16>() as f32 * rscale) - jitter;
                    let ry = (rng.gen::<i16>() as f32 * rscale) - jitter;
                    
                    let dst_idx = dst_idx_start + (i * 2) as usize;
                    data[dst_idx] = x + rx;
                    data[dst_idx + 1] = y + ry;
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
    kmVec2Add(&mut r, &scaled_r, &center);
    r
}
pub fn helper_helper_heman_points_from_poisson_1_1(
    pt_ref: &mut KmVec2,
    found_ref: &mut i32,
    j_ref: &mut KmVec2,
    minj_ref: &mut KmVec2,
    maxj_ref: &mut KmVec2,
    width: f32,
    height: f32,
    radius: f32,
    seed: &mut u32,
    rvec: KmVec2,
    r2: f32,
    maxcol: i32,
    maxrow: i32,
    grid: &[i32],
    samples: &[KmVec2],
    invcell: f32,
    ncols: i32,
    sindex: i32,
    delta: &mut KmVec2,
) {
    let mut pt = pt_ref.clone();
    let mut found = *found_ref;
    let mut j = j_ref.clone();
    let mut minj = minj_ref.clone();
    let mut maxj = maxj_ref.clone();

    pt = sample_annulus(radius, samples[sindex as usize].clone(), seed);
    
    if pt.x < 0.0 || pt.x >= width || pt.y < 0.0 || pt.y >= height {
        return;
    }

    minj = pt.clone();
    maxj = pt.clone();
    
    {
        let temp = maxj.clone();
        kmVec2Add(&mut maxj, &temp, &rvec);
    }
    
    {
        let temp = minj.clone();
        kmVec2Subtract(&mut minj, &temp, &rvec);
    }
    
    {
        let temp = minj.clone();
        kmVec2Scale(&mut minj, &temp, invcell);
    }
    
    {
        let temp = maxj.clone();
        kmVec2Scale(&mut maxj, &temp, invcell);
    }

    minj.x = if 0 > (if maxcol > minj.x as i32 { minj.x as i32 } else { maxcol }) {
        0
    } else {
        if maxcol > minj.x as i32 { minj.x as i32 } else { maxcol }
    } as f32;

    maxj.x = if 0 > (if maxcol > maxj.x as i32 { maxj.x as i32 } else { maxcol }) {
        0
    } else {
        if maxcol > maxj.x as i32 { maxj.x as i32 } else { maxcol }
    } as f32;

    minj.y = if 0 > (if maxrow > minj.y as i32 { minj.y as i32 } else { maxrow }) {
        0
    } else {
        if maxrow > minj.y as i32 { minj.y as i32 } else { maxrow }
    } as f32;

    maxj.y = if 0 > (if maxrow > maxj.y as i32 { maxj.y as i32 } else { maxrow }) {
        0
    } else {
        if maxrow > maxj.y as i32 { maxj.y as i32 } else { maxrow }
    } as f32;

    let mut reject = false;
    let mut j_y = minj.y as i32;
    while j_y <= maxj.y as i32 && !reject {
        let mut j_x = minj.x as i32;
        while j_x <= maxj.x as i32 && !reject {
            let entry = grid[(j_y * ncols + j_x) as usize];
            if entry > -1 && entry != sindex {
                kmVec2Subtract(delta, &samples[entry as usize], &pt);
                if kmVec2LengthSq(Some(delta)) < r2 {
                    reject = true;
                }
            }
            j_x += 1;
        }
        j_y += 1;
    }

    if reject {
        return;
    }

    found = 1;
    *pt_ref = pt;
    *found_ref = found;
    *j_ref = j;
    *minj_ref = minj;
    *maxj_ref = maxj;
}
pub fn helper_heman_points_from_poisson_1(
    invcell_ref: &mut f32,
    ncols_ref: &mut i32,
    nactives_ref: &mut i32,
    nsamples_ref: &mut i32,
    pt_ref: &mut KmVec2,
    width: f32,
    height: f32,
    radius: f32,
    maxattempts: i32,
    mut seed: u32,
    rvec: KmVec2,
    r2: f32,
    maxcol: i32,
    maxrow: i32,
    grid: &mut [i32],
    actives: &mut [i32],
    samples: &mut [KmVec2],
) {
    let invcell = *invcell_ref;
    let ncols = *ncols_ref;
    let mut nactives = *nactives_ref;
    let mut nsamples = *nsamples_ref;
    let mut pt = pt_ref.clone();

    let aindex = if randhashf(seed, 0.0, nactives as f32) > (nactives - 1) as f32 {
        nactives - 1
    } else {
        randhashf(seed + 1, 0.0, nactives as f32) as i32
    };
    seed += 2;
    let sindex = actives[aindex as usize];
    let mut found = 0;
    let mut j = KmVec2 { x: 0.0, y: 0.0 };
    let mut minj = KmVec2 { x: 0.0, y: 0.0 };
    let mut maxj = KmVec2 { x: 0.0, y: 0.0 };
    let mut delta = KmVec2 { x: 0.0, y: 0.0 };

    for attempt in 0..maxattempts {
        if found != 0 {
            break;
        }
        helper_helper_heman_points_from_poisson_1_1(
            &mut pt,
            &mut found,
            &mut j,
            &mut minj,
            &mut maxj,
            width,
            height,
            radius,
            &mut seed,
            rvec.clone(),
            r2,
            maxcol,
            maxrow,
            grid,
            samples,
            invcell,
            ncols,
            sindex,
            &mut delta,
        );
    }

    if found != 0 {
        let grid_index = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
        grid[grid_index as usize] = nsamples;
        actives[nactives as usize] = nsamples;
        nactives += 1;
        samples[nsamples as usize] = pt.clone();
        nsamples += 1;
    } else {
        nactives -= 1;
        if nactives <= 0 {
            // In C this would break out of an outer loop, but in Rust we'll just return
            // since we don't have context about the outer loop here
            *invcell_ref = invcell;
            *ncols_ref = ncols;
            *nactives_ref = nactives;
            *nsamples_ref = nsamples;
            *pt_ref = pt;
            return;
        }
        actives[aindex as usize] = actives[nactives as usize];
    }

    *invcell_ref = invcell;
    *ncols_ref = ncols;
    *nactives_ref = nactives;
    *nsamples_ref = nsamples;
    *pt_ref = pt;
}
pub fn helper_helper_heman_points_from_density_1_1(
    pt_ref: &mut KmVec2,
    found_ref: &mut i32,
    j_ref: &mut KmVec2,
    minj_ref: &mut KmVec2,
    maxj_ref: &mut KmVec2,
    density: &HemanImageS,
    minradius: f32,
    maxradius: f32,
    width: f32,
    height: f32,
    seed: &mut u32,
    rvec: KmVec2,
    invcell: f32,
    ncols: i32,
    maxcol: i32,
    maxrow: i32,
    grid: &[i32],
    ngrid: &[i32],
    samples: &[KmVec2],
    gcapacity: i32,
    sindex: i32,
    delta: &mut KmVec2,
) {
    let mut pt = sample_annulus(maxradius, samples[sindex as usize].clone(), seed);
    if pt.x < 0.0 || pt.x >= width || pt.y < 0.0 || pt.y >= height {
        return;
    }

    let mut minj = pt.clone();
    let mut maxj = pt.clone();
    
    let temp_maxj = maxj.clone();
    kmVec2Add(&mut maxj, &temp_maxj, &rvec);
    
    let temp_minj = minj.clone();
    kmVec2Subtract(&mut minj, &temp_minj, &rvec);
    
    let temp_minj = minj.clone();
    kmVec2Scale(&mut minj, &temp_minj, invcell);
    
    let temp_maxj = maxj.clone();
    kmVec2Scale(&mut maxj, &temp_maxj, invcell);

    minj.x = 0.0_f32.max(minj.x.min(maxcol as f32));
    maxj.x = 0.0_f32.max(maxj.x.min(maxcol as f32));
    minj.y = 0.0_f32.max(minj.y.min(maxrow as f32));
    maxj.y = 0.0_f32.max(maxj.y.min(maxrow as f32));

    let mut reject = false;
    let mut densityval = [0.0];
    heman_image_sample(density, pt.x, pt.y, &mut densityval);
    let densityval = densityval[0].sqrt();
    let mindist = maxradius - (densityval * (maxradius - minradius));
    let r2 = mindist * mindist;

    'outer: for y in minj.y as i32..=maxj.y as i32 {
        for x in minj.x as i32..=maxj.x as i32 {
            let grid_index = (y * ncols + x) * gcapacity;
            let ngrid_index = (y * ncols + x) as usize;
            let grid_end = grid_index + ngrid[ngrid_index];
            
            for g in grid_index..grid_end {
                let entry = grid[g as usize];
                if entry != sindex {
                    kmVec2Subtract(delta, &samples[entry as usize], &pt);
                    if kmVec2LengthSq(Some(delta)) < r2 {
                        reject = true;
                        break 'outer;
                    }
                }
            }
        }
    }

    if reject {
        return;
    }

    *found_ref = 1;
    *pt_ref = pt;
    *j_ref = KmVec2 { x: 0.0, y: 0.0 }; // Initialize j as it's not used in the loop
    *minj_ref = minj;
    *maxj_ref = maxj;
}
pub fn helper_heman_points_from_density_1(
    gindex_ref: &mut i32,
    gcapacity_ref: &mut i32,
    nactives_ref: &mut i32,
    nsamples_ref: &mut i32,
    pt_ref: &mut KmVec2,
    density: &HemanImage,
    minradius: f32,
    maxradius: f32,
    width: f32,
    height: f32,
    maxattempts: i32,
    mut seed: u32,
    rvec: KmVec2,
    invcell: f32,
    ncols: i32,
    maxcol: i32,
    maxrow: i32,
    grid: &mut [i32],
    ngrid: &mut [i32],
    actives: &mut [i32],
    samples: &mut [KmVec2],
) {
    let mut gindex = *gindex_ref;
    let gcapacity = *gcapacity_ref;
    let mut nactives = *nactives_ref;
    let mut nsamples = *nsamples_ref;
    let mut pt = pt_ref.clone();

    let aindex = if randhashf(seed, 0.0, nactives as f32) > (nactives - 1) as f32 {
        nactives - 1
    } else {
        randhashf(seed, 0.0, nactives as f32) as i32
    };
    seed += 1;
    let sindex = actives[aindex as usize];
    let mut found = 0;
    let mut j = KmVec2 { x: 0.0, y: 0.0 };
    let mut minj = KmVec2 { x: 0.0, y: 0.0 };
    let mut maxj = KmVec2 { x: 0.0, y: 0.0 };
    let mut delta = KmVec2 { x: 0.0, y: 0.0 };

    if let Some(density) = density.as_deref() {
        for attempt in 0..maxattempts {
            helper_helper_heman_points_from_density_1_1(
                &mut pt,
                &mut found,
                &mut j,
                &mut minj,
                &mut maxj,
                density,
                minradius,
                maxradius,
                width,
                height,
                &mut seed,
                rvec.clone(),
                invcell,
                ncols,
                maxcol,
                maxrow,
                grid,
                ngrid,
                samples,
                gcapacity,
                sindex,
                &mut delta,
            );

            if found != 0 {
                break;
            }
        }
    }

    if found != 0 {
        let grid_index = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
        if ngrid[grid_index as usize] >= gcapacity {
            found = 0;
        }
    }

    if found != 0 {
        actives[nactives as usize] = nsamples;
        nactives += 1;
        gindex = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
        let grid_pos = (gcapacity * gindex) + ngrid[gindex as usize];
        grid[grid_pos as usize] = nsamples;
        ngrid[gindex as usize] += 1;
        samples[nsamples as usize] = pt.clone();
        nsamples += 1;
    } else {
        nactives -= 1;
        if nactives <= 0 {
            return;
        }
        actives[aindex as usize] = actives[nactives as usize];
    }

    *gindex_ref = gindex;
    *gcapacity_ref = gcapacity;
    *nactives_ref = nactives;
    *nsamples_ref = nsamples;
    *pt_ref = pt;
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
    let mut invcell = 1.0 / cellsize;
    let mut ncols = (width * invcell).ceil() as i32;
    let nrows = (height * invcell).ceil() as i32;
    let maxcol = ncols - 1;
    let maxrow = nrows - 1;
    let ncells = ncols * nrows;

    let mut grid = vec![-1; ncells as usize];
    let mut actives = vec![0; ncells as usize];
    let mut nactives = 0;
    let mut result = heman_image_create(ncells, 1, 2);
    let samples = if let Some(ref mut res) = result {
        if let Some(ref mut data) = res.data {
            unsafe { std::mem::transmute::<&mut [f32], &mut [KmVec2]>(data) }
        } else {
            &mut []
        }
    } else {
        &mut []
    };
    let mut nsamples = 0;

    let mut pt = KmVec2 {
        x: (width * randhash(seed) as f32 * rscale),
        y: (height * randhash(seed + 1) as f32 * rscale),
    };
    seed += 2;

    let grid_idx = (pt.x * invcell) as i32 + ncols * (pt.y * invcell) as i32;
    grid[grid_idx as usize] = nsamples;
    actives[nactives as usize] = nsamples;
    nactives += 1;
    samples[nsamples as usize] = pt.clone();
    nsamples += 1;

    while nsamples < ncells {
        helper_heman_points_from_poisson_1(
            &mut invcell,
            &mut ncols,
            &mut nactives,
            &mut nsamples,
            &mut pt,
            width,
            height,
            radius,
            maxattempts,
            seed,
            rvec.clone(),
            r2,
            maxcol,
            maxrow,
            &mut grid,
            &mut actives,
            samples,
        );
    }

    if let Some(ref mut res) = result {
        res.width = nsamples;
    }
    result
}
pub fn heman_points_from_density(density: &HemanImage, minradius: f32, maxradius: f32) -> HemanPoints {
    // Assert that density has exactly 1 band
    if let Some(density) = density {
        assert_eq!(density.nbands, 1);
    } else {
        return None;
    }

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
    let ntexels = (cellsize * density.as_ref().unwrap().width as f32) as i32;
    let mut gcapacity = ntexels * ntexels;
    
    let mut grid = vec![0; (ncells * gcapacity) as usize];
    let mut ngrid = vec![0; ncells as usize];
    let mut actives = vec![0; ncells as usize];
    let mut nactives = 0;
    let maxsamples = ncells * gcapacity;
    
    let mut result = heman_image_create(maxsamples, 1, 2);
    if result.is_none() {
        return None;
    }
    
    let mut samples_slice = if let Some(ref mut res) = result {
        unsafe {
            std::slice::from_raw_parts_mut(
                res.data.as_mut().unwrap().as_mut_ptr() as *mut KmVec2,
                maxsamples as usize,
            )
        }
    } else {
        return None;
    };
    
    let mut nsamples = 0;
    let mut pt = KmVec2 {
        x: (width * randhash(seed) as f32) * rscale,
        y: (height * randhash(seed + 1) as f32) * rscale,
    };
    seed += 2;
    
    actives[nactives as usize] = nsamples;
    nactives += 1;
    let mut gindex = ((pt.x * invcell) as i32) + (ncols * ((pt.y * invcell) as i32));
    grid[(gcapacity * gindex + ngrid[gindex as usize]) as usize] = nsamples;
    ngrid[gindex as usize] += 1;
    samples_slice[nsamples as usize] = pt.clone();
    nsamples += 1;
    
    while nsamples < maxsamples {
        helper_heman_points_from_density_1(
            &mut gindex,
            &mut gcapacity,
            &mut nactives,
            &mut nsamples,
            &mut pt,
            density,
            minradius,
            maxradius,
            width,
            height,
            maxattempts,
            seed,
            rvec.clone(),
            invcell,
            ncols,
            maxcol,
            maxrow,
            &mut grid,
            &mut ngrid,
            &mut actives,
            samples_slice,
        );
    }
    
    if let Some(ref mut res) = result {
        res.width = nsamples;
    }
    
    result
}
