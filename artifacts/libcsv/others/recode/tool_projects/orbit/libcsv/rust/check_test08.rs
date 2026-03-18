fn main() {
    let test08_data = b"\" abc\"                                             \
                                                     \
                                                     \
                                                     \
                                                     \
                                                     \
                                                     \
                                                     \
                                          \", \"123\"";
    
    println!("test08_data length: {}", test08_data.len());
    println!("First 60 bytes:");
    for i in 0..60.min(test08_data.len()) {
        if i % 10 == 0 {
            print!("\n{:3}: ", i);
        }
        print!("{:02x} ", test08_data[i]);
    }
    println!("\n");
    
    // Expected: " abc" + 45 spaces + 7*53 spaces + 42 spaces + ", "123"
    // = 6 + 45 + 371 + 42 + 8 = 472
    let expected_data_len = 6 + 45 + 371 + 42 + 8;
    println!("Expected data length: {}", expected_data_len);
}
