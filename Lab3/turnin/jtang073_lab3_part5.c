/*	Author: jtang073
 *  Partner(s) Name: N/A
 *	Lab Section: 027
 *	Assignment: Lab 3  Exercise 1
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
    DDRB = 0x01; PORTB = 0x00;
    DDRD = 0x00; PORTD = 0xFF;
    unsigned char tempB = 0x00;
    unsigned char tempD = 0x00;
    unsigned char finalB = 0x00;
    unsigned short totalWeight = 0x0000;

    while (1) {
	tempD = PIND;
	tempB = PINB;
	finalB = 0x00;
	totalWeight = (tempD << 1) | (tempB & 0x01);
	if (totalWeight >= 0x0046) {
		finalB = 0x02;
	}
	else if (totalWeight > 0x0005) {
		finalB = 0x03;
	}
	else {
		finalB = 0x00;
	}
	PORTB = finalB;
	
    }
    return 1;
}
