use translate::*;
use std::env;
pub fn main() {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 4 {
        println!("Usage: cli indicator_name infile outfile");
        return;
    }
    let name = Some(args[1].as_str());
    let in_path = Some(args[2].as_str());
    let out_path = Some(args[3].as_str());
    run(name, in_path, out_path);
}
