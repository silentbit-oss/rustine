# Function-to-Test Coverage Map

This document maps each library function to the tests that exercise it.

## Summary
- Total functions: 52
- Covered functions: 52
- Uncovered functions: 0
- Coverage percentage: 100.0%

## Covered Functions

| Function | Source File | Tested In | Test Names |
|----------|-------------|-----------|------------|
| libzahl_realloc | allocator.c | generated | Generated: allocatorTest_generated.rs |
| zabs | zabs.c | test.c, test.rs | C: test_3 <br> Rust: test_11, test_3 |
| zadd | zadd.c | test.c, test.rs | C: test_2, test_4 <br> Rust: test_11, test_12, test_13 ... |
| zadd_unsigned | zadd.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_4 |
| zand | zand.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_5 |
| zbits | zbits.c | test.c, test.rs | C: test_1 <br> Rust: test_1, test_11 |
| zbset | zbset.c | test.c, test.rs | C: test_1 <br> Rust: test_1, test_11 |
| zbtest | zbtest.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_6 |
| zcmp | zcmp.c | test.c, test.rs | C: test_1, test_2, test_3 ... <br> Rust: test_1, test_11, test_12 ... |
| zcmpi | zcmpi.c | test.c, test.rs | C: test_2, test_4 <br> Rust: test_11, test_2, test_4 ... |
| zcmpmag | zcmpmag.c | test.c, test.rs | C: test_2, test_3, test_4 <br> Rust: test_11, test_2, test_3 ... |
| zcmpu | zcmpu.c | test.c, test.rs | C: test_2, test_4 <br> Rust: test_11, test_12, test_2 |
| zdiv | zdiv.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_12 ... |
| zdivmod | zdivmod.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_7 |
| zerror | zerror.c | generated | Generated: zerrorTest_generated.rs |
| zfree | zfree.c | test.c | C: test_1, test_2, test_3 ... |
| zgcd | zgcd.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_7 |
| zload | zload.c | test.c, test.rs | C: test_1 <br> Rust: test_1, test_11 |
| zlsb | zlsb.c | test.c, test.rs | C: test_1 <br> Rust: test_1, test_11 |
| zlsh | zlsh.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_6 |
| zmod | zmod.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_7 |
| zmodmul | zmodmul.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_7 |
| zmodpow | zmodpow.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_8 |
| zmodpowu | zmodpowu.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_12 ... |
| zmodsqr | zmodsqr.c | test.rs, generated | Rust: test_11 <br> Generated: zmodsqrTest_generated.rs |
| zmul | zmul.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_7 |
| zneg | zneg.c | test.c, test.rs | C: test_1, test_2, test_4 <br> Rust: test_1, test_10, test_11 ... |
| znot | znot.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_6 |
| zor | zor.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_5 |
| zperror | zperror.c | test.c | C: test_1, test_2, test_3 ... |
| zpow | zpow.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_8 |
| zpowu | zpowu.c | test.c, test.rs | C: test_4 <br> Rust: test_10, test_11, test_12 ... |
| zptest | zptest.c | test.c, test.rs | C: test_4 <br> Rust: test_9 |
| zrand | zrand.c | test.c, test.rs | C: test_4 <br> Rust: test_9 |
| zrand_get_random_bits | zrand.c | generated | Generated: zrandTest_generated.rs |
| zrsh | zrsh.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_6 |
| zsave | zsave.c | test.c, test.rs | C: test_1 <br> Rust: test_1, test_11 |
| zset | zset.c | test.c, test.rs | C: test_2, test_4 <br> Rust: test_11, test_2, test_6 |
| zseti | zseti.c | test.c, test.rs | C: test_3, test_4 <br> Rust: test_11, test_13, test_3 ... |
| zsets | zsets.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_13 ... |
| zsetu | zsetu.c | test.c, test.rs | C: test_1, test_2, test_3 ... <br> Rust: test_1, test_10, test_11 ... |
| zsetup | zsetup.c | test.c | C: test_1, test_2, test_3 ... |
| zsplit | zsplit.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_6 |
| zsqr | zsqr.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_13 ... |
| zstr | zstr.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_13, test_9 |
| zstr_length | zstr_length.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_9 |
| zsub | zsub.c | test.c, test.rs | C: test_3, test_4 <br> Rust: test_11, test_12, test_3 ... |
| zsub_unsigned | zsub.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_4 |
| zswap | zswap.c | test.c, test.rs | C: test_1 <br> Rust: test_1 |
| ztrunc | ztrunc.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_6 |
| zunsetup | zunsetup.c | test.c | C: test_1, test_2, test_3 ... |
| zxor | zxor.c | test.c, test.rs | C: test_4 <br> Rust: test_11, test_12, test_5 |

## Uncovered Functions

**All functions are covered by tests!**
