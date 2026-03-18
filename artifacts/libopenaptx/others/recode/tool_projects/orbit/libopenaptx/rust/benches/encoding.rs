// Benchmark suite for libopenaptx encoding/decoding performance
//
// This benchmark file is provided to measure the performance characteristics
// of the aptX codec implementation.
//
// Run with: cargo bench

use criterion::{black_box, criterion_group, criterion_main, Criterion, Throughput};
use libopenaptx::{aptx_decode, aptx_encode, aptx_finish, aptx_init};

const SAMPLE_COUNT: usize = 4096; // Number of stereo sample pairs
const NB_CHANNELS: usize = 2;

fn create_test_samples() -> Vec<u8> {
    // Generate test audio samples (sine wave pattern)
    // Each sample is 24-bit signed, stored as 3 bytes
    let mut samples = Vec::with_capacity(SAMPLE_COUNT * 4 * NB_CHANNELS * 3);
    for i in 0..SAMPLE_COUNT * 4 {
        let phase = (i as f64) * 2.0 * std::f64::consts::PI / 100.0;
        let sample = (phase.sin() * 8388607.0) as i32; // 24-bit range

        // Stereo: left and right channels (3 bytes per sample, 24-bit)
        for _ in 0..NB_CHANNELS {
            samples.push(((sample >> 0) & 0xFF) as u8);
            samples.push(((sample >> 8) & 0xFF) as u8);
            samples.push(((sample >> 16) & 0xFF) as u8);
        }
    }
    samples
}

fn benchmark_aptx_encoding(c: &mut Criterion) {
    let mut group = c.benchmark_group("aptx_encoding");
    group.throughput(Throughput::Elements(SAMPLE_COUNT as u64));

    group.bench_function("encode_standard", |b| {
        let samples = create_test_samples();

        b.iter(|| {
            let mut ctx = aptx_init(0).expect("Failed to initialize context");
            let mut output = vec![0u8; SAMPLE_COUNT * 4];
            let mut written = 0;
            let samples_len = samples.len();
            let output_len = output.len();
            let consumed = aptx_encode(
                ctx.as_mut(),
                black_box(&samples),
                samples_len,
                black_box(&mut output),
                output_len,
                &mut written,
            );
            black_box((consumed, written));
            aptx_finish(ctx);
        });
    });

    group.bench_function("encode_hd", |b| {
        let samples = create_test_samples();

        b.iter(|| {
            let mut ctx = aptx_init(1).expect("Failed to initialize context");
            let mut output = vec![0u8; SAMPLE_COUNT * 6];
            let mut written = 0;
            let samples_len = samples.len();
            let output_len = output.len();
            let consumed = aptx_encode(
                ctx.as_mut(),
                black_box(&samples),
                samples_len,
                black_box(&mut output),
                output_len,
                &mut written,
            );
            black_box((consumed, written));
            aptx_finish(ctx);
        });
    });

    group.finish();
}

fn benchmark_aptx_decoding(c: &mut Criterion) {
    let mut group = c.benchmark_group("aptx_decoding");
    group.throughput(Throughput::Elements(SAMPLE_COUNT as u64));

    group.bench_function("decode_standard", |b| {
        // Pre-encode some samples for decoding
        let samples = create_test_samples();
        let mut ctx = aptx_init(0).expect("Failed to initialize context");
        let mut encoded = vec![0u8; SAMPLE_COUNT * 4];
        let mut written = 0;
        let samples_len = samples.len();
        let encoded_len = encoded.len();
        aptx_encode(
            ctx.as_mut(),
            &samples,
            samples_len,
            &mut encoded,
            encoded_len,
            &mut written,
        );
        aptx_finish(ctx);

        // Trim to actual written size
        encoded.truncate(written);

        // Benchmark decoding
        b.iter(|| {
            let mut ctx = aptx_init(0).expect("Failed to initialize context");
            let mut output = vec![0u8; SAMPLE_COUNT * 4 * NB_CHANNELS * 3];
            let mut written = 0;
            let encoded_len = encoded.len();
            let output_len = output.len();
            let consumed = aptx_decode(
                ctx.as_mut(),
                black_box(&encoded),
                encoded_len,
                black_box(&mut output),
                output_len,
                &mut written,
            );
            black_box((consumed, written));
            aptx_finish(ctx);
        });
    });

    group.bench_function("decode_hd", |b| {
        // Pre-encode some samples for decoding
        let samples = create_test_samples();
        let mut ctx = aptx_init(1).expect("Failed to initialize context");
        let mut encoded = vec![0u8; SAMPLE_COUNT * 6];
        let mut written = 0;
        let samples_len = samples.len();
        let encoded_len = encoded.len();
        aptx_encode(
            ctx.as_mut(),
            &samples,
            samples_len,
            &mut encoded,
            encoded_len,
            &mut written,
        );
        aptx_finish(ctx);

        // Trim to actual written size
        encoded.truncate(written);

        // Benchmark decoding
        b.iter(|| {
            let mut ctx = aptx_init(1).expect("Failed to initialize context");
            let mut output = vec![0u8; SAMPLE_COUNT * 4 * NB_CHANNELS * 3];
            let mut written = 0;
            let encoded_len = encoded.len();
            let output_len = output.len();
            let consumed = aptx_decode(
                ctx.as_mut(),
                black_box(&encoded),
                encoded_len,
                black_box(&mut output),
                output_len,
                &mut written,
            );
            black_box((consumed, written));
            aptx_finish(ctx);
        });
    });

    group.finish();
}

fn benchmark_roundtrip(c: &mut Criterion) {
    let mut group = c.benchmark_group("aptx_roundtrip");
    group.throughput(Throughput::Elements(SAMPLE_COUNT as u64));

    group.bench_function("roundtrip_standard", |b| {
        let samples = create_test_samples();

        b.iter(|| {
            // Encode
            let mut enc_ctx = aptx_init(0).expect("Failed to initialize context");
            let mut encoded = vec![0u8; SAMPLE_COUNT * 4];
            let mut written = 0;
            let samples_len = samples.len();
            let encoded_len = encoded.len();
            aptx_encode(
                enc_ctx.as_mut(),
                black_box(&samples),
                samples_len,
                &mut encoded,
                encoded_len,
                &mut written,
            );
            aptx_finish(enc_ctx);

            // Decode
            let mut dec_ctx = aptx_init(0).expect("Failed to initialize context");
            let mut decoded = vec![0u8; SAMPLE_COUNT * 4 * NB_CHANNELS * 3];
            let mut dec_written = 0;
            let decoded_len = decoded.len();
            aptx_decode(
                dec_ctx.as_mut(),
                &encoded[..written],
                written,
                &mut decoded,
                decoded_len,
                &mut dec_written,
            );
            aptx_finish(dec_ctx);

            black_box((written, dec_written));
        });
    });

    group.bench_function("roundtrip_hd", |b| {
        let samples = create_test_samples();

        b.iter(|| {
            // Encode
            let mut enc_ctx = aptx_init(1).expect("Failed to initialize context");
            let mut encoded = vec![0u8; SAMPLE_COUNT * 6];
            let mut written = 0;
            let samples_len = samples.len();
            let encoded_len = encoded.len();
            aptx_encode(
                enc_ctx.as_mut(),
                black_box(&samples),
                samples_len,
                &mut encoded,
                encoded_len,
                &mut written,
            );
            aptx_finish(enc_ctx);

            // Decode
            let mut dec_ctx = aptx_init(1).expect("Failed to initialize context");
            let mut decoded = vec![0u8; SAMPLE_COUNT * 4 * NB_CHANNELS * 3];
            let mut dec_written = 0;
            let decoded_len = decoded.len();
            aptx_decode(
                dec_ctx.as_mut(),
                &encoded[..written],
                written,
                &mut decoded,
                decoded_len,
                &mut dec_written,
            );
            aptx_finish(dec_ctx);

            black_box((written, dec_written));
        });
    });

    group.finish();
}

criterion_group!(
    benches,
    benchmark_aptx_encoding,
    benchmark_aptx_decoding,
    benchmark_roundtrip
);
criterion_main!(benches);
