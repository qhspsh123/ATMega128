#include <avr/io.h> //AVR 기본 헤더
// LED Port : PG4  LED키려면 해당포트를 1 로 만들어줘야함

int main(void)
{
    /* Replace with your application code 고장나거나 전원이 꺼질 때 까지 계속실행되어야하므로 무한루프이다*/
    DDRG |= 0x10;	// XXXX XXXX --> 1byte   GPIO는 1bit 단위로 계산 XXXX 0101 ==> XXX1 0101
					//상위 세 비트는 스펙상 못쓰는 것. 다섯번째 비트: 1=출력 0=입력    ㄴ 기존값 연동을 위해 OR(|)실행
	while (1) 
    {
		PORTG |= 0x10;
    }
}

