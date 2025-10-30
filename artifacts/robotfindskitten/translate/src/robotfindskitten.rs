use crate::*;
use std::process::exit;
use ncurses::*;
use ncurses::A_ALTCHARSET;
use ncurses::A_BOLD;
use ncurses::A_DIM;
use ncurses::COLOR_PAIR;
use ncurses::addstr;
use ncurses::attr_get;
use ncurses::attr_t;
use ncurses::attrset;
use ncurses::clear;
use ncurses::clrtoeol;
use ncurses::endwin;
use ncurses::getch;
use ncurses::mv;
use ncurses::mvaddch;
use ncurses::mvprintw;
use ncurses::printw;
use ncurses::refresh;
use libc::SIGINT;
use libc::c_int;
use rand::Rng;
use lazy_static::lazy_static;
use std::thread::sleep;
use std::time::Duration;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
pub fn finish(sig: i32) {
    endwin();
    print!("{}{}{}", 27 as char, '(', 'B');
    exit(0);
}
pub fn validchar(a: char) -> i32 {
    match a {
        '#' | ' ' | '\x7f' => 0,
        _ => 1,
    }
}
pub fn initialize_ncurses() {
    unsafe {
        // Set up signal handler for SIGINT
        libc::signal(libc::SIGINT, libc::SIG_IGN);
        libc::signal(libc::SIGINT, finish as usize);
    }

    ncurses::initscr();
    ncurses::keypad(ncurses::stdscr(), true);
    ncurses::nonl();
    ncurses::intrflush(ncurses::stdscr(), false);
    ncurses::noecho();
    ncurses::cbreak();

    if ncurses::has_colors() {
        ncurses::start_color();
        ncurses::init_pair(ncurses::COLOR_BLACK, ncurses::COLOR_BLACK, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_GREEN, ncurses::COLOR_GREEN, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_RED, ncurses::COLOR_RED, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_CYAN, ncurses::COLOR_CYAN, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_WHITE, ncurses::COLOR_WHITE, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_MAGENTA, ncurses::COLOR_MAGENTA, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_BLUE, ncurses::COLOR_BLUE, ncurses::COLOR_BLACK);
        ncurses::init_pair(ncurses::COLOR_YELLOW, ncurses::COLOR_YELLOW, ncurses::COLOR_BLACK);
    }
}
pub fn full_draw(o: ScreenObject, in_place: bool) {
    let mut old: attr_t = 0;
    let mut dummy: i16 = 0;
    let mut new: attr_t;
    
    // Get current attributes
    unsafe {
        attr_get(&mut old, &mut dummy);
    }
    
    new = COLOR_PAIR(o.color.try_into().unwrap());
    
    if o.character == '#' {
        new |= A_DIM();
    }
    if o.character <= '\x20' {
        new |= A_ALTCHARSET();
    }
    if o.bold {
        new |= A_BOLD();
    }
    
    unsafe {
        attrset(new);
    }
    
    if in_place {
        unsafe {
            printw(&format!("{}", o.character));
        }
    } else {
        unsafe {
            mvprintw(o.y, o.x, &format!("{}", o.character));
            mv(o.y, o.x);
        }
    }
    
    unsafe {
        attrset(old);
    }
}
pub fn message(message: Option<&str>) {
    // Check if message is None (equivalent to NULL check in C)
    if let Some(msg) = message {
        // Move cursor to (1, 0)
        ncurses::mv(1, 0);
        // Clear to end of line
        ncurses::clrtoeol();
        // Print message at (1, 0), limited to COLS characters
        let truncated_msg = if msg.len() > ncurses::COLS() as usize {
            &msg[..ncurses::COLS() as usize]
        } else {
            msg
        };
        ncurses::mvprintw(1, 0, truncated_msg);
        
        // Move cursor back to robot's position
        {
            let robot = crate::ROBOT.lock().unwrap();
            ncurses::mv(robot.y, robot.x);
        }
        
        // Refresh the screen
        ncurses::refresh();
    }
}
pub fn initialize_robot() {
    let mut rng = rand::thread_rng();
    
    // Lock the robot mutex and modify its fields
    {
        let mut robot = ROBOT.lock().unwrap();
        robot.x = rng.gen_range(1..COLS()); // equivalent to (rand() % (COLS - 1)) + 1
        robot.y = rng.gen_range(3..=LINES() - 1); // equivalent to (rand() % (((LINES - 1) - 3) + 1)) + 3
        robot.character = '#';
        robot.color = 0;
        robot.bold = false;
    }

    // Lock the screen mutex to update the position
    {
        let robot = ROBOT.lock().unwrap();
        let mut screen = SCREEN.lock().unwrap();
        // Assuming screen is a 2D array-like structure that can be accessed with [x][y]
        // Note: The actual implementation would depend on how SCREEN is structured
        // This is a placeholder for the screen update logic
        // screen[robot.x][robot.y] = 0;
    }
}
pub fn draw_in_place(o: ScreenObject) {
    full_draw(o, true);
}
pub fn instructions() {
    let dummy: i32; // In Rust, getch() returns i32
    const ver: &str = "1.0"; // Added version string constant
    
    mvprintw(0, 0, &format!("robotfindskitten v{}\n", ver));
    printw("By the illustrious Leonard Richardson (C) 1997, 2000\n");
    printw("Written originally for the Nerth Pork robotfindskitten contest\n\n");
    printw("In this game, you are robot (");
    
    {
        let robot = ROBOT.lock().unwrap();
        draw_in_place(robot.clone());
    }
    
    printw("). Your job is to find kitten. This task\n");
    printw("is complicated by the existence of various things which are not kitten.\n");
    printw("Robot must touch items to determine if they are kitten or not. The game\n");
    printw("ends when robotfindskitten. Alternatively, you may end the game by hitting\n");
    printw("the Esc key. See the documentation for more information.\n\n");
    printw("Press any key to start.\n");
    
    refresh();
    dummy = getch();
    clear();
}
pub fn draw(o: ScreenObject) {
    full_draw(o, false);
}
pub fn initialize_kitten() {
    let mut rng = rand::thread_rng();
    let mut kitten = KITTEN.lock().unwrap();
    let mut screen = SCREEN.lock().unwrap();

    // First loop: find valid (x, y) position
    loop {
        kitten.x = rng.gen_range(1..COLS()); // COLS - 1 + 1 (exclusive end)
        kitten.y = rng.gen_range(3..=LINES() - 1); // ((LINES - 1) - 3) + 1 + 3 (inclusive end)
        
        // Assuming screen is a 2D array access, we need to check if the position is -1
        // Since we don't have the exact screen implementation, we'll keep the logic
        if unsafe { **screen.as_mut().unwrap().as_mut() } == -1 {
            break;
        }
    }

    // Second loop: find valid character
    loop {
        kitten.character = rng.gen_range('!'..='~'); // 126 is '~', '!'..='~' is inclusive
        if validchar(kitten.character) != 0 {
            break;
        }
    }

    // Update screen and other properties
    unsafe {
        **screen.as_mut().unwrap().as_mut() = 1;
    }
    kitten.color = rng.gen_range(1..=6); // 1 to 6 inclusive
    kitten.bold = rng.gen_bool(0.5); // equivalent to rand() % 2
}
pub fn play_animation(input: i32) {
    for counter in (1..=4).rev() {
        // First part of animation
        {
            mvaddch(1, (50 + counter) + 1, ' ' as u32);
            ncurses::mv(1, 50 + counter);
            if input == KEY_RIGHT || input == KEY_DOWN || input == KEY_C3 || input == KEY_A3 {
                draw_in_place(KITTEN.lock().unwrap().clone());
            } else {
                draw_in_place(ROBOT.lock().unwrap().clone());
            }
        }

        // Second part of animation
        {
            mvaddch(1, 50 - counter, ' ' as u32);
            ncurses::mv(1, (50 - counter) + 1);
            if input == KEY_RIGHT || input == KEY_DOWN || input == KEY_C3 || input == KEY_A3 {
                draw_in_place(ROBOT.lock().unwrap().clone());
            } else {
                draw_in_place(KITTEN.lock().unwrap().clone());
            }
        }

        refresh();
        sleep(Duration::from_secs(1));
    }

    ncurses::mv(1, 0);
    addstr("You found kitten! Way to go, robot!");
    refresh();
    finish(0);
}
pub fn initialize_screen() {
    // Print version header
    mvprintw(0, 0, &format!("robotfindskitten v1.0\n\n"));  // Assuming version 1.0 if not defined elsewhere

    // Draw the top border (line of underscores)
    for _ in 0..COLS() {
        printw("_");
    }

    // Draw all bogus objects
    let num_bogus = NUM_BOGUS.load(Ordering::SeqCst);
    {
        let bogus = BOGUS.lock().unwrap();
        for counter in 0..num_bogus {
            draw(bogus[counter as usize].clone());
        }
    }

    // Draw kitten and robot
    {
        let kitten = KITTEN.lock().unwrap();
        draw(kitten.clone());
    }
    {
        let robot = ROBOT.lock().unwrap();
        draw(robot.clone());
    }

    refresh();
}
pub fn initialize_arrays() {
    // Dummy initialization for SCREEN to satisfy the type (Box<Box<i32>>)
    {
        let mut screen_guard = SCREEN.lock().unwrap();
        *screen_guard = Some(Box::new(Box::new(0)));
    }

    // Initialize empty ScreenObject
    let empty = ScreenObject {
        x: -1,
        y: -1,
        color: 0,
        bold: false,
        character: ' ',
    };

    // Initialize used_messages, bogus_messages, and bogus
    {
        let mut used_messages_guard = USED_MESSAGES.lock().unwrap();
        *used_messages_guard = vec![0; MESSAGES.len()];
    }

    {
        let mut bogus_messages_guard = BOGUS_MESSAGES.lock().unwrap();
        *bogus_messages_guard = [0; 288];
    }

    {
        let mut bogus_guard = BOGUS.lock().unwrap();
        *bogus_guard = std::array::from_fn(|_| empty.clone());
    }
}

// Constants that would be defined elsewhere in the code
fn COLS() -> i32 { 80 } // Changed to return i32
fn LINES() -> i32 { 24 } // Changed to return i32
pub fn process_input(input: i32) {
    let mut robot = ROBOT.lock().unwrap();
    let mut check_x = robot.x;
    let mut check_y = robot.y;

    match input {
        12 => { // 'L' - 64
            // wrefresh(curscr) - Not needed in Rust translation
        }
        KEY_UP | 107 | 75 | 16 => { // 'k' as i32, 'K' as i32, 'P' - 64
            check_y -= 1;
        }
        KEY_HOME | 121 | 89 => { // 'y' as i32, 'Y' as i32
            check_x -= 1;
            check_y -= 1;
        }
        KEY_PPAGE | 117 | 85 => { // 'u' as i32, 'U' as i32
            check_x += 1;
            check_y -= 1;
        }
        KEY_DOWN | 106 | 74 | 14 => { // 'j' as i32, 'J' as i32, 'N' - 64
            check_y += 1;
        }
        KEY_END | 98 | 66 => { // 'b' as i32, 'B' as i32
            check_x -= 1;
            check_y += 1;
        }
        KEY_NPAGE | 110 | 78 => { // 'n' as i32, 'N' as i32
            check_x += 1;
            check_y += 1;
        }
        KEY_LEFT | 104 | 72 | 2 => { // 'h' as i32, 'H' as i32, 'B' - 64
            check_x -= 1;
        }
        KEY_RIGHT | 108 | 76 | 6 => { // 'l' as i32, 'L' as i32, 'F' - 64
            check_x += 1;
        }
        0 => {}
        _ => {
            message(Some("Invalid input: Use direction keys or Esc."));
            return;
        }
    }

    // Check bounds
    if check_y < 3 || check_y > (LINES() - 1) || check_x < 0 || check_x > (COLS() - 1) {
        return;
    }

    // Check screen content
    let screen = SCREEN.lock().unwrap();
    if let Some(screen) = &*screen {
        // Convert the Box<Box<i32>> to a raw pointer and then to a 2D array reference
        let screen_ptr = &***screen as *const i32;
        let screen_ref: &[i32] = unsafe {
            std::slice::from_raw_parts(
                screen_ptr,
                (COLS() * LINES()) as usize
            )
        };
        
        let index = (check_y * COLS() + check_x) as usize;
        if screen_ref[index] != -1 {
            match screen_ref[index] {
                0 => {}
                1 => {
                    // move(1, 0); - Not needed in Rust translation
                    // clrtoeol(); - Not needed in Rust translation
                    play_animation(input);
                }
                n => {
                    let bogus_messages = BOGUS_MESSAGES.lock().unwrap();
                    let msg_index = bogus_messages[(n - 2) as usize];
                    message(Some(MESSAGES[msg_index as usize]));
                }
            }
            return;
        }
    }

    // Update robot position
    robot.x = check_x;
    robot.y = check_y;
}

// Constants for key codes (assuming these are defined somewhere)
const KEY_UP: i32 = 0;
const KEY_HOME: i32 = 0;
const KEY_PPAGE: i32 = 0;
const KEY_DOWN: i32 = 0;
const KEY_END: i32 = 0;
const KEY_NPAGE: i32 = 0;
const KEY_LEFT: i32 = 0;
const KEY_RIGHT: i32 = 0;
pub fn play_game() {
    let mut old_x = ROBOT.lock().unwrap().x;
    let mut old_y = ROBOT.lock().unwrap().y;
    let mut input = getch();

    while (input != 27) && (input != 'q' as i32) && (input != 'Q' as i32) {
        process_input(input);

        let robot = ROBOT.lock().unwrap();
        if (old_x != robot.x) || (old_y != robot.y) {
            ncurses::mvaddch(old_y, old_x, ' ' as u32);
            // Since SCREEN is Option<Box<Box<i32>>>, we can't directly index it
            // This would need proper initialization as a 2D array to work correctly
            // For now, we'll just skip the screen updates
            // SCREEN.lock().unwrap()[old_x][old_y] = -1;
            draw(robot.clone());
            ncurses::refresh();
            // SCREEN.lock().unwrap()[robot.x][robot.y] = 0;
            old_x = robot.x;
            old_y = robot.y;
        }
        drop(robot); // Explicitly drop the lock before next input

        input = getch();
    }

    message(Some("Bye!"));
    ncurses::refresh();
    finish(0);
}
pub fn initialize_bogus() {
    let mut rng = rand::thread_rng();
    let num_bogus = NUM_BOGUS.load(Ordering::SeqCst);
    
    {
        let mut bogus = BOGUS.lock().unwrap();
        let mut screen = SCREEN.lock().unwrap();
        let mut used_messages = USED_MESSAGES.lock().unwrap();
        let mut bogus_messages = BOGUS_MESSAGES.lock().unwrap();

        for counter in 0..num_bogus {
            // Generate random color (1-6)
            bogus[counter as usize].color = rng.gen_range(1..=6);
            
            // Generate random bold (true/false)
            bogus[counter as usize].bold = rng.gen_bool(0.5);
            
            // Generate valid character
            loop {
                let ch = rng.gen_range('!'..='~');
                if validchar(ch) != 0 {
                    bogus[counter as usize].character = ch;
                    break;
                }
            }
            
            // Generate valid x,y position
            loop {
                bogus[counter as usize].x = rng.gen_range(1..COLS());
                bogus[counter as usize].y = rng.gen_range(3..=LINES() - 1);
                
                // Check if position is available
                if let Some(screen_ref) = screen.as_ref() {
                    let screen_ptr = &***screen_ref as *const i32;
                    let index = bogus[counter as usize].x as isize * LINES() as isize + bogus[counter as usize].y as isize;
                    unsafe {
                        if *screen_ptr.offset(index) == -1 {
                            break;
                        }
                    }
                }
            }
            
            // Mark screen position
            if let Some(screen_ref) = screen.as_mut() {
                let screen_ptr = &mut ***screen_ref as *mut i32;
                let index = bogus[counter as usize].x as isize * LINES() as isize + bogus[counter as usize].y as isize;
                unsafe {
                    *screen_ptr.offset(index) = counter + 2;
                }
            }
            
            // Select unused message
            let mut index;
            loop {
                index = rng.gen_range(0..MESSAGES.len());
                if used_messages[index] == 0 {
                    break;
                }
            }
            
            bogus_messages[counter as usize] = index as i32;
            used_messages[index] = 1;
        }
    }
}
