use crate::*;
use std::io;
use std::time::Duration;
use std::time::Instant;
use lazy_static::lazy_static;
use std::sync::Mutex;
use rand::Rng;
use std::sync::atomic::Ordering;
use std::io::Write;
pub fn bench(bm: fn(), label: Option<&str>) {
    // Print the label with right-aligned formatting (similar to %18s in C)
    if let Some(label) = label {
        print!(" {:>18}", label);
    } else {
        print!(" {:>18}", "");
    }
    
    // Flush stdout immediately (equivalent to fflush(stdout) in C)
    io::stdout().flush().expect("Failed to flush stdout");
    
    // Call the benchmark function
    bm();
}

pub fn start() {
    *START_TIME.lock().unwrap() = Instant::now();
}

lazy_static! {
    pub static ref START_TIME: Mutex<Instant> = Mutex::new(Instant::now());
}

pub fn stop() {
    let start_time = START_TIME.lock().unwrap();
    let duration = start_time.elapsed().as_secs_f64();
    println!(": \x1b[32m{:.4}\x1b[0ms", duration);
}

pub fn mark_insert() {
    let n = NODES.load(Ordering::SeqCst);
    let val = Box::new(10);
    let mut tree = match quadtree_new(0.0, 0.0, 1000.0, 1000.0) {
        Some(t) => t,
        None => return, // Handle quadtree creation failure if needed
    };
    
    let mut rng = rand::thread_rng();
    
    start();
    for _ in 0..n {
        let x = rng.gen_range(0.0..1000.0);
        let y = rng.gen_range(0.0..1000.0);
        quadtree_insert(&mut tree, x, y, val.clone());
    }
    stop();
    
    println!("  {:18} {}", "length:", tree.length);
    quadtree_free(tree);
}
