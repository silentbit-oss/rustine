use std::env;
use translate_without_break_down::*;
pub fn main() {
    let args: Vec<String> = std::env::args().collect();
    
    if args.len() < 4 {
        println!("Usage: cli indicator_name infile outfile");
        return;
    }

    let name = args.get(1).map(|s| s.as_str());
    let in_ = args.get(2).map(|s| s.as_str());
    let out = args.get(3).map(|s| s.as_str());

    run(name, in_, out);
}
