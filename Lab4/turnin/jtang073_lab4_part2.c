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

enum States {Start, Init, Reset, Plus, Minus, PlusOn, MinusOn} state;
void Tick() {
	switch(state) {
		case Start:
			state = Init;
			break;
		case Init:
			if ((PINA & 0x03) == 0x03) {
                                state = Reset;
                        }
			else if ((PINA & 0x01) == 0x01) {
				state = PlusOn;
			}
			else if ((PINA & 0x02) == 0x02) {
                                state = MinusOn;
                        }
			break;
		case Reset:
			if ((PINA & 0x03) == 0x03) {
				state = Reset;
			}
			else {
				state = Init;
			}
			break;
		case Plus:
			if ((PINA & 0x01) == 0x01) {
                                state = Plus;
                        }
                        else {
                                state = Init;
                        }
                        break;
		case PlusOn:
			state = Plus;
			break;
			
		case Minus:
                        if ((PINA & 0x02) == 0x02) {
                                state = Minus;
                        }
                        else {
                                state = Init;
                        }
                        break;
		case MinusOn:
			state = Minus;
			break;
			
		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			PORTC = 0x07;
			break;
		case Init:
			break;
		case Plus:
			break;
		case Minus:
			break;
		case PlusOn:
			if (PORTC < 0x09) {
                        	PORTC = PORTC + 1;
			}
                        break;
		case MinusOn:
			if (PORTC > 0x00) { 
                        	PORTC = PORTC - 1;
			}
                        break;
		default:
			PORTC = 0x07;
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
    /* Insert your solution below */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    while (1) {
	Tick();
    }
    return 1;
}
