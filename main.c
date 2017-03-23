#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>

#define UART_BAUD_RATE 2400

#include "uart.h"
#include "bmp085.h"

int main(void) 
{
	long l;
	double d;
	char printbuff[10];

	//init uart
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

	//init interrupt
	sei();
	//uart_puts_P( "bmp180 Logger \r");
	uart_puts("temperature1: \r");
	
	//init of senzor bmp085
	bmp085_init(); // rusi UART
	
	uart_puts("temperature_3: ");
	//main loop
	while(1)
	{
		//get temperature
		d = bmp085_gettemperature();
		dtostrf(d, 10, 2, printbuff);
		uart_puts("temperature2: "); 
		uart_puts(printbuff);  
		uart_puts(" C deg"); 
		uart_puts("\r\n");

		//get pressure
		l = bmp085_getpressure();
		ltoa(l, printbuff, 10);
		uart_puts("pressure: "); 
		uart_puts(printbuff);
		uart_puts(" Pa");
		uart_puts("\r\n");

		//get altitude
		d = bmp085_getaltitude();
		dtostrf(d, 10, 2, printbuff);
		uart_puts("altitude: ");
		uart_puts(printbuff);
		uart_puts(" M");
		uart_puts("\r\n");

		uart_puts("\r\n");
		_delay_ms(1500);
	}
	
	return 0;
}
