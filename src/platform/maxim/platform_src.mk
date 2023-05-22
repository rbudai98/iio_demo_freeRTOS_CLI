SRCS += $(PLATFORM_DRIVERS)/maxim_delay.c	\
	$(PLATFORM_DRIVERS)/maxim_irq.c		\
	$(PLATFORM_DRIVERS)/maxim_timer.c	\
	$(PLATFORM_DRIVERS)/maxim_uart.c	\
	$(PLATFORM_DRIVERS)/maxim_uart_stdio.c \
	$(PLATFORM_DRIVERS)/maxim_i2c.c 

	
INCS += $(PLATFORM_DRIVERS)/maxim_irq.h		\
	$(PLATFORM_DRIVERS)/maxim_uart.h	\
	$(PLATFORM_DRIVERS)/maxim_timer.h	\
	$(PLATFORM_DRIVERS)/maxim_uart_stdio.h \
	$(PLATFORM_DRIVERS)/maxim_i2c.h 

INCS += $(INCLUDE)/no_os_irq.h \
		$(INCLUDE)/no_os_i2c.h

SRCS += $(DRIVERS)/api/no_os_irq.c
SRCS += $(DRIVERS)/api/no_os_timer.c 
SRCS += $(DRIVERS)/api/no_os_i2c.c


SRCS += $(NO-OS)/util/no_os_lf256fifo.c