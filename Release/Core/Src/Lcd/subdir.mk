################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lcd/ili9488.c \
../Core/Src/Lcd/lcdts_io_gpio8.c \
../Core/Src/Lcd/stm32_adafruit_lcd.c \
../Core/Src/Lcd/stm32_adafruit_ts.c 

C_DEPS += \
./Core/Src/Lcd/ili9488.d \
./Core/Src/Lcd/lcdts_io_gpio8.d \
./Core/Src/Lcd/stm32_adafruit_lcd.d \
./Core/Src/Lcd/stm32_adafruit_ts.d 

OBJS += \
./Core/Src/Lcd/ili9488.o \
./Core/Src/Lcd/lcdts_io_gpio8.o \
./Core/Src/Lcd/stm32_adafruit_lcd.o \
./Core/Src/Lcd/stm32_adafruit_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lcd/%.o: ../Core/Src/Lcd/%.c Core/Src/Lcd/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/Src/Lcd -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

