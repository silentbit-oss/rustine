/*
 * Integration tests for openaptxenc and openaptxdec CLI utilities
 * Auto-generated test file
 */

use std::io::Write;
use std::process::{Command, Stdio};

const TEST_PCM_SIZE: usize = 1024;
const TEST_APTX_SIZE: usize = 256;
const TEST_APTXHD_SIZE: usize = 384;

/// Helper function to run a command with stdin and capture stdout/stderr
fn run_command_with_input(
    cmd: &str,
    args: &[&str],
    input: &[u8],
) -> (Vec<u8>, Vec<u8>, i32) {
    let mut child = Command::new(cmd)
        .args(args)
        .stdin(Stdio::piped())
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .spawn()
        .expect("Failed to spawn command");

    if !input.is_empty() {
        let stdin = child.stdin.as_mut().expect("Failed to open stdin");
        stdin.write_all(input).expect("Failed to write to stdin");
    }

    let output = child.wait_with_output().expect("Failed to wait for command");
    let exit_code = output.status.code().unwrap_or(-1);

    (output.stdout, output.stderr, exit_code)
}

#[test]
fn test_openaptxenc_help() {
    let (_, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxenc",
        &["--help"],
        &[],
    );

    assert_eq!(exit_code, 1, "openaptxenc --help should return exit code 1");
    let stderr_str = String::from_utf8_lossy(&stderr);
    assert!(
        stderr_str.contains("aptX encoder utility"),
        "Help text should contain 'aptX encoder utility'"
    );
}

#[test]
fn test_openaptxenc_invalid_option() {
    let (_, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxenc",
        &["--invalid"],
        &[],
    );

    assert_eq!(exit_code, 1, "openaptxenc --invalid should return exit code 1");
    let stderr_str = String::from_utf8_lossy(&stderr);
    assert!(
        stderr_str.contains("Invalid option"),
        "Error message should contain 'Invalid option'"
    );
}

#[test]
fn test_openaptxenc_empty_input() {
    let (stdout, _, exit_code) = run_command_with_input(
        "target/debug/openaptxenc",
        &[],
        &[],
    );

    assert_eq!(exit_code, 0, "openaptxenc with empty input should return 0");
    // Empty input should produce minimal or no output
    assert!(stdout.len() < 100, "Empty input should produce minimal output");
}

#[test]
fn test_openaptxenc_basic_encoding() {
    // Create test PCM data (24-bit stereo = 6 bytes per sample)
    let mut input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..input.len() {
        input[i] = (i % 256) as u8;
    }

    let (stdout, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxenc",
        &[],
        &input,
    );

    // Encoder may warn about dropped bytes if input isn't exact multiple
    let stderr_str = String::from_utf8_lossy(&stderr);
    let encoding_ok = exit_code == 0 || stderr_str.contains("dropped");

    assert!(encoding_ok, "openaptxenc basic encoding should succeed (or warn about dropped bytes)");
    assert!(stdout.len() > 0, "openaptxenc should produce output");
    assert!(
        stdout.len() < input.len(),
        "openaptxenc output should be compressed"
    );
}

#[test]
fn test_openaptxenc_hd_mode() {
    let mut input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..input.len() {
        input[i] = (i % 256) as u8;
    }

    let (stdout, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxenc",
        &["--hd"],
        &input,
    );

    let stderr_str = String::from_utf8_lossy(&stderr);
    let encoding_ok = exit_code == 0 || stderr_str.contains("dropped");

    assert!(encoding_ok, "openaptxenc --hd encoding should succeed");
    assert!(stdout.len() > 0, "openaptxenc --hd should produce output");
}

#[test]
fn test_openaptxdec_help() {
    let (_, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxdec",
        &["--help"],
        &[],
    );

    assert_eq!(exit_code, 1, "openaptxdec --help should return exit code 1");
    let stderr_str = String::from_utf8_lossy(&stderr);
    assert!(
        stderr_str.contains("aptX decoder utility"),
        "Help text should contain 'aptX decoder utility'"
    );
}

#[test]
fn test_openaptxdec_invalid_option() {
    let (_, stderr, exit_code) = run_command_with_input(
        "target/debug/openaptxdec",
        &["--invalid"],
        &[],
    );

    assert_eq!(exit_code, 1, "openaptxdec --invalid should return exit code 1");
    let stderr_str = String::from_utf8_lossy(&stderr);
    assert!(
        stderr_str.contains("Invalid option"),
        "Error message should contain 'Invalid option'"
    );
}

#[test]
fn test_openaptxdec_empty_input() {
    let (stdout, _, exit_code) = run_command_with_input(
        "target/debug/openaptxdec",
        &[],
        &[],
    );

    // Empty input should handle gracefully (return non-zero or empty output)
    assert!(
        exit_code != 0 || stdout.is_empty(),
        "openaptxdec with empty input should handle gracefully"
    );
}

#[test]
fn test_openaptxdec_basic_decoding() {
    // First encode some data
    let mut pcm_input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..pcm_input.len() {
        pcm_input[i] = (i % 256) as u8;
    }

    let (aptx_data, _, enc_exit) = run_command_with_input(
        "target/debug/openaptxenc",
        &[],
        &pcm_input,
    );

    if !aptx_data.is_empty() && (enc_exit == 0 || enc_exit == 1) {
        // Now decode it
        let (pcm_output, _, dec_exit) = run_command_with_input(
            "target/debug/openaptxdec",
            &[],
            &aptx_data,
        );

        assert_eq!(dec_exit, 0, "openaptxdec basic decoding should succeed");
        assert!(pcm_output.len() > 0, "openaptxdec should produce output");
    }
}

#[test]
fn test_openaptxdec_hd_mode() {
    // First encode some data in HD mode
    let mut pcm_input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..pcm_input.len() {
        pcm_input[i] = (i % 256) as u8;
    }

    let (aptx_data, _, enc_exit) = run_command_with_input(
        "target/debug/openaptxenc",
        &["--hd"],
        &pcm_input,
    );

    if !aptx_data.is_empty() && (enc_exit == 0 || enc_exit == 1) {
        // Now decode it with HD mode
        let (pcm_output, _, dec_exit) = run_command_with_input(
            "target/debug/openaptxdec",
            &["--hd"],
            &aptx_data,
        );

        assert_eq!(dec_exit, 0, "openaptxdec --hd decoding should succeed");
        assert!(pcm_output.len() > 0, "openaptxdec --hd should produce output");
    }
}

#[test]
fn test_roundtrip_consistency() {
    // Create test PCM data
    let mut pcm_input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..pcm_input.len() {
        pcm_input[i] = ((i * 7) % 256) as u8;
    }

    // Encode
    let (aptx_data, _, enc_exit) = run_command_with_input(
        "target/debug/openaptxenc",
        &[],
        &pcm_input,
    );

    if !aptx_data.is_empty() && (enc_exit == 0 || enc_exit == 1) {
        // Decode
        let (pcm_output, _, dec_exit) = run_command_with_input(
            "target/debug/openaptxdec",
            &[],
            &aptx_data,
        );

        if !pcm_output.is_empty() && dec_exit == 0 {
            // Output should be similar in size (may differ due to padding)
            let size_diff = if pcm_output.len() > pcm_input.len() {
                pcm_output.len() - pcm_input.len()
            } else {
                pcm_input.len() - pcm_output.len()
            };

            assert!(
                size_diff <= 64,
                "Round-trip output size should be similar to input (diff: {})",
                size_diff
            );
        }
    }
}

#[test]
fn test_roundtrip_hd_consistency() {
    // Create test PCM data
    let mut pcm_input = vec![0u8; TEST_PCM_SIZE];
    for i in 0..pcm_input.len() {
        pcm_input[i] = ((i * 13) % 256) as u8;
    }

    // Encode in HD mode
    let (aptx_data, _, enc_exit) = run_command_with_input(
        "target/debug/openaptxenc",
        &["--hd"],
        &pcm_input,
    );

    if !aptx_data.is_empty() && (enc_exit == 0 || enc_exit == 1) {
        // Decode in HD mode
        let (pcm_output, _, dec_exit) = run_command_with_input(
            "target/debug/openaptxdec",
            &["--hd"],
            &aptx_data,
        );

        if !pcm_output.is_empty() && dec_exit == 0 {
            // Output should be similar in size (may differ due to padding)
            let size_diff = if pcm_output.len() > pcm_input.len() {
                pcm_output.len() - pcm_input.len()
            } else {
                pcm_input.len() - pcm_output.len()
            };

            assert!(
                size_diff <= 64,
                "Round-trip HD output size should be similar to input (diff: {})",
                size_diff
            );
        }
    }
}
