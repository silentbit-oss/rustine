use crate::*;
use std::sync::Mutex;
use std::ffi::CStr;
use std::fmt::Write;
use std::os::raw::c_char;

pub fn helper_main_2(info: &[TiIndicatorInfo], mut info_idx: usize) -> i32 {
    let mut current_info = &info[info_idx];
    
    loop {
        match current_info.type_ {
            1 => print!("type overlay "),
            2 => print!("type indicator "),
            3 => print!("type math "),
            4 => print!("type simple "),
            _ => print!("type unknown "),
        }

        if let Some(name) = &current_info.name {
            print!("name {} ", name);
        }

        if let Some(full_name) = &current_info.full_name {
            print!("full_name {{{}}} ", full_name);
        }

        print!("inputs {{");
        for i in 0..current_info.inputs as usize {
            if i > 0 {
                print!(" ");
            }
            if let Some(input_name) = &current_info.input_names[i] {
                print!("{}", input_name);
            }
        }
        print!("}} ");

        print!("options {{");
        for i in 0..current_info.options as usize {
            if i > 0 {
                print!(" ");
            }
            if let Some(option_name) = &current_info.option_names[i] {
                print!("{{{}}}", option_name);
            }
        }
        print!("}} ");

        print!("outputs {{");
        for i in 0..current_info.outputs as usize {
            if i > 0 {
                print!(" ");
            }
            if let Some(output_name) = &current_info.output_names[i] {
                print!("{{{}}}", output_name);
            }
        }
        print!("}}");

        println!();

        info_idx += 1;
        if info_idx >= info.len() {
            break;
        }
        current_info = &info[info_idx];
        
        if current_info.name.is_none() {
            break;
        }
    }

    0
}

pub fn helper_helper_main_3_1(
    k_ref: &mut i32,
    bad_ref: &mut i32,
    info: &TiIndicatorInfo,
    o: i32,
    h: i32,
    l: i32,
    c: i32,
    r: i32,
    r2: i32,
    v: i32,
    a: i32,
    start: i32,
    i: i32,
) {
    let mut k = *k_ref;
    let mut bad = *bad_ref;

    print!("{}", DATET[i as usize]);
    
    if o != 0 {
        print!(" {:8.2}", OPEN.lock().unwrap()[i as usize]);
    }
    if h != 0 {
        print!(" {:8.2}", HIGH.lock().unwrap()[i as usize]);
    }
    if l != 0 {
        print!(" {:8.2}", LOW.lock().unwrap()[i as usize]);
    }
    if c != 0 {
        print!(" {:8.2}", CLOSE[i as usize]);
    }
    if v != 0 {
        print!(" {:8.0}", VOLUME.lock().unwrap()[i as usize]);
    }
    if r != 0 {
        print!(" {:8.2}", CLOSE[i as usize]);
    }
    if r2 != 0 {
        print!(" {:8.2}", OPEN.lock().unwrap()[i as usize]);
    }
    if a != 0 {
        print!(" {:8.2}", ALTERNATIVE[i as usize]);
    }

    if i >= start {
        let out = OUT.lock().unwrap();
        for k_idx in 0..info.outputs {
            let val = out[k_idx as usize][(i - start) as usize];
            if val.is_nan() {
                bad = 1;
            }
            print!(" {:8.3}", val);
        }
    }

    println!();
    
    *k_ref = k;
    *bad_ref = bad;
}

pub fn helper_main_3(
    info: &TiIndicatorInfo,
    o: i32,
    h: i32,
    l: i32,
    c: i32,
    r: i32,
    r2: i32,
    v: i32,
    a: i32,
    start: i32,
) -> i32 {
    let mut output = String::new();
    write!(output, "date        ").unwrap();
    
    if o != 0 {
        write!(output, " open   ").unwrap();
    }
    if h != 0 {
        write!(output, " high   ").unwrap();
    }
    if l != 0 {
        write!(output, " low    ").unwrap();
    }
    if c != 0 {
        write!(output, " close  ").unwrap();
    }
    if v != 0 {
        write!(output, " volume ").unwrap();
    }
    if r != 0 {
        write!(output, " input  ").unwrap();
    }
    if r2 != 0 {
        write!(output, " input2  ").unwrap();
    }
    if a != 0 {
        write!(output, " input  ").unwrap();
    }
    
    for i in 0..info.outputs {
        if let Some(name) = &info.output_names[i as usize] {
            write!(output, " {}", name).unwrap();
        }
    }
    
    println!("{}", output);
    
    let mut bad = 0;
    let mut k = 0;
    
    for i in 0..15 {
        helper_helper_main_3_1(
            &mut k,
            &mut bad,
            info,
            o,
            h,
            l,
            c,
            r,
            r2,
            v,
            a,
            start,
            i,
        );
    }
    
    if bad != 0 {
        if let Some(name) = &info.name {
            println!("\nERROR NaN in outputs ({}).", name);
        }
        return 1;
    }
    
    0
}
pub fn helper_main_1(
    o_ref: &mut i32,
    h_ref: &mut i32,
    l_ref: &mut i32,
    c_ref: &mut i32,
    r_ref: &mut i32,
    r2_ref: &mut i32,
    v_ref: &mut i32,
    j_ref: &mut i32,
    info: &TiIndicatorInfo,
    inputs: &mut [Option<&'static [f64]>],
) {
    let mut o = *o_ref;
    let mut h = *h_ref;
    let mut l = *l_ref;
    let mut c = *c_ref;
    let mut r = *r_ref;
    let mut r2 = *r2_ref;
    let mut v = *v_ref;
    let j = *j_ref;

    let j_usize = j as usize; // Convert i32 to usize for indexing
    
    let input_name = info.input_names[j_usize].as_ref().unwrap();
    let input_name_cstr = CStr::from_bytes_with_nul(input_name.as_bytes()).unwrap();

    match input_name_cstr.to_str().unwrap() {
        "open" => {
            inputs[j_usize] = Some(Box::leak(Box::new(*OPEN.lock().unwrap())));
            o = 1;
        }
        "high" => {
            inputs[j_usize] = Some(Box::leak(Box::new(*HIGH.lock().unwrap())));
            h = 1;
        }
        "low" => {
            inputs[j_usize] = Some(Box::leak(Box::new(*LOW.lock().unwrap())));
            l = 1;
        }
        "close" => {
            inputs[j_usize] = Some(&CLOSE);
            c = 1;
        }
        "volume" => {
            inputs[j_usize] = Some(Box::leak(Box::new(*VOLUME.lock().unwrap())));
            v = 1;
        }
        "real" => {
            if r == 0 {
                inputs[j_usize] = Some(&CLOSE);
                r = 1;
            } else {
                inputs[j_usize] = Some(Box::leak(Box::new(*OPEN.lock().unwrap())));
                r2 = 1;
            }
        }
        _ => panic!("Invalid input name"),
    }

    *o_ref = o;
    *h_ref = h;
    *l_ref = l;
    *c_ref = c;
    *r_ref = r;
    *r2_ref = r2;
    *v_ref = v;
    *j_ref = j;
}
