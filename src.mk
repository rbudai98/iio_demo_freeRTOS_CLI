include $(PROJECT)/src/platform/$(PLATFORM)/platform_src.mk
include $(PROJECT)/src/examples/examples_src.mk

SRCS += $(PROJECT)/src/platform/$(PLATFORM)/main.c

INCS += $(PROJECT)/src/common/app_config.h
INCS += $(PROJECT)/src/common/common_data.h
SRCS += $(PROJECT)/src/common/common_data.c

INCS += $(PROJECT)/src/platform/platform_includes.h

INCS += $(PROJECT)/src/platform/$(PLATFORM)/parameters.h
SRCS += $(PROJECT)/src/platform/$(PLATFORM)/parameters.c 

SRCS += $(DRIVERS)/api/no_os_uart.c     \
    $(NO-OS)/util/no_os_fifo.c      \
    $(NO-OS)/util/no_os_list.c      \
    $(NO-OS)/util/no_os_util.c      \
    $(NO-OS)/util/no_os_alloc.c     

INCS += $(INCLUDE)/no_os_delay.h     \
    $(INCLUDE)/no_os_error.h     \
    $(INCLUDE)/no_os_fifo.h      \
    $(INCLUDE)/no_os_irq.h       \
    $(INCLUDE)/no_os_lf256fifo.h \
    $(INCLUDE)/no_os_list.h      \
    $(INCLUDE)/no_os_timer.h     \
    $(INCLUDE)/no_os_uart.h      \
    $(INCLUDE)/no_os_util.h      \
    $(INCLUDE)/no_os_alloc.h     \
    $(INCLUDE)/no_os_mutex.h     \
    $(INCLUDE)/no_os_semaphore.h 


# linking th mutex implementation for freeRTOS
ifeq '$(FREERTOS)' 'y'
SRCS += $(NO-OS)/drivers/platform/freeRTOS/freertos_mutex.c \
        $(NO-OS)/drivers/platform/freeRTOS/freertos_semaphore.c \
        $(NO-OS)/drivers/platform/freeRTOS/freertos_delay.c 
INCS += $(PROJECT)/src/platform/$(PLATFORM)/FreeRTOSConfig.h

else
SRCS += $(NO-OS)/util/no_os_mutex.c \
        $(NO-OS)/util/no_os_semaphore.c
endif

INCS += $(DRIVERS)/adc/adc_demo/adc_demo.h \
    $(DRIVERS)/dac/dac_demo/dac_demo.h

SRCS += $(DRIVERS)/adc/adc_demo/adc_demo.c \
    $(DRIVERS)/dac/dac_demo/dac_demo.c


# Link Segger view files
INCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/SEGGER/*.h)
INCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/Config/*.h)
INCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/Sample/FreeRTOSV10.4/*.h)

SRCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/SEGGER/*.c)
SRCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/SEGGER/Syscalls/*.c)
SRCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/Sample/FreeRTOSV10.4/*.c)
SRCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/Sample/FreeRTOSV10.4/Config/Cortex-M/*.c)

ASM_SRCS += $(wildcard /home/robi/Workspace_no-os/SEGGER_SysView/Src/SEGGER/SEGGER_RTT_ASM_ARMv7M.S)
