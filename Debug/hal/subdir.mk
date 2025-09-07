################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/BUZ_prog.c \
../hal/CLCD_program.c \
../hal/DCMOTOR_program.c \
../hal/DT11_prog.c \
../hal/IR_prog.c \
../hal/KPD_prog.c \
../hal/LDR_prog.c \
../hal/LED_prog.c \
../hal/MQ2_prog.c \
../hal/PIR_prog.c \
../hal/soil\ moisture_program.c 

OBJS += \
./hal/BUZ_prog.o \
./hal/CLCD_program.o \
./hal/DCMOTOR_program.o \
./hal/DT11_prog.o \
./hal/IR_prog.o \
./hal/KPD_prog.o \
./hal/LDR_prog.o \
./hal/LED_prog.o \
./hal/MQ2_prog.o \
./hal/PIR_prog.o \
./hal/soil\ moisture_program.o 

C_DEPS += \
./hal/BUZ_prog.d \
./hal/CLCD_program.d \
./hal/DCMOTOR_program.d \
./hal/DT11_prog.d \
./hal/IR_prog.d \
./hal/KPD_prog.d \
./hal/LDR_prog.d \
./hal/LED_prog.d \
./hal/MQ2_prog.d \
./hal/PIR_prog.d \
./hal/soil\ moisture_program.d 


# Each subdirectory must supply rules for building sources it contributes
hal/%.o: ../hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal/soil\ moisture_program.o: ../hal/soil\ moisture_program.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"hal/soil moisture_program.d" -MT"hal/soil\ moisture_program.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


