use translate_new::*;
use std::env;
pub fn main() {
	println!("* main");
    println!("=== Running various inputs test ===");
    test_aptx_encode_decode_various();
    println!("\n=== Running HD mode test ===");
    test_aptx_hd_mode();
    println!("\n=== Running decode sync test ===");
    test_aptx_decode_sync();
    println!("\n=== Running invalid inputs test ===");
    test_aptx_invalid_inputs();
}
