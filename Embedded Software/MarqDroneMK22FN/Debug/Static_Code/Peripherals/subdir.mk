################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/Peripherals/ADC0_Init.c \
../Static_Code/Peripherals/FTM0_Init.c \
../Static_Code/Peripherals/FTM1_Init.c \
../Static_Code/Peripherals/FTM2_Init.c \
../Static_Code/Peripherals/FTM3_Init.c \
../Static_Code/Peripherals/PTC_Init.c \
../Static_Code/Peripherals/PTD_Init.c \
../Static_Code/Peripherals/SPI0_Init.c \
../Static_Code/Peripherals/SPI1_Init.c \
../Static_Code/Peripherals/UART0_Init.c \
../Static_Code/Peripherals/USB0_Init.c 

OBJS += \
./Static_Code/Peripherals/ADC0_Init.o \
./Static_Code/Peripherals/FTM0_Init.o \
./Static_Code/Peripherals/FTM1_Init.o \
./Static_Code/Peripherals/FTM2_Init.o \
./Static_Code/Peripherals/FTM3_Init.o \
./Static_Code/Peripherals/PTC_Init.o \
./Static_Code/Peripherals/PTD_Init.o \
./Static_Code/Peripherals/SPI0_Init.o \
./Static_Code/Peripherals/SPI1_Init.o \
./Static_Code/Peripherals/UART0_Init.o \
./Static_Code/Peripherals/USB0_Init.o 

C_DEPS += \
./Static_Code/Peripherals/ADC0_Init.d \
./Static_Code/Peripherals/FTM0_Init.d \
./Static_Code/Peripherals/FTM1_Init.d \
./Static_Code/Peripherals/FTM2_Init.d \
./Static_Code/Peripherals/FTM3_Init.d \
./Static_Code/Peripherals/PTC_Init.d \
./Static_Code/Peripherals/PTD_Init.d \
./Static_Code/Peripherals/SPI0_Init.d \
./Static_Code/Peripherals/SPI1_Init.d \
./Static_Code/Peripherals/UART0_Init.d \
./Static_Code/Peripherals/USB0_Init.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/Peripherals/%.o: ../Static_Code/Peripherals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/System" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/IO_Map" -I"C:\Freescale\KDS_3.0.0\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Generated_Code" -I"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Static_Code/Peripherals" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


