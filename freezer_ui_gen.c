#include	<string.h>

#include "m65_mem.h"
#include "m65_hal.h"
#include "frozen_memory.h"
#include "ascii.h"

#include "karljr.h"
#include "jude.h"


#define     FDDDIRADDR  0x00016000U

unsigned short file_count = 0;
unsigned short dir_depth = 0;
unsigned short drive_id = 0;
char disk_name_return[32] = "";
unsigned char disk_filecnt = 0;

unsigned char thumbchars[6][20];

// clang-format off
unsigned char c64_palette[64]={
    0x00, 0x00, 0x00, 0x00,
	0xff, 0xff, 0xff, 0x00,
	0xba, 0x13, 0x62, 0x00,
	0x66, 0xad, 0xff, 0x00,
	0xbb, 0xf3, 0x8b, 0x00,
	0x55, 0xec, 0x85, 0x00,
	0xd1, 0xe0, 0x79, 0x00,
	0xae, 0x5f, 0xc7, 0x00,
	0x9b, 0x47, 0x81, 0x00,
	0x87, 0x37, 0x00, 0x00,
	0xdd, 0x39, 0x78, 0x00,
	0xb5, 0xb5, 0xb5, 0x00,
	0xb8, 0xb8, 0xb8, 0x00,
	0x0b, 0x4f, 0xca, 0x00,
	0xaa, 0xd9, 0xfe, 0x00,
	0x8b, 0x8b, 0x8b, 0x00
};
// clang-format on

unsigned char colour_table[256];


void    flash_control(word ctrl, word clr) {
    karlDWFarPtr_t data;
    byte i;

    data.ptr.loword = ctrl;
    data.ptr.hiword = 0;
    zptrself = data.data;

    for (i = 0; i < 3; i++) {
        JudeEraseBkg(clr);
        usleep(250000);

        JudeEraseBkg(CLR_TEXT);
        usleep(250000);
    }

    KarlObjIncludeState(STATE_DIRTY);
}

void    flash_border(word clr) {
    byte c = JudeLogClrToSys(clr);
    byte i;
    byte p = PEEK(0xD020U);

    for (i = 0; i < 3; i ++) {
        POKE(0xD020U, c);
        usleep(250000);

        POKE(0xD020U, p);
        usleep(250000);
    }
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void	cntrl_state_dirty(void* ctrl) {
	karlFarPtr_t obj;
	dword data;

	obj.loword = (word)ctrl;
	obj.hiword = 0x0000;

	data = *((dword *)&obj);
	zptrself = data;
	KarlObjIncludeState(STATE_DIRTY); 
}


void save_to_slot(void) {
	uint32_t i;
	uint32_t j;
	uint32_t dest_freeze_slot_start_sector;
	find_freeze_slot_start_sector(0);
	freeze_slot_start_sector = *(uint32_t*)0xD681U;
	find_freeze_slot_start_sector(slot_number);
	dest_freeze_slot_start_sector = *(uint32_t*)0xD681U;

	JudeSetPointer(MPTR_WAIT);

//	512KB = 1024 sectors
//	Process in 64KB blocks, so that we can do multi-sector writes
//	and generally be about 10x faster than otherwise.
	for (i = 0; i < 1024; i += 128) {
//		POKE(0xD020U, 0x0e);
		for (j = 0; j < 128; j++) {
			sdcard_readsector(freeze_slot_start_sector + i + j);
			lcopy((unsigned long)sector_buffer, 0x40000U + (j << 9), 512);
		}
//		POKE(0xD020U, 0x00);
		for (j = 0; j < 128; j++) {
			lcopy(0x40000U + (j << 9), (unsigned long)sector_buffer, 512);
#ifdef USE_MULTIBLOCK_WRITE
			if (!j)
					sdcard_writesector(dest_freeze_slot_start_sector + i + j, 1);
	       	else
					sdcard_writenextsector();
#else
			sdcard_writesector(dest_freeze_slot_start_sector + i + j, 0);
#endif
		}
#ifdef USE_MULTIBLOCK_WRITE
//      Close multi-sector write job
		sdcard_writemultidone();
#endif
	}

	JudeSetPointer(MPTR_NORMAL);
}

void scan_directory(unsigned char id)
{
	unsigned char x, dir;
	struct m65_dirent* dirent;


	JudeSetPointer(MPTR_WAIT);

	closeall();

	file_count = 0;
	drive_id = id;

	dir = opendir();
	dirent = readdir(dir);
	while (dirent && ((unsigned short)dirent != 0xffffU)) {
		x = strlen(dirent->d_name);

//	check DIR attribute of dirent
	if (dirent->d_type & 0x10) {

//	File is a directory
	if (x < 60) {
		lfill(0x40000L + (file_count * 64), ' ', 64);
		lcopy((long)&dirent->d_name[0], 0x40000L + 1 + (file_count * 64), x);
//		Put / at the start of directory names to make them obviously different
		lpoke(0x40000L + (file_count * 64), '/');
//		Don't list "." directory pointer
		if (strcmp(".", dirent->d_name))
			file_count++;
		}
	} else if (x > 4) {
        if  ((!strncmp(&dirent->d_name[x - 4], ".D81", 4))
        ||   (!strncmp(&dirent->d_name[x - 4], ".d81", 4))
		||   (!strncmp(&dirent->d_name[x - 4], ".D65", 4))
        ||   (!strncmp(&dirent->d_name[x - 4], ".d65", 4))) {
//		File is a disk image
			lfill(0x40000L + (file_count * 64), ' ', 64);
			lcopy((long)&dirent->d_name[0], 0x40000L + (file_count * 64), x);
			file_count++;
			}
		}

		dirent = readdir(dir);
	}

	closedir(dir);

	JudeSetPointer(MPTR_NORMAL);
}


void set_palette(void)
{
	unsigned char c, x, y;

	// First set the 16 C64 colours
	// unsigned char c;
	POKE(0xD070U, 0xFF);
	// for (c = 0; c < 16; c++) {
	//	 POKE(0xD100U + c, c64_palette[c * 4 + 0]);
	//	 POKE(0xD200U + c, c64_palette[c * 4 + 1]);
	//	 POKE(0xD300U + c, c64_palette[c * 4 + 2]);
	// }

	// Then prepare a colour cube in the rest of the palette
	for (c = 0x10; c; c++) {
		// 3 bits for red
		POKE(0xD100U + c, (c >> 4) & 0xe);
		// 3 bits for green
		POKE(0xD200U + c, (c >> 1) & 0xe);
		// 2 bits for blue
		POKE(0xD300U + c, (c << 2) & 0xf);
	}

	// Make colour lookup table
	c = 0;
	do {
		colour_table[c] = c;
	} while (++c);

	// Now map C64 colours directly
	colour_table[0x00] = 0x20; // black	 ($00 = transparent colour, so we have to use very-dim red instead)
	colour_table[0xff] = 0x01; // white
	colour_table[0xe0] = 0x02; // red
	colour_table[0x1f] = 0x03; // cyan
	colour_table[0xe3] = 0x04; // purple
	colour_table[0x1c] = 0x05; // green
	colour_table[0x03] = 0x06; // blue
	colour_table[0xfc] = 0x07; // yellow
	colour_table[0xec] = 0x08; // orange
	colour_table[0xa8] = 0x09; // brown
	colour_table[0xad] = 0x0a; // pink
	colour_table[0x49] = 0x0b; // grey1
	colour_table[0x92] = 0x0c; // grey2
	colour_table[0x9e] = 0x0d; // lt.green
	colour_table[0x93] = 0x0e; // lt.blue
	colour_table[0xb6] = 0x0f; // grey3

// We should also map colour cube colours 0x00 -- 0x0f to
// somewhere sensible.
// 0x00 = black, so can stay
#if 0
	colour_table[0x01] = 0x06;	// dim blue -> blue
	// colour_table[0x02] = 0x06;	// medium dim blue -> blue
	// colour_table[0x03] = 0x06;	// bright blue -> blue
	colour_table[0x04] = 0x00;	// dim green + no blue
	colour_table[0x05] = 0x25;	
	colour_table[0x06] = 0x26;	
	colour_table[0x07] = 0x27;	
	colour_table[0x08] = 0x28;	
	colour_table[0x09] = 0x29;	
	colour_table[0x0A] = 0x2a;	
	colour_table[0x0B] = 0x2b;	
	colour_table[0x0C] = 0x2c;	
	colour_table[0x0D] = 0x2d;	
	colour_table[0x0E] = 0x2e;	
	colour_table[0x0F] = 0x2f;
#endif

	c = 0;

	for (x = 0; x < 11; x++) {
		for (y = 0; y < 6; y ++) {
			thumbchars[y][x * 2] = c;
			thumbchars[y][x * 2 + 1] = 0x14;
			c++;
		}
	}
};


char draw_directory_entry(unsigned char idx) {
    char type;
    char firsta0 = 1;
    char invalid = 0;
    unsigned char i, c;

//  Skip first 5 bytes
    for (i = 0; i < 2; i++)
        c = PEEK(0xD087U);
    
    type = PEEK(0xD087U);
    if (!(type & 0xf))
        invalid = 1;

    for (i = 0; i < 2; i++)
        c = PEEK(0xD087U);

//  Then draw the 16 chars with quotes
    lpoke(FDDDIRADDR + (idx * 20), '"');

    for (i = 0; i < 16; i++) {
        c = PEEK(0xD087U);

        if  (!c)
            invalid = 1;

        if  (firsta0 && (c == 0xa0)) {
            lpoke(FDDDIRADDR + (idx * 20) + 1 + i, 0x22);
            firsta0 = 0;
        } else {
//          if (c >= 'A' && c <= 'Z')
//              c &= 0x1f;
//          if (c >= 'a' && c <= 'z')
//              c &= 0x1f;
            
            lpoke(FDDDIRADDR + (idx * 20) + 1 + i, c & 0x7F);
        }
    }
    
    if  (firsta0) {
        lpoke(FDDDIRADDR + (idx * 20) + 16, '"');
    }

    if  (type & 0x40)
        lpoke(FDDDIRADDR + (idx * 20) + 18, '<');
    
    if  (!type & 0xf0)
        lpoke(FDDDIRADDR + (idx * 20) + 19, '*');

//  Read the rest of the entry to advance buffer pointer nicely
    for (i = 0; i < 11; i++)
        c = PEEK(0xD087U);

//  if (invalid) {
//      Erase whatever we drew
//      for (i = 21; i < 40; i++)
//          POKE(SCREEN_ADDRESS + (screen_row * 80) + (i * 2), ' ');
//  }
//  else {
//      lcopy((unsigned long)dir_line_colour, COLOUR_RAM_ADDRESS + (screen_row * 80) + (21 * 2), 19 * 2);
//  }

    return invalid;
}


void draw_directory_contents(void) {
	unsigned char x, c, i, n = 0;
//    unsigned long cnt;

//  lcopy(0x40000L + (selection_number * 64), (unsigned long)disk_name_return, 32);

//  Don't draw directories (although it would be nice to show their contents)

    if  (disk_name_return[0] == '/')
        return;

    JudeSetPointer(MPTR_WAIT);


//  Try to mount it, with border black while working
//  POKE(0xD020U, 15);

    POKE(0xD080, 0);

    sdcard_reset();

    if  (mega65_dos_attachd81(disk_name_return)) {
//      Mounting the image failed
        POKE(0xD080U, 0x40);
//	    POKE(0xD020U, 2);

//      XXX - Get DOS error code, and replace directory listing area with
//      appropriate error message
        JudeSetPointer(MPTR_NORMAL);
	    return;
	}

    while (!(PEEK(0xD082) & 0x01)) {
        POKE(0xD081, 0x10);
        usleep(7000);
    }

//dengland This delay is required or subsequent accesses will silently fail.
//Moreover, usleep is completely unreliable for this purpose.
//    for (cnt; cnt < 10000; cnt++) {
//        POKE(0xD020U, PEEK(0xD020U));
//    }

//  POKE(0xD020U, 0);

//  Mounted disk, so now get the directory.

//  Read T40 S1 (sectors begin at 1, not 0)
	POKE(0xD080U, 0x60); // motor and LED on
	POKE(0xD081U, 0x20); // Wait for motor spin up

    while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
    }

	POKE(0xD084U, 39);
	POKE(0xD085U, 1);
	POKE(0xD086U, 0);

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

	POKE(0xD081U, 0x41); // Read sector

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

//  abort if the sector read failed	
    if (PEEK(0xD082U) & 0x18) {
        POKE(0xD080U, 0x40);
        JudeSetPointer(MPTR_NORMAL);
//      POKE(0xD020U, 2);
		return; 
    }

//  Disk name is in bytes $04-$14, so skip first four bytes of sector buffer
//  (we have to assign the PEEK here, so it doesn't get optimised away)
	for (x = 0; x < 4; x++)
		c = PEEK(0xD087U);

    n = 0;

//  Then output title 
	for (x = 0; x < 16; x++) {
		c = PEEK(0xD087U);
//		if (c >= 'A' && c <= 'Z')
//			c &= 0x1f;
//		if (c >= 'a' && c <= 'z')
//			c &= 0x1f;
	
    	lpoke(FDDDIRADDR + (n * 20) + x, c & 0x7F);
	}
    n++;

//  Read sector
	POKE(0xD084U, 39);
	POKE(0xD085U, 2);
	POKE(0xD086U, 0);

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

	POKE(0xD081U, 0x41); 

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

//  abort if the sector read failed
	if (PEEK(0xD082U) & 0x18) {
        POKE(0xD080U, 0x40);
        JudeSetPointer(MPTR_NORMAL);
//      POKE(0xD020U, 2);
		return; 
    }

// Make sure we can see the data
//        LDA #$80
//        TRB $D689
    POKE(0xD689U, PEEK(0xD689) & 0x7F);

//  Skip 1st half of sector
	x = 0;
	do
		c = PEEK(0xD087U);
	while (++x);
	
//  begin drawing on row 1 of screen
//  x = 1; 
	for (i = 0; i < 8; i++)
		if (!draw_directory_entry(n))
			n++;
    
	POKE(0xD084U, 39);
	POKE(0xD085U, 3);
	POKE(0xD086U, 0);

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

	POKE(0xD081U, 0x41); // Read sector

	while (PEEK(0xD082U) & 0x80) {
        POKE(0xD020U, PEEK(0xD020U));
	}

//  abort if the sector read failed
	if (PEEK(0xD082U) & 0x18) {
        POKE(0xD080U, 0x40);
        JudeSetPointer(MPTR_NORMAL);
//      POKE(0xD020U, 2);
		return; 
    }

// Make sure we can see the data
//        LDA #$80
//        TRB $D689
    POKE(0xD689U, PEEK(0xD689) & 0x7F);


	for (i = 0; i < 16; i++) {
		if (!draw_directory_entry(n))
			n++;
		if (n >= 23)
			break;
	}

    disk_filecnt = n;

// Turn floppy LED and motor back off
	POKE(0xD080U, 0);
    JudeSetPointer(MPTR_NORMAL);
}


unsigned char detect_cpu_speed(void)
{
	if (freeze_peek(0xffd367dL) & 0x10)
		return 40;
	if (freeze_peek(0xffd3054L) & 0x40)
		return 40;
	if (freeze_peek(0xffd3031L) & 0x40)
		return 3;
	if (freeze_peek(0xffd0030L) & 0x01)
		return 2;
	return 1;
}

void set_cpu_speed(unsigned char speed)
{
	switch (speed) {
//	case 1:
//		break;
	case 2:
		// Make it 2MHz
		freeze_poke(0xffd0030L, 1);
		break;
	case 3:
		// Make it 3.5MHz
		freeze_poke(0xffd0030L, 0);
		freeze_poke(0xffd3031L, freeze_peek(0xffd3031L) | 0x40);
		break;
	case 40:
		// Make it 40MHz
		freeze_poke(0xffd367dL, freeze_peek(0xffd367dL) | 0x10);
		break;
	default:
		// Make it 1MHz
		freeze_poke(0xffd0030L, 0);
		freeze_poke(0xffd3031L, freeze_peek(0xffd3031L) & 0xbf);
		freeze_poke(0xffd3054L, freeze_peek(0xffd3054L) & 0xbf);
		freeze_poke(0xffd367dL, freeze_peek(0xffd367dL) & 0xef);
		break;
	}
}

// char c65_rom_name[12];
// char* detect_rom(void)
// {
// 	unsigned char i;

// 	// Check for C65 ROM via version string
// 	if ((freeze_peek(0x20016L) == 'V') && (freeze_peek(0x20017L) == '9')) {
// 		c65_rom_name[0] = ' ';
// 		c65_rom_name[1] = 'C';
// 		c65_rom_name[2] = '6';
// 		c65_rom_name[3] = '5';
// 		c65_rom_name[4] = ' ';
// 		for (i = 0; i < 6; i++)
// 			c65_rom_name[5 + i] = freeze_peek(0x20017L + i);
// 		c65_rom_name[11] = 0;
// 		return c65_rom_name;
// 	}

// 	if (freeze_peek(0x2e47dL) == 'J') {
// 		// Probably jiffy dos
// 		if (freeze_peek(0x2e535L) == 0x06)
// 			return "sx64 jiffy ";
// 		else
// 			return "c64 jiffy	";
// 	}

// 	// Else guess using detection routines from detect_roms.c
// 	// These were built using a combination of the ROMs from zimmers.net/pub/c64/firmware,
// 	// the RetroReplay ROM collection, and the JiffyDOS ROMs
// 	if (freeze_peek(0x2e449L) == 0x2e)
// 		return "C64GS			";
// 	if (freeze_peek(0x2e119L) == 0xc9)
// 		return "C64 REV1	 ";
// 	if (freeze_peek(0x2e67dL) == 0xb0)
// 		return "C64 REV2 JP";
// 	if (freeze_peek(0x2ebaeL) == 0x5b)
// 		return "C64 REV3 DK";
// 	if (freeze_peek(0x2e0efL) == 0x28)
// 		return "C64 SCAND	";
// 	if (freeze_peek(0x2ebf3L) == 0x40)
// 		return "C64 SWEDEN ";
// 	if (freeze_peek(0x2e461L) == 0x20)
// 		return "CYCLONE 1.0";
// 	if (freeze_peek(0x2e4a4L) == 0x41)
// 		return "DOLPHIN 1.0";
// 	if (freeze_peek(0x2e47fL) == 0x52)
// 		return "DOLPHIN 2AU";
// 	if (freeze_peek(0x2eed7L) == 0x2c)
// 		return "DOLPHIN 2P1";
// 	if (freeze_peek(0x2e7d2L) == 0x6b)
// 		return "DOLPHIN 2P2";
// 	if (freeze_peek(0x2e4a6L) == 0x32)
// 		return "DOLPHIN 2P3";
// 	if (freeze_peek(0x2e0f9L) == 0xaa)
// 		return "DOLPHIN 3.0";
// 	if (freeze_peek(0x2e462L) == 0x45)
// 		return "DOSROM V1.2";
// 	if (freeze_peek(0x2e472L) == 0x20)
// 		return "MERCRY3 PAL";
// 	if (freeze_peek(0x2e16dL) == 0x84)
// 		return "MERCRY NTSC";
// 	if (freeze_peek(0x2e42dL) == 0x4c)
// 		return "PET 4064	 ";
// 	if (freeze_peek(0x2e1d9L) == 0xa6)
// 		return "SX64 CROACH";
// 	if (freeze_peek(0x2eba9L) == 0x2d)
// 		return "SX64 SCAND ";
// 	if (freeze_peek(0x2e476L) == 0x2a)
// 		return "TRBOACS 2.6";
// 	if (freeze_peek(0x2e535L) == 0x07)
// 		return "TRBOACS 3P1";
// 	if (freeze_peek(0x2e176L) == 0x8d)
// 		return "TRBOASC 3P2";
// 	if (freeze_peek(0x2e42aL) == 0x72)
// 		return "TRBOPROC US";
// 	if (freeze_peek(0x2e4acL) == 0x81)
// 		return "C64C 251913";
// 	if (freeze_peek(0x2e479L) == 0x2a)
// 		return "C64 REV2	 ";
// 	if (freeze_peek(0x2e535L) == 0x06)
// 		return "SX64 REV4	";
// 	return "UNKNOWN ROM";
// }

void	freeze_reset(void) {
		unsigned char c;

//	Set C64 memory map, PC to reset vector and resume
		freeze_poke(0xFFD3640U + 8, freeze_peek(0x2FFFCL));
		freeze_poke(0xFFD3640U + 9, freeze_peek(0x2FFFDL));
//	Reset $01 port values
		freeze_poke(0xFFD3640U + 0x10, 0x3f);
		freeze_poke(0xFFD3640U + 0x11, 0x3f);

//	disable interrupts, clear decimal mode
		freeze_poke(0xFFD3640U + 0x07, 0xe7);
//	Clear memory mapping
		for (c = 0x0A; c <= 0x0F; c++)
				freeze_poke(0xFFD3640U + c, 0);
//	Turn off extended graphics mode, if selected
		freeze_poke(0xFFD3054U,0x00);
		unfreeze_slot(slot_number);

		KarlPanic();
}


unsigned char string_decimal_digits[16][5] = { { 0, 0, 0, 0, 1 }, { 0, 0, 0, 0, 2 }, { 0, 0, 0, 0, 4 }, { 0, 0, 0, 0, 8 },
	{ 0, 0, 0, 1, 6 }, { 0, 0, 0, 3, 2 }, { 0, 0, 0, 6, 4 }, { 0, 0, 1, 2, 8 }, { 0, 0, 2, 5, 6 }, { 0, 0, 5, 1, 2 },
	{ 0, 1, 0, 2, 4 }, { 0, 2, 0, 4, 8 }, { 0, 4, 0, 9, 6 }, { 0, 8, 1, 9, 2 }, { 1, 6, 3, 8, 4 }, { 3, 2, 7, 6, 8 } };

unsigned char string_buffer[6];
unsigned char string_hex_digits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0x01, 0x02, 0x03, 0x04, 0x05,
	0x06 };


unsigned char ii, j, carry, temp;
static unsigned int value;
void	decimal_to_string(unsigned int v) {
	value = v;

	// Start with all zeros
	for (ii = 0; ii < 5; ii++)
		string_buffer[ii] = 0;

	// Add power of two strings for all non-zero bits in value.
	// XXX - We should use BCD mode to do this more efficiently
	for (ii = 0; ii < 16; ii++) {
		if (value & 1) {
			carry = 0;
			for (j = 4; j < 128; j--) {
				temp = string_buffer[j] + string_decimal_digits[ii][j] + carry;
				if (temp > 9) {
					temp -= 10;
					carry = 1;
				}
				else
					carry = 0;
				string_buffer[j] = temp;
			}
		}
		value = value >> 1;
	}

	// Now convert to ascii digits
	for (j = 0; j < 5; j++)
		string_buffer[j] = string_buffer[j] | '0';

	// and clear out leading zeros
	for (j = 0; j < 4; j++) {
		if (string_buffer[j] != '0')
			break;
		string_buffer[j] = ' ';
	}
}

#define thumbnail_buffer	0xE000U
//unsigned char thumbnail_buffer[4096];

void draw_thumbnail(void)
{
	// Take the 4K of thumbnail data and render it to the display
	// area at $50000.
	// This requires a bit of fiddling:
	// First, the thumbnail data has a nominal address of $0010000
	// in the frozen memory, which overlaps with the main RAM,
	// so we can't use our normal routine to find the start of freeze
	// memory. Instead, we will find that region directly, and then
	// process the 8 sectors of data in a linear fashion.
	// The thumbnail bytes themselves are arranged linearly, so we
	// have to work out the right place to store them in the thumbnail
	// data.	We would really like to avoid having to use lpoke for
	// this all the time, because lpoke() uses a DMA for every memory
	// access, which really slows things down. This would be bad, since
	// we want users to be able to very quickly and smoothly flip between
	// the freeze slots and see what is there.
	// But there isn't currently a good solution to this, short of having
	// a second buffer into which to render it.
	unsigned char x, y, i;
	unsigned short yoffset,yoffset_out,xoffset,j;
	uint32_t thumbnail_sector = find_thumbnail_offset();

	// Can't find thumbnail area?	Then show no thumbnail
	if (thumbnail_sector == 0xFFFFFFFFU) {
		lfill(0x50000L, 0, 10 * 6 * 64);
		return;
	}
	// Copy thumbnail memory to buffer
	for (i = 0; i < 8; i++) {
		sdcard_readsector(freeze_slot_start_sector + thumbnail_sector + i);
		lcopy((long)sector_buffer, (long)thumbnail_buffer + (i * 0x200), 0x200);
	}

	// Pick colours of all pixels in the thumbnail
	for(j=0;j<4096;j++) 
        POKE(thumbnail_buffer + j, colour_table[PEEK(thumbnail_buffer + j)]);
	

//dengland
//***FIXME
//The bitmap seems pretty regular to me however there is a difference between "old" (existing 
//on my card) images and the new ones.	The new ones are currently displayed shifted right by 
//a column (8 pixels)

//	This would just shift the image up by a row (pixel)
//	Fix column 0 of pixels
//	yoffset=0;
//	for(j=0;j<49;j++) {
//		thumbnail_buffer[yoffset]=thumbnail_buffer[yoffset+1];
//		yoffset+=80;
//	}
	
// Rearrange pixels
	yoffset = 80 + 8; // skip dud first line

	for (y = 0; y < 48; y++) {
		yoffset_out = ((y & 7) << 3) + (y >> 3) * 64;
		xoffset=0;
		for (x = 0; x < 81; x+=8) {
			j=8; 
			lcopy ((unsigned long)thumbnail_buffer + x + yoffset, 0x50000L + xoffset + yoffset_out, j);

			xoffset+=64*6;			
		}
		yoffset += 80;
	}
}