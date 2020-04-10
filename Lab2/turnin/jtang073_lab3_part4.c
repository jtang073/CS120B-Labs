/*	Author: jtang073
 *  Partner(s) Name: N/A
 *	Lab Section: 027
 *	Assignment: Lab 2  Exercise 4
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
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned char tempC = 0x00;
    unsigned char tempD = 0x00;
    unsigned char tempDD = 0x00;
    unsigned char finalD = 0x00;
    unsigned short totalWeight = 0x0000;

    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	tempD = 0x00;
	tempDD = 0x00;
	totalWeight = tempA + tempB + tempC;
	if (totalWeight > 0x008C) {
		tempD = 0x01;
	}
	else {
		tempD = 0x00;
	}

	if (tempA > tempC) {
		if ((tempA - tempC) > 0x50) {
			tempDD = 0x02;
		}
	}
	else {
		if ((tempC - tempA) > 0x50) {
			tempDD = 0x02;
		}
	}
	finalD = (totalWeight & 0x00FC) | tempD | tempDD;
	PORTD = finalD;
	
    }
    return 1;
}
