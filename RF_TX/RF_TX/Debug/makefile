################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include example/src/subdir.mk
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
all: RF_TX.axf

# Tool invocations
RF_TX.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\Vatsal Makani\Desktop\FALL 2019\CMPE 245\Project\lpc_chip_175x_6x\Debug" -L"C:\Users\Vatsal Makani\Desktop\FALL 2019\CMPE 245\Project\lpc_board_nxp_lpcxpresso_1769\Debug" -Xlinker -Map="RF_TX.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "RF_TX_Debug.ld" -o "RF_TX.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) RF_TX.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "RF_TX.axf"; # arm-none-eabi-objcopy -v -O binary "RF_TX.axf" "RF_TX.bin" ; # checksum -p LPC1769 -d "RF_TX.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
