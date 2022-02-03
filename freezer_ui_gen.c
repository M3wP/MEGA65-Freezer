#include "m65_mem.h"
#include "m65_hal.h"
#include "frozen_memory.h"
#include "ascii.h"

#include "karljr.h"


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

void set_palette(void)
{
  unsigned char c, x, y;

  // First set the 16 C64 colours
  // unsigned char c;
  POKE(0xD070U, 0xFF);
  // for (c = 0; c < 16; c++) {
  //   POKE(0xD100U + c, c64_palette[c * 4 + 0]);
  //   POKE(0xD200U + c, c64_palette[c * 4 + 1]);
  //   POKE(0xD300U + c, c64_palette[c * 4 + 2]);
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
  colour_table[0x00] = 0x20; // black   ($00 = transparent colour, so we have to use very-dim red instead)
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
  colour_table[0x01] = 0x06;  // dim blue -> blue
  // colour_table[0x02] = 0x06;  // medium dim blue -> blue
  // colour_table[0x03] = 0x06;  // bright blue -> blue
  colour_table[0x04] = 0x00;  // dim green + no blue
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

  for (x = 0; x < 10; x++) {
    for (y = 0; y < 6; y ++) {
      thumbchars[y][x * 2] = c;
      thumbchars[y][x * 2 + 1] = 0x14;
      c++;
    }
  }
};


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
//  case 1:
//    break;
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

char c65_rom_name[12];
char* detect_rom(void)
{
  unsigned char i;

  // Check for C65 ROM via version string
  if ((freeze_peek(0x20016L) == 'V') && (freeze_peek(0x20017L) == '9')) {
    c65_rom_name[0] = ' ';
    c65_rom_name[1] = 'C';
    c65_rom_name[2] = '6';
    c65_rom_name[3] = '5';
    c65_rom_name[4] = ' ';
    for (i = 0; i < 6; i++)
      c65_rom_name[5 + i] = freeze_peek(0x20017L + i);
    c65_rom_name[11] = 0;
    return c65_rom_name;
  }

  if (freeze_peek(0x2e47dL) == 'J') {
    // Probably jiffy dos
    if (freeze_peek(0x2e535L) == 0x06)
      return "sx64 jiffy ";
    else
      return "c64 jiffy  ";
  }

  // Else guess using detection routines from detect_roms.c
  // These were built using a combination of the ROMs from zimmers.net/pub/c64/firmware,
  // the RetroReplay ROM collection, and the JiffyDOS ROMs
  if (freeze_peek(0x2e449L) == 0x2e)
    return "C64GS      ";
  if (freeze_peek(0x2e119L) == 0xc9)
    return "C64 REV1   ";
  if (freeze_peek(0x2e67dL) == 0xb0)
    return "C64 REV2 JP";
  if (freeze_peek(0x2ebaeL) == 0x5b)
    return "C64 REV3 DK";
  if (freeze_peek(0x2e0efL) == 0x28)
    return "C64 SCAND  ";
  if (freeze_peek(0x2ebf3L) == 0x40)
    return "C64 SWEDEN ";
  if (freeze_peek(0x2e461L) == 0x20)
    return "CYCLONE 1.0";
  if (freeze_peek(0x2e4a4L) == 0x41)
    return "DOLPHIN 1.0";
  if (freeze_peek(0x2e47fL) == 0x52)
    return "DOLPHIN 2AU";
  if (freeze_peek(0x2eed7L) == 0x2c)
    return "DOLPHIN 2P1";
  if (freeze_peek(0x2e7d2L) == 0x6b)
    return "DOLPHIN 2P2";
  if (freeze_peek(0x2e4a6L) == 0x32)
    return "DOLPHIN 2P3";
  if (freeze_peek(0x2e0f9L) == 0xaa)
    return "DOLPHIN 3.0";
  if (freeze_peek(0x2e462L) == 0x45)
    return "DOSROM V1.2";
  if (freeze_peek(0x2e472L) == 0x20)
    return "MERCRY3 PAL";
  if (freeze_peek(0x2e16dL) == 0x84)
    return "MERCRY NTSC";
  if (freeze_peek(0x2e42dL) == 0x4c)
    return "PET 4064   ";
  if (freeze_peek(0x2e1d9L) == 0xa6)
    return "SX64 CROACH";
  if (freeze_peek(0x2eba9L) == 0x2d)
    return "SX64 SCAND ";
  if (freeze_peek(0x2e476L) == 0x2a)
    return "TRBOACS 2.6";
  if (freeze_peek(0x2e535L) == 0x07)
    return "TRBOACS 3P1";
  if (freeze_peek(0x2e176L) == 0x8d)
    return "TRBOASC 3P2";
  if (freeze_peek(0x2e42aL) == 0x72)
    return "TRBOPROC US";
  if (freeze_peek(0x2e4acL) == 0x81)
    return "C64C 251913";
  if (freeze_peek(0x2e479L) == 0x2a)
    return "C64 REV2   ";
  if (freeze_peek(0x2e535L) == 0x06)
    return "SX64 REV4  ";
  return "UNKNOWN ROM";
}

void  freeze_reset(void) {
    unsigned char c;

//  Set C64 memory map, PC to reset vector and resume
    freeze_poke(0xFFD3640U + 8, freeze_peek(0x2FFFCL));
    freeze_poke(0xFFD3640U + 9, freeze_peek(0x2FFFDL));
//  Reset $01 port values
    freeze_poke(0xFFD3640U + 0x10, 0x3f);
    freeze_poke(0xFFD3640U + 0x11, 0x3f);

//  disable interrupts, clear decimal mode
    freeze_poke(0xFFD3640U + 0x07, 0xe7);
//  Clear memory mapping
    for (c = 0x0A; c <= 0x0F; c++)
        freeze_poke(0xFFD3640U + c, 0);
//  Turn off extended graphics mode, if selected
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
void  decimal_to_string(unsigned int v) {
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

//#define thumbnail_buffer  0x00008000U
unsigned char thumbnail_buffer[4096];

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
  // data.  We would really like to avoid having to use lpoke for
  // this all the time, because lpoke() uses a DMA for every memory
  // access, which really slows things down. This would be bad, since
  // we want users to be able to very quickly and smoothly flip between
  // the freeze slots and see what is there.
  // But there isn't currently a good solution to this, short of having
  // a second buffer into which to render it.
  unsigned char x, y, i;
  unsigned short yoffset,yoffset_out,xoffset,j;
  uint32_t thumbnail_sector = find_thumbnail_offset();

  // Can't find thumbnail area?  Then show no thumbnail
  if (thumbnail_sector == 0xFFFFFFFFL) {
    lfill(0x50000L, 0, 10 * 6 * 64);
    return;
  }
  // Copy thumbnail memory to buffer
  for (i = 0; i < 8; i++) {
    sdcard_readsector(freeze_slot_start_sector + thumbnail_sector + i);
    lcopy((long)sector_buffer, thumbnail_buffer + (i * 0x200), 0x200);
  }

  // Pick colours of all pixels in the thumbnail
  for(j=0;j<4096;j++) thumbnail_buffer[j]=colour_table[thumbnail_buffer[j]];
  

//dengland
//  I've removed these "fixes".  The bitmap seems pretty regular to me.

// Fix column 0 of pixels
  // yoffset=0;
  // for(j=0;j<49;j++) {
  //   thumbnail_buffer[yoffset]=thumbnail_buffer[yoffset+1];
  //   yoffset+=80;
  // }
  
  // Rearrange pixels
  //  yoffset = 80+13; // skip dud first line
  yoffset = 80; // skip dud first line


  for (y = 0; y < 48; y++) {
    yoffset_out = ((y & 7) << 3) + (y >> 3) * 64;
    xoffset=0;
//  for (x = 0; x < 73; x+=8) {
    for (x = 0; x < 80; x+=8) {
      // Also the whole thing is rotated by one byte, so add that on as we plot the pixel
      // PGS Optimise here

      j=8; 
//    if (x==72) j=2;

      lcopy ((unsigned long)&thumbnail_buffer[x + yoffset],
       0x50000L + xoffset + yoffset_out,
       j);

      xoffset+=64*6;      
    }
    yoffset += 80;
  }
}