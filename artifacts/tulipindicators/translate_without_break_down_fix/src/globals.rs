use crate::*;
use lazy_static::lazy_static;
use std::sync::atomic::AtomicI32;
use std::sync::atomic::Ordering;
use std::sync::Mutex;
use std::mem::zeroed;


lazy_static! {
    pub static ref OUT: std::sync::Mutex<[[f64; 4000]; 3]> =
        std::sync::Mutex::new([[0.0; 4000]; 3]);
}


lazy_static! {
    pub static ref DATET: [&'static str; 15] = [
        "2005-11-01", "2005-11-02", "2005-11-03", "2005-11-04", "2005-11-07",
        "2005-11-08", "2005-11-09", "2005-11-10", "2005-11-11", "2005-11-14",
        "2005-11-15", "2005-11-16", "2005-11-17", "2005-11-18", "2005-11-21"
    ];
}


lazy_static! {
    pub static ref DATE: [f64; 15] = [
        51101.0, 51102.0, 51103.0, 51104.0, 51107.0, 
        51108.0, 51109.0, 51110.0, 51111.0, 51114.0, 
        51115.0, 51116.0, 51117.0, 51118.0, 51121.0
    ];
}

pub static OPEN: [f64; 15] = [
    81.85, 81.2, 81.55, 82.91, 83.1, 83.41, 82.71, 82.7, 84.2, 84.25, 84.03, 85.45, 86.18, 88.0, 87.6
];


lazy_static! {
    pub static ref HIGH: std::sync::Mutex<[f64; 15]> = std::sync::Mutex::new([
        82.15, 81.89, 83.03, 83.3, 83.85,  // 5 elements
        83.9, 83.33, 84.3, 84.84, 85.0,     // 5 elements
        85.9, 86.58, 86.98, 88.0, 87.87     // 5 elements
    ]);
}

pub static LOW: [f64; 15] = [
    81.29, 80.64, 81.31, 82.65, 83.07, // 5 elements
    83.11, 82.49, 82.3, 84.15, 84.11, // 10 elements
    84.03, 85.39, 85.76, 87.17, 87.01, // 15 elements
];

pub static CLOSE: [f64; 15] = [
    81.59, 81.06, 82.87, 83.0, 83.61, 83.15, 82.84, 83.99, 84.55, 84.36, 85.53, 86.54, 86.89, 87.77, 87.29,
];


lazy_static! {
    pub static ref VOLUME: std::sync::Mutex<[f64; 15]> = std::sync::Mutex::new([
        5653100.0, 6447400.0, 7690900.0, 3831400.0, 4455100.0, // 5 elements
        3798000.0, 3936200.0, 4732000.0, 4841300.0, 3915300.0,  // 5 elements
        6830800.0, 6694100.0, 5293600.0, 7985800.0, 4807900.0   // 5 elements
    ]);
}


lazy_static! {
    pub static ref ALTERNATIVE: [f64; 15] = [
        0.2, 0.3, 0.4, 0.3, 0.5,  // 5 elements
        0.7, 0.75, 0.9, 0.9, 1.0, // 5 elements
        1.0, 0.2, 0.1, -0.1, -0.5 // 5 elements (total 15)
    ];
}


lazy_static! {
    pub static ref OPTIONSD_SMALL: std::sync::Mutex<[f64; 17]> = std::sync::Mutex::new([
        -20.0, -2.0, -1.0, 0.0, 0.7, 1.0, 2.0, 3.0, 4.0, 5.0, 
        6.0, 7.0, 8.0, 10.0, 20.0, 100.0, 999.0
    ]);
}


lazy_static! {
    pub static ref OPTIONSD_LARGE: std::sync::Mutex<[f64; 5]> =
        std::sync::Mutex::new([-5.0, 0.0, 1.0, 2.0, 5.0]);
}


lazy_static! {
    pub static ref DUMMY_IN: std::sync::Mutex<[f64; 20]> = std::sync::Mutex::new([
        1.0, 2.0, 3.0, 4.0, 5.0,  // 5 elements
        6.0, 7.0, 8.0, 9.0, 10.0, // 10 elements
        11.0, 12.0, 13.0, 14.0, 15.0, // 15 elements
        16.0, 17.0, 18.0, 19.0, 20.0  // 20 elements
    ]);
}


lazy_static! {
    pub static ref DUMMY_IN0: std::sync::Mutex<[f64; 20]> = 
        std::sync::Mutex::new([
            0.0, 0.0, 0.0, 0.0, 0.0,  // 5 elements
            0.0, 0.0, 0.0, 0.0, 0.0,  // 10 elements
            0.0, 0.0, 0.0, 0.0, 0.0,  // 15 elements
            0.0, 0.0, 0.0, 0.0, 0.0  // 20 elements
        ]);
}


lazy_static! {
    pub static ref DUMMY_OT: std::sync::Mutex<[f64; 20]> = 
        std::sync::Mutex::new([
            1.0, 2.0, 3.0, 4.0, 5.0,  // 5 elements
            6.0, 7.0, 8.0, 9.0, 10.0, // 10 elements
            11.0, 12.0, 13.0, 14.0, 15.0, // 15 elements
            16.0, 17.0, 18.0, 19.0, 20.0  // 20 elements
        ]);
}

pub const INPUT_SIZE: usize = std::mem::size_of::<[f64; 1]>() / std::mem::size_of::<f64>();

pub const SIZES: [i32; 7] = [
    0,  // 1
    1,  // 2
    2,  // 3
    3,  // 4
    4,  // 5
    8,  // 6
    20  // 7
];

pub const SIZES_COUNT: usize = SIZES.len();


lazy_static! {
    pub static ref ERRORS_CNT: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref LTESTS: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref LFAILS: AtomicI32 = AtomicI32::new(0);
}


lazy_static! {
    pub static ref TESTED_IND: std::sync::Mutex<[i32; 104]> = 
        std::sync::Mutex::new([0; 104]);
}


lazy_static! {
    pub static ref TESTED_CND: std::sync::Mutex<[i32; 26]> = 
        std::sync::Mutex::new([0; 26]);
}


lazy_static! {
    pub static ref BESTOF: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(1);
}

pub static FAILS: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);


lazy_static! {
    pub static ref IN: std::sync::Mutex<[[f64; 4000]; 5]> =
        std::sync::Mutex::new([[0.0; 4000]; 5]);
}


lazy_static! {
    pub static ref OUTREF: std::sync::Mutex<[[f64; 4000]; 3]> =
        std::sync::Mutex::new([[0.0; 4000]; 3]);
}


lazy_static! {
    pub static ref OUTSTREAM1: std::sync::Mutex<[[f64; 4000]; 3]> =
        std::sync::Mutex::new([[0.0; 4000]; 3]);
}


lazy_static! {
    pub static ref OUTSTREAMALL: std::sync::Mutex<[[f64; 4000]; 3]> =
        std::sync::Mutex::new([[0.0; 4000]; 3]);
}

pub static IND_OFFSET: std::sync::atomic::AtomicI32 = std::sync::atomic::AtomicI32::new(0);


// Unsafe impls for thread safety
unsafe impl Send for TiIndicatorInfo {}
unsafe impl Sync for TiIndicatorInfo {}

lazy_static! {
    pub static ref TI_INDICATORS: Mutex<Vec<TiIndicatorInfo>> = {
        let mut indicators = Vec::new();
        
        // Create an empty indicator with default values
        let empty_indicator = unsafe { zeroed::<TiIndicatorInfo>() };
        
        indicators.push(empty_indicator);
        Mutex::new(indicators)
    };
}


lazy_static! {
    pub static ref TC_CANDLES: std::sync::Mutex<Vec<TcCandleInfo>> = std::sync::Mutex::new(vec![
        // Array contents would go here
        // Each element would be a TcCandleInfo struct
    ]);
}


lazy_static! {
    pub static ref OUT_CND: Mutex<Option<TcResult>> = Mutex::new(None);
}

