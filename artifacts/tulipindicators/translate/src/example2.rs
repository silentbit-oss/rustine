use translate::*;
use std::env;
pub fn main() {
    println!("This program is an example of looping through");
    println!("each of the available indicators.\n");

    let ti_indicators = TI_INDICATORS.lock().unwrap();
    for info in ti_indicators.iter() {
        if info.name.is_none() {
            break;
        }

        println!(
            "{} ({}) has type {} with: {} inputs, {} options, {} outputs.",
            info.name.as_ref().unwrap(),
            info.full_name.as_ref().unwrap(),
            info.type_,
            info.inputs,
            info.options,
            info.outputs
        );

        print!("   inputs: ");
        for i in 0..info.inputs {
            if i > 0 {
                print!(", ");
            }
            if let Some(name) = info.input_names[i as usize].as_ref() {
                print!("{}", name);
            }
        }

        println!();
        print!("   options: ");
        for i in 0..info.options {
            if i > 0 {
                print!(", ");
            }
            if let Some(name) = info.option_names[i as usize].as_ref() {
                print!("{}", name);
            }
        }

        println!();
        print!("   outputs: ");
        for i in 0..info.outputs {
            if i > 0 {
                print!(", ");
            }
            if let Some(name) = info.output_names[i as usize].as_ref() {
                print!("{}", name);
            }
        }

        println!("\n");
    }
}
