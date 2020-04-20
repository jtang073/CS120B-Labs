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

enum States {Start, Init, Correct, Wrong, Unlock, Locked} state;
unsigned char index = 0x00;
unsigned char array[4] = {0x04, 0x01, 0x02, 0x01};
void Tick() {
	switch(state) {
		case Start:
			state = Init;
			break;
		case Init:
			if (index == 0x04) {
				state = Unlock;
			}
			else if ((PINA & 0x87) == array[index]) {
				state = Correct;
			}
			else if ((PINA & 0x87) == 0x80) {
				state = Locked;
			}
			else if (PINA == 0x00) {
				state = Init;
			}
			else {
				state = Wrong;
			}
			break;
		case Correct:
			if ((PINA & 0x07) == 0x00) {
                                ++index;
				state = Init;
                        }
			else {
				state = Correct;
			}
                        break;
		case Wrong:
			if ((PINA & 0x07) == 0x00) {
				index = 0x00;
				state = Init;
			}
			else {
				state = Wrong;
			}
			break;
		case Unlock:
                        if ((PINA & 0x07) == 0x00) {
				state = Init;
				index = 0x00;
			}
			else {
				state = Unlock;
			}
			break;
		case Locked:
			if ((PINA & 0x87) == 0x80) {
                                state = Locked;
                        }
                        else {
                                state = Init;
				index = 0x00;
                        }
                        break;
	}
	switch(state) {
		case Start:
			PORTB = 0x00;
			break;
		case Init:
			break;
		case Correct:
			break;
		case Wrong:
			break;
		case Unlock:
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
