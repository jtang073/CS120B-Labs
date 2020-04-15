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
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned char tempC = 0x00;

    while (1) {
	tempA = PINA;
	tempB = (tempA >> 4) & 0x0F;
	tempC = (tempA << 4) & 0xF0;
	
	PORTB = tempB;
	PORTC = tempC;
	
    }
    return 1;
}
