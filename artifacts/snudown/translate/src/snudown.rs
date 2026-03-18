use crate::*;
use lazy_static::lazy_static;
use std::sync::Mutex;
use pyo3::prelude::*;
use pyo3::prelude::PyObject;
use pyo3::types::PyBytes;
use pyo3::types::PyDict;
use pyo3::PyErr;
use pyo3::Python;
use crate::SnudownRendererMode::RENDERER_COUNT;
use crate::SnudownRendererMode::RENDERER_USERTEXT;
use crate::SnudownRendererMode::RENDERER_WIKI;
use pyo3::ffi::PyErr_SetString;
use pyo3::ffi::PyExc_ValueError;

pub fn snudown_md(
    _self: Option<&PyAny>,
    args: Option<&PyAny>,
    kwargs: Option<&PyDict>,
) -> PyResult<Option<pyo3::PyObject>> {
    
    lazy_static! {
        static ref KWLIST: Vec<&'static str> = vec![
            "text", "nofollow", "target", "toc_id_prefix", "renderer", "enable_toc"
        ];
    }

    let mut ib = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };

    let py = unsafe { pyo3::Python::assume_gil_acquired() };

    let (text, nofollow, target, toc_id_prefix, renderer, enable_toc) = match args {
        Some(args) => {
            let kwargs = kwargs.ok_or_else(|| PyErr::new::<pyo3::exceptions::PyValueError, _>("Missing kwargs"))?;
            let text: Vec<u8> = kwargs.get_item("text")?
                .ok_or_else(|| PyErr::new::<pyo3::exceptions::PyValueError, _>("Missing text"))?
                .extract()?;
            let nofollow: i32 = kwargs.get_item("nofollow")?
                .map(|n| n.extract())
                .transpose()?
                .unwrap_or(0);
            let target: Option<String> = kwargs.get_item("target")?
                .map(|t| t.extract())
                .transpose()?;
            let toc_id_prefix: Option<String> = kwargs.get_item("toc_id_prefix")?
                .map(|t| t.extract())
                .transpose()?;
            let renderer: i32 = kwargs.get_item("renderer")?
                .map(|r| r.extract())
                .transpose()?
                .unwrap_or(RENDERER_USERTEXT as i32);
            let enable_toc: i32 = kwargs.get_item("enable_toc")?
                .map(|e| e.extract())
                .transpose()?
                .unwrap_or(0);
            
            (text, nofollow, target, toc_id_prefix, renderer, enable_toc)
        }
        None => return Ok(None),
    };

    if renderer < 0 || renderer >= RENDERER_COUNT as i32 {
        unsafe {
            PyErr_SetString(PyExc_ValueError, "Invalid renderer\0".as_ptr() as *const _);
        }
        return Ok(None);
    }

    let mut sundown = SUNDOWN.lock().unwrap();
    let _snudown = &mut sundown[renderer as usize];
    
    let options = match &mut _snudown.state {
        Some(state) => &mut state.options,
        None => return Ok(None),
    };

    options.nofollow = nofollow;
    options.target = target.clone();

    let mut ob = Buf {
        data: Some(Vec::with_capacity(128)),
        size: 0,
        asize: 128,
        unit: 1,
    };

    let flags = options.html.flags;

    if enable_toc != 0 {
        if let Some(toc_state) = &mut _snudown.toc_state {
            toc_state.options.html.toc_id_prefix = toc_id_prefix.clone();
            if let Some(toc_renderer) = &mut _snudown.toc_renderer {
                sd_markdown_render(&mut ob, &text, text.len(), toc_renderer);
            }
            toc_state.options.html.toc_id_prefix = None;
            options.html.flags = flags | HtmlRenderMode::HTML_TOC as u32;
        }
    }

    options.html.toc_id_prefix = toc_id_prefix;
    if let Some(main_renderer) = &mut _snudown.main_renderer {
        sd_markdown_render(&mut ob, &text, text.len(), main_renderer);
    }
    options.html.toc_id_prefix = None;
    options.html.flags = flags;

    let result_text = ob.data.as_ref().map(|d| d.as_slice()).unwrap_or(&[]);
    let py_result = PyBytes::new(py, result_text).into();

    bufrelease(Some(Box::new(ob)));
    Ok(Some(py_result))
}
pub fn snudown_link_attr(ob: &mut Buf, link: &Buf, opaque: &SnudownRenderopt) {
    if opaque.nofollow != 0 {
        bufput(ob, b" rel=\"nofollow\"", (size_of::<&[u8; 16]>() - 1));
    }
    if let Some(target) = &opaque.target {
        bufput(ob, b" target=\"", (size_of::<&[u8; 9]>() - 1));
        bufputs(ob, target);
        bufputc(ob, b'\"' as i32);
    }
}
pub fn make_custom_renderer(
    state: ModuleState,
    renderflags: u32,
    markdownflags: u32,
    toc_renderer: bool,
) -> Option<Box<SdMarkdown>> {
    let mut state = state;
    if toc_renderer {
        sdhtml_toc_renderer(&mut state.callbacks, &mut state.options.html);
    } else {
        sdhtml_renderer(&mut state.callbacks, &mut state.options.html, renderflags);
    }
    
    state.options.html.link_attributes = Some((
        |mut ob: Buf, link: Buf, opaque: Box<dyn std::any::Any>| {
            if let Some(opts) = opaque.downcast_ref::<SnudownRenderopt>() {
                snudown_link_attr(&mut ob, &link, opts);
            }
        }
    ) as fn(Buf, Buf, Box<dyn std::any::Any>));
    
    state.options.html.html_element_whitelist = Some(
        HTML_ELEMENT_WHITELIST
            .iter()
            .filter_map(|&x| x.map(|s| s.to_string()))
            .collect(),
    );
    state.options.html.html_attr_whitelist = Some(
        HTML_ATTR_WHITELIST
            .iter()
            .map(|&s| s.to_string())
            .collect(),
    );

    sd_markdown_new(
        markdownflags,
        16,
        64,
        state.callbacks,
        Some(Box::new(state.options)),
    )
}
pub fn init_wiki_renderer(module: PyObject) {
    // Add constant to module (assuming equivalent Python FFI functionality exists)
    // In Rust, this would typically be handled by the Python FFI bindings
    // Since we don't have the exact PyModule_AddIntConstant equivalent, we'll skip this line
    
    // Lock the SUNDOWN mutex to safely modify its contents
    let mut sundown = SUNDOWN.lock().unwrap();
    
    // Initialize the RENDERER_WIKI index
    let renderer = &mut sundown[RENDERER_WIKI as usize];
    
    // Get references to the states from the mutex
    let wiki_state = WIKI_STATE.lock().unwrap();
    let wiki_toc_state = WIKI_TOC_STATE.lock().unwrap();
    
    // Create bitwise copies of the states for the renderers
    let state_copy1 = unsafe { std::ptr::read(&*wiki_state) };
    let state_copy2 = unsafe { std::ptr::read(&*wiki_state) };
    let toc_state_copy1 = unsafe { std::ptr::read(&*wiki_toc_state) };
    let toc_state_copy2 = unsafe { std::ptr::read(&*wiki_toc_state) };
    
    // Create the renderers using the copied states
    renderer.main_renderer = make_custom_renderer(
        state_copy1,
        SNUDOWN_WIKI_RENDER_FLAGS.bits(),
        SNUDOWN_DEFAULT_MD_FLAGS.bits(),
        false,
    );
    
    renderer.toc_renderer = make_custom_renderer(
        toc_state_copy1,
        SNUDOWN_WIKI_RENDER_FLAGS.bits(),
        SNUDOWN_DEFAULT_MD_FLAGS.bits(),
        true,
    );
    
    // Store the copied states (boxed)
    renderer.state = Some(Box::new(state_copy2));
    renderer.toc_state = Some(Box::new(toc_state_copy2));
}
pub fn init_default_renderer(module: &PyObject) {
    // Assuming there's a way to add constants to Python modules in Rust
    // This would typically be done through PyO3 or similar bindings
    // For now, we'll just focus on the Rust-side initialization
    
    let mut sundown = SUNDOWN.lock().unwrap();
    let renderer = &mut sundown[RENDERER_USERTEXT as usize];
    
    // Create new ModuleState instances by manually initializing fields
    let usertext_state_for_renderer = {
        let state_guard = USERTEXT_STATE.lock().unwrap();
        ModuleState {
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
                    flags: state_guard.options.html.flags,
                    toc_data: state_guard.options.html.toc_data.clone(),
                    toc_id_prefix: state_guard.options.html.toc_id_prefix.clone(),
                    link_attributes: state_guard.options.html.link_attributes.clone(),
                    html_attr_whitelist: state_guard.options.html.html_attr_whitelist.clone(),
                    html_element_whitelist: state_guard.options.html.html_element_whitelist.clone(),
                },
                nofollow: state_guard.options.nofollow,
                target: state_guard.options.target.clone(),
            },
        }
    };
    
    let usertext_state_for_storage = {
        let state_guard = USERTEXT_STATE.lock().unwrap();
        ModuleState {
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
                    flags: state_guard.options.html.flags,
                    toc_data: state_guard.options.html.toc_data.clone(),
                    toc_id_prefix: state_guard.options.html.toc_id_prefix.clone(),
                    link_attributes: state_guard.options.html.link_attributes.clone(),
                    html_attr_whitelist: state_guard.options.html.html_attr_whitelist.clone(),
                    html_element_whitelist: state_guard.options.html.html_element_whitelist.clone(),
                },
                nofollow: state_guard.options.nofollow,
                target: state_guard.options.target.clone(),
            },
        }
    };
    
    // Clone ModuleState for TOC
    let usertext_toc_state_for_renderer = {
        let state_guard = USERTEXT_TOC_STATE.lock().unwrap();
        ModuleState {
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
                    flags: state_guard.options.html.flags,
                    toc_data: state_guard.options.html.toc_data.clone(),
                    toc_id_prefix: state_guard.options.html.toc_id_prefix.clone(),
                    link_attributes: state_guard.options.html.link_attributes.clone(),
                    html_attr_whitelist: state_guard.options.html.html_attr_whitelist.clone(),
                    html_element_whitelist: state_guard.options.html.html_element_whitelist.clone(),
                },
                nofollow: state_guard.options.nofollow,
                target: state_guard.options.target.clone(),
            },
        }
    };
    
    let usertext_toc_state_for_storage = {
        let state_guard = USERTEXT_TOC_STATE.lock().unwrap();
        ModuleState {
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
                    flags: state_guard.options.html.flags,
                    toc_data: state_guard.options.html.toc_data.clone(),
                    toc_id_prefix: state_guard.options.html.toc_id_prefix.clone(),
                    link_attributes: state_guard.options.html.link_attributes.clone(),
                    html_attr_whitelist: state_guard.options.html.html_attr_whitelist.clone(),
                    html_element_whitelist: state_guard.options.html.html_element_whitelist.clone(),
                },
                nofollow: state_guard.options.nofollow,
                target: state_guard.options.target.clone(),
            },
        }
    };

    renderer.main_renderer = make_custom_renderer(
        usertext_state_for_renderer,
        SNUDOWN_DEFAULT_RENDER_FLAGS,
        SNUDOWN_DEFAULT_MD_FLAGS.bits(),
        false,
    );
    
    renderer.toc_renderer = make_custom_renderer(
        usertext_toc_state_for_renderer,
        SNUDOWN_DEFAULT_RENDER_FLAGS,
        SNUDOWN_DEFAULT_MD_FLAGS.bits(),
        true,
    );
    
    renderer.state = Some(Box::new(usertext_state_for_storage));
    renderer.toc_state = Some(Box::new(usertext_toc_state_for_storage));
}
pub fn initsnudown() -> Option<PyObject> {
    let py = unsafe { pyo3::Python::assume_gil_acquired() };
    
    // Create PyModuleDef structure
    let module_def = pyo3::ffi::PyModuleDef {
        m_base: pyo3::ffi::PyModuleDef_HEAD_INIT,
        m_name: "snudown\0".as_ptr() as *const i8,
        m_doc: SNUDOWN_MODULE__DOC__.as_ptr() as *const i8,
        m_size: 0,
        m_methods: SNUDOWN_METHODS.lock().unwrap().as_ptr() as *mut _,
        m_slots: std::ptr::null_mut(),
        m_traverse: None,
        m_clear: None,
        m_free: None,
    };

    let module = unsafe {
        pyo3::ffi::PyModule_Create2(
            &module_def as *const _ as *mut _,
            0,
        )
    };
    if module.is_null() {
        return Option::None;
    }
    
    let module = unsafe { pyo3::PyObject::from_owned_ptr(py, module) };
    init_default_renderer(&module);
    init_wiki_renderer(module.clone());
    
    unsafe {
        pyo3::ffi::PyModule_AddStringConstant(
            module.as_ptr(),
            "__version__\0".as_ptr() as *const i8,
            "1.7.0\0".as_ptr() as *const i8,
        );
    }
    Some(module)
}
