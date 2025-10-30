use translate_new::*;
use std::env;
pub fn main() {
	println!("* main");
    println!("=== Running various inputs test ===");
    // __AUTOCOMMENT__:7071b7b6-df47-4654-a0e6-7c87f3666172 test_aptx_encode_decode_various();
    println!("\n=== Running HD mode test ===");
    // __AUTOCOMMENT__:8fb4ce7f-85a8-4540-8a06-b399e963976c test_aptx_hd_mode();
    println!("\n=== Running decode sync test ===");
    test_aptx_decode_sync();
    println!("\n=== Running invalid inputs test ===");
    test_aptx_invalid_inputs();
}
