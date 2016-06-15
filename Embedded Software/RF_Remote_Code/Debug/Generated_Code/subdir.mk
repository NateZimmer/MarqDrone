################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ADC0.c \
../Generated_Code/CDC1.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/IFsh1.c \
../Generated_Code/IntFlashLdd1.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PTC.c \
../Generated_Code/PTD.c \
../Generated_Code/RNG1.c \
../Generated_Code/Rx1.c \
../Generated_Code/SPI0.c \
../Generated_Code/TPM1.c \
../Generated_Code/TPM2.c \
../Generated_Code/Tx1.c \
../Generated_Code/USB0.c \
../Generated_Code/USB1.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c \
../Generated_Code/usb_cdc.c \
../Generated_Code/usb_cdc_pstn.c \
../Generated_Code/usb_class.c \
../Generated_Code/usb_dci_kinetis.c \
../Generated_Code/usb_descriptor.c \
../Generated_Code/usb_driver.c \
../Generated_Code/usb_framework.c \
../Generated_Code/wdt_kinetis.c 

OBJS += \
./Generated_Code/ADC0.o \
./Generated_Code/CDC1.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/IFsh1.o \
./Generated_Code/IntFlashLdd1.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PTC.o \
./Generated_Code/PTD.o \
./Generated_Code/RNG1.o \
./Generated_Code/Rx1.o \
./Generated_Code/SPI0.o \
./Generated_Code/TPM1.o \
./Generated_Code/TPM2.o \
./Generated_Code/Tx1.o \
./Generated_Code/USB0.o \
./Generated_Code/USB1.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o \
./Generated_Code/usb_cdc.o \
./Generated_Code/usb_cdc_pstn.o \
./Generated_Code/usb_class.o \
./Generated_Code/usb_dci_kinetis.o \
./Generated_Code/usb_descriptor.o \
./Generated_Code/usb_driver.o \
./Generated_Code/usb_framework.o \
./Generated_Code/wdt_kinetis.o 

C_DEPS += \
./Generated_Code/ADC0.d \
./Generated_Code/CDC1.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/IFsh1.d \
./Generated_Code/IntFlashLdd1.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PTC.d \
./Generated_Code/PTD.d \
./Generated_Code/RNG1.d \
./Generated_Code/Rx1.d \
./Generated_Code/SPI0.d \
./Generated_Code/TPM1.d \
./Generated_Code/TPM2.d \
./Generated_Code/Tx1.d \
./Generated_Code/USB0.d \
./Generated_Code/USB1.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d \
./Generated_Code/usb_cdc.d \
./Generated_Code/usb_cdc_pstn.d \
./Generated_Code/usb_class.d \
./Generated_Code/usb_dci_kinetis.d \
./Generated_Code/usb_descriptor.d \
./Generated_Code/usb_driver.d \
./Generated_Code/usb_framework.d \
./Generated_Code/wdt_kinetis.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/PDD" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Static_Code/IO_Map" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Sources" -I"C:/Users/Z/Google Drive/Workspace_KDS/RF_Remote_Code/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


