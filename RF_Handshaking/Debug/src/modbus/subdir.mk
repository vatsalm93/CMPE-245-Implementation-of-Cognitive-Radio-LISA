################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/modbus/cr_startup_lpc175x_6x.c \
../src/modbus/crp.c \
../src/modbus/main.c \
../src/modbus/mb.c \
../src/modbus/mbcrc.c \
../src/modbus/mbfunccoils.c \
../src/modbus/mbfuncdisc.c \
../src/modbus/mbfuncholding.c \
../src/modbus/mbfuncinput.c \
../src/modbus/mbfuncother.c \
../src/modbus/mbrtu.c \
../src/modbus/mbutils.c \
../src/modbus/modbus.c \
../src/modbus/portevent.c \
../src/modbus/portserial.c \
../src/modbus/porttimer.c 

OBJS += \
./src/modbus/cr_startup_lpc175x_6x.o \
./src/modbus/crp.o \
./src/modbus/main.o \
./src/modbus/mb.o \
./src/modbus/mbcrc.o \
./src/modbus/mbfunccoils.o \
./src/modbus/mbfuncdisc.o \
./src/modbus/mbfuncholding.o \
./src/modbus/mbfuncinput.o \
./src/modbus/mbfuncother.o \
./src/modbus/mbrtu.o \
./src/modbus/mbutils.o \
./src/modbus/modbus.o \
./src/modbus/portevent.o \
./src/modbus/portserial.o \
./src/modbus/porttimer.o 

C_DEPS += \
./src/modbus/cr_startup_lpc175x_6x.d \
./src/modbus/crp.d \
./src/modbus/main.d \
./src/modbus/mb.d \
./src/modbus/mbcrc.d \
./src/modbus/mbfunccoils.d \
./src/modbus/mbfuncdisc.d \
./src/modbus/mbfuncholding.d \
./src/modbus/mbfuncinput.d \
./src/modbus/mbfuncother.d \
./src/modbus/mbrtu.d \
./src/modbus/mbutils.d \
./src/modbus/modbus.d \
./src/modbus/portevent.d \
./src/modbus/portserial.d \
./src/modbus/porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
src/modbus/%.o: ../src/modbus/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__CODE_RED -D__REDLIB__ -I"/Users/zzx/Documents/LPCXpresso_8.2.2/workspace/SimpleDemo" -I"/Users/zzx/Documents/LPCXpresso_8.2.2/workspace/CMSIS_CORE_LPC17xx/inc" -I"/Users/zzx/Documents/LPCXpresso_8.2.2/workspace/RF_Handshaking/include" -I"/Users/zzx/Documents/LPCXpresso_8.2.2/workspace/FreeRTOS_Library/include" -I"/Users/zzx/Documents/LPCXpresso_8.2.2/workspace/FreeRTOS_Library/portable" -O0 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


