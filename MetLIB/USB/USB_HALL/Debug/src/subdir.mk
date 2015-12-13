################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c \
../src/tm_stm32_buffer.c \
../src/tm_stm32_delay.c \
../src/tm_stm32_disco.c \
../src/tm_stm32_gpio.c \
../src/tm_stm32_rcc.c \
../src/tm_stm32_usb.c \
../src/tm_stm32_usb_device.c \
../src/tm_stm32_usb_device_cdc.c 

OBJS += \
./src/main.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o \
./src/tm_stm32_buffer.o \
./src/tm_stm32_delay.o \
./src/tm_stm32_disco.o \
./src/tm_stm32_gpio.o \
./src/tm_stm32_rcc.o \
./src/tm_stm32_usb.o \
./src/tm_stm32_usb_device.o \
./src/tm_stm32_usb_device_cdc.o 

C_DEPS += \
./src/main.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d \
./src/tm_stm32_buffer.d \
./src/tm_stm32_delay.d \
./src/tm_stm32_disco.d \
./src/tm_stm32_gpio.d \
./src/tm_stm32_rcc.d \
./src/tm_stm32_usb.d \
./src/tm_stm32_usb_device.d \
./src/tm_stm32_usb_device_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F429ZITx -DSTM32F429I_DISCO -DSTM32F4 -DSTM32 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -IC:/Users/gybel_000/workspace/USB_HALL/inc -IC:/Users/gybel_000/workspace/USB_HALL/CMSIS/core -IC:/Users/gybel_000/workspace/USB_HALL/CMSIS/device -IC:/Users/gybel_000/workspace/USB_HALL/HAL_Driver/Inc/Legacy -IC:/Users/gybel_000/workspace/USB_HALL/HAL_Driver/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/CustomHID/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/DFU/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Class/Template/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Device_Library/Core/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/MTP/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Class/Template/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Middlewares/ST/STM32_USB_Host_Library/Core/Inc -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ampire480272 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ampire640480 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/Common -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/cs43l22 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/exc7200 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ft6x06 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ili9325 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ili9341 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/l3gd20 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/lis302dl -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/lis3dsh -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/lsm303dlhc -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/mfxstm32l152 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/n25q128a -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/n25q256a -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/n25q512a -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/otm8009a -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ov2640 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/s25fl512s -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/s5k5cag -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/st7735 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/stmpe1600 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/stmpe811 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/ts3510 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Components/wm8994 -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Fonts -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/Log -IC:/Users/gybel_000/workspace/USB_HALL/Utilities/STM32F429I-Discovery -IC:/Users/gybel_000/workspace/USB_HALL/src -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


