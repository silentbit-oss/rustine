# C Functions and Methods to Translate

## Core Library Functions (libcsv.c)

libcsv.c:csv_error
libcsv.c:csv_get_opts
libcsv.c:csv_set_opts
libcsv.c:csv_init
libcsv.c:csv_free
libcsv.c:csv_fini
libcsv.c:csv_set_delim
libcsv.c:csv_set_quote
libcsv.c:csv_get_delim
libcsv.c:csv_get_quote
libcsv.c:csv_set_space_func
libcsv.c:csv_set_term_func
libcsv.c:csv_set_realloc_func
libcsv.c:csv_set_free_func
libcsv.c:csv_set_blk_size
libcsv.c:csv_get_buffer_size
libcsv.c:csv_increase_buffer
libcsv.c:csv_parse
libcsv.c:csv_write
libcsv.c:csv_fwrite
libcsv.c:csv_write2
libcsv.c:csv_fwrite2

## Test Functions (test_csv.c)

test_csv.c:fail_parser
test_csv.c:fail_writer
test_csv.c:cb1
test_csv.c:cb2
test_csv.c:test_parser
test_csv.c:test_writer
test_csv.c:test_writer2
test_csv.c:main

## Example Functions

examples/csvfix.c:cb1
examples/csvfix.c:cb2
examples/csvfix.c:main
examples/csvinfo.c:cb1
examples/csvinfo.c:cb2
examples/csvinfo.c:is_space
examples/csvinfo.c:is_term
examples/csvinfo.c:main
examples/csvtest.c:cb1
examples/csvtest.c:cb2
examples/csvtest.c:main
examples/csvvalid.c:main
