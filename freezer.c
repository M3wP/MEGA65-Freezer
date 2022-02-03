#include	"jude.h"
#include 	"freezer_ui.h"
#include 	"freezer.h"

void	main(void) {
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