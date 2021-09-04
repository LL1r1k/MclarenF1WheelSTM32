#ifndef INC_WS2812_H_
#define INC_WS2812_H_

#include "stm32f1xx_hal.h"
#include "telemetry_defs.h"
#include <cppmain.h>

struct RGB
{
	uint8_t R,G,B;
};

#define DELAY_LEN 50
#define LED_COUNT 21
#define ARRAY_LEN (DELAY_LEN + LED_COUNT*24)
#define HIGH 60
#define LOW 30

void ws1212_setup(Telemetry telemetry);
void ws2812_init(void);
void ws2812_setLED(int LEDnum, int Red, int Green, int Blue);

#endif /* INC_WS2812_H_ */
