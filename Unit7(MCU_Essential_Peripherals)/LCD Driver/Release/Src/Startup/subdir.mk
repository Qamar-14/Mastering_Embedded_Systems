################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Src/Startup/startup_stm32f103c6tx.s 

OBJS += \
./Src/Startup/startup_stm32f103c6tx.o 

S_DEPS += \
./Src/Startup/startup_stm32f103c6tx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Startup/startup_stm32f103c6tx.o: ../Src/Startup/startup_stm32f103c6tx.s
	arm-none-eabi-gcc -mcpu=cortex-m3 -c -x assembler-with-cpp -MMD -MP -MF"Src/Startup/startup_stm32f103c6tx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

