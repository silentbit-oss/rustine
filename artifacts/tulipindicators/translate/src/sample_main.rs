use translate::*;
use std::env;
use std::ffi::CStr;
use std::str::FromStr;
pub fn main() -> Result<(), Box<dyn std::error::Error>> {
    let info = &*TI_INDICATORS.lock().unwrap();
    let mut info_idx = 0;
    
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        println!("No indicator given.");
        println!("Example:");
        println!("\tsample ma 5");
        return Ok(());
    }

    if args[1] == "--version" {
        println!("TI VERSION: {}, TI BUILD: {}", "0.9.2", 1645649572);
        return Ok(());
    }

    if args[1] == "--list" {
        helper_main_2(info, info_idx);
        return Ok(());
    }

    let indicator_info = match ti_find_indicator(Some(&args[1])) {
        Some(info) => info,
        None => {
            println!("Couldn't find indicator: {}", args[1]);
            return Ok(());
        }
    };

    let mut inputs: Vec<Option<&[f64]>> = vec![None; 5];
    let mut out_guard = OUT.lock().unwrap();
    let rows: &mut [[f64; 4000]] = &mut *out_guard;
    let (first, rest) = rows.split_at_mut(1);
    let (second, third) = rest.split_at_mut(1);

    let mut outputs: Vec<&mut [f64]> = Vec::with_capacity(5);
    outputs.push(&mut first[0][..]);
    outputs.push(&mut second[0][..]);
    outputs.push(&mut third[0][..]);
    
    let mut o = 0;
    let mut h = 0;
    let mut l = 0;
    let mut c = 0;
    let mut r = 0;
    let mut r2 = 0;
    let mut v = 0;
    let mut a = 0;

    for mut j in 0..indicator_info.inputs {
        helper_main_1(
            &mut o,
            &mut h,
            &mut l,
            &mut c,
            &mut r,
            &mut r2,
            &mut v,
            &mut j,
            indicator_info,
            &mut inputs,
        );
    }

    let alts = ["acos", "asin", "atan", "cosh", "sinh", "tanh", "todeg"];
    for alt in alts.iter() {
        if *alt == indicator_info.name.as_ref().unwrap() {
            r = 0;
            a = 1;
            for j in 0..indicator_info.inputs {
                inputs[j as usize] = Some(&ALTERNATIVE);
            }
            break;
        }
    }

    let mut options = [0.0; 10];
    for i in 0..indicator_info.options {
        if args.len() < (3 + i as usize) {
            println!("*ERROR NOT ENOUGH OPTIONS*");
            for k in 1..args.len() {
                print!("{} ", args[k]);
            }
            println!();
            return Ok(());
        }
        options[i as usize] = f64::from_str(&args[2 + i as usize]).unwrap_or(0.0);
    }

    let start = if let Some(start_fn) = &indicator_info.start {
        start_fn(&options)
    } else {
        0
    };

    let input_slices: Vec<&[f64]> = inputs.iter().filter_map(|&x| x).collect();
    let ret = (indicator_info.indicator)(15, &input_slices, &options, &mut outputs);

    if ret == 0 {
        helper_main_3(indicator_info, o, h, l, c, r, r2, v, a, start);
        Ok(())
    } else {
        if ret == 1 {
            println!("*ERROR INVALID OPTION*");
            for i in 1..args.len() {
                print!("{} ", args[i]);
            }
            println!();
        } else {
            println!("*ERROR*");
        }
        Ok(())
    }
}
