use crate::*;
use std::os::raw;


#[derive(Clone)]
pub struct XSetWindowAttributes {
    pub background_pixmap: Pixmap,
    pub background_pixel: raw::c_ulong,
    pub border_pixmap: Pixmap,
    pub border_pixel: raw::c_ulong,
    pub bit_gravity: raw::c_int,
    pub win_gravity: raw::c_int,
    pub backing_store: raw::c_int,
    pub backing_planes: raw::c_ulong,
    pub backing_pixel: raw::c_ulong,
    pub save_under: raw::c_int,
    pub event_mask: raw::c_long,
    pub do_not_propagate_mask: raw::c_long,
    pub override_redirect: raw::c_int,
    pub colormap: Colormap,
    pub cursor: Cursor,
}

