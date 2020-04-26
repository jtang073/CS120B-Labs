/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *	Video (demo): https://drive.google.com/open?id=1FEw77C5ny-VH2oT67_bsbnywFgCYBo19
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Begin, Init, Reset, Plus, Minus, PlusOn, MinusOn} state;
void Tick() {
	switch(state) {
		case Start:
			state = Begin;
			break;
		case Begin:
			state = Init;
			break;
		case Init:
			if ((~PINA & 0x03) == 0x03) {
                                state = Reset;
                        }
			else if ((~PINA & 0x01) == 0x01) {
				state = PlusOn;
			}
			else if ((~PINA & 0x02) == 0x02) {
                                state = MinusOn;
                        }
			break;
		case Reset:
			if ((~PINA & 0x03) == 0x03) {
                                state = Reset;
                        }
                        else {
                                state = Init;
                        }
                        break;
		case Plus:
			if ((~PINA & 0x03) == 0x01) {
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
                        if ((~PINA & 0x03) == 0x02) {
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
		case Begin:
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
		case Reset:
			PORTC = 0x00;
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
