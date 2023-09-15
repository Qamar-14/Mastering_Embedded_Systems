################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/USART_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/SPI_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/RCC_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/I2C_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/GPIO_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/MCAL_Drivers/EXTI_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/HAL_Drivers/LCD_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/subdir.mk
-include Src/STM32F103C_Drivers/HAL_Drivers/I2C_EEPROM_SLAVE/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32_DRIVERS.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32_DRIVERS.list \

OBJCOPY_BIN += \
STM32_DRIVERS.bin \


# All Target
all: STM32_DRIVERS.axf secondary-outputs

# Tool invocations
STM32_DRIVERS.axf: $(OBJS) $(USER_OBJS) C:\Users\qamar\STM32CubeIDE\workspace_1.4.0\STM32_DRIVERS\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "STM32_DRIVERS.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\qamar\STM32CubeIDE\workspace_1.4.0\STM32_DRIVERS\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32_DRIVERS.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32_DRIVERS.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32_DRIVERS.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32_DRIVERS.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32_DRIVERS.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
