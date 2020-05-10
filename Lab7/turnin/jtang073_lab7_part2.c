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
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum States {Start, Init, NextLed, Pause, Restart1/*, Restart2*/} state;
unsigned char alternate = 0x00;
unsigned char score = 0x05;
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
	if (score == 0x00) {
		LCD_DisplayString(1, "0");
	}
	else if (score == 0x01) {
		LCD_DisplayString(1, "1");
	}
	else if (score == 0x02) {
                LCD_DisplayString(1, "2");
        }
	else if (score == 0x03) {
                LCD_DisplayString(1, "3");
        }
	else if (score == 0x04) {
                LCD_DisplayString(1, "4");
        }
	else if (score == 0x05) {
                LCD_DisplayString(1, "5");
        }
	else if (score == 0x06) {
                LCD_DisplayString(1, "6");
        }
	else if (score == 0x07) {
                LCD_DisplayString(1, "7");
        }
	else if (score == 0x08) {
                LCD_DisplayString(1, "8");
        }
	else if (score == 0x09) {
                LCD_DisplayString(1, "9");
		LCD_DisplayString(2, "VICTORY!!!");
        }

	switch(state) {
		case Start:	state = Init; break;
		case Init:	state = NextLed; break;
		case NextLed:	if ((~PINA & 0x01) == 0x01) {state = Pause;}
				else {state = NextLed;}
			       	break;
		case Pause:	if ((~PINA & 0x01) == 0x01) {state = Pause;}
				else {state = Restart1;}
				break;
		case Restart1:	if ((~PINA & 0x01) == 0x01) {state = Init;}
				else {state = Restart1;}
				break;
		/*case Restart2:	if ((~PINA & 0x01) == 0x01) {state = Restart2;}
				else {state = NextLed;}
				break;*/
		default:	state = Start; break;
	}
	switch (state) {
		case Start:     score = 0x05;break;
                case Init:      PORTB = 0x01; break;
		case NextLed:
			if (alternate == 0x00) {
				if (PORTB == 0x04) {
					PORTB = PORTB >> 1;
					alternate = 0x01;
				}
				else {
					PORTB = PORTB << 1;
				}
			}
			else {
				if (PORTB == 0x01) {
                                        PORTB = PORTB << 1;
                                        alternate = 0x00;
                                }
                                else {
                                        PORTB = PORTB >> 1;
                                }
			}
			break;
		case Pause: 	if (PORTB == 0x02) { ++score;}
				else {--score;} 
				break;
		case Restart1:	break;
		/*case Restart2: 	break;*/
                default:        break;
	}
}

void main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    TimerSet(300);
    TimerOn();
    LCD_init();
    while (1) {
	Tick();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
}
