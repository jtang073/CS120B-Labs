//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
		if (i > 10) {
			detect_eq_state = Yes_eq;
			i = 0;
		}
		else {detect_eq_state = DEQInit;}
            break;
	case Yes_eq:
	    	if (i > 10) {
			detect_eq_state = DEQInit;
			i = 0;
		}
		else {detect_eq_state = Yes_eq;}
		break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
		if ((PINA >> 3) > 0x00) {
                        ++i;
                }
                else {i = 0;}
		earthquake = 0x00;
            break;
	case Yes_eq:
		if ((PINA >> 3) > 0x00) {
			i = 0;
		}
		else {++i;}
		earthquake = 0x01;
		break;
        default:
            break;
    }
}
