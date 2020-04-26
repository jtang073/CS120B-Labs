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

unsigned array[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F};
unsigned char i = 0x00;
unsigned char invert = 0x00;
enum States {Start, Begin, Init, Reset, ResetOn, Plus, Minus, PlusOn, MinusOn} state;
void Tick() {
	switch(state) {
		case Start:
			state = Begin;
			break;
		case Begin:
			state = Init;
			break;
		case Init:
			if ((i > 0x08) || (i < 0x00)) {
				state = ResetOn;
			}
			else if ((~PINA & 0x01) == 0x01) {
				if ((invert & 0x01) == 0x01) {
                                	state = MinusOn;
                        	}
				else {
					state = PlusOn;
				}
			}
			else {
                        	state = Init;
                        }
			break;
		case Reset:
			if ((~PINA & 0x01) == 0x01) {
                                state = Reset;
                        }
                        else {
                                state = Begin;
                        }
                        break;
		case ResetOn:
			state = Reset;
			break;
		case Plus:
			if ((~PINA & 0x01) == 0x01) {
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
                        if ((~PINA & 0x01) == 0x01) {
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
			PORTC = 0x00;
			break;
		case Begin:
			PORTC = 0x00;
			break;
		case Init:
			break;
		case Plus:
			break;
		case Minus:
			break;
		case PlusOn:
			++i;
			PORTC = array[i];
                        break;
		case MinusOn:
			--i;
			PORTC = array[i];
                        break;
		case Reset:
			break;
		case ResetOn:
			PORTC = 0x00;
			if ((invert & 0x01) == 0x01) {
				invert = 0x00;
				i = 0x00;
			}
			else {
				invert = 0x01;
				i = 0x08;
			}
			break;
		default:
			PORTC = 0x00;
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
