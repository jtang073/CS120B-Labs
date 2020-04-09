/*	Author: jtang073
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned char tempA = 0x00;

    while (1) {
	tempA = PINA;
	if (tempA == 0x00) {
		PORTC = 0x04;	//all availiable
	}
	else if (tempA == 0x01 || tempA == 0x02 || tempA == 0x04 || tempA == 0x08) {
		PORTC = 0x03;	//3 availiable
	}
	else if (tempA == 0x03 || tempA == 0x05 || tempA == 0x06 || tempA == 0x09 || tempA == 0x0A || tempA == 0x0C) {
		PORTC = 0x02;	//2 availiable
	}
	else if (tempA == 0x07 || tempA == 0x0B || tempA == 0x0D || tempA == 0x0E) {
                PORTC = 0x01;	//1 availiable
        }
	else {
		PORTC = 0x00;	//full parking
	}
    }
    return 1;
}
