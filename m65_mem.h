#ifdef	INCLUDE_M65_MEM_H
#else
#define	INCLUDE_M65_MEM_H

extern void mega65_io_enable(void);
extern unsigned char lpeek(long address);
extern void lpoke(long address, unsigned char value);
extern void lcopy(long source_address, long destination_address, unsigned int count);
extern void lcopy_safe(unsigned long src, unsigned long dst, unsigned int count);
extern void lfill(long destination_address, unsigned char value, unsigned int count);

#define POKE(X, Y) (*(unsigned char*)(X)) = Y
#define PEEK(X) (*(unsigned char*)(X))

extern unsigned char lpeek_debounced(long address);

struct dmagic_dmalist
{
  // Enhanced DMA options
  unsigned char option_0b;
  unsigned char option_80;
  unsigned char source_mb;
  unsigned char option_81;
  unsigned char dest_mb;
  unsigned char option_85;
  unsigned char dest_skip;
  unsigned char end_of_options;

  // F018B format DMA request
  unsigned char command;
  unsigned int count;
  unsigned int source_addr;
  unsigned char source_bank;
  unsigned int dest_addr;
  unsigned char dest_bank;
  unsigned char sub_cmd; // F018B subcmd
  unsigned int modulo;
};

extern struct dmagic_dmalist dmalist;
extern unsigned char dma_byte;


#endif