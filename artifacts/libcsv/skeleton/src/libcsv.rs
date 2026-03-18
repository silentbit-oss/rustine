use crate::*;

pub fn csv_fwrite2(/* FILE *fp, const void *src, size_t src_size, unsigned char quote */) {
	todo!();
}
pub fn helper_csv_write2_1(/* size_t * const src_size_ref, unsigned int * const cdest_idx_ref, unsigned int * const csrc_idx_ref, size_t * const chars_ref, size_t dest_size, unsigned char quote, unsigned char * const cdest, const unsigned char * const csrc */) {
	todo!();
}
pub fn csv_init(/* struct csv_parser *p, unsigned char options */) {
	todo!();
}
pub fn csv_free(/* struct csv_parser *p */) {
	todo!();
}
pub fn csv_error(/* const struct csv_parser *p */) {
	todo!();
}
pub fn csv_strerror(/* int status */) {
	todo!();
}
pub fn csv_write2(/* void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote */) {
	todo!();
}
pub fn csv_write(/* void *dest, size_t dest_size, const void *src, size_t src_size */) {
	todo!();
}
pub fn csv_fwrite(/* FILE *fp, const void *src, size_t src_size */) {
	todo!();
}
pub fn csv_get_opts(/* const struct csv_parser *p */) {
	todo!();
}
pub fn csv_set_opts(/* struct csv_parser *p, unsigned char options */) {
	todo!();
}
pub fn csv_set_delim(/* struct csv_parser *p, unsigned char c */) {
	todo!();
}
pub fn csv_set_quote(/* struct csv_parser *p, unsigned char c */) {
	todo!();
}
pub fn csv_get_delim(/* const struct csv_parser *p */) {
	todo!();
}
pub fn csv_get_quote(/* const struct csv_parser *p */) {
	todo!();
}
pub fn csv_set_space_func(/* struct csv_parser *p, int (*f)(unsigned char) */) {
	todo!();
}
pub fn csv_set_term_func(/* struct csv_parser *p, int (*f)(unsigned char) */) {
	todo!();
}
pub fn csv_set_realloc_func(/* struct csv_parser *p, void *(*f)(void *, size_t) */) {
	todo!();
}
pub fn csv_set_free_func(/* struct csv_parser *p, void (*f)(void *) */) {
	todo!();
}
pub fn csv_set_blk_size(/* struct csv_parser *p, size_t size */) {
	todo!();
}
pub fn csv_get_buffer_size(/* const struct csv_parser *p */) {
	todo!();
}
pub fn csv_increase_buffer(/* struct csv_parser *p */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_2_2(/* int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, int c, int c, int c, unsigned char c, size_t pos */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_3_2(/* int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, int c, int c, int c, unsigned char c, size_t pos */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_3_3(/* int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, int c, int c, int c, unsigned char c, size_t pos */) {
	todo!();
}
pub fn helper_csv_fini_1(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), void * const data, int quoted, size_t spaces */) {
	todo!();
}
pub fn csv_fini(/* struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_1_1(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void * const data, size_t spaces, int quoted */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_2_1(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), int c, int c, void * const data, int c, unsigned char c, int quoted, size_t spaces */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_3_1(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void * const data, int quoted, size_t spaces */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_1_2(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, int c, void * const data, int c, unsigned char c, size_t spaces, int quoted */) {
	todo!();
}
pub fn helper_helper_csv_parse_1_1(/* int * const quoted_ref, int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, void * const data, unsigned char delim, unsigned char quote, int (* const is_space)(unsigned char), int (* const is_term)(unsigned char), int c, unsigned char c, size_t spaces */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_2_3(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, int c, void * const data, int c, unsigned char c, int quoted, size_t spaces */) {
	todo!();
}
pub fn helper_helper_csv_parse_1_2(/* int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, void * const data, unsigned char delim, unsigned char quote, int (* const is_space)(unsigned char), int (* const is_term)(unsigned char), int c, unsigned char c, size_t pos */) {
	todo!();
}
pub fn helper_helper_helper_csv_parse_1_3_4(/* int * const pstate_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, int c, void * const data, int c, unsigned char c, int quoted, size_t spaces */) {
	todo!();
}
pub fn helper_helper_csv_parse_1_3(/* int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), int c, void * const data, unsigned char delim, unsigned char quote, int (* const is_space)(unsigned char), int (* const is_term)(unsigned char), int c, unsigned char c, size_t pos */) {
	todo!();
}
pub fn helper_csv_parse_1(/* int * const c_ref, unsigned char * const c_ref, size_t * const pos_ref, int * const quoted_ref, int * const pstate_ref, size_t * const spaces_ref, size_t * const entry_pos_ref, struct csv_parser * const p, void (* const cb1)(void *, size_t, void *), void (* const cb2)(int c, void *), void * const data, const unsigned char * const us, unsigned char delim, unsigned char quote, int (* const is_space)(unsigned char), int (* const is_term)(unsigned char) */) {
	todo!();
}
pub fn csv_parse(/* struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data */) {
	todo!();
}
