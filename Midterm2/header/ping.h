
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Ping()
{
    switch(ping_state)
    {
        case PInit: if (p < 9) {++p; ping_state = PInit;}
		    else {ping_state = POn;}
            break;

	case POn:   {ping_state = PInit;}
		    break;

        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit: Pinger = 0x00;
            break;
	case POn:   Pinger = 0x01;
		    p = 0;
		    break;
        default:
            break;
    }
}
