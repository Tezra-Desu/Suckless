/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "~/.config/polybar/launch.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "Iosevka:size=12" };
static const char dmenufont[]       = "Iosevka:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#d580ff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"urxvt", "-name", "spspot", "-geometry", "95x25", "-e", "ncspot", NULL };
const char *spcmd2[] = {"urxvt", "-name", "spfm", "-geometry", "110x30", "-e", "ranger", NULL };
const char *spcmd3[] = {"emacs", "--name", "spnote", "-g", "90x30", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spspot",      spcmd1},
	{"spranger",    spcmd2},
	{"emacs",       spcmd3},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class          	        instance         title          tags mask       isfloating       monitor */
	{ "Gimp",	  	        NULL,		 NULL,		0,		1,	         -1 },
	{ "firefox-developer-edition", "Places",        "Library",	0,		1,		 -1 },
	{ "qBittorrent",  	        NULL,		 NULL,		0,		1,	         -1 },
	{ "mullvad-vpn",  	        NULL,		 NULL,		0,		1,	         -1 },
	{ "Pcmanfm",	  	        NULL,		 NULL,		0,		1,	         -1 },
	{ "generic",	  	       "haruna",	 NULL,		0,		1,	         -1 },
	{ "virt-manager", 	        NULL,		 NULL,		0,		1,	         -1 },
	{ "xarchiver",  	        NULL,		 NULL,		0,		1,	         -1 },
	{ "imv",         	        NULL,		 NULL,		0,		1,	         -1 },
	{ NULL,		    	       "spspot",	 NULL,		SPTAG(0),	1,		 -1 },
	{ NULL,		               "spfm",		 NULL,		SPTAG(1),	1,		 -1 },
	{ NULL,		               "spnote",	 NULL,		SPTAG(2),	1,		 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALT Mod1Mask
#define CTRL ControlMask
#define SHIFT ShiftMask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#include "maximize.c"
#include <X11/XF86keysym.h>

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *webcmd[]   = { "firefox-developer-edition", NULL };
static const char *fmcmd[]    = { "pcmanfm", NULL };
static const char *qbitcmd[]  = { "qbittorrent", NULL };
static const char *gamecmd[]  = { "pegasus-fe", NULL };
static const char *vmcmd[]    = { "virt-manager", NULL };
static const char *boorucmd[] = { "Grabber", NULL };
static const char *coomcmd[]  = { "YACReaderLibrary", NULL };


static Key keys[] = {
	/* modifier                     key        			function        argument */
	{ MODKEY,                       XK_space,  			spawn,          {.v = dmenucmd } },
	{ ALT,                          XK_Return, 			spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      			spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_f,      			spawn,          {.v = fmcmd } },
	{ MODKEY,                       XK_q,      			spawn,          {.v = qbitcmd } },
	{ MODKEY,                       XK_g,      			spawn,          {.v = gamecmd } },
	{ MODKEY,                       XK_v,      			spawn,          {.v = vmcmd } },
	{ MODKEY,                       XK_b,      			spawn,          {.v = boorucmd } },
	{ MODKEY,                       XK_c,      			spawn,          {.v = coomcmd } },
	{ MODKEY,                       XK_t,      			spawn,          SHCMD("~/.dwm/tor.sh") },
	{ MODKEY,                       XK_z,      			spawn,          SHCMD("~/.dwm/libre.sh") },
	{ MODKEY|ALT,                   XK_b,      			spawn,          SHCMD("~/.config/polybar/launch.sh") },
	{ MODKEY|CTRL,                  XK_b,      			togglebar,      {0} },
	{ MODKEY,                       XK_j,      			focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      			focusstack,     {.i = -1 } },
	{ MODKEY|CTRL,                  XK_j,      			pushdown,       {0} },
	{ MODKEY|CTRL,                  XK_k,      			pushup,         {0} },
	{ MODKEY|CTRL,                  XK_equal,  			incnmaster,     {.i = +1 } },
	{ MODKEY|CTRL,                  XK_minus,  			incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      			setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      			setmfact,       {.f = +0.05} },
	{ MODKEY|SHIFT,                 XK_z,      			zoom,           {0} },
	{ MODKEY,                       XK_Tab,    			view,           {0} },
	{ MODKEY,                       XK_x,      			killclient,     {0} },
	{ MODKEY|ALT,                   XK_t,      			setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ALT,                   XK_f,      			setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ALT,                   XK_m,      			setlayout,      {.v = &layouts[2]} },
	{ MODKEY|CTRL,                  XK_space,  			togglefloating, {0} },
	{ MODKEY|CTRL,                  XK_m,      			togglemaximize, {0} },
	{ MODKEY,                       XK_0,      			view,           {.ui = ~0 } },
	{ MODKEY|SHIFT,                 XK_0,      			tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  			focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, 			focusmon,       {.i = +1 } },
	{ MODKEY|SHIFT,                 XK_comma,  			tagmon,         {.i = -1 } },
	{ MODKEY|SHIFT,                 XK_period, 			tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  			setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  			setgaps,        {.i = +1 } },
	{ MODKEY|SHIFT,                 XK_equal,  			setgaps,        {.i = 0  } },
	{ MODKEY,          		XK_s,  	   			togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_r,	   			togglescratch,  {.ui = 1 } },
	{ MODKEY,            		XK_n,	   			togglescratch,  {.ui = 2 } },
	{ NULL,                         XF86XK_MonBrightnessUp, 	spawn,          SHCMD("~/.dwm/brightUp.sh") },
	{ NULL,                         XF86XK_MonBrightnessDown,  	spawn,          SHCMD("~/.dwm/brightDown.sh") },
	{ NULL,                         XF86XK_AudioRaiseVolume,   	spawn,          SHCMD("~/.dwm/volUp.sh") },
	{ NULL,                         XF86XK_AudioLowerVolume,     	spawn,          SHCMD("~/.dwm/volDown.sh") },
	{ NULL,                         XF86XK_AudioMute,      		spawn,          SHCMD("~/.dwm/volMute.sh") },
	{ NULL,                         XF86XK_AudioMicMute,    	spawn,          SHCMD("~/.dwm/micMute.sh") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|CTRL,                  XK_x,      			quit,           {0} },
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
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

