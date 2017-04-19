################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/mss_pdma/mss_pdma.c 

OBJS += \
./drivers/mss_pdma/mss_pdma.o 

C_DEPS += \
./drivers/mss_pdma/mss_pdma.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/mss_pdma/%.o: ../drivers/mss_pdma/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\CMSIS -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_ace -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers_config -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\drivers_config\mss_ace -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\Project\GIT\N64\N64_controller_iter4\N64_controller_iter_4\SoftConsole\N64_controller_iter_4_MSS_MSS_CM3_0\N64_controller_iter_4_MSS_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O1 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


