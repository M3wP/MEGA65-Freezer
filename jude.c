#include	"jude.h"

void	JudeViewInit(karlFarPtr_t *view) {
	zreg0wl = view->loword;
	zreg0wh = view->hiword;

	_JudeViewInit();
}

void 	JudeDrawText(word colour, byte indent, byte mwidth, byte docont) {
//	IN	zregAwl		Colour
//	IN	zregAb2		Indent
//	IN	zregAb3		Max width
//	IN	zregBb0		Do cont char if opt

	zregAwl = colour;
	zregAb2 = indent;
	zregAb3 = mwidth;
	zregBb0 = docont;

	_JudeDrawText();
}

byte	JudeLogClrIsReverse(word colour) {
	_JudeLogClrIsReverse(colour);
	__asm__	("BCS %g", isreverse);

	return 0;

isreverse:

	return 1;
}