#ifndef LCDTELEMETRY_H_
#define LCDTELEMETRY_H_

#include "FlickerFreeText.h"
#include "telemetry_defs.h"

#include "Fonts/fonts.h"

#include "MainPage.h"
#include "OutLapPage.h"

class LCDTelemetry {
public:
	LCDTelemetry();
	~LCDTelemetry();
	void Update(Telemetry telemetry);
	uint8_t getLasePage();

private:
	uint32_t lastBlueFlagTick;
	uint32_t lastYellowFlagTick;
	uint32_t lastChangeTick;

	uint8_t changes;
	uint8_t lastPage;

	FlickerFreeText* time;
	FlickerFreeText* valueChange;
	FlickerFreeText* gear;
	FlickerFreeText* speed;
	FlickerFreeText* rpm;
	FlickerFreeText* pitLimiterLabel;
	FlickerFreeText* clutchInLabel;

	MainPage* mainPage;
	OutLapPage* outLapPage;

	Telemetry oldTelemetry;
	uint8_t buffer[10];
};

#endif /* LCDTELEMETRY_H_ */
