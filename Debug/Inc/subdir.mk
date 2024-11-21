################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/SysTickDelay.c 

OBJS += \
./Inc/SysTickDelay.o 

C_DEPS += \
./Inc/SysTickDelay.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F446xx -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"C:/Users/user/STM32CubeIDE/workspace_1.14.0/FiniteStateMachine_TrafficLights/Drivers/CMSIS/Include" -I"C:/Users/user/STM32CubeIDE/workspace_1.14.0/FiniteStateMachine_TrafficLights/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/SysTickDelay.cyclo ./Inc/SysTickDelay.d ./Inc/SysTickDelay.o ./Inc/SysTickDelay.su

.PHONY: clean-Inc

