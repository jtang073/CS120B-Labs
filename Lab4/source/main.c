/*	Author: jtang073
 *  Partner(s) Name: 
 *	Lab Section: 027
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, OnPress, OnRelease, OffPress, OffRelease} state;
void Tick() {
	switch(state) {
		case Start:
			state = OnPress;
			break;
		case OnPress:
			if ((PINA & 0x01) == 0x01) {
				state = OnPress;
			}
			else {
				state = OnRelease;
			}
			break;
		case OnRelease:
			if ((PINA & 0x01) == 0x01) {
                                state = OffPress;
                        }
                        else {
                                state = OnRelease;
                        }
                        break;
		case OffPress:
			if ((PINA & 0x01) == 0x01) {
				state = OffPress;
			}
			else {
				state = OffRelease;
			}
			break;
		case OffRelease:
			if ((PINA & 0x01) == 0x01) {
				state = OnPress;
			}
			else {
				state = OffRelease;
			}
			break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			PORTB = 0x01;
			break;
		case OnPress:
                        PORTB = 0x01;
                        break;
		case OnRelease:
			break;
		case OffPress:
                        PORTB = 0x02;
                        break;
		case OffRelease:
			break;
		default:
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    while (1) {
	Tick();
    }
    return 1;
}
