use bitflags::bitflags;
use crate::*;
use crate::HtmlRenderMode::HTML_ESCAPE;
use crate::HtmlRenderMode::HTML_SAFELINK;
use crate::HtmlRenderMode::HTML_SKIP_HTML;
use crate::HtmlRenderMode::HTML_SKIP_IMAGES;
use crate::HtmlRenderMode::HTML_USE_XHTML;
use lazy_static::lazy_static;
use pyo3::PyResult;
use pyo3::ffi::METH_KEYWORDS;
use pyo3::ffi::METH_VARARGS;
use pyo3::ffi::PyMethodDefPointer;
use pyo3::types::PyAny;
use pyo3::types::PyDict;
use std::cell::UnsafeCell;
use std::mem::zeroed;
use std::ops::BitOr;
use std::sync::Mutex;
use std::sync::atomic::AtomicBool;
use std::sync::atomic::Ordering;

pub const HREF_SAFE: [u8; 256] = [
    2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, // 16 elements
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, // 32 elements
    0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, // 48 elements
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, // 64 elements
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 80 elements
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, // 96 elements
    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, // 112 elements
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, // 128 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 144 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 176 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 192 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 208 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 224 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 240 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 256 elements
];

pub const HTML_ESCAPE_TABLE: [u8; 256] = [
    7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 0, 7, 7, // 16 elements
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, // 32 elements
    0, 0, 1, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 4, // 48 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, // 64 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 80 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 96 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 112 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 128 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 144 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 176 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 192 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 208 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 224 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 240 elements
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 256 elements
];


lazy_static! {
    pub static ref HTML_ESCAPES: [&'static str; 8] = [
        "",
        "&quot;",
        "&amp;",
        "&#39;",
        "&#47;",
        "&lt;",
        "&gt;",
        ""
    ];
}

pub static SMARTYPANTS_CB_CHARS: [u8; 256] = [
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 16
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 32
    0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0, // 48
    0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, // 64
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 80
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, // 96
    9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 112
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 128
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 144
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 160
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 176
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 192
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 208
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 224
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 240
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  // 256
];

pub const MAX_NUM_ENTITY_VAL: u32 = 0x10ffff;

pub const MAX_NUM_ENTITY_LEN: usize = 7;


pub static SIP_HASH_KEY_INIT: AtomicBool = AtomicBool::new(false);


lazy_static! {
    pub static ref SIP_HASH_KEY: std::sync::Mutex<[u8; 16]> = 
        std::sync::Mutex::new([0; 16]);
}


lazy_static! {
    pub static ref HTML_ELEMENT_WHITELIST: [Option<&'static str>; 9] = [
        Some("tr"),
        Some("th"),
        Some("td"),
        Some("table"),
        Some("tbody"),
        Some("thead"),
        Some("tfoot"),
        Some("caption"),
        None,  // Represents the terminating 0 in C
    ];
}


lazy_static! {
    pub static ref HTML_ATTR_WHITELIST: [&'static str; 5] = [
        "colspan",
        "rowspan",
        "cellspacing",
        "cellpadding",
        "scope"
    ];
}

pub static SNUDOWN_MODULE__DOC__: &str = "When does the narwhal bacon? At Sundown.";

pub static SNUDOWN_MD__DOC__: &str = "Render a Markdown document";

bitflags::bitflags! {
    pub struct MkdExtensions: u32 {
        const MKDEXT_NO_INTRA_EMPHASIS = 1 << 0;
        const MKDEXT_SUPERSCRIPT = 1 << 1;
        const MKDEXT_AUTOLINK = 1 << 2;
        const MKDEXT_STRIKETHROUGH = 1 << 3;
        const MKDEXT_TABLES = 1 << 4;
    }
}

pub const SNUDOWN_DEFAULT_MD_FLAGS: MkdExtensions = MkdExtensions::from_bits_truncate(
    0b00001 |  // MKDEXT_NO_INTRA_EMPHASIS (1 << 0)
    0b00010 |  // MKDEXT_SUPERSCRIPT (1 << 1)
    0b00100 |  // MKDEXT_AUTOLINK (1 << 2)
    0b01000 |  // MKDEXT_STRIKETHROUGH (1 << 3)
    0b10000    // MKDEXT_TABLES (1 << 4)
);

#[derive(Copy, Clone)]
#[repr(u32)]  // Ensure the enum has the same size as u32
pub enum HtmlRenderMode {
    HTML_SKIP_HTML = 1 << 0,
    HTML_SKIP_IMAGES = 1 << 1,
    HTML_SAFELINK = 1 << 2,
    HTML_ESCAPE = 1 << 3,
    HTML_USE_XHTML = 1 << 4,
    // ... other variants as needed
}

impl BitOr for HtmlRenderMode {
    type Output = Self;

    fn bitor(self, rhs: Self) -> Self {
        // Safe because we've ensured the enum has the same size as u32
        unsafe { std::mem::transmute((self as u32) | (rhs as u32)) }
    }
}

impl From<HtmlRenderMode> for u32 {
    fn from(mode: HtmlRenderMode) -> u32 {
        mode as u32
    }
}

pub const SNUDOWN_DEFAULT_RENDER_FLAGS: u32 = (HtmlRenderMode::HTML_SKIP_HTML as u32)
    | (HtmlRenderMode::HTML_SKIP_IMAGES as u32)
    | (HtmlRenderMode::HTML_SAFELINK as u32)
    | (HtmlRenderMode::HTML_ESCAPE as u32)
    | (HtmlRenderMode::HTML_USE_XHTML as u32);

bitflags! {
    pub struct HtmlRenderFlags: u32 {
        const HTML_SKIP_HTML = 1 << 0;
        const HTML_SAFELINK = 1 << 1;
        const HTML_ALLOW_ELEMENT_WHITELIST = 1 << 2;
        const HTML_ESCAPE = 1 << 3;
        const HTML_USE_XHTML = 1 << 4;
    }
}

pub const SNUDOWN_WIKI_RENDER_FLAGS: HtmlRenderFlags = HtmlRenderFlags::from_bits_truncate(
    HtmlRenderFlags::HTML_SKIP_HTML.bits() |
    HtmlRenderFlags::HTML_SAFELINK.bits() |
    HtmlRenderFlags::HTML_ALLOW_ELEMENT_WHITELIST.bits() |
    HtmlRenderFlags::HTML_ESCAPE.bits() |
    HtmlRenderFlags::HTML_USE_XHTML.bits()
);

const RENDERER_COUNT: usize = 2;

unsafe impl Send for SnudownRenderer {}
unsafe impl Sync for SnudownRenderer {}

lazy_static! {
    pub static ref SUNDOWN: Mutex<[SnudownRenderer; RENDERER_COUNT]> = {
        Mutex::new(std::array::from_fn(|_| SnudownRenderer {
            main_renderer: None,
            toc_renderer: None,
            state: None,
            toc_state: None,
        }))
    };
}


unsafe impl Send for SdCallbacks {}
unsafe impl Sync for SdCallbacks {}
unsafe impl Send for SnudownRenderopt {}
unsafe impl Sync for SnudownRenderopt {}
unsafe impl Send for ModuleState {}
unsafe impl Sync for ModuleState {}

lazy_static! {
    pub static ref USERTEXT_TOC_STATE: std::sync::Mutex<ModuleState> = {
        let empty_callbacks: SdCallbacks = unsafe { zeroed() };
        let empty_options: SnudownRenderopt = unsafe { zeroed() };
        
        std::sync::Mutex::new(ModuleState {
            callbacks: empty_callbacks,
            options: empty_options,
        })
    };
}

lazy_static! {
    pub static ref WIKI_TOC_STATE: Mutex<ModuleState> = Mutex::new(ModuleState {
        callbacks: SdCallbacks {
            blockspoiler: None,
            spoilerspan: None,
            superscript: None,
            entity: None,
            doc_header: None,
            doc_footer: None,
            autolink: None,
            blockcode: None,
            blockhtml: None,
            blockquote: None,
            header: None,
            hrule: None,
            list: None,
            listitem: None,
            paragraph: None,
            table: None,
            table_cell: None,
            table_row: None,
            codespan: None,
            double_emphasis: None,
            emphasis: None,
            image: None,
            linebreak: None,
            link: None,
            raw_html_tag: None,
            triple_emphasis: None,
            strikethrough: None,
            normal_text: None,
        },
        options: SnudownRenderopt {
            html: HtmlRenderopt {
                toc_data: TocData {
                    header_count: 0,
                    current_level: 0,
                    level_offset: 0,
                },
                toc_id_prefix: None,
                flags: 0,
                html_element_whitelist: None,
                html_attr_whitelist: None,
                link_attributes: None,
            },
            nofollow: 0,
            target: None,
        },
    });
}

lazy_static! {
    pub static ref USERTEXT_STATE: std::sync::Mutex<ModuleState> = std::sync::Mutex::new(ModuleState {
        callbacks: SdCallbacks {
            autolink: None,
            blockcode: None,
            blockhtml: None,
            blockquote: None,
            codespan: None,
            double_emphasis: None,
            emphasis: None,
            image: None,
            linebreak: None,
            link: None,
            list: None,
            listitem: None,
            normal_text: None,
            paragraph: None,
            raw_html_tag: None,
            strikethrough: None,
            table: None,
            table_cell: None,
            table_row: None,
            triple_emphasis: None,
            header: None,
            hrule: None,
            blockspoiler: None,
            spoilerspan: None,
            superscript: None,
            entity: None,
            doc_header: None,
            doc_footer: None,
        },
        options: SnudownRenderopt {
            html: HtmlRenderopt {
                flags: 0,
                toc_data: TocData {
                    current_level: 0,
                    header_count: 0,
                    level_offset: 0,
                },
                toc_id_prefix: None,
                link_attributes: None,
                html_attr_whitelist: Some(Vec::new()),
                html_element_whitelist: Some(Vec::new()),
            },
            nofollow: 0,
            target: None,
        }
    });
}

lazy_static! {
    pub static ref WIKI_STATE: Mutex<ModuleState> = Mutex::new(ModuleState {
        callbacks: SdCallbacks {
            blockspoiler: None,
            header: None,
            hrule: None,
            spoilerspan: None,
            raw_html_tag: None,
            blockcode: None,
            blockquote: None,
            blockhtml: None,
            list: None,
            listitem: None,
            autolink: None,
            codespan: None,
            doc_footer: None,
            doc_header: None,
            double_emphasis: None,
            emphasis: None,
            entity: None,
            image: None,
            linebreak: None,
            link: None,
            paragraph: None,
            strikethrough: None,
            superscript: None,
            table: None,
            table_cell: None,
            table_row: None,
            triple_emphasis: None,
            normal_text: None,
            // Total of 27 fields initialized (original had 28, removed 3, added 1)
        },
        options: SnudownRenderopt {
            html: HtmlRenderopt {
                flags: 0,
                toc_data: unsafe { std::mem::zeroed() },
                toc_id_prefix: None,
                link_attributes: None,
                html_attr_whitelist: None,
                html_element_whitelist: None,
                // All 6 required fields initialized
            },
            nofollow: 0,
            target: None,
            // Initialize any other required fields for SnudownRenderopt
        },
    });
}

lazy_static! {
    pub static ref MARKDOWN_CHAR_PTRS: [CharTrigger; 13] = [
        None, // 0
        Some(char_emphasis),
        Some(char_codespan),
        None, // char_linebreak has wrong return type - needs to be fixed
        Some(char_link),
        Some(char_langle_tag),
        Some(char_escape),
        Some(char_entity),
        Some(char_autolink_url),
        Some(char_autolink_email),
        Some(char_autolink_www),
        Some(char_autolink_subreddit_or_username),
        Some(char_superscript),
    ];
}

lazy_static! {
    pub static ref SNUDOWN_METHODS: Mutex<[PyMethodDef; 2]> = Mutex::new([
        Some(Box::new(PyMethodDefStruct)),
        None
    ]);
}

type SmartypantsCallback = fn(
    ob: &mut Buf,
    smrt: &mut smartypants_data::SmartypantsData,
    previous_char: u8,
    text: &[u8],
    size: usize,
) -> usize;

#[derive(Clone)]
pub struct SmartypantsData {
    pub in_squote: i32,
    pub in_dquote: i32,
}

lazy_static! {
    pub static ref SMARTYPANTS_CB_PTRS: Mutex<[Option<SmartypantsCallback>; 11]> = Mutex::new([
        None,
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__dash(ob, &mut *smrt, previous_char, text, size)
        }),
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__parens(ob, &mut *smrt, previous_char, text, size)
        }),
        Some(smartypants_cb__squote),
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__dquote(ob, smrt, previous_char, Some(text), size)
        }),
        Some(smartypants_cb__amp),
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__period(ob, &mut *smrt, previous_char, text, size)
        }),
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__number(ob, &mut *smrt, previous_char, text, size)
        }),
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__ltag(ob, &mut *smrt, previous_char, text, size)
        }),
        None, // smartypants_cb__backtick has different return type
        Some(|ob, smrt, previous_char, text, size| {
            smartypants_cb__escape(ob, &mut *smrt, previous_char, text, size)
        }),
    ]);
}

