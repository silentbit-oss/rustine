/*
 * Generated test file for print_char_func function
 * Tests the character printing functionality of avl_data
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "avl_data.h"

// Helper function to capture stdout output
char captured_output[1024];
int capture_pos = 0;

void reset_capture() {
    memset(captured_output, 0, sizeof(captured_output));
    capture_pos = 0;
}

void capture_char(char c) {
    if (capture_pos < sizeof(captured_output) - 1) {
        captured_output[capture_pos++] = c;
        captured_output[capture_pos] = '\0';
    }
}

// Custom print_char_func that captures output for testing
void test_print_char_func(void *d) {
    mydata *p;

    assert(d != NULL);

    p = (mydata *) d;
    char c = (char)(p->key & 127);
    capture_char(c);
}

// Test case structure
typedef struct {
    int key;
    char expected_char;
    const char *description;
} test_case_t;

// Test basic printable ASCII characters
void test_uppercase_letters() {
    printf("Test: Uppercase letters... ");

    test_case_t cases[] = {
        {65, 'A', "Letter A"},
        {90, 'Z', "Letter Z"},
        {77, 'M', "Letter M"}
    };

    for (int i = 0; i < 3; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected '%c', got '%c'\n",
                   cases[i].description, cases[i].expected_char, captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

// Test lowercase letters
void test_lowercase_letters() {
    printf("Test: Lowercase letters... ");

    test_case_t cases[] = {
        {97, 'a', "Letter a"},
        {122, 'z', "Letter z"},
        {109, 'm', "Letter m"}
    };

    for (int i = 0; i < 3; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected '%c', got '%c'\n",
                   cases[i].description, cases[i].expected_char, captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

// Test digits
void test_digits() {
    printf("Test: Digit characters... ");

    test_case_t cases[] = {
        {48, '0', "Digit 0"},
        {57, '9', "Digit 9"},
        {53, '5', "Digit 5"}
    };

    for (int i = 0; i < 3; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected '%c', got '%c'\n",
                   cases[i].description, cases[i].expected_char, captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

// Test special characters
void test_special_characters() {
    printf("Test: Special characters... ");

    test_case_t cases[] = {
        {32, ' ', "Space"},
        {33, '!', "Exclamation"},
        {64, '@', "At symbol"},
        {126, '~', "Tilde"}
    };

    for (int i = 0; i < 4; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected '%c', got '%c'\n",
                   cases[i].description, cases[i].expected_char, captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

// Test masking behavior (key & 127)
void test_masking_behavior() {
    printf("Test: Masking behavior (key & 127)... ");

    test_case_t cases[] = {
        {128, '\0', "128 masked to 0"},
        {129, '\x01', "129 masked to 1"},
        {193, 'A', "193 masked to 65 (A)"},
        {255, '\x7f', "255 masked to 127"}
    };

    for (int i = 0; i < 4; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected 0x%02x, got 0x%02x\n",
                   cases[i].description, (unsigned char)cases[i].expected_char,
                   (unsigned char)captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

// Test edge cases
void test_edge_cases() {
    printf("Test: Edge cases... ");

    test_case_t cases[] = {
        {0, '\0', "Null character"},
        {127, '\x7f', "DEL character (127)"},
        {1, '\x01', "SOH character"}
    };

    for (int i = 0; i < 3; i++) {
        reset_capture();
        mydata *data = makedata(cases[i].key);
        test_print_char_func(data);

        if (captured_output[0] != cases[i].expected_char) {
            printf("FAILED: %s - Expected 0x%02x, got 0x%02x\n",
                   cases[i].description, (unsigned char)cases[i].expected_char,
                   (unsigned char)captured_output[0]);
            destroy_func(data);
            exit(1);
        }
        destroy_func(data);
    }

    printf("PASSED\n");
}

int main() {
    printf("=== Testing print_char_func ===\n\n");

    test_uppercase_letters();
    test_lowercase_letters();
    test_digits();
    test_special_characters();
    test_masking_behavior();
    test_edge_cases();

    printf("\n=== All tests PASSED ===\n");
    return 0;
}
