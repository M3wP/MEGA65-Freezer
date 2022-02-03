#include "m65_hal.h"
#include "m65_mem.h"

#include "frozen_memory.h"

#include "karljr.h"
#include "jude.h"
#include "jude_widgets.h"
#include "freezer_ui_gen.h"

#include "freezer_ui.h"



 // 		__asm__ ("SEI");
 // halt:
 // 		__asm__ ("INC $D020");
 // 		__asm__ ("JMP %g", halt);




void	update_state_page(void){
//	karlFarPtr_t* self = (karlFarPtr_t *)(zptrself);
	karlFarPtr_t obj;
	byte	i;
	dword	data;

//	KarlClearZ();


	draw_thumbnail();

	// obj.loword = (word)(&pnl_freeze_panel4);
	// obj.hiword = 0x0000;

	// data = *((dword *)&obj);
	// zptrself = data;
	// KarlObjIncludeState(STATE_DIRTY);


	if (slot_number) {
    	decimal_to_string(slot_number);

    	for (i = 0; i < 5; i++) {
    		str_freeze_ctrl16b[16 + (i * 2)] = string_buffer[i];
    	}

		ctl_freeze_control16.text_p.loword = (word)(&str_freeze_ctrl16b);
		ctl_freeze_control16.text_p.hiword = 0x0000;

		ctl_freeze_control1C.text_p.loword = (word)(&str_freeze_ctrl1Cb);
		ctl_freeze_control1C.text_p.hiword = 0x0000;

  	} else {
		ctl_freeze_control16.text_p.loword = (word)(&str_freeze_ctrl16a);
		ctl_freeze_control16.text_p.hiword = 0x0000;

		ctl_freeze_control1C.text_p.loword = (word)(&str_freeze_ctrl1Ca);
		ctl_freeze_control1C.text_p.hiword = 0x0000;
  	}

	obj.loword = (word)(&ctl_freeze_control16);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	KarlObjIncludeState(STATE_DIRTY);

	obj.loword = (word)(&ctl_freeze_control1C);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	KarlObjIncludeState(STATE_DIRTY);


//	CPU Frequency
  	i = detect_cpu_speed();
  	if (i >= 4) 
  		i = 4;
  	i--;

	obj.loword = (word)(&rgp_freeze_control5);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);

//	CPU MODE
	i = (freeze_peek(0xffd367dL) & 0x20) ? 1 : 0;

	obj.loword = (word)(&rgp_freeze_control2);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);

//	Joystick 1/2 swap
	i = (PEEK(0xd612L) & 0x20) ? 0 : 1;

	obj.loword = (word)(&rgp_freeze_control12);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);
 
// ROM version
	ctl_freeze_controlA.text_p.loword = (word)(detect_rom());
	ctl_freeze_controlA.text_p.hiword = 0x0000;

	obj.loword = (word)(&ctl_freeze_controlA);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	KarlObjIncludeState(STATE_DIRTY);

//	Cartridge enable
	i = (freeze_peek(0xffd367dL) & 0x01) ? 0 : 1;

	obj.loword = (word)(&rgp_freeze_controlF);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);

//	Video mode
	i = (freeze_peek(0xffd306fL) & 0x80) ? 1 : 0;

	obj.loword = (word)(&rgp_freeze_controlC);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);


	// obj.loword = (word)(&pge_freeze_page0);
	// obj.hiword = 0x0000;

	// data = *((dword *)&obj);
	// zptrself = data;
	// KarlObjIncludeState(STATE_DIRTY);
}




void __fastcall__	FreezeModPrepare(void) {
	KarlDefModPrepare();

//	Now find the start sector of the slot, and make a copy for safe keeping
  	slot_number = 0;
  	find_freeze_slot_start_sector(slot_number);
  	freeze_slot_start_sector = *(uint32_t*)0xD681U;

//	SD or SDHC card?
  	if (PEEK(0xD680U) & 0x10)
    	sdhc_card = 1;
  	else
    	sdhc_card = 0;

	
//	Reset border widths
  	POKE(0xD05CU, 80);
  	POKE(0xD05DU, 0xC0);

  	set_palette();

 	request_freeze_region_list();

  	update_state_page();
};


void __fastcall__ FreezePgeInit(void) {
	JudeDefPgeInit();

// Reset border widths
  POKE(0xD05CU, 80);
  POKE(0xD05DU, 0xC0);

// request_freeze_region_list();

//  update_state_page();
}


const unsigned long offs = 0x00010000 + 3 * 160 + 12;

void __fastcall__ FreezeThumbPresent(void) {
	unsigned char y;

	JudeDefPnlPresent();

// halt:
//     __asm__("INC $D020");
//     __asm__("JMP %g", halt);

	for (y = 0; y < 6; y++) {
		lcopy((unsigned long)(&thumbchars[y][0]), offs + y * 160, 20);
	}
}


void __fastcall__ FreezeSlotDecChg(void){
//	karlFarPtr_t* self = (karlFarPtr_t *)(zptrself);
//	karlObject_t* obj = (karlObject_t *)(self->loword);
//	word	flg	= (obj->state & (word)STATE_DOWN);

	word	flg	= (ctl_freeze_control15._element._object.state & STATE_DOWN);

// 		__asm__ ("SEI");
// halt:
// 		__asm__ ("INC $D020");
// 		__asm__ ("JMP %g", halt);


	// POKE(0xD020U, 0x05);
	JudeDefCtlChange();

	// slot_number = flg;
	// update_state_page();

	if (flg)  {
		if (slot_number)
	    	slot_number--;
	    else
	    	slot_number = get_freeze_slot_count() - 1;
	    
	    find_freeze_slot_start_sector(slot_number);
	    freeze_slot_start_sector = *(uint32_t*)0xD681U;

	    update_state_page();
	};

};



void __fastcall__ FreezeSlotIncChg(void){
	// karlFarPtr_t* self = (karlFarPtr_t *)(zptrself);
	// karlObject_t* obj = (karlObject_t*)(self->loword);
	// byte	flg	= (obj->state && STATE_DOWN);

	word	flg	= (ctl_freeze_control17._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
        if ((slot_number + 1) < get_freeze_slot_count())
        	slot_number++;
        else
        	slot_number = 0;
  
        find_freeze_slot_start_sector(slot_number);
        freeze_slot_start_sector = *(uint32_t*)0xD681U;

	    update_state_page();
	};
};



void	__fastcall__	FreezeSlotResumeChg(void) {
	word	flg	= (ctl_freeze_control1C._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		unfreeze_slot(slot_number);

		KarlPanic();
	};
};

void	__fastcall__	FreezeSlotResetChg(void) {
	word	flg	= (ctl_freeze_control1D._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		freeze_reset();
	};
};


void	__fastcall__	FreezeFreq1MHzChg(void){
	word	flg	= (rgp_freeze_control5._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
		set_cpu_speed(1);
	}; 
};

void	__fastcall__	FreezeFreq2MHzChg(void){
	word	flg	= (rbt_freeze_control2A._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(2);
	}; 
};

void	__fastcall__	FreezeFreq3_5MHzChg(void){
	word	flg	= (rbt_freeze_control6._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(3);
	}; 
};

void	__fastcall__	FreezeFreq40MHzChg(void){
	word	flg	= (rbt_freeze_control7._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(40);
	}; 
};