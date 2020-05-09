/*	Author: Jason Tang
 *  	Partner(s) Name: none
 *	Lab Section: 027
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States {Start, Begin, Init, Reset, Plus, Minus, PlusOn, MinusOn, Add, Sub} state;
unsigned char temp = 0x00;
volatile unsigned char TimerFlag = 0;
void TimerISR() { TimerFlag = 1;}
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;
void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}
void TimerOff() {
	TCCR1B = 0x00;
}
ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}
void TimerSet (unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

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
			else if ((~PINA & 0x03) == 0x01) {
				state = Add;
			}
			else if ((~PINA & 0x03) == 0x02) {
                                state = Sub;
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
			/*if (temp >= 0x0A) {
				temp = 0x00;
				state = PlusOn;
			}*/
			if ((~PINA & 0x03) == 0x01) {
                                state = Plus;
                        }
                        else {
                                state = Init;
                        }
                        break;
		case Add:
			if (temp >= 0x0A) {
                                temp = 0x00;
                        }
			state = PlusOn;
			break;
		case Sub:
			if (temp >= 0x0A) {
                                temp = 0x00;
                        }
			state = MinusOn;
			break;
		case PlusOn:
			if ((~PINA & 0x03) == 0x01) {
                                ++temp;
				state = PlusOn;
				if (temp >= 0x0A) {
					state = Add;
				}
                        }
                        else {
                                state = Plus;
                        }
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
			if ((~PINA & 0x03) == 0x02) {
                                state = MinusOn;
				++temp;
				if (temp >= 0x0A) {
					state = Sub;
				}
                        }
                        else {
                                state = Minus;
                        }
			break;

		default:
			state = Start;
			break;
	}
	switch(state) {
		case Start:
			PORTB = 0x07;
			break;
		case Begin:
			PORTB = 0x07;
			break;
		case Init:
			temp = 0x00;
			break;
		case PlusOn:
			break;
		case MinusOn:
			break;
		case Plus:
			break;
		case Minus:
			break;
		case Add:
			if (PORTB < 0x09) {
                        	PORTB = PORTB + 1;
			}
                        break;
		case Sub:
			if (PORTB > 0x00) {
                        	PORTB = PORTB - 1;
			}
                        break;
		case Reset:
			PORTB = 0x00;
			break;
		default:
			PORTB = 0x07;
			break;
	}
}

void main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(100);
    TimerOn();
    while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
}
