#define F_CPU 16000000UL
#include <avr/io.h> //AVR 기본 헤더
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h> // delay 함수를 사용하기 위한 헤더

//	SW : PG3 Input
// LED : PG4 Output LED키려면 해당포트를 1 로 만들어줘야함
char circular_shift_left(char pattern)
{
	return ( (pattern << 1) | (pattern >>7));
	
}
int get_button_state(void)
{
	
}
int Check()
{
	char v1 = PING & 0x01; //v1 = G그룹 1번 bit의 값
	char v2 = PING & 0x02; //v2 = G그룹 2번 bit의 값
	char v3 = PING & 0x04; //v3 = G그룹 3번 bit의 값
	if(v1 == 0) return 1;
	if(v2 == 0) return 2;
	if(v3 == 0) return 3;
	return 0;
}
int main(void)
{
    /* Replace with your application code 고장나거나 전원이 꺼질 때 까지 계속실행되어야하므로 무한루프이다*/
    DDRG |= 0x10;	// XXXX XXXX --> 1byte   GPIO는 1bit 단위로 계산 XXXX 0101 ==> XXX1 0101
					//상위 세 비트는 스펙상 못쓰는 것. 다섯번째 비트: 1=출력 0=입력    ㄴ 기존값 연동을 위해 OR(|)실행
					// |= 는 bit or를 뜻함
	DDRG &= ~0x06;  // XXXX XXXX ==> XXXX X00X: 0=입력
	
	int delay1 = 200;
	//char v = 1;
	char mode = 0; // mode = 0 : disable, mode = 1 : active
	while (1) // loop until SW press
	{
		if(Check()) {mode = 1; break;}
	}
	while (1)
	{
		if(mode == 1)
		{
			PORTG |= 0x10; //값을 내보내주는 출력 레지스터 입력용은 'pin' 이라는 레지스터 사용. 레지스터로 4번에 접근
			// DDG3 = 1; 로해도됨 -> bit에 직접 접근, but constant(상수), read only ==> 0x10 = 1 과 동일
			//bit mask 라고도 불림
			_delay_ms (delay1);
			PORTG &= ~0x10; //해당 bit OFF,  해당 bit를 반전시킬때 사용
			_delay_ms (delay1); //끄고 나서도 지연 해줘야함 바로 루프 반복하지 않게
		}
		if(Check() == 1)
		{
			if(mode == 1) mode = 0;
			else		mode =1;	
		}
		if(Check() == 2)	delay1 = delay1 + 100;
		if(Check() == 3)	delay1 = delay1 - 20;
		if(delay1 < 100)	delay1 = 100;
		//if(Check()) //pushed
		//{
			//if(mode == 0)	mode = 1;
			//else			mode = 0;
		//}
		_delay_ms (300);
	}
}

