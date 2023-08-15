################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.c 

OBJS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.o 

C_DEPS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.o: ../Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"C:/Users/noore/STM32CubeIDE/workspace_1.4.0/stm32/Src/STM32F103C_Drivers/MCAL_Drivers" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/usart.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

