use crate::*;
use lazy_static::lazy_static;
use ncurses::cbreak;
use ncurses::initscr;
use ncurses::keypad;
use ncurses::noecho;
use rand::Rng;
use std::sync::Mutex;
use std::sync::atomic::Ordering;
lazy_static! {
    pub static ref SCREEN: std::sync::Mutex<Option<Box<[Box<[i32]>]>>> = 
        std::sync::Mutex::new(None);
}

pub fn cleanup_test_environment() {
    // Assuming endwin() is an external C function that needs to be called
    // If there's a Rust equivalent, it should be used instead
    unsafe { endwin(); }

    // Lock the SCREEN mutex to access the global variable
    let mut screen_guard = SCREEN.lock().unwrap();
    
    // Take ownership of the screen data, replacing it with None
    if let Some(screen) = screen_guard.take() {
        // Iterate through each row (0..80 in C, which is 0..80 in Rust since the upper bound is exclusive)
        for row in screen.iter() {
            // The row is already a Box<[i32]>, which will be automatically dropped when the screen is dropped
            // No explicit free needed in Rust
        }
        // The entire screen Box<[Box<[i32]>]> will be dropped here, freeing all memory
    }
}

// If endwin() is a C function, we need to declare it as extern
extern "C" {
    fn endwin();
}
pub fn test_validchar_function() {
    println!("Testing validchar function...");
    assert_eq!(validchar('#'), 0);
    assert_eq!(validchar(' '), 0);
    assert_eq!(validchar(127 as char), 0);
    assert_eq!(validchar('a'), 1);
    assert_eq!(validchar('Z'), 1);
    assert_eq!(validchar('0'), 1);
    assert_eq!(validchar('@'), 1);
    assert_eq!(validchar('!'), 1);
    assert_eq!(validchar('~'), 1);
    println!("✓ validchar tests passed!");
}
pub fn setup_test_environment() {
    // Initialize the curses environment
    initscr();
    keypad(ncurses::stdscr(), true);
    noecho();
    cbreak();

    // Check if screen needs initialization
    {
        let mut screen = SCREEN.lock().unwrap();
        if screen.is_none() {
            initialize_arrays();
        }
    }

    // Set up robot
    {
        let mut robot = ROBOT.lock().unwrap();
        *robot = Some(ScreenObject {
            x: 10,
            y: 10,
            character: '#',
            color: 0,
            bold: false,
        });

        // Update screen position
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[10 as usize][10 as usize] = 0;
        }
    }

    // Set up kitten
    {
        let mut kitten = KITTEN.lock().unwrap();
        kitten.x = 15;
        kitten.y = 10;
        kitten.character = '*';
        kitten.color = 1;
        kitten.bold = true;

        // Update screen position
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[kitten.x as usize][kitten.y as usize] = 1;
        }
    }
}

pub fn test_invalid_input_handling() {
    println!("Testing invalid input handling...");
    setup_test_environment();
    
    let robot_lock = ROBOT.lock().unwrap();
    let robot = robot_lock.as_ref().unwrap();
    let orig_x = robot.x;
    let orig_y = robot.y;
    drop(robot_lock); // Release the lock before calling process_input
    
    process_input('x' as i32);
    {
        let robot_lock = ROBOT.lock().unwrap();
        let robot = robot_lock.as_ref().unwrap();
        assert!(robot.x == orig_x && robot.y == orig_y);
    }
    
    process_input('1' as i32);
    {
        let robot_lock = ROBOT.lock().unwrap();
        let robot = robot_lock.as_ref().unwrap();
        assert!(robot.x == orig_x && robot.y == orig_y);
    }
    
    process_input(999);
    {
        let robot_lock = ROBOT.lock().unwrap();
        let robot = robot_lock.as_ref().unwrap();
        assert!(robot.x == orig_x && robot.y == orig_y);
    }
    
    cleanup_test_environment();
    println!("✓ Invalid input handling tests passed!");
}
pub fn test_process_input_basic_movement() {
    println!("Testing process_input basic movement...");
    setup_test_environment();
    
    let robot = ROBOT.lock().unwrap();
    let orig_x = robot.as_ref().unwrap().x as usize;
    let orig_y = robot.as_ref().unwrap().y as usize;
    drop(robot); // Release the lock early
    
    {
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[orig_x + 1][orig_y] = -1;
        }
    }
    
    process_input(0o405);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, (orig_x + 1) as i32);
        assert_eq!(robot.as_ref().unwrap().y, orig_y as i32);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[orig_x][orig_y] = -1;
        }
    }
    
    process_input(0o404);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x as i32);
        assert_eq!(robot.as_ref().unwrap().y, orig_y as i32);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[orig_x][orig_y - 1] = -1;
        }
    }
    
    process_input(0o403);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x as i32);
        assert_eq!(robot.as_ref().unwrap().y, (orig_y - 1) as i32);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        if let Some(screen) = screen.as_mut() {
            screen[orig_x][orig_y] = -1;
        }
    }
    
    process_input(0o402);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x as i32);
        assert_eq!(robot.as_ref().unwrap().y, orig_y as i32);
    }
    
    cleanup_test_environment();
    println!("✓ process_input basic movement tests passed!");
}
pub fn test_process_input_nethack_keys() {
    println!("Testing process_input NetHack keys...");
    setup_test_environment();
    
    {
        let robot = ROBOT.lock().unwrap();
        let orig_x = robot.as_ref().unwrap().x as usize;
        let orig_y = robot.as_ref().unwrap().y as usize;
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x + 1][orig_y] = -1;
        }
        
        process_input('l' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().x, (orig_x + 1) as i32);
        }
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x][orig_y] = -1;
        }
        
        process_input('h' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().x, orig_x as i32);
        }
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x][orig_y - 1] = -1;
        }
        
        process_input('k' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().y, (orig_y - 1) as i32);
        }
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x][orig_y] = -1;
        }
        
        process_input('j' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().y, orig_y as i32);
        }
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x + 1][orig_y - 1] = -1;
        }
        
        process_input('u' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().x, (orig_x + 1) as i32);
            assert_eq!(robot.as_ref().unwrap().y, (orig_y - 1) as i32);
        }
        
        {
            let mut screen = SCREEN.lock().unwrap();
            let screen = screen.as_mut().unwrap();
            screen[orig_x][orig_y] = -1;
        }
        
        process_input('b' as i32);
        
        {
            let robot = ROBOT.lock().unwrap();
            assert_eq!(robot.as_ref().unwrap().x, orig_x as i32);
            assert_eq!(robot.as_ref().unwrap().y, orig_y as i32);
        }
        
        cleanup_test_environment();
        println!("✓ process_input NetHack key tests passed!");
    }
}

pub fn test_boundary_checking() {
    println!("Testing boundary checking...");
    setup_test_environment();
    
    {
        let mut robot = ROBOT.lock().unwrap();
        let robot = robot.as_mut().unwrap();
        robot.x = 0;
        robot.y = 10;
        
        let mut screen = SCREEN.lock().unwrap();
        let screen = screen.as_mut().unwrap();
        screen[robot.x as usize][robot.y as usize] = 0;
    }
    
    let orig_x = {
        let robot = ROBOT.lock().unwrap();
        robot.as_ref().unwrap().x
    };
    
    process_input(0o404);
    
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x);
    }
    
    {
        let mut robot = ROBOT.lock().unwrap();
        let robot = robot.as_mut().unwrap();
        robot.x = 10;
        robot.y = 3;
        
        let mut screen = SCREEN.lock().unwrap();
        let screen = screen.as_mut().unwrap();
        screen[robot.x as usize][robot.y as usize] = 0;
    }
    
    let orig_y = {
        let robot = ROBOT.lock().unwrap();
        robot.as_ref().unwrap().y
    };
    
    process_input(0o403);
    
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().y, orig_y);
    }
    
    cleanup_test_environment();
    println!("✓ Boundary checking tests passed!");
}
pub fn test_emacs_keys() {
    println!("Testing EMACS key movement...");
    setup_test_environment();
    
    let robot = ROBOT.lock().unwrap();
    let orig_x = robot.as_ref().unwrap().x;
    let orig_y = robot.as_ref().unwrap().y;
    drop(robot); // Release the lock early
    
    {
        let mut screen = SCREEN.lock().unwrap();
        screen.as_mut().unwrap()[(orig_x + 1) as usize][orig_y as usize] = -1;
    }
    
    process_input(6);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x + 1);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        screen.as_mut().unwrap()[orig_x as usize][orig_y as usize] = -1;
    }
    
    process_input(2);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().x, orig_x);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        screen.as_mut().unwrap()[orig_x as usize][(orig_y - 1) as usize] = -1;
    }
    
    process_input(16);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().y, orig_y - 1);
    }
    
    {
        let mut screen = SCREEN.lock().unwrap();
        screen.as_mut().unwrap()[orig_x as usize][orig_y as usize] = -1;
    }
    
    process_input(14);
    {
        let robot = ROBOT.lock().unwrap();
        assert_eq!(robot.as_ref().unwrap().y, orig_y);
    }
    
    cleanup_test_environment();
    println!("✓ EMACS key movement tests passed!");
}
pub fn test_initialize_functions() {
    println!("Testing initialization functions...");
    cleanup_test_environment();
    initialize_arrays();
    
    {
        let screen = SCREEN.lock().unwrap();
        assert!(screen.is_some(), "screen should be initialized");
    }

    initialize_robot();
    
    {
        let robot = ROBOT.lock().unwrap();
        let robot = robot.as_ref().unwrap();
        assert_eq!(robot.character, '#');
        assert_eq!(robot.color, 0);
        assert!(!robot.bold);
        assert!((robot.x >= 0) && (robot.x < COLS.load(Ordering::Relaxed)));
        assert!((robot.y >= 3) && (robot.y <= 23));
        
        let screen = SCREEN.lock().unwrap();
        let screen = screen.as_ref().unwrap();
        assert_eq!(screen[robot.x as usize][robot.y as usize], 0);
    }

    initialize_kitten();
    
    {
        let kitten = KITTEN.lock().unwrap();
        assert_eq!(validchar(kitten.character), 1);
        assert!((kitten.color >= 1) && (kitten.color <= 6));
        assert!((kitten.x >= 0) && (kitten.x < COLS.load(Ordering::Relaxed)));
        assert!((kitten.y >= 3) && (kitten.y <= 23));
        
        let screen = SCREEN.lock().unwrap();
        let screen = screen.as_ref().unwrap();
        assert_eq!(screen[kitten.x as usize][kitten.y as usize], 1);
        
        let robot = ROBOT.lock().unwrap();
        let robot = robot.as_ref().unwrap();
        assert!(!(robot.x == kitten.x && robot.y == kitten.y));
    }

    cleanup_test_environment();
    println!("✓ Initialization function tests passed!");
}
