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
const char str_freeze_ctrl9[] = "ROM          :";
const char str_freeze_ctrlA[] = "C65 920224";
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

const char	str_freeze_ctrl2D[] = "T O O L S";
const char	str_freeze_ctrl2E[] = "M - MONITOR";
const char	str_freeze_ctrl2F[] = "A - AUDIO MIXER";
const char	str_freeze_ctrl30[] = "S - SPRITE EDITOR";


extern const char str_freeze_ctrl2B[] = "F1 STATE|";
extern const char str_freeze_ctrl2C[] = "F2 TOOLS";


//==============================================================================
//==============================================================================


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
		DWRDTOFARPTRREC(0x1000, 0x0001),//		;mouseloc
		DWRDTOFARPTRREC(0x1200, 0x0001),//		;mptrloc
		0x01,//						;mousepal
		NEARTOFARPTRREC(vws_freeze_ui),//		;views_p
		0x01};//						;viewscnt

karlFarPtr_t uns_freeze_app[] = {
		NEARTOFARPTRREC(uni_freeze_ui)};

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
		DWRDTOFARPTRREC(0x0000, 0x0001),//				;location
		0x02,//						;cellsize
		NEARTOFARPTRREC(lys_freeze_view),//			;layers_p
		0x01,//						;layerscnt
		NEARTOFARPTRREC(brs_freeze_view),//			;bars_p
		0x02,//						;barscnt
		NEARTOFARPTRREC(pge_freeze_page0),//			;actvpage_p
		NEARTOFARPTRREC(pgs_freeze_view),//			;pages_p
		0x02,//						;pagescnt
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
		NEARTOFARPTRREC(str_freeze_page0),//			;text_p
		0x00,//						;textoffx
		NEARTOFARPTRREC(pns_freeze_page0),//			;panels_p
		0x05};//						;panelscnt


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
		NEARTOFARPTRREC(pge_freeze_page1)};


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
		0x00,//						;posx
		0x0A,//						;posy
		0x29,//						;width
		0x06,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel0),//			;controls_p
		0x09};//						;controlscnt


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
		0x00,//						;posx
		0x10,//						;posy
		0x20,//						;width
		0x09,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel1),//			;controls_p
		0x0C};//						;controlscnt


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
		0x2C,//						;posx
		0x02,//						;posy
		0x24,//						;width
		0x0D,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel2),//			;controls_p
		0x0B};//						;controlscnt

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
		0x2C,//						;posx
		0x10,//						;posy
		0x24,//						;width
		0x09,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel3),//			;controls_p
		0x0B};//						;controlscnt


karlFarPtr_t pns_freeze_page0[] = {
		NEARTOFARPTRREC(pnl_freeze_panel2),
		NEARTOFARPTRREC(pnl_freeze_panel3),
		NEARTOFARPTRREC(pnl_freeze_panel0),
		NEARTOFARPTRREC(pnl_freeze_panel1),
		NEARTOFARPTRREC(pnl_freeze_panel4)};


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
		0x00,//						;posx
		0x0A,//						;posy
		0x29,//						;width
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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x0C,//						;posy
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
		0x06,//						;posx
		0x0C,//						;posy
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
		0x0F,//						;posx
		0x0C,//						;posy
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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x0E,//						;posy
		0x05,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl4),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'f',//						;accelchar
//Label
		EVENTPTRNULLREC};

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
		0x06,//						;posx
		0x0E,//						;posy
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
		0x0F,//						;posx
		0x0E,//						;posy
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
		0x18,//						;posx
		0x0E,//						;posy
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
		0x21,//						;posx
		0x0E,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl7),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control5)};


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
		0x00,//						;posx
		0x10,//						;posy
		0x29,//						;width
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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x12,//						;posy
		0x0E,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl9),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'r',//						;accelchar
//Label
		NEARTOFARPTRREC(ctl_freeze_controlA)};

judeControl_t ctl_freeze_controlA = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel1),							//parent
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
		NEARTOFARPTRREC(pnl_freeze_panel1),//			;owner
		CLR_PAPER,//				;colour
		0x0F,//						;posx
		0x12,//						;posy
		0x11,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrlA),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x14,//						;posy
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
		0x0F,//						;posx
		0x14,//						;posy
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
		0x18,//						;posx
		0x14,//						;posy
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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x16,//						;posy
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
		0x0F,//						;posx
		0x16,//						;posy
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
		0x18,//						;posx
		0x16,//						;posy
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
		CLR_FACE,//				;colour
		0x00,//						;posx
		0x18,//						;posy
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
		0x0F,//						;posx
		0x18,//						;posy
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
		0x18,//						;posx
		0x18,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl10),//			; text_p
		0x01,//						;textoffx
		0xFF,//						;textaccel
		0x00,//
//Radio Button
		NEARTOFARPTRREC(rgp_freeze_control12)};


karlFarPtr_t cts_freeze_panel1[] = {
		NEARTOFARPTRREC(txt_freeze_control8),
		NEARTOFARPTRREC(lbl_freeze_control9),
		NEARTOFARPTRREC(ctl_freeze_controlA),
		NEARTOFARPTRREC(lbl_freeze_controlB),
		NEARTOFARPTRREC(rgp_freeze_controlC),
		NEARTOFARPTRREC(rbt_freeze_controlD),
		NEARTOFARPTRREC(lbl_freeze_controlE),
		NEARTOFARPTRREC(rgp_freeze_controlF),
		NEARTOFARPTRREC(rbt_freeze_control10),
		NEARTOFARPTRREC(lbl_freeze_control11),
		NEARTOFARPTRREC(rgp_freeze_control12),
		NEARTOFARPTRREC(rbt_freeze_control13)};


judeControl_t txt_freeze_control14 = {
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
		0x2C,//						;posx
		0x02,//						;posy
		0x24,//						;width
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
		0x2C,//						;posx
		0x04,//						;posy
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
		0x2F,//						;posx
		0x04,//						;posy
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
		0x4E,//						;posx
		0x04,//						;posy
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
		0x2C,//						;posx
		0x06,//						;posy
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
		0x37,//						;posx
		0x06,//						;posy
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
		0x2C,//						;posx
		0x08,//						;posy
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
		0x37,//						;posx
		0x08,//						;posy
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
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
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
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_FACE,//				;colour
		0x37,//						;posx
		0x0A,//						;posy
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1Ca),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF3};//						;accelchar

judeControl_t ctl_freeze_control1D = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
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
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_FACE,//				;colour
		0x37,//						;posx
		0x0C,//						;posy
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1D),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF5};//						;accelchar

judeControl_t ctl_freeze_control1E = {
//Object
		sizeof(judeControl_t),								//size
		NEARTOFARPTRREC(pnl_freeze_panel2),							//parent
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
		NEARTOFARPTRREC(pnl_freeze_panel2),//			;owner
		CLR_FACE,//				;colour
		0x37,//						;posx
		0x0E,//						;posy
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl1E),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		0xF7};//						;accelchar


karlFarPtr_t cts_freeze_panel2[] = {
		NEARTOFARPTRREC(txt_freeze_control14),
		NEARTOFARPTRREC(ctl_freeze_control15),
		NEARTOFARPTRREC(ctl_freeze_control16),
		NEARTOFARPTRREC(ctl_freeze_control17),
		NEARTOFARPTRREC(lbl_freeze_control18),
		NEARTOFARPTRREC(txt_freeze_control19),
		NEARTOFARPTRREC(lbl_freeze_control1A),
		NEARTOFARPTRREC(txt_freeze_control1B),
		NEARTOFARPTRREC(ctl_freeze_control1C),
		NEARTOFARPTRREC(ctl_freeze_control1D),
		NEARTOFARPTRREC(ctl_freeze_control1E)};


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
		0x2C,//						;posx
		0x10,//						;posy
		0x24,//						;width
		0x01,//						;height
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
		CLR_FACE,//				;colour
		0x2C,//						;posx
		0x12,//						;posy
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
		CLR_PAPER,//				;colour
		0x37,//						;posx
		0x12,//						;posy
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
		0x37,//						;posx
		0x13,//						;posy
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl22),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t lbl_freeze_control23 = {
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
		CLR_FACE,//				;colour
		0x2C,//						;posx
		0x14,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl23),//			; FACE_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'8'};//						;accelchar

judeControl_t ctl_freeze_control24 = {
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
		0x37,//						;posx
		0x14,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl24),//			; FACE_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t lbl_freeze_control25 = {
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
		CLR_FACE,//				;colour
		0x2C,//						;posx
		0x16,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl25),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'1'};//						;accelchar

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
		CLR_PAPER,//				;colour
		0x37,//						;posx
		0x16,//						;posy
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
		0x37,//						;posx
		0x17,//						;posy
		0x19,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl27),//			; text_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

judeControl_t lbl_freeze_control28 = {
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
		CLR_FACE,//				;colour
		0x2C,//						;posx
		0x18,//						;posy
		0x09,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl28),//			; FACE_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'9'};//						;accelchar

judeControl_t ctl_freeze_control29 = {
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
		0x37,//						;posx
		0x18,//						;posy
		0x08,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl29),//			; FACE_p
		0x00,//						;textoffx
		0xFF,//						;textaccel
		0x00};//						;accelchar

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
		0x00,//						;posx
		0x02,//						;posy
		0x29,//						;width
		0x08,//						;height
//Panel
		NEARTOFARPTRREC(lyr_freeze_layer),//			;layer_p
		NEARTOFARPTRREC(cts_freeze_panel4),//			;controls_p
		0x00};//						;controlscnt

karlFarPtr_t cts_freeze_panel4[] = {
	EVENTPTRNULLREC};



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
		0x01};//						;panelscnt

karlFarPtr_t pns_freeze_page1[] = {
		NEARTOFARPTRREC(pnl_freeze_panel5)};


judePanel_t	pnl_freeze_panel5 = {
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
		0x00,//						;posx
		0x03,//						;posy
		0x29,//						;width
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
		0x29,//						;width
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
		0x29,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2E),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'M'};//						;accelchar

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
		0x29,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl2F),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'A'};//						;accelchar

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
		0x29,//						;width
		0x01,//						;height
//Control
		NEARTOFARPTRREC(str_freeze_ctrl30),//			; text_p
		0x00,//						;textoffx
		0x00,//						;textaccel
		'S'};//						;accelchar
