################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC_prog.c \
../MCAL/DIO_program.c \
../MCAL/EEPROM_programe.c \
../MCAL/TWI_prog.c 

OBJS += \
./MCAL/ADC_prog.o \
./MCAL/DIO_program.o \
./MCAL/EEPROM_programe.o \
./MCAL/TWI_prog.o 

C_DEPS += \
./MCAL/ADC_prog.d \
./MCAL/DIO_program.d \
./MCAL/EEPROM_programe.d \
./MCAL/TWI_prog.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


