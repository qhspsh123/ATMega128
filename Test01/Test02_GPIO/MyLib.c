/*
 * MyLib.c
 *
 * Created: 2024-10-11 오후 2:38:11
 *  Author: user
 */ 
#include <avr/io.h>

int TestBit(char pin, char mask) // PINx 레지스터의 값이 mask bit가 0인지 1인지 판별
{
	if((pin & mask) != 0) return 1;
	return 0;
}

void StandBy() // PG4 PIN으로 프로그램 시작 스위치 연결
{
	DDRG &= ~0x10;	//	G4 : 입력으로 설정 & 1110 1111
	PORTG |= 0x10;	//  G4 : Pull-up	  | 0001 0000
	
	while(!TestBit(PING, 0x10));
	while(TestBit(PING, 0x10)); // if((PING & 0x10) == 0) break;
}