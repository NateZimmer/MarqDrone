################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Application/Commands.c \
../Sources/Application/Flight.c \
../Sources/Application/ICL.c \
../Sources/Application/ICL_Test.c \
../Sources/Application/RF.c \
../Sources/Application/Saved_Settings.c \
../Sources/Application/USB.c 

OBJS += \
./Sources/Application/Commands.o \
./Sources/Application/Flight.o \
./Sources/Application/ICL.o \
./Sources/Application/ICL_Test.o \
./Sources/Application/RF.o \
./Sources/Application/Saved_Settings.o \
./Sources/Application/USB.o 

C_DEPS += \
./Sources/Application/Commands.d \
./Sources/Application/Flight.d \
./Sources/Application/ICL.d \
./Sources/Application/ICL_Test.d \
./Sources/Application/RF.d \
./Sources/Application/Saved_Settings.d \
./Sources/Application/USB.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Application/%.o: ../Sources/Application/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/System" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Generated_Code" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


