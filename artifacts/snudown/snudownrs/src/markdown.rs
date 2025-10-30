use crate::*;

pub fn sd_version(/* int *ver_major, int *ver_minor, int *ver_revision */) {
	todo!();
}
pub fn hash_block_tag(/* const char *str, unsigned int len */) {
	todo!();
}
pub fn hash_html_entity(/* register const char *str, register size_t len */) {
	todo!();
}
pub fn backport_getrandom(/* void *buf, size_t buflen, unsigned int flags */) {
	todo!();
}
pub fn _isspace(/* int c */) {
	todo!();
}
pub fn is_mail_autolink(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn is_empty(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn is_hrule(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_codefence(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn is_headerline(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_quote(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_code(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn helper_parse_table_header_1(/* size_t * const i_ref, size_t * const col_ref, uint8_t * const data, int ** const column_data, size_t under_end */) {
	todo!();
}
pub fn helper_helper_find_emph_char_1_1(/* uint8_t * const data, size_t size, uint8_t c, size_t i */) {
	todo!();
}
pub fn helper_helper_find_emph_char_1_2(/* uint8_t * const data, size_t size, uint8_t c, size_t i */) {
	todo!();
}
pub fn find_block_tag(/* const char *str, unsigned int len */) {
	todo!();
}
pub fn is_valid_numeric_entity(/* uint32_t entity_val */) {
	todo!();
}
pub fn is_allowed_named_entity(/* register const char *str, register size_t len */) {
	todo!();
}
pub fn rndr_popbuf(/* struct sd_markdown *rndr, int type */) {
	todo!();
}
pub fn helper_find_emph_char_1(/* size_t * const i_ref, uint8_t * const data, size_t size, uint8_t c */) {
	todo!();
}
pub fn find_emph_char(/* uint8_t *data, size_t size, uint8_t c */) {
	todo!();
}
pub fn is_atxheader(/* struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn is_next_headerline(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_blockspoiler(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_oli(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn prefix_uli(/* uint8_t *data, size_t size */) {
	todo!();
}
pub fn helper_tag_length_1(/* size_t * const i_ref, size_t * const j_ref, uint8_t * const data, size_t size, enum mkd_autolink * const autolink */) {
	todo!();
}
pub fn helper_is_codefence_1(/* size_t * const i_ref, size_t * const syn_len_ref, unsigned int * const syn_start_idx_ref, uint8_t * const data, size_t size, uint8_t * const syn_start */) {
	todo!();
}
pub fn helper_helper_char_link_3_1(/* size_t * const i_ref, size_t * const link_e_ref, size_t * const title_b_ref, size_t * const title_e_ref, int * const in_title_ref, int * const qtype_ref, uint8_t * const data, size_t size */) {
	todo!();
}
pub fn char_linebreak(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_codespan(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn hash_link_ref(/* const uint8_t *link_ref, size_t length */) {
	todo!();
}
pub fn find_link_ref(/* struct link_ref **references, uint8_t *name, size_t length */) {
	todo!();
}
pub fn free_link_refs(/* struct link_ref **references */) {
	todo!();
}
pub fn htmlblock_end_tag(/* const char *tag, size_t tag_len, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn htmlblock_end(/* const char *curtag, struct sd_markdown *rndr, uint8_t *data, size_t size, int start_of_line */) {
	todo!();
}
pub fn add_link_ref(/* struct link_ref **references, const uint8_t *name, size_t name_size */) {
	todo!();
}
pub fn helper_is_ref_1(/* const uint8_t * const data, struct link_ref ** const refs, size_t id_offset, size_t id_end, size_t link_offset, size_t link_end, size_t title_offset, size_t title_end */) {
	todo!();
}
pub fn is_ref(/* const uint8_t *data, size_t beg, size_t end, size_t *last, struct link_ref **refs */) {
	todo!();
}
pub fn sd_markdown_free(/* struct sd_markdown *md */) {
	todo!();
}
pub fn char_escape(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn unscape_text(/* struct buf *ob, struct buf *src */) {
	todo!();
}
pub fn tag_length(/* uint8_t *data, size_t size, enum mkd_autolink *autolink */) {
	todo!();
}
pub fn expand_tabs(/* struct buf *ob, const uint8_t *line, size_t size */) {
	todo!();
}
pub fn helper_parse_htmlblock_1(/* size_t * const size_ref, size_t * const i_ref, size_t * const j_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int do_render */) {
	todo!();
}
pub fn parse_inline(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn is_codefence(/* uint8_t *data, size_t size, struct buf *syntax */) {
	todo!();
}
pub fn rndr_newbuf(/* struct sd_markdown *rndr, int type */) {
	todo!();
}
pub fn helper_helper_char_link_2_1(/* struct buf * const id_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl */) {
	todo!();
}
pub fn parse_htmlblock(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render */) {
	todo!();
}
pub fn parse_atxheader(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn helper_parse_table_row_1(/* size_t * const i_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, int * const col_data, int header_flag, size_t col, struct buf * const row_work */) {
	todo!();
}
pub fn parse_table_row(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t columns, int *col_data, int header_flag */) {
	todo!();
}
pub fn parse_table_header(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t *columns, int **column_data */) {
	todo!();
}
pub fn helper_char_link_2(/* size_t * const size_ref, size_t * const i_ref, size_t * const link_b_ref, size_t * const link_e_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl */) {
	todo!();
}
pub fn helper_parse_paragraph_2(/* size_t * const i_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int level */) {
	todo!();
}
pub fn sd_markdown_new(/* unsigned int extensions, size_t max_nesting, size_t max_table_cols, const struct sd_callbacks *callbacks, void *opaque */) {
	todo!();
}
pub fn char_autolink_url(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_autolink_email(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_superscript(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn parse_spoilerspan(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn parse_table(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn helper_char_link_1(/* size_t * const i_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl */) {
	todo!();
}
pub fn helper_char_link_3(/* size_t * const i_ref, size_t * const link_b_ref, size_t * const link_e_ref, size_t * const title_b_ref, size_t * const title_e_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, int * const in_title_ref, int * const qtype_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, struct buf * const link, struct buf * const title */) {
	todo!();
}
pub fn parse_emph2(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c */) {
	todo!();
}
pub fn parse_emph1(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c */) {
	todo!();
}
pub fn parse_emph3(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c */) {
	todo!();
}
pub fn char_emphasis(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_entity(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_langle_tag(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_autolink_www(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn helper_parse_paragraph_1(/* size_t * const i_ref, size_t * const end_ref, int * const level_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, size_t size */) {
	todo!();
}
pub fn parse_paragraph(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn parse_fencedcode(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn parse_blockcode(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size */) {
	todo!();
}
pub fn helper_parse_listitem_1(/* size_t * const beg_ref, size_t * const end_ref, size_t * const pre_ref, size_t * const sublist_ref, size_t * const i_ref, int * const in_empty_ref, int * const has_inside_empty_ref, int * const in_fence_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, int * const flags, struct buf * const work, size_t orgpre */) {
	todo!();
}
pub fn sd_markdown_render(/* struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md */) {
	todo!();
}
pub fn char_autolink_subreddit_or_username(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
pub fn char_link(/* struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size */) {
	todo!();
}
