CC65=	cc65
CL65=	cl65

#Can't mix 4510 and 65C02 right now
#COPTS=	-t c64 -Os --cpu 65c02 -Icc65/include
COPTS=	-t c64 -Icc65/include

LOPTS=	--asm-include-dir cc65/asminc --cfg-path cc65/cfg --lib-path cc65/lib

ASSFILES=	freezer.s\
		freezer_ui.s\
		freezer_ui_m3wp.s\
		freezer_ui_gen.s\
		frozen_memory.s\
		m65_fat32.s\
		m65_dos.s\
		m65_hal_mega65.s\
		m65_mem.s\
		_m65lib.s\
		jude.s\
		karljr.s\
		_jude_widgets.s\
		_jude.s\
		_karljr.s\
		_karljr_zp.s

DATAFILES=	ascii8x8.bin

HEADERS=	Makefile \
		freezer.h \
		freezer_ui.h \
		freezer_ui_m3wp.h\
		freezer_ui_gen.h\
		frozen_memory.h\
		m65_fat32.h\
		m65_dos.h\
		m65_hal.h \
		m65_mem.h \
		jude_widgets.h\
		jude.h \
		karljr.h \
		ascii.h

%.s:	%.c $(HEADERS)
	$(warning ======== Making: $@)
	$(CC65) $(COPTS) -o $@ $<

FREEZER.M65:	$(ASSFILES) $(HEADERS)
	$(warning ======== Making: $@)
	$(CL65) $(COPTS) $(LOPTS) --config jkjr.cfg -vm --add-source -l freezer.list -m freezer.map -o FREEZER.M65 $(ASSFILES)
