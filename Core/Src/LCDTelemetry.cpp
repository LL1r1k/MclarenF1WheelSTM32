#include <LCDTelemetry.h>

LCDTelemetry::LCDTelemetry()
{
	oldTelemetry = {0,};
	changes = 0;
	lastPage = 0;

	BSP_LCD_SetFont(&FreeSans24pt7b);
	valueChange =  new FlickerFreeText(150, 190, 2, (uint8_t*)"M11", 3);
	gear = new FlickerFreeText(190,125,3,(uint8_t*)"1", 1);
	speed = new FlickerFreeText(147,250,2,(uint8_t*)"100", 3);
	rpm = new FlickerFreeText(110,250,2,(uint8_t*)"10000", 5);
	pitLimiterLabel = new FlickerFreeText(110, 308, 1, (uint8_t*)"PIT LIMITER", 11);
	clutchInLabel = new FlickerFreeText(120, 308, 1, (uint8_t*)"CLUTCH IN", 9);
	time = new FlickerFreeText(150, 212, 1, (uint8_t*)"11:11:11", 8);

	mainPage = new MainPage(&oldTelemetry);
	mainPage->Static();

	outLapPage = new OutLapPage();
}

void LCDTelemetry::Update(Telemetry telemetry)
{
	uint32_t curTick = HAL_GetTick();
	if(!((oldTelemetry.flags >> 5) & 1) && ((telemetry.flags >> 5) & 1))
		lastBlueFlagTick = curTick;

	if(!((oldTelemetry.flags >> 6) & 1) && ((telemetry.flags >> 6) & 1))
		lastYellowFlagTick = curTick;

	if(oldTelemetry.differential != telemetry.differential)
	{
		changes = (1 << 0);
		lastChangeTick = curTick;
	}

	if(oldTelemetry.mix != telemetry.mix)
	{
		changes = (1 << 1);
		lastChangeTick = curTick;
	}

	if(oldTelemetry.ers != telemetry.ers)
	{
		changes = (1 << 2);
		lastChangeTick = curTick;
	}

	if(oldTelemetry.brakeBias != telemetry.brakeBias)
	{
		changes = (1 << 3);
		lastChangeTick = curTick;
	}
	if((telemetry.flags >> 9) & 1) //Idle
	{
		if(lastPage != 9)
		{
			BSP_LCD_Clear(LCD_COLOR_BLACK);
			BSP_LCD_SetTextColor(RC(0xFCA0));
			BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 70);
			BSP_LCD_SetFont(&MokiLean18pt7b);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_Draw_Text((uint8_t*)"Mclaren", 135, 50, 1);
		}
		BSP_LCD_SetFont(&FreeSans24pt7b);
		snprintf((char*)buffer, 9,"%02d:%02d:%02d", telemetry.curHours, telemetry.curMins, telemetry.curSecs);
		time->Draw_Text(buffer, lastPage != 9);

		lastPage = 9;
	}
	else if(((telemetry.flags >> 5) & 1) && (curTick - lastBlueFlagTick <= 1000)) //BlueFlag
	{
		if(lastPage != 4)
		{
			BSP_LCD_Clear(LCD_COLOR_BLUE);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetFont(&FreeSans24pt7b);
			BSP_LCD_Draw_Text((uint8_t*)"Blue Flag", 45, 190, 2);
			lastPage = 4;
		}

	}
	else if(((telemetry.flags >> 6) & 1) && (curTick - lastYellowFlagTick <= 1000)) //YellowFlag
	{
		if(lastPage != 5)
		{
			BSP_LCD_Clear(LCD_COLOR_YELLOW);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetFont(&FreeSans24pt7b);
			BSP_LCD_Draw_Text((uint8_t*)"Yellow Flag", 2, 190, 2);
			lastPage = 5;
		}
	}
	else if(changes != 0) //Changes
	{
		if(lastPage != 7)
		{
			BSP_LCD_Clear(LCD_COLOR_WHITE);
		}
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetFont(&FreeSans24pt7b);
		if((changes >> 0) & 1)
		{
			snprintf((char*)buffer, 4, "D%02d",telemetry.differential);
			valueChange->Draw_Text(buffer, lastPage != 7);
		}
		else if((changes >> 1) & 1)
		{
			snprintf((char*)buffer, 4, "M%02d",telemetry.mix);
			valueChange->Draw_Text(buffer, lastPage != 7);
		}
		else if((changes >> 2) & 1)
		{
			snprintf((char*)buffer, 4, "E%02d",telemetry.ers);
			valueChange->Draw_Text(buffer, lastPage != 7);
		}
		else if((changes >> 3) & 1)
		{
			snprintf((char*)buffer, 4, "B%02d",telemetry.brakeBias);
			valueChange->Draw_Text(buffer, lastPage != 7);
		}

		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

		lastPage = 7;
	}
	else if((telemetry.flags >> 8) & 1) //PitLimiter
	{
		if(lastPage != 6)
		{
			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			pitLimiterLabel->Draw_Text((uint8_t*)"PIT LIMITER", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_BLACK);

		}
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
		gear->Draw_Text(buffer, lastPage != 6);

		snprintf((char*)buffer, 4, "%3d", telemetry.speed);
		speed->Draw_Text(buffer, lastPage != 6);

		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);

		lastPage = 6;
	}
	else if((telemetry.flags >> 1) & 1) //LaunchMode
	{
		if(lastPage != 1)
		{
			BSP_LCD_Clear(LCD_COLOR_WHITE);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			clutchInLabel->Draw_Text((uint8_t*)"CLUTCH IN", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		}
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
		gear->Draw_Text(buffer, lastPage != 1);

		snprintf((char*)buffer, 6, "%5d", telemetry.rpm);
		rpm->Draw_Text(buffer, lastPage != 1);

		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
		lastPage = 1;

	}
	else if(((telemetry.flags >> 3) & 1) || ((telemetry.flags >> 4) & 1)) //outLapMode
	{
		if(lastPage != 2)
		{
			outLapPage->Static(telemetry);
			outLapPage->Update(telemetry, true);
			lastPage = 2;
		}
		else
			outLapPage->Update(telemetry);

	}
	else //MainPage
	{
		if(lastPage != 0)
		{
			mainPage->Static();
			mainPage->Update(telemetry, true);
			lastPage = 0;
		}
		else
			mainPage->Update(telemetry);
	}
	if(curTick - lastChangeTick > 2000)
		changes = 0;
	oldTelemetry = telemetry;
}

LCDTelemetry::~LCDTelemetry()
{
	delete time;
	delete valueChange;
	delete gear;
	delete speed;
	delete rpm;
	delete pitLimiterLabel;
	delete clutchInLabel;
	delete mainPage;
	delete outLapPage;
}

uint8_t LCDTelemetry::getLasePage()
{
	return lastPage;
}
