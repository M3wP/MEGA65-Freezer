;	.setcpu "65C02"
	.export _mega65_dos_attachd81
	.export _mega65_dos_chdir, _mega65_dos_chdirroot
	.export _mega65_dos_exechelper
	.export	_fetch_freeze_region_list_from_hypervisor
	.export _find_freeze_slot_start_sector
	.export _unfreeze_slot
	.export _read_file_from_sdcard
	.export _get_freeze_slot_count
	.export _opendir, _readdir, _closedir, _closeall
	
	.export	_mega65_save_zp

	.include "zeropage.inc"
	

.SEGMENT "DATA"
 savezp:
	.res	256


.SEGMENT "CODE"

	.p4510

_mega65_save_zp:
	LDA	#$00
	LDX	#$00
	LDY	#$00
	LDZ	#$00
	MAP
	EOM

	LDY	#$01
	TYS

	LDA	#$00
	TAB

	LDX	#$02
@loop:
	LDA	$00, X
	STA	savezp, X
	INX
	BNE	@loop

	RTS

_mega65_restore_zp:
	LDX	#$02
@loop:
	LDA	savezp, X
	STA	$00, X
	INX
	BNE	@loop

	RTS


	
_mega65_dos_exechelper:
	;; char mega65_dos_exechelper(char *image_name);

	LDA	#$00
	LDX	#$00
	LDY	#$00
	LDZ	#$00
	MAP
	EOM

	SEI

	LDY	#$01
	TYS

	LDA	#$00
	TAB

	LDA	#$80
	TRB	$D054

	LDA	#27
	STA	$D011

	LDA	#200
	STA	$D016

	LDA	#20
	STA	$D018

	LDA	#$00
	STA	$D060
	LDA	#$04
	STA	$D061
	LDA	#$00
	STA	$D062

	LDA	#$80
	TRB	$D031

	LDA	#$05
	TRB	$D054

	LDA	#$08
	TRB	$D031

;	Set VIC line size
	LDA #$28
	STA $D058
	LDA #$00
	STA $D059

;	Set VIC window w
	LDA	#$28
	STA	$D05E

;	CHRYSCL
	LDA	#$01
	STA	$D05B

;	Set VIC window h
	LDA	#$19
	STA	$D07B

	;; Get pointer to file name
	;; sp here is the ca65 sp ZP variable, not the stack pointer of a 4510
	ldy #1
	.p02
	lda (sp),y
	sta ptr1+1
	sta $0141
	dey
	lda (sp),y
	.p4510
	sta ptr1
	sta $0140

	;; Copy file name
	ldy #0
@NameCopyLoop:
	lda (ptr1),y
	sta $0100,y
	iny
	cmp #0
	bne @NameCopyLoop

	JSR	_mega65_restore_zp

	; close all files to work around hyppo file descriptor leak bug
        lda #$22
        sta $d640
        nop

	;;  Call dos_setname()
	ldy #>$0100
	ldx #<$0100
	lda #$2E     		; dos_setname Hypervisor trap
	STA $D640		; Do hypervisor trap
	NOP			; Wasted instruction slot required following hyper trap instruction
	;; XXX Check for error (carry would be clear)

	BCC	@error

	; close all files to work around hyppo file descriptor leak bug
       lda #$22
        sta $d640
        nop
	
	;; Now copy a little routine into place in $0340 that does the actual loading and jumps into
	;; the program when loaded.
	ldx #$00
@lfr1:	lda loadfile_routine,x
	sta $0340,x
	inx
	cpx #$34
	bne @lfr1

	;; Call helper routine
	jsr $0340
	
@error:
	;; as this is effectively like exec() on unix, it can only return an error
	LDA #$01
	LDX #$00
	
	RTS

loadfile_routine:
	LDA	#$2F
	STA	$00

	LDA	#$37
	STA	$01

;	LDA	#$41
;	STA	$00

	LDA	#$00
	STA	$D01A

	LDA	$DC0D
	ASL	$D019

	LDA	#$FF
	STA	$DC0D


	; Now load the file to $0400 over the screen
        lda #$36
        ldx #$FF
        ldy #$07
        ldz #$00
        sta $d640
        nop
        bcc @error

        LDX	#$FF
        TXS

        ldz     #$00
;@halt:
;		INC	$D020
;		BRA	@halt

        CLI
		jmp $080D

	rts
@error:
		LDA	#$02
		STA	$D020
		BRA	@error

	
_mega65_dos_attachd81:
	;; char mega65_dos_attachd81(char *image_name);

	;; Get pointer to file name
	;; sp here is the ca65 sp ZP variable, not the stack pointer of a 4510
	ldy #1
	.p02
	lda (sp),y
	sta ptr1+1
	sta $0441
	dey
	lda (sp),y
	.p4510
	sta ptr1
	sta $0440
	
	;; Copy file name
	ldy #0
@NameCopyLoop:
	lda (ptr1),y
	sta $0400,y
	iny
	cmp #0
	bne @NameCopyLoop
	
	;;  Call dos_setname()
	ldy #>$0400
	ldx #<$0400
	lda #$2E     		; dos_setname Hypervisor trap
	STA $D640		; Do hypervisor trap
	NOP			; Wasted instruction slot required following hyper trap instruction
	
	BCC	@return

        lda #$22
        sta $d640
        nop

	BCC	@return


	LDA	#$34
	STA	$D640
	CLV

	BCC	@return

	;; XXX Check for error (carry would be clear)

	;; Try to attach it
	LDA #$40
	STA $D640
	NOP

@return:
	;; return inverted carry flag, so result of 0 = success
	PHP
	PLA
	AND #$01
	EOR #$01
	LDX #$00

	RTS


_mega65_dos_chdirroot:
;	Change to root directory
		LDA #$3C
		STA $D640
		NOP
		RTS


_mega65_dos_chdir:
	;; char mega65_dos_chdir(char *dir_name);

	;; Get pointer to file name
	;; sp here is the ca65 sp ZP variable, not the stack pointer of a 4510
	ldy #1
	.p02
	lda (sp),y
	sta ptr1+1
	sta $0441
	dey
	lda (sp),y
	.p4510
	sta ptr1
	sta $0440
	
	;; Copy file name
	ldy #0
@NameCopyLoop:
	lda (ptr1),y
	sta $0400,y
	iny
	cmp #0
	bne @NameCopyLoop
	
	;;  Call dos_setname()
	ldy #>$0400
	ldx #<$0400
	lda #$2E     		; dos_setname Hypervisor trap
	STA $D640		; Do hypervisor trap
	NOP			; Wasted instruction slot required following hyper trap instruction
	;; XXX Check for error (carry would be clear)

	;; Find the file
	LDA #$34
	STA $D640
	NOP
	BCC @direntNotFound

	;; Try to change directory to it
	LDA #$0C
	STA $D640
	NOP

@direntNotFound:
	
	;; return inverted carry flag, so result of 0 = success
	PHP

	PLA
	AND #$01
	EOR #$01
	LDX #$00
	
	RTS
	

	
_unfreeze_slot:	

	;; Move 16-bit address from A/X to X/Y
	PHX
	TAY
	PLA
	TAX

	;; Call hypervisor trap
	LDA #$12    ; subfunction for syspart trap to unfreeze from a slot
	STA $D642   ; trigger hypervisor trap
	NOP         ; dead slot after hypervisor call that must be there to workaround CPU bug
	RTS

_get_freeze_slot_count:	

	;; Call hypervisor trap
	LDA #$16    ; subfunction for syspart trap to get freeze region list
	STA $D642   ; trigger hypervisor trap
	NOP         ; dead slot after hypervisor call that must be there to workaround CPU bug

	txa
	phy
	plx
	
	RTS	
	
_fetch_freeze_region_list_from_hypervisor:

	;; Move 16-bit address from A/X to X/Y
	PHX
	TAX
	PLA
	TAY

	;; Call hypervisor trap
	LDA #$14    ; subfunction for syspart trap to get freeze region list
	STA $D642   ; trigger hypervisor trap
	NOP         ; dead slot after hypervisor call that must be there to workaround CPU bug
	RTS

_find_freeze_slot_start_sector:	

	;; Move 16-bit address from A/X to X/Y
	;; XXX - We had to swap the X/Y byte order around for this to work: Why???
	PHX
	TAY
	PLA
	TAX

	;; Call hypervisor trap
	LDA #$10    ; subfunction for syspart trap to put start sector of freeze slot into $D681-$D684
	STA $D642   ; trigger hypervisor trap
	NOP         ; dead slot after hypervisor call that must be there to workaround CPU bug
	RTS
	

_read_file_from_sdcard:

	;;  read_file_from_sdcard(char *filename,uint32_t load_address);

	;; Hypervisor requires copy area to be page aligned, so
	;; we have to copy the name we want to load to somewhere on a page boundary
	;; This is a bit annoying.  I should find out why I made the hypervisor make
	;; such an requirement.  Oh, and it also has to be in the bottom 32KB of memory
	;; (that requirement makes more sense, as it is about ensuring that the
	;; Hypervisor can't be given a pointer that points into its own mapped address space)
	;; As we are not putting any screen at $0400, we can use that
	
	;; Get pointer to file name
	;; sp here is the ca65 sp ZP variable, not the stack pointer of a 4510
	ldy #5
	.p02
	lda (sp),y
	sta ptr1+1
	dey
	lda (sp),y
	.p4510
	sta ptr1

	;; Copy file name
	ldy #0
@NameCopyLoop:
	lda (ptr1),y
	sta $0400,y
	iny
	cmp #0
	bne @NameCopyLoop
	
	;;  Call dos_setname()
	ldy #>$0400
	ldx #<$0400
	lda #$2E     		; dos_setname Hypervisor trap
	STA $D640		; Do hypervisor trap
	NOP			; Wasted instruction slot required following hyper trap instruction
	;; XXX Check for error (carry would be clear)

	;; Get Load address into $00ZZYYXX
	ldy #2
	.p02
	lda (sp),y
	.p4510
	taz
	ldy #0
	.p02
	lda (sp),y
	tax
	iny
	lda (sp),y
	.p4510
	tay

	;; Ask hypervisor to do the load
	LDA #$36
	STA $D640		
	NOP
	;; XXX Check for error (carry would be clear)

	LDZ #$00
	
	RTS

_closeall:
	; close all files to work around hyppo file descriptor leak bug
        lda #$22
        sta $d640
        nop

	rts
	
	;; closedir takes file descriptor as argument (appears in A)
_closedir:
	TAX
	LDA #$16
	STA $D640
	NOP
	LDX #$00
	RTS
	
	;; Opendir takes no arguments and returns File descriptor in A
_opendir:
	LDA #$12
	STA $D640
	NOP
	LDX #$00
	RTS

	;; readdir takes the file descriptor returned by opendir as argument
	;; and gets a pointer to a MEGA65 DOS dirent structure.
	;; Again, the annoyance of the MEGA65 Hypervisor requiring a page aligned
	;; transfer area is a nuisance here. We will use $0400-$04FF, and then
	;; copy the result into a regular C dirent structure
	;;
	;; d_ino = first cluster of file
	;; d_off = offset of directory entry in cluster
	;; d_reclen = size of the dirent on disk (32 bytes)
	;; d_type = file/directory type
	;; d_name = name of file
_readdir:

	pha
	
	;; First, clear out the dirent
	ldx #0
	txa
@l1:	sta _readdir_dirent,x	
	dex
	bne @l1

	;; Third, call the hypervisor trap
	;; File descriptor gets passed in in X.
	;; Result gets written to transfer area we setup at $0400
	plx
	ldy #>$0400 		; write dirent to $0400 
	lda #$14
	STA $D640
	NOP

	bcs @readDirSuccess

	;;  Return end of directory
	lda #$00
	ldx #$00
	RTS

@readDirSuccess:
	
	;;  Copy file name
	ldx #$3f
@l2:	lda $0400,x
	sta _readdir_dirent+4+2+4+2,x
	dex
	bpl @l2
	;; make sure it is null terminated
	ldx $0400+64
	lda #$00
	sta _readdir_dirent+4+2+4+2,x

	;; Inode = cluster from offset 64+1+12 = 77
	ldx #$03
@l3:	lda $0477,x
	sta _readdir_dirent+0,x
	dex
	bpl @l3

	;; d_off stays zero as it is not meaningful here
	
	;; d_reclen we preload with the length of the file (this saves calling stat() on the MEGA65)
	ldx #3
@l4:	lda $0400+64+1+12+4,x
	sta _readdir_dirent+4+2,x
	dex
	bpl @l4

	;; File type and attributes
	;; XXX - We should translate these to C style meanings
	lda $0400+64+1+12+1+4+4
	sta _readdir_dirent+4+2+4

	;; Return address of dirent structure
	lda #<_readdir_dirent
	ldx #>_readdir_dirent
	
	RTS

_readdir_dirent:
	.dword 0   		; d_ino
	.word 0			; d_off
	.dword 0		; d_reclen
	.word 0			; d_type
	.res 256,$00
