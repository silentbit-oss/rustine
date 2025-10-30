extern int BSDopterr
/*** DEPENDENCIES:
***/


extern int BSDoptind
/*** DEPENDENCIES:
***/


extern int BSDoptopt
/*** DEPENDENCIES:
***/


extern int BSDoptreset
/*** DEPENDENCIES:
***/


extern char *BSDoptarg
/*** DEPENDENCIES:
***/


extern char **environ
/*** DEPENDENCIES:
***/


extern struct timeval start_time
/*** DEPENDENCIES:
***/


extern const char *socket_path
/*** DEPENDENCIES:
***/


extern const char *shell_command
/*** DEPENDENCIES:
***/


extern int ptm_fd
/*** DEPENDENCIES:
***/


extern int cfg_finished
/*** DEPENDENCIES:
***/


extern const char window_clock_table[14][5][5]
/*** DEPENDENCIES:
***/


static int alerts_fired
/*** DEPENDENCIES:
***/


static char *cfg_file
/*** DEPENDENCIES:
***/


extern char **cfg_causes
/*** DEPENDENCIES:
***/


extern u_int cfg_ncauses
/*** DEPENDENCIES:
***/


static int client_flags
/*** DEPENDENCIES:
***/


static struct event client_stdin
/*** DEPENDENCIES:
***/


static enum 
{
  CLIENT_EXIT_NONE,
  CLIENT_EXIT_DETACHED,
  CLIENT_EXIT_DETACHED_HUP,
  CLIENT_EXIT_LOST_TTY,
  CLIENT_EXIT_TERMINATED,
  CLIENT_EXIT_LOST_SERVER,
  CLIENT_EXIT_EXITED,
  CLIENT_EXIT_SERVER_EXITED
} client_exitreason = CLIENT_EXIT_NONE
/*** DEPENDENCIES:
***/


static int client_exitval
/*** DEPENDENCIES:
***/


static const char *client_exitsession
/*** DEPENDENCIES:
***/


static const char *client_execshell
/*** DEPENDENCIES:
***/


static const char *client_execcmd
/*** DEPENDENCIES:
***/


static int client_attached
/*** DEPENDENCIES:
***/


static const char *cmd_find_session_table[][2] = {{0, 0}}
/*** DEPENDENCIES:
***/


static const char *cmd_find_window_table[][2] = {{"{start}", "^"}, {"{last}", "!"}, {"{end}", "$"}, {"{next}", "+"}, {"{previous}", "-"}, {0, 0}}
/*** DEPENDENCIES:
***/


static const char *cmd_find_pane_table[][2] = {{"{last}", "!"}, {"{next}", "+"}, {"{previous}", "-"}, {"{top}", "top"}, {"{bottom}", "bottom"}, {"{left}", "left"}, {"{right}", "right"}, {"{top-left}", "top-left"}, {"{top-right}", "top-right"}, {"{bottom-left}", "bottom-left"}, {"{bottom-right}", "bottom-right"}, {"{up-of}", "{up-of}"}, {"{down-of}", "{down-of}"}, {"{left-of}", "{left-of}"}, {"{right-of}", "{right-of}"}, {0, 0}}
/*** DEPENDENCIES:
***/


static struct event format_job_event
/*** DEPENDENCIES:
***/


static const char *format_upper[] = {0, 0, 0, "pane_id", 0, "window_flags", 0, "host", "window_index", 0, 0, 0, 0, 0, 0, "pane_index", 0, 0, "session_name", "pane_title", 0, 0, "window_name", 0, 0, 0}
/*** DEPENDENCIES:
***/


static const char *format_lower[] = {0, 0, 0, 0, 0, 0, 0, "host_short", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
/*** DEPENDENCIES:
***/


static FILE *log_file
/*** DEPENDENCIES:
***/


static int log_level
/*** DEPENDENCIES:
***/


static const char *options_table_mode_keys_list[] = {"emacs", "vi", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_clock_mode_style_list[] = {"12", "24", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_status_keys_list[] = {"emacs", "vi", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_status_justify_list[] = {"left", "centre", "right", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_status_position_list[] = {"top", "bottom", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_bell_action_list[] = {"none", "any", "current", "other", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_visual_bell_list[] = {"off", "on", "both", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_pane_status_list[] = {"off", "top", "bottom", 0}
/*** DEPENDENCIES:
***/


static const char *options_table_set_clipboard_list[] = {"off", "external", "on", 0}
/*** DEPENDENCIES:
***/


static u_int paste_next_index
/*** DEPENDENCIES:
***/


static u_int paste_next_order
/*** DEPENDENCIES:
***/


static u_int paste_num_automatic
/*** DEPENDENCIES:
***/


static int server_fd
/*** DEPENDENCIES:
***/


static int server_exit
/*** DEPENDENCIES:
***/


static struct event server_ev_accept
/*** DEPENDENCIES:
***/


static u_int next_session_id
/*** DEPENDENCIES:
***/


static char **status_prompt_hlist
/*** DEPENDENCIES:
***/


static u_int status_prompt_hsize
/*** DEPENDENCIES:
***/


static int tty_log_fd = -1
/*** DEPENDENCIES:
***/


static const char *window_buffer_sort_list[] = {"time", "name", "size"}
/*** DEPENDENCIES:
***/


static const char *window_client_sort_list[] = {"name", "size", "creation", "activity"}
/*** DEPENDENCIES:
***/


static const char *window_tree_sort_list[] = {"index", "name", "time"}
/*** DEPENDENCIES:
***/


static u_int next_window_pane_id
/*** DEPENDENCIES:
***/


static u_int next_window_id
/*** DEPENDENCIES:
***/


static u_int next_active_point
/*** DEPENDENCIES:
***/


int imsg_fd_overhead = 0
/*** DEPENDENCIES:
***/


extern struct hooks *global_hooks
/*** DEPENDENCIES:
None
----------------------------
***/


extern struct options *global_w_options
/*** DEPENDENCIES:
None
----------------------------
***/


extern struct environ *global_environ
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct options_table_entry options_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


extern struct joblist all_jobs
/*** DEPENDENCIES:
struct joblist
{
  struct job *lh_first;
}
----------------------------
***/


extern struct tty_terms tty_terms
/*** DEPENDENCIES:
struct tty_terms
{
  struct tty_term *lh_first;
}
----------------------------
***/


extern const struct cmd_entry *cmd_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


extern struct key_tables key_tables
/*** DEPENDENCIES:
struct key_tables
{
  struct key_table *rbh_root;
}
----------------------------
***/


extern struct tmuxproc *server_proc
/*** DEPENDENCIES:
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
}
----------------------------
***/


extern struct clients clients
/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
***/


extern struct cmd_find_state marked_pane
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct grid_cell grid_default_cell
/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
***/


extern struct windows windows
/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
***/


extern struct window_pane_tree all_window_panes
/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
***/


extern const struct window_mode window_buffer_mode
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct window_mode window_tree_mode
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct window_mode window_clock_mode
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct window_mode window_client_mode
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct window_mode window_copy_mode
/*** DEPENDENCIES:
None
----------------------------
***/


extern struct sessions sessions
/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
***/


extern struct session_groups session_groups
/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
***/


static struct 
{
  struct window *tqh_first;
  struct window **tqh_last;
} alerts_list = {0, &alerts_list.tqh_first}
/*** DEPENDENCIES:
None
----------------------------
***/


static struct cmdq_item *cfg_item
/*** DEPENDENCIES:
None
----------------------------
***/


static struct tmuxpeer *client_peer
/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
***/


static enum msgtype client_exittype
/*** DEPENDENCIES:
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
}
----------------------------
***/


extern const struct cmd_entry cmd_attach_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_bind_key_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_break_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_capture_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_clear_history_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_choose_tree_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_choose_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_choose_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_command_prompt_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_confirm_before_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_copy_mode_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_clock_mode_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_detach_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_suspend_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_display_message_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_display_panes_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_find_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_if_shell_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_join_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_move_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_kill_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_kill_server_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_start_server_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_kill_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_kill_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_unlink_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_buffers_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_clients_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_keys_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_commands_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_panes_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_sessions_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_list_windows_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_load_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_lock_server_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_lock_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_lock_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_move_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_link_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_new_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_has_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_new_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_paste_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_pipe_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


static struct cmdq_list global_queue = {0, &global_queue.tqh_first}
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_refresh_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_rename_session_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_rename_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_resize_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_respawn_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_respawn_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_rotate_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_run_shell_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_save_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_select_layout_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_next_layout_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_previous_layout_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_select_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_last_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_select_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_next_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_previous_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_last_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_send_keys_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_send_prefix_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_set_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_delete_buffer_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_set_environment_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_set_hook_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_hooks_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_set_option_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_set_window_option_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_environment_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_messages_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_options_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_show_window_options_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_source_file_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_split_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_swap_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_swap_window_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_switch_client_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_unbind_key_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_wait_for_entry
/*** DEPENDENCIES:
None
----------------------------
***/


static struct wait_channels wait_channels = {0}
/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
***/


extern const struct cmd_entry cmd_down_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


extern const struct cmd_entry cmd_up_pane_entry
/*** DEPENDENCIES:
None
----------------------------
***/


static struct format_job_tree
{
  struct format_job *rbh_root;
} format_jobs = {0}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct grid_cell_entry grid_default_entry = {0, {.data = {0, 8, 8, ' '}}}
/*** DEPENDENCIES:
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
***/


static const struct input_key_ent input_keys[] = {{KEYC_BSPACE, "\177", 0}, {KEYC_PASTE_START, "\033[200~", 0}, {KEYC_PASTE_END, "\033[201~", 0}, {KEYC_F1, "\033OP", 0}, {KEYC_F2, "\033OQ", 0}, {KEYC_F3, "\033OR", 0}, {KEYC_F4, "\033OS", 0}, {KEYC_F5, "\033[15~", 0}, {KEYC_F6, "\033[17~", 0}, {KEYC_F7, "\033[18~", 0}, {KEYC_F8, "\033[19~", 0}, {KEYC_F9, "\033[20~", 0}, {KEYC_F10, "\033[21~", 0}, {KEYC_F11, "\033[23~", 0}, {KEYC_F12, "\033[24~", 0}, {KEYC_F1 | 0x800000000000ULL, "\033[25~", 0}, {KEYC_F2 | 0x800000000000ULL, "\033[26~", 0}, {KEYC_F3 | 0x800000000000ULL, "\033[28~", 0}, {KEYC_F4 | 0x800000000000ULL, "\033[29~", 0}, {KEYC_F5 | 0x800000000000ULL, "\033[31~", 0}, {KEYC_F6 | 0x800000000000ULL, "\033[32~", 0}, {KEYC_F7 | 0x800000000000ULL, "\033[33~", 0}, {KEYC_F8 | 0x800000000000ULL, "\033[34~", 0}, {KEYC_IC, "\033[2~", 0}, {KEYC_DC, "\033[3~", 0}, {KEYC_HOME, "\033[1~", 0}, {KEYC_END, "\033[4~", 0}, {KEYC_NPAGE, "\033[6~", 0}, {KEYC_PPAGE, "\033[5~", 0}, {KEYC_BTAB, "\033[Z", 0}, {KEYC_UP | 0x400000000000ULL, "\033[A", 0x2}, {KEYC_DOWN | 0x400000000000ULL, "\033[B", 0x2}, {KEYC_RIGHT | 0x400000000000ULL, "\033[C", 0x2}, {KEYC_LEFT | 0x400000000000ULL, "\033[D", 0x2}, {KEYC_UP, "\033OA", 0x2}, {KEYC_DOWN, "\033OB", 0x2}, {KEYC_RIGHT, "\033OC", 0x2}, {KEYC_LEFT, "\033OD", 0x2}, {KEYC_UP | 0x400000000000ULL, "\033OA", 0}, {KEYC_DOWN | 0x400000000000ULL, "\033OB", 0}, {KEYC_RIGHT | 0x400000000000ULL, "\033OC", 0}, {KEYC_LEFT | 0x400000000000ULL, "\033OD", 0}, {KEYC_UP, "\033[A", 0}, {KEYC_DOWN, "\033[B", 0}, {KEYC_RIGHT, "\033[C", 0}, {KEYC_LEFT, "\033[D", 0}, {KEYC_KP_SLASH, "\033Oo", 0x1}, {KEYC_KP_STAR, "\033Oj", 0x1}, {KEYC_KP_MINUS, "\033Om", 0x1}, {KEYC_KP_SEVEN, "\033Ow", 0x1}, {KEYC_KP_EIGHT, "\033Ox", 0x1}, {KEYC_KP_NINE, "\033Oy", 0x1}, {KEYC_KP_PLUS, "\033Ok", 0x1}, {KEYC_KP_FOUR, "\033Ot", 0x1}, {KEYC_KP_FIVE, "\033Ou", 0x1}, {KEYC_KP_SIX, "\033Ov", 0x1}, {KEYC_KP_ONE, "\033Oq", 0x1}, {KEYC_KP_TWO, "\033Or", 0x1}, {KEYC_KP_THREE, "\033Os", 0x1}, {KEYC_KP_ENTER, "\033OM", 0x1}, {KEYC_KP_ZERO, "\033Op", 0x1}, {KEYC_KP_PERIOD, "\033On", 0x1}, {KEYC_KP_SLASH, "/", 0}, {KEYC_KP_STAR, "*", 0}, {KEYC_KP_MINUS, "-", 0}, {KEYC_KP_SEVEN, "7", 0}, {KEYC_KP_EIGHT, "8", 0}, {KEYC_KP_NINE, "9", 0}, {KEYC_KP_PLUS, "+", 0}, {KEYC_KP_FOUR, "4", 0}, {KEYC_KP_FIVE, "5", 0}, {KEYC_KP_SIX, "6", 0}, {KEYC_KP_ONE, "1", 0}, {KEYC_KP_TWO, "2", 0}, {KEYC_KP_THREE, "3", 0}, {KEYC_KP_ENTER, "\n", 0}, {KEYC_KP_ZERO, "0", 0}, {KEYC_KP_PERIOD, ".", 0}}
/*** DEPENDENCIES:
struct input_key_ent
{
  key_code key;
  const char *data;
  int flags;
}
----------------------------
***/


static const struct input_table_entry input_esc_table[] = {{'0', "(", INPUT_ESC_SCSG0_ON}, {'0', ")", INPUT_ESC_SCSG1_ON}, {'7', "", INPUT_ESC_DECSC}, {'8', "", INPUT_ESC_DECRC}, {'8', "#", INPUT_ESC_DECALN}, {'=', "", INPUT_ESC_DECKPAM}, {'>', "", INPUT_ESC_DECKPNM}, {'B', "(", INPUT_ESC_SCSG0_OFF}, {'B', ")", INPUT_ESC_SCSG1_OFF}, {'D', "", INPUT_ESC_IND}, {'E', "", INPUT_ESC_NEL}, {'H', "", INPUT_ESC_HTS}, {'M', "", INPUT_ESC_RI}, {'\\', "", INPUT_ESC_ST}, {'c', "", INPUT_ESC_RIS}}
/*** DEPENDENCIES:
struct input_table_entry
{
  int ch;
  const char *interm;
  int type;
}
----------------------------
***/


static const struct input_table_entry input_csi_table[] = {{'@', "", INPUT_CSI_ICH}, {'A', "", INPUT_CSI_CUU}, {'B', "", INPUT_CSI_CUD}, {'C', "", INPUT_CSI_CUF}, {'D', "", INPUT_CSI_CUB}, {'E', "", INPUT_CSI_CNL}, {'F', "", INPUT_CSI_CPL}, {'G', "", INPUT_CSI_HPA}, {'H', "", INPUT_CSI_CUP}, {'J', "", INPUT_CSI_ED}, {'K', "", INPUT_CSI_EL}, {'L', "", INPUT_CSI_IL}, {'M', "", INPUT_CSI_DL}, {'P', "", INPUT_CSI_DCH}, {'S', "", INPUT_CSI_SU}, {'X', "", INPUT_CSI_ECH}, {'Z', "", INPUT_CSI_CBT}, {'b', "", INPUT_CSI_REP}, {'c', "", INPUT_CSI_DA}, {'c', ">", INPUT_CSI_DA_TWO}, {'d', "", INPUT_CSI_VPA}, {'f', "", INPUT_CSI_CUP}, {'g', "", INPUT_CSI_TBC}, {'h', "", INPUT_CSI_SM}, {'h', "?", INPUT_CSI_SM_PRIVATE}, {'l', "", INPUT_CSI_RM}, {'l', "?", INPUT_CSI_RM_PRIVATE}, {'m', "", INPUT_CSI_SGR}, {'n', "", INPUT_CSI_DSR}, {'q', " ", INPUT_CSI_DECSCUSR}, {'r', "", INPUT_CSI_DECSTBM}, {'s', "", INPUT_CSI_SCP}, {'t', "", INPUT_CSI_WINOPS}, {'u', "", INPUT_CSI_RCP}}
/*** DEPENDENCIES:
struct input_table_entry
{
  int ch;
  const char *interm;
  int type;
}
----------------------------
***/


static const struct input_transition input_state_ground_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_esc_enter_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_esc_intermediate_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_csi_enter_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_csi_parameter_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_csi_intermediate_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_csi_ignore_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_enter_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_parameter_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_intermediate_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_handler_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_escape_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_dcs_ignore_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_osc_string_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_apc_string_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_rename_string_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_transition input_state_consume_st_table[]
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_esc_intermediate = {"esc_intermediate", 0, 0, input_state_esc_intermediate_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_csi_parameter = {"csi_parameter", 0, 0, input_state_csi_parameter_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_csi_intermediate = {"csi_intermediate", 0, 0, input_state_csi_intermediate_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_csi_ignore = {"csi_ignore", 0, 0, input_state_csi_ignore_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_dcs_parameter = {"dcs_parameter", 0, 0, input_state_dcs_parameter_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_dcs_intermediate = {"dcs_intermediate", 0, 0, input_state_dcs_intermediate_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_dcs_handler = {"dcs_handler", 0, 0, input_state_dcs_handler_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_dcs_escape = {"dcs_escape", 0, 0, input_state_dcs_escape_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct input_state input_state_dcs_ignore = {"dcs_ignore", 0, 0, input_state_dcs_ignore_table}
/*** DEPENDENCIES:
None
----------------------------
***/


static const struct 
{
  const char *string;
  key_code key;
} key_string_table[] = {{"F1", KEYC_F1}, {"F2", KEYC_F2}, {"F3", KEYC_F3}, {"F4", KEYC_F4}, {"F5", KEYC_F5}, {"F6", KEYC_F6}, {"F7", KEYC_F7}, {"F8", KEYC_F8}, {"F9", KEYC_F9}, {"F10", KEYC_F10}, {"F11", KEYC_F11}, {"F12", KEYC_F12}, {"IC", KEYC_IC}, {"DC", KEYC_DC}, {"Home", KEYC_HOME}, {"End", KEYC_END}, {"NPage", KEYC_NPAGE}, {"PageDown", KEYC_NPAGE}, {"PgDn", KEYC_NPAGE}, {"PPage", KEYC_PPAGE}, {"PageUp", KEYC_PPAGE}, {"PgUp", KEYC_PPAGE}, {"Tab", '\011'}, {"BTab", KEYC_BTAB}, {"Space", ' '}, {"BSpace", KEYC_BSPACE}, {"Enter", '\r'}, {"Escape", '\033'}, {"Up", KEYC_UP}, {"Down", KEYC_DOWN}, {"Left", KEYC_LEFT}, {"Right", KEYC_RIGHT}, {"KP/", KEYC_KP_SLASH}, {"KP*", KEYC_KP_STAR}, {"KP-", KEYC_KP_MINUS}, {"KP7", KEYC_KP_SEVEN}, {"KP8", KEYC_KP_EIGHT}, {"KP9", KEYC_KP_NINE}, {"KP+", KEYC_KP_PLUS}, {"KP4", KEYC_KP_FOUR}, {"KP5", KEYC_KP_FIVE}, {"KP6", KEYC_KP_SIX}, {"KP1", KEYC_KP_ONE}, {"KP2", KEYC_KP_TWO}, {"KP3", KEYC_KP_THREE}, {"KPEnter", KEYC_KP_ENTER}, {"KP0", KEYC_KP_ZERO}, {"KP.", KEYC_KP_PERIOD}, {"MouseDown1Pane", KEYC_MOUSEDOWN1_PANE}, {"MouseDown1Status", KEYC_MOUSEDOWN1_STATUS}, {"MouseDown1Border", KEYC_MOUSEDOWN1_BORDER}, {"MouseDown2Pane", KEYC_MOUSEDOWN2_PANE}, {"MouseDown2Status", KEYC_MOUSEDOWN2_STATUS}, {"MouseDown2Border", KEYC_MOUSEDOWN2_BORDER}, {"MouseDown3Pane", KEYC_MOUSEDOWN3_PANE}, {"MouseDown3Status", KEYC_MOUSEDOWN3_STATUS}, {"MouseDown3Border", KEYC_MOUSEDOWN3_BORDER}, {"MouseUp1Pane", KEYC_MOUSEUP1_PANE}, {"MouseUp1Status", KEYC_MOUSEUP1_STATUS}, {"MouseUp1Border", KEYC_MOUSEUP1_BORDER}, {"MouseUp2Pane", KEYC_MOUSEUP2_PANE}, {"MouseUp2Status", KEYC_MOUSEUP2_STATUS}, {"MouseUp2Border", KEYC_MOUSEUP2_BORDER}, {"MouseUp3Pane", KEYC_MOUSEUP3_PANE}, {"MouseUp3Status", KEYC_MOUSEUP3_STATUS}, {"MouseUp3Border", KEYC_MOUSEUP3_BORDER}, {"MouseDrag1Pane", KEYC_MOUSEDRAG1_PANE}, {"MouseDrag1Status", KEYC_MOUSEDRAG1_STATUS}, {"MouseDrag1Border", KEYC_MOUSEDRAG1_BORDER}, {"MouseDrag2Pane", KEYC_MOUSEDRAG2_PANE}, {"MouseDrag2Status", KEYC_MOUSEDRAG2_STATUS}, {"MouseDrag2Border", KEYC_MOUSEDRAG2_BORDER}, {"MouseDrag3Pane", KEYC_MOUSEDRAG3_PANE}, {"MouseDrag3Status", KEYC_MOUSEDRAG3_STATUS}, {"MouseDrag3Border", KEYC_MOUSEDRAG3_BORDER}, {"MouseDragEnd1Pane", KEYC_MOUSEDRAGEND1_PANE}, {"MouseDragEnd1Status", KEYC_MOUSEDRAGEND1_STATUS}, {"MouseDragEnd1Border", KEYC_MOUSEDRAGEND1_BORDER}, {"MouseDragEnd2Pane", KEYC_MOUSEDRAGEND2_PANE}, {"MouseDragEnd2Status", KEYC_MOUSEDRAGEND2_STATUS}, {"MouseDragEnd2Border", KEYC_MOUSEDRAGEND2_BORDER}, {"MouseDragEnd3Pane", KEYC_MOUSEDRAGEND3_PANE}, {"MouseDragEnd3Status", KEYC_MOUSEDRAGEND3_STATUS}, {"MouseDragEnd3Border", KEYC_MOUSEDRAGEND3_BORDER}, {"WheelUpPane", KEYC_WHEELUP_PANE}, {"WheelUpStatus", KEYC_WHEELUP_STATUS}, {"WheelUpBorder", KEYC_WHEELUP_BORDER}, {"WheelDownPane", KEYC_WHEELDOWN_PANE}, {"WheelDownStatus", KEYC_WHEELDOWN_STATUS}, {"WheelDownBorder", KEYC_WHEELDOWN_BORDER}, {"DoubleClick1Pane", KEYC_DOUBLECLICK1_PANE}, {"DoubleClick1Status", KEYC_DOUBLECLICK1_STATUS}, {"DoubleClick1Border", KEYC_DOUBLECLICK1_BORDER}, {"DoubleClick2Pane", KEYC_DOUBLECLICK2_PANE}, {"DoubleClick2Status", KEYC_DOUBLECLICK2_STATUS}, {"DoubleClick2Border", KEYC_DOUBLECLICK2_BORDER}, {"DoubleClick3Pane", KEYC_DOUBLECLICK3_PANE}, {"DoubleClick3Status", KEYC_DOUBLECLICK3_STATUS}, {"DoubleClick3Border", KEYC_DOUBLECLICK3_BORDER}, {"TripleClick1Pane", KEYC_TRIPLECLICK1_PANE}, {"TripleClick1Status", KEYC_TRIPLECLICK1_STATUS}, {"TripleClick1Border", KEYC_TRIPLECLICK1_BORDER}, {"TripleClick2Pane", KEYC_TRIPLECLICK2_PANE}, {"TripleClick2Status", KEYC_TRIPLECLICK2_STATUS}, {"TripleClick2Border", KEYC_TRIPLECLICK2_BORDER}, {"TripleClick3Pane", KEYC_TRIPLECLICK3_PANE}, {"TripleClick3Status", KEYC_TRIPLECLICK3_STATUS}, {"TripleClick3Border", KEYC_TRIPLECLICK3_BORDER}}
/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
/*** DEPENDENCIES:
struct paste_buffer
{
  char *data;
  size_t size;
  char *name;
  time_t created;
  int automatic;
  u_int order;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } name_entry;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } time_entry;
}
----------------------------
***/


static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
/*** DEPENDENCIES:
struct paste_buffer
{
  char *data;
  size_t size;
  char *name;
  time_t created;
  int automatic;
  u_int order;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } name_entry;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } time_entry;
}
----------------------------
***/


static const struct grid_cell screen_write_pad_cell = {0x4, 0, 8, 8, {{0}, 0, 0, 0}}
/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
***/


static const struct tty_acs_entry tty_acs_table[] = {{'+', "\342\206\222"}, {',', "\342\206\220"}, {'-', "\342\206\221"}, {'.', "\342\206\223"}, {'0', "\342\226\256"}, {'`', "\342\227\206"}, {'a', "\342\226\222"}, {'f', "\302\260"}, {'g', "\302\261"}, {'h', "\342\226\222"}, {'i', "\342\230\203"}, {'j', "\342\224\230"}, {'k', "\342\224\220"}, {'l', "\342\224\214"}, {'m', "\342\224\224"}, {'n', "\342\224\274"}, {'o', "\342\216\272"}, {'p', "\342\216\273"}, {'q', "\342\224\200"}, {'r', "\342\216\274"}, {'s', "\342\216\275"}, {'t', "\342\224\234"}, {'u', "\342\224\244"}, {'v', "\342\224\264"}, {'w', "\342\224\254"}, {'x', "\342\224\202"}, {'y', "\342\211\244"}, {'z', "\342\211\245"}, {'{', "\317\200"}, {'|', "\342\211\240"}, {'}', "\302\243"}, {'~', "\302\267"}}
/*** DEPENDENCIES:
struct tty_acs_entry
{
  u_char key;
  const char *string;
}
----------------------------
***/


static const struct tty_default_key_raw tty_default_raw_keys[] = {{"\033Oo", KEYC_KP_SLASH}, {"\033Oj", KEYC_KP_STAR}, {"\033Om", KEYC_KP_MINUS}, {"\033Ow", KEYC_KP_SEVEN}, {"\033Ox", KEYC_KP_EIGHT}, {"\033Oy", KEYC_KP_NINE}, {"\033Ok", KEYC_KP_PLUS}, {"\033Ot", KEYC_KP_FOUR}, {"\033Ou", KEYC_KP_FIVE}, {"\033Ov", KEYC_KP_SIX}, {"\033Oq", KEYC_KP_ONE}, {"\033Or", KEYC_KP_TWO}, {"\033Os", KEYC_KP_THREE}, {"\033OM", KEYC_KP_ENTER}, {"\033Op", KEYC_KP_ZERO}, {"\033On", KEYC_KP_PERIOD}, {"\033OA", KEYC_UP}, {"\033OB", KEYC_DOWN}, {"\033OC", KEYC_RIGHT}, {"\033OD", KEYC_LEFT}, {"\033[A", KEYC_UP}, {"\033[B", KEYC_DOWN}, {"\033[C", KEYC_RIGHT}, {"\033[D", KEYC_LEFT}, {"\033OH", KEYC_HOME}, {"\033OF", KEYC_END}, {"\033[H", KEYC_HOME}, {"\033[F", KEYC_END}, {"\033Oa", KEYC_UP | 0x400000000000ULL}, {"\033Ob", KEYC_DOWN | 0x400000000000ULL}, {"\033Oc", KEYC_RIGHT | 0x400000000000ULL}, {"\033Od", KEYC_LEFT | 0x400000000000ULL}, {"\033[a", KEYC_UP | 0x800000000000ULL}, {"\033[b", KEYC_DOWN | 0x800000000000ULL}, {"\033[c", KEYC_RIGHT | 0x800000000000ULL}, {"\033[d", KEYC_LEFT | 0x800000000000ULL}, {"\033[11^", KEYC_F1 | 0x400000000000ULL}, {"\033[12^", KEYC_F2 | 0x400000000000ULL}, {"\033[13^", KEYC_F3 | 0x400000000000ULL}, {"\033[14^", KEYC_F4 | 0x400000000000ULL}, {"\033[15^", KEYC_F5 | 0x400000000000ULL}, {"\033[17^", KEYC_F6 | 0x400000000000ULL}, {"\033[18^", KEYC_F7 | 0x400000000000ULL}, {"\033[19^", KEYC_F8 | 0x400000000000ULL}, {"\033[20^", KEYC_F9 | 0x400000000000ULL}, {"\033[21^", KEYC_F10 | 0x400000000000ULL}, {"\033[23^", KEYC_F11 | 0x400000000000ULL}, {"\033[24^", KEYC_F12 | 0x400000000000ULL}, {"\033[2^", KEYC_IC | 0x400000000000ULL}, {"\033[3^", KEYC_DC | 0x400000000000ULL}, {"\033[7^", KEYC_HOME | 0x400000000000ULL}, {"\033[8^", KEYC_END | 0x400000000000ULL}, {"\033[6^", KEYC_NPAGE | 0x400000000000ULL}, {"\033[5^", KEYC_PPAGE | 0x400000000000ULL}, {"\033[11$", KEYC_F1 | 0x800000000000ULL}, {"\033[12$", KEYC_F2 | 0x800000000000ULL}, {"\033[13$", KEYC_F3 | 0x800000000000ULL}, {"\033[14$", KEYC_F4 | 0x800000000000ULL}, {"\033[15$", KEYC_F5 | 0x800000000000ULL}, {"\033[17$", KEYC_F6 | 0x800000000000ULL}, {"\033[18$", KEYC_F7 | 0x800000000000ULL}, {"\033[19$", KEYC_F8 | 0x800000000000ULL}, {"\033[20$", KEYC_F9 | 0x800000000000ULL}, {"\033[21$", KEYC_F10 | 0x800000000000ULL}, {"\033[23$", KEYC_F11 | 0x800000000000ULL}, {"\033[24$", KEYC_F12 | 0x800000000000ULL}, {"\033[2$", KEYC_IC | 0x800000000000ULL}, {"\033[3$", KEYC_DC | 0x800000000000ULL}, {"\033[7$", KEYC_HOME | 0x800000000000ULL}, {"\033[8$", KEYC_END | 0x800000000000ULL}, {"\033[6$", KEYC_NPAGE | 0x800000000000ULL}, {"\033[5$", KEYC_PPAGE | 0x800000000000ULL}, {"\033[11@", (KEYC_F1 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[12@", (KEYC_F2 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[13@", (KEYC_F3 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[14@", (KEYC_F4 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[15@", (KEYC_F5 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[17@", (KEYC_F6 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[18@", (KEYC_F7 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[19@", (KEYC_F8 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[20@", (KEYC_F9 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[21@", (KEYC_F10 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[23@", (KEYC_F11 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[24@", (KEYC_F12 | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[2@", (KEYC_IC | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[3@", (KEYC_DC | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[7@", (KEYC_HOME | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[8@", (KEYC_END | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[6@", (KEYC_NPAGE | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[5@", (KEYC_PPAGE | 0x400000000000ULL) | 0x800000000000ULL}, {"\033[I", KEYC_FOCUS_IN}, {"\033[O", KEYC_FOCUS_OUT}, {"\033[200~", KEYC_PASTE_START}, {"\033[201~", KEYC_PASTE_END}}
/*** DEPENDENCIES:
struct tty_default_key_raw
{
  const char *string;
  key_code key;
}
----------------------------
***/


static const struct tty_default_key_code tty_default_code_keys[] = {{TTYC_KF1, KEYC_F1}, {TTYC_KF2, KEYC_F2}, {TTYC_KF3, KEYC_F3}, {TTYC_KF4, KEYC_F4}, {TTYC_KF5, KEYC_F5}, {TTYC_KF6, KEYC_F6}, {TTYC_KF7, KEYC_F7}, {TTYC_KF8, KEYC_F8}, {TTYC_KF9, KEYC_F9}, {TTYC_KF10, KEYC_F10}, {TTYC_KF11, KEYC_F11}, {TTYC_KF12, KEYC_F12}, {TTYC_KF13, KEYC_F1 | 0x800000000000ULL}, {TTYC_KF14, KEYC_F2 | 0x800000000000ULL}, {TTYC_KF15, KEYC_F3 | 0x800000000000ULL}, {TTYC_KF16, KEYC_F4 | 0x800000000000ULL}, {TTYC_KF17, KEYC_F5 | 0x800000000000ULL}, {TTYC_KF18, KEYC_F6 | 0x800000000000ULL}, {TTYC_KF19, KEYC_F7 | 0x800000000000ULL}, {TTYC_KF20, KEYC_F8 | 0x800000000000ULL}, {TTYC_KF21, KEYC_F9 | 0x800000000000ULL}, {TTYC_KF22, KEYC_F10 | 0x800000000000ULL}, {TTYC_KF23, KEYC_F11 | 0x800000000000ULL}, {TTYC_KF24, KEYC_F12 | 0x800000000000ULL}, {TTYC_KF25, KEYC_F1 | 0x400000000000ULL}, {TTYC_KF26, KEYC_F2 | 0x400000000000ULL}, {TTYC_KF27, KEYC_F3 | 0x400000000000ULL}, {TTYC_KF28, KEYC_F4 | 0x400000000000ULL}, {TTYC_KF29, KEYC_F5 | 0x400000000000ULL}, {TTYC_KF30, KEYC_F6 | 0x400000000000ULL}, {TTYC_KF31, KEYC_F7 | 0x400000000000ULL}, {TTYC_KF32, KEYC_F8 | 0x400000000000ULL}, {TTYC_KF33, KEYC_F9 | 0x400000000000ULL}, {TTYC_KF34, KEYC_F10 | 0x400000000000ULL}, {TTYC_KF35, KEYC_F11 | 0x400000000000ULL}, {TTYC_KF36, KEYC_F12 | 0x400000000000ULL}, {TTYC_KF37, (KEYC_F1 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF38, (KEYC_F2 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF39, (KEYC_F3 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF40, (KEYC_F4 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF41, (KEYC_F5 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF42, (KEYC_F6 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF43, (KEYC_F7 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF44, (KEYC_F8 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF45, (KEYC_F9 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF46, (KEYC_F10 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF47, (KEYC_F11 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF48, (KEYC_F12 | 0x800000000000ULL) | 0x400000000000ULL}, {TTYC_KF49, KEYC_F1 | 0x200000000000ULL}, {TTYC_KF50, KEYC_F2 | 0x200000000000ULL}, {TTYC_KF51, KEYC_F3 | 0x200000000000ULL}, {TTYC_KF52, KEYC_F4 | 0x200000000000ULL}, {TTYC_KF53, KEYC_F5 | 0x200000000000ULL}, {TTYC_KF54, KEYC_F6 | 0x200000000000ULL}, {TTYC_KF55, KEYC_F7 | 0x200000000000ULL}, {TTYC_KF56, KEYC_F8 | 0x200000000000ULL}, {TTYC_KF57, KEYC_F9 | 0x200000000000ULL}, {TTYC_KF58, KEYC_F10 | 0x200000000000ULL}, {TTYC_KF59, KEYC_F11 | 0x200000000000ULL}, {TTYC_KF60, KEYC_F12 | 0x200000000000ULL}, {TTYC_KF61, (KEYC_F1 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KF62, (KEYC_F2 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KF63, (KEYC_F3 | 0x200000000000ULL) | 0x800000000000ULL}, {TTYC_KICH1, KEYC_IC}, {TTYC_KDCH1, KEYC_DC}, {TTYC_KHOME, KEYC_HOME}, {TTYC_KEND, KEYC_END}, {TTYC_KNP, KEYC_NPAGE}, {TTYC_KPP, KEYC_PPAGE}, {TTYC_KCBT, KEYC_BTAB}, {TTYC_KCUU1, KEYC_UP}, {TTYC_KCUD1, KEYC_DOWN}, {TTYC_KCUB1, KEYC_LEFT}, {TTYC_KCUF1, KEYC_RIGHT}, {TTYC_KDC2, (KEYC_DC | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC3, (KEYC_DC | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC4, ((KEYC_DC | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC5, (KEYC_DC | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC6, ((KEYC_DC | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDC7, ((KEYC_DC | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIND, (KEYC_DOWN | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN2, (KEYC_DOWN | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN3, (KEYC_DOWN | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN4, ((KEYC_DOWN | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN5, (KEYC_DOWN | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN6, ((KEYC_DOWN | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KDN7, ((KEYC_DOWN | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND2, (KEYC_END | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND3, (KEYC_END | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND4, ((KEYC_END | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND5, (KEYC_END | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND6, ((KEYC_END | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KEND7, ((KEYC_END | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM2, (KEYC_HOME | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM3, (KEYC_HOME | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM4, ((KEYC_HOME | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM5, (KEYC_HOME | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM6, ((KEYC_HOME | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KHOM7, ((KEYC_HOME | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC2, (KEYC_IC | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC3, (KEYC_IC | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC4, ((KEYC_IC | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC5, (KEYC_IC | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC6, ((KEYC_IC | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KIC7, ((KEYC_IC | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT2, (KEYC_LEFT | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT3, (KEYC_LEFT | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT4, ((KEYC_LEFT | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT5, (KEYC_LEFT | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT6, ((KEYC_LEFT | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KLFT7, ((KEYC_LEFT | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT2, (KEYC_NPAGE | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT3, (KEYC_NPAGE | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT4, ((KEYC_NPAGE | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT5, (KEYC_NPAGE | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT6, ((KEYC_NPAGE | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KNXT7, ((KEYC_NPAGE | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV2, (KEYC_PPAGE | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV3, (KEYC_PPAGE | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV4, ((KEYC_PPAGE | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV5, (KEYC_PPAGE | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV6, ((KEYC_PPAGE | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KPRV7, ((KEYC_PPAGE | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT2, (KEYC_RIGHT | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT3, (KEYC_RIGHT | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT4, ((KEYC_RIGHT | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT5, (KEYC_RIGHT | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT6, ((KEYC_RIGHT | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRIT7, ((KEYC_RIGHT | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KRI, (KEYC_UP | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP2, (KEYC_UP | 0x800000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP3, (KEYC_UP | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP4, ((KEYC_UP | 0x800000000000ULL) | 0x200000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP5, (KEYC_UP | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP6, ((KEYC_UP | 0x800000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}, {TTYC_KUP7, ((KEYC_UP | 0x200000000000ULL) | 0x400000000000ULL) | 0x1000000000000ULL}}
/*** DEPENDENCIES:
struct tty_default_key_code
{
  enum tty_code_code code;
  key_code key;
}
----------------------------
***/


static const struct tty_term_code_entry tty_term_codes[] = {.TTYC_ACSC = {TTYCODE_STRING, "acsc"}, .TTYC_AX = {TTYCODE_FLAG, "AX"}, .TTYC_BCE = {TTYCODE_FLAG, "bce"}, .TTYC_BEL = {TTYCODE_STRING, "bel"}, .TTYC_BLINK = {TTYCODE_STRING, "blink"}, .TTYC_BOLD = {TTYCODE_STRING, "bold"}, .TTYC_CIVIS = {TTYCODE_STRING, "civis"}, .TTYC_CLEAR = {TTYCODE_STRING, "clear"}, .TTYC_CNORM = {TTYCODE_STRING, "cnorm"}, .TTYC_COLORS = {TTYCODE_NUMBER, "colors"}, .TTYC_CR = {TTYCODE_STRING, "Cr"}, .TTYC_CSR = {TTYCODE_STRING, "csr"}, .TTYC_CS = {TTYCODE_STRING, "Cs"}, .TTYC_CUB1 = {TTYCODE_STRING, "cub1"}, .TTYC_CUB = {TTYCODE_STRING, "cub"}, .TTYC_CUD1 = {TTYCODE_STRING, "cud1"}, .TTYC_CUD = {TTYCODE_STRING, "cud"}, .TTYC_CUF1 = {TTYCODE_STRING, "cuf1"}, .TTYC_CUF = {TTYCODE_STRING, "cuf"}, .TTYC_CUP = {TTYCODE_STRING, "cup"}, .TTYC_CUU1 = {TTYCODE_STRING, "cuu1"}, .TTYC_CUU = {TTYCODE_STRING, "cuu"}, .TTYC_CVVIS = {TTYCODE_STRING, "cvvis"}, .TTYC_DCH1 = {TTYCODE_STRING, "dch1"}, .TTYC_DCH = {TTYCODE_STRING, "dch"}, .TTYC_DIM = {TTYCODE_STRING, "dim"}, .TTYC_DL1 = {TTYCODE_STRING, "dl1"}, .TTYC_DL = {TTYCODE_STRING, "dl"}, .TTYC_E3 = {TTYCODE_STRING, "E3"}, .TTYC_ECH = {TTYCODE_STRING, "ech"}, .TTYC_ED = {TTYCODE_STRING, "ed"}, .TTYC_EL1 = {TTYCODE_STRING, "el1"}, .TTYC_EL = {TTYCODE_STRING, "el"}, .TTYC_ENACS = {TTYCODE_STRING, "enacs"}, .TTYC_FSL = {TTYCODE_STRING, "fsl"}, .TTYC_HOME = {TTYCODE_STRING, "home"}, .TTYC_HPA = {TTYCODE_STRING, "hpa"}, .TTYC_ICH1 = {TTYCODE_STRING, "ich1"}, .TTYC_ICH = {TTYCODE_STRING, "ich"}, .TTYC_IL1 = {TTYCODE_STRING, "il1"}, .TTYC_IL = {TTYCODE_STRING, "il"}, .TTYC_INDN = {TTYCODE_STRING, "indn"}, .TTYC_INVIS = {TTYCODE_STRING, "invis"}, .TTYC_KCBT = {TTYCODE_STRING, "kcbt"}, .TTYC_KCUB1 = {TTYCODE_STRING, "kcub1"}, .TTYC_KCUD1 = {TTYCODE_STRING, "kcud1"}, .TTYC_KCUF1 = {TTYCODE_STRING, "kcuf1"}, .TTYC_KCUU1 = {TTYCODE_STRING, "kcuu1"}, .TTYC_KDC2 = {TTYCODE_STRING, "kDC"}, .TTYC_KDC3 = {TTYCODE_STRING, "kDC3"}, .TTYC_KDC4 = {TTYCODE_STRING, "kDC4"}, .TTYC_KDC5 = {TTYCODE_STRING, "kDC5"}, .TTYC_KDC6 = {TTYCODE_STRING, "kDC6"}, .TTYC_KDC7 = {TTYCODE_STRING, "kDC7"}, .TTYC_KDCH1 = {TTYCODE_STRING, "kdch1"}, .TTYC_KDN2 = {TTYCODE_STRING, "kDN"}, .TTYC_KDN3 = {TTYCODE_STRING, "kDN3"}, .TTYC_KDN4 = {TTYCODE_STRING, "kDN4"}, .TTYC_KDN5 = {TTYCODE_STRING, "kDN5"}, .TTYC_KDN6 = {TTYCODE_STRING, "kDN6"}, .TTYC_KDN7 = {TTYCODE_STRING, "kDN7"}, .TTYC_KEND2 = {TTYCODE_STRING, "kEND"}, .TTYC_KEND3 = {TTYCODE_STRING, "kEND3"}, .TTYC_KEND4 = {TTYCODE_STRING, "kEND4"}, .TTYC_KEND5 = {TTYCODE_STRING, "kEND5"}, .TTYC_KEND6 = {TTYCODE_STRING, "kEND6"}, .TTYC_KEND7 = {TTYCODE_STRING, "kEND7"}, .TTYC_KEND = {TTYCODE_STRING, "kend"}, .TTYC_KF10 = {TTYCODE_STRING, "kf10"}, .TTYC_KF11 = {TTYCODE_STRING, "kf11"}, .TTYC_KF12 = {TTYCODE_STRING, "kf12"}, .TTYC_KF13 = {TTYCODE_STRING, "kf13"}, .TTYC_KF14 = {TTYCODE_STRING, "kf14"}, .TTYC_KF15 = {TTYCODE_STRING, "kf15"}, .TTYC_KF16 = {TTYCODE_STRING, "kf16"}, .TTYC_KF17 = {TTYCODE_STRING, "kf17"}, .TTYC_KF18 = {TTYCODE_STRING, "kf18"}, .TTYC_KF19 = {TTYCODE_STRING, "kf19"}, .TTYC_KF1 = {TTYCODE_STRING, "kf1"}, .TTYC_KF20 = {TTYCODE_STRING, "kf20"}, .TTYC_KF21 = {TTYCODE_STRING, "kf21"}, .TTYC_KF22 = {TTYCODE_STRING, "kf22"}, .TTYC_KF23 = {TTYCODE_STRING, "kf23"}, .TTYC_KF24 = {TTYCODE_STRING, "kf24"}, .TTYC_KF25 = {TTYCODE_STRING, "kf25"}, .TTYC_KF26 = {TTYCODE_STRING, "kf26"}, .TTYC_KF27 = {TTYCODE_STRING, "kf27"}, .TTYC_KF28 = {TTYCODE_STRING, "kf28"}, .TTYC_KF29 = {TTYCODE_STRING, "kf29"}, .TTYC_KF2 = {TTYCODE_STRING, "kf2"}, .TTYC_KF30 = {TTYCODE_STRING, "kf30"}, .TTYC_KF31 = {TTYCODE_STRING, "kf31"}, .TTYC_KF32 = {TTYCODE_STRING, "kf32"}, .TTYC_KF33 = {TTYCODE_STRING, "kf33"}, .TTYC_KF34 = {TTYCODE_STRING, "kf34"}, .TTYC_KF35 = {TTYCODE_STRING, "kf35"}, .TTYC_KF36 = {TTYCODE_STRING, "kf36"}, .TTYC_KF37 = {TTYCODE_STRING, "kf37"}, .TTYC_KF38 = {TTYCODE_STRING, "kf38"}, .TTYC_KF39 = {TTYCODE_STRING, "kf39"}, .TTYC_KF3 = {TTYCODE_STRING, "kf3"}, .TTYC_KF40 = {TTYCODE_STRING, "kf40"}, .TTYC_KF41 = {TTYCODE_STRING, "kf41"}, .TTYC_KF42 = {TTYCODE_STRING, "kf42"}, .TTYC_KF43 = {TTYCODE_STRING, "kf43"}, .TTYC_KF44 = {TTYCODE_STRING, "kf44"}, .TTYC_KF45 = {TTYCODE_STRING, "kf45"}, .TTYC_KF46 = {TTYCODE_STRING, "kf46"}, .TTYC_KF47 = {TTYCODE_STRING, "kf47"}, .TTYC_KF48 = {TTYCODE_STRING, "kf48"}, .TTYC_KF49 = {TTYCODE_STRING, "kf49"}, .TTYC_KF4 = {TTYCODE_STRING, "kf4"}, .TTYC_KF50 = {TTYCODE_STRING, "kf50"}, .TTYC_KF51 = {TTYCODE_STRING, "kf51"}, .TTYC_KF52 = {TTYCODE_STRING, "kf52"}, .TTYC_KF53 = {TTYCODE_STRING, "kf53"}, .TTYC_KF54 = {TTYCODE_STRING, "kf54"}, .TTYC_KF55 = {TTYCODE_STRING, "kf55"}, .TTYC_KF56 = {TTYCODE_STRING, "kf56"}, .TTYC_KF57 = {TTYCODE_STRING, "kf57"}, .TTYC_KF58 = {TTYCODE_STRING, "kf58"}, .TTYC_KF59 = {TTYCODE_STRING, "kf59"}, .TTYC_KF5 = {TTYCODE_STRING, "kf5"}, .TTYC_KF60 = {TTYCODE_STRING, "kf60"}, .TTYC_KF61 = {TTYCODE_STRING, "kf61"}, .TTYC_KF62 = {TTYCODE_STRING, "kf62"}, .TTYC_KF63 = {TTYCODE_STRING, "kf63"}, .TTYC_KF6 = {TTYCODE_STRING, "kf6"}, .TTYC_KF7 = {TTYCODE_STRING, "kf7"}, .TTYC_KF8 = {TTYCODE_STRING, "kf8"}, .TTYC_KF9 = {TTYCODE_STRING, "kf9"}, .TTYC_KHOM2 = {TTYCODE_STRING, "kHOM"}, .TTYC_KHOM3 = {TTYCODE_STRING, "kHOM3"}, .TTYC_KHOM4 = {TTYCODE_STRING, "kHOM4"}, .TTYC_KHOM5 = {TTYCODE_STRING, "kHOM5"}, .TTYC_KHOM6 = {TTYCODE_STRING, "kHOM6"}, .TTYC_KHOM7 = {TTYCODE_STRING, "kHOM7"}, .TTYC_KHOME = {TTYCODE_STRING, "khome"}, .TTYC_KIC2 = {TTYCODE_STRING, "kIC"}, .TTYC_KIC3 = {TTYCODE_STRING, "kIC3"}, .TTYC_KIC4 = {TTYCODE_STRING, "kIC4"}, .TTYC_KIC5 = {TTYCODE_STRING, "kIC5"}, .TTYC_KIC6 = {TTYCODE_STRING, "kIC6"}, .TTYC_KIC7 = {TTYCODE_STRING, "kIC7"}, .TTYC_KICH1 = {TTYCODE_STRING, "kich1"}, .TTYC_KIND = {TTYCODE_STRING, "kind"}, .TTYC_KLFT2 = {TTYCODE_STRING, "kLFT"}, .TTYC_KLFT3 = {TTYCODE_STRING, "kLFT3"}, .TTYC_KLFT4 = {TTYCODE_STRING, "kLFT4"}, .TTYC_KLFT5 = {TTYCODE_STRING, "kLFT5"}, .TTYC_KLFT6 = {TTYCODE_STRING, "kLFT6"}, .TTYC_KLFT7 = {TTYCODE_STRING, "kLFT7"}, .TTYC_KMOUS = {TTYCODE_STRING, "kmous"}, .TTYC_KNP = {TTYCODE_STRING, "knp"}, .TTYC_KNXT2 = {TTYCODE_STRING, "kNXT"}, .TTYC_KNXT3 = {TTYCODE_STRING, "kNXT3"}, .TTYC_KNXT4 = {TTYCODE_STRING, "kNXT4"}, .TTYC_KNXT5 = {TTYCODE_STRING, "kNXT5"}, .TTYC_KNXT6 = {TTYCODE_STRING, "kNXT6"}, .TTYC_KNXT7 = {TTYCODE_STRING, "kNXT7"}, .TTYC_KPP = {TTYCODE_STRING, "kpp"}, .TTYC_KPRV2 = {TTYCODE_STRING, "kPRV"}, .TTYC_KPRV3 = {TTYCODE_STRING, "kPRV3"}, .TTYC_KPRV4 = {TTYCODE_STRING, "kPRV4"}, .TTYC_KPRV5 = {TTYCODE_STRING, "kPRV5"}, .TTYC_KPRV6 = {TTYCODE_STRING, "kPRV6"}, .TTYC_KPRV7 = {TTYCODE_STRING, "kPRV7"}, .TTYC_KRIT2 = {TTYCODE_STRING, "kRIT"}, .TTYC_KRIT3 = {TTYCODE_STRING, "kRIT3"}, .TTYC_KRIT4 = {TTYCODE_STRING, "kRIT4"}, .TTYC_KRIT5 = {TTYCODE_STRING, "kRIT5"}, .TTYC_KRIT6 = {TTYCODE_STRING, "kRIT6"}, .TTYC_KRIT7 = {TTYCODE_STRING, "kRIT7"}, .TTYC_KRI = {TTYCODE_STRING, "kri"}, .TTYC_KUP2 = {TTYCODE_STRING, "kUP"}, .TTYC_KUP3 = {TTYCODE_STRING, "kUP3"}, .TTYC_KUP4 = {TTYCODE_STRING, "kUP4"}, .TTYC_KUP5 = {TTYCODE_STRING, "kUP5"}, .TTYC_KUP6 = {TTYCODE_STRING, "kUP6"}, .TTYC_KUP7 = {TTYCODE_STRING, "kUP7"}, .TTYC_MS = {TTYCODE_STRING, "Ms"}, .TTYC_OP = {TTYCODE_STRING, "op"}, .TTYC_REV = {TTYCODE_STRING, "rev"}, .TTYC_RGB = {TTYCODE_FLAG, "RGB"}, .TTYC_RI = {TTYCODE_STRING, "ri"}, .TTYC_RMACS = {TTYCODE_STRING, "rmacs"}, .TTYC_RMCUP = {TTYCODE_STRING, "rmcup"}, .TTYC_RMKX = {TTYCODE_STRING, "rmkx"}, .TTYC_SETAB = {TTYCODE_STRING, "setab"}, .TTYC_SETAF = {TTYCODE_STRING, "setaf"}, .TTYC_SETRGBB = {TTYCODE_STRING, "setrgbb"}, .TTYC_SETRGBF = {TTYCODE_STRING, "setrgbf"}, .TTYC_SE = {TTYCODE_STRING, "Se"}, .TTYC_SGR0 = {TTYCODE_STRING, "sgr0"}, .TTYC_SITM = {TTYCODE_STRING, "sitm"}, .TTYC_SMACS = {TTYCODE_STRING, "smacs"}, .TTYC_SMCUP = {TTYCODE_STRING, "smcup"}, .TTYC_SMKX = {TTYCODE_STRING, "smkx"}, .TTYC_SMSO = {TTYCODE_STRING, "smso"}, .TTYC_SMUL = {TTYCODE_STRING, "smul"}, .TTYC_SMXX = {TTYCODE_STRING, "smxx"}, .TTYC_SS = {TTYCODE_STRING, "Ss"}, .TTYC_TC = {TTYCODE_FLAG, "Tc"}, .TTYC_TSL = {TTYCODE_STRING, "tsl"}, .TTYC_U8 = {TTYCODE_NUMBER, "U8"}, .TTYC_VPA = {TTYCODE_STRING, "vpa"}, .TTYC_XENL = {TTYCODE_FLAG, "xenl"}, .TTYC_XT = {TTYCODE_FLAG, "XT"}}
/*** DEPENDENCIES:
struct tty_term_code_entry
{
  enum tty_code_type type;
  const char *name;
}
----------------------------
***/


static const struct xterm_keys_entry xterm_keys_table[] = {{KEYC_F1, "\033[1;_P"}, {KEYC_F1, "\033O1;_P"}, {KEYC_F1, "\033O_P"}, {KEYC_F2, "\033[1;_Q"}, {KEYC_F2, "\033O1;_Q"}, {KEYC_F2, "\033O_Q"}, {KEYC_F3, "\033[1;_R"}, {KEYC_F3, "\033O1;_R"}, {KEYC_F3, "\033O_R"}, {KEYC_F4, "\033[1;_S"}, {KEYC_F4, "\033O1;_S"}, {KEYC_F4, "\033O_S"}, {KEYC_F5, "\033[15;_~"}, {KEYC_F6, "\033[17;_~"}, {KEYC_F7, "\033[18;_~"}, {KEYC_F8, "\033[19;_~"}, {KEYC_F9, "\033[20;_~"}, {KEYC_F10, "\033[21;_~"}, {KEYC_F11, "\033[23;_~"}, {KEYC_F12, "\033[24;_~"}, {KEYC_UP, "\033[1;_A"}, {KEYC_DOWN, "\033[1;_B"}, {KEYC_RIGHT, "\033[1;_C"}, {KEYC_LEFT, "\033[1;_D"}, {KEYC_HOME, "\033[1;_H"}, {KEYC_END, "\033[1;_F"}, {KEYC_PPAGE, "\033[5;_~"}, {KEYC_NPAGE, "\033[6;_~"}, {KEYC_IC, "\033[2;_~"}, {KEYC_DC, "\033[3;_~"}, {'!', "\033[27;_;33~"}, {'#', "\033[27;_;35~"}, {'(', "\033[27;_;40~"}, {')', "\033[27;_;41~"}, {'+', "\033[27;_;43~"}, {',', "\033[27;_;44~"}, {'-', "\033[27;_;45~"}, {'.', "\033[27;_;46~"}, {'0', "\033[27;_;48~"}, {'1', "\033[27;_;49~"}, {'2', "\033[27;_;50~"}, {'3', "\033[27;_;51~"}, {'4', "\033[27;_;52~"}, {'5', "\033[27;_;53~"}, {'6', "\033[27;_;54~"}, {'7', "\033[27;_;55~"}, {'8', "\033[27;_;56~"}, {'9', "\033[27;_;57~"}, {':', "\033[27;_;58~"}, {';', "\033[27;_;59~"}, {'<', "\033[27;_;60~"}, {'=', "\033[27;_;61~"}, {'>', "\033[27;_;62~"}, {'?', "\033[27;_;63~"}, {'\'', "\033[27;_;39~"}, {'\r', "\033[27;_;13~"}, {'\t', "\033[27;_;9~"}}
/*** DEPENDENCIES:
struct xterm_keys_entry
{
  key_code key;
  const char *template;
}
----------------------------
***/


static const struct input_state input_state_ground = {"ground", input_ground, 0, input_state_ground_table}
/*** DEPENDENCIES:
static void input_ground(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  evbuffer_drain(ictx->since_ground, EVBUFFER_LENGTH(ictx->since_ground));
  if (ictx->input_space > 32)
  {
    ictx->input_space = 32;
    ictx->input_buf = xrealloc(ictx->input_buf, 32);
  }
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_esc_enter = {"esc_enter", input_clear, 0, input_state_esc_enter_table}
/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_csi_enter = {"csi_enter", input_clear, 0, input_state_csi_enter_table}
/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_dcs_enter = {"dcs_enter", input_enter_dcs, 0, input_state_dcs_enter_table}
/*** DEPENDENCIES:
static void input_enter_dcs(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_consume_st = {"consume_st", input_enter_rename, 0, input_state_consume_st_table}
/*** DEPENDENCIES:
static void input_enter_rename(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_osc_string = {"osc_string", input_enter_osc, input_exit_osc, input_state_osc_string_table}
/*** DEPENDENCIES:
static void input_enter_osc(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


----------------------------
static void input_exit_osc(struct input_ctx *ictx)
{
  u_char *p = ictx->input_buf;
  unsigned int p_idx = 0;
  u_int option;
  if (ictx->flags & 0x1)
  {
    return;
  }
  if (((ictx->input_len < 1) || (p[p_idx] < '0')) || (p[p_idx] > '9'))
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, p);
  option = 0;
  while ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
  {
    option = ((option * 10) + p[p_idx]) - '0';
    p_idx += 1;
  }

  if (p[p_idx] == ';')
  {
    p_idx += 1;
  }
  switch (option)
  {
    case 0:

    case 2:
    {
      if (utf8_isvalid(p))
      {
        screen_set_title(ictx->ctx.s, p);
        server_status_window(ictx->wp->window);
      }
      break;
    }

    case 4:
    {
      input_osc_4(ictx->wp, p);
      break;
    }

    case 10:
    {
      input_osc_10(ictx->wp, p);
      break;
    }

    case 11:
    {
      input_osc_11(ictx->wp, p);
      break;
    }

    case 12:
    {
      if (utf8_isvalid(p) && (p[p_idx] != '?'))
      {
        screen_set_cursor_colour(ictx->ctx.s, p);
      }
      break;
    }

    case 52:
    {
      input_osc_52(ictx->wp, p);
      break;
    }

    case 104:
    {
      input_osc_104(ictx->wp, p);
      break;
    }

    case 112:
    {
      if (p[p_idx] == '\0')
      {
        screen_set_cursor_colour(ictx->ctx.s, "");
      }
      break;
    }

    default:
    {
      log_debug("%s: unknown '%u'", __func__, option);
      break;
    }

  }

}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_apc_string = {"apc_string", input_enter_apc, input_exit_apc, input_state_apc_string_table}
/*** DEPENDENCIES:
static void input_exit_apc(struct input_ctx *ictx)
{
  if (ictx->flags & 0x1)
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, ictx->input_buf);
  if (!utf8_isvalid(ictx->input_buf))
  {
    return;
  }
  screen_set_title(ictx->ctx.s, ictx->input_buf);
  server_status_window(ictx->wp->window);
}


----------------------------
static void input_enter_apc(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


----------------------------
None
----------------------------
***/


static const struct input_state input_state_rename_string = {"rename_string", input_enter_rename, input_exit_rename, input_state_rename_string_table}
/*** DEPENDENCIES:
static void input_exit_rename(struct input_ctx *ictx)
{
  if (ictx->flags & 0x1)
  {
    return;
  }
  if (!options_get_number(ictx->wp->window->options, "allow-rename"))
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, ictx->input_buf);
  if (!utf8_isvalid(ictx->input_buf))
  {
    return;
  }
  window_set_name(ictx->wp->window, ictx->input_buf);
  options_set_number(ictx->wp->window->options, "automatic-rename", 0);
  server_status_window(ictx->wp->window);
}


----------------------------
static void input_enter_rename(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


----------------------------
None
----------------------------
***/


static const struct 
{
  const char *name;
  void (*arrange)(struct window *);
} layout_sets[] = {{"even-horizontal", layout_set_even_h}, {"even-vertical", layout_set_even_v}, {"main-horizontal", layout_set_main_h}, {"main-vertical", layout_set_main_v}, {"tiled", layout_set_tiled}}
/*** DEPENDENCIES:
static void layout_set_even_v(struct window *w)
{
  layout_set_even(w, LAYOUT_TOPBOTTOM);
}


----------------------------
static void layout_set_main_h(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcmain;
  unsigned int lcmain_idx = 0;
  struct layout_cell *lcrow;
  unsigned int lcrow_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int mainheight;
  u_int otherheight;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  u_int totalrows;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  n -= 1;
  columns = (w->sx + 1) / (2 + 1);
  if (columns == 0)
  {
    columns = 1;
  }
  rows = 1 + ((n - 1) / columns);
  columns = 1 + ((n - 1) / rows);
  width = (w->sx - (n - 1)) / columns;
  mainheight = options_get_number(w->options, "main-pane-height") + 1;
  otherheight = options_get_number(w->options, "other-pane-height") + 1;
  if ((otherheight > 1) && ((w->sy - otherheight) > mainheight))
  {
    mainheight = w->sy - otherheight;
  }
  if (mainheight < (2 + 1))
  {
    mainheight = 2 + 1;
  }
  totalrows = (rows * (2 + 1)) - 1;
  if ((mainheight + totalrows) > w->sy)
  {
    if (((totalrows + 2) + 1) > w->sy)
    {
      mainheight = 2 + 2;
    }
    else
      mainheight = w->sy - totalrows;
    height = 2;
  }
  else
    height = ((w->sy - mainheight) - (rows - 1)) / rows;
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, (mainheight + (rows * (height + 1))) - 1, 0, 0);
  layout_make_node(lc, LAYOUT_TOPBOTTOM);
  lcmain_idx = layout_create_cell(lc);
  layout_set_size(lcmain, w->sx, mainheight - 1, 0, 0);
  layout_make_leaf(lcmain, (&w->panes)->tqh_first);
  do
  {
    lcmain->entry.tqe_next = 0;
    lcmain->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcmain[lcmain_idx];
    (&lc->cells)->tqh_last = &lcmain->entry.tqe_next;
  }
  while (0);
  wp_idx = (&w->panes)->tqh_first->entry.tqe_next;
  for (j = 0; j < rows; j += 1)
  {
    helper_layout_set_main_h_1(&wp_idx, &lcrow_idx, &lcchild_idx, &used, &i, w, wp, lc, lcrow, lcchild, width, height, columns);
  }

  used = ((mainheight + (rows * height)) + rows) - 1;
  if (w->sy > used)
  {
    lcrow_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lcrow, LAYOUT_TOPBOTTOM, w->sy - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
}


----------------------------
static void layout_set_even_h(struct window *w)
{
  layout_set_even(w, LAYOUT_LEFTRIGHT);
}


----------------------------
void layout_set_tiled(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcrow;
  unsigned int lcrow_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  rows = (columns = 1);
  while ((rows * columns) < n)
  {
    rows += 1;
    if ((rows * columns) < n)
    {
      columns += 1;
    }
  }

  width = (w->sx - (columns - 1)) / columns;
  if (width < 2)
  {
    width = 2;
  }
  height = (w->sy - (rows - 1)) / rows;
  if (height < 2)
  {
    height = 2;
  }
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, ((width + 1) * columns) - 1, ((height + 1) * rows) - 1, 0, 0);
  layout_make_node(lc, LAYOUT_TOPBOTTOM);
  wp_idx = (&w->panes)->tqh_first;
  for (j = 0; j < rows; j += 1)
  {
    helper_layout_set_tiled_1(&wp_idx, &lcrow_idx, &lcchild_idx, &used, &i, w, wp, lc, lcrow, lcchild, n, width, height, j, columns);
  }

  used = ((rows * height) + rows) - 1;
  if (w->sy > used)
  {
    lcrow_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lcrow, LAYOUT_TOPBOTTOM, w->sy - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
}


----------------------------
static void layout_set_main_v(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcmain;
  unsigned int lcmain_idx = 0;
  struct layout_cell *lccolumn;
  unsigned int lccolumn_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int mainwidth;
  u_int otherwidth;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  u_int totalcolumns;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  n -= 1;
  rows = (w->sy + 1) / (2 + 1);
  if (rows == 0)
  {
    rows = 1;
  }
  columns = 1 + ((n - 1) / rows);
  rows = 1 + ((n - 1) / columns);
  height = (w->sy - (n - 1)) / rows;
  mainwidth = options_get_number(w->options, "main-pane-width") + 1;
  otherwidth = options_get_number(w->options, "other-pane-width") + 1;
  if ((otherwidth > 1) && ((w->sx - otherwidth) > mainwidth))
  {
    mainwidth = w->sx - otherwidth;
  }
  if (mainwidth < (2 + 1))
  {
    mainwidth = 2 + 1;
  }
  totalcolumns = (columns * (2 + 1)) - 1;
  if ((mainwidth + totalcolumns) > w->sx)
  {
    if (((totalcolumns + 2) + 1) > w->sx)
    {
      mainwidth = 2 + 2;
    }
    else
      mainwidth = w->sx - totalcolumns;
    width = 2;
  }
  else
    width = ((w->sx - mainwidth) - (columns - 1)) / columns;
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, (mainwidth + (columns * (width + 1))) - 1, w->sy, 0, 0);
  layout_make_node(lc, LAYOUT_LEFTRIGHT);
  lcmain_idx = layout_create_cell(lc);
  layout_set_size(lcmain, mainwidth - 1, w->sy, 0, 0);
  layout_make_leaf(lcmain, (&w->panes)->tqh_first);
  do
  {
    lcmain->entry.tqe_next = 0;
    lcmain->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcmain[lcmain_idx];
    (&lc->cells)->tqh_last = &lcmain->entry.tqe_next;
  }
  while (0);
  wp_idx = (&w->panes)->tqh_first->entry.tqe_next;
  for (j = 0; j < columns; j += 1)
  {
    helper_layout_set_main_v_1(&wp_idx, &lccolumn_idx, &lcchild_idx, &used, &i, w, wp, lc, lccolumn, lcchild, width, height, rows);
  }

  used = ((mainwidth + (columns * width)) + columns) - 1;
  if (w->sx > used)
  {
    lccolumn_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lccolumn, LAYOUT_LEFTRIGHT, w->sx - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


