#ifdef	INCLUDE_M65_HAL_H
#else
#define	INCLUDE_M65_HAL_H

#include <sys/types.h>
#include <ctype.h>
#include <stdint.h>

extern unsigned char sdhc_card;
extern uint8_t sector_buffer[512];
extern unsigned short slot_number;

extern void sdcard_reset(void);
extern uint32_t sdcard_getsize(void);
extern void sdcard_open(void);
extern void sdcard_writesector(const uint32_t sector_number, uint8_t is_multi);
extern void sdcard_readsector(const uint32_t sector_number);
extern void sdcard_erase(const uint32_t first_sector, const uint32_t last_sector);
extern void mega65_fast(void);
extern void sdcard_map_sector_buffer(void);
extern void usleep(uint32_t micros);
extern void sdcard_writenextsector(void);
extern void sdcard_writemultidone(void);

extern void clear_sector_buffer(void);

#endif