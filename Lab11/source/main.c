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

unsigned char x = 0x00;
unsigned char keypad = 0x00;

enum KeypadStates {Start, Init};
int KeypadTick(int state) {
	x = GetKeypadKey();
	switch(state) {
		case Start: 	state = Init; 
				break;
		case Init:	state = Init;	
				break;
		default:	state = Start;
				break;
	}
	switch(state) {
		case Start:	break;
		case Init:	
			switch(x) {
				case '\0': 	keypad = 0x1F; break;
				case '1':	keypad = 0x01; break;
				case '2':	keypad = 0x02; break;
				case '3':	keypad = 0x03; break;
				case '4':	keypad = 0x04; break;
				case '5':	keypad = 0x05; break;
				case '6':	keypad = 0x06; break;
				case '7':	keypad = 0x07; break;
				case '8':	keypad = 0x08; break;
				case '9':	keypad = 0x09; break;
				case 'A':	keypad = 0x0A; break;
				case 'B':	keypad = 0x0B; break;
				case 'C':	keypad = 0x0C; break;
				case 'D':	keypad = 0x0D; break;
				case '*':	keypad = 0x0E; break;
				case '0':	keypad = 0x00; break;
				case '#':	keypad = 0x0F; break;
				default:	keypad = 0x1B; break;
			}
			PORTB = keypad;
			break;
				
		default:	break;
	}
	return state;
}

enum LCDStates { LCDStart, LCDInit, LCDDisp };
unsigned char text[] = "               CS120B is Legend... wait for it DARY!";
unsigned char currPos = 0x01;
unsigned char lcd[16];
int LCDTick(int state) {
	switch(state) {
		case LCDStart:	state = LCDInit;
				break;
		case LCDInit:	if (keypad == 0x1F) {state = LCDInit;}
				else {state = LCDDisp;}
				break;
		case LCDDisp:	state = LCDInit;
		default: 	state = LCDStart;
				break;
	}
	switch(state) {
		case LCDStart:	break;
		case LCDInit:	/*for (int k = 0; k < 16; ++k) {
					lcd[k] = text[(k + currPos) % 52];
				}
				currPos = ((currPos + 1) % 52); // scooch over
				LCD_DisplayString(1, lcd);*/
				LCD_Cursor(currPos);
				break;
		case LCDDisp:	//LCD_Cursor(currPos);
				LCD_WriteData(x);
				if (currPos > 15) {
					currPos = 1;
				}
				else { ++currPos;}
				break;
		default:	break;
	}
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0xFF; PORTA = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    LCD_init();
    static task task1, task2;
    task *tasks[] = { &task1, &task2 };
    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    const char start = 0;

    task1.state = start;
    task1.period = 10;
    task1.elapsedTime = task1.period;
    task1.TickFct = &KeypadTick;

    task2.state = start;
    task2.period = 20;
    task2.elapsedTime = task2.period;
    task2.TickFct = &LCDTick;

    TimerSet(10);
    TimerOn();
    
    LCD_DisplayString(1, "Congratulations!");

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
