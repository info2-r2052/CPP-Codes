################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/UTILS/CALLBACK/subdir.mk
-include src/UART0_Driver/subdir.mk
-include src/TIMERSW_Driver/subdir.mk
-include src/TECLADO_Driver/subdir.mk
-include src/SYSTICK_Driver/subdir.mk
-include src/GPIO_Driver/subdir.mk
-include src/GPIOF_Driver/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: LPC845_CPP_R2053_LCD.axf

# Tool invocations
LPC845_CPP_R2053_LCD.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -Xlinker -Map="LPC845_CPP_R2053_LCD.map" -Xlinker --cref -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0 -mthumb -T "LPC845_CPP_R2052_Debug.ld" -o "LPC845_CPP_R2053_LCD.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) LPC845_CPP_R2053_LCD.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "LPC845_CPP_R2053_LCD.axf"; # arm-none-eabi-objcopy -v -O binary "LPC845_CPP_R2053_LCD.axf" "LPC845_CPP_R2053_LCD.bin" ; # checksum -p LPC845 -d "LPC845_CPP_R2053_LCD.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
