
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

/* complete the state machine. */

void Detect_Max_Amp()
{
    switch(detect_max_amp_state)
    {
        case DMAInit:
		if ((PINA >> 3) > maxAmp) {
			detect_max_amp_state = DMASave;
		}
		else {detect_max_amp_state = DMAInit;}
            break;
        
	case DMASave:
	    	detect_max_amp_state = DMAInit;
		break;

        default:
            break;
    }
    switch(detect_max_amp_state)
    {
        case DMAInit:
            break;
	case DMASave:	maxAmp = (PINA >> 3);
			break;
        default:
            break;
    }
}
