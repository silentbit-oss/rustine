use crate::*;


pub struct SnudownRenderer {
    pub main_renderer: Option<Box<SdMarkdown>>,
    pub toc_renderer: Option<Box<SdMarkdown>>,
    pub state: Option<Box<ModuleState>>,
    pub toc_state: Option<Box<ModuleState>>,
}

