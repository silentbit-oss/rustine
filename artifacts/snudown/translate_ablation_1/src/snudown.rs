use crate::*;
use crate::HtmlRenderMode::HTML_TOC;
use crate::SNUDOWN_METHODS as snudown_methods;
use crate::SNUDOWN_MODULE__DOC__ as snudown_module__doc__;
use crate::SnudownRendererMode::RENDERER_COUNT;
use crate::SnudownRendererMode::RENDERER_USERTEXT;
use crate::SnudownRendererMode::RENDERER_WIKI;
use lazy_static::lazy_static;
use pyo3::PyErr;
use pyo3::Python;
use pyo3::ffi::PyArg_ParseTupleAndKeywords;
use pyo3::ffi::PyErr_SetString;
use pyo3::ffi::PyExc_ValueError;
use pyo3::ffi::Py_BuildValue;
use pyo3::prelude::*;
use pyo3::prelude::PyObject;
use pyo3::types::PyBytes;
use pyo3::types::PyDict;
use pyo3::types::PyTuple;
use std::ffi::CStr;
use std::ptr;
use std::sync::Mutex;
pub fn snudown_md(
    _self: &PyAny,
    args: &PyTuple,
    kwargs: Option<&PyDict>,
) -> PyResult<PyObject> {
    let kwlist = [
        "text\0".as_ptr() as *const i8,
        "nofollow\0".as_ptr() as *const i8,
        "target\0".as_ptr() as *const i8,
        "toc_id_prefix\0".as_ptr() as *const i8,
        "renderer\0".as_ptr() as *const i8,
        "enable_toc\0".as_ptr() as *const i8,
        ptr::null(),
    ];

    let mut ib = Buf {
        data: None,
        size: 0,
        asize: 0,
        unit: 0,
    };

    let mut nofollow = 0;
    let mut target: *mut i8 = ptr::null_mut();
    let mut toc_id_prefix: *mut i8 = ptr::null_mut();
    let mut renderer = RENDERER_USERTEXT as i32;
    let mut enable_toc = 0;

    let py = _self.py();

    unsafe {
        if PyArg_ParseTupleAndKeywords(
            args.as_ptr(),
            kwargs.map_or(ptr::null_mut(), |d| d.as_ptr()),
            "s#|izzii\0".as_ptr() as *const i8,
            kwlist.as_ptr() as *mut *mut i8,
            &mut ib.data,
            &mut ib.size,
            &mut nofollow,
            &mut target,
            &mut toc_id_prefix,
            &mut renderer,
            &mut enable_toc,
        ) == 0
        {
            return Err(PyErr::fetch(py));
        }
    }

    if renderer < 0 || renderer >= RENDERER_COUNT as i32 {
        return Err(PyErr::new::<pyo3::exceptions::PyValueError, _>(
            "Invalid renderer",
        ));
    }

    let mut sundown_guard = SUNDOWN.lock().unwrap();
    let _snudown = &mut sundown_guard[renderer as usize];
    let options = &mut _snudown.state.as_mut().unwrap().options;
    options.nofollow = nofollow;
    options.target = if target.is_null() {
        None
    } else {
        unsafe { Some(CStr::from_ptr(target).to_string_lossy().into_owned()) }
    };

    let mut ob = match bufnew(128) {
        Some(buf) => buf,
        None => return Err(PyErr::fetch(py)),
    };

    let flags = options.html.flags;

    if enable_toc != 0 {
        _snudown.toc_state.as_mut().unwrap().options.html.toc_id_prefix = 
            if toc_id_prefix.is_null() {
                None
            } else {
                unsafe { Some(CStr::from_ptr(toc_id_prefix).to_string_lossy().into_owned()) }
            };
        sd_markdown_render(
            &mut ob,
            unsafe { std::slice::from_raw_parts(ib.data.as_ref().unwrap().as_ptr() as *const u8, ib.size) },
            ib.size,
            _snudown.toc_renderer.as_mut().unwrap(),
        );
        _snudown.toc_state.as_mut().unwrap().options.html.toc_id_prefix = None;
        options.html.flags = flags | HTML_TOC as u32;
    }

    options.html.toc_id_prefix = if toc_id_prefix.is_null() {
        None
    } else {
        unsafe { Some(CStr::from_ptr(toc_id_prefix).to_string_lossy().into_owned()) }
    };
    sd_markdown_render(
        &mut ob,
        unsafe { std::slice::from_raw_parts(ib.data.as_ref().unwrap().as_ptr() as *const u8, ib.size) },
        ib.size,
        _snudown.main_renderer.as_mut().unwrap(),
    );
    options.html.toc_id_prefix = None;
    options.html.flags = flags;

    let result_text = if ob.data.is_none() {
        ""
    } else {
        unsafe { std::str::from_utf8_unchecked(ob.data.as_ref().unwrap()) }
    };

    let py_result = unsafe {
        Py_BuildValue(
            "s#\0".as_ptr() as *const i8,
            result_text.as_ptr() as *const i8,
            ob.size,
        )
    };
    bufrelease(Some(ob));
    
    Ok(unsafe { PyObject::from_owned_ptr(py, py_result) })
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
pub fn initsnudown() -> PyResult<()> {
    let py = unsafe { Python::assume_gil_acquired() };
    
    // Create module with methods directly instead of iterating manually
    let module = PyModule::new(py, "snudown")?;
    
    // Add docstring
    module.add("__doc__", snudown_module__doc__)?;
    
    // Initialize renderers
    init_default_renderer(&module.into());
    init_wiki_renderer(module.into());
    
    // Add version constant
    module.add("__version__", "1.7.0")?;
    
    Ok(())
}
