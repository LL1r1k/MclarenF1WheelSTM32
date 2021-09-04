#include <FlickerFreeText.h>

FlickerFreeText::FlickerFreeText(uint16_t X, uint16_t Y, uint8_t Size, uint8_t* sample, uint8_t len)
{
	this->Size = Size;
	this->X = X;
	this->Y = Y;
	this->sample = sample;
	this->len = len;

	uint8_t* tmpText = sample;
	GFXglyph* glyph;
	GFXfont* font = BSP_LCD_GetFont();

	this->oldText = new uint8_t[len+1];
	this->chars = new FlickerFreeChar*[len];
	for(uint8_t i=0;i<len;i++)
	{
		glyph = &(font->glyph[(*tmpText++-' ')]);
		this->chars[i] = new FlickerFreeChar(X, Y, Size);
		this->oldText[i] = 0;
		X += glyph->xAdvance * Size;
	}

}
FlickerFreeText::~FlickerFreeText()
{
	for(uint8_t i=0;i<len;i++)
		delete this->chars[i];
	delete[] this->chars;
	delete[] this->oldText;
}

void  FlickerFreeText::Draw_Text(uint8_t* Text, uint8_t redraw)
{
	uint8_t idx = 0;
    while (Text[idx]) {
    	if(this->oldText[idx] != Text[idx] || redraw)
    	{
    		this->chars[idx]->Draw_Char(Text[idx]);
    	}
		idx++;
    }
    strcpy((char*)this->oldText, (const char*)Text);
}
