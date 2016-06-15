################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/External/cc.c \
../Sources/External/cc2500.c 

OBJS += \
./Sources/External/cc.o \
./Sources/External/cc2500.o 

C_DEPS += \
./Sources/External/cc.d \
./Sources/External/cc2500.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/External/%.o: ../Sources/External/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/IO_Map" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


