################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_program.c \
../LCD_program.c \
../LDR_program.c \
../LM35_program.c \
../MQ5_program.c \
../TIMER_program.c \
../USART_prog.c \
../main.c 

OBJS += \
./ADC_program.o \
./DIO_program.o \
./LCD_program.o \
./LDR_program.o \
./LM35_program.o \
./MQ5_program.o \
./TIMER_program.o \
./USART_prog.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DIO_program.d \
./LCD_program.d \
./LDR_program.d \
./LM35_program.d \
./MQ5_program.d \
./TIMER_program.d \
./USART_prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


