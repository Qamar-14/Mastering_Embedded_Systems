################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32F103C_Drivers/LCD_DRIVER/lcd.c 

OBJS += \
./Src/STM32F103C_Drivers/LCD_DRIVER/lcd.o 

C_DEPS += \
./Src/STM32F103C_Drivers/LCD_DRIVER/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32F103C_Drivers/LCD_DRIVER/lcd.o: ../Src/STM32F103C_Drivers/LCD_DRIVER/lcd.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/STM32F103C_Drivers/LCD_DRIVER/lcd.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

