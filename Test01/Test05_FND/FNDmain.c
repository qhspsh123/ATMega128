#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <alloca.h>
#define FND_TYPE_CATHOD


#define CDDR	DDRB
#define CPORT	PORTB
#define IDDR	DDRA
#define IPORT	PORTA

unsigned char img[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x67}; // 0123456789
char data [] = {0, 0, 0, 0}; //1234
	
int digit(int num) // num 변수를 1000, 100, 10, 1 자릿수 추출하여 data[] 배열에 저장
{
	if(num > 9999) return 0;	//인수 유효성 체크	
	data[3] = num % 10;//1
	data[2] = (num / 10) % 10;//10
	data[1] = (num / 100) % 10;//100
	data[0] = (num / 1000);//1000
	return 1;
}

volatile int st = 0;
ISR(INT0_vect)
{
	if(st == 0) st++;
	else if(st == 1) st++;
	else if(st > 1) st = 0;
}

volatile int i = 0;
volatile int cnt;
volatile int num = 0;
ISR(TIMER0_COMP_vect)		//비교일치 인터럽트
{
	TCNT0 = 0;
	cnt++;
	if (cnt == 5)
	{	
		if (st == 0) num = 0;
		if (st == 1) num++;
		if (st == 2) ;
		cnt = 0;
	}
	//for(num = 0; num <10000; num++)
	//{
		//digit(num);
		//for(int i = 0; i < 4; i++)
		//{
			//CPORT = ~_BV(i); //1 << i;
			//{
				//IPORT = img[data[i]];
				//if(i == 2) IPORT |= 0x8F;
				//_delay_ms(5);
			//}
			//
		//}
	//}
}
volatile int j = 0;
ISR(TIMER2_OVF_vect)
{
	digit(num);
	CPORT = ~_BV(j); //1 << i;
	IPORT = img[data[j]];
	if (j == 1)	IPORT = IPORT + 0x80;
	j++;
	if (j == 4) j = 0;
}
int main(void)
{
	// Timer0: 100ms stop-watch, timer2: FND refresh
	TIMSK |= 0x42;		// OCIE0 TOIE2
	TCCR0 |= 0x06;		// 분주비 110: 256, 111: 1024
	TCCR2 |= 0x04;		// 분주비 101: 256, (1/16M) * 256 * 256 = 
	OCR0 = 125;			// (1/16M) * 224 *1024 * 7 = 0.100352
	
	CDDR |= 0x0F;		// 하위 4bit를 출력으로 설정
	IDDR |= 0xFF;		// 8bit 전체를 출력으로 설정
	CPORT |= 0x00;
	IPORT |= 0xBF;		
	EIMSK |= _BV(INT0); // State(st) change interrupt 설정 INT0 활성화
	EICRA |= 0x03;		// 상승에지에서 interrupt 요청 발생
	sei();
	
	int num;
    /* Replace with your application code */
    while (1)
    {		
	    //for(num = 0; num <10000; num++)
	    //{
			//
	    //}
	    //_delay_ms(10);
		//digit(num);
		//for(int i = 0; i < 4; i++)
		//{
			//CPORT = ~_BV(i); //1 << i;
			//{
				//IPORT = img[data[i]];
				//_delay_ms(5);
			//}
		//}
    }
    
}
