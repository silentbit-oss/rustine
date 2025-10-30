use crate::*;

pub fn json_c_object_sizeof(/* void */) {
	todo!();
}
pub fn json_abort(/* const char *message */) {
	todo!();
}
pub fn json_object_get(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_userdata(/* json_object *jso */) {
	todo!();
}
pub fn json_object_new_null(/* void */) {
	todo!();
}
pub fn lh_get_hash(/* const struct lh_table *t, const void *k */) {
	todo!();
}
pub fn lh_entry_k(/* const struct lh_entry *e */) {
	todo!();
}
pub fn lh_entry_k_is_constant(/* const struct lh_entry *e */) {
	todo!();
}
pub fn lh_entry_v(/* const struct lh_entry *e */) {
	todo!();
}
pub fn lh_entry_set_val(/* struct lh_entry *e, void *newval */) {
	todo!();
}
pub fn lh_entry_next(/* const struct lh_entry *e */) {
	todo!();
}
pub fn lh_entry_prev(/* const struct lh_entry *e */) {
	todo!();
}
pub fn json_object_free_userdata_func(/* struct json_object *jso, void *userdata */) {
	todo!();
}
pub fn json_object_generic_delete(/* struct json_object *jso */) {
	todo!();
}
pub fn JC_OBJECT(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_object_delete(/* struct json_object *jso_base */) {
	todo!();
}
pub fn JC_ARRAY(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_array_delete(/* struct json_object *jso */) {
	todo!();
}
pub fn JC_STRING(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_string_delete(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_put(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_array_entry_free(/* void *data */) {
	todo!();
}
pub fn json_object_array_shrink(/* struct json_object *jso, int empty_slots */) {
	todo!();
}
pub fn json_object_new(/* enum json_type o_type, size_t alloc_size, json_object_to_json_string_fn *to_json_string */) {
	todo!();
}
pub fn json_object_new_int64(/* int64_t i */) {
	todo!();
}
pub fn json_object_new_uint64(/* uint64_t i */) {
	todo!();
}
pub fn JC_DOUBLE(/* struct json_object *jso */) {
	todo!();
}
pub fn helper_json_object_double_to_json_string_format_1(/* unsigned int * const format_idx_ref, unsigned int * const p_idx_ref, unsigned int * const q_idx_ref, int * const size_ref, int flags, const char * const format, struct json_object_double * const jsodbl, char buf[128], char * const p, char * const q */) {
	todo!();
}
pub fn json_object_double_to_json_string_format(/* struct json_object *jso, struct printbuf *pb, int level, int flags, const char *format */) {
	todo!();
}
pub fn json_object_double_to_json_string(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_new_double(/* double d */) {
	todo!();
}
pub fn json_object_set_userdata(/* json_object *jso, void *userdata, json_object_delete_fn *user_delete */) {
	todo!();
}
pub fn json_object_set_serializer(/* json_object *jso, json_object_to_json_string_fn *to_string_func, void *userdata, json_object_delete_fn *user_delete */) {
	todo!();
}
pub fn json_object_new_double_s(/* double d, const char *ds */) {
	todo!();
}
pub fn json_object_get_type(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_object_add_ex(/* struct json_object *jso, const char * const key, struct json_object * const val, const unsigned opts */) {
	todo!();
}
pub fn json_object_object_add(/* struct json_object *jso, const char *key, struct json_object *val */) {
	todo!();
}
pub fn _json_object_new_string(/* const char *s, const size_t len */) {
	todo!();
}
pub fn json_object_new_string_len(/* const char *s, const int len */) {
	todo!();
}
pub fn json_object_lh_entry_free(/* struct lh_entry *ent */) {
	todo!();
}
pub fn json_object_new_object(/* void */) {
	todo!();
}
pub fn json_object_new_array_ext(/* int initial_size */) {
	todo!();
}
pub fn json_object_new_array(/* void */) {
	todo!();
}
pub fn json_object_array_add(/* struct json_object *jso, struct json_object *val */) {
	todo!();
}
pub fn json_object_new_boolean(/* json_bool b */) {
	todo!();
}
pub fn JC_ARRAY_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_array_length(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_array_get_idx(/* const struct json_object *jso, size_t idx */) {
	todo!();
}
pub fn lh_table_head(/* const lh_table *t */) {
	todo!();
}
pub fn JC_OBJECT_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_object(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_to_json_string_length(/* struct json_object *jso, int flags, size_t *length */) {
	todo!();
}
pub fn json_object_to_json_string_ext(/* struct json_object *jso, int flags */) {
	todo!();
}
pub fn json_object_to_json_string(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_is_type(/* const struct json_object *jso, enum json_type type */) {
	todo!();
}
pub fn json_object_object_get_ex(/* const struct json_object *jso, const char *key, struct json_object **value */) {
	todo!();
}
pub fn json_object_object_get(/* const struct json_object *jso, const char *key */) {
	todo!();
}
pub fn json_object_new_int(/* int32_t i */) {
	todo!();
}
pub fn JC_INT(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_set_int64(/* struct json_object *jso, int64_t new_value */) {
	todo!();
}
pub fn json_object_set_int(/* struct json_object *jso, int new_value */) {
	todo!();
}
pub fn json_object_set_uint64(/* struct json_object *jso, uint64_t new_value */) {
	todo!();
}
pub fn json_object_new_string(/* const char *s */) {
	todo!();
}
pub fn JC_STRING_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn get_string_component_mutable(/* struct json_object *jso */) {
	todo!();
}
pub fn _json_object_set_string_len(/* json_object *jso, const char *s, size_t len */) {
	todo!();
}
pub fn json_object_set_string(/* json_object *jso, const char *s */) {
	todo!();
}
pub fn json_object_set_string_len(/* json_object *jso, const char *s, int len */) {
	todo!();
}
pub fn JC_BOOL(/* struct json_object *jso */) {
	todo!();
}
pub fn JC_BOOL_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn JC_DOUBLE_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn JC_INT_C(/* const struct json_object *jso */) {
	todo!();
}
pub fn get_string_component(/* const struct json_object *jso */) {
	todo!();
}
pub fn indent(/* struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn _json_object_get_string_len(/* const struct json_object_string *jso */) {
	todo!();
}
pub fn helper_json_object_get_int_1(/* double * const cdouble_ref, const struct json_object * const jso */) {
	todo!();
}
pub fn helper_helper_json_escape_str_1_2(/* size_t * const pos_ref, size_t * const start_offset_ref, struct printbuf * const pb, const char * const str, int flags, unsigned char c */) {
	todo!();
}
pub fn json_object_array_put_idx(/* struct json_object *jso, size_t idx, struct json_object *val */) {
	todo!();
}
pub fn json_object_get_int(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_array(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_set_boolean(/* struct json_object *jso, json_bool new_value */) {
	todo!();
}
pub fn json_c_set_serialization_double_format(/* const char *double_format, int global_or_thread */) {
	todo!();
}
pub fn json_object_get_string(/* struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_string_len(/* const struct json_object *jso */) {
	todo!();
}
pub fn helper_helper_json_escape_str_1_1(/* size_t * const pos_ref, size_t * const start_offset_ref, struct printbuf * const pb, const char * const str, unsigned char c */) {
	todo!();
}
pub fn helper_json_escape_str_1(/* size_t * const len_ref, size_t * const pos_ref, size_t * const start_offset_ref, unsigned char * const c_ref, struct printbuf * const pb, const char * const str, int flags */) {
	todo!();
}
pub fn json_escape_str(/* struct printbuf *pb, const char *str, size_t len, int flags */) {
	todo!();
}
pub fn json_object_double_to_json_string_default_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn _json_object_userdata_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_userdata_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_copy_serializer_data(/* struct json_object *src, struct json_object *dst */) {
	todo!();
}
pub fn json_object_deep_copy(/* struct json_object *src, struct json_object **dst, json_c_shallow_copy_fn *shallow_copy */) {
	todo!();
}
pub fn json_object_array_insert_idx(/* struct json_object *jso, size_t idx, struct json_object *val */) {
	todo!();
}
pub fn json_object_array_del_idx(/* struct json_object *jso, size_t idx, size_t count */) {
	todo!();
}
pub fn json_object_object_del(/* struct json_object *jso, const char *key */) {
	todo!();
}
pub fn json_object_object_length(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_array_sort(/* struct json_object *jso, int (*sort_fn)(const void *, const void *) */) {
	todo!();
}
pub fn json_object_array_bsearch(/* const struct json_object *key, const struct json_object *jso, int (*sort_fn)(const void *, const void *) */) {
	todo!();
}
pub fn json_object_int_inc(/* struct json_object *jso, int64_t val */) {
	todo!();
}
pub fn json_object_set_double(/* struct json_object *jso, double new_value */) {
	todo!();
}
pub fn json_object_boolean_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_int_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_get_boolean(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_double(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_string_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_object_array_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn helper_json_object_object_to_json_string_1(/* int * const had_children_ref, struct printbuf * const pb, int level, int flags, struct json_object_iter iter */) {
	todo!();
}
pub fn json_object_get_uint64(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_get_int64(/* const struct json_object *jso */) {
	todo!();
}
pub fn json_object_object_to_json_string_func(/* struct json_object *jso, struct printbuf *pb, int level, int flags */) {
	todo!();
}
pub fn json_c_shallow_copy_default_func(/* json_object *src, json_object *parent, const char *key, size_t index, json_object **dst */) {
	todo!();
}
