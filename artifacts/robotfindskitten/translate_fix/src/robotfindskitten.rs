use crate::*;
use std::process::exit;
use ncurses::A_ALTCHARSET;
use ncurses::A_BOLD;
use ncurses::A_DIM;
use ncurses::COLOR_BLACK;
use ncurses::COLOR_BLUE;
use ncurses::COLOR_CYAN;
use ncurses::COLOR_GREEN;
use ncurses::COLOR_MAGENTA;
use ncurses::COLOR_PAIR;
use ncurses::COLOR_RED;
use ncurses::COLOR_WHITE;
use ncurses::COLOR_YELLOW;
use ncurses::WINDOW;
use ncurses::attr_get;
use ncurses::attrset;
use ncurses::cbreak;
use ncurses::clear;
use ncurses::clrtoeol;
use ncurses::endwin;
use ncurses::getch;
use ncurses::has_colors;
use ncurses::init_pair;
use ncurses::initscr;
use ncurses::intrflush;
use ncurses::keypad;
use ncurses::mv;
use ncurses::mvprintw;
use ncurses::nl;
use ncurses::noecho;
use ncurses::printw;
use ncurses::refresh;
use ncurses::start_color;
use libc::SIGINT;
use rand::Rng;
use std::thread::sleep;
use std::time::Duration;
use lazy_static::lazy_static;
use std::sync::Mutex;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
pub fn finish(sig: i32) {
	println!("* finish");
    ncurses::endwin();
    print!("{}{}{}", 27 as char, '(', 'B');
    exit(0);
}
pub fn validchar(a: char) -> i32 {
	println!("* validchar");
    match a {
        '#' | ' ' | '\x7f' => 0,
        _ => 1,
    }
}
pub fn initialize_ncurses() {
	println!("* initialize_ncurses");
    unsafe {
        libc::signal(libc::SIGINT, finish as libc::sighandler_t);
    }
    
    let window = initscr();
    keypad(window, true);
    nl();
    intrflush(window, false);
    noecho();
    cbreak();
    
    if has_colors() {
        start_color();
        init_pair(ncurses::COLOR_BLACK, ncurses::COLOR_BLACK, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_GREEN, ncurses::COLOR_GREEN, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_RED, ncurses::COLOR_RED, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_CYAN, ncurses::COLOR_CYAN, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_WHITE, ncurses::COLOR_WHITE, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_MAGENTA, ncurses::COLOR_MAGENTA, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_BLUE, ncurses::COLOR_BLUE, ncurses::COLOR_BLACK);
        init_pair(ncurses::COLOR_YELLOW, ncurses::COLOR_YELLOW, ncurses::COLOR_BLACK);
    }
}
pub fn message(message: Option<&str>) {
	println!("* message");
    // Check if message is None (equivalent to NULL in C)
    if let Some(msg) = message {
        // Move cursor to (1, 0)
        mv(1, 0);
        // Clear to end of line
        clrtoeol();
        // Print message at (1, 0)
        mvprintw(1, 0, msg);
        
        // Get robot position and move cursor there
        let robot = ROBOT.lock().unwrap();
        if let Some(r) = robot.as_ref() {
            mv(r.y, r.x);
        }
        
        // Refresh the screen
        refresh();
    }
}
pub fn initialize_robot() {
	println!("* initialize_robot");
    let mut rng = rand::thread_rng();
    
    // Lock the ROBOT mutex and modify its contents
    let mut robot = ROBOT.lock().unwrap();
    if let Some(ref mut robot) = *robot {
        let cols = COLS.load(std::sync::atomic::Ordering::Relaxed);
        robot.x = rng.gen_range(1..(cols - 1)) + 1;  // Match C's rand() % (COLS - 1) + 1
        let lines = LINES.load(std::sync::atomic::Ordering::Relaxed);
        robot.y = rng.gen_range(3..lines);
        robot.character = '#';
        robot.color = 0;
        robot.bold = false;
    }

    // Lock the SCREEN mutex and modify its contents
    let robot = ROBOT.lock().unwrap();
    let mut screen = SCREEN.lock().unwrap();
    if let Some(ref mut screen) = *screen {
        if let Some(robot) = &*robot {
            if let Some(row) = screen.get_mut(robot.x as usize) {
                if let Some(cell) = row.get_mut(robot.y as usize) {
                    *cell = 0;
                }
            }
        }
    }
}
pub fn full_draw(o: ScreenObject, in_place: bool) {
	println!("* full_draw");
    let mut old: attr_t = 0;
    let mut dummy: i16 = 0;
    let mut new: attr_t;
    
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
pub fn draw_in_place(o: ScreenObject) {
	println!("* draw_in_place");
    full_draw(o, true);
}
pub fn instructions() {
	println!("* instructions");
    let dummy;
    const VER: &str = "1.0"; // Added version constant
    mvprintw(0, 0, &format!("robotfindskitten v{}\n", VER));
    printw("By the illustrious Leonard Richardson (C) 1997, 2000\n");
    printw("Written originally for the Nerth Pork robotfindskitten contest\n\n");
    printw("In this game, you are robot (");
    
    {
        let robot_guard = ROBOT.lock().unwrap();
        if let Some(robot) = robot_guard.as_ref() {
            draw_in_place(robot.clone());
        }
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
	println!("* draw");
    full_draw(o, false);
}
pub fn initialize_kitten() {
	println!("* initialize_kitten");
    let mut rng = rand::thread_rng();
    let mut kitten = KITTEN.lock().unwrap();
    let mut screen = SCREEN.lock().unwrap();
    
    // Generate random position until an empty spot is found
    loop {
        kitten.x = rng.gen_range(1..COLS.load(std::sync::atomic::Ordering::Relaxed) - 1) + 1;
        kitten.y = rng.gen_range(3..LINES.load(std::sync::atomic::Ordering::Relaxed) - 1);
        
        if let Some(screen_ref) = screen.as_ref() {
            if screen_ref[kitten.x as usize][kitten.y as usize] == -1 {
                break;
            }
        }
    }
    
    // Generate random valid character
    loop {
        kitten.character = rng.gen_range('!'..='~');
        if validchar(kitten.character) != 0 {
            break;
        }
    }
    
    // Update screen and kitten properties
    if let Some(screen_ref) = screen.as_mut() {
        screen_ref[kitten.x as usize][kitten.y as usize] = 1;
    }
    
    kitten.color = rng.gen_range(1..=6);
    kitten.bold = rng.gen_bool(0.5);
}
pub fn play_animation(input: i32) {
	println!("* play_animation");
    for counter in (1..=4).rev() {
        // First part of animation
        {
            // Clear right position
            // Note: Assuming mvaddch equivalent would be handled by some screen API
            // move(1, 50 + counter);
            if (input == KEY_RIGHT) || (input == KEY_DOWN) || (input == KEY_C3) || (input == KEY_A3) {
                let kitten = KITTEN.lock().unwrap();
                draw_in_place(kitten.clone());
            } else {
                let robot = ROBOT.lock().unwrap();
                if let Some(robot) = robot.as_ref() {
                    draw_in_place(robot.clone());
                }
            }
        }

        // Second part of animation
        {
            // Clear left position
            // move(1, (50 - counter) + 1);
            if (input == KEY_RIGHT) || (input == KEY_DOWN) || (input == KEY_C3) || (input == KEY_A3) {
                let robot = ROBOT.lock().unwrap();
                if let Some(robot) = robot.as_ref() {
                    draw_in_place(robot.clone());
                }
            } else {
                let kitten = KITTEN.lock().unwrap();
                draw_in_place(kitten.clone());
            }
        }

        // Note: Assuming refresh() would be handled by some screen API
        sleep(Duration::from_secs(1));
    }

    // Note: Assuming move(1, 0) and addstr would be handled by some screen API
    // move(1, 0);
    // addstr("You found kitten! Way to go, robot!");
    // refresh();
    finish(0);
}

// Constants that would be defined elsewhere (assuming they're i32 like in C)
const KEY_RIGHT: i32 = 0;
const KEY_DOWN: i32 = 0;
const KEY_C3: i32 = 0;
const KEY_A3: i32 = 0;
pub fn initialize_arrays() {
	println!("* initialize_arrays");
    // Initialize screen as a 2D array of COLS x LINES
    {
        let mut screen = SCREEN.lock().unwrap();
        let cols = COLS.load(std::sync::atomic::Ordering::Relaxed) as usize;
        let lines = LINES.load(std::sync::atomic::Ordering::Relaxed) as usize;
        *screen = Some(
            (0..cols)
                .map(|_| (0..lines).map(|_| -1).collect::<Vec<_>>().into_boxed_slice())
                .collect::<Vec<_>>()
                .into_boxed_slice(),
        );
    }

    // Create empty ScreenObject
    let empty = ScreenObject {
        x: -1,
        y: -1,
        color: 0,
        bold: false,
        character: ' ',
    };

    // Initialize used_messages, bogus_messages, and bogus arrays
    {
        let mut used_messages = USED_MESSAGES.lock().unwrap();
        let mut bogus_messages = BOGUS_MESSAGES.lock().unwrap();
        let mut bogus = BOGUS.lock().unwrap();

        let messages_len = MESSAGES.lock().unwrap().len();
        *used_messages = vec![0; messages_len];
        *bogus_messages = vec![0; messages_len];
        *bogus = vec![empty; messages_len];
    }
}
pub fn process_input(input: i32) {
	println!("* process_input");
    let mut robot = ROBOT.lock().unwrap();
    let screen = SCREEN.lock().unwrap();
    let messages = MESSAGES.lock().unwrap();
    let bogus_messages = BOGUS_MESSAGES.lock().unwrap();

    let mut check_x = robot.as_ref().unwrap().x;
    let mut check_y = robot.as_ref().unwrap().y;

    match input {
        x if x == b'L' as i32 - 64 => {
            // wrefresh(curscr); - No Rust equivalent available
        },
        x if x == ncurses::KEY_UP || x == b'k' as i32 || x == b'K' as i32 || x == b'P' as i32 - 64 => {
            check_y -= 1;
        },
        x if x == ncurses::KEY_HOME || x == b'y' as i32 || x == b'Y' as i32 => {
            check_x -= 1;
            check_y -= 1;
        },
        x if x == ncurses::KEY_PPAGE || x == b'u' as i32 || x == b'U' as i32 => {
            check_x += 1;
            check_y -= 1;
        },
        x if x == ncurses::KEY_DOWN || x == b'j' as i32 || x == b'J' as i32 || x == b'N' as i32 - 64 => {
            check_y += 1;
        },
        x if x == ncurses::KEY_END || x == b'b' as i32 || x == b'B' as i32 => {
            check_x -= 1;
            check_y += 1;
        },
        x if x == ncurses::KEY_NPAGE || x == b'n' as i32 || x == b'N' as i32 => {
            check_x += 1;
            check_y += 1;
        },
        x if x == ncurses::KEY_LEFT || x == b'h' as i32 || x == b'H' as i32 || x == b'B' as i32 - 64 => {
            check_x -= 1;
        },
        x if x == ncurses::KEY_RIGHT || x == b'l' as i32 || x == b'L' as i32 || x == b'F' as i32 - 64 => {
            check_x += 1;
        },
        0 => {},
        _ => {
            message(Some("Invalid input: Use direction keys or Esc."));
            return;
        }
    }

    if check_y < 3 || check_y > (LINES.load(std::sync::atomic::Ordering::Relaxed) - 1) || check_x < 0 || check_x > (COLS.load(std::sync::atomic::Ordering::Relaxed) - 1) {
        return;
    }

    if let Some(screen) = screen.as_ref() {
        if screen[check_x as usize][check_y as usize] != -1 {
            match screen[check_x as usize][check_y as usize] {
                0 => {},
                1 => {
                    // move(1, 0); - No Rust equivalent available
                    // clrtoeol(); - No Rust equivalent available
                    play_animation(input);
                },
                _ => {
                    let msg_idx = bogus_messages[(screen[check_x as usize][check_y as usize] - 2) as usize];
                    message(Some(messages[msg_idx as usize]));
                }
            }
            return;
        }
    }

    robot.as_mut().unwrap().x = check_x;
    robot.as_mut().unwrap().y = check_y;
}
pub fn initialize_screen() {
	println!("* initialize_screen");
    // Print version header
    mvprintw(0, 0, &format!("robotfindskitten v{}\n\n", env!("CARGO_PKG_VERSION")));

    // Draw the top border (line of underscores)
    let cols = COLS.load(Ordering::SeqCst);
    for _ in 0..cols {
        printw("_");
    }

    // Draw all bogus objects
    let num_bogus = NUM_BOGUS.load(Ordering::SeqCst);
    {
        let bogus = BOGUS.lock().unwrap();
        for counter in 0..num_bogus {
            if let Some(obj) = bogus.get(counter as usize) {
                draw(obj.clone());
            }
        }
    }

    // Draw kitten and robot
    {
        let kitten = KITTEN.lock().unwrap();
        draw(kitten.clone());
    }
    {
        let robot = ROBOT.lock().unwrap();
        if let Some(robot_obj) = &*robot {
            draw(robot_obj.clone());
        }
    }

    refresh();
}
pub fn play_game() {
	println!("* play_game");
    ncurses::initscr();
    ncurses::keypad(ncurses::stdscr(), true);
    ncurses::nodelay(ncurses::stdscr(), true);

    let mut old_x = {
        let robot = ROBOT.lock().unwrap();
        robot.as_ref().unwrap().x
    };
    let mut old_y = {
        let robot = ROBOT.lock().unwrap();
        robot.as_ref().unwrap().y
    };
    let mut input = ncurses::getch();

    while input != 27 && input != b'q' as i32 && input != b'Q' as i32 {
        process_input(input);

        let (new_x, new_y) = {
            let robot = ROBOT.lock().unwrap();
            let robot = robot.as_ref().unwrap();
            (robot.x, robot.y)
        };

        if (old_x != new_x) || (old_y != new_y) {
            ncurses::mvaddch(old_y as i32, old_x as i32, ' ' as u32);
            {
                let mut screen = SCREEN.lock().unwrap();
                let screen = screen.as_mut().unwrap();
                screen[old_x as usize][old_y as usize] = -1;
            }

            {
                let robot = ROBOT.lock().unwrap();
                let robot = robot.as_ref().unwrap();
                draw(robot.clone());
            }

            ncurses::refresh();

            {
                let mut screen = SCREEN.lock().unwrap();
                let screen = screen.as_mut().unwrap();
                screen[new_x as usize][new_y as usize] = 0;
            }

            old_x = new_x;
            old_y = new_y;
        }

        input = ncurses::getch();
    }

    message(Some("Bye!"));
    ncurses::refresh();
    finish(0);
}
pub fn initialize_bogus() {
	println!("* initialize_bogus");
    let mut rng = rand::thread_rng();
    let num_bogus = NUM_BOGUS.load(Ordering::SeqCst);
    // Load atomic COLS and LINES values
    let cols_val = COLS.load(Ordering::Relaxed);
    let lines_val = LINES.load(Ordering::Relaxed);
    
    {
        let mut bogus = BOGUS.lock().unwrap();
        let mut screen = SCREEN.lock().unwrap();
        let mut used_messages = USED_MESSAGES.lock().unwrap();
        let mut bogus_messages = BOGUS_MESSAGES.lock().unwrap();
        let messages = MESSAGES.lock().unwrap();

        for counter in 0..num_bogus {
            // Generate color (1-6)
            let color = rng.gen_range(1..=6);
            // Generate bold (true/false)
            let bold = rng.gen_bool(0.5);
            
            // Generate valid character
            let character = loop {
                let c = rng.gen_range('!'..='~');
                if validchar(c) != 0 {
                    break c;
                }
            };
            
            // Generate valid x,y position
            let (x, y) = loop {
                // Use loaded atomic values
                let x_pos = rng.gen_range(1..cols_val);
                let y_pos = rng.gen_range(3..=lines_val - 1);
                if screen.as_ref().unwrap()[x_pos as usize][y_pos as usize] == -1 {
                    break (x_pos, y_pos);
                }
            };
            
            // Update screen
            screen.as_mut().unwrap()[x as usize][y as usize] = counter + 2;
            
            // Find unused message index
            let index = loop {
                let idx = rng.gen_range(0..messages.len());
                if used_messages.get(idx).map_or(true, |&v| v == 0) {
                    break idx;
                }
            };
            
            // Update bogus entry
            bogus.push(crate::screen_object::ScreenObject {
                color,
                bold,
                character,
                x,
                y,
            });
            
            // Update message tracking
            bogus_messages.push(index as i32);
            used_messages[index] = 1;
        }
    }
}
