#ifdef	INCLUDE_FREEZER_UI_GEN_H
#else
#define	INCLUDE_FREEZER_UI_GEN_H

struct process_descriptor_t process_descriptor;

extern unsigned short file_count;
extern unsigned short dir_depth;
extern unsigned char drive_id;
extern char disk_name_return[32];
extern unsigned char disk_filecnt;


extern unsigned char c64_palette[64];

extern unsigned char colour_table[256];

extern void    flash_control(word ctrl, word clr);
extern void    flash_border(word clr);

extern void 	set_palette(void);

extern unsigned char detect_cpu_speed(void);
extern void 	set_cpu_speed(unsigned char speed);

//extern char* 	detect_rom(void);

extern void 	freeze_reset(void);


extern	void	decimal_to_string(unsigned int v);


extern	unsigned char string_buffer[];

extern 	void	draw_thumbnail();

extern	unsigned char thumbchars[6][20];

extern	void	save_to_slot(void);

extern	void 	scan_directory(unsigned char id);
extern 	void	draw_directory_contents(void);

extern	void	cntrl_state_dirty(void* ctrl);

#endif