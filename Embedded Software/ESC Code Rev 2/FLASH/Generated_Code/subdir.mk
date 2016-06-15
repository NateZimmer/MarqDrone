################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/CMP0.c" \
"../Generated_Code/CS1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/PE_LDD.c" \
"../Generated_Code/PIT.c" \
"../Generated_Code/PTB.c" \
"../Generated_Code/PTD.c" \
"../Generated_Code/TPM0.c" \
"../Generated_Code/TPM1.c" \
"../Generated_Code/TPM2.c" \
"../Generated_Code/Vectors.c" \
"../Generated_Code/WAIT1.c" \

C_SRCS += \
../Generated_Code/CMP0.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PIT.c \
../Generated_Code/PTB.c \
../Generated_Code/PTD.c \
../Generated_Code/TPM0.c \
../Generated_Code/TPM1.c \
../Generated_Code/TPM2.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \

OBJS += \
./Generated_Code/CMP0.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PIT.o \
./Generated_Code/PTB.o \
./Generated_Code/PTD.o \
./Generated_Code/TPM0.o \
./Generated_Code/TPM1.o \
./Generated_Code/TPM2.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \

C_DEPS += \
./Generated_Code/CMP0.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PIT.d \
./Generated_Code/PTB.d \
./Generated_Code/PTD.d \
./Generated_Code/TPM0.d \
./Generated_Code/TPM1.d \
./Generated_Code/TPM2.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \

OBJS_QUOTED += \
"./Generated_Code/CMP0.o" \
"./Generated_Code/CS1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/PE_LDD.o" \
"./Generated_Code/PIT.o" \
"./Generated_Code/PTB.o" \
"./Generated_Code/PTD.o" \
"./Generated_Code/TPM0.o" \
"./Generated_Code/TPM1.o" \
"./Generated_Code/TPM2.o" \
"./Generated_Code/Vectors.o" \
"./Generated_Code/WAIT1.o" \

C_DEPS_QUOTED += \
"./Generated_Code/CMP0.d" \
"./Generated_Code/CS1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/PE_LDD.d" \
"./Generated_Code/PIT.d" \
"./Generated_Code/PTB.d" \
"./Generated_Code/PTD.d" \
"./Generated_Code/TPM0.d" \
"./Generated_Code/TPM1.d" \
"./Generated_Code/TPM2.d" \
"./Generated_Code/Vectors.d" \
"./Generated_Code/WAIT1.d" \

OBJS_OS_FORMAT += \
./Generated_Code/CMP0.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PIT.o \
./Generated_Code/PTB.o \
./Generated_Code/PTD.o \
./Generated_Code/TPM0.o \
./Generated_Code/TPM1.o \
./Generated_Code/TPM2.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/CMP0.o: ../Generated_Code/CMP0.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CMP0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CMP0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/CS1.o: ../Generated_Code/CS1.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/CS1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/CS1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Cpu.o: ../Generated_Code/Cpu.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Cpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Cpu.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PE_LDD.o: ../Generated_Code/PE_LDD.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PE_LDD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PE_LDD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PIT.o: ../Generated_Code/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PTB.o: ../Generated_Code/PTB.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PTB.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PTB.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/PTD.o: ../Generated_Code/PTD.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/PTD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/PTD.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TPM0.o: ../Generated_Code/TPM0.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TPM0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TPM0.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TPM1.o: ../Generated_Code/TPM1.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TPM1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TPM1.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/TPM2.o: ../Generated_Code/TPM2.c
	@echo 'Building file: $<'
	@echo 'Executing target #19 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/TPM2.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/TPM2.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/Vectors.o: ../Generated_Code/Vectors.c
	@echo 'Building file: $<'
	@echo 'Executing target #20 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/Vectors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/Vectors.o"
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/WAIT1.o: ../Generated_Code/WAIT1.c
	@echo 'Building file: $<'
	@echo 'Executing target #21 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Generated_Code/WAIT1.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Generated_Code/WAIT1.o"
	@echo 'Finished building: $<'
	@echo ' '


