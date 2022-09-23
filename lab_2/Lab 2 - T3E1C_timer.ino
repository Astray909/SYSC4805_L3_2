/*Sample Code to generate PWM signal with period 60 msec and pulse duration 10 usec From Timer 0 Channel 0.
The output pin is B25, which is Arduino Pin 2.
Using Register level access
*/
void setup()
{
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;//TC0 power ON - Timer Counter 0 channel 0 
  PIOB->PIO_PDR |= PIO_PDR_P25; // The pin is no more driven by GPIO
  PIOB->PIO_ABSR |= PIO_PB25B_TIOA0;// B Assign B25 to alternative periph_B (TIOA0):
  TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 //MCK/2 = 42 MHz, 
                            | TC_CMR_WAVE //Waveform mode
                            | TC_CMR_WAVSEL_UP_RC //Count UP mode till RC
                            | TC_CMR_ACPA_CLEAR //Clear TIOA0 on RA compare match 
                            | TC_CMR_ACPC_SET; // Set TIOA0 on RC compare match
                            
  TC0->TC_CHANNEL[0].TC_RC = 2520000-1; //Set the frequency to 66.667Hz (Period 60 ms)
  TC0->TC_CHANNEL[0].TC_RA = 420-1; //Set the duty cycle (Pulse of 10 usec) 

  TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG //Software trigger TC0 channel 0 counter
                            | TC_CCR_CLKEN;//and enable
}

void loop()
{

}