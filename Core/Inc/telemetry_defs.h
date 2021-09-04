#ifndef TELEMETRY_DEFS_H_
#define TELEMETRY_DEFS_H_

#include "cppmain.h"

typedef struct{
	int16_t curHours;
	int16_t curMins;
	int16_t curSecs;
	int16_t gear;
	int16_t ersBar;
	int16_t fuelBar;
	int16_t mix;
	int16_t ers;
	int16_t fuel;
	int16_t fuelDelta;
	int16_t tireFL;
	int16_t tireFR;
	int16_t tireRL;
	int16_t tireRR;
	int16_t rpm;
	int16_t lapsRemains;
	int16_t position;
	int16_t brakeBias;
	int16_t speed;
	int16_t brakeFL;
	int16_t brakeFR;
	int16_t brakeRL;
	int16_t brakeRR;
	int16_t engineTemp;
	int16_t oilTemp;
	int16_t differential;
	int16_t curLapSec;
	int16_t curLapMs;
	int16_t bestLapSec;
	int16_t bestLapMs;
	int16_t lastLapSec;
	int16_t lastLapMs;
	int16_t deltaAheadSec;
	int16_t deltaAheadMs;
	int16_t deltaBehindSec;
	int16_t deltaBehindMs;
	int16_t deltaToBestSec;
	int16_t deltaToBestMs;
	int16_t safetyCarDeltaSec;
	int16_t safetyCarDeltaMs;
	int16_t flags;
	int16_t led[5];

} Telemetry;


#endif /* TELEMETRY_DEFS_H_ */
