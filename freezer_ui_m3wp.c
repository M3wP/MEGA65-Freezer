#include "m65_hal.h"
#include "m65_mem.h"

#include "frozen_memory.h"

#include "karljr.h"
#include "jude.h"
#include "jude_widgets.h"
#include "freezer_ui_gen.h"

#include "freezer_ui.h"
#include "freezer_ui_m3wp.h"


//==============================================================================




 // 		__asm__ ("SEI");
 // halt:
 // 		__asm__ ("INC $D020");
 // 		__asm__ ("JMP %g", halt);


char pathstack[8][32];


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	update_dir_path(void) {
	karlDWFarPtr_t data;

	if (dir_depth < 8) {
		txt_freeze_control38.text_p.loword = (word)&pathstack[dir_depth];
		txt_freeze_control38.text_p.hiword = 0;

		data.ptr.loword = (word)&txt_freeze_control38;
		data.ptr.hiword = 0;
		zptrself = data.data;

		KarlObjIncludeState(STATE_DIRTY);
	}

	data.ptr.loword = (word)&btn_freeze_control3B;
	data.ptr.hiword = 0;
	zptrself = data.data;

	if  (dir_depth == 0) 
		KarlObjExcludeState(STATE_ENABLED);
	else
		KarlObjIncludeState(STATE_ENABLED);
	
	KarlObjIncludeState(STATE_DIRTY);
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	update_drive_num0(void) {
	byte	i, j;

  	decimal_to_string(freeze_peek(0x10113L));
   	j = 0;
   	for (i = 0; i < 5; i++) {
   		if (string_buffer[i] != ' ') {
   			str_freeze_ctrl24[j] = string_buffer[i];
   			j++;
   		}
   	}
   	str_freeze_ctrl24[j] = 0x00;

	cntrl_state_dirty(&ctl_freeze_control24);
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	update_drive_num1(void) {
	byte	i, j;

  	decimal_to_string(freeze_peek(0x10114L));
   	j = 0;
   	for (i = 0; i < 5; i++) {
   		if (string_buffer[i] != ' ') {
   			str_freeze_ctrl29[j] = string_buffer[i];
   			j++;
   		}
   	}
   	str_freeze_ctrl29[j] = 0x00;

	cntrl_state_dirty(&ctl_freeze_control29);
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	update_state_page(void){
//	karlFarPtr_t* self = (karlFarPtr_t *)(zptrself);
  	karlFarPtr_t obj;
  	dword data;
  	byte	i;

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

  	cntrl_state_dirty(&ctl_freeze_control16);
	cntrl_state_dirty(&ctl_freeze_control1C);

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
 
//  ROM version
//	ctl_freeze_controlA.text_p.loword = (word)(detect_rom());
//	ctl_freeze_controlA.text_p.hiword = 0x0000;
// 	cntrl_state_dirty(&ctl_freeze_controlA);

//	CRT Emulation
	i = (freeze_peek(0xFFD3054) & 0x10) ? 1 : 0;
	obj.loword = (word)(&rgp_freeze_controlA);
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	JudeRGroupReset(i);


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
  	update_drive_num0();
  	update_drive_num1();


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

	cntrl_state_dirty(&txt_freeze_control19);
	cntrl_state_dirty(&txt_freeze_control22);
	cntrl_state_dirty(&txt_freeze_control27);

 	while (PEEK(0xD012U) < 0xf8)
    	continue;
}


unsigned char menubar_colours[] = {
	0x0E, 0x0D, 0x07, 0x0A
};
const unsigned long menuoffs = 0x0FF80000;


const char str_lbx_prior[] = "[UP]";
const char str_lbx_next[]  = "[DOWN]";

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeLBxPresent(void) {
	karlDWFarPtr_t data;
	freezeListBox_t *self;
	unsigned char lines = 0;
	unsigned short colour = CLR_TEXT;
	unsigned short clrtmp;
	unsigned long lineptr;
	unsigned char y, x, w, f, f2, n, pgh, pgl, pgm, cl;

	data.data = zptrself;
	self = (freezeListBox_t*)(data.ptr.loword);

	KarlObjExcludeState(STATE_DIRTY);

	f = (self->_control._element._object.state & STATE_ENABLED);
	if 	(!f)
		colour = CLR_SHADOW;

	y = self->_control._element.posy;
	x = self->_control._element.posx;
	w = self->_control._element.width;

	cl = (self->currline == 0xFF) ? 0 : self->currline;

	data.ptr = self->lines_p;

	pgl = (self->linesoff > 0) ? 1 : 0;
	pgm = (((self->linescnt - self->linesoff) + pgl) > self->_control._element.height) ? 1 : 0;
	pgh = self->_control._element.height - (pgl + pgm);

	lines = pgh;

	if  (lines > self->linescnt)
		lines = self->linescnt; 
	
	if  ((lines + self->linesoff + pgl) > self->linescnt)
		lines = self->linescnt - self->linesoff;


		f2 = (self->_control._element._object.state & STATE_PICKED);

		self->_control._element._object.tag = 1;

		JudeEraseBkg(colour);

//		POKE(0xD020U, 0);

		if 	(lines) {
//			if  (f2)
//				POKE(0xD020U, 7);
//			else
//				POKE(0xD020U, 5);

			lineptr = data.data + (self->linewidth * self->linesoff);

			n = 0;
			if 	(self->linesoff) {
				data.ptr.loword = (word)(str_lbx_prior);
				data.ptr.hiword = 0;

				if  (cl == n)
					clrtmp = (f) ? 
							(self->_control._element._object.state & STATE_ACTIVE) ? CLR_PAPER  : 
							CLR_SHADOW : colour;
				else
					clrtmp = colour;

				if  ((self->hotline == n) && f && f2)
					clrtmp = CLR_FOCUS;

				JudeEraseLine(w, x, y, clrtmp);
				JudeDrawTextDirect(clrtmp, 0, w, 0x00, x, y, (w - 4) / 2, data.data);
				y++;
				n++;
			}

			while (lines) {
				if  (self->selline == (n + self->linesoff - pgl))
					clrtmp = (f) ? CLR_FOCUS : CLR_PAPER;
				else if  (cl == n)
					clrtmp = (f) ? 
							(self->_control._element._object.state & STATE_ACTIVE) ? CLR_PAPER  : 
							CLR_SHADOW : colour;
				else
					clrtmp = colour;

				if  ((self->hotline == n) && f && f2)
					clrtmp = (clrtmp == CLR_FOCUS) ? CLR_PAPER : CLR_FOCUS;

				JudeEraseLine(w, x, y, clrtmp);
				JudeDrawTextDirect(clrtmp, 0, w, 0x00, x, y, 0, lineptr);
				y++;
				n++;
				
				lineptr+= self->linewidth /*64*/;	
				lines--;
			}

			if 	((self->linescnt - self->linesoff) > pgh) {
				if  (cl == n)
					clrtmp = (f) ? 
							(self->_control._element._object.state & STATE_ACTIVE) ? CLR_PAPER  : 
							CLR_SHADOW : colour;
				else
					clrtmp = colour;

				if  ((self->hotline == n) && f && f2)
					clrtmp = CLR_FOCUS;

				data.ptr.loword = (word)(str_lbx_next);
				data.ptr.hiword = 0;

				JudeEraseLine(w, x, y, clrtmp);
				JudeDrawTextDirect(clrtmp, 0, w, 0x00, x, y, (w - 6) / 2, data.data);
				y++;
				n++;
				lines--;
			}
		}
	//}
}


extern void __fastcall__	FreezeLBxChange(void) {
	karlDWFarPtr_t data;
	freezeListBox_t *self;
	unsigned char dwn, flg = 0;
	unsigned char h;
	void (*sel)(void);

	data.data = zptrself;
	self = (freezeListBox_t*)(data.ptr.loword);

	flg = (self->_control._element._object.state &
			(STATE_ENABLED | STATE_VISIBLE));

	dwn = (flg && (self->_control._element._object.state & STATE_DOWN));

	if  (flg
	&&   (mouseXCol >= self->_control._element.posx)
	&&   (mouseXCol < (self->_control._element.posx + self->_control._element.width)) 
	&&	 (mouseYRow >= self->_control._element.posy)
	&&   (mouseYRow < (self->_control._element.posy + self->_control._element.height))) {
//		flg = 1;
		if  (self->_control._element._object.state & STATE_PICKED) {
			self->hotline = mouseYRow - self->_control._element.posy;
			if  (self->hotline >= self->linescnt) 
				self->hotline = self->linescnt - 1;
			if  (self->hotline > (self->linescnt - self->linesoff))
				self->hotline = self->linescnt - self->linesoff;

			self->_control._element._object.tag = 0;

			KarlObjIncludeState(STATE_DIRTY);
		}

		if  (self->_control._element._object.state & STATE_DOWN) {
			h = (self->_control._element.height - 2);

			if  ((self->linesoff > 0) && (self->hotline == 0)) {
				if  ((self->linesoff - h) < 0)
					self->linesoff = 0;
				else 
					self->linesoff-= h;
				flg = 0;
			} else if ((self->hotline == (self->_control._element.height - 1))
			&& ((self->linescnt - self->linesoff) > h)) {
				if ((self->linesoff + h) > self->linescnt)
					self->linesoff = self->linescnt - h;
				else
					self->linesoff+= h;

				flg = 0;
			}
		}

		if (!flg) {
			self->hotline = 0x00;
			self->currline = 0x00;
		} else if (dwn) {
			self->currline = self->hotline;
		}
	};
	
	JudeDefCtlChange();

	if (dwn && flg && (self->currline != 0xFF)) {
		self->selline = self->linesoff + self->currline - ((self->linesoff > 0) ? 1 : 0);
		sel = (void(*)(void))self->select;
		if (sel)
			sel();
	}

}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ FreezeLBxPressed(void) {
//***FIXME.  I need to address these "correctly"
	char key = _zkarljr[0x64];
	unsigned char mod = _zkarljr[0x65];
	unsigned char flg = 0;
	unsigned char h, l;
	void (*sel)(void);

	karlDWFarPtr_t data;
	freezeListBox_t *self;

	data.data = zptrself;
	self = (freezeListBox_t*)(data.ptr.loword);

//	flg = (self->_control._element._object.state &
//			(STATE_ACTIVE| STATE_ENABLED | STATE_VISIBLE));

	flg = 0;

	if  (self->_control._element._object.state & (STATE_ACTIVE)) {
		l = (self->linescnt - self->linesoff) - ((self->linesoff > 0) ? 0 : 1);
		if  (l > (self->_control._element.height - 1))
			l = (self->_control._element.height - 1);

		switch (key) {
			case KEY_C64_CDOWN:
			case KEY_C64_CRIGHT:
			case KEY_M65_TAB:
				if  ((key == KEY_M65_TAB)
				||	 ((mod & KEY_MOD_SHIFT) && (self->currline == 0)) 
				||   ((!(mod & KEY_MOD_SHIFT)) && (self->currline == l))) {
					_JudeMoveActiveControl();
				}
				else {
					if (!(mod & KEY_MOD_SHIFT)) 
						self->currline++;
					else
						self->currline--;

					self->hotline = self->currline;

					self->_control._element._object.tag = 0;

					KarlObjIncludeState(STATE_DIRTY);
//					JudeUnDownCtrl();
				}
				break;
			case KEY_ASC_CR:
				h = (self->_control._element.height - 2);

				if  ((self->linesoff > 0) && (self->currline == 0)) {
					if  ((self->linesoff - h) < 0)
						self->linesoff = 0;
					else 
						self->linesoff-= h;
					flg = 1;
				} else if ((self->currline == (self->_control._element.height - 1))
				&& ((self->linescnt - self->linesoff) > h)) {
					if ((self->linesoff + h) > self->linescnt)
						self->linesoff = self->linescnt - h;
					else
						self->linesoff+= h;

					flg = 1;
				}

				self->hotline = self->currline;

				self->_control._element._object.tag = 0;
				KarlObjIncludeState(STATE_DIRTY);

				if (flg) {
					self->currline = 0x00;
				} else {
					self->selline = self->linesoff + self->currline - ((self->linesoff > 0) ? 1 : 0);

					sel = (void(*)(void))self->select;
					if (sel)
 						sel();
				
					JudeUnDownCtrl();
				}

				break;	
		}
	
		karl_errorno = ERROR_ABORT;
	} else
		JudeDefCtlKeypress();
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void 	__fastcall__	FreezeImgLstSelect(void) {
	unsigned long faddr;
	karlDWFarPtr_t data;
//	karlFarPtr_t obj;
//	unsigned char i;
	unsigned char l;

	data.ptr = lbx_freeze_control3A.lines_p;

	l = (lbx_freeze_control3A.linesoff > 0) ? lbx_freeze_control3A.currline - 1 : 
			lbx_freeze_control3A.currline;

	faddr = data.data + 
			(l + lbx_freeze_control3A.linesoff) * lbx_freeze_control3A.linewidth;


	lcopy(faddr, (unsigned long)disk_name_return, 32);
//  Then null terminate it
    for (l = 31; l; l--)
	    if  (disk_name_return[l] == ' ')
            disk_name_return[l] = 0;
	    else
	        break;

//***FIXME Remove this debugging
	data.ptr.loword = (unsigned short)disk_name_return;
	data.ptr.hiword = 0;
	JudeDrawTextDirect(CLR_PAPER, 0, 32, 0, 0, 0, 0, data.data);
//---

	disk_filecnt = 0;
	lbx_freeze_control3C.linesoff = 0x00;
	lbx_freeze_control3C.currline = 0x00;
	lbx_freeze_control3C.hotline = 0x00;
	lbx_freeze_control3C.selline = 0xFF;

	if (disk_name_return[0] == '/') {
//		Its a directory
        if (!mega65_dos_chdir(&disk_name_return[1])) {
        	if  (disk_name_return[2] == '.') 
				dir_depth--;
			else {
				dir_depth++;

				if (dir_depth < 8) {
					pathstack[dir_depth][0] = '.';

					for (l = 1; l < 31; l++)
						pathstack[dir_depth][l] = disk_name_return[l - 1];

					pathstack[dir_depth][31] = 0;
				}
			}

			update_dir_path();

	        scan_directory(drive_id);

			lbx_freeze_control3A.linescnt = file_count;
			lbx_freeze_control3C.linescnt = 0;

			lbx_freeze_control3A.linesoff = 0x00;
			lbx_freeze_control3A.currline = 0x00;
			lbx_freeze_control3A.hotline = 0x00;
			lbx_freeze_control3A.selline = 0xFF;

			lbx_freeze_control3A._control._element._object.state|= STATE_ENABLED; 
			lbx_freeze_control3A._control._element._object.tag = 0;

			lbx_freeze_control3C._control._element._object.state = STATE_VISIBLE; 
			lbx_freeze_control3C._control._element._object.tag = 0;

			data.ptr.loword = (word)&lbx_freeze_control3A;
			data.ptr.hiword = 0x0000;
			zptrself = data.data;
			KarlObjIncludeState(STATE_DIRTY); 
   		}
    } else {
		draw_directory_contents();

		lbx_freeze_control3C.linescnt = disk_filecnt;

		lbx_freeze_control3C._control._element._object.state|= STATE_ENABLED; 
		lbx_freeze_control3C._control._element._object.tag = 0;
	}

	data.ptr.loword = (word)&lbx_freeze_control3C;
	data.ptr.hiword = 0x0000;
	zptrself = data.data;
	KarlObjIncludeState(STATE_DIRTY); 
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezePage0Keypress(void) {
	_zkarljr[0x65] = KEY_MOD_SYS;


	_JudeProcessAccelerators();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__	FreezeMenuBarPrs(void) {
	unsigned char i, x;
	karlDWFarPtr_t data;
	unsigned short clr;

	JudeDefPnlPresent();



	for (i = 0; i < 4; i++) {
		clr = CLR_INFORM + i;
		x = JudeLogClrToSys(clr);
		menubar_colours[i] = x;

		for (x = 0; x < 4; x++) {
			lpoke(menuoffs + (i * 8) + (x * 2) + 1, menubar_colours[i]);
			lpoke((menuoffs + 128) + (i * 8) + (x * 2) + 1, menubar_colours[3 - i]);
		}
	}

	data.ptr.loword = (word)(str_freeze_bar0);
	data.ptr.hiword = 0;

	JudeDrawTextDirect(CLR_PAPER, 0, 0x2C, 0x00, 0, 0, 0x13, data.data);
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


const unsigned long thumboffs = 0x00012000 + 4 * 160 + 24;

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
void	__fastcall__ 	FreezeCRTEnblChg(void) {
	word	flg	= (rgp_freeze_controlA._control._element._object.state & STATE_DOWN);

	JudeDefRGpChange();

	if (flg) {
        freeze_poke(0xFFD3054L, freeze_peek(0xFFD3054L) & (0xFF ^ 0x10));
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	__fastcall__ 	FreezeCRTDsblChg(void) {
	word	flg	= (rbt_freeze_control40._control._element._object.state & STATE_DOWN);

	JudeDefRBtChange();

	if (flg) {
        freeze_poke(0xFFD3054L, freeze_peek(0xFFD3054L) | 0x10);
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
void __fastcall__	FreezeDiskNum0Chg(void) {
	word	flg	= (ctl_freeze_control24._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		freeze_poke(0x10113L, freeze_peek(0x10113L) ^ 2);
		update_drive_num0();
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	init_disk_select(byte id) {
	karlDWFarPtr_t data;

	data.ptr.loword = (word)(&rgp_freeze_control34);
	data.ptr.hiword = 0x0000;
	zptrself = data.data;
	JudeRGroupReset(0);

	pathstack[0][0] = '/';
	pathstack[0][1] = 0;

	mega65_dos_chdirroot();
	dir_depth = 0;

	update_dir_path();

	scan_directory(id);

	lbx_freeze_control3A.linescnt = file_count;
	lbx_freeze_control3C.linescnt = 0;

	lbx_freeze_control3A.linesoff = 0x00;
	lbx_freeze_control3A.currline = 0x00;
	lbx_freeze_control3A.hotline = 0x00;
	lbx_freeze_control3A.selline = 0xFF;

	lbx_freeze_control3C.linesoff = 0x00;
	lbx_freeze_control3C.currline = 0x00;
	lbx_freeze_control3C.hotline = 0x00;
	lbx_freeze_control3C.selline = 0xFF;

	lbx_freeze_control3A._control._element._object.state = STATE_VISIBLE; 
	lbx_freeze_control3A._control._element._object.tag = 0;

	lbx_freeze_control3C._control._element._object.state = STATE_VISIBLE; 
	lbx_freeze_control3C._control._element._object.tag = 0;

 	data.ptr.loword = (word)&pge_freeze_page2;
	data.ptr.hiword = 0x0000;
	zptrself = data.data;
	JudeActivatePage(); 
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDiskImg0Chg(void) {
	word	flg	= (ctl_freeze_control21._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		init_disk_select(0);
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDiskNum1Chg(void) {
	word	flg	= (ctl_freeze_control29._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		freeze_poke(0x10114L, freeze_peek(0x10114L) ^ 2);
		update_drive_num1();
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDiskImg1Chg(void) {
	word	flg	= (ctl_freeze_control26._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		init_disk_select(1);
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDrvTypeImgChg(void) {
	karlDWFarPtr_t data;
	byte	flg = rbt_freeze_control36._control._element._object.state & STATE_DOWN;

	JudeDefRBtChange();

	data.ptr.loword = (word)&lbx_freeze_control3A;
	data.ptr.hiword = 0;
	zptrself = data.data;

	if  (flg) {
		if (rbt_freeze_control36._control._element._object.tag) {
			KarlObjIncludeState(STATE_ENABLED);

			update_dir_path();

			data.ptr.loword = (word)&lbx_freeze_control3C;
			data.ptr.hiword = 0;
			zptrself = data.data;

			if  (lbx_freeze_control3A.selline != 0xFF)
				KarlObjIncludeState(STATE_ENABLED);
		} else {
			KarlObjExcludeState(STATE_ENABLED);

			data.ptr.loword = (word)&lbx_freeze_control3C;
			data.ptr.hiword = 0;
			zptrself = data.data;

			KarlObjExcludeState(STATE_ENABLED);

			data.ptr.loword = (word)&btn_freeze_control3B;
			data.ptr.hiword = 0;
			zptrself = data.data;

			KarlObjExcludeState(STATE_ENABLED);
		}
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDirUpChange(void) {
	karlDWFarPtr_t data;
	word	flg	= (btn_freeze_control3B._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
		mega65_dos_chdir("..");

		dir_depth--;
		disk_filecnt = 0;

		lbx_freeze_control3C.linesoff = 0x00;
		lbx_freeze_control3C.currline = 0x00;
		lbx_freeze_control3C.hotline = 0x00;
		lbx_freeze_control3C.selline = 0xFF;


//***FIXME This code is the same as above FreezeImgLstSelect
		update_dir_path();

        scan_directory(drive_id);

		lbx_freeze_control3A.linescnt = file_count;
		lbx_freeze_control3C.linescnt = 0;

		lbx_freeze_control3A.linesoff = 0x00;
		lbx_freeze_control3A.currline = 0x00;
		lbx_freeze_control3A.hotline = 0x00;
		lbx_freeze_control3A.selline = 0xFF;

		lbx_freeze_control3A._control._element._object.state|= STATE_ENABLED; 
		lbx_freeze_control3A._control._element._object.tag = 0;

		lbx_freeze_control3C._control._element._object.state = STATE_VISIBLE; 
		lbx_freeze_control3C._control._element._object.tag = 0;

		data.ptr.loword = (word)&lbx_freeze_control3A;
		data.ptr.hiword = 0x0000;
		zptrself = data.data;
		KarlObjIncludeState(STATE_DIRTY); 

		data.ptr.loword = (word)&lbx_freeze_control3C;
		data.ptr.hiword = 0x0000;
		zptrself = data.data;
		KarlObjIncludeState(STATE_DIRTY); 
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDrvAcceptChg(void) {
	karlDWFarPtr_t data;
	byte flg = (btn_freeze_control3E._element._object.state & STATE_DOWN);
	byte x, i, ok;

	ok = 1;

	JudeDefCtlChange();

	if  (flg) {
		if  ((rbt_freeze_control36._control._element._object.tag)
		&&   (lbx_freeze_control3A.selline == 0xFF))
			flash_control((word)&lbx_freeze_control3A, CLR_ABORT);
		else {
//			First, clear flags for the F011 image
    		if  (drive_id == 0) {
//				Clear flags for drive 0
        		lpoke(0xffd368bL, lpeek(0xffd368bL) & 0xb8);

//				there seem to be an issue reliably using lpoke/lpeek here
//				so for now we repeat to ensure we have what we want
        		while (lpeek(0xffd36a1L) & 1) {
         			lpoke(0xffd36a1L, lpeek(0xffd36a1L) & 0xfe);
        		}
    		}
    		else if (drive_id == 1) {
//				Clear flags for drive 1
        		lpoke(0xffd368bL, lpeek(0xffd368bL) & 0x47);
        		while (lpeek(0xffd36a1L) & 4) {
        			lpoke(0xffd36a1L, lpeek(0xffd36a1L) & 0xfb);
        		}
    		}

			if (rgp_freeze_control34._control._element._object.tag) {
				if (drive_id == 0)
              		lpoke(0xffd368bL, (lpeek(0xffd368bL) & 0xb8) + 0x01);
            	if (drive_id == 1)
              		lpoke(0xffd368bL, (lpeek(0xffd368bL) & 0x47) + 0x08);
          	} else if (rbt_freeze_control35._control._element._object.tag) {
				if (drive_id == 0)
//					Use internal drive (drive 0 only)
	            	while (!(lpeek(0xffd36a1L) & 1)) {
              			lpoke(0xffd36a1L, lpeek(0xffd36a1L) | 0x01);
              		}

            	if (drive_id == 1)
//					Use 1565 external drive (drive 1 only)
            		while (!(lpeek(0xffd36a1L) & 4)) {
              			lpoke(0xffd36a1L, lpeek(0xffd36a1L) | 0x04);
              		}
            } else {
          		if  (drive_id == 0)
            		lpoke(0xffd368bL, (lpeek(0xffd368bL) & 0xb8) + 0x07);
          		if (drive_id == 1)
            		lpoke(0xffd368bL, (lpeek(0xffd368bL) & 0x47) + 0x38);
          		if (mega65_dos_attachd81(disk_name_return)) {
//					Mounting the image failed
          			ok = 0;
        			POKE(0xD080U, 0x40);

//					Mark drive as having nothing in it
            		if (drive_id == 0) {
//						Clear flags for drive 0
              			lpoke(0xffd368bL, lpeek(0xffd368bL) & 0xb8);
              			lpoke(0xffd36a1L, lpeek(0xffd36a1L) & 0xfe);
            		}
            		else if (drive_id == 1) {
//						Clear flags for drive 1
              			lpoke(0xffd368bL, lpeek(0xffd368bL) & 0x47);
              			lpoke(0xffd36a1L, lpeek(0xffd36a1L) & 0xfb);
            		}            	
            	} else {
//					Mount succeeded, now seek to track 0 to make sure DOS
//					knows where we are, and to make sure the drive head is
//					sitting properly.
        			while (!(PEEK(0xD082) & 0x01)) {
          				POKE(0xD081, 0x10);
          				usleep(7000);
        			}
//					Now check the contents of $D084 to find out the most recently
//					requested track, and seek the head to that track.
					x = freeze_peek(0xFFD3084); // Get last requested track by frozen programme
					while(x) {
	  					POKE(0xD081, 0x18);
	  					while(PEEK(0xD082)&0x80) 
	  						POKE(0xD020,PEEK(0xD020)+1);
	  					x--;
					}            		
          			
          			request_freeze_region_list();

//					Replace disk image name in process descriptor block
           			for (i = 0; (i < 32) && disk_name_return[i]; i++)
                		freeze_poke(0xFFFBD00L + 0x15 + i, disk_name_return[i]);
//					Update length of name
              		freeze_poke(0xFFFBD00L + 0x13, i);

//					Pad with spaces as required by hypervisor
              		for (; i < 32; i++)
                		freeze_poke(0xFFFBD00L + 0x15 + i, ' ');
            	}
			}

			if (ok) {
				POKE(0xD080U, 0);
				update_state_page();
		 		
		 		data.ptr.loword = (word)&pge_freeze_page0;
	  			data.ptr.hiword = 0x0000;
	  			zptrself = data.data;
	 			JudeActivatePage();
	 		} else
	 			flash_border(CLR_ABORT);
		}
	}
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeDrvCancelChg(void) {
	karlDWFarPtr_t data;
	byte flg = btn_freeze_control3F._element._object.state & STATE_DOWN;

	JudeDefCtlChange();

	if  (flg) {
	 	data.ptr.loword = (word)&pge_freeze_page0;
  		data.ptr.hiword = 0x0000;
  		zptrself = data.data;
 		JudeActivatePage(); 				
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


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void __fastcall__	FreezeMkDskChange(void) {
	word	flg	= (btn_freeze_control48._element._object.state & STATE_DOWN);

	JudeDefCtlChange();

	if (flg) {
//		Save the current freeze slot number, so that the image can get mounted against us
	    POKE(0x03C0, slot_number & 0xff);
	    POKE(0x03C1, slot_number >> 8);

//		Tell MAKEDISK if we want a D81 or a D65 image
	    if (rgp_freeze_control46._control._element._object.tag)
	    	POKE(0x33c,0); // 0=DD
	    else
	      	POKE(0x33c,1); // 1=HD

	    mega65_dos_exechelper("MAKEDISK.M65");

	    KarlPanic();
	}
}