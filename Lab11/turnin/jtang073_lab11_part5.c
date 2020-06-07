/*	Author: Jason Tang
 *	Partner(s) Name: none
 *	Lab Section: 027
 *	Assignment: Lab 11  Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <timer.h>
#include <keypad.h>
#include <io.h>
#include <scheduler.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char currPos = 2;

enum ButtonStates {Start, Init, ButtonUp, ButtonDown, Release};
int ButtonTick(int state) {
	switch(state) {
		case Start: 	state = Init; 
				break;
		case Init:	if ((~PINB & 0x03) == 0x01) {state = ButtonDown;}
				else if ((~PINB & 0x03) == 0x02) {state = ButtonUp;}
				else {state = Init;}
				break;
		case ButtonDown: state = Release; break;
		case ButtonUp:	state = Release; break;
		case Release:	if ((~PINB & 0x03) == 0x00) {state = Init;}
				else {state = Release;}
				break;
		default:	state = Start;
				break;
	}
	switch(state) {
		case Start:	break;
		case Init:	break;
		case ButtonDown: currPos = 18; break;
		case ButtonUp:	currPos = 2; break;
		case Release:	break;
		default:	break;
	}
	return state;
}

enum LCDStates { LCDStart, LCDInit , LCDFailed };
unsigned char text[] = "                #        #                "; //17, 26
unsigned char lose[] = "Oh no, You Lost!  Press Reset";
unsigned char j = 0;
int LCDTick(int state) {
	switch(state) {
		case LCDStart:	state = LCDInit;
				break;
		case LCDInit:	if (text[currPos + j] == '#') {
                                        state = LCDFailed;
				}
				else {state = LCDInit;}
				break;
		case LCDFailed: if ((~PINB & 0x07) == 0x04) {
                                        state = LCDInit;
                                }
                                else {state = LCDFailed;}
				break;
		default: 	state = LCDStart;
				break;
	}
	switch(state) {
		case LCDStart:	break;

		case LCDInit:	for (int k = 1; k <= 32; ++k) {
					LCD_Cursor(k);
					LCD_WriteData(text[(k+j)%32]);
				}
				LCD_Cursor(currPos);
				if (j >= 32) {
                                        j = 0;
                                }
                                else {
                                        ++j;
                                }
				break;

		case LCDFailed:	//LCD_DisplayString(1, lose); 
				for (j = 1; j <= sizeof(lose) - 1; ++j) {
					LCD_Cursor(j);
					LCD_WriteData(lose[j-1]);
				}
				currPos = 2;
				j = 0;
				break;

		default:	break;
	}
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;//f00f
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    LCD_init();
    static task task1, task2;
    task *tasks[] = { &task1, &task2 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    const char start = -1;

    task1.state = start;
    task1.period = 10;
    task1.elapsedTime = task1.period;
    task1.TickFct = &ButtonTick;

    task2.state = start;
    task2.period = 20;
    task2.elapsedTime = task2.period;
    task2.TickFct = &LCDTick;

    TimerSet(10);
    TimerOn();

    unsigned short i;
    while (1) {
	for (i = 0; i < numTasks; ++i) {
		if (tasks[i]->elapsedTime == tasks[i]->period) {
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
