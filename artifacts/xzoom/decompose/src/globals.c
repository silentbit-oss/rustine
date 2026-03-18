GC gc
/*** DEPENDENCIES:
***/


char *progname
/*** DEPENDENCIES:
***/


int set_title
/*** DEPENDENCIES:
***/


int xgrab
/*** DEPENDENCIES:
***/


int ygrab
/*** DEPENDENCIES:
***/


int magx = 2
/*** DEPENDENCIES:
***/


int magy = 2
/*** DEPENDENCIES:
***/


int flipxy = False
/*** DEPENDENCIES:
***/


int flipx = False
/*** DEPENDENCIES:
***/


int flipy = False
/*** DEPENDENCIES:
***/


int xzoom_flag = False
/*** DEPENDENCIES:
***/


int yzoom_flag = False
/*** DEPENDENCIES:
***/


int width[2] = {0, 256}
/*** DEPENDENCIES:
***/


int height[2] = {0, 256}
/*** DEPENDENCIES:
***/


XImage *ximage[2]
/*** DEPENDENCIES:
***/


int created_images = False
/*** DEPENDENCIES:
***/


int delays[5] = {200000, 100000, 50000, 10000, 0}
/*** DEPENDENCIES:
***/


int delay_index = 0
/*** DEPENDENCIES:
***/


int delay = 200000
/*** DEPENDENCIES:
***/


Display *dpy
/*** DEPENDENCIES:
pub type Display = _XDisplay;
----------------------------
***/


Screen *scr
/*** DEPENDENCIES:
pub struct Screen {
    pub ext_data: *mut XExtData,
    pub display: *mut _XDisplay,
    pub root: Window,
    pub width: std::os::raw::c_int,
    pub height: std::os::raw::c_int,
    pub mwidth: std::os::raw::c_int,
    pub mheight: std::os::raw::c_int,
    pub ndepths: std::os::raw::c_int,
    pub depths: *mut Depth,
    pub root_depth: std::os::raw::c_int,
    pub root_visual: *mut Visual,
    pub default_gc: GC,
    pub cmap: Colormap,
    pub white_pixel: std::os::raw::c_ulong,
    pub black_pixel: std::os::raw::c_ulong,
    pub max_maps: std::os::raw::c_int,
    pub min_maps: std::os::raw::c_int,
    pub backing_store: std::os::raw::c_int,
    pub save_unders: std::os::raw::c_int,
    pub root_input_mask: std::os::raw::c_long,
}
----------------------------
***/


Window win
/*** DEPENDENCIES:
pub type Window = XID;
----------------------------
***/


Cursor when_button
/*** DEPENDENCIES:
pub type Cursor = XID;
----------------------------
***/


Cursor crosshair
/*** DEPENDENCIES:
pub type Cursor = XID;
----------------------------
***/


