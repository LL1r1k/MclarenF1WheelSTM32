#include <OutLapPage.h>

OutLapPage::OutLapPage()
{
	BSP_LCD_SetFont(&FreeSans24pt7b);
	gear = new FlickerFreeText(210, 193, 2,(uint8_t*)"1", 1);

	BSP_LCD_SetFont(&FreeSans12pt7b);
	mix = new FlickerFreeText(300, 252, 1, (uint8_t*)"1", 1);
	ers = new FlickerFreeText(300, 280, 1, (uint8_t*)"1", 1);
	ersBar = new FlickerFreeText(260, 308, 1, (uint8_t*)"100", 3);
	speed = new FlickerFreeText(215, 225, 1, (uint8_t*)"100", 3);
	engineTemp = new FlickerFreeText(85, 232, 1, (uint8_t*)"1234", 4);
	oilTemp = new FlickerFreeText(350, 232, 1, (uint8_t*)"1234", 4);

	BSP_LCD_SetFont(&FreeSans18pt7b);
	deltaAhead = new FlickerFreeText(127, 64, 1, (uint8_t*)"+11.11", 6);
	deltaBehind = new FlickerFreeText(242, 64, 1, (uint8_t*)"+11.11", 6);
	tireFL = new FlickerFreeText(32, 40, 1, (uint8_t*)"111", 3);
	tireFR = new FlickerFreeText(388, 40, 1, (uint8_t*)"111", 3);
	tireRL = new FlickerFreeText(32, 92, 1, (uint8_t*)"111", 3);
	tireRR = new FlickerFreeText(388, 92, 1, (uint8_t*)"111", 3);
	brakeFL = new FlickerFreeText(32, 255, 1, (uint8_t*)"1111", 4);
	brakeFR = new FlickerFreeText(378, 255, 1, (uint8_t*)"1111", 4);
	brakeRL = new FlickerFreeText(32, 307, 1, (uint8_t*)"1111", 4);
	brakeRR = new FlickerFreeText(378, 307, 1, (uint8_t*)"1111", 4);
}

void OutLapPage::Static(Telemetry telemetry)
{
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_FillRect(0, 125, BSP_LCD_GetXSize(), 75);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

	BSP_LCD_SetFont(&FreeSans24pt7b);
	if((telemetry.flags >> 3) & 1)
	{
		StaticOut();
		lastMode = 0;

	}
	else
	{
		StaticCool();
		lastMode = 1;
	}

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

void OutLapPage::StaticOut()
{
	BSP_LCD_SetFont(&FreeSans24pt7b);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_Draw_Text((uint8_t*)"COOL", 25, 180, 1);
	BSP_LCD_Draw_Text((uint8_t*)"MODE", 315, 180, 1);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_Draw_Text((uint8_t*)"OUT", 50, 180, 1);
	BSP_LCD_Draw_Text((uint8_t*)"LAP", 340, 180, 1);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize()-125-75+5);
	BSP_LCD_FillRect(0, 200, BSP_LCD_GetXSize(), 120);

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&FreeSans9pt7b);
	BSP_LCD_Draw_Text((uint8_t*)"TYRE TEMPS", 5, 60, 1);
	BSP_LCD_Draw_Text((uint8_t*)"TYRE TEMPS", 360, 60, 1);
	BSP_LCD_Draw_Text((uint8_t*)"BRAKE TEMPS", 5, 275, 1);
	BSP_LCD_Draw_Text((uint8_t*)"BRAKE TEMPS", 350, 275, 1);

	BSP_LCD_Draw_Text((uint8_t*)"Ahead", 155, 30, 1);
	BSP_LCD_Draw_Text((uint8_t*)"Behind", 275, 30, 1);

	BSP_LCD_SetFont(&FreeSans12pt7b);
	BSP_LCD_Draw_Text((uint8_t*)"MIX MODE", 160, 252, 1);
	BSP_LCD_Draw_Text((uint8_t*)"ERS MODE", 160, 280, 1);
	BSP_LCD_Draw_Text((uint8_t*)"SOC", 190, 308, 1);
}

void OutLapPage::StaticCool()
{
	BSP_LCD_SetFont(&FreeSans24pt7b);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_Draw_Text((uint8_t*)"OUT", 50, 180, 1);
	BSP_LCD_Draw_Text((uint8_t*)"LAP", 340, 180, 1);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_Draw_Text((uint8_t*)"COOL", 25, 180, 1);
	BSP_LCD_Draw_Text((uint8_t*)"MODE", 315, 180, 1);

	BSP_LCD_SetTextColor(RC(0x06DF));
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize()-125-75+5);
	BSP_LCD_FillRect(0, 200, BSP_LCD_GetXSize(), 120);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(RC(0x06DF));

	BSP_LCD_SetFont(&FreeSans9pt7b);
	BSP_LCD_Draw_Text((uint8_t*)"Ahead", 155, 30, 1);
	BSP_LCD_Draw_Text((uint8_t*)"Behind", 275, 30, 1);

	BSP_LCD_SetFont(&FreeSans12pt7b);
	BSP_LCD_Draw_Text((uint8_t*)"MIX MODE", 160, 252, 1);
	BSP_LCD_Draw_Text((uint8_t*)"ERS MODE", 160, 280, 1);
	BSP_LCD_Draw_Text((uint8_t*)"SOC", 190, 308, 1);

	BSP_LCD_Draw_Text((uint8_t*)"ENG T", 10, 232, 1);
	BSP_LCD_Draw_Text((uint8_t*)"OIL T", 410, 232, 1);
}

void OutLapPage::Update(Telemetry telemetry, uint8_t redraw)
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	//Gear
	BSP_LCD_SetFont(&FreeSans24pt7b);
	if(telemetry.gear == -1)
		snprintf((char*)buffer, 2, "R");
	else if(telemetry.gear == 0)
		snprintf((char*)buffer, 2, "N");
	else
		snprintf((char*)buffer, 2, "%d", telemetry.gear);
	gear->Draw_Text(buffer, redraw);

	if((telemetry.flags >> 3) & 1)
	{
		if(lastMode != 0)
		{
			StaticOut();
		}
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		BSP_LCD_SetFont(&FreeSans12pt7b);
		snprintf((char*)buffer, 4, "%3d", telemetry.speed);
		speed->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 2, "%1d", telemetry.mix);
		mix->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 2, "%1d", telemetry.ers);
		ers->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 2, "%1d", telemetry.ers);
		ers->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 4, "%3d", telemetry.ersBar*100/255);
		ersBar->Draw_Text(buffer, redraw || (lastMode != 0));

		BSP_LCD_SetFont(&FreeSans18pt7b);
		snprintf((char*)buffer, 7, "%+03d.%02d", telemetry.deltaAheadSec, telemetry.deltaAheadMs < 0 ? -telemetry.deltaAheadMs : telemetry.deltaAheadMs);
		if(telemetry.deltaAheadMs < 0)
			for(uint8_t i =0;i<3;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaAhead->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 7, "%+03d.%02d", telemetry.deltaBehindSec, telemetry.deltaBehindMs < 0 ? -telemetry.deltaBehindMs : telemetry.deltaBehindMs);
		if(telemetry.deltaBehindMs < 0)
			for(uint8_t i =0;i<3;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaBehind->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 4, "%3d", telemetry.tireFL);
		tireFL->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 4, "%3d", telemetry.tireFR);
		tireFR->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 4, "%3d", telemetry.tireRL);
		tireRL->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 4, "%3d", telemetry.tireRR);
		tireRR->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 5, "%4d", telemetry.brakeFL);
		brakeFL->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 5, "%4d", telemetry.brakeFR);
		brakeFR->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 5, "%4d", telemetry.brakeRL);
		brakeRL->Draw_Text(buffer, redraw || (lastMode != 0));
		snprintf((char*)buffer, 5, "%4d", telemetry.brakeRR);
		brakeRR->Draw_Text(buffer, redraw || (lastMode != 0));

		lastMode = 0;
	}
	else
	{
		if(lastMode != 1)
		{
			StaticCool();
		}
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(RC(0x06DF));
		BSP_LCD_SetFont(&FreeSans12pt7b);
		snprintf((char*)buffer, 4, "%3d", telemetry.speed);
		speed->Draw_Text(buffer, redraw || (lastMode != 1));

		snprintf((char*)buffer, 2, "%1d", telemetry.mix);
		mix->Draw_Text(buffer, redraw || (lastMode != 1));

		snprintf((char*)buffer, 2, "%1d", telemetry.ers);
		ers->Draw_Text(buffer, redraw || (lastMode != 1));

		snprintf((char*)buffer, 2, "%1d", telemetry.ers);
		ers->Draw_Text(buffer, redraw || (lastMode != 1));

		snprintf((char*)buffer, 4, "%3d", telemetry.ersBar*100/255);
		ersBar->Draw_Text(buffer, redraw || (lastMode != 1));

		snprintf((char*)buffer, 5, "%4d", telemetry.engineTemp);
		engineTemp->Draw_Text(buffer, redraw | (lastMode != 0));
		snprintf((char*)buffer, 5, "%4d", telemetry.oilTemp);
		oilTemp->Draw_Text(buffer, redraw || (lastMode != 0));

		BSP_LCD_SetFont(&FreeSans18pt7b);
		snprintf((char*)buffer, 7, "%+3d.%02d", telemetry.deltaAheadSec, telemetry.deltaAheadMs < 0 ? -telemetry.deltaAheadMs : telemetry.deltaAheadMs);
		if(telemetry.deltaAheadMs < 0)
			for(uint8_t i =0;i<3;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaAhead->Draw_Text(buffer, redraw || (lastMode != 0));

		snprintf((char*)buffer, 7, "%+3d.%02d", telemetry.deltaBehindSec, telemetry.deltaBehindMs < 0 ? -telemetry.deltaBehindMs : telemetry.deltaBehindMs);
		if(telemetry.deltaBehindMs < 0)
			for(uint8_t i =0;i<3;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaBehind->Draw_Text(buffer, redraw || (lastMode != 0));

		lastMode = 1;
	}

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
}

OutLapPage::~OutLapPage()
{
	delete gear;
	delete mix;
	delete ers;
	delete ersBar;
	delete speed;
	delete deltaAhead;
	delete deltaBehind;
	delete tireFL;
	delete tireFR;
	delete tireRL;
	delete tireRR;
	delete brakeFL;
	delete brakeFR;
	delete brakeRL;
	delete brakeRR;
	delete engineTemp;
	delete oilTemp;
}
