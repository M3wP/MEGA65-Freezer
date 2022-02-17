#include	<memory.h>
#include	<jude.h>

#include 	"freezer_ui.h"
#include 	"freezer.h"


void	action(void) {
		karlFarPtr_t	modulep = {
			NEARTOFARPTRREC(mod_freeze_app)};
		karlFarPtr_t	viewp = {
			NEARTOFARPTRREC(vew_freeze_view)};

		KarlInit();
		JudeInit();

		KarlModAttach(&modulep);
		JudeViewInit(&viewp);

		JudeMain();
}

void	main(void) {
		mega65_save_zp();
		action();
}