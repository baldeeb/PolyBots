################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal/CortexM3/cortex_nvic.c 

OBJS += \
./hal/CortexM3/cortex_nvic.o 

C_DEPS += \
./hal/CortexM3/cortex_nvic.d 


# Each subdirectory must supply rules for building sources it contributes
hal/CortexM3/%.o: ../hal/CortexM3/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -DACTEL_STDIO_THRU_UART -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\CMSIS -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\CMSIS\startup_gcc -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_gpio -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_nvm\drivers\F2DSS_NVM -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_pdma -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_rtc\drivers\mss_rtc -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_spi -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_spi\drivers\mss_spi -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_timer -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_uart -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_watchdog -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_watchdog\drivers -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\drivers\mss_watchdog\drivers\mss_watchdog -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\hal -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\hal\CortexM3 -IN:\eecs373\project\pixyCam\pixyCam\SoftConsole\pixyCam_MSS_MSS_CM3_0\pixyCam_MSS_MSS_CM3_0_hw_platform\hal\CortexM3\GNU -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


