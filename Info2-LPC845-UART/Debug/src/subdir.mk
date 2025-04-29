################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../src/aeabi_romdiv_patch.s 

CPP_SRCS += \
../src/LPC845_CPP_R2052.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc84x.cpp 

C_SRCS += \
../src/crp.c \
../src/mtb.c 

OBJS += \
./src/LPC845_CPP_R2052.o \
./src/aeabi_romdiv_patch.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc84x.o \
./src/crp.o \
./src/mtb.o 

CPP_DEPS += \
./src/LPC845_CPP_R2052.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc84x.d 

C_DEPS += \
./src/crp.d \
./src/mtb.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\inc" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\LCD_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\UART0_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\TECLADO_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\GPIOF_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\UTILS\CALLBACK" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\TIMERSW_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\SYSTICK_Driver" -I"C:\Users\gusta\Dropbox\Facultad\LPC845 CL2020\LPC845_CPP_R2053_LCD\src\GPIO_Driver" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0PLUS -D__USE_ROMDIVIDE -D__LPC84X__ -g3 -mcpu=cortex-m0 -mthumb -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M0PLUS -D__MTB_BUFFER_SIZE=256 -D__USE_ROMDIVIDE -DCPP_USE_HEAP -D__LPC84X__ -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


