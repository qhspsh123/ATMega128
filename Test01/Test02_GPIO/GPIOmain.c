#define F_CPU 16000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <alloca.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define SW1  PORTG4 // (1<<0) bit shift 0번 shift 0001
#define SW2  PORTD0 
#define SW3  PORTD1 
#define LED1 PORTG1

volatile int ival = 1000;

ISR(INT0_vect) //점점 느리게
{
	ival += 100;
	if(ival > 2000) ival = 2000;

}

ISR(INT1_vect) //점점 빠르게
{
	ival -= 100;
	if(ival < 80) ival = 100;
}


	
int main(void)
{
	
    /* Replace with your application code */
	// DDRG는 0 ~ 4 까지만 있다. 하위 4 Bit + 상위 LSB 1 Bit => 5개 Bit 
	
	DDRG &= ~0x0C;	//	0b 0000 1100 => 0b 1111 0011 : 입력 마스크
	DDRG |= 0x03;	//  0b xxxx xx11				 : 출력 마스크
	PORTG |= _BV(LED1); //(1<<LED1); = 0x02; // 시작되면 LED ON
	StandBy();
	PORTG &= ~_BV(LED1); //(1<<LED1); = 0x02; // 시작되면 LED ON

	// Mask Register : EIMSK
	EIMSK |= 0x03;
	// Create Register : EICRA
	EICRA |= 0x0A;

	
	sei();
	
    while (1) 
    {	 
		//if((PING & _BV(SW2)) == 0) ival += 500;	//G1 Slower
		//else if((PING & _BV(SW3)) == 0)			//G2 Faster
		//{
			//ival -=500;
			//if(ival < 10) ival = 100;
		//}
		PORTG |= _BV(LED1); //LED ON
		_delay_ms(ival);		//  1/1000 sec delay
		PORTG &= ~_BV(LED1); //LED OFF
		_delay_ms(ival); 
    }
}

