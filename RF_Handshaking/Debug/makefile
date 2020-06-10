################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
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
all: RF_Handshaking.axf

# Tool invocations
RF_Handshaking.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Vatsal Makani\Desktop\FALL 2019\CMPE 245\Project\FreeRTOS_Library\Debug" -L"C:\Users\Vatsal Makani\Desktop\FALL 2019\CMPE 245\Project\CMSIS_CORE_LPC17xx\Debug" -Xlinker --gc-sections -Xlinker -Map=RF_Handshaking.map -mcpu=cortex-m3 -mthumb -T "Example16_Debug.ld" -o "RF_Handshaking.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) RF_Handshaking.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size RF_Handshaking.axf ; arm-none-eabi-objcopy -O ihex RF_Handshaking.axf RF_Handshaking.hex
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
