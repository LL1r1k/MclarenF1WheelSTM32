#include <FlickerFreeChar.h>

FlickerFreeChar::FlickerFreeChar(uint16_t X, uint16_t Y, uint8_t Size)
{
	this->Size= Size;
	this->X= X;
	this->Y= Y;
	this->oldChar = ' ';
}


void  FlickerFreeChar::Draw_Char(uint8_t Character)
{
	BSP_LCD_Draw_Char(Character, X, Y, Size,oldChar);
	oldChar = Character;
}
