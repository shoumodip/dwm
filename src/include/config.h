/* See LICENSE file for copyright and license details. */

/* Appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int snap     = 0; /* snap pixel */
static const int showbar           = 1; /* 0 means no bar */
static const int topbar            = 1; /* 0 means bottom bar */

static const char *fonts[]         = { "Monospace:pixelsize=18:antialias=true:autohint=true" };

static const char *colors[][3]     = {
    /*                Fg         Bg         Border   */
    [SchemeNorm]  = { "#ebdbb2", "#282828", "#282828" },
    [SchemeSel]   = { "#282828", "#689d6a", "#689d6a" },
    [SchemeTitle] = { "#282828", "#282828", "#282828" },
};

/* Tags */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* Rules */
static const Rule rules[] = {0};

/* Layouts */
static const float mfact     = 0.50; /* Master window size */
static const int nmaster     = 1;    /* Number of master windows */
static const int resizehints = 0;    /* Don't respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* Symbol     Function */
    { "[]=",      tile },    /* Tiled layout */
    { "[M]",      monocle }, /* Monocle layout */
    { "><>",      NULL },    /* Floating layout */
};

/* Keymap builders */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Helper for spawning shell commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Dmenu */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenurun", "-m", dmenumon, NULL };

static Key keys[] = {
    /* Modifier             Key                 Function        Argument */

    /* Programs */
    { MODKEY,               XK_d,               spawn,          {.v = dmenucmd } },
    { MODKEY,               XK_Return,          spawn,          SHCMD("$TERMINAL") },
    { MODKEY,               XK_w,               spawn,          SHCMD("$BROWSER") },
    { MODKEY,               XK_e,               spawn,          SHCMD("$TERMINAL -e $EDITOR") },
    { 0,                    XK_Print,           spawn,          SHCMD("shot 'full screen'") },

    /* System actions */
    { MODKEY,               XK_BackSpace,       spawn,          SHCMD("prompt 'Shutdown:' 'sudo shutdown -h now'") },
    { MODKEY,               XK_r,               spawn,          SHCMD("prompt 'Reboot:' 'sudo reboot'") },

    /* Sound */
    { MODKEY,               XK_s,               spawn,          SHCMD("$TERMINAL -e pulsemixer") },
    { MODKEY|ShiftMask,     XK_m,               spawn,          SHCMD("volctrl mute") },
    { MODKEY,               XK_equal,           spawn,          SHCMD("volctrl up") },
    { MODKEY|ShiftMask,     XK_equal,           spawn,          SHCMD("volctrl up 15") },
    { MODKEY,               XK_minus,           spawn,          SHCMD("volctrl down") },
    { MODKEY|ShiftMask,     XK_minus,           spawn,          SHCMD("volctrl down 15") },

    /* Menus */
    { MODKEY|ShiftMask,     XK_k,               spawn,          SHCMD("dmenukill") },
    { MODKEY,               XK_u,               spawn,          SHCMD("dmenumount") },
    { MODKEY|ShiftMask,     XK_u,               spawn,          SHCMD("dmenuumount") },
    { ShiftMask,            XK_F6,              spawn,          SHCMD("shot") },

    /* MUSIC */
    { MODKEY,               XK_m,               spawn,          SHCMD("dmenumpc") },

    { MODKEY,               XK_comma,           spawn,          SHCMD("mpc prev") },
    { MODKEY,               XK_period,          spawn,          SHCMD("mpc next") },
    { MODKEY|ShiftMask,     XK_comma,           spawn,          SHCMD("mpc seek 0%") },
    { MODKEY|ShiftMask,     XK_period,          spawn,          SHCMD("mpc repeat") },

    { MODKEY,               XK_bracketright,    spawn,          SHCMD("mpc seek +5") },
    { MODKEY,               XK_bracketleft,     spawn,          SHCMD("mpc seek -5") },
    { MODKEY|ShiftMask,     XK_bracketright,    spawn,          SHCMD("mpc seek +10") },
    { MODKEY|ShiftMask,     XK_bracketleft,     spawn,          SHCMD("mpc seek -10") },
    { MODKEY|ControlMask,   XK_bracketright,    spawn,          SHCMD("mpc seek +60") },
    { MODKEY|ControlMask,   XK_bracketleft,     spawn,          SHCMD("mpc seek -60") },

    { MODKEY,               XK_p,               spawn,          SHCMD("mpc toggle") },
    { MODKEY|ShiftMask,     XK_p,               spawn,          SHCMD("mpc pause") },

    /* DWM */
    { MODKEY,               XK_b,               togglebar,      {0} },
    { MODKEY|ShiftMask,     XK_q,               quit,           {0} },

    /* Layouts */
    { MODKEY,               XK_t,               setlayout,      {.v = &layouts[0]} },
    { MODKEY|ShiftMask,     XK_t,               setlayout,      {.v = &layouts[1]} },
    { MODKEY|ShiftMask,     XK_f,               setlayout,      {.v = &layouts[2]} },

    /* Windows */
    { MODKEY,               XK_j,               focusstack,     {.i = +1 } },
    { MODKEY,               XK_k,               focusstack,     {.i = -1 } },
    { MODKEY,               XK_q,               killclient,     {0} },
    { MODKEY,               XK_space,           zoom,           {0} },
    { MODKEY,               XK_v,               focusmaster,    {0} },

    /* Window modes */
    { MODKEY|ShiftMask,     XK_space,           togglefloating, {0} },
    { MODKEY,               XK_f,               togglefullscr,  {0} },

    /* Master windows */
    { MODKEY,               XK_o,               incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,     XK_o,               incnmaster,     {.i = -1 } },
    { MODKEY,               XK_h,               setmfact,       {.f = -0.05} },
    { MODKEY,               XK_l,               setmfact,       {.f = +0.05} },

    /* Monitors */
    { MODKEY,               XK_comma,           focusmon,       {.i = -1 } },
    { MODKEY,               XK_period,          focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,     XK_comma,           tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,     XK_period,          tagmon,         {.i = +1 } },

    /* Tags */
    { MODKEY,               XK_Tab,             view,           {0} },
    { MODKEY,               XK_0,               view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,     XK_0,               tag,            {.ui = ~0 } },
    TAGKEYS(                XK_1,               0)
    TAGKEYS(                XK_2,               1)
    TAGKEYS(                XK_3,               2)
    TAGKEYS(                XK_4,               3)
    TAGKEYS(                XK_5,               4)
    TAGKEYS(                XK_6,               5)
    TAGKEYS(                XK_7,               6)
    TAGKEYS(                XK_8,               7)
    TAGKEYS(                XK_9,               8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* Click                Event           Button          Function        Argument */

    /* Layouts */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

    /* Window */
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

    /* Tags */
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

