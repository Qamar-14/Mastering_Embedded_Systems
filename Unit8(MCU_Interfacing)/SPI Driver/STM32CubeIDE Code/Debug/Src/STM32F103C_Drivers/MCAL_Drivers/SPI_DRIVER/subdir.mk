################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.c 

OBJS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.o 

C_DEPS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.o: ../Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/spi.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

