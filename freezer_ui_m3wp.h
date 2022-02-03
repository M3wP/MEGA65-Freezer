#ifdef	INCLUDE_FREEZER_UI_M3WP_H
#else
#define	INCLUDE_FREEZER_UI_M3WP_H

//#include "karljr.h"
//#include "jude.h"
//#include "jude_widgets.h"

extern void __fastcall__ 	FreezeModPrepare(void);
extern void __fastcall__ 	FreezePgeInit(void);

extern void __fastcall__ 	FreezeThumbPresent(void);

extern void __fastcall__ 	FreezeSlotDecChg(void);
extern void __fastcall__ 	FreezeSlotIncChg(void);

extern void	__fastcall__	FreezeSlotResumeChg(void);
extern void	__fastcall__	FreezeSlotResetChg(void);

extern void	__fastcall__	FreezeFreq1MHzChg(void);
extern void	__fastcall__	FreezeFreq2MHzChg(void);
extern void	__fastcall__	FreezeFreq3_5MHzChg(void);
extern void	__fastcall__	FreezeFreq40MHzChg(void);


#endif