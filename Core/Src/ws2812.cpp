#include <ws2812.h>
#include <math.h>

uint16_t BUF_DMA [ARRAY_LEN] = {0};
uint8_t LED_Data[LED_COUNT][4];
extern TIM_HandleTypeDef htim2;

void ws2812_setLED(int LEDnum, int Red, int Green, int Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

void ws2812_init(void)
{
  for(uint16_t i=0;i<ARRAY_LEN;i++)
	  BUF_DMA[i] = 0;
}

void ws1212_setup(Telemetry telemetry)
{
	uint8_t brightness = 30;
	for(uint8_t i=0;i<LED_COUNT;i+=5)
	{
		int16_t tmp = telemetry.led[i/5];
		for(uint8_t j =i;j<i+5;j++)
		{
			uint8_t led = (tmp >> (3*(j-i))) & 7;
			if(led == 0)
				ws2812_setLED(j, 0, 0, 0);
			if(led == 0b100)
				ws2812_setLED(j, brightness, 0, 0);
			if(led == 0b010)
				ws2812_setLED(j, 0, brightness, 0);
			if(led == 0b001)
				ws2812_setLED(j, 0, 0, brightness);
			if(led == 0b110)
				ws2812_setLED(j, brightness, brightness, 0);
			if(led == 0b111)
				ws2812_setLED(j, brightness, brightness, brightness);
		}
	}

	uint32_t indx=0;
	uint32_t color;

	for (int i= 0; i<LED_COUNT; i++)
	{
		color = ((LED_Data[i][1]<<16) | (LED_Data[i][2]<<8) | (LED_Data[i][3]));
		for (int i=23; i>=0; i--)
		{
			if (color&(1<<i))
				BUF_DMA[indx] = HIGH;
			else
				BUF_DMA[indx] = LOW;
			indx++;
		}
	}
	for (int i=0; i<50; i++)
	{
		BUF_DMA[indx] = 0;
		indx++;
	}
	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)BUF_DMA, indx);
}
