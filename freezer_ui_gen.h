#ifdef	INCLUDE_FREEZER_UI_GEN_H
#else
#define	INCLUDE_FREEZER_UI_GEN_H

struct process_descriptor_t process_descriptor;


extern unsigned char c64_palette[64];

extern unsigned char colour_table[256];

extern void 	set_palette(void);

extern unsigned char detect_cpu_speed(void);
extern void 	set_cpu_speed(unsigned char speed);

extern char* 	detect_rom(void);

extern void 	freeze_reset(void);


extern	void	decimal_to_string(unsigned int v);


extern	unsigned char string_buffer[];

extern 	void	draw_thumbnail();

extern	unsigned char thumbchars[6][20];

#endif