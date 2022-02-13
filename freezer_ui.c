//******************************************************************************
//
//==============================================================================
//
//
//
//
//
//
//
//
//******************************************************************************


#include	"karljr.h"
#include	"jude.h"
#include	"jude_widgets.h"
#include	"freezer_ui.h"
#include	"freezer_ui_m3wp.h"


//==============================================================================
//==============================================================================


const char str_freeze_page0[] = "STATE";
const char str_freeze_page1[] = "TOOLS";
const char str_freeze_page2[] = "DISK";

const char str_freeze_bar0[] = "M E G A 6 5   F R E E Z E R   U T I L I T Y ";

const char str_freeze_ctrl0[] = "C P U";
const char str_freeze_ctrl1[] = "MODE:";
const char str_freeze_ctrl2[] = "AUTO";
const char str_freeze_ctrl3[] = "4502";
const char str_freeze_ctrl4[] = "FREQ:";
const char str_freeze_ctrl5[] = "1 MHZ";
const char str_freeze_ctrl6[] = "3.5MHZ";
const char str_freeze_ctrl7[] = "40 MHZ";
const char str_freeze_ctrl8[] = "F E A T U R E S";
const char str_freeze_ctrl9[] = "CRT EMULATION:";
//const char str_freeze_ctrlA[] = "C65 920224";
const char str_freeze_ctrlB[] = "VIDEO MODE   :";
const char str_freeze_ctrlC[] = "PAL50";
const char str_freeze_ctrlD[] = "NTSC60";
const char str_freeze_ctrlE[] = "CART ENABLE  :";
const char str_freeze_ctrlF[] = "YES";
const char str_freeze_ctrl10[] = "NO";
const char str_freeze_ctrl11[] = "JOYSTICK SWAP:";
const char str_freeze_ctrl14[] = "T A S K";
const char str_freeze_ctrl15[] = "-";

const char str_freeze_ctrl16a[] = "   P A U S E D   S T A T E";
unsigned char str_freeze_ctrl16b[] = "    S L O T #   x x x x x";

const char str_freeze_ctrl17[] = " +";
const char str_freeze_ctrl18[] = "TYPE    :";
char str_freeze_ctrl19[] = "OPERATING SYSTEM";
const char str_freeze_ctrl1A[] = "ID      :";
char str_freeze_ctrl1B[] = "255      ";

const char str_freeze_ctrl1Ca[] = "F3 RESUME";
const char str_freeze_ctrl1Cb[] = "F3 LOAD";

const char str_freeze_ctrl1D[] = "F5 RESET";
const char str_freeze_ctrl1E[] = "F7 SAVE TO SLOT";
const char str_freeze_ctrl1F[] = "D R I V E S";
const char str_freeze_ctrl20[] = "0 TYPE  :";
const char str_freeze_ctrl21[] = "IMAGE:D81";
char str_freeze_ctrl22[] = "MUZAK1.D81                      ";
const char str_freeze_ctrl23[] = "8 UNIT #:";
char str_freeze_ctrl24[] = "8        ";
const char str_freeze_ctrl25[] = "1 TYPE  :";
const char str_freeze_ctrl26[] = "3.5\"";
char str_freeze_ctrl27[] = "                                ";
const char str_freeze_ctrl28[] = "9 UNIT #:";
char str_freeze_ctrl29[] = "9        ";
const char str_freeze_ctrl2A[] = "2 MHZ";

extern const char str_freeze_ctrl2B[] = "F1 STATE|";
extern const char str_freeze_ctrl2C[] = "F2 TOOLS";

const char	str_freeze_ctrl2D[] = "A D D I T I O N A L   T O O L S";
const char	str_freeze_ctrl2E[] = "M - MONITOR";
const char	str_freeze_ctrl2F[] = "A - AUDIO MIXER";
const char	str_freeze_ctrl30[] = "S - SPRITE EDITOR";

const char	str_freeze_ctrl41[] = "M A K E   D I S K   I M A G E";
const char  str_freeze_ctrl42[] = "DRIVE   :";
const char  str_freeze_ctrl43[] = "INTRNL.";
const char  str_freeze_ctrl44[] = "EXTRNL.";
const char  str_freeze_ctrl45[] = "SIZE    :";
const char  str_freeze_ctrl46[] = "D81";
const char  str_freeze_ctrl47[] = "D65";
const char  str_freeze_ctrl48[] = "CREATE";

const char	str_freeze_ctrl31[] = "D R I V E   T Y P E";
const char  str_freeze_ctrl32[] = "C O N T E N T S";

const char	str_freeze_ctrl34[] = "NONE";
const char	str_freeze_ctrl35[] = "HARDWARE";
const char	str_freeze_ctrl36[] = "IMAGE FILE";
const char	str_freeze_ctrl37[] = "CUR. DIR:";
const char	str_freeze_ctrl3B[] = "~";
char	str_freeze_ctrl38[] = "/                                  ";
const char	str_freeze_ctrl39[] = "IMAGES  :";

const char  str_freeze_ctrl3D[] = "U P D A T E";
const char  str_freeze_ctrl3E[] = "ACCEPT";
const char  str_freeze_ctrl3F[] = "CANCEL";


//==============================================================================
//==============================================================================

//CPU
#define	POSX_FREEZE_PNL_0 0x26
#define	POSY_FREEZE_PNL_0 0x0A
#define	WIDT_FREEZE_PNL_0 0x2A
#define	HGHT_FREEZE_PNL_0 0x06

//FEATURES
#define	POSX_FREEZE_PNL_1 0x26
#define	POSY_FREEZE_PNL_1 0x10
#define	WIDT_FREEZE_PNL_1 0x2A
#define	HGHT_FREEZE_PNL_1 0x09

//TASK
#define	POSX_FREEZE_PNL_2 0x00
#define	POSY_FREEZE_PNL_2 0x0A
#define	WIDT_FREEZE_PNL_2 0x24
#define	HGHT_FREEZE_PNL_2 0x05

//DRIVES
#define	POSX_FREEZE_PNL_3 0x00
#define	POSY_FREEZE_PNL_3 0x10
#define	WIDT_FREEZE_PNL_3 0x24
#define	HGHT_FREEZE_PNL_3 0x09

//THUMB
#define	POSX_FREEZE_PNL_4 0x00 
#define	POSY_FREEZE_PNL_4 0x03
#define	WIDT_FREEZE_PNL_4 0x24
#define	HGHT_FREEZE_PNL_4 0x07

//FKEYS
#define	POSX_FREEZE_PNL_9 0x26
#define	POSY_FREEZE_PNL_9 0x03
#define	WIDT_FREEZE_PNL_9 0x24
#define	HGHT_FREEZE_PNL_9 0x05


karlModule_t mod_freeze_app = {
//	Object
		sizeof(karlModule_t),		//size
		FARPTRNULLREC,				//parent
		NEARTOEVENTPTR(FreezeModPrepare),//prepare
		NEARTOEVENTPTR(KarlDefModInit),		//initialise
		NEARTOEVENTPTR(KarlDefModChange),		//change
		NEARTOEVENTPTR(KarlDefModRelease),		//release
		STATE_DEFAULT,			//state
		0x0000,					//oldstate
		0x0000,					//options
		0x0000,					//tag
//	Named
		"M65FREEZER      ",		//name
//	Module
		NEARTOFARPTRREC(uns_freeze_app),			//units_p
		0x01};					//unitscnt


judeUInterface_t uni_freeze_ui = {
//	Object
		sizeof(judeUInterface_t),								//size
		NEARTOFARPTRREC(mod_freeze_app),							//parent
		NEARTOEVENTPTR(JudeDefUIPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefUIInit),//			;initialise
		NEARTOEVENTPTR(JudeDefUIChange),//			;change
		NEARTOEVENTPTR(JudeDefUIRelease),//		;release
		STATE_DEFAULT,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//	Named
		"M65FREEZERM3WP  ",//		;name
//	UI
		DWRDTOFARPTRREC(0x3000, 0x0001),//		;mouseloc
		DWRDTOFARPTRREC(0x3200, 0x0001),//		;mptrloc
		0x01,//						;mousepal
		NEARTOFARPTRREC(vws_freeze_ui),//		;views_p
		0x01};//						;viewscnt

karlFarPtr_t uns_freeze_app[] = {
		NEARTOFARPTRREC(uni_freeze_ui)};

//------------------------------------------------------------------------------
//VIEW
//------------------------------------------------------------------------------

judeView_t vew_freeze_view = {
//Object
		sizeof(judeView_t),								//size
		NEARTOFARPTRREC(uni_freeze_ui),							//parent
		NEARTOEVENTPTR(JudeDefViewPrepare),//		;prepare
//		NEARTOEVENTPTR(FreezeViewInit),//			;initialise
		NEARTOEVENTPTR(JudeDefViewInit),
		NEARTOEVENTPTR(JudeDefViewChange),//			;change
		NEARTOEVENTPTR(JudeDefViewRelease),//		;release
		STATE_DEFAULT,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//View
		0x50,//						;width
		0x19,//						;height
		DWRDTOFARPTRREC(0x2000, 0x0001),//				;location
		0x02,//						;cellsize
		NEARTOFARPTRREC(lys_freeze_view),//			;layers_p
		0x01,//						;layerscnt
		NEARTOFARPTRREC(brs_freeze_view),//			;bars_p
		0x02,//						;barscnt
		NEARTOFARPTRREC(pge_freeze_page0),//			;actvpage_p
		NEARTOFARPTRREC(pgs_freeze_view),//			;pages_p
		0x03,//						;pagescnt
		0x0000};//					;linelen

karlFarPtr_t vws_freeze_ui[] = {
		NEARTOFARPTRREC(vew_freeze_view)};

judeLayer_t	lyr_freeze_layer = {
//Object
		sizeof(judeLayer_t),								//size
		NEARTOFARPTRREC(vew_freeze_view),							//parent
		NEARTOEVENTPTR(JudeDefLyrPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefLyrInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLyrChange),//			;change
		NEARTOEVENTPTR(JudeDefLyrRelease),//		;release
		STATE_DEFAULT,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Layer
		0x50,//						;width
		0x0000,//					;offset
		0x00,//						;transparent
		0x01};//						;background

karlFarPtr_t lys_freeze_view[] = {
		NEARTOFARPTRREC(lyr_freeze_layer)};

//------------------------------------------------------------------------------
//BAR 0
//------------------------------------------------------------------------------

judeBar_t	bar_freeze_bar0 = {
//Object
		sizeof(judeBar_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(FreezeMenuBarPrs),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_PAPER,//				;colour
		0x00,//						;posx
		0x00,//						;posy
		0x50,//						;width
		0x01,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_bar0),//			;controls_p
		0x00,//						;controlscnt
//Bar
		0x00};//						;position

karlFarPtr_t cts_freeze_bar0[] = {
		FARPTRNULLREC};


//------------------------------------------------------------------------------
//BAR 1
//------------------------------------------------------------------------------

judeBar_t bar_freeze_bar1 = {
//Object
		sizeof(judeBar_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_SHADOW,//				;colour
		0x00,//						;posx
		0x01,//						;posy
		0x50,//						;width
		0x01,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_bar1),//			;controls_p
		0x02,//						;controlscnt
//Bar
		0x00};//						;position

karlFarPtr_t cts_freeze_bar1[] = {
		NEARTOFARPTRREC(pbt_freeze_control2B),
		NEARTOFARPTRREC(pbt_freeze_control2C)};

judePageBtnCtrl_t	pbt_freeze_control2B = {
//Object
		sizeof(judePageBtnCtrl_t),								//size
		NEARTOFARPTRREC(bar_freeze_bar1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPBtChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_TEXTACCEL2X | OPT_NODOWNACTV,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPBtPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(bar_freeze_bar1),//			;owner
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x01,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2B),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF1,//						;accelchar
		NEARTOFARPTRREC(pge_freeze_page0)};//						

judePageBtnCtrl_t	pbt_freeze_control2C = {
//Object
		sizeof(judePageBtnCtrl_t),								//size
		NEARTOFARPTRREC(bar_freeze_bar1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPBtChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_TEXTACCEL2X | OPT_NODOWNACTV,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPBtPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(bar_freeze_bar1),//			;owner
		CLR_FACE,//				;colour
		0x09,//						;posx
		0x01,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2C),//			; text_p
		0x01,//						;textoffx
		0x01,//						;textaccel
		0xF2,//						;accelchar
		NEARTOFARPTRREC(pge_freeze_page1)};//						


karlFarPtr_t brs_freeze_view[] = {
		NEARTOFARPTRREC(bar_freeze_bar0),
		NEARTOFARPTRREC(bar_freeze_bar1)};

karlFarPtr_t pgs_freeze_view[] = {
		NEARTOFARPTRREC(pge_freeze_page0),
		NEARTOFARPTRREC(pge_freeze_page1),
		NEARTOFARPTRREC(pge_freeze_page2)};


//------------------------------------------------------------------------------
//PAGE 0 STATE
//------------------------------------------------------------------------------


judePage_t	pge_freeze_page0 = {
//Object
		sizeof(judePage_t),								//size
		NEARTOFARPTRREC(lyr_freeze_layer),							//parent
		NEARTOEVENTPTR(JudeDefPgePrepare),//		;prepare
		NEARTOEVENTPTR(FreezePgeInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPgeChange),//			;change
		NEARTOEVENTPTR(JudeDefPgeRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPgePresent),//		;present
		NEARTOEVENTPTR(FreezePage0Keypress),//					;keypress
		FARPTRNULLREC,//				;owner
		CLR_EMPTY,//				;colour
		0x00,//						;posx
		0x02,//						;posy
		0x50,//						;width
		0x17,//						;height
//Page
		FARPTRNULLREC,//				;pagenxt
		FARPTRNULLREC,//				;pagebak
		NEARTOFARPTRREC(str_freeze_page0),//			;text_p
		0x00,//						;textoffx
		NEARTOFARPTRREC(pns_freeze_page0),//			;panels_p
		0x06};//						;panelscnt


karlFarPtr_t pns_freeze_page0[] = {
		NEARTOFARPTRREC(pnl_freeze_panel2),
		NEARTOFARPTRREC(pnl_freeze_panel3),
		NEARTOFARPTRREC(pnl_freeze_panel9),
		NEARTOFARPTRREC(pnl_freeze_panel0),
		NEARTOFARPTRREC(pnl_freeze_panel1),
		NEARTOFARPTRREC(pnl_freeze_panel4)};


//------------------------------------------------------------------------------
//PANEL 0 CPU
//------------------------------------------------------------------------------
judePanel_t	pnl_freeze_panel0 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_INSET,//				;colour
		POSX_FREEZE_PNL_0,//						;posx
		POSY_FREEZE_PNL_0,//						;posy
		WIDT_FREEZE_PNL_0,//						;width
		HGHT_FREEZE_PNL_0,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel0),//			;controls_p
		0x09};//						;controlscnt

karlFarPtr_t cts_freeze_panel0[] = {
		NEARTOFARPTRREC(txt_freeze_control0),
		NEARTOFARPTRREC(lbl_freeze_control1),
		NEARTOFARPTRREC(rgp_freeze_control2),
		NEARTOFARPTRREC(rbt_freeze_control3),
		NEARTOFARPTRREC(lbl_freeze_control4),
		NEARTOFARPTRREC(rgp_freeze_control5),
		NEARTOFARPTRREC(rbt_freeze_control2A),
		NEARTOFARPTRREC(rbt_freeze_control6),
		NEARTOFARPTRREC(rbt_freeze_control7)};


//------------------------------------------------------------------------------
//PANEL 1 Features
//------------------------------------------------------------------------------
judePanel_t	pnl_freeze_panel1 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_INSET,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1,//						;posy
		WIDT_FREEZE_PNL_1,//						;width
		HGHT_FREEZE_PNL_1,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel1),//			;controls_p
		0x0D};//						;controlscnt


karlFarPtr_t cts_freeze_panel1[] = {
		NEARTOFARPTRREC(txt_freeze_control8),
		NEARTOFARPTRREC(lbl_freeze_control9),
		NEARTOFARPTRREC(rgp_freeze_controlA),
		NEARTOFARPTRREC(rbt_freeze_control40),
		NEARTOFARPTRREC(lbl_freeze_controlB),
		NEARTOFARPTRREC(rgp_freeze_controlC),
		NEARTOFARPTRREC(rbt_freeze_controlD),
		NEARTOFARPTRREC(lbl_freeze_controlE),
		NEARTOFARPTRREC(rgp_freeze_controlF),
		NEARTOFARPTRREC(rbt_freeze_control10),
		NEARTOFARPTRREC(lbl_freeze_control11),
		NEARTOFARPTRREC(rgp_freeze_control12),
		NEARTOFARPTRREC(rbt_freeze_control13)};


//------------------------------------------------------------------------------
//PANEL 2 Task
//------------------------------------------------------------------------------
judePanel_t pnl_freeze_panel2 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_INSET,//				;colour
		POSX_FREEZE_PNL_2,
		POSY_FREEZE_PNL_2,
		WIDT_FREEZE_PNL_2,
		HGHT_FREEZE_PNL_2,
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel2),//			;controls_p
		0x07};//						;controlscnt

karlFarPtr_t cts_freeze_panel2[] = {
		NEARTOFARPTRREC(ctl_freeze_control15),
		NEARTOFARPTRREC(ctl_freeze_control16),
		NEARTOFARPTRREC(ctl_freeze_control17),
		NEARTOFARPTRREC(lbl_freeze_control18),
		NEARTOFARPTRREC(txt_freeze_control19),
		NEARTOFARPTRREC(lbl_freeze_control1A),
		NEARTOFARPTRREC(txt_freeze_control1B)};


//------------------------------------------------------------------------------
//PANEL 9 FKeys
//------------------------------------------------------------------------------
judePanel_t pnl_freeze_panel9 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_INSET,//				;colour
		POSX_FREEZE_PNL_9,
		POSY_FREEZE_PNL_9,
		WIDT_FREEZE_PNL_9,
		HGHT_FREEZE_PNL_9,
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel9),//			;controls_p
		0x03};//						;controlscnt

karlFarPtr_t cts_freeze_panel9[] = {
		NEARTOFARPTRREC(ctl_freeze_control1C),
		NEARTOFARPTRREC(ctl_freeze_control1D),
		NEARTOFARPTRREC(ctl_freeze_control1E)};

//------------------------------------------------------------------------------
//PANEL 3 Drives
//------------------------------------------------------------------------------

judePanel_t pnl_freeze_panel3 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_INSET,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3,
		WIDT_FREEZE_PNL_3,
		HGHT_FREEZE_PNL_3,
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel3),//			;controls_p
		0x0B};//						;controlscnt

karlFarPtr_t cts_freeze_panel3[] = {
		NEARTOFARPTRREC(txt_freeze_control1F),
		NEARTOFARPTRREC(lbl_freeze_control20),
		NEARTOFARPTRREC(ctl_freeze_control21),
		NEARTOFARPTRREC(txt_freeze_control22),
		NEARTOFARPTRREC(lbl_freeze_control23),
		NEARTOFARPTRREC(ctl_freeze_control24),
		NEARTOFARPTRREC(lbl_freeze_control25),
		NEARTOFARPTRREC(ctl_freeze_control26),
		NEARTOFARPTRREC(txt_freeze_control27),
		NEARTOFARPTRREC(lbl_freeze_control28),
		NEARTOFARPTRREC(ctl_freeze_control29)};

//------------------------------------------------------------------------------
//PANEL 4 Thumb
//------------------------------------------------------------------------------

judePanel_t	pnl_freeze_panel4 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page0),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(FreezeThumbPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page0),//			;owner
		CLR_EMPTY,//				;colour
		POSX_FREEZE_PNL_4,
		POSY_FREEZE_PNL_4,
		WIDT_FREEZE_PNL_4,
		HGHT_FREEZE_PNL_4,
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel4),//			;controls_p
		0x01};//						;controlscnt

karlFarPtr_t cts_freeze_panel4[] = {
		NEARTOFARPTRREC(txt_freeze_control14)};



judeControl_t txt_freeze_control0 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_0,//						;posx
		POSY_FREEZE_PNL_0,//						;posy
		WIDT_FREEZE_PNL_0,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl0),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control1 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_0,//						;posx
		POSY_FREEZE_PNL_0 + 2,//						;posy
		0x05,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1),//			; text_p
		0x00,//						;textoffx
		0x01,//						;textaccel
		'o',//						;accelchar
//Label
		NEARTOFARPTRREC(rgp_freeze_control2)};

judeRadioGrpCtrl_t rgp_freeze_control2 = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeModeAutoChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 7,//						;posx
		POSY_FREEZE_PNL_0 + 2,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp0),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_control1)};//						


karlFarPtr_t cts_freeze_rgrp0[] = {
		NEARTOFARPTRREC(rgp_freeze_control2),
		NEARTOFARPTRREC(rbt_freeze_control3)};


judeRadioBtnCtrl_t rbt_freeze_control3 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeMode4502Chg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 0x10,//						;posx
		POSY_FREEZE_PNL_0 + 2,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl3),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control2)};


judeLabelCtrl_t lbl_freeze_control4 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_0,//						;posx
		POSY_FREEZE_PNL_0 + 4,//						;posy
		0x05,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl4),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'f',//						;accelchar
//Label
		FARPTRNULLREC};

judeRadioGrpCtrl_t rgp_freeze_control5 = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeFreq1MHzChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 7,//						;posx
		POSY_FREEZE_PNL_0 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl5),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp1),
		0x04,
		NEARTOFARPTRREC(lbl_freeze_control4)};//						


karlFarPtr_t cts_freeze_rgrp1[] = {
		NEARTOFARPTRREC(rgp_freeze_control5),
		NEARTOFARPTRREC(rbt_freeze_control2A),
		NEARTOFARPTRREC(rbt_freeze_control6),
		NEARTOFARPTRREC(rbt_freeze_control7)};

judeRadioBtnCtrl_t rbt_freeze_control2A = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeFreq2MHzChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 16,//						;posx
		POSY_FREEZE_PNL_0 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2A),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control5)};

judeRadioBtnCtrl_t rbt_freeze_control6 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeFreq3_5MHzChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 0x19,//						;posx
		POSY_FREEZE_PNL_0 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl6),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control5)};

judeRadioBtnCtrl_t rbt_freeze_control7 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel0),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeFreq40MHzChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel0),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_0 + 0x22,//						;posx
		POSY_FREEZE_PNL_0 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl7),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control5)};


judeControl_t txt_freeze_control8 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1,//						;posy
		WIDT_FREEZE_PNL_1,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl8),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control9 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1 + 2,//						;posy
		0x0E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl9),//			; text_p
		0x00,//						;textoffx
		0x01,//						;textaccel
		'r',//						;accelchar
//Label
		NEARTOFARPTRREC(rgp_freeze_controlA)};

judeRadioGrpCtrl_t rgp_freeze_controlA = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeCRTEnblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x10,//						;posx
		POSY_FREEZE_PNL_1 + 2,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlF),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp6),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_control9)};//

karlFarPtr_t cts_freeze_rgrp6[] = {
		NEARTOFARPTRREC(rgp_freeze_controlA),
		NEARTOFARPTRREC(rbt_freeze_control40)};


judeRadioBtnCtrl_t rbt_freeze_control40 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeCRTDsblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x19,//						;posx
		POSY_FREEZE_PNL_1 + 2,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl10),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_controlA)};


judeLabelCtrl_t lbl_freeze_controlB = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1 + 4,//						;posy
		0x0E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlB),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'v',//						;accelchar
//Label
		NEARTOFARPTRREC(rgp_freeze_controlC)};


judeRadioGrpCtrl_t rgp_freeze_controlC = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeVideoPALChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x10,//						;posx
		POSY_FREEZE_PNL_1 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlC),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp2),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_controlB)};//						

karlFarPtr_t cts_freeze_rgrp2[] = {
		NEARTOFARPTRREC(rgp_freeze_controlC),
		NEARTOFARPTRREC(rbt_freeze_controlD)};


judeRadioBtnCtrl_t rbt_freeze_controlD = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeVideoNTSCChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x19,//						;posx
		POSY_FREEZE_PNL_1 + 4,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlD),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_controlC)};


judeLabelCtrl_t lbl_freeze_controlE = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1 + 6,//						;posy
		0x0E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlE),//			; text_p
		0x00,//						;textoffx
		0x03,//						;textaccel
		't',//						;accelchar
//Label
		NEARTOFARPTRREC(rgp_freeze_controlF)};


judeRadioGrpCtrl_t rgp_freeze_controlF = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeCartEnblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x10,//						;posx
		POSY_FREEZE_PNL_1 + 6,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlF),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp3),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_controlE)};//

karlFarPtr_t cts_freeze_rgrp3[] = {
		NEARTOFARPTRREC(rgp_freeze_controlF),
		NEARTOFARPTRREC(rbt_freeze_control10)};


judeRadioBtnCtrl_t rbt_freeze_control10 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeCartDsblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x19,//						;posx
		POSY_FREEZE_PNL_1 + 6,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl10),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_controlF)};

judeLabelCtrl_t lbl_freeze_control11 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_1,//						;posx
		POSY_FREEZE_PNL_1 + 8,//						;posy
		0x0E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl11),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'j',//						;accelchar
//Label
		NEARTOFARPTRREC(rgp_freeze_control12)};


judeRadioGrpCtrl_t rgp_freeze_control12 = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeJoySEnblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x10,//						;posx
		POSY_FREEZE_PNL_1 + 8,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlF),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp4),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_control11)};//

karlFarPtr_t cts_freeze_rgrp4[] = {
		NEARTOFARPTRREC(rgp_freeze_control12),
		NEARTOFARPTRREC(rbt_freeze_control13)};


judeRadioBtnCtrl_t rbt_freeze_control13 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeJoySDsblChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_1 + 0x19,//						;posx
		POSY_FREEZE_PNL_1 + 8,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl10),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control12)};


judeControl_t txt_freeze_control14 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel4),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel4),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_4,
		POSY_FREEZE_PNL_4,
		WIDT_FREEZE_PNL_4,
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl14),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t ctl_freeze_control15 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeSlotDecChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_2,
		POSY_FREEZE_PNL_2,
		0x02,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl15),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'-'};//						;accelchar

judeControl_t ctl_freeze_control16 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_PAPER,//				;colour
		POSX_FREEZE_PNL_2 + 3,
		POSY_FREEZE_PNL_2,
		0x1E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl16a),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t ctl_freeze_control17 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeSlotIncChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_2 + 0x22,
		POSY_FREEZE_PNL_2,
		0x02,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl17),//			; text_p
		0x00,//						;textoffx
		0x01,//						;textaccel
		'+'};//						;accelchar

judeControl_t lbl_freeze_control18 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_SHADOW,//				;colour
		POSX_FREEZE_PNL_2,
		POSY_FREEZE_PNL_2 + 2,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl18),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t txt_freeze_control19 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_2 + 0x0B,
		POSY_FREEZE_PNL_2 + 2,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl19),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t lbl_freeze_control1A = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_SHADOW,//				;colour
		POSX_FREEZE_PNL_2,
		POSY_FREEZE_PNL_2 + 4,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1A),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t txt_freeze_control1B = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_2 + 0x0B,
		POSY_FREEZE_PNL_2 + 4,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1B),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t ctl_freeze_control1C = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel9),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeSlotResumeChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_TEXTACCEL2X,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel9),//			;owner
		CLR_ACCEPT,//				;colour
		POSX_FREEZE_PNL_9,
		POSY_FREEZE_PNL_9,
		0x18,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1Ca),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF3};//						;accelchar

judeControl_t ctl_freeze_control1D = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel9),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeSlotResetChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_TEXTACCEL2X,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel9),//			;owner
		CLR_APPLY,//				;colour
		POSX_FREEZE_PNL_9,
		POSY_FREEZE_PNL_9 + 2,
		0x18,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1D),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF5};//						;accelchar

judeControl_t ctl_freeze_control1E = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel9),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeSlotSaveChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_TEXTACCEL2X,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel9),//			;owner
		CLR_ABORT,//				;colour
		POSX_FREEZE_PNL_9,
		POSY_FREEZE_PNL_9 + 4,
		0x18,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1E),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF7};//						;accelchar


judeControl_t txt_freeze_control1F = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3,
		WIDT_FREEZE_PNL_3,
		0x01,
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1F),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control20 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3 + 2,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl20),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'0',//						;accelchar
//Label
		NEARTOFARPTRREC(ctl_freeze_control21)};

judeControl_t ctl_freeze_control21 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDiskImg0Chg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 2,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl21),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t txt_freeze_control22 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE | OPT_TEXTCONTMRK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 3,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl22),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control23 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3 + 4,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl23),//			; FACE_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'8',//						;accelchar\
//Label
		NEARTOFARPTRREC(ctl_freeze_control24)};

judeControl_t ctl_freeze_control24 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDiskNum0Chg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 4,
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl24),//			; FACE_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control25 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3 + 6,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl25),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'1',//						;accelchar\
//Label
		NEARTOFARPTRREC(ctl_freeze_control26)};


judeControl_t ctl_freeze_control26 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 6,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl26),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t txt_freeze_control27 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE | OPT_TEXTCONTMRK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_TEXT,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 7,
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl27),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control28 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_ITEM,//				;colour
		POSX_FREEZE_PNL_3,
		POSY_FREEZE_PNL_3 + 8,
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl28),//			; FACE_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'9',//						;accelchar\
//Label
		NEARTOFARPTRREC(ctl_freeze_control29)};


judeControl_t ctl_freeze_control29 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel3),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDiskNum1Chg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel3),//			;owner
		CLR_FACE,//				;colour
		POSX_FREEZE_PNL_3 + 0x0B,
		POSY_FREEZE_PNL_3 + 8,
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl29),//			; FACE_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


judePage_t	pge_freeze_page1 = {
//Object
		sizeof(judePage_t),								//size
		NEARTOFARPTRREC(lyr_freeze_layer),							//parent
		NEARTOEVENTPTR(JudeDefPgePrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPgeInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPgeChange),//			;change
		NEARTOEVENTPTR(JudeDefPgeRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPgePresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		FARPTRNULLREC,//				;owner
		CLR_EMPTY,//				;colour
		0x00,//						;posx
		0x02,//						;posy
		0x50,//						;width
		0x17,//						;height
//Page
		FARPTRNULLREC,//				;pagenxt
		FARPTRNULLREC,//				;pagebak
		NEARTOFARPTRREC(str_freeze_page1),//			;text_p
		0x00,//						;textoffx
		NEARTOFARPTRREC(pns_freeze_page1),//			;panels_p
		0x02};//						;panelscnt

karlFarPtr_t pns_freeze_page1[] = {
		NEARTOFARPTRREC(pnl_freeze_panel5),
		NEARTOFARPTRREC(pnl_freeze_panelA)};


judePanel_t	pnl_freeze_panel5 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page1),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page1),//			;owner
		CLR_INSET,//				;colour
		0x00,//						;posx
		0x03,//						;posy
		0x21,//						;width
		0x14,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel5),//			;controls_p
		0x04};//						;controlscnt

karlFarPtr_t cts_freeze_panel5[] = {
		NEARTOFARPTRREC(txt_freeze_control2D),
		NEARTOFARPTRREC(btn_freeze_control2E),
		NEARTOFARPTRREC(btn_freeze_control2F),
		NEARTOFARPTRREC(btn_freeze_control30)};


judeControl_t txt_freeze_control2D = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel5),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel5),//			;owner
		CLR_TEXT,//				;colour
		0x00,//						;posx
		0x03,//						;posy
		0x24,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2D),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t btn_freeze_control2E = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel5),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeToolMonChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel5),//			;owner
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x05,//						;posy
		0x24,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2E),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'm'};//						;accelchar

judeControl_t btn_freeze_control2F = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel5),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeToolAudChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel5),//			;owner
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x07,//						;posy
		0x24,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2F),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'a'};//						;accelchar

judeControl_t btn_freeze_control30 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel5),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeToolSprChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel5),//			;owner
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x09,//						;posy
		0x24,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl30),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		's'};//						;accelchar


judePanel_t	pnl_freeze_panelA = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page1),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page1),//			;owner
		CLR_INSET,//				;colour
		0x26,//						;posx
		0x03,//						;posy
		0x2A,//						;width
		0x14,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panelA),//			;controls_p
		0x05};//						;controlscnt

karlFarPtr_t cts_freeze_panelA[] = {
		NEARTOFARPTRREC(txt_freeze_control41),
		// NEARTOFARPTRREC(lbl_freeze_control42),
		// NEARTOFARPTRREC(rgp_freeze_control43),
		// NEARTOFARPTRREC(rbt_freeze_control44),
		NEARTOFARPTRREC(lbl_freeze_control45),
		NEARTOFARPTRREC(rgp_freeze_control46),
		NEARTOFARPTRREC(rbt_freeze_control47),
		NEARTOFARPTRREC(btn_freeze_control48)};


judeControl_t txt_freeze_control41 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
		CLR_TEXT,//				;colour
		0x26,//						;posx
		0x03,//						;posy
		0x2A,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl41),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

// judeLabelCtrl_t lbl_freeze_control42 = {
// //Object
// 		sizeof(judeLabelCtrl_t),								//size
// 		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
// 		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
// 		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
// 		NEARTOEVENTPTR(JudeDefLblChange),//			;change
// 		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
// 		STATE_DEFCTRL,//			;state
// 		0x0000,//					;oldstate
// 		OPT_NONAVIGATE,//					;options
// 		0x0000,//					;tag
// //Element
// 		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
// 		EVENTPTRNULLREC,//					;keypress
// 		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
// 		CLR_ITEM,//				;colour
// 		0x26,//						;posx
// 		0x05,//						;posy
// 		0x09,//						;width
// 		0x01,//						;height
// //Control
// 		NEARTOFARPTRREC(str_freeze_ctrl42),//			; text_p
// 		0x00,//						;textoffx
// 		0x03,//						;textaccel
// 		'v',
// 		NEARTOFARPTRREC(rgp_freeze_control43)};

// judeRadioGrpCtrl_t rgp_freeze_control43 = {
// //Object
// 		sizeof(judeRadioGrpCtrl_t),								//size
// 		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
// 		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
// 		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
// 		NEARTOEVENTPTR(JudeDefRGpChange),//			;change
// 		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
// 		STATE_DEFCTRL,//			;state
// 		0x0000,//					;oldstate
// 		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
// 		0x0001,//					;tag
// //Element
// 		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
// 		EVENTPTRNULLREC,//					;keypress
// 		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
// 		CLR_FACE,//				;colour
// 		0x31,//						;posx
// 		0x05,//						;posy
// 		0x08,//						;width
// 		0x01,//						;height
// //Control
// 		NEARTOFARPTRREC(str_freeze_ctrl43),//			; text_p
// 		0x01,//						;textoffx
// 		0xFF,//						;textaccel
// 		0x00,
// //Radio Group
// 		NEARTOFARPTRREC(cts_freeze_rgrp7),
// 		0x02,
// 		NEARTOFARPTRREC(lbl_freeze_control42)};//

// karlFarPtr_t cts_freeze_rgrp7[] = {
// 		NEARTOFARPTRREC(rgp_freeze_control43),
// 		NEARTOFARPTRREC(rbt_freeze_control44)};


// judeRadioBtnCtrl_t rbt_freeze_control44 = {
// //Object
// 		sizeof(judeRadioBtnCtrl_t),								//size
// 		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
// 		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
// 		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
// 		NEARTOEVENTPTR(JudeDefRBtChange),//			;change
// 		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
// 		STATE_DEFCTRL,//			;state
// 		0x0000,//					;oldstate
// 		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
// 		0x0000,//					;tag
// //Element
// 		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
// 		EVENTPTRNULLREC,//					;keypress
// 		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
// 		CLR_FACE,//				;colour
// 		0x3A,//						;posx
// 		0x05,//						;posy
// 		0x08,//						;width
// 		0x01,//						;height
// //Control
// 		NEARTOFARPTRREC(str_freeze_ctrl44),//			; text_p
// 		0x01,//						;textoffx
// 		0xFF,//						;textaccel
// 		0x00,//
// //Radio Button
// 		NEARTOFARPTRREC(rgp_freeze_control43)};

judeLabelCtrl_t lbl_freeze_control45 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
		CLR_ITEM,//				;colour
		0x26,//						;posx
		0x05,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl45),//			; text_p
		0x00,//						;textoffx
		0x03,//						;textaccel
		'z',
		NEARTOFARPTRREC(rgp_freeze_control46)};

judeRadioGrpCtrl_t rgp_freeze_control46 = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefRGpChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0001,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
		CLR_FACE,//				;colour
		0x31,//						;posx
		0x05,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl46),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp8),
		0x02,
		NEARTOFARPTRREC(lbl_freeze_control45)};//

karlFarPtr_t cts_freeze_rgrp8[] = {
		NEARTOFARPTRREC(rgp_freeze_control46),
		NEARTOFARPTRREC(rbt_freeze_control47)};


judeRadioBtnCtrl_t rbt_freeze_control47 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefRBtChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
		CLR_FACE,//				;colour
		0x3A,//						;posx
		0x05,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl47),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control46)};

judeControl_t btn_freeze_control48 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panelA),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeMkDskChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panelA),//			;owner
		CLR_ACCEPT,//				;colour
		0x46,//						;posx
		0x05,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl48),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'c'};//						;accelchar


judePage_t	pge_freeze_page2 = {
//Object
		sizeof(judePage_t),								//size
		NEARTOFARPTRREC(lyr_freeze_layer),							//parent
		NEARTOEVENTPTR(JudeDefPgePrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPgeInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPgeChange),//			;change
		NEARTOEVENTPTR(JudeDefPgeRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPgePresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		FARPTRNULLREC,//				;owner
		CLR_EMPTY,//				;colour
		0x00,//						;posx
		0x02,//						;posy
		0x50,//						;width
		0x17,//						;height
//Page
		FARPTRNULLREC,//				;pagenxt
		FARPTRNULLREC,//				;pagebak
		NEARTOFARPTRREC(str_freeze_page2),//			;text_p
		0x00,//						;textoffx
		NEARTOFARPTRREC(pns_freeze_page2),//			;panels_p
		0x03};//						;panelscnt

karlFarPtr_t pns_freeze_page2[] = {
		NEARTOFARPTRREC(pnl_freeze_panel6),
		NEARTOFARPTRREC(pnl_freeze_panel7),
		NEARTOFARPTRREC(pnl_freeze_panel8)};

judePanel_t	pnl_freeze_panel6 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page2),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page2),//			;owner
		CLR_INSET,//				;colour
		0x00,//						;posx
		0x03,//						;posy
		0x38,//						;width
		0x15,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel6),//			;controls_p
		0x0A};//						;controlscnt

karlFarPtr_t cts_freeze_panel6[] = {
		NEARTOFARPTRREC(txt_freeze_control31),
		NEARTOFARPTRREC(lbl_freeze_control33),
		NEARTOFARPTRREC(rgp_freeze_control34),
		NEARTOFARPTRREC(rbt_freeze_control35),
		NEARTOFARPTRREC(rbt_freeze_control36),
		NEARTOFARPTRREC(lbl_freeze_control37),
		NEARTOFARPTRREC(btn_freeze_control3B),
		NEARTOFARPTRREC(txt_freeze_control38),
		NEARTOFARPTRREC(lbl_freeze_control39),
		NEARTOFARPTRREC(lbx_freeze_control3A)};

judePanel_t	pnl_freeze_panel7 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page2),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page2),//			;owner
		CLR_INSET,//				;colour
		0x3C,//						;posx
		0x03,//						;posy
		0x14,//						;width
		0x12,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel7),//			;controls_p
		0x02};//						;controlscnt

karlFarPtr_t cts_freeze_panel7[] = {
		NEARTOFARPTRREC(txt_freeze_control32),
		NEARTOFARPTRREC(lbx_freeze_control3C)};

judeControl_t txt_freeze_control31 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_TEXT,//				;colour
		0x00,//						;posx
		0x03,//						;posy
		0x38,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl31),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t txt_freeze_control32 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel7),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel7),//			;owner
		CLR_TEXT,//				;colour
		0x3C,//						;posx
		0x03,//						;posy
		0x14,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl32),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control33 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_ITEM,//				;colour
		0x00,//						;posx
		0x05,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl18),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		't',
		FARPTRNULLREC};

judeRadioGrpCtrl_t rgp_freeze_control34 = {
//Object
		sizeof(judeRadioGrpCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefRGpChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_FACE,//				;colour
		0x0A,//						;posx
		0x05,//						;posy
		0x0C,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl34),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Group
		NEARTOFARPTRREC(cts_freeze_rgrp5),
		0x03,
		NEARTOFARPTRREC(lbl_freeze_control33)};//						


karlFarPtr_t cts_freeze_rgrp5[] = {
		NEARTOFARPTRREC(rgp_freeze_control34),
		NEARTOFARPTRREC(rbt_freeze_control35),
		NEARTOFARPTRREC(rbt_freeze_control36)};


judeRadioBtnCtrl_t rbt_freeze_control35 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefRBtChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_FACE,//				;colour
		0x17,//						;posx
		0x05,//						;posy
		0x0C,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl35),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control34)};

judeRadioBtnCtrl_t rbt_freeze_control36 = {
//Object
		sizeof(judeRadioBtnCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDrvTypeImgChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NOAUTOCHKOF | OPT_AUTOCHECK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_FACE,//				;colour
		0x24,//						;posx
		0x05,//						;posy
		0x0C,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl36),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control34)};

judeLabelCtrl_t lbl_freeze_control37 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_SHADOW,//				;colour
		0x00,//						;posx
		0x07,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl37),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Label
		FARPTRNULLREC};


judeControl_t btn_freeze_control3B = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDirUpChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_FACE,//				;colour
		0x0A,//						;posx
		0x07,//						;posy
		0x02,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl3B),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0x5F};//						;accelchar

judeControl_t txt_freeze_control38 = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_TEXT,//				;colour
		0x0D,//						;posx
		0x07,//						;posy
		0x2B,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl38),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeLabelCtrl_t lbl_freeze_control39 = {
//Object
		sizeof(judeLabelCtrl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefLblChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_SHADOW,//				;colour
		0x00,//						;posx
		0x09,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl39),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00,
//Label
		FARPTRNULLREC};

freezeListBox_t lbx_freeze_control3A = {
//Object
		sizeof(freezeListBox_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel6),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeLBxChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE | STATE_ENABLED,//			;state
		0x0000,//					;oldstate
		OPT_AUTOTRACK,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(FreezeLBxPresent),//		;present
		NEARTOEVENTPTR(FreezeLBxPressed),//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel6),//			;owner
		CLR_TEXT,//				;colour
		0x0A,//						;posx
		0x09,//						;posy
		0x2E,//						;width
		0x10,//						;height
//Control
		FARPTRNULLREC,//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//ListBox
		NEARTOEVENTPTR(FreezeImgLstSelect),
		DWRDTOFARPTRREC(0x0000, 0x0004),
		0x00,
		0x40,
		0x00,
		0x00,
		0x00,
		0xFF};

freezeListBox_t lbx_freeze_control3C = {
//Object
		sizeof(freezeListBox_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel7),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeLBxChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_VISIBLE,//			;state
		0x0000,//					;oldstate
		OPT_AUTOTRACK | OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(FreezeLBxPresent),//		;present
		NEARTOEVENTPTR(FreezeLBxPressed),//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel7),//			;owner
		CLR_TEXT,//				;colour
		0x3C,//						;posx
		0x05,//						;posy
		0x14,//						;width
		0x10,//						;height
//Control
		FARPTRNULLREC,//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00,//						;accelchar
//ListBox
		EVENTPTRNULLREC,
		DWRDTOFARPTRREC(0x6000, 0x0001),
		0x00,
		0x14,
		0x00,
		0x00,
		0x00,
		0xFF};

judePanel_t	pnl_freeze_panel8 = {
//Object
		sizeof(judePanel_t),								//size
		NEARTOFARPTRREC(pge_freeze_page2),							//parent
		NEARTOEVENTPTR(JudeDefPnlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefPnlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefPnlChange),//			;change
		NEARTOEVENTPTR(JudeDefPnlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefPnlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pge_freeze_page2),//			;owner
		CLR_INSET,//				;colour
		0x3C,//						;posx
		0x16,//						;posy
		0x14,//						;width
		0x03,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel8),//			;controls_p
		0x03};//						;controlscnt

karlFarPtr_t cts_freeze_panel8[] = {
		NEARTOFARPTRREC(txt_freeze_control3D),
		NEARTOFARPTRREC(btn_freeze_control3E),
		NEARTOFARPTRREC(btn_freeze_control3F)};

judeControl_t txt_freeze_control3D = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel8),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(JudeDefCtlChange),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		OPT_NONAVIGATE,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel8),//			;owner
		CLR_TEXT,//				;colour
		0x3C,//						;posx
		0x16,//						;posy
		0x14,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl3D),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t btn_freeze_control3E = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel8),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDrvAcceptChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel8),//			;owner
		CLR_ACCEPT,//				;colour
		0x3C,//						;posx
		0x18,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl3E),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		KEY_ASC_CR};//						;accelchar

judeControl_t btn_freeze_control3F = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel8),							//parent
		NEARTOEVENTPTR(JudeDefCtlPrepare),//		;prepare
		NEARTOEVENTPTR(JudeDefCtlInit),//			;initialise
		NEARTOEVENTPTR(FreezeDrvCancelChg),//			;change
		NEARTOEVENTPTR(JudeDefCtlRelease),//		;release
		STATE_DEFCTRL,//			;state
		0x0000,//					;oldstate
		0x0000,//					;options
		0x0000,//					;tag
//Element
		NEARTOEVENTPTR(JudeDefCtlPresent),//		;present
		EVENTPTRNULLREC,//					;keypress
		NEARTOFARPTRREC(pnl_freeze_panel8),//			;owner
		CLR_ABORT,//				;colour
		0x47,//						;posx
		0x18,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl3F),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		KEY_M65_ESC};//						;accelchar
