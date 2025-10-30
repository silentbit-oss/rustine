use ::libc;
extern "C" {
    pub type event_base;
    pub type evbuffer;
    pub type bufferevent_ops;
    pub type args_entry;
    pub type environ;
    pub type options;
    pub type hooks;
    pub type screen_titles;
    pub type input_ctx;
    pub type format_tree;
    pub type tty_code;
    pub type format_job_tree;
    pub type tmuxpeer;
    pub type screen_write_collect_item;
    pub type screen_write_collect_line;
    fn close(__fd: libc::c_int) -> libc::c_int;
    fn memcpy(
        _: *mut libc::c_void,
        _: *const libc::c_void,
        _: libc::c_ulong,
    ) -> *mut libc::c_void;
    fn strlen(_: *const libc::c_char) -> libc::c_ulong;
    fn time(__timer: *mut time_t) -> time_t;
    fn ctime_r(__timer: *const time_t, __buf: *mut libc::c_char) -> *mut libc::c_char;
    fn gettimeofday(__tv: *mut timeval, __tz: *mut libc::c_void) -> libc::c_int;
    fn bufferevent_free(bufev: *mut bufferevent);
    fn xstrdup(_: *const libc::c_char) -> *mut libc::c_char;
    fn xasprintf(
        _: *mut *mut libc::c_char,
        _: *const libc::c_char,
        _: ...
    ) -> libc::c_int;
    fn proc_send(
        _: *mut tmuxpeer,
        _: msgtype,
        _: libc::c_int,
        _: *const libc::c_void,
        _: size_t,
    ) -> libc::c_int;
    fn notify_client(_: *const libc::c_char, _: *mut client);
    fn notify_session_window(_: *const libc::c_char, _: *mut session, _: *mut window);
    fn notify_pane(_: *const libc::c_char, _: *mut window_pane);
    fn options_get_string(
        _: *mut options,
        _: *const libc::c_char,
    ) -> *const libc::c_char;
    fn options_get_number(_: *mut options, _: *const libc::c_char) -> libc::c_longlong;
    fn tty_raw(_: *mut tty, _: *const libc::c_char);
    fn tty_stop_tty(_: *mut tty);
    fn tty_term_string(_: *mut tty_term, _: tty_code_code) -> *const libc::c_char;
    fn alerts_check_session(_: *mut session);
    static mut clients: clients;
    fn server_client_set_key_table(_: *mut client, _: *const libc::c_char);
    fn status_timer_start(_: *mut client);
    fn recalculate_sizes();
    static grid_default_cell: grid_cell;
    fn screen_write_start(_: *mut screen_write_ctx, _: *mut window_pane, _: *mut screen);
    fn screen_write_stop(_: *mut screen_write_ctx);
    fn screen_write_nputs(
        _: *mut screen_write_ctx,
        _: ssize_t,
        _: *const grid_cell,
        _: *const libc::c_char,
        _: ...
    );
    fn screen_write_cursormove(_: *mut screen_write_ctx, _: u_int, _: u_int);
    fn screen_write_scrollregion(_: *mut screen_write_ctx, _: u_int, _: u_int);
    fn screen_write_linefeed(_: *mut screen_write_ctx, _: libc::c_int, _: u_int);
    fn winlink_find_by_index(_: *mut winlinks, _: libc::c_int) -> *mut winlink;
    fn winlink_find_by_window(_: *mut winlinks, _: *mut window) -> *mut winlink;
    fn winlink_remove(_: *mut winlinks, _: *mut winlink);
    fn winlink_stack_remove(_: *mut winlink_stack, _: *mut winlink);
    fn window_unzoom(_: *mut window) -> libc::c_int;
    fn window_remove_pane(_: *mut window, _: *mut window_pane);
    fn window_count_panes(_: *mut window) -> u_int;
    fn layout_close_pane(_: *mut window_pane);
    static mut sessions: sessions;
    fn sessions_RB_NEXT(_: *mut session) -> *mut session;
    fn sessions_RB_MINMAX(_: *mut sessions, _: libc::c_int) -> *mut session;
    fn session_destroy(_: *mut session, _: *const libc::c_char);
    fn session_update_activity(_: *mut session, _: *mut timeval);
    fn session_attach(
        _: *mut session,
        _: *mut window,
        _: libc::c_int,
        _: *mut *mut libc::c_char,
    ) -> *mut winlink;
    fn session_detach(_: *mut session, _: *mut winlink) -> libc::c_int;
    fn session_has(_: *mut session, _: *mut window) -> libc::c_int;
    fn session_select(_: *mut session, _: libc::c_int) -> libc::c_int;
    fn session_group_contains(_: *mut session) -> *mut session_group;
    fn session_renumber_windows(_: *mut session);
}
pub type __u_char = libc::c_uchar;
pub type __u_short = libc::c_ushort;
pub type __u_int = libc::c_uint;
pub type __uint8_t = libc::c_uchar;
pub type __uint16_t = libc::c_ushort;
pub type __uint32_t = libc::c_uint;
pub type __pid_t = libc::c_int;
pub type __time_t = libc::c_long;
pub type __suseconds_t = libc::c_long;
pub type __ssize_t = libc::c_long;
pub type u_char = __u_char;
pub type u_short = __u_short;
pub type u_int = __u_int;
pub type pid_t = __pid_t;
pub type ssize_t = __ssize_t;
pub type time_t = __time_t;
pub type size_t = libc::c_ulong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct timeval {
    pub tv_sec: __time_t,
    pub tv_usec: __suseconds_t,
}
pub type uint8_t = __uint8_t;
pub type uint16_t = __uint16_t;
pub type uint32_t = __uint32_t;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct event {
    pub ev_evcallback: event_callback,
    pub ev_timeout_pos: C2RustUnnamed_4,
    pub ev_fd: libc::c_int,
    pub ev_base: *mut event_base,
    pub ev_: C2RustUnnamed,
    pub ev_events: libc::c_short,
    pub ev_res: libc::c_short,
    pub ev_timeout: timeval,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed {
    pub ev_io: C2RustUnnamed_2,
    pub ev_signal: C2RustUnnamed_0,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_0 {
    pub ev_signal_next: C2RustUnnamed_1,
    pub ev_ncalls: libc::c_short,
    pub ev_pncalls: *mut libc::c_short,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_1 {
    pub le_next: *mut event,
    pub le_prev: *mut *mut event,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_2 {
    pub ev_io_next: C2RustUnnamed_3,
    pub ev_timeout: timeval,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_3 {
    pub le_next: *mut event,
    pub le_prev: *mut *mut event,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_4 {
    pub ev_next_with_common_timeout: C2RustUnnamed_5,
    pub min_heap_idx: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_5 {
    pub tqe_next: *mut event,
    pub tqe_prev: *mut *mut event,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct event_callback {
    pub evcb_active_next: C2RustUnnamed_7,
    pub evcb_flags: libc::c_short,
    pub evcb_pri: uint8_t,
    pub evcb_closure: uint8_t,
    pub evcb_cb_union: C2RustUnnamed_6,
    pub evcb_arg: *mut libc::c_void,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_6 {
    pub evcb_callback: Option::<
        unsafe extern "C" fn(libc::c_int, libc::c_short, *mut libc::c_void) -> (),
    >,
    pub evcb_selfcb: Option::<
        unsafe extern "C" fn(*mut event_callback, *mut libc::c_void) -> (),
    >,
    pub evcb_evfinalize: Option::<
        unsafe extern "C" fn(*mut event, *mut libc::c_void) -> (),
    >,
    pub evcb_cbfinalize: Option::<
        unsafe extern "C" fn(*mut event_callback, *mut libc::c_void) -> (),
    >,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_7 {
    pub tqe_next: *mut event_callback,
    pub tqe_prev: *mut *mut event_callback,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct bufferevent {
    pub ev_base: *mut event_base,
    pub be_ops: *const bufferevent_ops,
    pub ev_read: event,
    pub ev_write: event,
    pub input: *mut evbuffer,
    pub output: *mut evbuffer,
    pub wm_read: event_watermark,
    pub wm_write: event_watermark,
    pub readcb: bufferevent_data_cb,
    pub writecb: bufferevent_data_cb,
    pub errorcb: bufferevent_event_cb,
    pub cbarg: *mut libc::c_void,
    pub timeout_read: timeval,
    pub timeout_write: timeval,
    pub enabled: libc::c_short,
}
pub type bufferevent_event_cb = Option::<
    unsafe extern "C" fn(*mut bufferevent, libc::c_short, *mut libc::c_void) -> (),
>;
pub type bufferevent_data_cb = Option::<
    unsafe extern "C" fn(*mut bufferevent, *mut libc::c_void) -> (),
>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct event_watermark {
    pub low: size_t,
    pub high: size_t,
}
pub type cc_t = libc::c_uchar;
pub type speed_t = libc::c_uint;
pub type tcflag_t = libc::c_uint;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct termios {
    pub c_iflag: tcflag_t,
    pub c_oflag: tcflag_t,
    pub c_cflag: tcflag_t,
    pub c_lflag: tcflag_t,
    pub c_line: cc_t,
    pub c_cc: [cc_t; 32],
    pub c_ispeed: speed_t,
    pub c_ospeed: speed_t,
}
pub type bitstr_t = libc::c_uchar;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct imsg_hdr {
    pub type_0: uint32_t,
    pub len: uint16_t,
    pub flags: uint16_t,
    pub peerid: uint32_t,
    pub pid: uint32_t,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct args {
    pub tree: args_tree,
    pub argc: libc::c_int,
    pub argv: *mut *mut libc::c_char,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct args_tree {
    pub rbh_root: *mut args_entry,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct client {
    pub name: *const libc::c_char,
    pub peer: *mut tmuxpeer,
    pub queue: cmdq_list,
    pub pid: pid_t,
    pub fd: libc::c_int,
    pub event: event,
    pub retval: libc::c_int,
    pub creation_time: timeval,
    pub activity_time: timeval,
    pub environ: *mut environ,
    pub jobs: *mut format_job_tree,
    pub title: *mut libc::c_char,
    pub cwd: *const libc::c_char,
    pub term: *mut libc::c_char,
    pub ttyname: *mut libc::c_char,
    pub tty: tty,
    pub written: size_t,
    pub discarded: size_t,
    pub redraw: size_t,
    pub stdin_callback: Option::<
        unsafe extern "C" fn(*mut client, libc::c_int, *mut libc::c_void) -> (),
    >,
    pub stdin_callback_data: *mut libc::c_void,
    pub stdin_data: *mut evbuffer,
    pub stdin_closed: libc::c_int,
    pub stdout_data: *mut evbuffer,
    pub stderr_data: *mut evbuffer,
    pub repeat_timer: event,
    pub click_timer: event,
    pub click_button: u_int,
    pub status: status_line,
    pub flags: libc::c_int,
    pub keytable: *mut key_table,
    pub identify_timer: event,
    pub identify_callback: Option::<
        unsafe extern "C" fn(*mut client, *mut window_pane) -> (),
    >,
    pub identify_callback_data: *mut libc::c_void,
    pub message_string: *mut libc::c_char,
    pub message_timer: event,
    pub message_next: u_int,
    pub message_log: C2RustUnnamed_24,
    pub prompt_string: *mut libc::c_char,
    pub prompt_buffer: *mut utf8_data,
    pub prompt_index: size_t,
    pub prompt_inputcb: prompt_input_cb,
    pub prompt_freecb: prompt_free_cb,
    pub prompt_data: *mut libc::c_void,
    pub prompt_hindex: u_int,
    pub prompt_mode: C2RustUnnamed_23,
    pub prompt_flags: libc::c_int,
    pub session: *mut session,
    pub last_session: *mut session,
    pub wlmouse: libc::c_int,
    pub references: libc::c_int,
    pub entry: C2RustUnnamed_8,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_8 {
    pub tqe_next: *mut client,
    pub tqe_prev: *mut *mut client,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct session {
    pub id: u_int,
    pub name: *mut libc::c_char,
    pub cwd: *const libc::c_char,
    pub creation_time: timeval,
    pub last_attached_time: timeval,
    pub activity_time: timeval,
    pub last_activity_time: timeval,
    pub lock_timer: event,
    pub sx: u_int,
    pub sy: u_int,
    pub curw: *mut winlink,
    pub lastw: winlink_stack,
    pub windows: winlinks,
    pub statusat: libc::c_int,
    pub hooks: *mut hooks,
    pub options: *mut options,
    pub flags: libc::c_int,
    pub attached: u_int,
    pub tio: *mut termios,
    pub environ: *mut environ,
    pub references: libc::c_int,
    pub gentry: C2RustUnnamed_10,
    pub entry: C2RustUnnamed_9,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_9 {
    pub rbe_left: *mut session,
    pub rbe_right: *mut session,
    pub rbe_parent: *mut session,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_10 {
    pub tqe_next: *mut session,
    pub tqe_prev: *mut *mut session,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct winlinks {
    pub rbh_root: *mut winlink,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct winlink {
    pub idx: libc::c_int,
    pub session: *mut session,
    pub window: *mut window,
    pub status_width: size_t,
    pub status_cell: grid_cell,
    pub status_text: *mut libc::c_char,
    pub flags: libc::c_int,
    pub entry: C2RustUnnamed_13,
    pub wentry: C2RustUnnamed_12,
    pub sentry: C2RustUnnamed_11,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_11 {
    pub tqe_next: *mut winlink,
    pub tqe_prev: *mut *mut winlink,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_12 {
    pub tqe_next: *mut winlink,
    pub tqe_prev: *mut *mut winlink,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_13 {
    pub rbe_left: *mut winlink,
    pub rbe_right: *mut winlink,
    pub rbe_parent: *mut winlink,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct grid_cell {
    pub flags: u_char,
    pub attr: u_short,
    pub fg: libc::c_int,
    pub bg: libc::c_int,
    pub data: utf8_data,
}
#[derive(Copy, Clone)]
#[repr(C, packed)]
pub struct utf8_data {
    pub data: [u_char; 9],
    pub have: u_char,
    pub size: u_char,
    pub width: u_char,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct window {
    pub id: u_int,
    pub name: *mut libc::c_char,
    pub name_event: event,
    pub name_time: timeval,
    pub alerts_timer: event,
    pub activity_time: timeval,
    pub active: *mut window_pane,
    pub last: *mut window_pane,
    pub panes: window_panes,
    pub lastlayout: libc::c_int,
    pub layout_root: *mut layout_cell,
    pub saved_layout_root: *mut layout_cell,
    pub old_layout: *mut libc::c_char,
    pub sx: u_int,
    pub sy: u_int,
    pub flags: libc::c_int,
    pub alerts_queued: libc::c_int,
    pub alerts_entry: C2RustUnnamed_16,
    pub options: *mut options,
    pub style: grid_cell,
    pub active_style: grid_cell,
    pub references: u_int,
    pub winlinks: C2RustUnnamed_15,
    pub entry: C2RustUnnamed_14,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_14 {
    pub rbe_left: *mut window,
    pub rbe_right: *mut window,
    pub rbe_parent: *mut window,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_15 {
    pub tqh_first: *mut winlink,
    pub tqh_last: *mut *mut winlink,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_16 {
    pub tqe_next: *mut window,
    pub tqe_prev: *mut *mut window,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct layout_cell {
    pub type_0: layout_type,
    pub parent: *mut layout_cell,
    pub sx: u_int,
    pub sy: u_int,
    pub xoff: u_int,
    pub yoff: u_int,
    pub wp: *mut window_pane,
    pub cells: layout_cells,
    pub entry: C2RustUnnamed_17,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_17 {
    pub tqe_next: *mut layout_cell,
    pub tqe_prev: *mut *mut layout_cell,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct layout_cells {
    pub tqh_first: *mut layout_cell,
    pub tqh_last: *mut *mut layout_cell,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct window_pane {
    pub id: u_int,
    pub active_point: u_int,
    pub window: *mut window,
    pub layout_cell: *mut layout_cell,
    pub saved_layout_cell: *mut layout_cell,
    pub sx: u_int,
    pub sy: u_int,
    pub osx: u_int,
    pub osy: u_int,
    pub xoff: u_int,
    pub yoff: u_int,
    pub flags: libc::c_int,
    pub argc: libc::c_int,
    pub argv: *mut *mut libc::c_char,
    pub shell: *mut libc::c_char,
    pub cwd: *const libc::c_char,
    pub pid: pid_t,
    pub tty: [libc::c_char; 32],
    pub status: libc::c_int,
    pub fd: libc::c_int,
    pub event: *mut bufferevent,
    pub resize_timer: event,
    pub ictx: *mut input_ctx,
    pub colgc: grid_cell,
    pub palette: *mut libc::c_int,
    pub pipe_fd: libc::c_int,
    pub pipe_event: *mut bufferevent,
    pub pipe_off: size_t,
    pub screen: *mut screen,
    pub base: screen,
    pub status_screen: screen,
    pub status_size: size_t,
    pub saved_cx: u_int,
    pub saved_cy: u_int,
    pub saved_grid: *mut grid,
    pub saved_cell: grid_cell,
    pub mode: *const window_mode,
    pub modedata: *mut libc::c_void,
    pub modetimer: event,
    pub modelast: time_t,
    pub modeprefix: u_int,
    pub searchstr: *mut libc::c_char,
    pub entry: C2RustUnnamed_19,
    pub tree_entry: C2RustUnnamed_18,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_18 {
    pub rbe_left: *mut window_pane,
    pub rbe_right: *mut window_pane,
    pub rbe_parent: *mut window_pane,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_19 {
    pub tqe_next: *mut window_pane,
    pub tqe_prev: *mut *mut window_pane,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct window_mode {
    pub name: *const libc::c_char,
    pub init: Option::<
        unsafe extern "C" fn(
            *mut window_pane,
            *mut cmd_find_state,
            *mut args,
        ) -> *mut screen,
    >,
    pub free: Option::<unsafe extern "C" fn(*mut window_pane) -> ()>,
    pub resize: Option::<unsafe extern "C" fn(*mut window_pane, u_int, u_int) -> ()>,
    pub key: Option::<
        unsafe extern "C" fn(
            *mut window_pane,
            *mut client,
            *mut session,
            key_code,
            *mut mouse_event,
        ) -> (),
    >,
    pub key_table: Option::<
        unsafe extern "C" fn(*mut window_pane) -> *const libc::c_char,
    >,
    pub command: Option::<
        unsafe extern "C" fn(
            *mut window_pane,
            *mut client,
            *mut session,
            *mut args,
            *mut mouse_event,
        ) -> (),
    >,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct mouse_event {
    pub valid: libc::c_int,
    pub key: key_code,
    pub statusat: libc::c_int,
    pub x: u_int,
    pub y: u_int,
    pub b: u_int,
    pub lx: u_int,
    pub ly: u_int,
    pub lb: u_int,
    pub s: libc::c_int,
    pub w: libc::c_int,
    pub wp: libc::c_int,
    pub sgr_type: u_int,
    pub sgr_b: u_int,
}
pub type key_code = libc::c_ulonglong;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmd_find_state {
    pub flags: libc::c_int,
    pub current: *mut cmd_find_state,
    pub s: *mut session,
    pub wl: *mut winlink,
    pub w: *mut window,
    pub wp: *mut window_pane,
    pub idx: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct screen {
    pub title: *mut libc::c_char,
    pub titles: *mut screen_titles,
    pub grid: *mut grid,
    pub cx: u_int,
    pub cy: u_int,
    pub cstyle: u_int,
    pub ccolour: *mut libc::c_char,
    pub rupper: u_int,
    pub rlower: u_int,
    pub mode: libc::c_int,
    pub tabs: *mut bitstr_t,
    pub sel: screen_sel,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct screen_sel {
    pub flag: libc::c_int,
    pub hidden: libc::c_int,
    pub rectflag: libc::c_int,
    pub lineflag: C2RustUnnamed_20,
    pub modekeys: libc::c_int,
    pub sx: u_int,
    pub sy: u_int,
    pub ex: u_int,
    pub ey: u_int,
    pub cell: grid_cell,
}
pub type C2RustUnnamed_20 = libc::c_uint;
pub const LINE_SEL_RIGHT_LEFT: C2RustUnnamed_20 = 2;
pub const LINE_SEL_LEFT_RIGHT: C2RustUnnamed_20 = 1;
pub const LINE_SEL_NONE: C2RustUnnamed_20 = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct grid {
    pub flags: libc::c_int,
    pub sx: u_int,
    pub sy: u_int,
    pub hscrolled: u_int,
    pub hsize: u_int,
    pub hlimit: u_int,
    pub linedata: *mut grid_line,
}
#[derive(Copy, Clone)]
#[repr(C, packed)]
pub struct grid_line {
    pub cellused: u_int,
    pub cellsize: u_int,
    pub celldata: *mut grid_cell_entry,
    pub extdsize: u_int,
    pub extddata: *mut grid_cell,
    pub flags: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C, packed)]
pub struct grid_cell_entry {
    pub flags: u_char,
    pub c2rust_unnamed: C2RustUnnamed_21,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub union C2RustUnnamed_21 {
    pub offset: u_int,
    pub data: C2RustUnnamed_22,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_22 {
    pub attr: u_char,
    pub fg: u_char,
    pub bg: u_char,
    pub data: u_char,
}
pub type layout_type = libc::c_uint;
pub const LAYOUT_WINDOWPANE: layout_type = 2;
pub const LAYOUT_TOPBOTTOM: layout_type = 1;
pub const LAYOUT_LEFTRIGHT: layout_type = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct window_panes {
    pub tqh_first: *mut window_pane,
    pub tqh_last: *mut *mut window_pane,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct winlink_stack {
    pub tqh_first: *mut winlink,
    pub tqh_last: *mut *mut winlink,
}
pub type C2RustUnnamed_23 = libc::c_uint;
pub const PROMPT_COMMAND: C2RustUnnamed_23 = 1;
pub const PROMPT_ENTRY: C2RustUnnamed_23 = 0;
pub type prompt_free_cb = Option::<unsafe extern "C" fn(*mut libc::c_void) -> ()>;
pub type prompt_input_cb = Option::<
    unsafe extern "C" fn(
        *mut client,
        *mut libc::c_void,
        *const libc::c_char,
        libc::c_int,
    ) -> libc::c_int,
>;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_24 {
    pub tqh_first: *mut message_entry,
    pub tqh_last: *mut *mut message_entry,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct message_entry {
    pub msg: *mut libc::c_char,
    pub msg_num: u_int,
    pub msg_time: time_t,
    pub entry: C2RustUnnamed_25,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_25 {
    pub tqe_next: *mut message_entry,
    pub tqe_prev: *mut *mut message_entry,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct key_table {
    pub name: *const libc::c_char,
    pub key_bindings: key_bindings,
    pub references: u_int,
    pub entry: C2RustUnnamed_26,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_26 {
    pub rbe_left: *mut key_table,
    pub rbe_right: *mut key_table,
    pub rbe_parent: *mut key_table,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct key_bindings {
    pub rbh_root: *mut key_binding,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct key_binding {
    pub key: key_code,
    pub cmdlist: *mut cmd_list,
    pub flags: libc::c_int,
    pub entry: C2RustUnnamed_27,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_27 {
    pub rbe_left: *mut key_binding,
    pub rbe_right: *mut key_binding,
    pub rbe_parent: *mut key_binding,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmd_list {
    pub references: libc::c_int,
    pub list: C2RustUnnamed_28,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_28 {
    pub tqh_first: *mut cmd,
    pub tqh_last: *mut *mut cmd,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmd {
    pub entry: *const cmd_entry,
    pub args: *mut args,
    pub file: *mut libc::c_char,
    pub line: u_int,
    pub flags: libc::c_int,
    pub qentry: C2RustUnnamed_29,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_29 {
    pub tqe_next: *mut cmd,
    pub tqe_prev: *mut *mut cmd,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmd_entry {
    pub name: *const libc::c_char,
    pub alias: *const libc::c_char,
    pub args: C2RustUnnamed_31,
    pub usage: *const libc::c_char,
    pub source: cmd_entry_flag,
    pub target: cmd_entry_flag,
    pub flags: libc::c_int,
    pub exec: Option::<unsafe extern "C" fn(*mut cmd, *mut cmdq_item) -> cmd_retval>,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmdq_item {
    pub name: *const libc::c_char,
    pub queue: *mut cmdq_list,
    pub next: *mut cmdq_item,
    pub client: *mut client,
    pub type_0: cmdq_type,
    pub group: u_int,
    pub number: u_int,
    pub time: time_t,
    pub flags: libc::c_int,
    pub shared: *mut cmdq_shared,
    pub source: cmd_find_state,
    pub target: cmd_find_state,
    pub cmdlist: *mut cmd_list,
    pub cmd: *mut cmd,
    pub cb: cmdq_cb,
    pub data: *mut libc::c_void,
    pub entry: C2RustUnnamed_30,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_30 {
    pub tqe_next: *mut cmdq_item,
    pub tqe_prev: *mut *mut cmdq_item,
}
pub type cmdq_cb = Option::<
    unsafe extern "C" fn(*mut cmdq_item, *mut libc::c_void) -> cmd_retval,
>;
pub type cmd_retval = libc::c_int;
pub const CMD_RETURN_STOP: cmd_retval = 2;
pub const CMD_RETURN_WAIT: cmd_retval = 1;
pub const CMD_RETURN_NORMAL: cmd_retval = 0;
pub const CMD_RETURN_ERROR: cmd_retval = -1;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmdq_shared {
    pub references: libc::c_int,
    pub flags: libc::c_int,
    pub formats: *mut format_tree,
    pub mouse: mouse_event,
    pub current: cmd_find_state,
}
pub type cmdq_type = libc::c_uint;
pub const CMDQ_CALLBACK: cmdq_type = 1;
pub const CMDQ_COMMAND: cmdq_type = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmdq_list {
    pub tqh_first: *mut cmdq_item,
    pub tqh_last: *mut *mut cmdq_item,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct cmd_entry_flag {
    pub flag: libc::c_char,
    pub type_0: cmd_find_type,
    pub flags: libc::c_int,
}
pub type cmd_find_type = libc::c_uint;
pub const CMD_FIND_SESSION: cmd_find_type = 2;
pub const CMD_FIND_WINDOW: cmd_find_type = 1;
pub const CMD_FIND_PANE: cmd_find_type = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_31 {
    pub template: *const libc::c_char,
    pub lower: libc::c_int,
    pub upper: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct status_line {
    pub timer: event,
    pub status: screen,
    pub old_status: *mut screen,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct tty {
    pub client: *mut client,
    pub sx: u_int,
    pub sy: u_int,
    pub cx: u_int,
    pub cy: u_int,
    pub cstyle: u_int,
    pub ccolour: *mut libc::c_char,
    pub mode: libc::c_int,
    pub rlower: u_int,
    pub rupper: u_int,
    pub rleft: u_int,
    pub rright: u_int,
    pub fd: libc::c_int,
    pub event_in: event,
    pub in_0: *mut evbuffer,
    pub event_out: event,
    pub out: *mut evbuffer,
    pub timer: event,
    pub discarded: size_t,
    pub tio: termios,
    pub cell: grid_cell,
    pub last_wp: libc::c_int,
    pub last_cell: grid_cell,
    pub flags: libc::c_int,
    pub term: *mut tty_term,
    pub term_name: *mut libc::c_char,
    pub term_flags: libc::c_int,
    pub term_type: C2RustUnnamed_32,
    pub mouse: mouse_event,
    pub mouse_drag_flag: libc::c_int,
    pub mouse_drag_update: Option::<
        unsafe extern "C" fn(*mut client, *mut mouse_event) -> (),
    >,
    pub mouse_drag_release: Option::<
        unsafe extern "C" fn(*mut client, *mut mouse_event) -> (),
    >,
    pub key_timer: event,
    pub key_tree: *mut tty_key,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct tty_key {
    pub ch: libc::c_char,
    pub key: key_code,
    pub left: *mut tty_key,
    pub right: *mut tty_key,
    pub next: *mut tty_key,
}
pub type C2RustUnnamed_32 = libc::c_uint;
pub const TTY_UNKNOWN: C2RustUnnamed_32 = 6;
pub const TTY_VT420: C2RustUnnamed_32 = 5;
pub const TTY_VT320: C2RustUnnamed_32 = 4;
pub const TTY_VT220: C2RustUnnamed_32 = 3;
pub const TTY_VT102: C2RustUnnamed_32 = 2;
pub const TTY_VT101: C2RustUnnamed_32 = 1;
pub const TTY_VT100: C2RustUnnamed_32 = 0;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct tty_term {
    pub name: *mut libc::c_char,
    pub references: u_int,
    pub acs: [[libc::c_char; 2]; 256],
    pub codes: *mut tty_code,
    pub flags: libc::c_int,
    pub entry: C2RustUnnamed_33,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_33 {
    pub le_next: *mut tty_term,
    pub le_prev: *mut *mut tty_term,
}
pub type tty_code_code = libc::c_uint;
pub const TTYC_XT: tty_code_code = 207;
pub const TTYC_XENL: tty_code_code = 206;
pub const TTYC_VPA: tty_code_code = 205;
pub const TTYC_U8: tty_code_code = 204;
pub const TTYC_TSL: tty_code_code = 203;
pub const TTYC_TC: tty_code_code = 202;
pub const TTYC_SS: tty_code_code = 201;
pub const TTYC_SMXX: tty_code_code = 200;
pub const TTYC_SMUL: tty_code_code = 199;
pub const TTYC_SMSO: tty_code_code = 198;
pub const TTYC_SMKX: tty_code_code = 197;
pub const TTYC_SMCUP: tty_code_code = 196;
pub const TTYC_SMACS: tty_code_code = 195;
pub const TTYC_SITM: tty_code_code = 194;
pub const TTYC_SGR0: tty_code_code = 193;
pub const TTYC_SETRGBF: tty_code_code = 192;
pub const TTYC_SETRGBB: tty_code_code = 191;
pub const TTYC_SETAF: tty_code_code = 190;
pub const TTYC_SETAB: tty_code_code = 189;
pub const TTYC_SE: tty_code_code = 188;
pub const TTYC_RMKX: tty_code_code = 187;
pub const TTYC_RMCUP: tty_code_code = 186;
pub const TTYC_RMACS: tty_code_code = 185;
pub const TTYC_RI: tty_code_code = 184;
pub const TTYC_RGB: tty_code_code = 183;
pub const TTYC_REV: tty_code_code = 182;
pub const TTYC_OP: tty_code_code = 181;
pub const TTYC_MS: tty_code_code = 180;
pub const TTYC_KUP7: tty_code_code = 179;
pub const TTYC_KUP6: tty_code_code = 178;
pub const TTYC_KUP5: tty_code_code = 177;
pub const TTYC_KUP4: tty_code_code = 176;
pub const TTYC_KUP3: tty_code_code = 175;
pub const TTYC_KUP2: tty_code_code = 174;
pub const TTYC_KRIT7: tty_code_code = 173;
pub const TTYC_KRIT6: tty_code_code = 172;
pub const TTYC_KRIT5: tty_code_code = 171;
pub const TTYC_KRIT4: tty_code_code = 170;
pub const TTYC_KRIT3: tty_code_code = 169;
pub const TTYC_KRIT2: tty_code_code = 168;
pub const TTYC_KRI: tty_code_code = 167;
pub const TTYC_KPRV7: tty_code_code = 166;
pub const TTYC_KPRV6: tty_code_code = 165;
pub const TTYC_KPRV5: tty_code_code = 164;
pub const TTYC_KPRV4: tty_code_code = 163;
pub const TTYC_KPRV3: tty_code_code = 162;
pub const TTYC_KPRV2: tty_code_code = 161;
pub const TTYC_KPP: tty_code_code = 160;
pub const TTYC_KNXT7: tty_code_code = 159;
pub const TTYC_KNXT6: tty_code_code = 158;
pub const TTYC_KNXT5: tty_code_code = 157;
pub const TTYC_KNXT4: tty_code_code = 156;
pub const TTYC_KNXT3: tty_code_code = 155;
pub const TTYC_KNXT2: tty_code_code = 154;
pub const TTYC_KNP: tty_code_code = 153;
pub const TTYC_KMOUS: tty_code_code = 152;
pub const TTYC_KLFT7: tty_code_code = 151;
pub const TTYC_KLFT6: tty_code_code = 150;
pub const TTYC_KLFT5: tty_code_code = 149;
pub const TTYC_KLFT4: tty_code_code = 148;
pub const TTYC_KLFT3: tty_code_code = 147;
pub const TTYC_KLFT2: tty_code_code = 146;
pub const TTYC_KIND: tty_code_code = 145;
pub const TTYC_KICH1: tty_code_code = 144;
pub const TTYC_KIC7: tty_code_code = 143;
pub const TTYC_KIC6: tty_code_code = 142;
pub const TTYC_KIC5: tty_code_code = 141;
pub const TTYC_KIC4: tty_code_code = 140;
pub const TTYC_KIC3: tty_code_code = 139;
pub const TTYC_KIC2: tty_code_code = 138;
pub const TTYC_KHOME: tty_code_code = 137;
pub const TTYC_KHOM7: tty_code_code = 136;
pub const TTYC_KHOM6: tty_code_code = 135;
pub const TTYC_KHOM5: tty_code_code = 134;
pub const TTYC_KHOM4: tty_code_code = 133;
pub const TTYC_KHOM3: tty_code_code = 132;
pub const TTYC_KHOM2: tty_code_code = 131;
pub const TTYC_KF9: tty_code_code = 130;
pub const TTYC_KF8: tty_code_code = 129;
pub const TTYC_KF7: tty_code_code = 128;
pub const TTYC_KF63: tty_code_code = 127;
pub const TTYC_KF62: tty_code_code = 126;
pub const TTYC_KF61: tty_code_code = 125;
pub const TTYC_KF60: tty_code_code = 124;
pub const TTYC_KF6: tty_code_code = 123;
pub const TTYC_KF59: tty_code_code = 122;
pub const TTYC_KF58: tty_code_code = 121;
pub const TTYC_KF57: tty_code_code = 120;
pub const TTYC_KF56: tty_code_code = 119;
pub const TTYC_KF55: tty_code_code = 118;
pub const TTYC_KF54: tty_code_code = 117;
pub const TTYC_KF53: tty_code_code = 116;
pub const TTYC_KF52: tty_code_code = 115;
pub const TTYC_KF51: tty_code_code = 114;
pub const TTYC_KF50: tty_code_code = 113;
pub const TTYC_KF5: tty_code_code = 112;
pub const TTYC_KF49: tty_code_code = 111;
pub const TTYC_KF48: tty_code_code = 110;
pub const TTYC_KF47: tty_code_code = 109;
pub const TTYC_KF46: tty_code_code = 108;
pub const TTYC_KF45: tty_code_code = 107;
pub const TTYC_KF44: tty_code_code = 106;
pub const TTYC_KF43: tty_code_code = 105;
pub const TTYC_KF42: tty_code_code = 104;
pub const TTYC_KF41: tty_code_code = 103;
pub const TTYC_KF40: tty_code_code = 102;
pub const TTYC_KF4: tty_code_code = 101;
pub const TTYC_KF39: tty_code_code = 100;
pub const TTYC_KF38: tty_code_code = 99;
pub const TTYC_KF37: tty_code_code = 98;
pub const TTYC_KF36: tty_code_code = 97;
pub const TTYC_KF35: tty_code_code = 96;
pub const TTYC_KF34: tty_code_code = 95;
pub const TTYC_KF33: tty_code_code = 94;
pub const TTYC_KF32: tty_code_code = 93;
pub const TTYC_KF31: tty_code_code = 92;
pub const TTYC_KF30: tty_code_code = 91;
pub const TTYC_KF3: tty_code_code = 90;
pub const TTYC_KF29: tty_code_code = 89;
pub const TTYC_KF28: tty_code_code = 88;
pub const TTYC_KF27: tty_code_code = 87;
pub const TTYC_KF26: tty_code_code = 86;
pub const TTYC_KF25: tty_code_code = 85;
pub const TTYC_KF24: tty_code_code = 84;
pub const TTYC_KF23: tty_code_code = 83;
pub const TTYC_KF22: tty_code_code = 82;
pub const TTYC_KF21: tty_code_code = 81;
pub const TTYC_KF20: tty_code_code = 80;
pub const TTYC_KF2: tty_code_code = 79;
pub const TTYC_KF19: tty_code_code = 78;
pub const TTYC_KF18: tty_code_code = 77;
pub const TTYC_KF17: tty_code_code = 76;
pub const TTYC_KF16: tty_code_code = 75;
pub const TTYC_KF15: tty_code_code = 74;
pub const TTYC_KF14: tty_code_code = 73;
pub const TTYC_KF13: tty_code_code = 72;
pub const TTYC_KF12: tty_code_code = 71;
pub const TTYC_KF11: tty_code_code = 70;
pub const TTYC_KF10: tty_code_code = 69;
pub const TTYC_KF1: tty_code_code = 68;
pub const TTYC_KEND7: tty_code_code = 67;
pub const TTYC_KEND6: tty_code_code = 66;
pub const TTYC_KEND5: tty_code_code = 65;
pub const TTYC_KEND4: tty_code_code = 64;
pub const TTYC_KEND3: tty_code_code = 63;
pub const TTYC_KEND2: tty_code_code = 62;
pub const TTYC_KEND: tty_code_code = 61;
pub const TTYC_KDN7: tty_code_code = 60;
pub const TTYC_KDN6: tty_code_code = 59;
pub const TTYC_KDN5: tty_code_code = 58;
pub const TTYC_KDN4: tty_code_code = 57;
pub const TTYC_KDN3: tty_code_code = 56;
pub const TTYC_KDN2: tty_code_code = 55;
pub const TTYC_KDCH1: tty_code_code = 54;
pub const TTYC_KDC7: tty_code_code = 53;
pub const TTYC_KDC6: tty_code_code = 52;
pub const TTYC_KDC5: tty_code_code = 51;
pub const TTYC_KDC4: tty_code_code = 50;
pub const TTYC_KDC3: tty_code_code = 49;
pub const TTYC_KDC2: tty_code_code = 48;
pub const TTYC_KCUU1: tty_code_code = 47;
pub const TTYC_KCUF1: tty_code_code = 46;
pub const TTYC_KCUD1: tty_code_code = 45;
pub const TTYC_KCUB1: tty_code_code = 44;
pub const TTYC_KCBT: tty_code_code = 43;
pub const TTYC_INVIS: tty_code_code = 42;
pub const TTYC_INDN: tty_code_code = 41;
pub const TTYC_IL1: tty_code_code = 40;
pub const TTYC_IL: tty_code_code = 39;
pub const TTYC_ICH1: tty_code_code = 38;
pub const TTYC_ICH: tty_code_code = 37;
pub const TTYC_HPA: tty_code_code = 36;
pub const TTYC_HOME: tty_code_code = 35;
pub const TTYC_FSL: tty_code_code = 34;
pub const TTYC_ENACS: tty_code_code = 33;
pub const TTYC_EL1: tty_code_code = 32;
pub const TTYC_EL: tty_code_code = 31;
pub const TTYC_ED: tty_code_code = 30;
pub const TTYC_ECH: tty_code_code = 29;
pub const TTYC_E3: tty_code_code = 28;
pub const TTYC_DL1: tty_code_code = 27;
pub const TTYC_DL: tty_code_code = 26;
pub const TTYC_DIM: tty_code_code = 25;
pub const TTYC_DCH1: tty_code_code = 24;
pub const TTYC_DCH: tty_code_code = 23;
pub const TTYC_CVVIS: tty_code_code = 22;
pub const TTYC_CUU1: tty_code_code = 21;
pub const TTYC_CUU: tty_code_code = 20;
pub const TTYC_CUP: tty_code_code = 19;
pub const TTYC_CUF1: tty_code_code = 18;
pub const TTYC_CUF: tty_code_code = 17;
pub const TTYC_CUD1: tty_code_code = 16;
pub const TTYC_CUD: tty_code_code = 15;
pub const TTYC_CUB1: tty_code_code = 14;
pub const TTYC_CUB: tty_code_code = 13;
pub const TTYC_CSR: tty_code_code = 12;
pub const TTYC_CS: tty_code_code = 11;
pub const TTYC_CR: tty_code_code = 10;
pub const TTYC_COLORS: tty_code_code = 9;
pub const TTYC_CNORM: tty_code_code = 8;
pub const TTYC_CLEAR: tty_code_code = 7;
pub const TTYC_CIVIS: tty_code_code = 6;
pub const TTYC_BOLD: tty_code_code = 5;
pub const TTYC_BLINK: tty_code_code = 4;
pub const TTYC_BEL: tty_code_code = 3;
pub const TTYC_BCE: tty_code_code = 2;
pub const TTYC_ACSC: tty_code_code = 1;
pub const TTYC_AX: tty_code_code = 0;
pub type msgtype = libc::c_uint;
pub const MSG_EXEC: msgtype = 217;
pub const MSG_WAKEUP: msgtype = 216;
pub const MSG_UNLOCK: msgtype = 215;
pub const MSG_SUSPEND: msgtype = 214;
pub const MSG_STDOUT: msgtype = 213;
pub const MSG_STDIN: msgtype = 212;
pub const MSG_STDERR: msgtype = 211;
pub const MSG_SHUTDOWN: msgtype = 210;
pub const MSG_SHELL: msgtype = 209;
pub const MSG_RESIZE: msgtype = 208;
pub const MSG_READY: msgtype = 207;
pub const MSG_LOCK: msgtype = 206;
pub const MSG_EXITING: msgtype = 205;
pub const MSG_EXITED: msgtype = 204;
pub const MSG_EXIT: msgtype = 203;
pub const MSG_DETACHKILL: msgtype = 202;
pub const MSG_DETACH: msgtype = 201;
pub const MSG_COMMAND: msgtype = 200;
pub const MSG_IDENTIFY_CWD: msgtype = 108;
pub const MSG_IDENTIFY_CLIENTPID: msgtype = 107;
pub const MSG_IDENTIFY_DONE: msgtype = 106;
pub const MSG_IDENTIFY_ENVIRON: msgtype = 105;
pub const MSG_IDENTIFY_STDIN: msgtype = 104;
pub const MSG_IDENTIFY_OLDCWD: msgtype = 103;
pub const MSG_IDENTIFY_TTYNAME: msgtype = 102;
pub const MSG_IDENTIFY_TERM: msgtype = 101;
pub const MSG_IDENTIFY_FLAGS: msgtype = 100;
pub const MSG_VERSION: msgtype = 12;
#[derive(Copy, Clone)]
#[repr(C)]
pub struct screen_write_ctx {
    pub wp: *mut window_pane,
    pub s: *mut screen,
    pub item: *mut screen_write_collect_item,
    pub list: *mut screen_write_collect_line,
    pub scrolled: u_int,
    pub bg: u_int,
    pub cells: u_int,
    pub written: u_int,
    pub skipped: u_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct session_group {
    pub name: *const libc::c_char,
    pub sessions: C2RustUnnamed_35,
    pub entry: C2RustUnnamed_34,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_34 {
    pub rbe_left: *mut session_group,
    pub rbe_right: *mut session_group,
    pub rbe_parent: *mut session_group,
    pub rbe_color: libc::c_int,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct C2RustUnnamed_35 {
    pub tqh_first: *mut session,
    pub tqh_last: *mut *mut session,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct sessions {
    pub rbh_root: *mut session,
}
#[derive(Copy, Clone)]
#[repr(C)]
pub struct clients {
    pub tqh_first: *mut client,
    pub tqh_last: *mut *mut client,
}
#[no_mangle]
pub unsafe extern "C" fn server_redraw_client(mut c: *mut client) {
    (*c).flags |= 0x8 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn server_status_client(mut c: *mut client) {
    (*c).flags |= 0x10 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn server_redraw_session(mut s: *mut session) {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if (*c).session == s {
            server_redraw_client(c);
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_redraw_session_group(mut s: *mut session) {
    let mut sg: *mut session_group = 0 as *mut session_group;
    sg = session_group_contains(s);
    if sg.is_null() {
        server_redraw_session(s);
    } else {
        s = (*sg).sessions.tqh_first;
        while !s.is_null() {
            server_redraw_session(s);
            s = (*s).gentry.tqe_next;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn server_status_session(mut s: *mut session) {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if (*c).session == s {
            server_status_client(c);
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_status_session_group(mut s: *mut session) {
    let mut sg: *mut session_group = 0 as *mut session_group;
    sg = session_group_contains(s);
    if sg.is_null() {
        server_status_session(s);
    } else {
        s = (*sg).sessions.tqh_first;
        while !s.is_null() {
            server_status_session(s);
            s = (*s).gentry.tqe_next;
        }
    };
}
#[no_mangle]
pub unsafe extern "C" fn server_redraw_window(mut w: *mut window) {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if !((*c).session).is_null() && (*(*(*c).session).curw).window == w {
            server_redraw_client(c);
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_redraw_window_borders(mut w: *mut window) {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if !((*c).session).is_null() && (*(*(*c).session).curw).window == w {
            (*c).flags |= 0x400 as libc::c_int;
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_status_window(mut w: *mut window) {
    let mut s: *mut session = 0 as *mut session;
    s = sessions_RB_MINMAX(&mut sessions, -(1 as libc::c_int));
    while !s.is_null() {
        if session_has(s, w) != 0 {
            server_status_session(s);
        }
        s = sessions_RB_NEXT(s);
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_lock() {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if !((*c).session).is_null() {
            server_lock_client(c);
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_lock_session(mut s: *mut session) {
    let mut c: *mut client = 0 as *mut client;
    c = clients.tqh_first;
    while !c.is_null() {
        if (*c).session == s {
            server_lock_client(c);
        }
        c = (*c).entry.tqe_next;
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_lock_client(mut c: *mut client) {
    let mut cmd: *const libc::c_char = 0 as *const libc::c_char;
    if (*c).flags & 0x2000 as libc::c_int != 0 {
        return;
    }
    if (*c).flags & 0x40 as libc::c_int != 0 {
        return;
    }
    cmd = options_get_string(
        (*(*c).session).options,
        b"lock-command\0" as *const u8 as *const libc::c_char,
    );
    if *cmd as libc::c_int == '\0' as i32
        || (strlen(cmd)).wrapping_add(1 as libc::c_int as libc::c_ulong)
            > (16384 as libc::c_int as libc::c_ulong)
                .wrapping_sub(::core::mem::size_of::<imsg_hdr>() as libc::c_ulong)
    {
        return;
    }
    tty_stop_tty(&mut (*c).tty);
    tty_raw(&mut (*c).tty, tty_term_string((*c).tty.term, TTYC_SMCUP));
    tty_raw(&mut (*c).tty, tty_term_string((*c).tty.term, TTYC_CLEAR));
    tty_raw(&mut (*c).tty, tty_term_string((*c).tty.term, TTYC_E3));
    (*c).flags |= 0x40 as libc::c_int;
    proc_send(
        (*c).peer,
        MSG_LOCK,
        -(1 as libc::c_int),
        cmd as *const libc::c_void,
        (strlen(cmd)).wrapping_add(1 as libc::c_int as libc::c_ulong),
    );
}
#[no_mangle]
pub unsafe extern "C" fn server_kill_pane(mut wp: *mut window_pane) {
    let mut w: *mut window = (*wp).window;
    if window_count_panes(w) == 1 as libc::c_int as u_int {
        server_kill_window(w);
        recalculate_sizes();
    } else {
        server_unzoom_window(w);
        layout_close_pane(wp);
        window_remove_pane(w, wp);
        server_redraw_window(w);
    };
}
#[no_mangle]
pub unsafe extern "C" fn server_kill_window(mut w: *mut window) {
    let mut s: *mut session = 0 as *mut session;
    let mut next_s: *mut session = 0 as *mut session;
    let mut target_s: *mut session = 0 as *mut session;
    let mut sg: *mut session_group = 0 as *mut session_group;
    let mut wl: *mut winlink = 0 as *mut winlink;
    next_s = sessions_RB_MINMAX(&mut sessions, -(1 as libc::c_int));
    while !next_s.is_null() {
        s = next_s;
        next_s = sessions_RB_NEXT(s);
        if session_has(s, w) == 0 {
            continue;
        }
        server_unzoom_window(w);
        loop {
            wl = winlink_find_by_window(&mut (*s).windows, w);
            if wl.is_null() {
                break;
            }
            if session_detach(s, wl) != 0 {
                server_destroy_session_group(s);
                break;
            } else {
                server_redraw_session_group(s);
            }
        }
        if options_get_number(
            (*s).options,
            b"renumber-windows\0" as *const u8 as *const libc::c_char,
        ) != 0
        {
            sg = session_group_contains(s);
            if !sg.is_null() {
                target_s = (*sg).sessions.tqh_first;
                while !target_s.is_null() {
                    session_renumber_windows(target_s);
                    target_s = (*target_s).gentry.tqe_next;
                }
            } else {
                session_renumber_windows(s);
            }
        }
    }
    recalculate_sizes();
}
#[no_mangle]
pub unsafe extern "C" fn server_link_window(
    mut src: *mut session,
    mut srcwl: *mut winlink,
    mut dst: *mut session,
    mut dstidx: libc::c_int,
    mut killflag: libc::c_int,
    mut selectflag: libc::c_int,
    mut cause: *mut *mut libc::c_char,
) -> libc::c_int {
    let mut dstwl: *mut winlink = 0 as *mut winlink;
    let mut srcsg: *mut session_group = 0 as *mut session_group;
    let mut dstsg: *mut session_group = 0 as *mut session_group;
    srcsg = session_group_contains(src);
    dstsg = session_group_contains(dst);
    if src != dst && !srcsg.is_null() && !dstsg.is_null() && srcsg == dstsg {
        xasprintf(cause, b"sessions are grouped\0" as *const u8 as *const libc::c_char);
        return -(1 as libc::c_int);
    }
    dstwl = 0 as *mut winlink;
    if dstidx != -(1 as libc::c_int) {
        dstwl = winlink_find_by_index(&mut (*dst).windows, dstidx);
    }
    if !dstwl.is_null() {
        if (*dstwl).window == (*srcwl).window {
            xasprintf(
                cause,
                b"same index: %d\0" as *const u8 as *const libc::c_char,
                dstidx,
            );
            return -(1 as libc::c_int);
        }
        if killflag != 0 {
            notify_session_window(
                b"window-unlinked\0" as *const u8 as *const libc::c_char,
                dst,
                (*dstwl).window,
            );
            (*dstwl).flags
                &= !(0x1 as libc::c_int | 0x2 as libc::c_int | 0x4 as libc::c_int);
            winlink_stack_remove(&mut (*dst).lastw, dstwl);
            winlink_remove(&mut (*dst).windows, dstwl);
            if dstwl == (*dst).curw {
                selectflag = 1 as libc::c_int;
                (*dst).curw = 0 as *mut winlink;
            }
        }
    }
    if dstidx == -(1 as libc::c_int) {
        dstidx = (-(1 as libc::c_int) as libc::c_longlong
            - options_get_number(
                (*dst).options,
                b"base-index\0" as *const u8 as *const libc::c_char,
            )) as libc::c_int;
    }
    dstwl = session_attach(dst, (*srcwl).window, dstidx, cause);
    if dstwl.is_null() {
        return -(1 as libc::c_int);
    }
    if selectflag != 0 {
        session_select(dst, (*dstwl).idx);
    }
    server_redraw_session_group(dst);
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn server_unlink_window(
    mut s: *mut session,
    mut wl: *mut winlink,
) {
    if session_detach(s, wl) != 0 {
        server_destroy_session_group(s);
    } else {
        server_redraw_session_group(s);
    };
}
#[no_mangle]
pub unsafe extern "C" fn server_destroy_pane(
    mut wp: *mut window_pane,
    mut notify: libc::c_int,
) {
    let mut w: *mut window = (*wp).window;
    let mut ctx: screen_write_ctx = screen_write_ctx {
        wp: 0 as *mut window_pane,
        s: 0 as *mut screen,
        item: 0 as *mut screen_write_collect_item,
        list: 0 as *mut screen_write_collect_line,
        scrolled: 0,
        bg: 0,
        cells: 0,
        written: 0,
        skipped: 0,
    };
    let mut gc: grid_cell = grid_cell {
        flags: 0,
        attr: 0,
        fg: 0,
        bg: 0,
        data: utf8_data {
            data: [0; 9],
            have: 0,
            size: 0,
            width: 0,
        },
    };
    let mut t: time_t = 0;
    let mut tim: [libc::c_char; 26] = [0; 26];
    if (*wp).fd != -(1 as libc::c_int) {
        bufferevent_free((*wp).event);
        close((*wp).fd);
        (*wp).fd = -(1 as libc::c_int);
    }
    if options_get_number(
        (*w).options,
        b"remain-on-exit\0" as *const u8 as *const libc::c_char,
    ) != 0
    {
        if !(*wp).flags & 0x200 as libc::c_int != 0 {
            return;
        }
        if (*wp).flags & 0x400 as libc::c_int != 0 {
            return;
        }
        (*wp).flags |= 0x400 as libc::c_int;
        if notify != 0 {
            notify_pane(b"pane-died\0" as *const u8 as *const libc::c_char, wp);
        }
        screen_write_start(&mut ctx, wp, &mut (*wp).base);
        screen_write_scrollregion(
            &mut ctx,
            0 as libc::c_int as u_int,
            ((*(*ctx.s).grid).sy).wrapping_sub(1 as libc::c_int as u_int),
        );
        screen_write_cursormove(
            &mut ctx,
            0 as libc::c_int as u_int,
            ((*(*ctx.s).grid).sy).wrapping_sub(1 as libc::c_int as u_int),
        );
        screen_write_linefeed(&mut ctx, 1 as libc::c_int, 8 as libc::c_int as u_int);
        memcpy(
            &mut gc as *mut grid_cell as *mut libc::c_void,
            &grid_default_cell as *const grid_cell as *const libc::c_void,
            ::core::mem::size_of::<grid_cell>() as libc::c_ulong,
        );
        time(&mut t);
        ctime_r(&mut t, tim.as_mut_ptr());
        if (*wp).status & 0x7f as libc::c_int == 0 as libc::c_int {
            screen_write_nputs(
                &mut ctx as *mut screen_write_ctx,
                -(1 as libc::c_int) as ssize_t,
                &mut gc as *mut grid_cell,
                b"Pane is dead (status %d, %s)\0" as *const u8 as *const libc::c_char,
                ((*wp).status & 0xff00 as libc::c_int) >> 8 as libc::c_int,
                tim.as_mut_ptr(),
            );
        } else if (((*wp).status & 0x7f as libc::c_int) + 1 as libc::c_int)
            as libc::c_schar as libc::c_int >> 1 as libc::c_int > 0 as libc::c_int
        {
            screen_write_nputs(
                &mut ctx as *mut screen_write_ctx,
                -(1 as libc::c_int) as ssize_t,
                &mut gc as *mut grid_cell,
                b"Pane is dead (signal %d, %s)\0" as *const u8 as *const libc::c_char,
                (*wp).status & 0x7f as libc::c_int,
                tim.as_mut_ptr(),
            );
        }
        screen_write_stop(&mut ctx);
        (*wp).flags |= 0x1 as libc::c_int;
        return;
    }
    if notify != 0 {
        notify_pane(b"pane-exited\0" as *const u8 as *const libc::c_char, wp);
    }
    server_unzoom_window(w);
    layout_close_pane(wp);
    window_remove_pane(w, wp);
    if ((*w).panes.tqh_first).is_null() {
        server_kill_window(w);
    } else {
        server_redraw_window(w);
    };
}
unsafe extern "C" fn server_destroy_session_group(mut s: *mut session) {
    let mut sg: *mut session_group = 0 as *mut session_group;
    let mut s1: *mut session = 0 as *mut session;
    sg = session_group_contains(s);
    if sg.is_null() {
        server_destroy_session(s);
    } else {
        s = (*sg).sessions.tqh_first;
        while !s.is_null()
            && {
                s1 = (*s).gentry.tqe_next;
                1 as libc::c_int != 0
            }
        {
            server_destroy_session(s);
            session_destroy(
                s,
                (*::core::mem::transmute::<
                    &[u8; 29],
                    &[libc::c_char; 29],
                >(b"server_destroy_session_group\0"))
                    .as_ptr(),
            );
            s = s1;
        }
    };
}
unsafe extern "C" fn server_next_session(mut s: *mut session) -> *mut session {
    let mut s_loop: *mut session = 0 as *mut session;
    let mut s_out: *mut session = 0 as *mut session;
    s_out = 0 as *mut session;
    s_loop = sessions_RB_MINMAX(&mut sessions, -(1 as libc::c_int));
    while !s_loop.is_null() {
        if !(s_loop == s) {
            if s_out.is_null()
                || (if (*s_loop).activity_time.tv_sec == (*s_out).activity_time.tv_sec {
                    ((*s_loop).activity_time.tv_usec < (*s_out).activity_time.tv_usec)
                        as libc::c_int
                } else {
                    ((*s_loop).activity_time.tv_sec < (*s_out).activity_time.tv_sec)
                        as libc::c_int
                }) != 0
            {
                s_out = s_loop;
            }
        }
        s_loop = sessions_RB_NEXT(s_loop);
    }
    return s_out;
}
#[no_mangle]
pub unsafe extern "C" fn server_destroy_session(mut s: *mut session) {
    let mut c: *mut client = 0 as *mut client;
    let mut s_new: *mut session = 0 as *mut session;
    if options_get_number(
        (*s).options,
        b"detach-on-destroy\0" as *const u8 as *const libc::c_char,
    ) == 0
    {
        s_new = server_next_session(s);
    } else {
        s_new = 0 as *mut session;
    }
    c = clients.tqh_first;
    while !c.is_null() {
        if !((*c).session != s) {
            if s_new.is_null() {
                (*c).session = 0 as *mut session;
                (*c).flags |= 0x4 as libc::c_int;
            } else {
                (*c).last_session = 0 as *mut session;
                (*c).session = s_new;
                server_client_set_key_table(c, 0 as *const libc::c_char);
                status_timer_start(c);
                notify_client(
                    b"client-session-changed\0" as *const u8 as *const libc::c_char,
                    c,
                );
                session_update_activity(s_new, 0 as *mut timeval);
                gettimeofday(&mut (*s_new).last_attached_time, 0 as *mut libc::c_void);
                server_redraw_client(c);
                alerts_check_session(s_new);
            }
        }
        c = (*c).entry.tqe_next;
    }
    recalculate_sizes();
}
#[no_mangle]
pub unsafe extern "C" fn server_check_unattached() {
    let mut s: *mut session = 0 as *mut session;
    s = sessions_RB_MINMAX(&mut sessions, -(1 as libc::c_int));
    while !s.is_null() {
        if !((*s).flags & 0x1 as libc::c_int == 0) {
            if options_get_number(
                (*s).options,
                b"destroy-unattached\0" as *const u8 as *const libc::c_char,
            ) != 0
            {
                session_destroy(
                    s,
                    (*::core::mem::transmute::<
                        &[u8; 24],
                        &[libc::c_char; 24],
                    >(b"server_check_unattached\0"))
                        .as_ptr(),
                );
            }
        }
        s = sessions_RB_NEXT(s);
    }
}
#[no_mangle]
pub unsafe extern "C" fn server_set_stdin_callback(
    mut c: *mut client,
    mut cb: Option::<
        unsafe extern "C" fn(*mut client, libc::c_int, *mut libc::c_void) -> (),
    >,
    mut cb_data: *mut libc::c_void,
    mut cause: *mut *mut libc::c_char,
) -> libc::c_int {
    if c.is_null() || !((*c).session).is_null() {
        *cause = xstrdup(b"no client with stdin\0" as *const u8 as *const libc::c_char);
        return -(1 as libc::c_int);
    }
    if (*c).flags & 0x1 as libc::c_int != 0 {
        *cause = xstrdup(b"stdin is a tty\0" as *const u8 as *const libc::c_char);
        return -(1 as libc::c_int);
    }
    if ((*c).stdin_callback).is_some() {
        *cause = xstrdup(b"stdin in use\0" as *const u8 as *const libc::c_char);
        return -(1 as libc::c_int);
    }
    (*c).stdin_callback_data = cb_data;
    (*c).stdin_callback = cb;
    (*c).references += 1;
    (*c).references;
    if (*c).stdin_closed != 0 {
        ((*c).stdin_callback)
            .expect(
                "non-null function pointer",
            )(c, 1 as libc::c_int, (*c).stdin_callback_data);
    }
    proc_send(
        (*c).peer,
        MSG_STDIN,
        -(1 as libc::c_int),
        0 as *const libc::c_void,
        0 as libc::c_int as size_t,
    );
    return 0 as libc::c_int;
}
#[no_mangle]
pub unsafe extern "C" fn server_unzoom_window(mut w: *mut window) {
    if window_unzoom(w) == 0 as libc::c_int {
        server_redraw_window(w);
    }
}
