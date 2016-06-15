################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ESC_Code.c" \
"../Sources/Events.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ESC_Code.c \
../Sources/Events.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ESC_Code.o \
./Sources/Events.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ESC_Code.d \
./Sources/Events.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ESC_Code.o" \
"./Sources/Events.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ESC_Code.d" \
"./Sources/Events.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ESC_Code.o \
./Sources/Events.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ESC_Code.o: ../Sources/ESC_Code.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ESC_Code.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ESC_Code.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


