# CS120B Intro to Embedded Systems (Spring 2020)
**Professor/Author:** Philip Brisk

**College:** University of California, Riverside

**Name:** Jason Tang

**Partner:** None

**Section:** 027

## Lab 1
Zybooks reading. (No lab folder available)

## Lab 2
1)	Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night.
2)	Port A's pins 3 to 0, each connect to a parking space sensor, 1 meaning a car is parked in the space, of a four-space parking lot. Write a program that outputs in binary on port C the number of available spaces (Hint: declare a variable "unsigned char cntavail;" you can assign a number to a port as follows: 
PORTC = cntavail;).
3)	Extend the previous program to still write the available spaces number, but only to PC3..PC0, and to set PC7 to 1 if the lot is full.
4)	**(Challenge)** An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg.  The remaining 6 bits on D should display an approximation of the total combined weight, accurate within 3 kg.  (Interesting note: Disneyland recently redid their "It's a Small World" ride because the average passenger weight has increased over the years, causing more boats to get stuck on the bottom).

## Lab 3
1)	Count the number of 1s on ports A and B and output that number on port C.
2)	A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. Level 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..PC1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less.
3)	In addition to the above, PA4 is 1 if a key is in the ignition, PA5 is one if a driver is seated, and PA6 is 1 if the driver's seatbelt is fastened. PC7 should light a "Fasten seatbelt" icon if a key is in the ignition, the driver is seated, but the belt is not fastened.
4)	**(Challenge):** Read an 8-bit value on PA7..PA0 and write that value on PB3..PB0PC7..PC4. That is to say,  take the upper nibble of PINA and map it to the lower nibble of PORTB, likewise take the lower nibble of PINA and map it to the upper nibble of PORTC (PA7 -> PB3, PA6 -> PB2, … PA1 -> PC5, PA0 -> PC4).
5)	**(Challenge):** A car's passenger-seat weight sensor outputs a 9-bit value (ranging from 0 to 511) and connects to input PD7..PD0PB0 on the microcontroller. If the weight is equal to or above 70 pounds, the airbag should be enabled by setting PB1 to 1. If the weight is above 5 but below 70, the airbag should be disabled and an "Airbag disabled" icon should light by setting PB2 to 1. (Neither B1 nor B2 should be set if the weight is 5 or less, as there is no passenger)

## Lab 4
1)	PB0 and PB1 each connect to an LED, and PB0's LED is initially on. Pressing a button connected to PA0 turns off PB0's LED and turns on PB1's LED, staying that way after button release. Pressing the button again turns off PB1's LED and turns on PB0's LED.
2)	Buttons are connected to PA0 and PA1. Output for PORTC is initially 7. Pressing PA0 increments PORTC once (stopping at 9). Pressing PA1 decrements PORTC once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0.
3)	A household has a digital combination deadbolt lock system on the doorway. The system has buttons on a keypad. Button 'X' connects to PA0, 'Y' to PA1, and '#' to PA2. Pressing and releasing '#', then pressing 'Y', should unlock the door by setting PB0 to 1. Any other sequence fails to unlock. Pressing a button from inside the house (PA7) locks the door (PB0=0). For debugging purposes, give each state a number, and always write the current state to PORTC (consider using the enum state variable). Also, be sure to check that only one button is pressed at a time.
4)	**(Challenge)** Extend the above door so that it can also be locked by entering the earlier code.
5)	**(Challenge)** Extend the above door to require the 4-button sequence #-X-Y-X rather than the earlier 2-button sequence. To avoid excessive states, store the correct button sequence in an array, and use a looping SM.

## Lab 5
1)	(From an earlier lab) A car has a fuel-level sensor that sets PA3..PA0 to a value between 0 (empty) and 15 (full). A series of LEDs connected to PC5..PC0 should light to graphically indicate the fuel level. If the fuel level is 1 or 2, PC5 lights. If the level is 3 or 4, PC5 and PC4 light. 5-6 lights PC5..PC3. 7-9 lights PC5..PC2. 10-12 lights PC5..C1. 13-15 lights PC5..PC0. Also, PC6 connects to a "Low fuel" icon, which should light if the level is 4 or less. Use buttons on PA3..PA0 and mimic the fuel-level sensor with presses.
2)	(From an earlier lab) Buttons are connected to PA0 and PA1. Output for PORTC is initially 0. Pressing PA0 increments PORTC (stopping at 9). Pressing PA1 decrements PORTC (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTC resets to 0. If a reset occurs, both buttons should be fully released before additional increments or decrements are allowed to happen. Use LEDs (and resistors) on PORTC. Use a state machine (not synchronous) captured in C.
3)	**(Challenge)** Create your own festive lights display with 6 LEDs connected to port PB5..PB0, lighting in some attractive sequence. Pressing the button on PA0 changes the lights to the next configuration in the sequence.  Use a state machine (not synchronous) captured in C.

## Lab 6
1)	Create a synchSM to blink three LEDs connected to PB0, PB1, and PB2 in sequence, 1 second each. Implement that synchSM in C using the method defined in class. In addition to demoing your program, you will need to show that your code adheres entirely to the method with no variations.
2)	Create a simple light game that requires pressing a button on PA0 while the middle of three LEDs on PB0, PB1, and PB2 is lit. The LEDs light for 300 ms each in sequence. When the button is pressed, the currently lit LED stays lit. Pressing the button again restarts the game.
3)	**(Challenge)** (from an earlier lab) Buttons are connected to PA0 and PA1. Output for PORTB is initially 7. Pressing PA0 increments PORTB once (stopping at 9). Pressing PA1 decrements PORTB once (stopping at 0). If both buttons are depressed (even if not initially simultaneously), PORTB resets to 0. Now that we have timing, only check to see if a button has been pressed every 100 ms. Additionally, if a button is held, then the count should continue to increment (or decrement) at a rate of once per second.	

## Lab 7
1)	Buttons are connected to PA0 and PA1. Output PORTC and PORTD drive the LCD display, initially displaying 0. Pressing PA0 increments the display (stopping at 9). Pressing PA1 decrements the display (stopping at 0). If both buttons are depressed (even if not initially simultaneously), the display resets to 0. If a button is held, then the display continues to increment (or decrement) at a rate of once per second. Use a synchronous state machine captured in C.
2)	**(Challenge)** Extend the earlier light game to maintain a score on the LCD display. The initial score is 5. Each time the user presses the button at the right time (the middle LED), the score increments. Each time the user fails, the score decrements. When reaching 9, show victory somehow.

## Lab 8
TBD - May 17, 2020

## Lab 9
TBD - May 17, 2020

## Lab 10
TBD - May 24, 2020

## Lab 11
TBD - May 31, 2020

## Lab 12
TBD - June 7, 2020
