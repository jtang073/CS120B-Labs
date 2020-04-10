# Test file for "Lab2"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
#test "PINA: 0x00 => PORTB: 0xFF"
# Set inputs
#setPINA 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTB 0xFF
# Check pass/fail
#checkResult

# Add tests below

test "(100)PINA: 0x64, (80)PINB: 0x50, (10)PINC: 0x0A => (190)PORTD: 0xBF (101111 11)"
setPINA 0x64
setPINB 0x50
setPINC 0x0A
continue 5
expectPORTD 0xBF
checkResult

test "(79)PINA: 0x4F, (0)PINB: 0x00, (0)PINC: 0x00 => (79)PORTD: 0x4C (010011 00)"
setPINA 0x4F
setPINB 0x00
setPINC 0x00
continue 5
expectPORTD 0x4C
checkResult

test "(100)PINA: 0x64, (60)PINB: 0x3C, (30)PINC: 0x1E => (190)PORTD: 0xBD (101111 01)"
setPINA 0x64
setPINB 0x3C
setPINC 0x1E
continue 5
expectPORTD 0xBD
checkResult

test "(100)PINA: 0x64, (10)PINB: 0x0A, (10)PINC: 0x0A => (120)PORTD: 0x7A (011110 10)"
setPINA 0x64
setPINB 0x0A
setPINC 0x0A
continue 5
expectPORTD 0x7A
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
