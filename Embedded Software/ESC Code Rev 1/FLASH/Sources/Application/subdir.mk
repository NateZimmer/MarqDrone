################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Application/Compare.c" \
"../Sources/Application/Timer_App.c" \

C_SRCS += \
../Sources/Application/Compare.c \
../Sources/Application/Timer_App.c \

OBJS += \
./Sources/Application/Compare.o \
./Sources/Application/Timer_App.o \

C_DEPS += \
./Sources/Application/Compare.d \
./Sources/Application/Timer_App.d \

OBJS_QUOTED += \
"./Sources/Application/Compare.o" \
"./Sources/Application/Timer_App.o" \

C_DEPS_QUOTED += \
"./Sources/Application/Compare.d" \
"./Sources/Application/Timer_App.d" \

OBJS_OS_FORMAT += \
./Sources/Application/Compare.o \
./Sources/Application/Timer_App.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/Compare.o: ../Sources/Application/Compare.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Compare.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Compare.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Application/Timer_App.o: ../Sources/Application/Timer_App.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Application/Timer_App.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Application/Timer_App.o"
	@echo 'Finished building: $<'
	@echo ' '


