#ifndef OUTLAPPAGE_H_
#define OUTLAPPAGE_H_

#include "cppmain.h"
#include "FlickerFreeText.h"
#include "telemetry_defs.h"

class OutLapPage {
public:
	OutLapPage();
	~OutLapPage();
	void Static(Telemetry telemetry);
	void Update(Telemetry telemetry, uint8_t redraw = false);
private:
	void StaticOut();
	void StaticCool();

	FlickerFreeText* gear;
	FlickerFreeText* mix;
	FlickerFreeText* ers;
	FlickerFreeText* ersBar;
	FlickerFreeText* speed;

	FlickerFreeText* deltaAhead;
	FlickerFreeText* deltaBehind;

	FlickerFreeText* tireFL;
	FlickerFreeText* tireFR;
	FlickerFreeText* tireRL;
	FlickerFreeText* tireRR;

	FlickerFreeText* brakeFL;
	FlickerFreeText* brakeFR;
	FlickerFreeText* brakeRL;
	FlickerFreeText* brakeRR;

	FlickerFreeText* engineTemp;
	FlickerFreeText* oilTemp;

	uint8_t buffer[10];
	uint8_t lastMode;
};

#endif /* OUTLAPPAGE_H_ */
