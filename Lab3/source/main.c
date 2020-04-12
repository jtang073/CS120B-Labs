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
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned char tempC = 0x00;

    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = 0x00;
	if ((tempA & 0x01) == 0x01) {
		tempC = tempC + 1;
	}
	if ((tempA & 0x02) == 0x02) {
		tempC = tempC + 1;
	}
	if ((tempA & 0x04) == 0x04) {
                tempC = tempC + 1;
        }
        if ((tempA & 0x08) == 0x08) {
                tempC = tempC + 1;
        }
	if ((tempA & 0x10) == 0x10) {
                tempC = tempC + 1;
        }
        if ((tempA & 0x20) == 0x20) {
                tempC = tempC + 1;
        }
	if ((tempA & 0x40) == 0x40) {
                tempC = tempC + 1;
        }
        if ((tempA & 0x80) == 0x80) {
                tempC = tempC + 1;
        }
	if ((tempB & 0x01) == 0x01) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x02) == 0x02) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x04) == 0x04) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x08) == 0x08) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x10) == 0x10) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x20) == 0x20) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x40) == 0x40) {
                tempC = tempC + 1;
        }
        if ((tempB & 0x80) == 0x80) {
                tempC = tempC + 1;
        }
	PORTC = tempC;
	
    }
    return 1;
}
