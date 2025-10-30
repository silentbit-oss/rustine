use std::env;
use translate_without_break_down::*;
pub fn main() {
    println!("Running test 1...");
    let result1 = test_1();
    if result1 != 0 {
        println!("test 1 failed with code {}", result1);
        std::process::exit(result1);
    }
    println!("test 1 passed.");

    println!("Running test 2...");
    let result2 = test_2();
    if result2 != 0 {
        println!("test 2 failed with code {}", result2);
        std::process::exit(result2);
    }
    println!("test 2 passed.");

    println!("Running test 3...");
    let result3 = test_3();
    if result3 != 0 {
        println!("test 3 failed with code {}", result3);
        std::process::exit(result3);
    }
    println!("test 3 passed.");

    println!("Running test 4...");
    let result4 = test_4();
    if result4 != 0 {
        println!("test 4 failed with code {}", result4);
        std::process::exit(result4);
    }
    println!("test 4 passed.");

    println!("Running test 5...");
    let result5 = test_5();
    if result5 != 0 {
        println!("test 5 failed with code {}", result5);
        std::process::exit(result5);
    }
    println!("test 5 passed.");

    println!("Running test 6...");
    let result6 = test_6();
    if result6 != 0 {
        println!("test 6 failed with code {}", result6);
        std::process::exit(result6);
    }
    println!("test 6 passed.");

    println!("Running test 7...");
    let result7 = test_7();
    if result7 != 0 {
        println!("test 7 failed with code {}", result7);
        std::process::exit(result7);
    }
    println!("test 7 passed.");

    println!("Running test 8...");
    let result8 = test_8();
    if result8 != 0 {
        println!("test 8 failed with code {}", result8);
        std::process::exit(result8);
    }
    println!("test 8 passed.");

    println!("Running test 9...");
    let result9 = test_9();
    if result9 != 0 {
        println!("test 9 failed with code {}", result9);
        std::process::exit(result9);
    }
    println!("test 9 passed.");

    println!("Running test 10...");
    let result10 = test_10();
    if result10 != 0 {
        println!("test 10 failed with code {}", result10);
        std::process::exit(result10);
    }
    println!("test 10 passed.");

    println!("All tests passed successfully!");
}
