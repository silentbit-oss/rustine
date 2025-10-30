use crate::*;
use std::io;
use std::time::Duration;
use std::time::Instant;
use std::sync::Mutex;
use lazy_static::lazy_static;
use rand::Rng;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::io::Write;


pub fn bench(bm: fn(), label: Option<&str>) {
    // Print the label with right-aligned formatting (similar to C's %18s)
    if let Some(label) = label {
        print!(" {:>18}", label);
    } else {
        print!(" {:>18}", ""); // Handle None case (equivalent to NULL in C)
    }
    
    // Flush stdout immediately (equivalent to fflush(stdout) in C)
    io::stdout().flush().expect("Failed to flush stdout");
    
    // Call the benchmark function
    bm();
}

pub fn start() {
    let mut start_time = START_TIME.lock().unwrap();
    *start_time = Some(Instant::now().elapsed());
}

lazy_static! {
    pub static ref startTime: Mutex<Option<Instant>> = Mutex::new(None);
}

pub fn stop() {
    let duration = if let Some(start_time) = *startTime.lock().unwrap() {
        start_time.elapsed().as_secs_f32()
    } else {
        0.0
    };
    println!(": \x1b[32m{:.4}\x1b[0ms", duration);
}
pub fn mark_insert() {
    let n = NODES.load(Ordering::SeqCst);
    let mut tree = quadtree_new(0.0, 0.0, 1000.0, 1000.0).unwrap();
    let mut rng = rand::thread_rng();

    start();
    
    for _ in 0..n {
        let x = rng.gen_range(0.0..1000.0);
        let y = rng.gen_range(0.0..1000.0);
        let val: Box<dyn std::any::Any> = Box::new(10);
        quadtree_insert(&mut *tree, x, y, val);
    }

    stop();
    println!("  {:18} {}", "length:", tree.length);
    quadtree_free(tree);
}
