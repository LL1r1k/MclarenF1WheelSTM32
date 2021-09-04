#include <MainPage.h>

MainPage::MainPage(Telemetry* oldTelemetry)
{
	this->oldTelemetry = oldTelemetry;
	ERSValue = 0;
	FuelValue = 0;
	lastMode = 0;
	endOfLapTriggered = 0;

	lastDRSTick = 0;
	lastEndOfLapTick = 0;

	BSP_LCD_SetFont(&FreeSans24pt7b);
	gear = new FlickerFreeText(200,125,3,(uint8_t*)"1", 1);
	safetyCar = new FlickerFreeText(90, 308, 1, (uint8_t*)"SAFETY CAR", 10);

	BSP_LCD_SetFont(&FreeSans18pt7b);
	drsOn = new FlickerFreeText(180, 230, 1, (uint8_t*)"DRS ON", 6);
	curLapTime = new FlickerFreeText(15, 40, 1, (uint8_t*)"01:12.822", 9);
	deltaAhead = new FlickerFreeText(322, 40, 1, (uint8_t*)"+100.250", 8);
	tireFL = new FlickerFreeText(180, 210, 1, (uint8_t*)"100", 3);
	tireFR = new FlickerFreeText(260, 210, 1, (uint8_t*)"100", 3);
	tireRL = new FlickerFreeText(180, 250, 1, (uint8_t*)"100", 3);
	tireRR = new FlickerFreeText(260, 250, 1, (uint8_t*)"100", 3);

	BSP_LCD_SetFont(&FreeSans12pt7b);
	mix = new FlickerFreeText(118, 105, 1, (uint8_t*)"333", 3);
	ers = new FlickerFreeText(118, 140, 1, (uint8_t*)"333", 3);
	fuel = new FlickerFreeText(118, 175, 1, (uint8_t*)"110", 3);
	fuelDelta = new FlickerFreeText(105, 175, 1, (uint8_t*)"+1.10", 5);
	bestLap = new FlickerFreeText(340, 210, 1, (uint8_t*)"01:12.822", 9);
	lastLapTime = new FlickerFreeText(50, 235, 1, (uint8_t*)"01:12.822", 9);
	deltaBest = new FlickerFreeText(346, 245, 1, (uint8_t*)"+100.250", 8);
	mixLabel = new FlickerFreeText(40, 105, 1, (uint8_t*)"MIX", 3);
	leftLabel = new FlickerFreeText(40, 105, 1, (uint8_t*)"LEFT", 4);
	ersLabel = new FlickerFreeText(40, 140, 1, (uint8_t*)"ERS", 3);
	posLabel = new FlickerFreeText(40, 140, 1, (uint8_t*)"POS", 3);
	fuelLabel = new FlickerFreeText(40, 175, 1, (uint8_t*)"FUEL", 4);
}

void MainPage::Static()
{
	lastMode = 0;
	BSP_LCD_Clear(LCD_COLOR_BLACK);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_FillRect(30, 72, 2, 120);
	BSP_LCD_FillRect(30, 72, 140, 2);
	BSP_LCD_FillRect(170, 72, 2, 120);
	BSP_LCD_FillRect(30, 190 , 140, 2);
	BSP_LCD_FillRect(330, 175, 2, 90);
	BSP_LCD_FillRect(330, 175, 120, 2);
	BSP_LCD_FillRect(450, 175, 2, 90);
	BSP_LCD_FillRect(330, 263 , 120, 2);

	BSP_LCD_SetFont(&FreeSans12pt7b);
	mixLabel->Draw_Text((uint8_t*)"MIX", true);
	ersLabel->Draw_Text((uint8_t*)"ERS", true);
	fuelLabel->Draw_Text((uint8_t*)"FUEL", true);

}

void MainPage::Update(Telemetry telemetry, uint8_t redraw)
{
	uint32_t curTick = HAL_GetTick();
	if(redraw)
	{
		ERSValue = 0;
		FuelValue = 0;
	}

	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	//Gear
	BSP_LCD_SetFont(&FreeSans24pt7b);
	if(telemetry.gear == -1)
		snprintf((char*)buffer, 2, "R");
	else if(telemetry.gear == 0)
		snprintf((char*)buffer, 2, "N");
	else
		snprintf((char*)buffer, 2, "%d", telemetry.gear);
	gear->Draw_Text(buffer, redraw);

	//CurLap, DeltaAhead
	BSP_LCD_SetFont(&FreeSans18pt7b);
	snprintf((char*)buffer, 10, "%02d:%02d.%03d",telemetry.curLapSec / 60,telemetry.curLapSec % 60 ,telemetry.curLapMs);
	curLapTime->Draw_Text(buffer, redraw);

	if(!((oldTelemetry->flags >> 7) & 1) && ((telemetry.flags >> 7) & 1))
		lastDRSTick = curTick;

	if(((telemetry.flags >> 7) & 1) && (curTick - lastDRSTick <= 1000))	//DRS On
	{
		if(!((lastMode >> 7) & 1))
		{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			snprintf((char*)buffer, 4, "%3d",telemetry.tireFL);
			tireFL->Draw_Text(buffer, true);
			snprintf((char*)buffer, 4, "%3d",telemetry.tireFR);
			tireFR->Draw_Text(buffer, true);
			snprintf((char*)buffer, 4, "%3d",telemetry.tireRL);
			tireRL->Draw_Text(buffer, true);
			snprintf((char*)buffer, 4, "%3d",telemetry.tireRR);
			tireRR->Draw_Text(buffer, true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

			drsOn->Draw_Text((uint8_t*)"DRS ON", true);
		}

		lastMode |= (1 << 7);
	}
	else
	{
		if((lastMode >> 7) & 1)
		{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			drsOn->Draw_Text((uint8_t*)"      ", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}
		uint8_t modeRedraw = (lastMode >> 7) & 1;
		//Tires
		snprintf((char*)buffer, 4, "%3d",telemetry.tireFL);
		tireFL->Draw_Text(buffer, redraw | modeRedraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.tireFR);
		tireFR->Draw_Text(buffer, redraw | modeRedraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.tireRL);
		tireRL->Draw_Text(buffer, redraw | modeRedraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.tireRR);
		tireRR->Draw_Text(buffer, redraw | modeRedraw);
		lastMode &= ~(1 << 7);
	}

	if(!((oldTelemetry->flags >> 2) & 1) && ((telemetry.flags >> 2) & 1))
	{
		endOfLapTriggered = 1;
		lastEndOfLapTick = curTick;
	}

	BSP_LCD_SetFont(&FreeSans12pt7b);
	if(endOfLapTriggered)	//EndOfLap
	{
		if(!((lastMode >> 2) & 1))
		{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			mixLabel->Draw_Text((uint8_t*)"MIX", true);
			ersLabel->Draw_Text((uint8_t*)"ERS", true);
			fuel->Draw_Text((uint8_t*)"   ", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			leftLabel->Draw_Text((uint8_t*)"LEFT", true);
			posLabel->Draw_Text((uint8_t*)"POS", true);
		}
		snprintf((char*)buffer, 4, "%3d",telemetry.lapsRemains);
		mix->Draw_Text(buffer, redraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.position);
		ers->Draw_Text(buffer, redraw);

		int8_t tmpSign = telemetry.fuelDelta > 0 ? 1 : -1;
		telemetry.fuelDelta *= tmpSign;
		snprintf((char*)buffer, 6, "%+2d.%02d", telemetry.fuelDelta / 100, telemetry.fuelDelta % 100);
		if(buffer[0]=='+' && tmpSign == -1)
			buffer[0] = '-';
		fuelDelta->Draw_Text(buffer, redraw || (lastMode >> 2) & 1);

		snprintf((char*)buffer, 10, "%02d:%02d.%03d",telemetry.lastLapSec / 60,telemetry.lastLapSec % 60 ,telemetry.lastLapMs);
		lastLapTime->Draw_Text(buffer, redraw || !((lastMode >> 2) & 1));
		lastMode |= (1 << 2);
	}
	else
	{
		if((lastMode >> 2) & 1)
		{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			leftLabel->Draw_Text((uint8_t*)"LEFT", true);
			posLabel->Draw_Text((uint8_t*)"POS", true);
			fuelDelta->Draw_Text((uint8_t*)"     ", true);
			lastLapTime->Draw_Text((uint8_t*)"         ", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			mixLabel->Draw_Text((uint8_t*)"MIX", true);
			ersLabel->Draw_Text((uint8_t*)"ERS", true);
		}
		//MIX ERS FUEL
		snprintf((char*)buffer, 4, "%3d",telemetry.mix+1);
		mix->Draw_Text(buffer, redraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.ers);
		ers->Draw_Text(buffer, redraw);
		snprintf((char*)buffer, 4, "%3d",telemetry.fuel);
		fuel->Draw_Text(buffer, redraw || (lastMode >> 2) & 1);

		lastMode &= ~(1 << 2);
	}

	if((telemetry.flags >> 0) & 1)	//SafetyCar
	{
		if(!((lastMode >> 1) & 1))
		{
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_FillRect(330, 175, 2, 90);
			BSP_LCD_FillRect(330, 175, 120, 2);
			BSP_LCD_FillRect(450, 175, 2, 90);
			BSP_LCD_FillRect(330, 263 , 120, 2);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

			bestLap->Draw_Text((uint8_t*)"         ", redraw);
			deltaBest->Draw_Text((uint8_t*)"        ", redraw);

			BSP_LCD_FillRect(30, 268, BSP_LCD_GetXSize() - 59, 48);
			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_SetFont(&FreeSans24pt7b);
			safetyCar->Draw_Text((uint8_t*)"SAFETY CAR", true);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}

		BSP_LCD_SetFont(&FreeSans18pt7b);
		uint8_t redSafetyCarDelta = false;
		if(telemetry.safetyCarDeltaMs > 0)
		{
			if(oldTelemetry->safetyCarDeltaMs <= 0)
				redSafetyCarDelta = true;
			BSP_LCD_SetTextColor(LCD_COLOR_RED);
		}
		else if(telemetry.safetyCarDeltaMs < 0)
		{
			if(oldTelemetry->safetyCarDeltaMs >= 0)
				redSafetyCarDelta = true;
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		}
		else
		{
			if(oldTelemetry->safetyCarDeltaMs > 0 || oldTelemetry->safetyCarDeltaMs < 0)
				redSafetyCarDelta = true;
		}
		snprintf((char*)buffer, 9, "%+4d.%03d", telemetry.safetyCarDeltaSec, telemetry.safetyCarDeltaMs < 0 ? -telemetry.safetyCarDeltaMs : telemetry.safetyCarDeltaMs);
		if(telemetry.safetyCarDeltaMs < 0)
			for(uint8_t i =0;i<4;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaAhead->Draw_Text(buffer, redraw || redSafetyCarDelta);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

		lastMode |= (1 << 1);
	}
	else
	{
		if((lastMode >> 1) & 1)
		{
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
			BSP_LCD_FillRect(330, 175, 2, 90);
			BSP_LCD_FillRect(330, 175, 120, 2);
			BSP_LCD_FillRect(450, 175, 2, 90);
			BSP_LCD_FillRect(330, 263 , 120, 2);

			BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
			BSP_LCD_FillRect(30, 268, BSP_LCD_GetXSize() - 59, 48);
			BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
		}

		//BestLap
		snprintf((char*)buffer, 10, "%02d:%02d.%03d",telemetry.bestLapSec / 60,telemetry.bestLapSec % 60 ,telemetry.bestLapMs);
		bestLap->Draw_Text(buffer, redraw);

		uint8_t redrawDeltaToBest = false;
		if(telemetry.deltaToBestMs > 0)
		{
			if(oldTelemetry->deltaToBestMs <= 0)
				redrawDeltaToBest = true;
			BSP_LCD_SetTextColor(LCD_COLOR_RED);
		}
		else if(telemetry.deltaToBestMs < 0)
		{
			if(oldTelemetry->deltaToBestMs >= 0)
				redrawDeltaToBest = true;
			BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		}
		else
		{
			if(oldTelemetry->deltaToBestMs > 0 || oldTelemetry->deltaToBestMs < 0)
				redrawDeltaToBest = true;
		}
		snprintf((char*)buffer, 9, "%+4d.%03d", telemetry.deltaToBestSec, telemetry.deltaToBestMs < 0 ? -telemetry.deltaToBestMs : telemetry.deltaToBestMs);
		if(telemetry.deltaToBestMs < 0)
			for(uint8_t i =0;i<4;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaBest->Draw_Text(buffer, redraw || redrawDeltaToBest);
		BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

		BSP_LCD_SetFont(&FreeSans18pt7b);
		snprintf((char*)buffer, 9, "%+4d.%03d", telemetry.deltaAheadSec, telemetry.deltaAheadMs < 0 ? -telemetry.deltaAheadMs : telemetry.deltaAheadMs);
		if(telemetry.deltaAheadMs < 0)
			for(uint8_t i =0;i<4;i++)
				if(buffer[i]=='+')
				{
					buffer[i] = '-';
					break;
				}
		deltaAhead->Draw_Text(buffer, redraw || ((lastMode >> 1) & 1));

		lastMode &= ~(1 << 1);
	}

	if(curTick - lastEndOfLapTick > 8000)
		endOfLapTriggered = 0;

	//ERS & FUELBAR
	DrawBar(telemetry.ersBar,  ERSValue, 5, 60, 255, 18);
	DrawBar(telemetry.fuelBar, FuelValue, 458, 60, 255, 18);
}

MainPage::~MainPage()
{
	delete gear;
	delete curLapTime;
	delete deltaAhead;
	delete mix;
	delete ers;
	delete fuel;
	delete fuelDelta;
	delete bestLap;
	delete deltaBest;
	delete tireFL;
	delete tireFR;
	delete tireRL;
	delete tireRR;
	delete safetyCar;
	delete drsOn;
	delete mixLabel;
	delete leftLabel;
	delete ersLabel;
	delete posLabel;
	delete fuelLabel;
	delete lastLapTime;;
}

void MainPage::DrawBar(uint8_t value, uint8_t prevVal, uint16_t X, uint16_t Y, uint8_t Height, uint8_t Widht)
{
	if(value == prevVal)
		return;
	if(value > prevVal)
	{
		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		for(int16_t i = prevVal; i < value;i++)
			BSP_LCD_FillRect(X, Height+Y-i, Widht, 1);
	}
	else
	{
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		for(int16_t i = prevVal; i >= value;i--)
			BSP_LCD_FillRect(X, Height+Y-i, Widht, 1);
	}
	prevVal = value;
}
