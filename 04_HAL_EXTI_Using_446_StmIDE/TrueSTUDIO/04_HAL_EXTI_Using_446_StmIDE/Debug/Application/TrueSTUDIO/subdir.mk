################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
C:/Users/ilker/Atollic/TrueSTUDIO/STM32_workspace_9.3/04_HAL_EXTI_Using_446_StmIDE/TrueSTUDIO/startup_stm32f446xx.s 

C_SRCS += \
C:/Users/ilker/Atollic/TrueSTUDIO/STM32_workspace_9.3/04_HAL_EXTI_Using_446_StmIDE/TrueSTUDIO/syscalls.c 

OBJS += \
./Application/TrueSTUDIO/startup_stm32f446xx.o \
./Application/TrueSTUDIO/syscalls.o 

S_DEPS += \
./Application/TrueSTUDIO/startup_stm32f446xx.d 

C_DEPS += \
./Application/TrueSTUDIO/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Application/TrueSTUDIO/startup_stm32f446xx.o: C:/Users/ilker/Atollic/TrueSTUDIO/STM32_workspace_9.3/04_HAL_EXTI_Using_446_StmIDE/TrueSTUDIO/startup_stm32f446xx.s Application/TrueSTUDIO/subdir.mk
	arm-none-eabi-gcc -c -mcpu=cortex-m4 -g3 -c -Wa,-W -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"
Application/TrueSTUDIO/syscalls.o: C:/Users/ilker/Atollic/TrueSTUDIO/STM32_workspace_9.3/04_HAL_EXTI_Using_446_StmIDE/TrueSTUDIO/syscalls.c Application/TrueSTUDIO/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../../../Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

