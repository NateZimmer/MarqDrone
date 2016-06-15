################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Drivers/ADC.c \
../Sources/Drivers/GPIO.c \
../Sources/Drivers/LED_PWM.c \
../Sources/Drivers/PWM.c \
../Sources/Drivers/Remote.c \
../Sources/Drivers/SPI.c \
../Sources/Drivers/Timer.c \
../Sources/Drivers/USB_Echo.c 

OBJS += \
./Sources/Drivers/ADC.o \
./Sources/Drivers/GPIO.o \
./Sources/Drivers/LED_PWM.o \
./Sources/Drivers/PWM.o \
./Sources/Drivers/Remote.o \
./Sources/Drivers/SPI.o \
./Sources/Drivers/Timer.o \
./Sources/Drivers/USB_Echo.o 

C_DEPS += \
./Sources/Drivers/ADC.d \
./Sources/Drivers/GPIO.d \
./Sources/Drivers/LED_PWM.d \
./Sources/Drivers/PWM.d \
./Sources/Drivers/Remote.d \
./Sources/Drivers/SPI.d \
./Sources/Drivers/Timer.d \
./Sources/Drivers/USB_Echo.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/%.o: ../Sources/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/IO_Map" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


