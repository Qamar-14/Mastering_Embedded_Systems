#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 8000000UL

int main(void)
{
	// Setting LED pins PD2,PD3 and PB2 as input pins
	DDRD  &= ~( (1<<2) | (1<<2))  ;	
	DDRB  &= ~(1<<2);	

	// Enabling interrupts INT1 INT0 INT2
	GICR |= (1<<7 | 1<<6 | 1<<5);
	
	// Configuring interrupts as any logical change(INT0), rising(INT1) ,and falling(INT2)
	MCUCR = 0x09;
	MCUCSR &= ~(1<<6);


	// Enabling global interrupt
	sei();
	

	// Setting LED pins PD5,PD6 and PD7 as output pins
	DDRD |= ((1<<5) | (1<<6) | (1<<7)) ;	

	while(1)
	{
		PORTD &= ~((1<<5) | (1<<6) | (1<<7)) ;
		_delay_ms(1000);
	}



	return 0;
}



ISR(INT0_vect)
{
	PORTD |= (1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	PORTD |= (1<<6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	PORTD |= (1<<7);
	_delay_ms(1000);
}
