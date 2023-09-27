################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.c 

OBJS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.o 

C_DEPS += \
./Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.o: ../Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"C:/Users/qamar/OneDrive/Desktop/Mastering_Embedded_Systems/Unit8(MCU_Interfacing)/SPI Driver/STM32CubeIDE Code/Src/STM32F103C_Drivers" -I"C:/Users/qamar/OneDrive/Desktop/Mastering_Embedded_Systems/Unit8(MCU_Interfacing)/SPI Driver/STM32CubeIDE Code/Src/STM32F103C_Drivers/MCAL_Drivers" -I"C:/Users/qamar/OneDrive/Desktop/Mastering_Embedded_Systems/Unit8(MCU_Interfacing)/SPI Driver/STM32CubeIDE Code/Src/STM32F103C_Drivers/HAL_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/i2c.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

