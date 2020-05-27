
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i



/*complete the state machine*/

void Detect_ZC()
{
    switch(detect_zc_state)
    {
        case DZCInit: 
		      if (k >= 1) {
			      detect_zc_state = Yes_zc;
		      }
		      else if ((PINA & 0x07) == 0x00) { //east
			      if (saved == 0x04) {
				      ++k;
				      detect_zc_state = DZCInit;
			      }
		      }
		      else if ((PINA & 0x07) == 0x01) { //NE
                              if (saved == 0x05) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x02) { //N
                              if (saved == 0x06) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x03) { //NW
                              if (saved == 0x07) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x04) { //W
                              if (saved == 0x00) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x05) { //SW
                              if (saved == 0x01) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x06) { //S
                              if (saved == 0x02) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else if ((PINA & 0x07) == 0x07) { //SE
                              if (saved == 0x03) {
                                      ++k;
				      detect_zc_state = DZCInit;
                              }
                      }
		      else {k = 0; saved = (PINA & 0x07); detect_zc_state = DZCInit;}
            break;
        
	case Yes_zc: detect_zc_state = DZCInit; break;

        default:
            detect_zc_state = DZCInit;
            break;
    }
    switch(detect_zc_state)
    {
        case DZCInit: ZC = 0x00;
            break;
	case Yes_zc: ZC = 0x01;
		     k = 0;
		     saved = (PINA & 0x07);
		     break;
        default:
            break;
    }
}
