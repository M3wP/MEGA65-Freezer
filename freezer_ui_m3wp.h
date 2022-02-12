#ifdef	INCLUDE_FREEZER_UI_M3WP_H
#else
#define	INCLUDE_FREEZER_UI_M3WP_H

#include "karljr.h"
#include "jude.h"
#include "jude_widgets.h"

typedef	struct	LISTBOX {
		judeControl_t	_control;

		EVENTPTR		select;

		karlFarPtr_t	lines_p;
		byte			linescnt;
		byte			linewidth;
		byte			currline;
		byte			linesoff;
		byte			hotline;
		byte			selline;
	} freezeListBox_t;

extern void __fastcall__	FreezeLBxPresent(void);
extern void __fastcall__	FreezeLBxPressed(void);
extern void __fastcall__	FreezeLBxChange(void);

extern void	__fastcall__	FreezeImgLstSelect(void);

extern void __fastcall__ 	FreezeModPrepare(void);

extern void __fastcall__ 	FreezePgeInit(void);
extern void __fastcall__ 	FreezePage0Keypress(void);

extern void	__fastcall__	FreezeMenuBarPrs(void);

extern void __fastcall__ 	FreezeThumbPresent(void);

extern void __fastcall__ 	FreezeSlotDecChg(void);
extern void __fastcall__ 	FreezeSlotIncChg(void);

extern void	__fastcall__	FreezeSlotResumeChg(void);
extern void	__fastcall__	FreezeSlotResetChg(void);

extern void	__fastcall__	FreezeSlotSaveChg(void);

extern void	__fastcall__	FreezeModeAutoChg(void);
extern void __fastcall__	FreezeMode4502Chg(void);

extern void	__fastcall__	FreezeFreq1MHzChg(void);
extern void	__fastcall__	FreezeFreq2MHzChg(void);
extern void	__fastcall__	FreezeFreq3_5MHzChg(void);
extern void	__fastcall__	FreezeFreq40MHzChg(void);

extern void	__fastcall__ 	FreezeVideoPALChg(void);
extern void __fastcall__ 	FreezeVideoNTSCChg(void);

extern void	__fastcall__ 	FreezeCartEnblChg(void);
extern void	__fastcall__ 	FreezeCartDsblChg(void);

extern void	__fastcall__ 	FreezeJoySEnblChg(void);
extern void	__fastcall__ 	FreezeJoySDsblChg(void);

extern void __fastcall__	FreezeDiskNum0Chg(void);
extern void __fastcall__	FreezeDiskImg0Chg(void);

extern void __fastcall__	FreezeDiskNum1Chg(void);
extern void __fastcall__	FreezeDiskImg1Chg(void);

extern void	__fastcall__ 	FreezeToolMonChg(void);
extern void	__fastcall__ 	FreezeToolAudChg(void);
extern void	__fastcall__ 	FreezeToolSprChg(void);

#endif