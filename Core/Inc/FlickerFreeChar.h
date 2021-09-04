#ifndef FLICKERFREECHAR_H_
#define FLICKERFREECHAR_H_

#include "cppmain.h"
#include <string.h>
#include "stm32_adafruit_lcd.h"

class FlickerFreeChar {
public:
	FlickerFreeChar(uint16_t X, uint16_t Y, uint8_t Size);
	void  Draw_Char(uint8_t Character);
private:
	uint16_t X;
	uint16_t Y;
	int8_t Size;
	uint8_t oldChar;
};

#endif /* FLICKERFREECHAR_H_ */
