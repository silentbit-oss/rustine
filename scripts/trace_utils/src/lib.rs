use std::fs::OpenOptions;
use std::io::Write;
use std::sync::Mutex;
use std::time::{SystemTime, UNIX_EPOCH};
use once_cell::sync::Lazy;

static LOG_FILE: Lazy<Mutex<std::fs::File>> = Lazy::new(|| {
    Mutex::new(OpenOptions::new()
        .create(true)
        .append(true)
        .open("callchain.log")
        .expect("Failed to open log file"))
});

pub fn log_event(label: &str, addr: *const (), func: &str){
    let timestamp = SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_micros();
    let msg = format!("{timestamp},{label},{addr:p},{func}\n");
    let mut file = LOG_FILE.lock().unwrap();
    file.write_all(msg.as_bytes()).unwrap();
}

pub struct LogGuard {
    pub func: &'static str,
}

impl LogGuard {
    pub fn new(func: &'static str) -> Self {
        let addr = func as *const _ as *const ();
        log_event("ENTER", addr, func);
        LogGuard { func }
    }
}

impl Drop for LogGuard {
    fn drop(&mut self) {
        let addr = self.func as *const _ as *const ();
        log_event("EXIT", addr, self.func);
    }
}


#[macro_export]
macro_rules! LOG_TEST_START {
    ($name:expr) => {
        $crate::log_event("TEST_START", std::ptr::null(), $name);
    };
    () => {
        $crate::log_event("TEST_START", std::ptr::null(), "unknown_test");
    };
}


#[macro_export]
macro_rules! LOG_TEST_END {
    ($name:expr) => {
        $crate::log_event("TEST_END", std::ptr::null(), $name);
    };
    () => {
        $crate::log_event("TEST_END", std::ptr::null(), "unknown_test");
    };
}
