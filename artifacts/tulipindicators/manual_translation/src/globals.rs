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
        //let empty_indicator = unsafe { zeroed::<TiIndicatorInfo>() };
        
        indicators.push(TiIndicatorInfo{
            name: Some("abs".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_abs_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_abs,
            indicator_ref: ti_abs,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("dpo".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_dpo_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_dpo,
            indicator_ref: ti_dpo,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("dm".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_dm_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_dm,
            indicator_ref: ti_dm,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("div".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_div_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_div,
            indicator_ref: ti_div,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("di".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_di_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_di,
            indicator_ref: ti_di,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("fisher".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_fisher_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_fisher,
            indicator_ref: ti_fisher,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("exp".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_exp_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_exp,
            indicator_ref: ti_exp,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("emv".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_emv_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_emv,
            indicator_ref: ti_emv,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("ema".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ema_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ema,
            indicator_ref: ti_ema,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("dema".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_dema_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_dema,
            indicator_ref: ti_dema,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("decay".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_decay_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_decay,
            indicator_ref: ti_decay,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("cvi".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_cvi_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_cvi,
            indicator_ref: ti_cvi,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("crossover".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_crossover_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_crossover,
            indicator_ref: ti_crossover,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("crossany".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_crossany_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_crossany,
            indicator_ref: ti_crossany,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("cosh".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_cosh_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_cosh,
            indicator_ref: ti_cosh,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("cos".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_cos_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_cos,
            indicator_ref: ti_cos,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("acos".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_acos_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_acos,
            indicator_ref: ti_acos,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("ad".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ad_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ad,
            indicator_ref: ti_ad,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("floor".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_floor_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_floor,
            indicator_ref: ti_floor,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("kama".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_kama_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_kama,
            indicator_ref: ti_kama,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("hma".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_hma_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_hma,
            indicator_ref: ti_hma,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("fosc".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_fosc_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_fosc,
            indicator_ref: ti_fosc,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("add".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_add_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_add,
            indicator_ref: ti_add,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("adosc".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_adosc_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_adosc,
            indicator_ref: ti_adosc,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("dx".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_dx_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_dx,
            indicator_ref: ti_dx,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("adx".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_adx_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_adx,
            indicator_ref: ti_adx,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("adxr".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_adxr_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_adxr,
            indicator_ref: ti_adxr,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("ao".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ao_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ao,
            indicator_ref: ti_ao,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("aroonosc".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_aroonosc_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_aroonosc,
            indicator_ref: ti_aroonosc,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("atan".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_atan_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_atan,
            indicator_ref: ti_atan,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("apo".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_apo_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_apo,
            indicator_ref: ti_apo,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("asin".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_asin_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_asin,
            indicator_ref: ti_asin,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("aroon".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_aroon_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_aroon,
            indicator_ref: ti_aroon,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("cmo".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_cmo_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_cmo,
            indicator_ref: ti_cmo,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("ceil".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ceil_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ceil,
            indicator_ref: ti_ceil,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("cci".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_cci_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_cci,
            indicator_ref: ti_cci,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("bop".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_bop_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_bop,
            indicator_ref: ti_bop,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("bbands".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_bbands_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_bbands,
            indicator_ref: ti_bbands,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("avgprice".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_avgprice_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_avgprice,
            indicator_ref: ti_avgprice,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("atr".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_atr_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_atr,
            indicator_ref: ti_atr,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("ceil".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ceil_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ceil,
            indicator_ref: ti_ceil,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("fosc".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_fosc_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_fosc,
            indicator_ref: ti_ceil,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("mom".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_mom_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_mom,
            indicator_ref: ti_mom,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("min".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_min_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_min,
            indicator_ref: ti_min,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("mfi".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_mfi_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_mfi,
            indicator_ref: ti_mfi,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("md".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_md_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_md,
            indicator_ref: ti_md,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("max".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_max_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_max,
            indicator_ref: ti_max,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("mass".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_mass_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_mass,
            indicator_ref: ti_mass,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("macd".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_macd_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_macd,
            indicator_ref: ti_macd,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("log10".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_log10_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_log10,
            indicator_ref: ti_log10,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("ln".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ln_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ln,
            indicator_ref: ti_ln,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("mul".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_mul_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_mul,
            indicator_ref: ti_mul,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("nvi".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_nvi_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_nvi,
            indicator_ref: ti_nvi,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("obv".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_obv_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_obv,
            indicator_ref: ti_obv,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("natr".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_natr_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_natr,
            indicator_ref: ti_natr,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("msw".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_msw_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_msw,
            indicator_ref: ti_msw,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });

        indicators.push(TiIndicatorInfo{
            name: Some("ppo".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_ppo_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_ppo,
            indicator_ref: ti_ppo,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("psar".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_psar_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_psar,
            indicator_ref: ti_psar,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("rsi".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_rsi_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_rsi,
            indicator_ref: ti_rsi,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("tsf".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_tsf_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_tsf,
            indicator_ref: ti_tsf,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("vhf".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_vhf_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_vhf,
            indicator_ref: ti_vhf,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("vwma".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_vwma_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_vwma,
            indicator_ref: ti_vwma,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("kvo".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_kvo_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_kvo,
            indicator_ref: ti_kvo,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("lag".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_lag_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_lag,
            indicator_ref: ti_lag,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
        indicators.push(TiIndicatorInfo{
            name: Some("linreg".to_string()),
            full_name: Some("Vector Absolute Value".to_string()),
            start: Some(Box::new(|slice: &[f64]| { ti_linreg_start(Some(slice))}) as Box<dyn Fn(&[f64]) -> i32>),
            indicator: ti_linreg,
            indicator_ref: ti_linreg,
            type_: 4,
            inputs: 1,
            options: 0,
            outputs: 1,
            input_names: [Some("real".to_string())],
            option_names: [None],
            output_names: [Some("abs".to_string())],
            stream_new: ti_abs_stream_new,
            stream_run: None,
            stream_free: None,
        });
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

