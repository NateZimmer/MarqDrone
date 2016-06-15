################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/__arm_end.c" \
"../Project_Settings/Startup_Code/__arm_start.c" \

C_SRCS += \
../Project_Settings/Startup_Code/__arm_end.c \
../Project_Settings/Startup_Code/__arm_start.c \

OBJS += \
./Project_Settings/Startup_Code/__arm_end.o \
./Project_Settings/Startup_Code/__arm_start.o \

C_DEPS += \
./Project_Settings/Startup_Code/__arm_end.d \
./Project_Settings/Startup_Code/__arm_start.d \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/__arm_end.o" \
"./Project_Settings/Startup_Code/__arm_start.o" \

C_DEPS_QUOTED += \
"./Project_Settings/Startup_Code/__arm_end.d" \
"./Project_Settings/Startup_Code/__arm_start.d" \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/__arm_end.o \
./Project_Settings/Startup_Code/__arm_start.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/__arm_end.o: ../Project_Settings/Startup_Code/__arm_end.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Settings/Startup_Code/__arm_end.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Settings/Startup_Code/__arm_end.o"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/__arm_start.o: ../Project_Settings/Startup_Code/__arm_start.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Settings/Startup_Code/__arm_start.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Settings/Startup_Code/__arm_start.o"
	@echo 'Finished building: $<'
	@echo ' '


