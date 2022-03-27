/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 28;       /* snap pixel */
static const int scalepreview       = 1;        /* Tag preview scaling */
static const unsigned int gappih    = 1;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 1;       /* vert inner gap between windows */
static const unsigned int gappoh    = 1;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 1;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */

static const char *fonts[]          = {  "Monospace: size=10","Ubuntu:size=10", "fontawesome: size=14" };
static const char dmenufont[]       = "Ubuntu: size=10";
static const char col_gray1[]       = "#202020";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#000000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "" };
static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "0", "+8%",     NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "0", "-8%",     NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *brightnessinc[] = {"light", "-A", "5%", NULL};
static const char *brightnessdec[] = {"light", "-U", "5%", NULL};

static const Rule rules[] = {
	 //xprop(1):
        //WM_CLASS(STRING) = instance, class
        //WM_NAME(STRING) = title
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Zoom",     NULL,       NULL,       1 << 3,       0,           -1 },
	{ "Atom",     NULL,       NULL,       1,            0,           -1 },
	{ "qutebrowser",     NULL,       NULL,       1 << 2,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

#include <X11/XF86keysym.h>
static const Layout layouts[] = {
	/* symbol     arrange function */
 	{ "[\\]",      dwindle },
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod1Mask
#define MODKEY4 Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY4,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY4|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY4|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY4|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray4, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *atomcmd[]  = { "atom", NULL };
static const char *firefoxcmd[]  = { "librewolf", NULL };
static const char *qutecmd[]  = { "qutebrowser", NULL };
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY4,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY4,                       XK_Return, spawn,          {.v = termcmd } },
	{ ControlMask|MODKEY4,           XK_a,       spawn,          {.v = atomcmd } },
	{ ControlMask|MODKEY4,           XK_f,       spawn,          {.v = firefoxcmd } },
	{ ControlMask|MODKEY4,           XK_s,       spawn,          {.v = qutecmd } },
	{ MODKEY4,                       XK_b,      togglebar,      {0} },
	{ MODKEY4|ShiftMask,             XK_w,      tabmode,        {-1} },
	{ MODKEY4,                       XK_c,      focusstack,     {.i = +1 } },
	{ MODKEY4|ShiftMask,             XK_c,      focusstack,     {.i = -1 } },
	{ MODKEY4|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY4|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY4,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY4,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY4|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY4,                       XK_Tab,    view,           {0} },
	{ MODKEY4,                      XK_w,      killclient,     {0} },
	{ MODKEY4|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY4,                       XK_t,      setlayout,      {.v = &layouts[1]} },
        { MODKEY4,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY4,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY4,                       XK_s,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY4|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY4,                       XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY4|ShiftMask,             XK_g,      setlayout,      {.v = &layouts[11]} },
	{ MODKEY4,                       XK_space,  setlayout,      {0} },
	{ MODKEY4|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY4,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY4|ShiftMask,             XK_f,      togglefullscr,  {.ui = ~0 } },
	{ MODKEY4|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY4,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY4,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY4|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY4|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY4,                       XK_n, shiftview,       {.i = +1 } },
	{ MODKEY4,             XK_p,  shiftview,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    	{ MODKEY,                       XK_F12,    spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F11,    spawn,          {.v = downvol } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = mutevol } },
    	{ 0,                            XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute, spawn,        {.v = mutevol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },
	{ 0,                            XF86XK_MonBrightnessUp, spawn,    {.v=brightnessinc }},
    	{ 0,                            XF86XK_MonBrightnessDown, spawn, {.v=brightnessdec}},
    	{ MODKEY,                       XK_F1,     spawn, {.v=brightnessdec}},
    	{ MODKEY,                       XK_F2,     spawn, {.v=brightnessinc}},
	{ MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};
