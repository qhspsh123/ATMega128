#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

#define DDR DDRG
#define PORT PORTG
#define LED PORTG1

int cnt = 0, cnt1 = 0, cntEx = 5, st =0;

ISR(INT0_vect) //점점 느리게
{
	cntEx++;
}

ISR(INT1_vect) //점점 빠르게
{
	cntEx--;
	if(cntEx <1) cntEx = 1;
}

ISR(TIMER0_OVF_vect)
{
	cnt++;			//256마다 불러오면 너무 짧으니까 cnt라는 매개변수를 둬 time interval 을 늘린다.
	if(cnt > 25)	// (1/16M) *256 * 256 *25 = 100ms
	{
		cnt = 0;
		cnt1++;
		if(cnt1 >= cntEx)
		{
			cnt1 = 0;
			if(st) { PORT &= ~_BV(LED); st = 0; }
			else   { PORT |= _BV(LED); st = 1; }
		}
			
		
	}
}

int main(void)
{
	DDR |= _BV(LED);		//LED port 설정
	PORT |= _BV(LED);	//LED On
	StandBy();
	PORT &= ~_BV(LED);	//LED off

	TIMSK |= 0x01;			//TOIE0
	TCCR0 |= 0x06;			// 분주비 110: 256 111: 1024
					//Interrupt enable
	EIMSK |= 0x03;
	EICRA |= 0x0F;
	sei();	

	


	/* Replace with your application code */
	while(1)
	{

	}
}