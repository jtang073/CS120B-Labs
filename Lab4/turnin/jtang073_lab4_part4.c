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

enum States {Start, Init, UnlockPound, UnlockY, UnlockYRelease, Locked} state;
void Tick() {
	switch(state) {
		case Start:
			state = Init;
			break;
		case Init:
			if ((PINA & 0x07) == 0x04) {
				state = UnlockPound;
			}
			else if ((PINA & 0x87) == 0x80) {
				state = Locked;
			}
			else {
				state = Init;
			}
			break;
		case UnlockPound:
			if ((PINA & 0x07) == 0x04) {
                                state = UnlockPound;
                        }
                        else {
                                state = UnlockY;
                        }
                        break;
		case UnlockY:
			if (((PINA & 0x07) == 0x02) && ((PORTB & 0x01) == 0x01)) {
                                state = Locked;
                        }
			else if ((PINA & 0x07) == 0x02) {
				state = UnlockYRelease;
			}
			else if (PINA == 0x00) {
				state = UnlockY;
			}
                        else {
                                state = Init;
                        }
                        break;
		case UnlockYRelease:
			if ((PINA & 0x07) == 0x02) {
                                state = UnlockYRelease;
                        }
                        else {
                                state = Init;
                        }
                        break;
		case Locked:
			if ((PINA & 0x87) == 0x80) {
                                state = Locked;
                        }
			else if ((PINA & 0x07) == 0x02) {
				state = Locked;
			}
                        else {
                                state = Init;
                        }
                        break;
	}
	switch(state) {
		case Start:
			PORTB = 0x00;
			break;
		case Init:
			break;
		case UnlockPound:
			break;
		case UnlockY:
			break;
		case UnlockYRelease:
			PORTB = 0x01;
			break;
		case Locked:
			PORTB = 0x00;
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
