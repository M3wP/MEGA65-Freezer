	.export	_fetch_freeze_region_list_from_hypervisor
	.export _find_freeze_slot_start_sector
	.export _unfreeze_slot
	.export _get_freeze_slot_count

	.CODE

	.setcpu	"4510"

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
