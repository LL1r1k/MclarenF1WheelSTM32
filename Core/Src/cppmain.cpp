#include "cppmain.h"
#include "ws2812.h"
#include "LCDTelemetry.h"

bool running = true;

uint8_t button_buf[2];
uint8_t button_buf2[2];
uint32_t ADC_BUF[5] = {0,};

extern ADC_HandleTypeDef hadc1;
extern I2C_HandleTypeDef hi2c1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
volatile uint8_t error = 0;
volatile uint8_t first = 1;

Telemetry telemetry = {0,};

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){

}

volatile uint32_t lastTick = 0;
volatile uint16_t count2 = 0;
volatile uint16_t count = 0;
volatile uint16_t i2cError = 0;
volatile uint32_t lastTick2 = 0;
volatile uint32_t value = 0;
volatile uint32_t value2 = 0;
volatile uint8_t lastState = 0;
volatile uint8_t listening = 0;

void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(error == 1)
		HAL_I2C_EnableListen_IT(&hi2c1);
	else
	{
		value = HAL_GetTick() - lastTick;
		lastTick = HAL_GetTick();
		count++;
	}
	error = 0;
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
	if(TransferDirection==I2C_DIRECTION_TRANSMIT)
	{
		first = 3;
		HAL_I2C_Slave_Seq_Receive_DMA(hi2c, (uint8_t*)&telemetry, sizeof(telemetry), I2C_NEXT_FRAME);
	}
	else
		HAL_I2C_Slave_Seq_Transmit_DMA(hi2c, (uint8_t*)&telemetry, sizeof(telemetry), I2C_NEXT_FRAME);
}

const int8_t increment[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(first == 1)
	{
		first = 2;
		HAL_I2C_Master_Receive_DMA(&hi2c1, (uint16_t)(0x21<<1), button_buf2, 2);
	}
	else if(first == 2)
	{
		first = 0;
		uint8_t state = button_buf2[1] & 0b11;
		if(state != lastState)
		{
			count += increment[state | (lastState << 2)];
			lastState = state;
		}

		//HAL_I2C_EnableListen_IT(&hi2c1);
		value2 = HAL_GetTick() - lastTick2;
		lastTick2 = HAL_GetTick();
		count2++;
	}
}

void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
	error = 1;
	if(first == 1 || first == 2)
	{
		i2cError++;
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	HAL_TIM_PWM_Stop_DMA(htim, TIM_CHANNEL_1);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim3)
	{
		//HAL_I2C_DisableListen_IT(&hi2c1);
		first = 1;
		listening++;
		if(listening >= 10)
		{
			if(listening == 10)
				HAL_I2C_DisableListen_IT(&hi2c1);
			HAL_I2C_Master_Receive_DMA(&hi2c1, (uint16_t)(0x20<<1), button_buf, 2);
		}

	}else if (htim == &htim4)
	{
		listening = 0;
		HAL_I2C_EnableListen_IT(&hi2c1);
	}

}

void cppmain() {
	button_buf[0] = 0xff;
	button_buf[1] = 0xff;
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(0x20<<1), button_buf, 2, 100);
	HAL_I2C_Master_Transmit(&hi2c1, (uint16_t)(0x21<<1), button_buf, 2, 100);

	ws2812_init();
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_ADC_Start_DMA(&hadc1, ADC_BUF, 5);

	BSP_LCD_Init();

	LCDTelemetry lcdTelemetry = LCDTelemetry();
	while(running){
		//snprintf(trans_str, 63, "ADC %d %d %d %d %d\n", (uint16_t)ADC_BUF[0], (uint16_t)ADC_BUF[1], (uint16_t)ADC_BUF[2], (uint16_t)ADC_BUF[3], (uint16_t)ADC_BUF[4]);

		telemetry.speed = i2cError;
		telemetry.brakeFL = count;
		telemetry.brakeRL = count2;
		telemetry.brakeFR = value;
		telemetry.brakeRR = value2;

		telemetry.flags = 8;

		telemetry.tireFL = button_buf[0];
		telemetry.tireFR = button_buf2[0];
		telemetry.tireRL = button_buf[1];
		telemetry.tireRR = button_buf2[1];

		lcdTelemetry.Update(telemetry);
		ws1212_setup(telemetry);
	}

}





