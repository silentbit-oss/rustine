# C Functions and Methods to Translate

## Source Files

### c/libtree.c
c/libtree.c:utoa
c/libtree.c:small_vec_u64_init
c/libtree.c:small_vec_u64_append
c/libtree.c:small_vec_u64_free
c/libtree.c:host_is_little_endian
c/libtree.c:is_ascending_order
c/libtree.c:string_table_maybe_grow
c/libtree.c:string_table_store
c/libtree.c:string_table_copy_from_file
c/libtree.c:is_in_exclude_list
c/libtree.c:tree_preamble
c/libtree.c:apply_exclude_list
c/libtree.c:check_absolute_paths
c/libtree.c:check_search_paths
c/libtree.c:interpolate_variables
c/libtree.c:print_colon_delimited_paths
c/libtree.c:print_line
c/libtree.c:print_error
c/libtree.c:visited_files_contains
c/libtree.c:visited_files_append
c/libtree.c:recurse
c/libtree.c:ld_conf_globbing
c/libtree.c:parse_ld_config_file
c/libtree.c:parse_ld_so_conf
c/libtree.c:parse_ld_library_path
c/libtree.c:set_default_paths
c/libtree.c:libtree_state_init
c/libtree.c:libtree_state_free
c/libtree.c:print_tree

## Test Files

### c/tests/test.c
c/tests/test.c:create_test_elf_file
c/tests/test.c:create_test_config_file
c/tests/test.c:create_elf_with_program_headers
c/tests/test.c:main

### c/tests/06_symbol_versions/main.c
c/tests/06_symbol_versions/main.c:main

### c/tests/06_symbol_versions/v1.c
c/tests/06_symbol_versions/v1.c:xyz

### c/tests/06_symbol_versions/v2.c
c/tests/06_symbol_versions/v2.c:xyz_old
c/tests/06_symbol_versions/v2.c:xyz_new
