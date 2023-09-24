################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.c 

OBJS += \
./Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.o 

C_DEPS += \
./Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.o: ../Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

