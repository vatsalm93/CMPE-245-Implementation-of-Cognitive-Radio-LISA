################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPC1769_GPIO_Changed.axf

# Tool invocations
LPC1769_GPIO_Changed.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Vatsal Makani\Desktop\FALL 2019\CMPE 245\Project\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="LPC1769_GPIO_Changed.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "Hello_world_Debug.ld" -o "LPC1769_GPIO_Changed.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) LPC1769_GPIO_Changed.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC1769_GPIO_Changed.axf"; # arm-none-eabi-objcopy -v -O binary "LPC1769_GPIO_Changed.axf" "LPC1769_GPIO_Changed.bin" ; # checksum -p LPC1769 -d "LPC1769_GPIO_Changed.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
