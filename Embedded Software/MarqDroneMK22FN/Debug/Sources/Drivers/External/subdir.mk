################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Drivers/External/MPU9250.c \
../Sources/Drivers/External/Mag_Filter.c \
../Sources/Drivers/External/cc.c \
../Sources/Drivers/External/cc2500.c 

OBJS += \
./Sources/Drivers/External/MPU9250.o \
./Sources/Drivers/External/Mag_Filter.o \
./Sources/Drivers/External/cc.o \
./Sources/Drivers/External/cc2500.o 

C_DEPS += \
./Sources/Drivers/External/MPU9250.d \
./Sources/Drivers/External/Mag_Filter.d \
./Sources/Drivers/External/cc.d \
./Sources/Drivers/External/cc2500.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/Drivers/External/%.o: ../Sources/Drivers/External/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/System" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Generated_Code" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


