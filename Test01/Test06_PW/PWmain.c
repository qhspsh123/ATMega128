#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <alloca.h>

#define BUZZER	PORTB6
#define LED_R	PORTG0
#define LED_G	PORTG1
#define LED_B	PORTG2	//교수님은 LED_Y로 되어있음
#define DDR		DDRG
#define PORT	PORTG
volatile int unsigned period = 30;
volatile int DutyRate = 50;
volatile int PlayBtn= 0;
int led_b_st = 0;
volatile int cnt = 0, cnt_ref = 20;

int CS = 8;	//분주비, Prescaler


enum {DO = 130, Do = 138, RE = 146, Re = 155, MI = 164, FA = 174, Fa = 185, SL = 196, Sl = 207, LA = 220, La = 233, SI = 246};
int song[] = {SL, SL, LA, LA, SL, SL, MI, SL, SL, MI, MI, RE, SL, SL, LA, LA, SL, SL, MI, SL, MI, RE, MI, DO};
int song1[100];

void conv()
{
	for(int i = 0; i < 25; i++)
	{
		song1[i] = F_CPU / /*(long)*/(CS * song[i]*5);		//분주비 1024 로 할 경우 (long)(long) 테스트 연잔자 필요
	}
}

ISR(INT0_vect)
{
	PlayBtn++;
	DDRB |= 0x40; 
	if(PlayBtn>1) {
		PlayBtn = 0;
		DDRB &= ~0x40;
	}
		
	//OCR1A += 100;
	//period -= 10;
	//if(period <0) period = 30;
}

ISR(INT1_vect)
{
	OCR1B += 100;
	//DutyRate += 10;
	//if(DutyRate> 90) DutyRate = 10;					//SW PWM
}

ISR(INT2_vect)
{
		//cnt_ref -= 1;
		//if (cnt_ref < 0) cnt_ref = 20;
		OCR1C += 100;
}


ISR(TIMER0_COMP_vect)
{
	//if(++cnt > cnt_ref)
	//{
		//if (led_b_st) {PORT &= ~0x04; led_b_st = 0; }//_BV(LED_B) on
		//else {PORT |= 0x04; led_b_st = 1;}//_BV(LED_B) on
		//cnt=0;
	//}
	//
	//TCNT0 = 0;
}

ISR(TIMER1_COMPA_vect)
{
	
}
ISR(TIMER1_COMPB_vect)
{
	
}
ISR(TIMER1_COMPC_vect)
{
	
}
int main(void)
{
	DDR = 0x07;
	//DDRB |= 0xE0;  //PB 5, 6, 7: output, 
	
	//ETIMSK |= 0x01; //EMTMSK |= (1 << OCIE1C)
	TIMSK |= (1 << OCIE1A) | (1 << OCIE1B); //TIMSK |= 0x1C;	
	EIMSK |= 0x07;	// (1 << INT0) | (1 << INT1) | (1 << INT2)
	EICRA |= 0x2A; // Falling Edge (Rising 은 3F) 
	
	ICR1 = 100;
	
	TCCR0 |= 0x07;	//PSC 1024
	TCCR1A |= 0xAA;	// (1 << COM1A1) | (1 << COM1B1) |	(1 << COM1C1) | (1 << WGM11)		COM1A1, 0  COM1B1, 0  COM1C1, 0     WGM1 1, 0(파형생성모드)
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1<<CS11); // (1 << CS12) | (1 << CS10);			//|=0x1D									분주비 100 (256) 
	OCR1A = ICR1;
	OCR1B = 100;
	OCR1C = 300;
	conv();
	OCR0 = 157;
	sei();
    while (1) 
    {
		
		if (PlayBtn)
		{
			for (int j = 0; j < 24; j++)
			{	
				
				ICR1 = song1[j];
				if(j == 6 | j == 18)_delay_ms(500);
				if(j == 23) _delay_ms(1700);
				if(j == 11) _delay_ms(1700);
				_delay_ms(500);
				
				
				
			}
		}
		//PORT |= 0x03; _delay_ms((period * DutyRate) / 100);			//T_H
		//PORT &= ~0x03; _delay_ms(period * (100-DutyRate) / 100);	//T_L
    }
}

