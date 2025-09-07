################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_program.c \
../EEROM_project.c \
../KPD_program.c \
../LCD_program.c \
../LED_program.c \
../TIMER_program.c \
../USART_prog.c \
../control.c \
../main.c \
../securtiy.c 

OBJS += \
./ADC_program.o \
./DIO_program.o \
./EEROM_project.o \
./KPD_program.o \
./LCD_program.o \
./LED_program.o \
./TIMER_program.o \
./USART_prog.o \
./control.o \
./main.o \
./securtiy.o 

C_DEPS += \
./ADC_program.d \
./DIO_program.d \
./EEROM_project.d \
./KPD_program.d \
./LCD_program.d \
./LED_program.d \
./TIMER_program.d \
./USART_prog.d \
./control.d \
./main.d \
./securtiy.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


