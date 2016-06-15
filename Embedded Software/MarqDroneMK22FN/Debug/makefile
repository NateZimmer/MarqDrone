################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Static_Code/System/subdir.mk
-include Static_Code/Peripherals/subdir.mk
-include Sources/Schedule/subdir.mk
-include Sources/Drivers/External/subdir.mk
-include Sources/Drivers/subdir.mk
-include Sources/Application/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: MarqDroneMK22FN.elf secondary-outputs

# Tool invocations
MarqDroneMK22FN.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C++ Linker'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -T "C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Project_Settings/Linker_Files/ProcessorExpert.ld" -Xlinker --gc-sections -L"C:/Users/Z/Google Drive/Workspace_KDS/MarqDroneMK22FN/Project_Settings/Linker_Files" -Wl,-Map,"MarqDroneMK22FN.map" -u _printf_float -specs=nano.specs -specs=nosys.specs -o "MarqDroneMK22FN.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS)$(S_UPPER_DEPS) MarqDroneMK22FN.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
