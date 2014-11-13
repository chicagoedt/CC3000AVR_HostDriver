make:
	avr-gcc -O3 -mmcu=atmega32u4 -c spi.c\
					security.c\
					wlan.c\
					socket.c\
					hci.c\
					cc3000_common.c\
					evnt_handler.c\
					netapp.c\
					nvmem.c\
