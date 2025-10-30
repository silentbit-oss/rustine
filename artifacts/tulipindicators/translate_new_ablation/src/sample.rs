use rand::Rng;
use std::env;
use std::ffi::CStr;
use std::sync::MutexGuard;
use translate_without_break_down::*;
pub fn main() -> std::process::ExitCode {
    let args: Vec<String> = std::env::args().collect();
    let argc = args.len();
    let argv: Vec<&str> = args.iter().map(|s| s.as_str()).collect();

    if argc < 2 {
        println!("No indicator given.");
        println!("Example:");
        println!("\tsample ma 5");
        return std::process::ExitCode::from(1);
    }

    if argv[1] == "--version" {
        println!("TI VERSION: {}, TI BUILD: {}", "0.9.2", 1645649572);
        return std::process::ExitCode::SUCCESS;
    }

    let ti_indicators = TI_INDICATORS.lock().unwrap();
    let mut info = &ti_indicators[0];
    let mut info_idx = 0;

    if argv[1] == "--list" {
        loop {
            match info.type_ {
                1 => print!("type overlay "),
                2 => print!("type indicator "),
                3 => print!("type math "),
                4 => print!("type simple "),
                _ => print!("type unknown "),
            }

            print!("name {} ", info.name.as_ref().unwrap_or(&"".to_string()));
            print!("full_name {{{}}} ", info.full_name.as_ref().unwrap_or(&"".to_string()));

            print!("inputs {{");
            for i in 0..info.inputs as usize {
                if i > 0 {
                    print!(" ");
                }
                print!("{}", info.input_names[i].as_ref().unwrap_or(&"".to_string()));
            }
            print!("}} ");

            print!("options {{");
            for i in 0..info.options as usize {
                if i > 0 {
                    print!(" ");
                }
                print!("{{{}}}", info.option_names[i].as_ref().unwrap_or(&"".to_string()));
            }
            print!("}} ");

            print!("outputs {{");
            for i in 0..info.outputs as usize {
                if i > 0 {
                    print!(" ");
                }
                print!("{{{}}}", info.output_names[i].as_ref().unwrap_or(&"".to_string()));
            }
            print!("}}");

            println!();

            info_idx += 1;
            if info_idx >= ti_indicators.len() || ti_indicators[info_idx].name.is_none() {
                break;
            }
            info = &ti_indicators[info_idx];
        }
        return std::process::ExitCode::SUCCESS;
    }

    let indicator_name = argv[1];
    let found_info = match ti_find_indicator(Some(indicator_name)) {
        Some(found) => found,
        None => {
            println!("Couldn't find indicator: {}", argv[1]);
            return std::process::ExitCode::from(1);
        }
    };
    let info = found_info;

    // Create a vector to hold input slices
    let mut inputs: Vec<&[f64]> = Vec::new();

    let mut o = false;
    let mut h = false;
    let mut l = false;
    let mut c = false;
    let mut r = false;
    let mut r2 = false;
    let mut v = false;
    let mut a = false;

    // First collect all the data we need
    let high_data = if info.input_names.iter().any(|n| n.as_deref() == Some("high")) {
        h = true;
        Some(HIGH.lock().unwrap().to_vec())
    } else {
        None
    };

    let volume_data = if info.input_names.iter().any(|n| n.as_deref() == Some("volume")) {
        v = true;
        Some(VOLUME.lock().unwrap().to_vec())
    } else {
        None
    };

    for j in 0..info.inputs as usize {
        let empty = "".to_string();
        let input_name = info.input_names[j].as_ref().unwrap_or(&empty);
        match input_name.as_str() {
            "open" => {
                inputs.push(&OPEN);
                o = true;
            }
            "high" => {
                inputs.push(high_data.as_ref().unwrap().as_slice());
            }
            "low" => {
                inputs.push(&LOW);
                l = true;
            }
            "close" => {
                inputs.push(&CLOSE);
                c = true;
            }
            "volume" => {
                inputs.push(volume_data.as_ref().unwrap().as_slice());
            }
            "real" => {
                if !r {
                    inputs.push(&CLOSE);
                    r = true;
                } else {
                    inputs.push(&OPEN);
                    r2 = true;
                }
            }
            _ => panic!("Unknown input name"),
        }
    }

    let alts = ["acos", "asin", "atan", "cosh", "sinh", "tanh", "todeg"];
    for alt in alts.iter() {
        if *alt == info.name.as_ref().unwrap_or(&"".to_string()) {
            r = false;
            a = true;
            inputs.clear();
            for _ in 0..info.inputs as usize {
                inputs.push(&ALTERNATIVE[..]);
            }
            break;
        }
    }

    let mut options = [0.0; 10];
    for i in 0..info.options as usize {
        if argc < 3 + i {
            println!("*ERROR NOT ENOUGH OPTIONS*");
            for k in 1..argc {
                print!("{} ", argv[k]);
            }
            println!();
            return std::process::ExitCode::from(1);
        }
        options[i] = argv[2 + i].parse().unwrap_or(0.0);
    }

    let start = match &info.start {
        Some(func) => func(&options),
        None => 0,
    };

    let mut out_guard = OUT.lock().unwrap();
    // Destructure the array into separate row references
    let [row0, row1, row2] = &mut *out_guard;
    // Create mutable slices for each row
    let output0 = &mut row0[..15];
    let output1 = &mut row1[..15];
    let output2 = &mut row2[..15];
    let outputs_arr = &mut [output0, output1, output2];

    let ret = (info.indicator)(
        15,
        Some(&inputs),
        Some(&options),
        Some(outputs_arr),
    );

    if ret == 0 {
        let mut bad = false;
        print!("date        ");
        if o { print!(" open   "); }
        if h { print!(" high   "); }
        if l { print!(" low    "); }
        if c { print!(" close  "); }
        if v { print!(" volume "); }
        if r { print!(" input  "); }
        if r2 { print!(" input2  "); }
        if a { print!(" input  "); }

        for i in 0..info.outputs as usize {
            print!(" {}", info.output_names[i].as_ref().unwrap_or(&"".to_string()));
        }
        println!();

        let high_guard = HIGH.lock().unwrap();
        let volume_guard = VOLUME.lock().unwrap();

        for i in 0..15 {
            print!("{}", DATET[i]);
            if o { print!(" {:8.2}", OPEN[i]); }
            if h { print!(" {:8.2}", high_guard[i]); }
            if l { print!(" {:8.2}", LOW[i]); }
            if c { print!(" {:8.2}", CLOSE[i]); }
            if v { print!(" {:8.0}", volume_guard[i]); }
            if r { print!(" {:8.2}", CLOSE[i]); }
            if r2 { print!(" {:8.2}", OPEN[i]); }
            if a { print!(" {:8.2}", ALTERNATIVE[i]); }

            if i >= start as usize {
                for k in 0..info.outputs as usize {
                    if out_guard[k][i - start as usize].is_nan() {
                        bad = true;
                    }
                    print!(" {:8.3}", out_guard[k][i - start as usize]);
                }
            }
            println!();
        }

        if bad {
            println!("\nERROR NaN in outputs ({}).", info.name.as_ref().unwrap_or(&"".to_string()));
            return std::process::ExitCode::from(1);
        }
        return std::process::ExitCode::SUCCESS;
    } else {
        if ret == 1 {
            println!("*ERROR INVALID OPTION*");
            for i in 1..argc {
                print!("{} ", argv[i]);
            }
            println!();
        } else {
            println!("*ERROR*");
        }
        return std::process::ExitCode::from(1);
    }
}
