/* Taken from https://github.com/djpohly/dwl/issues/466 */
#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }
/* appearance */
static const int sloppyfocus               = 0;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;  /* 1 means idle inhibitors will disable idle tracking even if it's surface isn't visible  */
static const unsigned int borderpx         = 1;  /* border pixel of windows */
static const float rootcolor[]             = COLOR(0x222222ff);
static const float bordercolor[]           = COLOR(0x444444ff);
static const float focuscolor[]            = COLOR(0x005577ff);
static const float urgentcolor[]           = COLOR(0xff0000ff);
/* To conform the xdg-protocol, set the alpha to zero to restore the old behavior */
static const float fullscreen_bg[]         = {0.1f, 0.1f, 0.1f, 1.0f}; /* You can also use glsl colors */

/* tagging - TAGCOUNT must be no greater than 31 */
#define TAGCOUNT (9)

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id                   title    tags mask    isfloating monitor scratchkey */
    /* examples:
    { "Gimp",				    NULL,	 0,			  1,	     -1 },
    */
	{ NULL,                     "scratchpad", 0,      1,         -1,     's' },
	{ "pavucontrol",            NULL,         0,      1,         -1,     0   },
	{ "galculator",             NULL,         0,      1,         -1,     0   },
	{ "Lxappearance",           NULL,         0,      1,         -1,     0   },
	{ "floatingterm",           NULL,         0,      1,         -1,     0   },
	{ "localsend_app",          NULL,         0,      1,         -1,     0   },
	{ "Code",                   NULL,         1 << 1, 0,         -1,     0   },
	{ "neovide",                NULL,         1 << 1, 0,         -1,     0   },
	{ "Gimp",                   NULL,         1 << 1, 1,         -1,     0   },
	{ "ghb",                    NULL,         1 << 1, 1,         -1,     0   },
	{ "nemo",                   NULL,         1 << 1, 0,         -1,     0   },
	{ "foot",                   NULL,         1 << 1, 0,         -1,     0   },
	{ "org.pipewire.Helvum",    NULL,         1 << 1, 0,         -1,     0   },
	{ "firefox",                NULL,         1 << 2, 0,         -1,     0   },
	{ "org.pwmt.zathura",       NULL,         1 << 3, 0,         -1,     0   },
	{ "marktext",               NULL,         1 << 3, 0,         -1,     0   },
	{ "libreoffice",            NULL,         1 << 3, 0,         -1,     0   },
	{ "discord",                NULL,         1 << 4, 0,         -1,     0   },
	{ "org.telegram.desktop",   NULL,         1 << 4, 0,         -1,     0   },
	{ "Spotify",                NULL,         1 << 5, 0,         -1,     0   },
	{ "YouTube Music",          NULL,         1 << 5, 0,         -1,     0   },
	{ "qBittorrent",            NULL,         1 << 6, 0,         -1,     0   },
	{ "obs",                    NULL,         1 << 7, 0,         -1,     0   },
	{ "bottles",                NULL,         1 << 7, 0,         -1,     0   },
	{ "steam",                  NULL,         1 << 7, 0,         -1,     0   },
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
/* NOTE: ALWAYS add a fallback rule, even if you are completely sure it won't be used */
static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5f,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
	*/
	/* defaults */
	{ NULL,       0.55f, 1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
	.options = "caps:swapescape",
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;
/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER
*/
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
/* You can choose between:
LIBINPUT_CONFIG_TAP_MAP_LRM -- 1/2/3 finger tap maps to left/right/middle
LIBINPUT_CONFIG_TAP_MAP_LMR -- 1/2/3 finger tap maps to left/middle/right
*/
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

/* If you want to use the windows key for MODKEY, use WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_ALT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]    = { "alacritty", NULL };
static const char *menucmd[]    = { "rofi", "-show", "combi", "-combi-modi", "drun,run", "-modi", "combi", "-show-icons", NULL };
static const char *lockscrn[]   = { "swaylock", "-feS", "--effect-blur", "4x3", "--effect-greyscale", "--indicator-radius", "24", "--indicator-thickness", "8", "--indicator-x-position", "64", "--indicator-y-position", "64", NULL };
static const char *audioctl[]   = { "pavucontrol", NULL };
static const char scrnshot[]    = { "slurp | grim -g - $(xdg-user-dir PICTURES)/Screenshots/Screenshot_$(date +%F_%H-%M-%S.png)" };
static const char fscrnshot[]   = { "grim $(xdg-user-dir PICTURES)/Screenshots/Screenshot_$(date +%F_%H-%M-%S.png)" };
static const char *volmute[]    = { "wpctl", "set-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *volinc[]     = { "wpctl", "set-volume", "@DEFAULT_SINK@", "0.05+", NULL };
static const char *voldec[]     = { "wpctl", "set-volume", "@DEFAULT_SINK@", "0.05-", NULL };
static const char *brightinc[]  = { "xbacklight", "-inc", "5", "-steps", "5", NULL };
static const char *brightdec[]  = { "xbacklight", "-dec", "5", "-steps", "5", NULL };
static const char *netmcmd[]    = { "alacritty", "--class", "floatingterm,floatingterm", "-e", "nmtui", NULL };
static const char *bluecmd[]    = { "alacritty", "--class", "floatingterm,floatingterm", "-e", "bluetuith", NULL };

/* named scratchpads - First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = { "s", "alacritty", "-t", "scratchpad", NULL };

static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,             spawn,       {.v = audioctl } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_L,             spawn,       {.v = lockscrn } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_N,             spawn,       {.v = netmcmd } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_B,             spawn,       {.v = bluecmd } },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_S,             spawn,       SHCMD(scrnshot) },
    { 0,                         XKB_KEY_Print,         spawn,       SHCMD(fscrnshot) },
    { 0,                 XKB_KEY_XF86AudioRaiseVolume,  spawn,       {.v = volinc } },
    { 0,                 XKB_KEY_XF86AudioLowerVolume,  spawn,       {.v = voldec } },
    { 0,                 XKB_KEY_XF86AudioMute,         spawn,       {.v = volmute } },
    { 0,                 XKB_KEY_XF86MonBrightnessUp,   spawn,       {.v = brightinc } },
    { 0,                 XKB_KEY_XF86MonBrightnessDown, spawn,       {.v = brightdec } },

	{ MODKEY,                    XKB_KEY_p,          spawn,          {.v = menucmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_grave,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                    XKB_KEY_b,          togglebar,      {0} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_i,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_d,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05f} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05f} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_C,          killclient,     {0} },
	{ MODKEY,                    XKB_KEY_t,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                    XKB_KEY_f,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                    XKB_KEY_m,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
	/* Ctrl-Alt-Fx is used to switch to another VT, if you don't know what a VT is
	 * do not remove them.
	 */
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
