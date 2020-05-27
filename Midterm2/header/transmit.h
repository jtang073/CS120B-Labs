//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Transmit()
{
    switch(transmit_state)
    {
        case TInit: transmit_state = TInit;
            break;
        default:
            transmit_state = TInit;
            break;
    }
    switch(transmit_state)
    {
        case TInit: if (earthquake == 0x01) {PORTB = (maxAmp << 3) | (ZC << 2) | (earthquake << 1) | (Pinger & 0x01);}
			    else {PORTB = (ZC << 2) | (earthquake << 1) | (Pinger & 0x01);}
            break;
        default:
            break;
    }

}
