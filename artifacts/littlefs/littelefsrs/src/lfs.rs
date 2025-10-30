use crate::*;

pub fn lfs_max(/* uint32_t a, uint32_t b */) {
	todo!();
}
pub fn lfs_min(/* uint32_t a, uint32_t b */) {
	todo!();
}
pub fn lfs_aligndown(/* uint32_t a, uint32_t alignment */) {
	todo!();
}
pub fn lfs_npw2(/* uint32_t a */) {
	todo!();
}
pub fn lfs_ctz(/* uint32_t a */) {
	todo!();
}
pub fn lfs_popc(/* uint32_t a */) {
	todo!();
}
pub fn lfs_scmp(/* uint32_t a, uint32_t b */) {
	todo!();
}
pub fn lfs_fromle32(/* uint32_t a */) {
	todo!();
}
pub fn lfs_frombe32(/* uint32_t a */) {
	todo!();
}
pub fn lfs_malloc(/* size_t size */) {
	todo!();
}
pub fn lfs_free(/* void *p */) {
	todo!();
}
pub fn lfs_path_namelen(/* const char *path */) {
	todo!();
}
pub fn lfs_mlist_isopen(/* struct lfs_mlist *head, struct lfs_mlist *node */) {
	todo!();
}
pub fn lfs_alignup(/* uint32_t a, uint32_t alignment */) {
	todo!();
}
pub fn lfs_tole32(/* uint32_t a */) {
	todo!();
}
pub fn lfs_tobe32(/* uint32_t a */) {
	todo!();
}
pub fn lfs_path_isdir(/* const char *path */) {
	todo!();
}
pub fn lfs_pair_swap(/* lfs_block_t pair[2] */) {
	todo!();
}
pub fn lfs_pair_isnull(/* const lfs_block_t pair[2] */) {
	todo!();
}
pub fn lfs_pair_cmp(/* const lfs_block_t paira[2], const lfs_block_t pairb[2] */) {
	todo!();
}
pub fn lfs_pair_issync(/* const lfs_block_t paira[2], const lfs_block_t pairb[2] */) {
	todo!();
}
pub fn lfs_gstate_xor(/* lfs_gstate_t *a, const lfs_gstate_t *b */) {
	todo!();
}
pub fn lfs_gstate_iszero(/* const lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_ctz_fromle32(/* struct lfs_ctz *ctz */) {
	todo!();
}
pub fn lfs_ctz_tole32(/* struct lfs_ctz *ctz */) {
	todo!();
}
pub fn lfs_mlist_remove(/* lfs_t *lfs, struct lfs_mlist *mlist */) {
	todo!();
}
pub fn lfs_mlist_append(/* lfs_t *lfs, struct lfs_mlist *mlist */) {
	todo!();
}
pub fn lfs_fs_disk_version(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_prepsuperblock(/* lfs_t *lfs, bool needssuperblock */) {
	todo!();
}
pub fn lfs_alloc_ckpoint(/* lfs_t *lfs */) {
	todo!();
}
pub fn helper_helper_lfs_dir_find_1_1(/* unsigned int * const name_idx_ref, unsigned int * const suffix_idx_ref, lfs_size_t * const sufflen_ref, int * const depth_ref, const char * const suffix */) {
	todo!();
}
pub fn lfs_deinit(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_unmount_(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_unmount(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_superblock_tole32(/* lfs_superblock_t *superblock */) {
	todo!();
}
pub fn lfs_tag_size(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_gstate_needssuperblock(/* const lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_gstate_getorphans(/* const lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_tag_type1(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_gstate_hasmovehere(/* const lfs_gstate_t *a, const lfs_block_t *pair */) {
	todo!();
}
pub fn lfs_tag_chunk(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_tag_splice(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_tag_id(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_tag_isdelete(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_tag_dsize(/* lfs_tag_t tag */) {
	todo!();
}
pub fn helper_lfs_bd_read_1(/* lfs_block_t * const block_ref, lfs_off_t * const off_ref, lfs_size_t * const size_ref, unsigned int * const data_idx_ref, lfs_t * const lfs, const lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_size_t hint, uint8_t * const data */) {
	todo!();
}
pub fn lfs_bd_read(/* lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_dir_getslice(/* lfs_t *lfs, const lfs_mdir_t *dir, lfs_tag_t gmask, lfs_tag_t gtag, lfs_off_t goff, void *gbuffer, lfs_size_t gsize */) {
	todo!();
}
pub fn lfs_dir_getread(/* lfs_t *lfs, const lfs_mdir_t *dir, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_tag_t gmask, lfs_tag_t gtag, lfs_off_t off, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_cache_zero(/* lfs_t *lfs, lfs_cache_t *pcache */) {
	todo!();
}
pub fn lfs_cache_drop(/* lfs_t *lfs, lfs_cache_t *rcache */) {
	todo!();
}
pub fn lfs_bd_cmp(/* lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_bd_flush(/* lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate */) {
	todo!();
}
pub fn lfs_bd_prog(/* lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn helper_helper_lfs_file_relocate_1_1(/* int * const err_ref, lfs_t * const lfs, lfs_file_t * const file, lfs_block_t nblock, lfs_off_t i */) {
	todo!();
}
pub fn lfs_bd_erase(/* lfs_t *lfs, lfs_block_t block */) {
	todo!();
}
pub fn lfs_tortoise_detectcycles(/* const lfs_mdir_t *dir, struct lfs_tortoise_t *tortoise */) {
	todo!();
}
pub fn lfs_ctz_index(/* lfs_t *lfs, lfs_off_t *off */) {
	todo!();
}
pub fn lfs_ctz_traverse(/* lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, int (*cb)(void *, lfs_block_t), void *data */) {
	todo!();
}
pub fn lfs_dir_get(/* lfs_t *lfs, const lfs_mdir_t *dir, lfs_tag_t gmask, lfs_tag_t gtag, void *buffer */) {
	todo!();
}
pub fn lfs_tag_type3(/* lfs_tag_t tag */) {
	todo!();
}
pub fn helper_helper_lfs_fs_traverse__1_1(/* int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, int (* const cb)(void *data, lfs_block_t block), void * const data, void * const data, void * const data, bool includeorphans, lfs_mdir_t dir, uint16_t id */) {
	todo!();
}
pub fn lfs_tag_type2(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_tag_isvalid(/* lfs_tag_t tag */) {
	todo!();
}
pub fn lfs_pair_fromle32(/* lfs_block_t pair[2] */) {
	todo!();
}
pub fn lfs_fcrc_fromle32(/* struct lfs_fcrc *fcrc */) {
	todo!();
}
pub fn lfs_bd_crc(/* lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, lfs_size_t size, uint32_t *crc */) {
	todo!();
}
pub fn helper_helper_helper_lfs_dir_fetchmatch_1_1_1(/* lfs_stag_t * const besttag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, uint32_t * const crc_ref, int * const err_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_block_t temptail[2], uint16_t tempcount, bool tempsplit, lfs_stag_t tempbesttag, lfs_tag_t tag */) {
	todo!();
}
pub fn helper_helper_lfs_dir_fetchmatch_1_1(/* lfs_stag_t * const besttag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, uint16_t * const tempcount_ref, bool * const tempsplit_ref, lfs_stag_t * const tempbesttag_ref, bool * const maybeerased_ref, bool * const hasfcrc_ref, uint32_t * const crc_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_tag_t fmask, lfs_tag_t ftag, void * const data, void * const data, lfs_block_t temptail[2], struct lfs_fcrc fcrc */) {
	todo!();
}
pub fn helper_lfs_dir_fetchmatch_1(/* lfs_stag_t * const besttag_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_tag_t fmask, lfs_tag_t ftag, uint16_t * const id, void * const data, void * const data, uint32_t revs[2], int r */) {
	todo!();
}
pub fn lfs_dir_fetchmatch(/* lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2], lfs_tag_t fmask, lfs_tag_t ftag, uint16_t *id, int (*cb)(void *data, lfs_tag_t tag, const void *buffer), void *data */) {
	todo!();
}
pub fn lfs_dir_fetch(/* lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2] */) {
	todo!();
}
pub fn helper_lfs_fs_traverse__1(/* int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, int (* const cb)(void *data, lfs_block_t block), void * const data, void * const data, bool includeorphans, lfs_mdir_t dir, struct lfs_tortoise_t tortoise */) {
	todo!();
}
pub fn lfs_fs_traverse_(/* lfs_t *lfs, int (*cb)(void *data, lfs_block_t block), void *data, bool includeorphans */) {
	todo!();
}
pub fn lfs_alloc_lookahead(/* void *p, lfs_block_t block */) {
	todo!();
}
pub fn lfs_alloc_drop(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_alloc_scan(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_alloc(/* lfs_t *lfs, lfs_block_t *block */) {
	todo!();
}
pub fn helper_lfs_file_relocate_1(/* lfs_t * const lfs, lfs_file_t * const file */) {
	todo!();
}
pub fn lfs_file_relocate(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_outline(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn helper_helper_helper_lfs_ctz_extend_1_1_2(/* int * const err_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_block_t * const block, lfs_off_t * const off, lfs_block_t nblock, lfs_size_t noff */) {
	todo!();
}
pub fn helper_helper_helper_lfs_ctz_extend_1_1_1(/* int * const err_ref, lfs_block_t * const nhead_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t nblock, lfs_off_t i, lfs_size_t skips, lfs_off_t i */) {
	todo!();
}
pub fn helper_helper_lfs_ctz_extend_1_1(/* int * const err_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_size_t size, lfs_block_t * const block, lfs_off_t * const off, lfs_block_t nblock */) {
	todo!();
}
pub fn helper_lfs_ctz_extend_1(/* lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_size_t size, lfs_block_t * const block, lfs_off_t * const off */) {
	todo!();
}
pub fn lfs_ctz_extend(/* lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, lfs_block_t *block, lfs_off_t *off */) {
	todo!();
}
pub fn lfs_ctz_find(/* lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, lfs_size_t pos, lfs_block_t *block, lfs_off_t *off */) {
	todo!();
}
pub fn helper_helper_lfs_file_flushedwrite_1_2(/* lfs_t * const lfs, lfs_file_t * const file */) {
	todo!();
}
pub fn helper_helper_lfs_file_flushedwrite_1_1(/* lfs_t * const lfs, lfs_file_t * const file, const uint8_t * const data, lfs_size_t diff */) {
	todo!();
}
pub fn helper_lfs_file_flushedwrite_1(/* unsigned int * const data_idx_ref, lfs_size_t * const nsize_ref, lfs_t * const lfs, lfs_file_t * const file, const uint8_t * const data */) {
	todo!();
}
pub fn lfs_file_flushedwrite(/* lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_file_flushedread(/* lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn helper_helper_lfs_file_flush_1_1(/* lfs_t * const lfs, lfs_file_t * const file, lfs_off_t pos */) {
	todo!();
}
pub fn helper_lfs_file_flush_1(/* lfs_t * const lfs, lfs_file_t * const file */) {
	todo!();
}
pub fn lfs_file_flush(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_fs_parent(/* lfs_t *lfs, const lfs_block_t pair[2], lfs_mdir_t *parent */) {
	todo!();
}
pub fn lfs_fs_prepmove(/* lfs_t *lfs, uint16_t id, const lfs_block_t pair[2] */) {
	todo!();
}
pub fn lfs_fs_pred(/* lfs_t *lfs, const lfs_block_t pair[2], lfs_mdir_t *pdir */) {
	todo!();
}
pub fn lfs_dir_commit_size(/* void *p, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn lfs_dir_needsrelocation(/* lfs_t *lfs, lfs_mdir_t *dir */) {
	todo!();
}
pub fn lfs_pair_tole32(/* lfs_block_t pair[2] */) {
	todo!();
}
pub fn lfs_gstate_tole32(/* lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_bd_sync(/* lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate */) {
	todo!();
}
pub fn lfs_fcrc_tole32(/* struct lfs_fcrc *fcrc */) {
	todo!();
}
pub fn lfs_dir_commitprog(/* lfs_t *lfs, struct lfs_commit *commit, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_dir_commitattr(/* lfs_t *lfs, struct lfs_commit *commit, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn helper_helper_lfs_dir_commitcrc_1_1(/* lfs_t * const lfs, struct lfs_commit * const commit, uint32_t crc, uint32_t crc, lfs_off_t noff, uint8_t eperturb, uint32_t crc */) {
	todo!();
}
pub fn helper_lfs_dir_commitcrc_1(/* lfs_off_t * const off1_ref, uint32_t * const crc1_ref, uint32_t * const crc_ref, uint32_t * const crc_ref, lfs_t * const lfs, struct lfs_commit * const commit, const lfs_off_t end */) {
	todo!();
}
pub fn lfs_dir_commitcrc(/* lfs_t *lfs, struct lfs_commit *commit */) {
	todo!();
}
pub fn lfs_gstate_fromle32(/* lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_dir_getgstate(/* lfs_t *lfs, const lfs_mdir_t *dir, lfs_gstate_t *gstate */) {
	todo!();
}
pub fn helper_helper_lfs_dir_compact_1_1(/* lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin, uint16_t end, bool relocated */) {
	todo!();
}
pub fn helper_lfs_dir_compact_1(/* bool * const relocated_ref, bool * const tired_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin, uint16_t end */) {
	todo!();
}
pub fn lfs_dir_compact(/* lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t begin, uint16_t end */) {
	todo!();
}
pub fn lfs_dir_alloc(/* lfs_t *lfs, lfs_mdir_t *dir */) {
	todo!();
}
pub fn lfs_dir_split(/* lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t split, uint16_t end */) {
	todo!();
}
pub fn helper_lfs_dir_splittingcompact_2(/* uint16_t * const end_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin */) {
	todo!();
}
pub fn lfs_fs_size_count(/* void *p, lfs_block_t block */) {
	todo!();
}
pub fn lfs_fs_size_(/* lfs_t *lfs */) {
	todo!();
}
pub fn helper_lfs_dir_splittingcompact_1(/* uint16_t * const end_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin */) {
	todo!();
}
pub fn lfs_dir_splittingcompact(/* lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t begin, uint16_t end */) {
	todo!();
}
pub fn helper_lfs_dir_relocatingcommit_2(/* lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount */) {
	todo!();
}
pub fn helper_lfs_dir_relocatingcommit_1(/* lfs_t * const lfs, lfs_mdir_t * const dir, const lfs_block_t pair[2], const struct lfs_mattr * const attrs, int attrcount, lfs_block_t oldpair[2], struct lfs_mlist * const d */) {
	todo!();
}
pub fn lfs_dir_relocatingcommit(/* lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2], const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *pdir */) {
	todo!();
}
pub fn lfs_gstate_hasorphans(/* const lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_fs_preporphans(/* lfs_t *lfs, int8_t orphans */) {
	todo!();
}
pub fn helper_helper_lfs_dir_orphaningcommit_2_2(/* lfs_mdir_t * const ldir_ref, int * const state_ref, bool * const orphans_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir */) {
	todo!();
}
pub fn helper_helper_lfs_dir_orphaningcommit_2_1(/* lfs_mdir_t * const ldir_ref, int * const state_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir, bool hasparent */) {
	todo!();
}
pub fn helper_lfs_dir_orphaningcommit_2(/* lfs_mdir_t * const ldir_ref, int * const state_ref, bool * const orphans_ref, unsigned int * const d_idx_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir */) {
	todo!();
}
pub fn helper_lfs_dir_orphaningcommit_1(/* lfs_mdir_t * const ldir_ref, int * const state_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_block_t lpair[2], lfs_mdir_t pdir */) {
	todo!();
}
pub fn lfs_dir_orphaningcommit(/* lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount */) {
	todo!();
}
pub fn helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_2(/* bool * const moreorphans_ref, lfs_t * const lfs, lfs_mdir_t pdir, lfs_mdir_t parent, lfs_stag_t tag */) {
	todo!();
}
pub fn helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_1(/* bool * const moreorphans_ref, int * const err_ref, lfs_t * const lfs, lfs_mdir_t dir, lfs_mdir_t pdir */) {
	todo!();
}
pub fn helper_helper_helper_lfs_fs_deorphan_1_1_1(/* bool * const moreorphans_ref, int * const err_ref, lfs_t * const lfs, bool powerloss, int pass, lfs_mdir_t dir, lfs_mdir_t pdir */) {
	todo!();
}
pub fn helper_helper_lfs_fs_deorphan_1_1(/* lfs_mdir_t * const pdir_ref, bool * const moreorphans_ref, lfs_t * const lfs, bool powerloss, int pass, lfs_mdir_t dir */) {
	todo!();
}
pub fn helper_lfs_fs_deorphan_1(/* int * const pass_ref, lfs_t * const lfs, bool powerloss */) {
	todo!();
}
pub fn lfs_fs_deorphan(/* lfs_t *lfs, bool powerloss */) {
	todo!();
}
pub fn lfs_dir_commit(/* lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount */) {
	todo!();
}
pub fn lfs_fs_desuperblock(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_gstate_hasmove(/* const lfs_gstate_t *a */) {
	todo!();
}
pub fn lfs_fs_demove(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_forceconsistency(/* lfs_t *lfs */) {
	todo!();
}
pub fn helper_lfs_dir_find_1(/* unsigned int * const name_idx_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const char ** const path, uint16_t * const id, const char * const name */) {
	todo!();
}
pub fn lfs_dir_find(/* lfs_t *lfs, lfs_mdir_t *dir, const char **path, uint16_t *id */) {
	todo!();
}
pub fn lfs_dir_drop(/* lfs_t *lfs, lfs_mdir_t *dir, lfs_mdir_t *tail */) {
	todo!();
}
pub fn helper_lfs_remove__1(/* int * const err_ref, struct lfs_mlist * const dir_ref, lfs_t * const lfs, lfs_mdir_t cwd, lfs_stag_t tag */) {
	todo!();
}
pub fn lfs_remove_(/* lfs_t *lfs, const char *path */) {
	todo!();
}
pub fn lfs_remove(/* lfs_t *lfs, const char *path */) {
	todo!();
}
pub fn lfs_path_islast(/* const char *path */) {
	todo!();
}
pub fn helper_lfs_rename__1(/* int * const err_ref, struct lfs_mlist * const prevdir_ref, lfs_t * const lfs, lfs_mdir_t newcwd, uint16_t newid */) {
	todo!();
}
pub fn lfs_rename_(/* lfs_t *lfs, const char *oldpath, const char *newpath */) {
	todo!();
}
pub fn lfs_rename(/* lfs_t *lfs, const char *oldpath, const char *newpath */) {
	todo!();
}
pub fn lfs_commitattr(/* lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_removeattr_(/* lfs_t *lfs, const char *path, uint8_t type */) {
	todo!();
}
pub fn lfs_removeattr(/* lfs_t *lfs, const char *path, uint8_t type */) {
	todo!();
}
pub fn helper_lfs_mkdir__1(/* int * const err_ref, struct lfs_mlist * const cwd_ref, lfs_t * const lfs, lfs_mdir_t dir, lfs_mdir_t pred */) {
	todo!();
}
pub fn lfs_mkdir_(/* lfs_t *lfs, const char *path */) {
	todo!();
}
pub fn lfs_mkdir(/* lfs_t *lfs, const char *path */) {
	todo!();
}
pub fn lfs_fs_mkconsistent_(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_mkconsistent(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_gc_(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_gc(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_superblock_fromle32(/* lfs_superblock_t *superblock */) {
	todo!();
}
pub fn lfs_fs_disk_version_major(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_disk_version_minor(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_dir_tell_(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_file_tell_(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_init(/* lfs_t *lfs, const struct lfs_config *cfg */) {
	todo!();
}
pub fn lfs_format_(/* lfs_t *lfs, const struct lfs_config *cfg */) {
	todo!();
}
pub fn lfs_format(/* lfs_t *lfs, const struct lfs_config *cfg */) {
	todo!();
}
pub fn helper_helper_lfs_mount__1_1(/* int * const err_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_mdir_t dir */) {
	todo!();
}
pub fn helper_lfs_mount__1(/* int * const err_ref, lfs_t * const lfs, lfs_mdir_t dir, struct lfs_tortoise_t tortoise */) {
	todo!();
}
pub fn lfs_mount_(/* lfs_t *lfs, const struct lfs_config *cfg */) {
	todo!();
}
pub fn lfs_mount(/* lfs_t *lfs, const struct lfs_config *cfg */) {
	todo!();
}
pub fn lfs_dir_getinfo(/* lfs_t *lfs, lfs_mdir_t *dir, uint16_t id, struct lfs_info *info */) {
	todo!();
}
pub fn lfs_stat_(/* lfs_t *lfs, const char *path, struct lfs_info *info */) {
	todo!();
}
pub fn lfs_stat(/* lfs_t *lfs, const char *path, struct lfs_info *info */) {
	todo!();
}
pub fn lfs_setattr_(/* lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_setattr(/* lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_file_size_(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_seek_(/* lfs_t *lfs, lfs_file_t *file, lfs_soff_t off, int whence */) {
	todo!();
}
pub fn lfs_file_rewind_(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_rewind(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_dir_close_(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_dir_close(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_dir_rewind_(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_dir_rewind(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_fs_stat_(/* lfs_t *lfs, struct lfs_fsinfo *fsinfo */) {
	todo!();
}
pub fn lfs_fs_stat(/* lfs_t *lfs, struct lfs_fsinfo *fsinfo */) {
	todo!();
}
pub fn lfs_fs_size(/* lfs_t *lfs */) {
	todo!();
}
pub fn lfs_fs_traverse(/* lfs_t *lfs, int (*cb)(void *, lfs_block_t), void *data */) {
	todo!();
}
pub fn lfs_fs_grow_(/* lfs_t *lfs, lfs_size_t block_count */) {
	todo!();
}
pub fn lfs_fs_grow(/* lfs_t *lfs, lfs_size_t block_count */) {
	todo!();
}
pub fn lfs_getattr_(/* lfs_t *lfs, const char *path, uint8_t type, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_getattr(/* lfs_t *lfs, const char *path, uint8_t type, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn helper_lfs_file_sync__1(/* int * const err_ref, lfs_t * const lfs, lfs_file_t * const file */) {
	todo!();
}
pub fn lfs_file_sync_(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_close_(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn helper_lfs_file_opencfg__2(/* int * const err_ref, int * const err_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_file_t * const file, const char * const path, int flags */) {
	todo!();
}
pub fn helper_lfs_file_opencfg__1(/* int * const err_ref, int * const err_ref, lfs_t * const lfs, lfs_file_t * const file, lfs_stag_t tag */) {
	todo!();
}
pub fn lfs_file_opencfg_(/* lfs_t *lfs, lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *cfg */) {
	todo!();
}
pub fn lfs_file_open_(/* lfs_t *lfs, lfs_file_t *file, const char *path, int flags */) {
	todo!();
}
pub fn lfs_file_open(/* lfs_t *lfs, lfs_file_t *file, const char *path, int flags */) {
	todo!();
}
pub fn lfs_file_close(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_sync(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_dir_open_(/* lfs_t *lfs, lfs_dir_t *dir, const char *path */) {
	todo!();
}
pub fn lfs_dir_open(/* lfs_t *lfs, lfs_dir_t *dir, const char *path */) {
	todo!();
}
pub fn lfs_dir_read_(/* lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info */) {
	todo!();
}
pub fn lfs_dir_read(/* lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info */) {
	todo!();
}
pub fn lfs_dir_seek_(/* lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off */) {
	todo!();
}
pub fn lfs_dir_seek(/* lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off */) {
	todo!();
}
pub fn lfs_dir_tell(/* lfs_t *lfs, lfs_dir_t *dir */) {
	todo!();
}
pub fn lfs_dir_commit_commit_func(/* void *p, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn lfs_file_opencfg(/* lfs_t *lfs, lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *cfg */) {
	todo!();
}
pub fn lfs_file_seek(/* lfs_t *lfs, lfs_file_t *file, lfs_soff_t off, int whence */) {
	todo!();
}
pub fn lfs_file_write_(/* lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn helper_lfs_file_truncate__1(/* lfs_off_t * const size_ref, lfs_t * const lfs, lfs_file_t * const file */) {
	todo!();
}
pub fn lfs_file_truncate_(/* lfs_t *lfs, lfs_file_t *file, lfs_off_t size */) {
	todo!();
}
pub fn lfs_file_truncate(/* lfs_t *lfs, lfs_file_t *file, lfs_off_t size */) {
	todo!();
}
pub fn lfs_file_tell(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_size(/* lfs_t *lfs, lfs_file_t *file */) {
	todo!();
}
pub fn lfs_file_read_(/* lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_file_read(/* lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_file_write(/* lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size */) {
	todo!();
}
pub fn lfs_dir_traverse_filter(/* void *p, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn helper_lfs_dir_traverse_1(/* lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, struct lfs_dir_traverse stack[3 - 1] */) {
	todo!();
}
pub fn lfs_dir_find_match_func(/* void *data, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn lfs_fs_parent_match_func(/* void *data, lfs_tag_t tag, const void *buffer */) {
	todo!();
}
pub fn helper_helper_helper_lfs_dir_traverse_2_2_1(/* lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned * const sp_ref, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, lfs_tag_t tag, const void * const buffer, void * const data, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer, lfs_tag_t tag, lfs_off_t off, lfs_tag_t ptag, int attrcount, lfs_tag_t tag, lfs_tag_t tag, struct lfs_diskoff disk */) {
	todo!();
}
pub fn helper_helper_lfs_dir_traverse_2_2(/* lfs_tag_t * const tag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned * const sp_ref, int * const res_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, lfs_t * const lfs, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer */) {
	todo!();
}
pub fn helper_helper_lfs_dir_traverse_2_1(/* lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, lfs_tag_t tag, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer, lfs_tag_t tag, unsigned int cb_idx, lfs_tag_t tag, unsigned int buffer_idx */) {
	todo!();
}
pub fn helper_lfs_dir_traverse_2(/* lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, int * const res_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, lfs_t * const lfs, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer */) {
	todo!();
}
pub fn lfs_dir_traverse_func(/* lfs_t *lfs, const lfs_mdir_t *dir, lfs_off_t off, lfs_tag_t ptag, const struct lfs_mattr *attrs, int attrcount, lfs_tag_t tmask, lfs_tag_t ttag, uint16_t begin, uint16_t end, int16_t diff, int (*cb)(void *data, lfs_tag_t tag, const void *buffer), void *data */) {
	todo!();
}
