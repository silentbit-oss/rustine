use crate::*;
use std::mem::size_of;


pub type CharTrigger = Option<
    fn(
        ob: &mut Buf,
        rndr: &mut SdMarkdown,
        data: &[u8],
        max_rewind: usize,
        max_lookbehind: usize,
        size: usize,
    ) -> usize,
>;

