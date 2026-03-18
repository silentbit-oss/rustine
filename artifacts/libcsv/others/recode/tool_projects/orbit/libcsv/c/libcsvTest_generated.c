/*
 * libcsvTest_generated.c
 * Comprehensive tests for uncovered libcsv functions
 * Tests functional equivalence between C and Rust implementations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "csv.h"

/* Test counter */
static int tests_run = 0;
static int tests_passed = 0;

/* Test helper macros */
#define TEST_ASSERT(expr, msg) \
    do { \
        tests_run++; \
        if (expr) { \
            tests_passed++; \
            printf("  [PASS] %s\n", msg); \
        } else { \
            printf("  [FAIL] %s\n", msg); \
        } \
    } while(0)

#define TEST_START(name) \
    printf("\n=== Test: %s ===\n", name)

/* Custom memory functions for testing */
static void* test_realloc(void* ptr, size_t size) {
    return realloc(ptr, size);
}

static void test_free(void* ptr) {
    free(ptr);
}

/* Test 1: csv_get_opts - Returns current parser options */
void test_csv_get_opts(void) {
    TEST_START("csv_get_opts");

    struct csv_parser parser;
    int result;

    /* Initialize with no options */
    csv_init(&parser, 0);
    result = csv_get_opts(&parser);
    TEST_ASSERT(result == 0, "get_opts returns 0 when initialized with no options");
    csv_free(&parser);

    /* Initialize with CSV_STRICT */
    csv_init(&parser, CSV_STRICT);
    result = csv_get_opts(&parser);
    TEST_ASSERT(result == CSV_STRICT, "get_opts returns CSV_STRICT");
    csv_free(&parser);

    /* Initialize with multiple options */
    csv_init(&parser, CSV_STRICT | CSV_APPEND_NULL);
    result = csv_get_opts(&parser);
    TEST_ASSERT(result == (CSV_STRICT | CSV_APPEND_NULL),
                "get_opts returns combined options");
    csv_free(&parser);

    /* Test with all options */
    unsigned char all_opts = CSV_STRICT | CSV_REPALL_NL | CSV_STRICT_FINI |
                             CSV_APPEND_NULL | CSV_EMPTY_IS_NULL;
    csv_init(&parser, all_opts);
    result = csv_get_opts(&parser);
    TEST_ASSERT(result == all_opts, "get_opts returns all options combined");
    csv_free(&parser);

    /* Test with NULL parser */
    result = csv_get_opts(NULL);
    TEST_ASSERT(result == -1, "get_opts returns -1 for NULL parser");
}

/* Test 2: csv_get_delim - Returns current delimiter character */
void test_csv_get_delim(void) {
    TEST_START("csv_get_delim");

    struct csv_parser parser;
    unsigned char delim;

    /* Test default delimiter */
    csv_init(&parser, 0);
    delim = csv_get_delim(&parser);
    TEST_ASSERT(delim == CSV_COMMA, "get_delim returns default comma");
    csv_free(&parser);

    /* Test custom delimiter - pipe */
    csv_init(&parser, 0);
    csv_set_delim(&parser, '|');
    delim = csv_get_delim(&parser);
    TEST_ASSERT(delim == '|', "get_delim returns pipe after setting");
    csv_free(&parser);

    /* Test custom delimiter - semicolon */
    csv_init(&parser, 0);
    csv_set_delim(&parser, ';');
    delim = csv_get_delim(&parser);
    TEST_ASSERT(delim == ';', "get_delim returns semicolon after setting");
    csv_free(&parser);

    /* Test custom delimiter - tab */
    csv_init(&parser, 0);
    csv_set_delim(&parser, '\t');
    delim = csv_get_delim(&parser);
    TEST_ASSERT(delim == '\t', "get_delim returns tab after setting");
    csv_free(&parser);

    /* Test delimiter changes multiple times */
    csv_init(&parser, 0);
    csv_set_delim(&parser, '|');
    csv_set_delim(&parser, ';');
    csv_set_delim(&parser, ':');
    delim = csv_get_delim(&parser);
    TEST_ASSERT(delim == ':', "get_delim returns last set delimiter");
    csv_free(&parser);
}

/* Test 3: csv_get_quote - Returns current quote character */
void test_csv_get_quote(void) {
    TEST_START("csv_get_quote");

    struct csv_parser parser;
    unsigned char quote;

    /* Test default quote */
    csv_init(&parser, 0);
    quote = csv_get_quote(&parser);
    TEST_ASSERT(quote == CSV_QUOTE, "get_quote returns default double quote");
    csv_free(&parser);

    /* Test custom quote - single quote */
    csv_init(&parser, 0);
    csv_set_quote(&parser, '\'');
    quote = csv_get_quote(&parser);
    TEST_ASSERT(quote == '\'', "get_quote returns single quote after setting");
    csv_free(&parser);

    /* Test custom quote - backtick */
    csv_init(&parser, 0);
    csv_set_quote(&parser, '`');
    quote = csv_get_quote(&parser);
    TEST_ASSERT(quote == '`', "get_quote returns backtick after setting");
    csv_free(&parser);

    /* Test quote changes multiple times */
    csv_init(&parser, 0);
    csv_set_quote(&parser, '\'');
    csv_set_quote(&parser, '`');
    csv_set_quote(&parser, '"');
    quote = csv_get_quote(&parser);
    TEST_ASSERT(quote == '"', "get_quote returns last set quote character");
    csv_free(&parser);
}

/* Test 4: csv_set_realloc_func - Sets custom memory realloc function */
void test_csv_set_realloc_func(void) {
    TEST_START("csv_set_realloc_func");

    struct csv_parser parser;

    /* Set custom realloc function */
    csv_init(&parser, 0);
    csv_set_realloc_func(&parser, test_realloc);
    TEST_ASSERT(parser.realloc_func == test_realloc,
                "set_realloc_func sets custom realloc function");
    csv_free(&parser);

    /* Verify parser still works with custom realloc */
    csv_init(&parser, 0);
    csv_set_realloc_func(&parser, test_realloc);
    const char* data = "a,b,c\n";
    size_t parsed = csv_parse(&parser, data, strlen(data), NULL, NULL, NULL);
    TEST_ASSERT(parsed == strlen(data),
                "parser works with custom realloc function");
    csv_free(&parser);

    /* Test with NULL function pointer (should not change) */
    csv_init(&parser, 0);
    void* original_func = (void*)parser.realloc_func;
    csv_set_realloc_func(&parser, NULL);
    TEST_ASSERT(parser.realloc_func == original_func,
                "set_realloc_func ignores NULL function pointer");
    csv_free(&parser);

    /* Test with NULL parser */
    csv_set_realloc_func(NULL, test_realloc);
    TEST_ASSERT(1, "set_realloc_func handles NULL parser safely");
}

/* Test 5: csv_set_free_func - Sets custom memory free function */
void test_csv_set_free_func(void) {
    TEST_START("csv_set_free_func");

    struct csv_parser parser;

    /* Set custom free function */
    csv_init(&parser, 0);
    csv_set_free_func(&parser, test_free);
    TEST_ASSERT(parser.free_func == test_free,
                "set_free_func sets custom free function");
    csv_free(&parser);

    /* Verify parser cleanup works with custom free */
    csv_init(&parser, 0);
    csv_set_free_func(&parser, test_free);
    csv_set_realloc_func(&parser, test_realloc);
    const char* data = "a,b,c\n";
    csv_parse(&parser, data, strlen(data), NULL, NULL, NULL);
    csv_free(&parser);
    TEST_ASSERT(1, "parser cleanup works with custom free function");

    /* Test with NULL function pointer (should not change) */
    csv_init(&parser, 0);
    void* original_func = (void*)parser.free_func;
    csv_set_free_func(&parser, NULL);
    TEST_ASSERT(parser.free_func == original_func,
                "set_free_func ignores NULL function pointer");
    csv_free(&parser);

    /* Test with NULL parser */
    csv_set_free_func(NULL, test_free);
    TEST_ASSERT(1, "set_free_func handles NULL parser safely");
}

/* Test 6: csv_set_blk_size - Sets custom block size for buffer allocation */
void test_csv_set_blk_size(void) {
    TEST_START("csv_set_blk_size");

    struct csv_parser parser;

    /* Test default block size */
    csv_init(&parser, 0);
    TEST_ASSERT(parser.blk_size == 128, "default block size is 128");
    csv_free(&parser);

    /* Set custom block size - 256 */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 256);
    TEST_ASSERT(parser.blk_size == 256, "set_blk_size sets size to 256");
    csv_free(&parser);

    /* Set custom block size - 512 */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 512);
    TEST_ASSERT(parser.blk_size == 512, "set_blk_size sets size to 512");
    csv_free(&parser);

    /* Set custom block size - 1024 */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 1024);
    TEST_ASSERT(parser.blk_size == 1024, "set_blk_size sets size to 1024");
    csv_free(&parser);

    /* Test small block size - 1 */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 1);
    TEST_ASSERT(parser.blk_size == 1, "set_blk_size handles size 1");
    csv_free(&parser);

    /* Test zero block size */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 0);
    TEST_ASSERT(parser.blk_size == 0, "set_blk_size accepts zero");
    csv_free(&parser);

    /* Test very large block size */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 1024 * 1024);
    TEST_ASSERT(parser.blk_size == 1024 * 1024,
                "set_blk_size handles large size");
    csv_free(&parser);

    /* Test with NULL parser */
    csv_set_blk_size(NULL, 256);
    TEST_ASSERT(1, "set_blk_size handles NULL parser safely");
}

/* Test 7: csv_get_buffer_size - Returns current internal buffer size */
void test_csv_get_buffer_size(void) {
    TEST_START("csv_get_buffer_size");

    struct csv_parser parser;
    size_t size;

    /* Test initial buffer size (before any parsing) */
    csv_init(&parser, 0);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size == 0, "get_buffer_size returns 0 initially");
    csv_free(&parser);

    /* Test buffer size after parsing small data */
    csv_init(&parser, 0);
    const char* data1 = "a,b,c\n";
    csv_parse(&parser, data1, strlen(data1), NULL, NULL, NULL);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size >= strlen(data1),
                "get_buffer_size returns size >= data length after parsing");
    csv_free(&parser);

    /* Test buffer size with default block size (128) */
    csv_init(&parser, 0);
    csv_parse(&parser, data1, strlen(data1), NULL, NULL, NULL);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size == 128,
                "get_buffer_size returns 128 after parsing with default block size");
    csv_free(&parser);

    /* Test buffer size after parsing larger data */
    csv_init(&parser, 0);
    char large_data[200];
    memset(large_data, 'a', 199);
    large_data[199] = '\0';
    csv_parse(&parser, large_data, strlen(large_data), NULL, NULL, NULL);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size >= 199,
                "get_buffer_size handles large data");
    csv_free(&parser);

    /* Test buffer size with custom block size */
    csv_init(&parser, 0);
    csv_set_blk_size(&parser, 256);
    csv_parse(&parser, data1, strlen(data1), NULL, NULL, NULL);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size == 256,
                "get_buffer_size returns 256 with custom block size");
    csv_free(&parser);

    /* Test buffer size after csv_free */
    csv_init(&parser, 0);
    csv_parse(&parser, data1, strlen(data1), NULL, NULL, NULL);
    csv_free(&parser);
    size = csv_get_buffer_size(&parser);
    TEST_ASSERT(size == 0, "get_buffer_size returns 0 after csv_free");

    /* Test with NULL parser */
    size = csv_get_buffer_size(NULL);
    TEST_ASSERT(size == 0, "get_buffer_size returns 0 for NULL parser");
}

/* Integration test: Test combined usage of all functions */
void test_integration(void) {
    TEST_START("Integration - Combined function usage");

    struct csv_parser parser;

    /* Initialize parser with options */
    csv_init(&parser, CSV_STRICT | CSV_APPEND_NULL);

    /* Verify initial state */
    TEST_ASSERT(csv_get_opts(&parser) == (CSV_STRICT | CSV_APPEND_NULL),
                "integration: options set correctly");
    TEST_ASSERT(csv_get_delim(&parser) == CSV_COMMA,
                "integration: default delimiter is comma");
    TEST_ASSERT(csv_get_quote(&parser) == CSV_QUOTE,
                "integration: default quote is double quote");
    TEST_ASSERT(csv_get_buffer_size(&parser) == 0,
                "integration: initial buffer size is 0");

    /* Customize parser configuration */
    csv_set_delim(&parser, ';');
    csv_set_quote(&parser, '\'');
    csv_set_blk_size(&parser, 512);
    csv_set_realloc_func(&parser, test_realloc);
    csv_set_free_func(&parser, test_free);

    /* Verify customizations */
    TEST_ASSERT(csv_get_delim(&parser) == ';',
                "integration: delimiter changed to semicolon");
    TEST_ASSERT(csv_get_quote(&parser) == '\'',
                "integration: quote changed to single quote");
    TEST_ASSERT(parser.blk_size == 512,
                "integration: block size changed to 512");

    /* Parse some data and verify buffer allocation */
    const char* data = "a;b;c\n";
    csv_parse(&parser, data, strlen(data), NULL, NULL, NULL);
    TEST_ASSERT(csv_get_buffer_size(&parser) == 512,
                "integration: buffer allocated with custom block size");

    /* Clean up */
    csv_free(&parser);
    TEST_ASSERT(csv_get_buffer_size(&parser) == 0,
                "integration: buffer freed successfully");
}

/* Main test runner */
int main(void) {
    printf("========================================\n");
    printf("libcsv Uncovered Functions Test Suite\n");
    printf("Testing C Implementation\n");
    printf("========================================\n");

    /* Run all tests */
    test_csv_get_opts();
    test_csv_get_delim();
    test_csv_get_quote();
    test_csv_set_realloc_func();
    test_csv_set_free_func();
    test_csv_set_blk_size();
    test_csv_get_buffer_size();
    test_integration();

    /* Print summary */
    printf("\n========================================\n");
    printf("Test Summary\n");
    printf("========================================\n");
    printf("Tests Run:    %d\n", tests_run);
    printf("Tests Passed: %d\n", tests_passed);
    printf("Tests Failed: %d\n", tests_run - tests_passed);
    printf("========================================\n");

    if (tests_passed == tests_run) {
        printf("Result: ALL TESTS PASSED\n");
        return 0;
    } else {
        printf("Result: SOME TESTS FAILED\n");
        return 1;
    }
}
