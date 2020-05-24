/*	Author: Jason Tang
 *  	Partner(s) Name: none
 *	Lab Section: 027
 *	Assignment: Lab 10  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *	Demo: https://drive.google.com/drive/folders/17Lj00EERTAOPsR5L8tM3jGRO6wzX64mr?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum ThreeLEDStates {ThreeStart, Zero, One, Two} ThreeLEDstate;
enum BlinkingLEDStates {BlinkingStart, BlinkingInit, Blink} BlinkingLEDstate;
enum CombineLEDStates {CombineStart, CombineInit} CombineLEDstate;
unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;

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

void TickThreeLEDsSM() {
	switch(ThreeLEDstate) {
		case ThreeStart:	ThreeLEDstate = Zero; break;
		
		case Zero:	ThreeLEDstate = One;
				break;

		case One:	ThreeLEDstate = Two;
				break;

		case Two:	ThreeLEDstate = Zero;
				break;

		default:	ThreeLEDstate = ThreeStart; break;
	}

	switch (ThreeLEDstate) {
		case ThreeStart:        break;
		case Zero:		threeLEDs = 0x01; break;
		case One:		threeLEDs = 0x02; break;
		case Two:		threeLEDs = 0x04; break;
                default:        	break;
	}
}

void TickBlinkingLEDSM() {
	switch (BlinkingLEDstate) {
                case BlinkingStart:     BlinkingLEDstate = BlinkingInit; break;
                case BlinkingInit:      BlinkingLEDstate = Blink; break;
                case Blink:     	BlinkingLEDstate = BlinkingInit; break;
                default:        	BlinkingLEDstate = BlinkingStart; break;
        }
	switch (BlinkingLEDstate) {
                case BlinkingStart:     break;
                case BlinkingInit:      blinkingLED = 0x00; break;
                case Blink:    		blinkingLED = 0x01; break;
                default:        	break;
        }
}

void TickCombineLEDsSM() {
        switch (CombineLEDstate) {
                case CombineStart:      CombineLEDstate = CombineInit; break;
                case CombineInit:       CombineLEDstate = CombineInit; break;
                default:		CombineLEDstate = CombineStart; break;
        }
        switch (CombineLEDstate) {
                case CombineStart:      break;
                case CombineInit:       PORTB = ((blinkingLED << 3) | (threeLEDs)); break;
                default:       		break;
        }
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    unsigned long ThreeElapsed = 0;
    unsigned long BlinkingElapsed = 0;
    const unsigned long timerPeriod = 100;
    TimerSet(100);
    TimerOn();
    ThreeLEDstate = ThreeStart;
    BlinkingLEDstate = BlinkingStart;
    CombineLEDstate = CombineStart;

    while (1) {
	if (ThreeElapsed >= 300) {
		TickThreeLEDsSM();
		ThreeElapsed = 0;
	}
	if (BlinkingElapsed >= 1000) {
		TickBlinkingLEDSM();
		BlinkingElapsed = 0;
	}
	TickCombineLEDsSM();
	while(!TimerFlag) {};
	TimerFlag = 0;
	ThreeElapsed += timerPeriod;
	BlinkingElapsed += timerPeriod;
    }
    return 0;
}
