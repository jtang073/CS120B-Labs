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

enum States {Start, Zero, One} state;
void Tick() {
	switch(state) {
		case Start:
			state = PB0;
			break;
		case Zero:
			if (PINA & 0x01) {
				state = PB1;
			}
			else {
				state = PB0;
			}
			break;
		case One:
			if (PINA & 0x01) {
                                state = PB1;
                        }
                        else {
                                state = PB0;
                        }
                        break;
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			PORTB = 0x00;
			break;
		case Zero:
                        PORTB = 0x01;
                        break;
		case One:
                        PORTB = 0x02;
                        break;
		default:
			PORTB = 0x00;
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
