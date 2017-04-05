################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CortexM3/GNU/hal_assert.c 

S_UPPER_SRCS += \
../hal/CortexM3/GNU/hal.S \
../hal/CortexM3/GNU/hw_reg_access.S 

OBJS += \
./hal/CortexM3/GNU/hal.o \
./hal/CortexM3/GNU/hal_assert.o \
./hal/CortexM3/GNU/hw_reg_access.o 

C_DEPS += \
./hal/CortexM3/GNU/hal_assert.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Assembler'
	arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -specs=bare.specs  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

hal/CortexM3/GNU/%.o: ../hal/CortexM3/GNU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\CMSIS -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_ace -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers_config -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers_config\mss_ace -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\eecs373\project\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O1 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


