#ifdef	INCLUDE_FROZEN_MEMORY_GEN_H
#else
#define	INCLUDE_FROZEN_MEMORY_GEN_H

#include <sys/types.h>
#include <ctype.h>
#include <stdint.h>

#include "fileio.h"

//Note:  This is another one of those cobbled in asm support routines.
extern void unfreeze_slot(unsigned short);



extern void fetch_freeze_region_list_from_hypervisor(unsigned short);
extern unsigned char fastcall find_freeze_slot_start_sector(unsigned short);

extern void request_freeze_region_list(void);
extern uint32_t address_to_freeze_slot_offset(uint32_t address);
extern uint32_t find_thumbnail_offset(void);
extern unsigned char freeze_peek(uint32_t addr);
extern void freeze_poke(uint32_t addr, unsigned char v);
extern unsigned char freeze_fetch_sector(uint32_t addr, unsigned char* buffer);
extern unsigned char freeze_fetch_sector_32(uint32_t addr, uint32_t dest, unsigned int count);
extern unsigned char freeze_store_sector(uint32_t addr, unsigned char* buffer);
extern unsigned char freeze_store_sector_32(uint32_t addr, uint32_t src, unsigned int count);
extern unsigned short get_freeze_slot_count(void);

struct freeze_region_t {
  unsigned long address_base;
  union {
#define REGION_LENGTH_MASK 0xFFFFFF
    unsigned long region_length; // only lower 24 bits are valid, space occupied rounded up to next 512 bytes
    struct {
      unsigned char skip[3];
      unsigned char freeze_prep;
    };
  };
};

#define MAX_REGIONS (256 / sizeof(struct freeze_region_t))

extern struct freeze_region_t freeze_region_list[MAX_REGIONS];
extern unsigned char freeze_region_count;
extern unsigned long freeze_slot_start_sector;

struct process_descriptor_t {
  unsigned char task_id;
  char process_name[16];
  unsigned char d81_image0_flags;
  unsigned char d81_image1_flags;
  unsigned char d81_image0_namelen;
  unsigned char d81_image1_namelen;
  char d81_image0_name[32];
  char d81_image1_name[32];
  char filler[0x80 - (1 + 16 + 1 + 1 + 1 + 1 + 32 + 32)];
  struct file_descriptor_t file_descriptors[4];

  // Pad out to whole sector size, so we can load it easily
  char padding[256];
};


extern unsigned char freeze_peek(uint32_t addr);
extern void freeze_poke(uint32_t addr, unsigned char v);

#endif