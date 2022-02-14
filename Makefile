CC65=	cc65
CL65=	cl65

#Can't mix 4510 and 65C02 right now
#COPTS=	-t c64 -Os --cpu 65c02 -Icc65/include
COPTS=	-t c64 -Os -Icc65/include

LOPTS=	--asm-include-dir cc65/asminc --cfg-path cc65/cfg --lib-path cc65/lib

ASSFILES=	freezer.s\
		freezer_ui.s\
		freezer_ui_m3wp.s\
		freezer_ui_gen.s\
		frozen_memory.s


#		m65_fat32.s\
		m65_dos.s\
		m65_hal_mega65.s\
		m65_mem.s\
		_m65lib.s


DATAFILES=	ascii8x8.bin

HEADERS=	Makefile \
		freezer.h \
		freezer_ui.h \
		freezer_ui_m3wp.h\
		freezer_ui_gen.h\
		frozen_memory.h\
		ascii.h

TILDOLIBFILES=	jude.o\
		karljr.o\
		_jude_widgets.o\
		_jude.o\
		_karljr.o\
		_karljr_zp.o

TILDOINCLUDES=	_jude_types.inc\
		_karljr_types.inc

TILDOHEADERS=	jude_widgets.h\
		jude.h \
		karljr.h

M65LIBFILES=	m65_fat32.o\
		m65_dos.o\
		m65_hal_mega65.o\
		m65_mem.o\
		_m65lib.o

M65LIBHEADERS=	m65_fat32.h\
		m65_dos.h\
		m65_hal.h \
		m65_mem.h\
		ascii.h


FREEZER.M65:	$(ASSFILES) $(HEADERS) libmega65.a libtilda.a
	$(warning ======== Making: $@)
	$(CL65) $(COPTS) $(LOPTS) --config jkjr.cfg -vm --add-source -Ln freezer.vice -l freezer.list -m freezer.map -o FREEZER.M65 $(ASSFILES) libmega65.a libtilda.a

%.o:	%.s
	$(warning ======== Making: $@)
	ca65 -o $@ $<

%.s:	%.c 
	$(warning ======== Making: $@)
	$(CC65) $(COPTS) -o $@ $<

libmega65.a:	$(M65LIBFILES) $(M65LIBHEADERS)
	$(warning ======== Making: $@)
	ar65 r $@ $(M65LIBFILES)

libtilda.a:		$(TILDOLIBFILES) $(TILDOHEADERS) $(TILDOINCLUDES)
	$(warning ======== Making: $@)
	ar65 r $@ $(TILDOLIBFILES)


run:	FREEZER.M65
	m65 -l com6 -s 2000000 -F -4 -r $<