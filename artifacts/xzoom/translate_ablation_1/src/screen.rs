use crate::*;
use std::os::raw::c_int;
use std::os::raw::c_long;
use std::os::raw::c_ulong;

pub struct Screen {
    pub ext_data: Option<Box<XExtData>>,
    pub display: Option<Box<Display>>,  // Changed from XDisplay to Display
    pub root: Window,
    pub width: c_int,
    pub height: c_int,
    pub mwidth: c_int,
    pub mheight: c_int,
    pub ndepths: c_int,
    pub depths: Option<Box<Depth>>,
    pub root_depth: c_int,
    pub root_visual: Option<Box<Visual>>,
    pub default_gc: GC,
    pub cmap: Colormap,
    pub white_pixel: c_ulong,
    pub black_pixel: c_ulong,
    pub max_maps: c_int,
    pub min_maps: c_int,
    pub backing_store: c_int,
    pub save_unders: c_int,
    pub root_input_mask: c_long,
}

