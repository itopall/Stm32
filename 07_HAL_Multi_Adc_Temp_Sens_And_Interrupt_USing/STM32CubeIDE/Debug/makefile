################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/subdir.mk
-include Application/Startup/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := 07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.list \

OBJCOPY_BIN += \
07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.bin \


# All Target
all: main-build

# Main-build Target
main-build: 07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.elf secondary-outputs

# Tool invocations
07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.elf: $(OBJS) $(USER_OBJS) C:\Users\ilker\Atollic\TrueSTUDIO\STM32_workspace_9.3\07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing\STM32CubeIDE\STM32F446RE_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\ilker\Atollic\TrueSTUDIO\STM32_workspace_9.3\07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing\STM32CubeIDE\STM32F446RE_FLASH.ld" --specs=nosys.specs -Wl,-Map="07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.list"
	@echo 'Finished building: $@'
	@echo ' '

07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SIZE_OUTPUT)$(OBJDUMP_LIST)$(EXECUTABLES)$(OBJS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)$(OBJCOPY_BIN) 07_HAL_Multi_Adc_Temp_Sens_And_Interrupt_USing.elf
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
