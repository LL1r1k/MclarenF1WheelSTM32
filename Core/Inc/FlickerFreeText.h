#ifndef FLICKERFREETEXT_H_
#define FLICKERFREETEXT_H_

#include "FlickerFreeChar.h"

class FlickerFreeText {
public:
	FlickerFreeText(uint16_t X, uint16_t Y, uint8_t Size, uint8_t* sample, uint8_t len);
	~FlickerFreeText();
	void Draw_Text(uint8_t* Text, uint8_t redraw);
private:
	uint16_t X;
	uint16_t Y;
	int8_t Size;
	uint8_t* sample;
	uint8_t len;
	FlickerFreeChar** chars;
	uint8_t* oldText;

};

#endif /* FLICKERFREETEXT_H_ */
