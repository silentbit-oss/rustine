use crate::*;
use std::mem::size_of;



pub struct SdCallbacks {
    pub blockcode: Option<Box<dyn Fn(&mut Buf, &Buf, &Buf, &mut dyn std::any::Any)>>,
    pub blockquote: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub blockspoiler: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub blockhtml: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub header: Option<Box<dyn Fn(&mut Buf, &Buf, i32, &mut dyn std::any::Any)>>,
    pub hrule: Option<Box<dyn Fn(&mut Buf, &mut dyn std::any::Any)>>,
    pub list: Option<Box<dyn Fn(&mut Buf, &Buf, i32, &mut dyn std::any::Any)>>,
    pub listitem: Option<Box<dyn Fn(&mut Buf, &Buf, i32, &mut dyn std::any::Any)>>,
    pub paragraph: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub table: Option<Box<dyn Fn(&mut Buf, &Buf, &Buf, &mut dyn std::any::Any)>>,
    pub table_row: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub table_cell: Option<Box<dyn Fn(&mut Buf, &Buf, i32, &mut dyn std::any::Any, i32)>>,
    pub autolink: Option<Box<dyn Fn(&mut Buf, &Buf, MkdAutolink, &mut dyn std::any::Any) -> i32>>,
    pub codespan: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub spoilerspan: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub double_emphasis: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub emphasis: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub image: Option<Box<dyn Fn(&mut Buf, &Buf, &Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub linebreak: Option<Box<dyn Fn(&mut Buf, &mut dyn std::any::Any) -> i32>>,
    pub link: Option<Box<dyn Fn(&mut Buf, &Buf, &Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub raw_html_tag: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub triple_emphasis: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub strikethrough: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub superscript: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any) -> i32>>,
    pub entity: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub normal_text: Option<Box<dyn Fn(&mut Buf, &Buf, &mut dyn std::any::Any)>>,
    pub doc_header: Option<Box<dyn Fn(&mut Buf, &mut dyn std::any::Any)>>,
    pub doc_footer: Option<Box<dyn Fn(&mut Buf, &mut dyn std::any::Any)>>,
}

