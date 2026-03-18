/*
 * Integration tests for openaptxenc and openaptxdec CLI utilities
 * Auto-generated test file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define TEST_PCM_SIZE 1024
#define TEST_APTX_SIZE 256
#define TEST_APTXHD_SIZE 384

static int test_count = 0;
static int test_passed = 0;

void assert_test(int condition, const char *test_name) {
    test_count++;
    if (condition) {
        printf("PASS: %s\n", test_name);
        test_passed++;
    } else {
        printf("FAIL: %s\n", test_name);
    }
}

/* Helper to run a command with stdin/stdout pipes */
int run_command(const char *cmd, const char *input_data, size_t input_len,
                char *output_data, size_t output_max, size_t *output_len,
                int *exit_code) {
    int pipe_in[2], pipe_out[2];
    pid_t pid;

    if (pipe(pipe_in) == -1 || pipe(pipe_out) == -1) {
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        return -1;
    }

    if (pid == 0) {
        /* Child process */
        close(pipe_in[1]);
        close(pipe_out[0]);

        dup2(pipe_in[0], STDIN_FILENO);
        dup2(pipe_out[1], STDOUT_FILENO);

        close(pipe_in[0]);
        close(pipe_out[1]);

        /* Set LD_LIBRARY_PATH for shared library */
        setenv("LD_LIBRARY_PATH", ".", 1);

        execl("/bin/sh", "sh", "-c", cmd, NULL);
        exit(1);
    } else {
        /* Parent process */
        close(pipe_in[0]);
        close(pipe_out[1]);

        /* Write input */
        if (input_data && input_len > 0) {
            write(pipe_in[1], input_data, input_len);
        }
        close(pipe_in[1]);

        /* Read output */
        *output_len = 0;
        if (output_data) {
            ssize_t n = read(pipe_out[0], output_data, output_max);
            if (n > 0) {
                *output_len = n;
            }
        }
        close(pipe_out[0]);

        /* Wait for child */
        int status;
        waitpid(pid, &status, 0);
        *exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

        return 0;
    }
}

/* Helper to run a command and capture stderr */
int run_command_stderr(const char *cmd, char *stderr_data, size_t stderr_max,
                       size_t *stderr_len, int *exit_code) {
    int pipe_err[2];
    pid_t pid;

    if (pipe(pipe_err) == -1) {
        return -1;
    }

    pid = fork();
    if (pid == -1) {
        return -1;
    }

    if (pid == 0) {
        /* Child process */
        close(pipe_err[0]);
        dup2(pipe_err[1], STDERR_FILENO);
        close(pipe_err[1]);

        /* Set LD_LIBRARY_PATH for shared library */
        setenv("LD_LIBRARY_PATH", ".", 1);

        execl("/bin/sh", "sh", "-c", cmd, NULL);
        exit(1);
    } else {
        /* Parent process */
        close(pipe_err[1]);

        /* Read stderr */
        *stderr_len = 0;
        if (stderr_data) {
            ssize_t n = read(pipe_err[0], stderr_data, stderr_max);
            if (n > 0) {
                *stderr_len = n;
            }
        }
        close(pipe_err[0]);

        /* Wait for child */
        int status;
        waitpid(pid, &status, 0);
        *exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;

        return 0;
    }
}

/* Test 1: openaptxenc help output */
void test_openaptxenc_help() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command_stderr("./openaptxenc --help", output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 1, "openaptxenc --help returns exit code 1");
    assert_test(output_len > 0 && strstr(output, "aptX encoder utility") != NULL,
                "openaptxenc --help displays help text");
}

/* Test 2: openaptxenc invalid option */
void test_openaptxenc_invalid_option() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command_stderr("./openaptxenc --invalid", output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 1, "openaptxenc --invalid returns exit code 1");
    assert_test(output_len > 0 && strstr(output, "Invalid option") != NULL,
                "openaptxenc --invalid displays error message");
}

/* Test 3: openaptxenc empty input */
void test_openaptxenc_empty_input() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command("./openaptxenc", "", 0, output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 0, "openaptxenc with empty input returns 0");
    /* Empty input should produce minimal or no output */
}

/* Test 4: openaptxenc basic encoding */
void test_openaptxenc_basic_encoding() {
    char input[TEST_PCM_SIZE];
    char output[TEST_APTX_SIZE * 2];
    size_t output_len;
    int exit_code;

    /* Create test PCM data (24-bit stereo = 6 bytes per sample) */
    memset(input, 0, sizeof(input));
    for (size_t i = 0; i < sizeof(input); i++) {
        input[i] = i % 256;
    }

    run_command("./openaptxenc", input, sizeof(input), output, sizeof(output), &output_len, &exit_code);

    /* Exit code may be 1 if encoder warns about dropped bytes (not exact multiple of sample size) */
    assert_test(exit_code == 0 || exit_code == 1, "openaptxenc basic encoding succeeds (or warns)");
    assert_test(output_len > 0, "openaptxenc produces output");
    /* aptX compresses roughly 4:1, so expect smaller output */
    assert_test(output_len < sizeof(input), "openaptxenc output is compressed");
}

/* Test 5: openaptxenc HD mode */
void test_openaptxenc_hd_mode() {
    char input[TEST_PCM_SIZE];
    char output[TEST_APTXHD_SIZE * 2];
    size_t output_len;
    int exit_code;

    memset(input, 0, sizeof(input));
    for (size_t i = 0; i < sizeof(input); i++) {
        input[i] = i % 256;
    }

    run_command("./openaptxenc --hd", input, sizeof(input), output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 0 || exit_code == 1, "openaptxenc --hd encoding succeeds (or warns)");
    assert_test(output_len > 0, "openaptxenc --hd produces output");
}

/* Test 6: openaptxdec help output */
void test_openaptxdec_help() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command_stderr("./openaptxdec --help", output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 1, "openaptxdec --help returns exit code 1");
    assert_test(output_len > 0 && strstr(output, "aptX decoder utility") != NULL,
                "openaptxdec --help displays help text");
}

/* Test 7: openaptxdec invalid option */
void test_openaptxdec_invalid_option() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command_stderr("./openaptxdec --invalid", output, sizeof(output), &output_len, &exit_code);

    assert_test(exit_code == 1, "openaptxdec --invalid returns exit code 1");
    assert_test(output_len > 0 && strstr(output, "Invalid option") != NULL,
                "openaptxdec --invalid displays error message");
}

/* Test 8: openaptxdec empty input */
void test_openaptxdec_empty_input() {
    char output[4096];
    size_t output_len;
    int exit_code;

    run_command("./openaptxdec", "", 0, output, sizeof(output), &output_len, &exit_code);

    /* Empty input should return non-zero due to missing stream header */
    assert_test(exit_code != 0 || output_len == 0, "openaptxdec with empty input handles gracefully");
}

/* Test 9: openaptxdec basic decoding */
void test_openaptxdec_basic_decoding() {
    char pcm_input[TEST_PCM_SIZE];
    char aptx_data[TEST_APTX_SIZE * 2];
    char pcm_output[TEST_PCM_SIZE * 2];
    size_t aptx_len, pcm_len;
    int exit_code;

    /* First encode some data */
    memset(pcm_input, 0, sizeof(pcm_input));
    for (size_t i = 0; i < sizeof(pcm_input); i++) {
        pcm_input[i] = i % 256;
    }

    run_command("./openaptxenc", pcm_input, sizeof(pcm_input), aptx_data, sizeof(aptx_data), &aptx_len, &exit_code);

    if (aptx_len > 0 && (exit_code == 0 || exit_code == 1)) {
        /* Now decode it */
        run_command("./openaptxdec", aptx_data, aptx_len, pcm_output, sizeof(pcm_output), &pcm_len, &exit_code);

        assert_test(exit_code == 0, "openaptxdec basic decoding succeeds");
        assert_test(pcm_len > 0, "openaptxdec produces output");
    } else {
        printf("SKIP: openaptxdec basic decoding (encoder failed)\n");
    }
}

/* Test 10: openaptxdec HD mode */
void test_openaptxdec_hd_mode() {
    char pcm_input[TEST_PCM_SIZE];
    char aptx_data[TEST_APTXHD_SIZE * 2];
    char pcm_output[TEST_PCM_SIZE * 2];
    size_t aptx_len, pcm_len;
    int exit_code;

    /* First encode some data in HD mode */
    memset(pcm_input, 0, sizeof(pcm_input));
    for (size_t i = 0; i < sizeof(pcm_input); i++) {
        pcm_input[i] = i % 256;
    }

    run_command("./openaptxenc --hd", pcm_input, sizeof(pcm_input), aptx_data, sizeof(aptx_data), &aptx_len, &exit_code);

    if (aptx_len > 0 && (exit_code == 0 || exit_code == 1)) {
        /* Now decode it with HD mode */
        run_command("./openaptxdec --hd", aptx_data, aptx_len, pcm_output, sizeof(pcm_output), &pcm_len, &exit_code);

        assert_test(exit_code == 0, "openaptxdec --hd decoding succeeds");
        assert_test(pcm_len > 0, "openaptxdec --hd produces output");
    } else {
        printf("SKIP: openaptxdec --hd decoding (encoder failed)\n");
    }
}

/* Test 11: Round-trip consistency */
void test_roundtrip_consistency() {
    char pcm_input[TEST_PCM_SIZE];
    char aptx_data[TEST_APTX_SIZE * 2];
    char pcm_output[TEST_PCM_SIZE * 2];
    size_t aptx_len, pcm_len;
    int exit_code;

    /* Create test PCM data */
    memset(pcm_input, 0, sizeof(pcm_input));
    for (size_t i = 0; i < sizeof(pcm_input); i++) {
        pcm_input[i] = (i * 7) % 256;
    }

    /* Encode */
    run_command("./openaptxenc", pcm_input, sizeof(pcm_input), aptx_data, sizeof(aptx_data), &aptx_len, &exit_code);

    if (aptx_len > 0 && (exit_code == 0 || exit_code == 1)) {
        /* Decode */
        run_command("./openaptxdec", aptx_data, aptx_len, pcm_output, sizeof(pcm_output), &pcm_len, &exit_code);

        if (pcm_len > 0 && exit_code == 0) {
            /* Output should be similar in size (may differ due to padding) */
            assert_test(pcm_len >= sizeof(pcm_input) - 64 && pcm_len <= sizeof(pcm_input) + 64,
                       "Round-trip output size is reasonable");
        } else {
            printf("SKIP: Round-trip consistency (decoder failed)\n");
        }
    } else {
        printf("SKIP: Round-trip consistency (encoder failed)\n");
    }
}

int main() {
    printf("=== CLI Integration Tests (C) ===\n\n");

    /* Change to the directory containing the binaries */
    if (chdir("/workspace/data/tool_projects/orbit/libopenaptx/c") != 0) {
        fprintf(stderr, "Failed to change to test directory\n");
        return 1;
    }

    /* Run encoder tests */
    printf("--- openaptxenc tests ---\n");
    test_openaptxenc_help();
    test_openaptxenc_invalid_option();
    test_openaptxenc_empty_input();
    test_openaptxenc_basic_encoding();
    test_openaptxenc_hd_mode();

    printf("\n--- openaptxdec tests ---\n");
    test_openaptxdec_help();
    test_openaptxdec_invalid_option();
    test_openaptxdec_empty_input();
    test_openaptxdec_basic_decoding();
    test_openaptxdec_hd_mode();

    printf("\n--- Round-trip tests ---\n");
    test_roundtrip_consistency();

    printf("\n=== Summary ===\n");
    printf("Passed: %d/%d\n", test_passed, test_count);

    return (test_passed == test_count) ? 0 : 1;
}
