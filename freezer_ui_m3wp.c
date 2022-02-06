#include "m65_hal.h"
#include "m65_mem.h"

#include "frozen_memory.h"

#include "karljr.h"
#include "jude.h"
#include "jude_widgets.h"
#include "freezer_ui_gen.h"

#include "freezer_ui.h"



//==============================================================================




 // 		__asm__ ("SEI");
 // halt:
 // 		__asm__ ("INC $D020");
 // 		__asm__ ("JMP %g", halt);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	update_state_page(void){
//	karlFarPtr_t* self = (karlFarPtr_t *)(zptrself);
	karlFarPtr_t obj;
	byte	i, j;
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

//	Draw drive numbers
  	decimal_to_string(freeze_peek(0x10113L));
   	j = 0;
   	for (i = 0; i < 5; i++) {
   		if (string_buffer[i] != ' ') {
   			str_freeze_ctrl24[j] = string_buffer[i];
   			j++;
   		}
   	}
   	str_freeze_ctrl24[j] = 0x00;

  	decimal_to_string(freeze_peek(0x10114L));
   	j = 0;
   	for (i = 0; i < 5; i++) {
   		if (string_buffer[i] != ' ') {
   			str_freeze_ctrl29[j] = string_buffer[i];
   			j++;
   		}
   	}
   	str_freeze_ctrl24[j] = 0x00;


/*	Display info from the process descriptor
    The useful bits are:
    $00     - Task ID (0-255, $FF = operating system)
    $01-$10 - Process name (16 characters)
    $11     - D81 image 0 flags
    $12     - D81 image 1 flags
    $13     - D81 image 0 name len
    $14     - D81 image 1 name len
    $15-$34 - D81 image 0 file name (max 32 chars, not null terminated)
    $35-$54 - D81 image 0 file name (max 32 chars, not null terminated)
    $55-$7F - RESERVED
    $80-$FF - File descriptors

    We should just read the sector containing all this, and get it out all at once.
*/
	lfill((long)&process_descriptor, 0, sizeof(process_descriptor));
  	freeze_fetch_sector(0xFFFBD00L, (unsigned char*)&process_descriptor);

  	decimal_to_string(process_descriptor.task_id);
   	for (i = 0; i < 5; i++) {
   		str_freeze_ctrl1B[i] = string_buffer[i];
   	}

	str_freeze_ctrl19[0] = 0x00;
	str_freeze_ctrl22[0] = 0x00;
	str_freeze_ctrl27[0] = 0x00;

  	if ((process_descriptor.process_name[0] >= ' ') && 
  		(process_descriptor.process_name[0] <= 0x7f)) {
		for (i = 0; i < 16; i++)
      		if (!process_descriptor.process_name[i])
        		break;
    	
		if (i == 16)
      		lcopy((unsigned long)process_descriptor.process_name, 
      			(unsigned long)str_freeze_ctrl19, 16);

//		Show name of current mounted disk image
    	if (process_descriptor.d81_image0_namelen) {
      		for (i = 0; i < process_descriptor.d81_image0_namelen; i++)
        		if (!process_descriptor.d81_image0_name[i])
          			break;
      	if (i == process_descriptor.d81_image0_namelen)
        	lcopy((unsigned long)process_descriptor.d81_image0_name, 
        		(unsigned long)str_freeze_ctrl22,
        		process_descriptor.d81_image0_namelen < 32 ? process_descriptor.d81_image0_namelen : 32);
    	}

    	if (process_descriptor.d81_image1_namelen) {
      		for (i = 0; i < process_descriptor.d81_image1_namelen; i++)
        		if (!process_descriptor.d81_image1_name[i])
          			break;
      	if (i == process_descriptor.d81_image1_namelen)
        	lcopy((unsigned long)process_descriptor.d81_image1_name, 
        		(unsigned long)str_freeze_ctrl27,
            	process_descriptor.d81_image1_namelen < 32 ? process_descriptor.d81_image1_namelen : 32);
    	}
    }

 	while (PEEK(0xD012U) < 0xf8)
    	continue;
}


unsigned char menubar_colours[] = {
	0x0E, 0x0D, 0x07, 0x0A
};
const unsigned long menuoffs = 0x0FF80000;


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeMenuBarPrs(void) {
	unsigned char i, x;

	JudeDefPnlPresent();

	for (i = 0; i < 4; i++) {
		for (x = 0; x < 5; x++) {
			lpoke(menuoffs + (i * 8) + (x * 2) + 1, menubar_colours[i]);
			lpoke((menuoffs + 128) + (i * 8) + (x * 2) + 1, menubar_colours[3 - i]);
		}
	}

	JudeDrawTextDirect(CLR_PAPER, 0, 0x2C, 0x00, 0, 0, 0x13, str_freeze_bar0);
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeModPrepare(void) {
//	Reset border widths
  	POKE(0xD05CU, 80);
  	POKE(0xD05DU, 0xC0);

 //	Put $DD00 DDR back to default
  	POKE(0xDD02,0xFF);
  
 //	Enable extended attributes so we can use reverse
  	POKE(0xD031U, PEEK(0xD031U) | 0x20);

 // Correct horizontal scaling
 // POKE(0xD05AU, 0x78);
  
 //	Reset character set address
  	POKE(0xD068, 0x00);
  	POKE(0xD069, 0x10);
  	POKE(0xD06A, 0x00);

 //	Silence SIDs
  	POKE(0xD418U, 0);
  	POKE(0xD438U, 0);
  	POKE(0xD458U, 0);
  	POKE(0xD478U, 0);


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

  	set_palette();

 	request_freeze_region_list();
};


void __fastcall__ FreezePgeInit(void) {
	JudeDefPgeInit();

//	Reset border widths
//	POKE(0xD05CU, 80);
//	POKE(0xD05DU, 0xC0);

  	update_state_page();
}


const unsigned long thumboffs = 0x00010000 + 3 * 160 + 12;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__ FreezeThumbPresent(void) {
	unsigned char y;

	JudeDefPnlPresent();

// halt:
//     __asm__("INC $D020");
//     __asm__("JMP %g", halt);

	for (y = 0; y < 6; y++) {
		lcopy((unsigned long)(&thumbchars[y][0]), thumboffs + y * 160, 20);
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
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



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeSlotResumeChg(void) {
	word	flg	= (ctl_freeze_control1C._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		unfreeze_slot(slot_number);

		KarlPanic();
	};
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeSlotResetChg(void) {
	word	flg	= (ctl_freeze_control1D._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		freeze_reset();

		KarlPanic();
	};
};


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeSlotSaveChg(void) {
	word	flg	= (ctl_freeze_control1E._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		save_to_slot();
	};
};



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeModeAutoChg(void) {
	word	flg	= (rgp_freeze_control2._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
		freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) | 0x20);
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeMode4502Chg(void) {
	word	flg	= (rbt_freeze_control3._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) & (0xFF ^ 0x20));
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeFreq1MHzChg(void){
	word	flg	= (rgp_freeze_control5._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
		set_cpu_speed(1);
	}; 
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeFreq2MHzChg(void){
	word	flg	= (rbt_freeze_control2A._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(2);
	}; 
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeFreq3_5MHzChg(void){
	word	flg	= (rbt_freeze_control6._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(3);
	}; 
};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeFreq40MHzChg(void){
	word	flg	= (rbt_freeze_control7._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		set_cpu_speed(40);
	}; 
};


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeVideoPALChg(void) {
	word	flg	= (rgp_freeze_controlC._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
        freeze_poke(0xFFD306fL, 0x00);
        freeze_poke(0xFFD3072L, 0x00);
        freeze_poke(0xFFD3048L, 0x69);
        freeze_poke(0xFFD3049L, 0x0 + (lpeek(0xFFD3049L) & 0xF0));
        freeze_poke(0xFFD304AL, 0xFA);
        freeze_poke(0xFFD304BL, 0x1 + (lpeek(0xFFD304BL) & 0xF0));
        freeze_poke(0xFFD304EL, 0x69);
        freeze_poke(0xFFD304FL, 0x0 + (lpeek(0xFFD304FL) & 0xF0));
        freeze_poke(0xFFD3072L, 0);
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeVideoNTSCChg(void) {
	word	flg	= (rbt_freeze_controlD._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
        freeze_poke(0xFFD306fL, 0x87);
        freeze_poke(0xFFD3072L, 0x18);
        freeze_poke(0xFFD3048L, 0x2A);
        freeze_poke(0xFFD3049L, 0x0 + (lpeek(0xFFD3049L) & 0xf0));
        freeze_poke(0xFFD304AL, 0xB9);
        freeze_poke(0xFFD304BL, 0x1 + (lpeek(0xFFD304BL) & 0xf0));
        freeze_poke(0xFFD304EL, 0x2A);
        freeze_poke(0xFFD304FL, 0x0 + (lpeek(0xFFD304FL) & 0xf0));
        freeze_poke(0xFFD3072L, 24);
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeCartEnblChg(void) {
	word	flg	= (rgp_freeze_controlF._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
        freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) & (0xFF ^ 0x01));
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeCartDsblChg(void) {
	word	flg	= (rbt_freeze_control10._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) | 0x01);
	}
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeJoySEnblChg(void) {
	word	flg	= (rgp_freeze_control12._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
        freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) & (0xFF ^ 0x01));
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeJoySDsblChg(void) {
	word	flg	= (rbt_freeze_control13._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		freeze_poke(0xFFD367dL, freeze_peek(0xFFD367dL) | 0x01);
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDiskImg0Chg(void) {
	word	flg	= (ctl_freeze_control21._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		scan_directory(0);
	}
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeToolMonChg(void) {
	word	flg	= (btn_freeze_control2E._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		mega65_dos_exechelper("MONITOR.M65");
		KarlPanic();
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeToolAudChg(void) {
	word	flg	= (btn_freeze_control2F._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		mega65_dos_exechelper("AUDIOMIX.M65");
		KarlPanic();
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeToolSprChg(void) {
	word	flg	= (btn_freeze_control30._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
		mega65_dos_exechelper("SPRITED.M65");
		KarlPanic();
	}
}