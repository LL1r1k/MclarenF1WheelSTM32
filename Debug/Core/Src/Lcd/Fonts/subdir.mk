################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Lcd/Fonts/FreeSans12pt7b.c \
../Core/Src/Lcd/Fonts/FreeSans18pt7b.c \
../Core/Src/Lcd/Fonts/FreeSans24pt7b.c \
../Core/Src/Lcd/Fonts/FreeSans9pt7b.c \
../Core/Src/Lcd/Fonts/MokiLean18pt7b.c 

C_DEPS += \
./Core/Src/Lcd/Fonts/FreeSans12pt7b.d \
./Core/Src/Lcd/Fonts/FreeSans18pt7b.d \
./Core/Src/Lcd/Fonts/FreeSans24pt7b.d \
./Core/Src/Lcd/Fonts/FreeSans9pt7b.d \
./Core/Src/Lcd/Fonts/MokiLean18pt7b.d 

OBJS += \
./Core/Src/Lcd/Fonts/FreeSans12pt7b.o \
./Core/Src/Lcd/Fonts/FreeSans18pt7b.o \
./Core/Src/Lcd/Fonts/FreeSans24pt7b.o \
./Core/Src/Lcd/Fonts/FreeSans9pt7b.o \
./Core/Src/Lcd/Fonts/MokiLean18pt7b.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Lcd/Fonts/%.o: ../Core/Src/Lcd/Fonts/%.c Core/Src/Lcd/Fonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/Src/Lcd -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

