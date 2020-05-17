/*	Author: Jason Tang
 *  	Partner(s) Name: none
 *	Lab Section: 027
 *	Assignment: Lab 8  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *	Demo: https://drive.google.com/drive/folders/1yAnALESDkdTPnRFxuDGLOQAdb88LgJq2?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned short x = 0x00;
unsigned short max = 0xFF;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1<< ADATE);
}

int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    ADC_init();
    while (1) {
	x = ADC;
	unsigned char xb = (char)x;
	unsigned decrement = max/8;
	//unsigned char xd = (char)(x >> 8);
	if (xb <= (decrement * 1)) {
		PORTB = 0x01;
	}
	else if (xb <= (decrement * 2)) {
                PORTB = 0x03;
        }
	else if (xb <= (decrement * 3)) {
		PORTB = 0x07;
	}
	else if (xb <= (decrement * 4)) {
                PORTB = 0x0F;
        }
	else if (xb <= (decrement * 5)) {
                PORTB = 0x1F;
        }
	else if (xb <= (decrement * 6)) {
                PORTB = 0x3F;
        }
	else if (xb <= (decrement * 7)) {
                PORTB = 0x7F;
        }
	else if (xb <= (decrement * 8)) {
		PORTB = 0xFF;
	}
    }
    return 0;
}
