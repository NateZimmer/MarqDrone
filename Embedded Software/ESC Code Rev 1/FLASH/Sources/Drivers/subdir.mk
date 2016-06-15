################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Drivers/ESC.c" \
"../Sources/Drivers/GPIO.c" \

C_SRCS += \
../Sources/Drivers/ESC.c \
../Sources/Drivers/GPIO.c \

OBJS += \
./Sources/Drivers/ESC.o \
./Sources/Drivers/GPIO.o \

C_DEPS += \
./Sources/Drivers/ESC.d \
./Sources/Drivers/GPIO.d \

OBJS_QUOTED += \
"./Sources/Drivers/ESC.o" \
"./Sources/Drivers/GPIO.o" \

C_DEPS_QUOTED += \
"./Sources/Drivers/ESC.d" \
"./Sources/Drivers/GPIO.d" \

OBJS_OS_FORMAT += \
./Sources/Drivers/ESC.o \
./Sources/Drivers/GPIO.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/ESC.o: ../Sources/Drivers/ESC.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/ESC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/ESC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Drivers/GPIO.o: ../Sources/Drivers/GPIO.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Drivers/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Drivers/GPIO.o"
	@echo 'Finished building: $<'
	@echo ' '


