################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/App/Commands.c \
../Sources/App/IMU_Data.c \
../Sources/App/Joystick.c \
../Sources/App/RF_Control.c \
../Sources/App/Saved_Settings.c \
../Sources/App/Scheduler.c \
../Sources/App/Task_List.c 

OBJS += \
./Sources/App/Commands.o \
./Sources/App/IMU_Data.o \
./Sources/App/Joystick.o \
./Sources/App/RF_Control.o \
./Sources/App/Saved_Settings.o \
./Sources/App/Scheduler.o \
./Sources/App/Task_List.o 

C_DEPS += \
./Sources/App/Commands.d \
./Sources/App/IMU_Data.d \
./Sources/App/Joystick.d \
./Sources/App/RF_Control.d \
./Sources/App/Saved_Settings.d \
./Sources/App/Scheduler.d \
./Sources/App/Task_List.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/App/%.o: ../Sources/App/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/IO_Map" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


