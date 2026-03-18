typedef enum 
{
  HTML_SKIP_HTML = 1 << 0,
  HTML_SKIP_STYLE = 1 << 1,
  HTML_SKIP_IMAGES = 1 << 2,
  HTML_SKIP_LINKS = 1 << 3,
  HTML_EXPAND_TABS = 1 << 4,
  HTML_SAFELINK = 1 << 5,
  HTML_TOC = 1 << 6,
  HTML_HARD_WRAP = 1 << 7,
  HTML_USE_XHTML = 1 << 8,
  HTML_ESCAPE = 1 << 9,
  HTML_ALLOW_ELEMENT_WHITELIST = 1 << 10
} html_render_mode
/*** DEPENDENCIES:
***/


