# Test file for "Lab3"


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
#test "PINA: 0x00, PINB: 0x00 => PORTC: 0"
# Set inputs
#setPINA 0x00
#setPINB 0x00
# Continue for several ticks
#continue 2
# Set expect values
#expectPORTC 0
# Check pass/fail
#checkResult

# Add tests below

test "(1)PINA: 0x01, (0)PINB: 0x00 => (1)PORTC: 0x01"
setPINA 0x01
setPINB 0x00
continue 5
expectPORTC 0x01
checkResult

test "(2)PINA: 0x03, (0)PINB: 0x00 => (2)PORTC: 0x02"
setPINA 0x03
setPINB 0x00
continue 5
expectPORTC 0x02
checkResult

test "(0)PINA: 0x00, (1)PINB: 0x01 => (1)PORTC: 0x01"
setPINA 0x00
setPINB 0x01
continue 5
expectPORTC 0x01
checkResult

test "(4)PINA: 0xF0, (4)PINB: 0x0F => (8)PORTC: 0x08"
setPINA 0xF0
setPINB 0x0F
continue 5
expectPORTC 0x08
checkResult

test "(2)PINA: 0x03, (3)PINB: 0x70 => (5)PORTC: 0x05"
setPINA 0x03
setPINB 0x70
continue 5
expectPORTC 0x05
checkResult

test "(8)PINA: 0xFF, (8)PINB: 0xFF => (16)PORTC: 0x10"
setPINA 0xFF
setPINB 0xFF
continue 5
expectPORTC 0x10
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
