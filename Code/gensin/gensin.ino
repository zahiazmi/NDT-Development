///////////////////////////////////Pin 5/////////////////////////////////////
#define OSP_SET_WIDTH2(cycles2) (OCR0B = 0xff-(cycles2-1))
void osp_setup2(uint8_t cycles2) {
  TCCR0B =  0;
  TCNT0 = 0x00;
  OCR0A = 0;
  OSP_SET_WIDTH2(cycles2);
  TCCR0A = _BV(COM0B0) | _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
  TCCR0B = _BV(WGM02) | _BV(CS00);
  DDRD |= _BV(5);
}

void osp_setup2() {
  osp_setup2(1);
}

#define OSP_FIRE2() (TCNT0 = OCR0B - 1)
#define OSP_INPROGRESS2() (TCNT0>0)
#define OSP_SET_AND_FIRE2(cycles2) {uint8_t m2=0xff-(cycles2-1); OCR0B=m2;TCNT0 =m2-1;}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Pin 3////////////////////////////////////////////////

#define OSP_SET_WIDTH(cycles) (OCR2B = 0xff-(cycles-1))
void osp_setup(uint8_t cycles) {
  TCCR2B =  0;
  TCNT2 = 0x00;
  OCR2A = 0;
  OSP_SET_WIDTH(cycles);
  TCCR2A = _BV(COM2B0) | _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  DDRD |= _BV(3);
}

void osp_setup() {
  osp_setup(1);
}

#define OSP_FIRE() (TCNT2 = OCR2B - 1)
#define OSP_INPROGRESS() (TCNT2>0)
#define OSP_SET_AND_FIRE(cycles) {uint8_t m=0xff-(cycles-1); OCR2B=m;TCNT2 =m-1;}
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////Pin 10////////////////////////////////////////

#define OSP_SET_WIDTH3(cycles3) (OCR1B = 0xffff-(cycles3-1))
void osp_setup3(uint16_t cycles3) {
  TCCR1B = 0;
  TCNT1 = 0x0000; // Start counting at bottom.
  ICR1 = 0;
  OSP_SET_WIDTH3(cycles3);
  TCCR1A = (1 << COM1B0) | (1 << COM1B1) | (1 << WGM11); // OC1B=Set on Match, clear on BOTTOM. Mode 14 Fast PWM. p.131
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10); // Prescaler = 1; Start counting now. Max ~4mS
  DDRB = (1 << 2);   // Set pin to output (Note that OC1B = GPIO port PB2 = Arduino Digital Pin D10 Uno)
}

void osp_setup3() {
  osp_setup3(1);
}

#define OSP_FIRE3() (TCNT1 = OCR1B - 1)
#define OSP_INPROGRESS3() (TCNT1>0)
#define OSP_SET_AND_FIRE3(cycles3) {uint16_t m3=0xffff-(cycles3-1); OCR1B=m3; TCNT1 = m3-1;} // Prescaler = 1 only
/////////////////////////////////////////////////////////////////////////////////////////////////////////
float freq1=0.08; //pin D3
float freq2=0.5; //pin D5
float freq3=1; //pin D10


void setup()
{
  osp_setup();
  osp_setup2();
  osp_setup3();
}

void loop()
{
  OSP_SET_AND_FIRE(500/freq1/62.5) //pin D3;
  OSP_SET_AND_FIRE2(500/freq2/62.5) //pin D5;
  OSP_SET_AND_FIRE3(500/freq3/62.5) //pin D10;
  delayMicroseconds(1000);      // Wait a sec to let the audience clap
}
