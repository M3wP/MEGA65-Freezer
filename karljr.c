#include	"karljr.h"


void	KarlModAttach(karlFarPtr_t *module) {
	zreg0wl = module->loword;
	zreg0wh = module->hiword;
	_KarlModAttach();
}
