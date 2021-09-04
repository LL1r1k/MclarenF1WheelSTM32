#ifndef MAINPAGE_H_
#define MAINPAGE_H_

#include "FlickerFreeText.h"
#include "telemetry_defs.h"

class MainPage {
public:
	MainPage(Telemetry* oldTelemetry);
	~MainPage();
	void Static();
	void Update(Telemetry telemetry, uint8_t redraw = false);
private:
	void DrawBar(uint8_t value, uint8_t prevValue, uint16_t X,uint16_t Y, uint8_t Height, uint8_t Widht);

	FlickerFreeText* gear;
	FlickerFreeText* curLapTime;
	FlickerFreeText* deltaAhead;
	FlickerFreeText* mix;
	FlickerFreeText* ers;
	FlickerFreeText* fuel;
	FlickerFreeText* fuelDelta;
	FlickerFreeText* bestLap;
	FlickerFreeText* deltaBest;
	FlickerFreeText* tireFL;
	FlickerFreeText* tireFR;
	FlickerFreeText* tireRL;
	FlickerFreeText* tireRR;

	FlickerFreeText* safetyCar;

	FlickerFreeText* drsOn;

	FlickerFreeText* mixLabel;
	FlickerFreeText* leftLabel;
	FlickerFreeText* ersLabel;
	FlickerFreeText* posLabel;
	FlickerFreeText* fuelLabel;

	FlickerFreeText* lastLapTime;;

	uint32_t lastDRSTick;
	uint32_t lastEndOfLapTick;
	uint8_t endOfLapTriggered;
	uint8_t ERSValue;
	uint8_t FuelValue;

	uint8_t buffer[10];
	uint8_t lastMode;
	Telemetry* oldTelemetry;
};

#endif /* MAINPAGE_H_ */
