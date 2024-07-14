################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Main/Src/drive_speed_ctrl.c \
../Main/Src/init.c \
../Main/Src/motor.c 

OBJS += \
./Main/Src/drive_speed_ctrl.o \
./Main/Src/init.o \
./Main/Src/motor.o 

C_DEPS += \
./Main/Src/drive_speed_ctrl.d \
./Main/Src/init.d \
./Main/Src/motor.d 


# Each subdirectory must supply rules for building sources it contributes
Main/Src/%.o Main/Src/%.su Main/Src/%.cyclo: ../Main/Src/%.c Main/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32F411xE -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DEXTERNAL_CLOCK_VALUE=12288000 -DHSI_VALUE=16000000 -DLSI_VALUE=32000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=1 -DDATA_CACHE_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/Users/j93es/workspace/c/lottery-wheel/lottery-wheel/External Library/Inc" -I"/Users/j93es/workspace/c/lottery-wheel/lottery-wheel/Main/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Main-2f-Src

clean-Main-2f-Src:
	-$(RM) ./Main/Src/drive_speed_ctrl.cyclo ./Main/Src/drive_speed_ctrl.d ./Main/Src/drive_speed_ctrl.o ./Main/Src/drive_speed_ctrl.su ./Main/Src/init.cyclo ./Main/Src/init.d ./Main/Src/init.o ./Main/Src/init.su ./Main/Src/motor.cyclo ./Main/Src/motor.d ./Main/Src/motor.o ./Main/Src/motor.su

.PHONY: clean-Main-2f-Src
