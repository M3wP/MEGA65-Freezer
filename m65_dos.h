#ifdef	INCLUDE_M65_DOS_H
#else
#define	INCLUDE_M65_DOS_H

#include <sys/types.h>
#include <ctype.h>
#include <stdint.h>

extern char cdecl mega65_dos_chdirroot(void);
extern char cdecl mega65_dos_chdir(char* dirname);
extern char cdecl mega65_dos_attachd81(char* image_name);
extern char cdecl mega65_dos_exechelper(char* filename);

extern void cdecl read_file_from_sdcard(char* filename, uint32_t load_address);
extern unsigned char opendir(void);
extern struct m65_dirent* readdir(unsigned char);
extern void closedir(unsigned char);
extern void closeall(void);


struct m65_dirent {
  uint32_t d_ino;
  uint16_t d_off;
  uint32_t d_reclen;
  uint16_t d_type;
  char d_name[256];
};

struct file_descriptor_t {
#define FD_DISK_ID_FILE_CLOSED 0xFF
  unsigned char disk_id;
  unsigned long start_cluster;
  unsigned long current_cluster;
  unsigned char sector_in_cluster;
  unsigned long file_length;
  unsigned long buffer_position;
  unsigned long directory_cluster;
  unsigned short entry_in_directory;
  unsigned long buffer_address;
  unsigned short bytes_in_buffer;
  unsigned short offset_in_buffer;
};

#endif
