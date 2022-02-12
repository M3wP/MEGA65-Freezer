#include	"jude.h"
#include 	"freezer_ui.h"
#include 	"freezer.h"
#include	"m65_mem.h"

void	main(void) {
		karlFarPtr_t	modulep = {
			NEARTOFARPTRREC(mod_freeze_app)};
		karlFarPtr_t	viewp = {
			NEARTOFARPTRREC(vew_freeze_view)};

		mega65_save_zp();

		KarlInit();
		JudeInit();

		KarlModAttach(&modulep);
		JudeViewInit(&viewp);

		JudeMain();
}