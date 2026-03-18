use crate::*;

// typedef struct binn_struct binn

pub fn binn_version() {
	todo!();
}
pub fn binn_create_type(/* int storage_type, int data_type_index */) {
	todo!();
}
pub fn binn_is_struct(/* void *ptr */) {
	todo!();
}
pub fn strlen2(/* char *str */) {
	todo!();
}
pub fn binn_get_ptr_type(/* void *ptr */) {
	todo!();
}
pub fn CalcAllocation(/* int needed_size, int alloc_size */) {
	todo!();
}
pub fn type_family(/* int type */) {
	todo!();
}
pub fn GetWriteConvertedData(/* int *ptype, void **ppvalue, int *psize */) {
	todo!();
}
pub fn int_type(/* int type */) {
	todo!();
}
pub fn copy_raw_value(/* void *psource, void *pdest, int data_store */) {
	todo!();
}
pub fn copy_float_value(/* void *psource, void *pdest, int source_type, int dest_type */) {
	todo!();
}
pub fn helper_read_map_id_1(/* unsigned int * const p_idx_ref, int * const id_ref, unsigned char * const p, unsigned char c */) {
	todo!();
}
pub fn helper_binn_map_set_raw_1(/* unsigned int * const p_idx_ref, int id, unsigned char * const p, unsigned char sign */) {
	todo!();
}
pub fn helper_helper_binn_read_pair_1_1(/* unsigned int * const p_idx_ref, unsigned int * const key_idx_ref, unsigned char * const len_ref, unsigned char * const p, unsigned char * const plimit, unsigned int plimit_idx */) {
	todo!();
}
pub fn binn_get_type_info(/* int long_type, int *pstorage_type, int *pextra_type */) {
	todo!();
}
pub fn check_alloc_functions() {
	todo!();
}
pub fn binn_malloc(/* int size */) {
	todo!();
}
pub fn binn_alloc_item() {
	todo!();
}
pub fn binn_memdup(/* void *src, int size */) {
	todo!();
}
pub fn binn_value(/* int type, void *pvalue, int size, binn_mem_free freefn */) {
	todo!();
}
pub fn copy_be32(/* u32 *pdest, u32 *psource */) {
	todo!();
}
pub fn IsValidBinnHeader(/* void *pbuf, int *ptype, int *pcount, int *psize, int *pheadersize */) {
	todo!();
}
pub fn binn_save_header(/* binn *item */) {
	todo!();
}
pub fn binn_ptr(/* void *ptr */) {
	todo!();
}
pub fn copy_be64(/* u64 *pdest, u64 *psource */) {
	todo!();
}
pub fn helper_GetValue_1(/* unsigned int * const p_idx_ref, int * const DataSize_ref, unsigned char * const p, binn * const value */) {
	todo!();
}
pub fn copy_be16(/* u16 *pdest, u16 *psource */) {
	todo!();
}
pub fn GetValue(/* unsigned char *p, binn *value */) {
	todo!();
}
pub fn helper_AdvanceDataPos_1(/* unsigned int * const p_idx_ref, int * const DataSize_ref, unsigned char * const p, unsigned char * const plimit */) {
	todo!();
}
pub fn helper_AdvanceDataPos_2(/* unsigned int * const p_idx_ref, int * const DataSize_ref, unsigned char * const p, unsigned char * const plimit, int storage_type */) {
	todo!();
}
pub fn AdvanceDataPos(/* unsigned char *p, unsigned char *plimit */) {
	todo!();
}
pub fn binn_list_get_value(/* void *ptr, int pos, binn *value */) {
	todo!();
}
pub fn copy_int_value(/* void *psource, void *pdest, int source_type, int dest_type */) {
	todo!();
}
pub fn copy_value(/* void *psource, void *pdest, int source_type, int dest_type, int data_store */) {
	todo!();
}
pub fn binn_get_read_storage(/* int type */) {
	todo!();
}
pub fn zero_value(/* void *pvalue, int type */) {
	todo!();
}
pub fn binn_list_get(/* void *ptr, int pos, int type, void *pvalue, int *psize */) {
	todo!();
}
pub fn read_map_id(/* unsigned char **pp, unsigned char *plimit */) {
	todo!();
}
pub fn SearchForID(/* unsigned char *p, int header_size, int size, int numitems, int id */) {
	todo!();
}
pub fn binn_map_get_value(/* void *ptr, int id, binn *value */) {
	todo!();
}
pub fn binn_map_get(/* void *ptr, int id, int type, void *pvalue, int *psize */) {
	todo!();
}
pub fn helper_SearchForKey_1(/* unsigned int * const p_idx_ref, unsigned char * const len_ref, unsigned char * const p, const char * const key, unsigned char * const plimit, unsigned int plimit_idx, unsigned char * const base, unsigned int base_idx, int keylen */) {
	todo!();
}
pub fn SearchForKey(/* unsigned char *p, int header_size, int size, int numitems, const char *key */) {
	todo!();
}
pub fn binn_object_get_value(/* void *ptr, const char *key, binn *value */) {
	todo!();
}
pub fn binn_object_get(/* void *ptr, const char *key, int type, void *pvalue, int *psize */) {
	todo!();
}
pub fn helper_binn_is_valid_ex_1(/* unsigned int * const p_idx_ref, unsigned char * const len_ref, int type, unsigned char * const p, unsigned char * const plimit, unsigned char * const base, unsigned int base_idx */) {
	todo!();
}
pub fn binn_is_valid_ex(/* void *ptr, int *ptype, int *pcount, int *psize */) {
	todo!();
}
pub fn atoi64(/* char *str */) {
	todo!();
}
pub fn binn_get_write_storage(/* int type */) {
	todo!();
}
pub fn binn_is_container(/* binn *item */) {
	todo!();
}
pub fn helper_binn_create_1(/* int * const size_ref, unsigned int * const pointer_idx_ref, binn * const item, void * const pointer */) {
	todo!();
}
pub fn binn_create(/* binn *item, int type, int size, void *pointer */) {
	todo!();
}
pub fn binn_new(/* int type, int size, void *pointer */) {
	todo!();
}
pub fn binn_list() {
	todo!();
}
pub fn binn_map() {
	todo!();
}
pub fn binn_object() {
	todo!();
}
pub fn binn_is_valid(/* void *ptr, int *ptype, int *pcount, int *psize */) {
	todo!();
}
pub fn binn_list_int8(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_int16(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_int32(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_uint8(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_uint16(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_uint32(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_float(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_double(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_null(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_str(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_blob(/* void *list, int pos, int *psize */) {
	todo!();
}
pub fn binn_list_list(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_map(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_object(/* void *list, int pos */) {
	todo!();
}
pub fn binn_map_int8(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_int16(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_int32(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_uint8(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_uint16(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_uint32(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_float(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_double(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_null(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_str(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_blob(/* void *map, int id, int *psize */) {
	todo!();
}
pub fn binn_map_list(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_map(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_object(/* void *map, int id */) {
	todo!();
}
pub fn binn_object_int8(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_int16(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_int32(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_uint8(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_uint16(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_uint32(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_float(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_double(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_null(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_str(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_blob(/* void *obj, const char *key, int *psize */) {
	todo!();
}
pub fn binn_object_list(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_map(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_object(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_buf_type(/* void *pbuf */) {
	todo!();
}
pub fn binn_buf_count(/* void *pbuf */) {
	todo!();
}
pub fn binn_buf_size(/* void *pbuf */) {
	todo!();
}
pub fn is_integer(/* char *p */) {
	todo!();
}
pub fn is_float(/* char *p */) {
	todo!();
}
pub fn helper_binn_map_set_raw_2(/* int * const id_ref, unsigned int * const p_idx_ref, unsigned char * const p, unsigned char sign */) {
	todo!();
}
pub fn helper_AddValue_1(/* int * const size_ref, int * const ArgSize_ref, void * const pvalue */) {
	todo!();
}
pub fn helper_AddValue_3(/* int * const size_ref, int * const int32_ref, unsigned int * const p_idx_ref, binn * const item, void * const pvalue, int storage_type, unsigned char * const p */) {
	todo!();
}
pub fn CheckAllocation(/* binn *item, int add_size */) {
	todo!();
}
pub fn compress_int(/* int *pstorage_type, int *ptype, void *psource */) {
	todo!();
}
pub fn helper_AddValue_2(/* unsigned int * const p_idx_ref, binn * const item, int type, unsigned char * const p */) {
	todo!();
}
pub fn AddValue(/* binn *item, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_list_add_raw(/* binn *item, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_list_add(/* binn *list, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_map_set_raw(/* binn *item, int id, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_map_set(/* binn *map, int id, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_object_set_raw(/* binn *item, const char *key, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_object_set(/* binn *obj, const char *key, int type, void *pvalue, int size */) {
	todo!();
}
pub fn binn_create_list(/* binn *list */) {
	todo!();
}
pub fn binn_create_map(/* binn *map */) {
	todo!();
}
pub fn binn_create_object(/* binn *object */) {
	todo!();
}
pub fn binn_free(/* binn *item */) {
	todo!();
}
pub fn binn_load(/* void *data, binn *value */) {
	todo!();
}
pub fn binn_list_int64(/* void *list, int pos */) {
	todo!();
}
pub fn binn_list_bool(/* void *list, int pos */) {
	todo!();
}
pub fn binn_map_int64(/* void *map, int id */) {
	todo!();
}
pub fn binn_map_bool(/* void *map, int id */) {
	todo!();
}
pub fn binn_object_int64(/* void *obj, const char *key */) {
	todo!();
}
pub fn binn_object_bool(/* void *obj, const char *key */) {
	todo!();
}
pub fn helper_binn_read_pair_1(/* int * const int32_ref, int * const id_ref, int * const counter_ref, unsigned int * const p_idx_ref, unsigned int * const key_idx_ref, unsigned char * const len_ref, int pos, int type, unsigned char * const p, unsigned char * const plimit, unsigned int plimit_idx, unsigned char * const base, unsigned int base_idx */) {
	todo!();
}
pub fn binn_read_pair(/* int expected_type, void *ptr, int pos, int *pid, char *pkey, binn *value */) {
	todo!();
}
pub fn binn_map_get_pair(/* void *ptr, int pos, int *pid, binn *value */) {
	todo!();
}
pub fn binn_object_get_pair(/* void *ptr, int pos, char *pkey, binn *value */) {
	todo!();
}
pub fn helper_binn_read_next_pair_2(/* unsigned int * const p_idx_ref, unsigned int * const key_idx_ref, unsigned short * const len_ref, binn_iter * const iter, char * const pkey, unsigned char * const p, unsigned char * const key */) {
	todo!();
}
pub fn binn_size(/* void *ptr */) {
	todo!();
}
pub fn binn_set_alloc_functions(/* void *(*new_malloc)(size_t), void *(*new_realloc)(void *, size_t), void (*new_free)(void *) */) {
	todo!();
}
pub fn binn_release(/* binn *item */) {
	todo!();
}
pub fn binn_type(/* void *ptr */) {
	todo!();
}
pub fn binn_count(/* void *ptr */) {
	todo!();
}
pub fn binn_list_uint64(/* void *list, int pos */) {
	todo!();
}
pub fn binn_map_uint64(/* void *map, int id */) {
	todo!();
}
pub fn binn_object_uint64(/* void *obj, const char *key */) {
	todo!();
}
pub fn store_value(/* binn *value */) {
	todo!();
}
pub fn binn_list_read(/* void *list, int pos, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_map_read(/* void *map, int id, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_object_read(/* void *obj, const char *key, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_map_read_pair(/* void *ptr, int pos, int *pid, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_object_read_pair(/* void *ptr, int pos, char *pkey, int *ptype, int *psize */) {
	todo!();
}
pub fn helper_binn_read_next_pair_1(/* int * const int32_ref, int * const id_ref, binn_iter * const iter, int * const pid, unsigned char * const p, unsigned int p_idx */) {
	todo!();
}
pub fn binn_read_next_pair(/* int expected_type, binn_iter *iter, int *pid, char *pkey, binn *value */) {
	todo!();
}
pub fn binn_map_next(/* binn_iter *iter, int *pid, binn *value */) {
	todo!();
}
pub fn binn_object_next(/* binn_iter *iter, char *pkey, binn *value */) {
	todo!();
}
pub fn binn_copy(/* void *old */) {
	todo!();
}
pub fn binn_list_add_new(/* binn *list, binn *value */) {
	todo!();
}
pub fn binn_map_set_new(/* binn *map, int id, binn *value */) {
	todo!();
}
pub fn binn_object_set_new(/* binn *obj, const char *key, binn *value */) {
	todo!();
}
pub fn binn_open(/* void *data */) {
	todo!();
}
pub fn binn_list_value(/* void *ptr, int pos */) {
	todo!();
}
pub fn binn_map_value(/* void *ptr, int id */) {
	todo!();
}
pub fn binn_object_value(/* void *ptr, const char *key */) {
	todo!();
}
pub fn binn_map_pair(/* void *map, int pos, int *pid */) {
	todo!();
}
pub fn binn_object_pair(/* void *obj, int pos, char *pkey */) {
	todo!();
}
pub fn binn_iter_init(/* binn_iter *iter, void *ptr, int expected_type */) {
	todo!();
}
pub fn binn_list_next(/* binn_iter *iter, binn *value */) {
	todo!();
}
pub fn binn_list_read_next(/* binn_iter *iter, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_map_read_next(/* binn_iter *iter, int *pid, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_object_read_next(/* binn_iter *iter, char *pkey, int *ptype, int *psize */) {
	todo!();
}
pub fn binn_set_string(/* binn *item, char *str, binn_mem_free pfree */) {
	todo!();
}
pub fn binn_set_blob(/* binn *item, void *ptr, int size, binn_mem_free pfree */) {
	todo!();
}
pub fn binn_get_str(/* binn *value */) {
	todo!();
}
pub fn binn_list_next_value(/* binn_iter *iter */) {
	todo!();
}
pub fn binn_map_next_value(/* binn_iter *iter, int *pid */) {
	todo!();
}
pub fn binn_object_next_value(/* binn_iter *iter, char *pkey */) {
	todo!();
}
pub fn binn_get_int32(/* binn *value, int *pint */) {
	todo!();
}
pub fn binn_add_value(/* binn *item, int binn_type, int id, char *name, int type, void *pvalue, int size */) {
	todo!();
}
pub fn is_bool_str(/* char *str, BOOL *pbool */) {
	todo!();
}
pub fn binn_get_bool(/* binn *value, BOOL *pbool */) {
	todo!();
}
pub fn binn_get_int64(/* binn *value, int64 *pint */) {
	todo!();
}
pub fn binn_get_double(/* binn *value, double *pfloat */) {
	todo!();
}
