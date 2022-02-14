CC65=	cc65
CL65=	cl65

TILDAPATH=	mega65-tilda-lib

#Can't mix 4510 and 65C02 right now
#COPTS=	-t c64 -Os --cpu 65c02 -Icc65/include
COPTS=	-t c64 -Os -Icc65/include -I$(TILDAPATH)/inc

LOPTS=	--asm-include-dir cc65/asminc --cfg-path cc65/cfg --lib-path cc65/lib --lib-path $(TILDAPATH)/lib

ASSFILES=	freezer.s\
		freezer_ui.s\
		freezer_ui_m3wp.s\
		freezer_ui_gen.s\
		frozen_memory.s

DATAFILES=	ascii8x8.bin

HEADERS=	Makefile \
		freezer.h \
		freezer_ui.h \
		freezer_ui_m3wp.h\
		freezer_ui_gen.h\
		frozen_memory.h\
		ascii.h


M65LIBCCFILES=	m65_fat32.c\
		m65_dos.c\
		m65_hal_mega65.c\
        m65_mem.c

M65LIBASMFILES=	_m65lib.s

M65LIBHEADERFILES=	m65_fat32.h\
		m65_dos.h\
		m65_hal.h \
		m65_mem.h\
		ascii.h


FREEZER.M65:	$(ASSFILES) $(HEADERS) libmega65.a $(TILDAPATH)/lib/libtilda.a
	$(warning ======== Making: $@)
	$(CL65) $(COPTS) $(LOPTS) --config $(TILDAPATH)/tilda.cfg -vm --add-source -Ln freezer.vice -l freezer.list -m freezer.map -o FREEZER.M65 $(ASSFILES) libmega65.a $(TILDAPATH)/lib/libtilda.a

%.o:	%.s
	$(warning ======== Making: $@)
	ca65 -o $@ $<

%.s:	%.c 
	$(warning ======== Making: $@)
	$(CC65) $(COPTS) -o $@ $<


libmega65.a:	$(M65LIBCCFILES:.c=.o) $(M65LIBASMFILES:.s=.o) 
		$(warning ======== Making: $@)
		ar65 r $@ $(M65LIBCCFILES:.c=.o) $(M65LIBASMFILES:.s=.o) 

$(M65LIBCCFILES:.c=.o): $(M65LIBCCFILES:.c=.s)

$(M65LIBCCFILES:.c=.s): $(M65LIBCCFILES) $(M65LIBHEADERFILES)

$(M65LIBASMFILES:.s=.o):	$(M65LIBASMFILES)



$(TILDAPATH)/lib/libtilda.a:		
	$(warning ======== Making: $@)
	make -C $(TILDAPATH)

run:	FREEZER.M65
	m65 -l com6 -s 2000000 -F -4 -r $<
