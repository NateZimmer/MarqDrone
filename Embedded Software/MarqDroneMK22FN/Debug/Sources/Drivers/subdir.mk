################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Drivers/ADC.c \
../Sources/Drivers/FC.c \
../Sources/Drivers/GPIO.c \
../Sources/Drivers/LED_PWM.c \
../Sources/Drivers/PWM.c \
../Sources/Drivers/SPI.c \
../Sources/Drivers/TPM0.c \
../Sources/Drivers/serial.c 

OBJS += \
./Sources/Drivers/ADC.o \
./Sources/Drivers/FC.o \
./Sources/Drivers/GPIO.o \
./Sources/Drivers/LED_PWM.o \
./Sources/Drivers/PWM.o \
./Sources/Drivers/SPI.o \
./Sources/Drivers/TPM0.o \
./Sources/Drivers/serial.o 

C_DEPS += \
./Sources/Drivers/ADC.d \
./Sources/Drivers/FC.d \
./Sources/Drivers/GPIO.d \
./Sources/Drivers/LED_PWM.d \
./Sources/Drivers/PWM.d \
./Sources/Drivers/SPI.d \
./Sources/Drivers/TPM0.d \
./Sources/Drivers/serial.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/%.o: ../Sources/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/System" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Generated_Code" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


