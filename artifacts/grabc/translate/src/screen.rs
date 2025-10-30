use crate::*;
use std::os::raw::c_int;
use std::os::raw::c_long;
use std::os::raw::c_ulong;

#[derive(Clone)]
pub struct Screen {
    pub ext_data: Option<Box<XExtData>>,
    pub display: Option<Box<XDisplay>>,
    pub root: Window,
    pub width: c_int,
    pub height: c_int,
    pub mwidth: c_int,
    pub mheight: c_int,
    pub ndepths: c_int,
    pub depths: Option<Vec<Depth>>,
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

// Assuming these types are defined elsewhere in the codebase
pub type Window = u32;
pub type GC = u32;
pub type Colormap = u32;

#[derive(Clone)]
pub struct XExtData;

#[derive(Clone)]
pub struct XDisplay;

#[derive(Clone)]
pub struct Depth;

#[derive(Clone)]
pub struct Visual;

