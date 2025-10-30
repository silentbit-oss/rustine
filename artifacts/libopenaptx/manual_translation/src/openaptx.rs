use crate::*;
use std::alloc::Layout;
use std::alloc::alloc;
use rand::Rng;
use std::cmp::Ordering;
use lazy_static::lazy_static;
use std::slice;

pub fn clip_intp2(a: i32, p: u32) -> i32 {
    if p == 0 {
        return 0;
    }
    if ((a as u32).wrapping_add(1u32 << p)) & !((2u32 << p).wrapping_sub(1)) != 0 {
        let mask = (1u32 << p) - 1;
        (a >> 31) ^ mask as i32
    } else {
        a
    }
}
pub fn clip(a: i32, amin: i32, amax: i32) -> i32 {
	println!("* clip");
    if a < amin {
        amin
    } else if a > amax {
        amax
    } else {
        a
    }
}
pub fn sign_extend(val: i32, bits: u32) -> i32 {
	println!("* sign_extend");
    let shift = (8 * (std::mem::size_of::<i32>() as u32)) - bits;
    let v = ((val as u32) << shift) as i32;
    v >> shift
}
pub fn rshift32(value: i32, shift: u32) -> i32 {
	println!("* rshift32");
    let rounding = (1 as i32) << (shift - 1);
    let mask = ((1 as i32) << (shift + 1)) - 1;
    ((value + rounding) >> shift) - ((value & mask) == rounding) as i32
}
pub fn rshift64(value: i64, shift: u32) -> i64 {
	println!("* rshift64");
    let rounding = 1i64 << (shift - 1);
    let mask = (1i64 << (shift + 1)) - 1;
    ((value + rounding) >> shift) - i64::from((value & mask) == rounding)
}
pub fn aptx_bin_search(value: i32, factor: i32, intervals: &[i32], nb_intervals: i32) -> i32 {
	println!("* aptx_bin_search");
    let mut idx = 0;
    let mut i = nb_intervals >> 1;
    
    while i > 0 {
        if ((factor as i64) * (intervals[(idx + i) as usize] as i64)) <= ((value as i64) << 24) {
            idx += i;
        }
        i >>= 1;
    }
    
    idx
}
pub fn aptx_finish(ctx: Option<Box<AptxContext>>) {
	println!("* aptx_finish");
    // In Rust, Box will automatically free the memory when it goes out of scope
    // The Option wrapper allows for NULL pointer checking like in C
    // No explicit free needed - Rust's ownership system handles it
}
pub fn aptx_update_codeword_history(channel: &mut AptxChannel) {
	println!("* aptx_update_codeword_history");
    let cw = ((channel.quantize[0].quantized_sample & 3) << 0)
           + ((channel.quantize[1].quantized_sample & 2) << 1)
           + ((channel.quantize[2].quantized_sample & 1) << 3);
    
    channel.codeword_history = (cw << 8) + ((channel.codeword_history as u32) << 4) as i32;
}
pub fn aptx_qmf_filter_signal_push(signal: &mut AptxFilterSignal, sample: i32) {
	println!("* aptx_qmf_filter_signal_push");
    signal.buffer[signal.pos as usize] = sample;
    signal.buffer[(signal.pos as usize) + 16] = sample;
    signal.pos = (signal.pos + 1) & (16 - 1);
}
pub fn aptx_reconstructed_differences_update(
    prediction: &mut AptxPrediction,
    reconstructed_difference: i32,
    order: i32,
) -> i32 {
    let p = prediction.pos;
    let rd1 = &mut prediction.reconstructed_differences;
    let rd2_start = order as usize;
    
    rd1[p as usize] = rd1[rd2_start + p as usize];
    
    let new_p = (p + 1) % order;
    prediction.pos = new_p;
    
    rd1[rd2_start + new_p as usize] = reconstructed_difference;
    
    new_p
}
pub fn aptx_quantized_parity(channel: &AptxChannel) -> i32 {
	println!("* aptx_quantized_parity");
    let mut parity = channel.dither_parity;
    for subband in 0..4 {
        parity ^= channel.quantize[subband].quantized_sample;
    }
    parity & 1
}
pub fn aptx_reset(ctx: &mut AptxContext) {
	println!("* aptx_reset");
    // Save the hd value before zeroing the struct
    let hd = ctx.hd;
    
    // Zero out the entire struct using memset (unsafe)
    unsafe {
        let size = std::mem::size_of_val(ctx);
        let ptr = ctx as *mut AptxContext as *mut u8;
        std::ptr::write_bytes(ptr, 0, size);
    }

    // Restore the hd value and set other fields
    ctx.hd = hd;
    ctx.decode_skip_leading = (90 + 3) / 4;
    ctx.encode_remaining = (90 + 3) / 4;

    // Iterate through channels and subbands to set prediction values
    for chan in 0..2 { // NB_CHANNELS is 2
        let channel = &mut ctx.channels[chan];
        for subband in 0..4 {
            let prediction = &mut channel.prediction[subband];
            prediction.prev_sign[0] = 1;
            prediction.prev_sign[1] = 1;
        }
    }
}
pub fn aptx_init(hd: bool) -> Option<Box<AptxContext>> {
	println!("* aptx_init");
    // Allocate memory for AptxContext using Box (handles memory management automatically)
    let mut ctx = Box::new(AptxContext {
        decode_sync_packets: 0,
        decode_dropped: 0,
        channels: [
            AptxChannel {
                codeword_history: 0,
                dither: [0; 4],
                dither_parity: 0,
                qmf: aptx__q_m_f_analysis::AptxQmfAnalysis {
                    inner_filter_signal: core::array::from_fn(|_| core::array::from_fn(|_| AptxFilterSignal { buffer: [0; 32], pos: 0 })),
                    outer_filter_signal: core::array::from_fn(|_| AptxFilterSignal { buffer: [0; 32], pos: 0 }),
                },
                quantize: core::array::from_fn(|_| aptx_quantize::AptxQuantize {
                    error: 0,
                    quantized_sample: 0,
                    quantized_sample_parity_change: 0,
                }),
                invert_quantize: core::array::from_fn(|_| aptx_invert_quantize::AptxInvertQuantize {
                    factor_select: 0,
                    quantization_factor: 0,
                    reconstructed_difference: 0,
                }),
                prediction: core::array::from_fn(|_| aptx_prediction::AptxPrediction {
                    prev_sign: [0; 2],
                    reconstructed_differences: [0; 48],
                    previous_reconstructed_sample: 0,
                    predicted_sample: 0,
                    d_weight: [0; 24],
                    pos: 0,
                    predicted_difference: 0,
                    s_weight: [0; 2],
                }),
            },
            AptxChannel {
                codeword_history: 0,
                dither: [0; 4],
                dither_parity: 0,
                qmf: aptx__q_m_f_analysis::AptxQmfAnalysis {
                    inner_filter_signal: core::array::from_fn(|_| core::array::from_fn(|_| AptxFilterSignal { buffer: [0; 32], pos: 0 })),
                    outer_filter_signal: core::array::from_fn(|_| AptxFilterSignal { buffer: [0; 32], pos: 0 }),
                },
                quantize: core::array::from_fn(|_| aptx_quantize::AptxQuantize {
                    error: 0,
                    quantized_sample: 0,
                    quantized_sample_parity_change: 0,
                }),
                invert_quantize: core::array::from_fn(|_| aptx_invert_quantize::AptxInvertQuantize {
                    factor_select: 0,
                    quantization_factor: 0,
                    reconstructed_difference: 0,
                }),
                prediction: core::array::from_fn(|_| aptx_prediction::AptxPrediction {
                    prev_sign: [0; 2],
                    reconstructed_differences: [0; 48],
                    previous_reconstructed_sample: 0,
                    predicted_sample: 0,
                    d_weight: [0; 24],
                    pos: 0,
                    predicted_difference: 0,
                    s_weight: [0; 2],
                }),
            }
        ],
        hd: if hd { 1 } else { 0 },
        sync_idx: 0,
        encode_remaining: 0,
        decode_skip_leading: 0,
        decode_sync_buffer_len: 0,
        decode_sync_buffer: [0; 6],
    });
    
    // Call aptx_reset to initialize the context
    aptx_reset(&mut ctx);
    
    Some(ctx)
}
pub fn aptxhd_pack_codeword(channel: &AptxChannel) -> u32 {
	println!("* aptxhd_pack_codeword");
    let parity = aptx_quantized_parity(channel);
    ((((((channel.quantize[3].quantized_sample & 0x01E) | parity) << 19) 
        | ((channel.quantize[2].quantized_sample & 0x00F) << 15)) 
        | ((channel.quantize[1].quantized_sample & 0x03F) << 9)) 
        | ((channel.quantize[0].quantized_sample & 0x1FF) << 0)) as u32
}
pub fn aptx_pack_codeword(channel: &AptxChannel) -> u16 {
	println!("* aptx_pack_codeword");
    let parity = aptx_quantized_parity(channel);
    ((((((channel.quantize[3].quantized_sample & 0x06) | parity) << 13) 
        | ((channel.quantize[2].quantized_sample & 0x03) << 11)) 
        | ((channel.quantize[1].quantized_sample & 0x0F) << 7)) 
        | ((channel.quantize[0].quantized_sample & 0x7F) << 0)) as u16
}
pub fn aptx_prediction_filtering(
    prediction: &mut AptxPrediction,
    reconstructed_difference: i32,
    order: i32,
) {
    let reconstructed_sample = clip_intp2(
        reconstructed_difference.wrapping_add(prediction.predicted_sample),
        23,
    );

    let predictor = clip_intp2(
        ((((prediction.s_weight[0] as i64) * (prediction.previous_reconstructed_sample as i64))
            .wrapping_add(
                ((prediction.s_weight[1] as i64) * (reconstructed_sample as i64)),
            )
            >> 22) as i32),
        23,
    );

    prediction.previous_reconstructed_sample = reconstructed_sample;

    let reconstructed_differences_idx = aptx_reconstructed_differences_update(
        prediction,
        reconstructed_difference,
        order,
    );

    let srd0 = ((reconstructed_difference > 0) as i32 - (reconstructed_difference < 0) as i32)
        .wrapping_mul(1 << 23);

    let mut predicted_difference: i64 = 0;
    for i in 0..order {
        let rel_index1 = (reconstructed_differences_idx - i - 1).rem_euclid(order);
        let abs_index1 = (order as usize) + rel_index1 as usize;
        let srd = (prediction.reconstructed_differences[abs_index1] >> 31) | 1;
        let d_weight = prediction.d_weight[i as usize];
        prediction.d_weight[i as usize] = rshift32(
            d_weight.wrapping_sub(srd.wrapping_mul(srd0)),
            8,
        );
        let rel_index2 = (reconstructed_differences_idx - i).rem_euclid(order);
        let abs_index2 = (order as usize) + rel_index2 as usize;
        predicted_difference = predicted_difference.wrapping_add(
            (prediction.reconstructed_differences[abs_index2] as i64)
                .wrapping_mul(prediction.d_weight[i as usize] as i64),
        );
    }

    prediction.predicted_difference = clip_intp2((predicted_difference >> 22) as i32, 23);
    prediction.predicted_sample = clip_intp2(
        predictor.wrapping_add(prediction.predicted_difference),
        23,
    );
}
pub fn rshift64_clip24(value: i64, shift: u32) -> i32 {
	println!("* rshift64_clip24");
    clip_intp2(rshift64(value, shift) as i32, 23)
}
pub fn aptx_invert_quantization(
    invert_quantize: &mut AptxInvertQuantize,
    quantized_sample: i32,
    dither: i32,
    tables: &AptxTables,
) {
	println!("* aptx_invert_quantization");
    let idx = (quantized_sample ^ (-((quantized_sample < 0) as i32))) + 1;
    let mut qr = tables.quantize_intervals.as_ref().unwrap()[idx as usize] / 2;
    if quantized_sample < 0 {
        qr = -qr;
    }
    
    let dither_factor = tables.invert_quantize_dither_factors.as_ref().unwrap()[idx as usize];
    qr = rshift64_clip24(
        ((qr as i64) << 32) + ((dither as i64) * dither_factor as i64),
        32,
    );
    
    invert_quantize.reconstructed_difference = 
        ((invert_quantize.quantization_factor as i64 * qr as i64) >> 19) as i32;
    
    let mut factor_select = 32620 * invert_quantize.factor_select;
    let offset = tables.quantize_factor_select_offset.as_ref().unwrap()[idx as usize] as i32;
    factor_select = rshift32(factor_select + (offset << 15), 15);
    invert_quantize.factor_select = clip(factor_select, 0, tables.factor_max);
    
    let idx = (invert_quantize.factor_select & 0xFF) >> 3;
    let shift = (tables.factor_max - invert_quantize.factor_select) >> 8;
    invert_quantize.quantization_factor = 
        ((QUANTIZATION_FACTORS[idx as usize] as i32) << 11) >> shift;
}
pub fn aptx_process_subband(
    invert_quantize: &mut AptxInvertQuantize,
    prediction: &mut AptxPrediction,
    quantized_sample: i32,
    dither: i32,
    tables: &AptxTables,
) {
	println!("* aptx_process_subband");
    aptx_invert_quantization(invert_quantize, quantized_sample, dither, tables);
    
    let sign = (invert_quantize.reconstructed_difference > (-prediction.predicted_difference)) as i32 
        - (invert_quantize.reconstructed_difference < (-prediction.predicted_difference)) as i32;
    
    let same_sign = [
        sign * prediction.prev_sign[0],
        sign * prediction.prev_sign[1],
    ];
    
    prediction.prev_sign[0] = prediction.prev_sign[1];
    prediction.prev_sign[1] = sign | 1;
    
    let mut range = 0x100000;
    let mut sw1 = rshift32((-same_sign[1]) * prediction.s_weight[1], 1);
    sw1 = (clip(sw1, -range, range) & (!0xF)) * 16;
    
    range = 0x300000;
    let weight = [
        ((254 * prediction.s_weight[0]) + (0x800000 * same_sign[0])) + sw1,
        (255 * prediction.s_weight[1]) + (0xC00000 * same_sign[1]),
    ];
    
    prediction.s_weight[0] = clip(rshift32(weight[0], 8), -range, range);
    range = 0x3C0000 - prediction.s_weight[0];
    prediction.s_weight[1] = clip(rshift32(weight[1], 8), -range, range);
    
    aptx_prediction_filtering(prediction, invert_quantize.reconstructed_difference, tables.prediction_order);
}
pub fn aptx_invert_quantize_and_prediction(channel: &mut AptxChannel, hd: i32) {
	println!("* aptx_invert_quantize_and_prediction");
    for subband in 0..4 {
        aptx_process_subband(
            &mut channel.invert_quantize[subband],
            &mut channel.prediction[subband],
            channel.quantize[subband].quantized_sample,
            channel.dither[subband],
            &ALL_TABLES[hd as usize][subband],
        );
    }
}
pub fn aptx_check_parity(channels: &[AptxChannel; 2], sync_idx: &mut u8) -> i32 {
	println!("* aptx_check_parity");
    let parity = aptx_quantized_parity(&channels[0]) ^ aptx_quantized_parity(&channels[1]);
    let eighth = (*sync_idx == 7) as i32;
    *sync_idx = (*sync_idx + 1) & 7;
    parity ^ eighth
}
pub fn aptx_insert_sync(channels: &mut [AptxChannel; 2], sync_idx: &mut u8) {
	println!("* aptx_insert_sync");
    const MAP: [usize; 4] = [1, 2, 0, 3];
    let mut min_idx = 0;
    
    if aptx_check_parity(channels, sync_idx) != 0 {
        // Initialize min with the first element we'll compare against
        let (mut min_channel_idx, mut min_quantize_idx) = (1, MAP[0]);
        let mut min_error = channels[min_channel_idx].quantize[min_quantize_idx].error;
        min_idx = min_quantize_idx;

        // Find the minimum error across all quantize elements
        for c_idx in (0..=1).rev() {
            for i in 0..4 {
                let current_error = channels[c_idx].quantize[MAP[i]].error;
                if current_error < min_error {
                    min_idx = i;
                    min_error = current_error;
                    min_channel_idx = c_idx;
                    min_quantize_idx = MAP[i];
                }
            }
        }
        
        // Apply the parity change to the element with minimum error
        channels[min_channel_idx].quantize[min_quantize_idx].quantized_sample = 
            channels[min_channel_idx].quantize[min_quantize_idx].quantized_sample_parity_change;
    }
}
pub fn rshift32_clip24(value: i32, shift: u32) -> i32 {
	println!("* rshift32_clip24");
    clip_intp2(rshift32(value, shift), 23)
}
pub fn aptx_quantize_difference(
    quantize: &mut AptxQuantize,
    sample_difference: i32,
    dither: i32,
    quantization_factor: i32,
    tables: &AptxTables,
) {
	println!("* aptx_quantize_difference");
    let intervals = tables.quantize_intervals.as_ref().unwrap();
    let mut intervals_idx = 0;
    let mut quantized_sample;
    let dithered_sample;
    let mut parity_change;
    let mut d;
    let mean;
    let interval;
    let inv;
    let mut sample_difference_abs = sample_difference;
    let error;

    // Handle absolute value and clipping
    if sample_difference_abs < 0 {
        sample_difference_abs = -sample_difference_abs;
    }
    if sample_difference_abs > ((1 << 23) - 1) {
        sample_difference_abs = (1 << 23) - 1;
    }

    quantized_sample = aptx_bin_search(
        sample_difference_abs >> 4,
        quantization_factor,
        intervals,
        tables.tables_size,
    );

    d = rshift32_clip24(
        (((dither as i64) * (dither as i64)) >> 32) as i32,
        7,
    ) - (1 << 23);
    d = rshift64(
        (d as i64) * (tables.quantize_dither_factors.as_ref().unwrap()[quantized_sample as usize] as i64),
        23,
    ) as i32;

    intervals_idx += quantized_sample as usize;
    mean = (intervals[1 + intervals_idx] + intervals[intervals_idx]) / 2;
    interval = (intervals[1 + intervals_idx] - intervals[intervals_idx])
        * ((if sample_difference < 0 { -1 } else { 0 }) | 1);

    dithered_sample = rshift64_clip24(
        ((dither as i64) * (interval as i64))
            + ((clip_intp2(mean + d, 23) as i64) << 32),
        32,
    );

    error = ((sample_difference_abs as i64) << 20)
        - ((dithered_sample as i64) * (quantization_factor as i64));

    quantize.error = rshift64(error, 23) as i32;
    if quantize.error < 0 {
        quantize.error = -quantize.error;
    }

    parity_change = quantized_sample;
    match error.cmp(&0) {
        Ordering::Less => {
            quantized_sample -= 1;
        }
        _ => {
            parity_change -= 1;
        }
    }
    parity_change -= 1;

    inv = if sample_difference < 0 { -1 } else { 0 };
    quantize.quantized_sample = quantized_sample ^ inv;
    quantize.quantized_sample_parity_change = parity_change ^ inv;
}

pub fn aptx_qmf_convolution(signal: &AptxFilterSignal, coeffs: &[i32; 16], shift: u32) -> i32 {
	println!("* aptx_qmf_convolution");
    let sig = &signal.buffer[signal.pos as usize..];
    let mut e: i64 = 0;
    
    for i in 0..16 {
        e += (sig[i] as i64) * (coeffs[i] as i64);
    }
    
    rshift64_clip24(e, shift)
}
pub fn aptx_qmf_polyphase_analysis(
    signal: &mut [AptxFilterSignal; 2],
    coeffs: &[[i32; 16]; 2],
    shift: u32,
    samples: &[i32; 2],
) -> (i32, i32) {
	println!("* aptx_qmf_polyphase_analysis");
    let mut subbands = [0i32; 2];
    
    for i in 0..2 {
        aptx_qmf_filter_signal_push(&mut signal[i], samples[(2 - 1) - i]);
        subbands[i] = aptx_qmf_convolution(&signal[i], &coeffs[i], shift);
    }
    
    (clip_intp2(subbands[0] + subbands[1], 23), clip_intp2(subbands[0] - subbands[1], 23))
}
pub fn aptx_qmf_tree_analysis(
    qmf: &mut AptxQmfAnalysis,
    samples: &[i32; 4],
    subband_samples: &mut [i32; 4],
) {
	println!("* aptx_qmf_tree_analysis");
    let mut intermediate_samples = [0i32; 4];
    
    // First loop - process outer filter
    for i in 0..2 {
        let samples_slice = [samples[2 * i], samples[2 * i + 1]];
        //let (low, high) = intermediate_samples.split_at_mut(2);
        let low_high = aptx_qmf_polyphase_analysis(
            &mut qmf.outer_filter_signal,
            &APTX_QMF_OUTER_COEFFS,
            23,
            &samples_slice,
        );
        intermediate_samples[0 + i] = low_high.0;
        intermediate_samples[2 + i] = low_high.1;
    }
    
    // Second loop - process inner filter
    for i in 0..2 {
        let intermediate_slice = [intermediate_samples[2 * i], intermediate_samples[2 * i + 1]];
        let low_high = aptx_qmf_polyphase_analysis(
            &mut qmf.inner_filter_signal[i],
            &APTX_QMF_INNER_COEFFS,
            23,
            &intermediate_slice,
        );
        subband_samples[2 * i] = low_high.0;
        subband_samples[2 * i + 1] = low_high.1;
    }
}
pub fn aptx_generate_dither(channel: &mut AptxChannel) {
	println!("* aptx_generate_dither");
    aptx_update_codeword_history(channel);
    let m = 5_184_443_i64 * (i64::from(channel.codeword_history) >> 7);
    let d = (m * 4 + (m >> 22)) as i32;
    
    for subband in 0..4 {
        channel.dither[subband] = ((d as u32) << (23 - (5 * subband))) as i32;
    }
    
    channel.dither_parity = (d >> 25) & 1;
}

pub fn aptx_encode_channel(channel: &mut AptxChannel, samples: &[i32; 4], hd: i32) {
	println!("* aptx_encode_channel");
    let mut subband_samples = [0i32; 4];
    let mut diff;
    
    aptx_qmf_tree_analysis(&mut channel.qmf, samples, &mut subband_samples);
    aptx_generate_dither(channel);
    
    for subband in 0..4 {
        diff = clip_intp2(
            subband_samples[subband] - channel.prediction[subband].predicted_sample,
            23
        );
        aptx_quantize_difference(
            &mut channel.quantize[subband],
            diff,
            channel.dither[subband],
            channel.invert_quantize[subband].quantization_factor,
            &ALL_TABLES[hd as usize][subband]
        );
    }
}
pub fn aptx_encode_samples(ctx: &mut AptxContext, samples: &[[i32; 4]; 2], output: &mut [u8]) {
	println!("* aptx_encode_samples");
    // First loop: encode each channel
    for channel in 0..2 {
        aptx_encode_channel(&mut ctx.channels[channel], &samples[channel], ctx.hd as i32);
    }

    // Insert sync
    aptx_insert_sync(&mut ctx.channels, &mut ctx.sync_idx);

    // Second loop: process and pack codewords
    for channel in 0..2 {
        aptx_invert_quantize_and_prediction(&mut ctx.channels[channel], ctx.hd as i32);
        
        if ctx.hd != 0 {
            let codeword = aptxhd_pack_codeword(&ctx.channels[channel]);
            output[(3 * channel)] = (codeword >> 16) as u8;
            output[(3 * channel) + 1] = (codeword >> 8) as u8;
            output[(3 * channel) + 2] = codeword as u8;
        } else {
            let codeword = aptx_pack_codeword(&ctx.channels[channel]);
            output[(2 * channel)] = (codeword >> 8) as u8;
            output[(2 * channel) + 1] = codeword as u8;
        }
    }
}
pub fn aptx_encode(
    ctx: &mut AptxContext,
    input: &[u8],
    output: &mut [u8],
    written: &mut usize,
) -> usize {
	println!("* aptx_encode");
    const NB_CHANNELS: usize = 2;
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut samples = [[0i32; 4]; NB_CHANNELS];
    let mut ipos = 0;
    let mut opos = 0;

    while ipos + (3 * NB_CHANNELS * 4) <= input.len() && opos + sample_size <= output.len() {
        for sample in 0..4 {
            for channel in 0..NB_CHANNELS {
                samples[channel][sample] = ((input[ipos] as u32)
                    | ((input[ipos + 1] as u32) << 8)
                    | ((input[ipos + 2] as i8 as u32) << 16)) as i32;
                ipos += 3;
            }
        }

        aptx_encode_samples(ctx, &samples, &mut output[opos..opos + sample_size]);
        opos += sample_size;
    }

    *written = opos;
    ipos
}
pub fn aptxhd_unpack_codeword(channel: &mut AptxChannel, codeword: u32) {
	println!("* aptxhd_unpack_codeword");
    channel.quantize[0].quantized_sample = sign_extend((codeword >> 0) as i32, 9);
    channel.quantize[1].quantized_sample = sign_extend((codeword >> 9) as i32, 6);
    channel.quantize[2].quantized_sample = sign_extend((codeword >> 15) as i32, 4);
    channel.quantize[3].quantized_sample = sign_extend((codeword >> 19) as i32, 5);
    channel.quantize[3].quantized_sample = (channel.quantize[3].quantized_sample & (!1)) | aptx_quantized_parity(channel);
}
pub fn aptx_unpack_codeword(channel: &mut AptxChannel, codeword: u16) {
	println!("* aptx_unpack_codeword");
    channel.quantize[0].quantized_sample = sign_extend((codeword >> 0) as i32, 7);
    channel.quantize[1].quantized_sample = sign_extend((codeword >> 7) as i32, 4);
    channel.quantize[2].quantized_sample = sign_extend((codeword >> 11) as i32, 2);
    channel.quantize[3].quantized_sample = sign_extend((codeword >> 13) as i32, 3);
    channel.quantize[3].quantized_sample = (channel.quantize[3].quantized_sample & (!1)) | aptx_quantized_parity(channel);
}
pub fn aptx_qmf_polyphase_synthesis(
    signal: &mut [AptxFilterSignal; 2],
    coeffs: &[[i32; 16]; 2],
    shift: u32,
    low_subband_input: i32,
    high_subband_input: i32,
    samples: &mut [i32; 2],
) {
	println!("* aptx_qmf_polyphase_synthesis");
    let subbands = [
        low_subband_input + high_subband_input,
        low_subband_input - high_subband_input,
    ];

    for i in 0..2 {
        aptx_qmf_filter_signal_push(&mut signal[i], subbands[1 - i]);
        samples[i] = aptx_qmf_convolution(&signal[i], &coeffs[i], shift);
    }
}
pub fn aptx_qmf_tree_synthesis(
    qmf: &mut AptxQmfAnalysis,
    subband_samples: &[i32; 4],
    samples: &mut [i32; 4],
) {
	println!("* aptx_qmf_tree_synthesis");
    let mut intermediate_samples = [0; 4];
    
    // First loop: process inner filters
    for i in 0..2 {
        aptx_qmf_polyphase_synthesis(
            &mut qmf.inner_filter_signal[i],
            &APTX_QMF_INNER_COEFFS,
            22,
            subband_samples[2 * i],
            subband_samples[2 * i + 1],
            &mut intermediate_samples[2 * i..=2 * i + 1].try_into().unwrap(),
        );
    }
    
    // Second loop: process outer filters
    for i in 0..2 {
        aptx_qmf_polyphase_synthesis(
            &mut qmf.outer_filter_signal,
            &APTX_QMF_OUTER_COEFFS,
            21,
            intermediate_samples[i],
            intermediate_samples[2 + i],
            &mut samples[2 * i..=2 * i + 1].try_into().unwrap(),
        );
    }
}
pub fn aptx_decode_channel(channel: &mut AptxChannel, samples: &mut [i32; 4]) {
	println!("* aptx_decode_channel");
    let mut subband_samples = [0; 4];
    
    for subband in 0..4 {
        subband_samples[subband] = channel.prediction[subband].previous_reconstructed_sample;
    }

    aptx_qmf_tree_synthesis(&mut channel.qmf, &subband_samples, samples);
}
pub fn aptx_decode_samples(
    ctx: &mut AptxContext,
    input: &[u8],
    samples: &mut [[i32; 4]; 2], // NB_CHANNELS is 2
) -> i32 {
	println!("* aptx_decode_samples");
    // Process each channel
    for channel in 0..2 {
        {
            let ctx_channel = &mut ctx.channels[channel];
            aptx_generate_dither(ctx_channel);

            if ctx.hd != 0 {
                let codeword = (input[3 * channel] as u32) << 16
                    | (input[3 * channel + 1] as u32) << 8
                    | (input[3 * channel + 2] as u32);
                aptxhd_unpack_codeword(ctx_channel, codeword);
            } else {
                let codeword = (input[2 * channel] as u16) << 8 | (input[2 * channel + 1] as u16);
                aptx_unpack_codeword(ctx_channel, codeword);
            }

            aptx_invert_quantize_and_prediction(ctx_channel, ctx.hd as i32);
        }
    }

    let ret = aptx_check_parity(&ctx.channels, &mut ctx.sync_idx);

    // Decode each channel
    for channel in 0..2 {
        aptx_decode_channel(&mut ctx.channels[channel], &mut samples[channel]);
    }

    ret
}
pub fn aptx_decode(
    ctx: &mut AptxContext,
    input: &[u8],
    output: &mut [u8],
    written: &mut usize,
) -> usize {
	println!("* aptx_decode");
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut samples = [[0i32; 4]; 2]; // NB_CHANNELS is 2
    let mut ipos = 0;
    let mut opos = 0;

    while (ipos + sample_size) <= input.len() 
        && ((opos + (3 * 2 * 4)) <= output.len() || ctx.decode_skip_leading > 0) 
    {
        if aptx_decode_samples(ctx, &input[ipos..], &mut samples) != 0 {
            break;
        }

        let mut sample = 0;
        if ctx.decode_skip_leading > 0 {
            ctx.decode_skip_leading -= 1;
            if ctx.decode_skip_leading > 0 {
                ipos += sample_size;
                continue;
            }
            sample = 90 % 4;
        }

        for sample_idx in sample..4 {
            for channel in 0..2 {
                let value = samples[channel][sample_idx] as u32;
                output[opos] = (value & 0xFF) as u8;
                output[opos + 1] = ((value >> 8) & 0xFF) as u8;
                output[opos + 2] = ((value >> 16) & 0xFF) as u8;
                opos += 3;
            }
        }

        ipos += sample_size;
    }

    *written = opos;
    ipos
}
pub fn aptx_decode_sync_finish(ctx: &mut AptxContext) -> usize {
	println!("* aptx_decode_sync_finish");
    let dropped = ctx.decode_sync_buffer_len as usize;
    aptx_reset(ctx);
    dropped
}
pub fn aptx_reset_decode_sync(ctx: &mut AptxContext) {
	println!("* aptx_reset_decode_sync");
    // Save the current state before resetting
    let decode_dropped = ctx.decode_dropped;
    let decode_sync_packets = ctx.decode_sync_packets;
    let decode_sync_buffer_len = ctx.decode_sync_buffer_len;
    let decode_sync_buffer = ctx.decode_sync_buffer;

    // Reset the context
    aptx_reset(ctx);

    // Restore the saved state
    ctx.decode_sync_buffer = decode_sync_buffer;
    ctx.decode_sync_buffer_len = decode_sync_buffer_len;
    ctx.decode_sync_packets = decode_sync_packets;
    ctx.decode_dropped = decode_dropped;
}
pub fn aptx_encode_finish(
    ctx: &mut AptxContext,
    output: &mut [u8],
    output_size: usize,
    written: &mut usize,
) -> i32 {
	println!("* aptx_encode_finish");
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut samples = [[0i32; 4]; 2]; // NB_CHANNELS is 2

    if ctx.encode_remaining == 0 {
        *written = 0;
        return 1;
    }

    let mut opos = 0;
    while ctx.encode_remaining > 0 && (opos + sample_size) <= output_size {
        aptx_encode_samples(ctx, &samples, &mut output[opos..opos + sample_size]);
        ctx.encode_remaining -= 1;
        opos += sample_size;
    }

    *written = opos;

    if ctx.encode_remaining > 0 {
        return 0;
    }

    aptx_reset(ctx);
    1
}
pub fn helper_aptx_decode_sync_2(
    input_size_step_ref: &mut usize,
    processed_step_ref: &mut usize,
    ipos_ref: &mut usize,
    opos_ref: &mut usize,
    ctx: &mut AptxContext,
    input: &[u8],
    output: &mut [u8],
    synced: &mut i32,
    dropped: &mut usize,
    sample_size: usize,
    written_step: usize,
) {
	println!("* helper_aptx_decode_sync_2");
    let mut input_size_step = *input_size_step_ref;
    let mut processed_step = *processed_step_ref;
    let mut ipos = *ipos_ref;
    let mut opos = *opos_ref;

    input_size_step = (((((output.len() - opos) / 3) * 2) * 4) + ctx.decode_skip_leading as usize) * sample_size;
    if input_size_step > ((input.len() - ipos) / sample_size) * sample_size {
        input_size_step = ((input.len() - ipos) / sample_size) * sample_size;
    }

    if input_size_step > (((90 + 3) / 4 - ctx.decode_sync_packets) * sample_size) && ctx.decode_dropped > 0 {
        input_size_step = ((90 + 3) / 4 - ctx.decode_sync_packets) * sample_size;
    }

    let mut written_step_local = written_step;
    processed_step = aptx_decode(
        ctx,
        &input[ipos..],
        &mut output[opos..],
        &mut written_step_local,
    );
    ipos += processed_step;
    opos += written_step_local;

    if ctx.decode_dropped > 0 && (processed_step / sample_size) > 0 {
        ctx.decode_dropped += processed_step;
        ctx.decode_sync_packets += processed_step / sample_size;
        if ctx.decode_sync_packets >= (90 + 3) / 4 {
            *dropped += ctx.decode_dropped;
            ctx.decode_dropped = 0;
            ctx.decode_sync_packets = 0;
        }
    }

    if processed_step < input_size_step {
        aptx_reset_decode_sync(ctx);
        *synced = 0;
        ipos += 1;
        ctx.decode_dropped += 1;
        ctx.decode_sync_packets = 0;
    } else if ctx.decode_dropped == 0 {
        *synced = 1;
    }

    *input_size_step_ref = input_size_step;
    *processed_step_ref = processed_step;
    *ipos_ref = ipos;
    *opos_ref = opos;
}
pub fn helper_aptx_decode_sync_1(
    sample_size_ref: &mut usize,
    processed_step_ref: &mut usize,
    ipos_ref: &mut usize,
    opos_ref: &mut usize,
    i_ref: &mut usize,
    ctx: &mut AptxContext,
    input: &[u8],
    output: &mut [u8],
    output_size: usize,
    synced: &mut i32,
    dropped: &mut usize,
    written_step: usize,
) {
	println!("* helper_aptx_decode_sync_1");
    let sample_size = *sample_size_ref;
    let mut processed_step = *processed_step_ref;
    let mut ipos = *ipos_ref;
    let mut opos = *opos_ref;
    let mut i = *i_ref;

    // Update decode_sync_buffer with current input
    ctx.decode_sync_buffer[sample_size - 1] = input[ipos];
    ipos += 1;

    // Create a temporary buffer slice to avoid simultaneous borrows
    let buffer_slice = ctx.decode_sync_buffer[..sample_size].to_vec();

    // Perform decoding
    let output_slice = &mut output[opos..output_size];
    let mut written_step_local = written_step;
    processed_step = aptx_decode(
        ctx,
        &buffer_slice,
        output_slice,
        &mut written_step_local,
    );
    opos += written_step_local;

    if ctx.decode_dropped > 0 && processed_step == sample_size {
        ctx.decode_dropped += processed_step;
        ctx.decode_sync_packets += 1;
        if ctx.decode_sync_packets >= (90 + 3) / 4 {
            *dropped += ctx.decode_dropped;
            ctx.decode_dropped = 0;
            ctx.decode_sync_packets = 0;
        }
    }

    if processed_step < sample_size {
        aptx_reset_decode_sync(ctx);
        *synced = 0;
        ctx.decode_dropped += 1;
        ctx.decode_sync_packets = 0;

        // Shift buffer contents
        for i in 0..(sample_size - 1) {
            ctx.decode_sync_buffer[i] = ctx.decode_sync_buffer[i + 1];
        }
    } else {
        if ctx.decode_dropped == 0 {
            *synced = 1;
        }
        ctx.decode_sync_buffer_len = 0;
    }

    // Update references
    *sample_size_ref = sample_size;
    *processed_step_ref = processed_step;
    *ipos_ref = ipos;
    *opos_ref = opos;
    *i_ref = i;
}
pub fn aptx_decode_sync(
    ctx: &mut AptxContext,
    input: &[u8],
    output: &mut [u8],
    written: &mut usize,
    synced: &mut i32,
    dropped: &mut usize,
) -> usize {
	println!("* aptx_decode_sync");
    let sample_size = if ctx.hd != 0 { 6 } else { 4 };
    let mut ipos = 0;
    let mut opos = 0;
    
    *synced = 0;
    *dropped = 0;
    
    if ctx.decode_sync_buffer_len > 0 && (sample_size - 1 - ctx.decode_sync_buffer_len as usize) <= input.len() {
        while ctx.decode_sync_buffer_len < (sample_size - 1) as u8 {
            ctx.decode_sync_buffer[ctx.decode_sync_buffer_len as usize] = input[ipos];
            ctx.decode_sync_buffer_len += 1;
            ipos += 1;
        }
    }
    
    while ctx.decode_sync_buffer_len == (sample_size - 1) as u8 
        && ipos < sample_size 
        && ipos < input.len() 
        && (opos + (3 * 2 * 4) <= output.len() 
            || ctx.decode_skip_leading > 0 
            || ctx.decode_dropped > 0)
    {
        let mut sample_size_ref = sample_size;
        let mut processed_step = 0;
        let mut written_step = 0;
        let mut i = 0;
        
        helper_aptx_decode_sync_1(
            &mut sample_size_ref,
            &mut processed_step,
            &mut ipos,
            &mut opos,
            &mut i,
            ctx,
            input,
            output,
            output.len(),
            synced,
            dropped,
            written_step,
        );
    }
    
    if ctx.decode_sync_buffer_len == (sample_size - 1) as u8 && ipos == sample_size {
        ipos = 0;
        ctx.decode_sync_buffer_len = 0;
    }
    
    while ipos + sample_size <= input.len() 
        && (opos + (3 * 2 * 4) <= output.len() 
            || ctx.decode_skip_leading > 0 
            || ctx.decode_dropped > 0)
    {
        let mut input_size_step = 0;
        let mut processed_step = 0;
        let mut written_step = 0;
        
        helper_aptx_decode_sync_2(
            &mut input_size_step,
            &mut processed_step,
            &mut ipos,
            &mut opos,
            ctx,
            input,
            output,
            synced,
            dropped,
            sample_size,
            written_step,
        );
    }
    
    if ipos + sample_size > input.len() {
        while ipos < input.len() {
            ctx.decode_sync_buffer[ctx.decode_sync_buffer_len as usize] = input[ipos];
            ctx.decode_sync_buffer_len += 1;
            ipos += 1;
        }
    }
    
    *written = opos;
    ipos
}
