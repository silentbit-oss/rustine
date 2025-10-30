use crate::*;

// static const char HREF_SAFE[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

// static const char HTML_ESCAPE_TABLE[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 1, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

// static const char *HTML_ESCAPES[] = {"", "&quot;", "&amp;", "&#39;", "&#47;", "&lt;", "&gt;", ""}

// static const uint8_t smartypants_cb_chars[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

// const unsigned MAX_NUM_ENTITY_VAL = 0x10ffff

// const size_t MAX_NUM_ENTITY_LEN = 7

// int sip_hash_key_init = 0

// uint8_t sip_hash_key[16]

// static char *html_element_whitelist[] = {"tr", "th", "td", "table", "tbody", "thead", "tfoot", "caption", 0}

// static char *html_attr_whitelist[] = {"colspan", "rowspan", "cellspacing", "cellpadding", "scope", 0}

// static const char snudown_module__doc__[] = "When does the narwhal bacon? At Sundown."

// static const char snudown_md__doc__[] = "Render a Markdown document"

// static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES

// static const unsigned int snudown_default_render_flags = (((HTML_SKIP_HTML | HTML_SKIP_IMAGES) | HTML_SAFELINK) | HTML_ESCAPE) | HTML_USE_XHTML

// static const unsigned int snudown_wiki_render_flags = (((HTML_SKIP_HTML | HTML_SAFELINK) | HTML_ALLOW_ELEMENT_WHITELIST) | HTML_ESCAPE) | HTML_USE_XHTML

// static char_trigger markdown_char_ptrs[] = {0, &char_emphasis, &char_codespan, &char_linebreak, &char_link, &char_langle_tag, &char_escape, &char_entity, &char_autolink_url, &char_autolink_email, &char_autolink_www, &char_autolink_subreddit_or_username, &char_superscript}

// static struct snudown_renderer sundown[RENDERER_COUNT]

// static struct module_state usertext_toc_state

// static struct module_state wiki_toc_state

// static struct module_state usertext_state

// static struct module_state wiki_state

// static PyMethodDef snudown_methods[] = {{"markdown", (PyCFunction) snudown_md, METH_VARARGS | METH_KEYWORDS, snudown_md__doc__}, {0, 0, 0, 0}}

// static size_t (*smartypants_cb_ptrs[])(struct buf *, struct smartypants_data *, uint8_t, const uint8_t *, size_t) = {0, smartypants_cb__dash, smartypants_cb__parens, smartypants_cb__squote, smartypants_cb__dquote, smartypants_cb__amp, smartypants_cb__period, smartypants_cb__number, smartypants_cb__ltag, smartypants_cb__backtick, smartypants_cb__escape}

