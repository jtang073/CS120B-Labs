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

test "(500)PIND: 0xFA, PINB: 0x00, (SEATBELT ENABLE)PORTB: 0x02"
setPIND 0xFA
setPINB 0x00
continue 5
expectPORTB 0x02
checkResult

test "(69)PIND: 0x22, PINB: 0x01, (SEATBELT DISABLE)PORTB: 0x04"
setPIND 0x22
setPINB 0x01
continue 5
expectPORTB 0x04
checkResult

test "(1)PIND: 0x00, PINB: 0x01, (NONE)PORTB: 0x00"
setPIND 0x00
setPINB 0x01
continue 5
expectPORTB 0x00
checkResult

test "EDGE (5)PIND: 0x02, PINB: 0x01, (NONE)PORTB: 0x00"
setPIND 0x00
setPINB 0x01
continue 5
expectPORTB 0x00
checkResult

test "EDGE (70)PIND: 0x23, PINB: 0x00, (SEATBELT ENABLE)PORTB: 0x02"
setPIND 0x23
setPINB 0x00
continue 5
expectPORTB 0x02
checkResult

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
