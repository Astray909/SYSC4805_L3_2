volatile uint32_t CaptureCountA;
volatile boolean CaptureFlag;

/*Sample code to configure the PWM module to generate a PWM signal on pin 35,
which is PC3 - Arduino physical Pin 60.
* Period: 60 msec, Pulse duration: 10 usec. * Register Level Access
*/
void setup() {
  PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
  PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
  PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module

  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);//Set PWM clock 1MHz (Mck/84) 
  PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
                              | PWM_CMR_CPOL; //Set output polarity be high.

  PWM->PWM_CH_NUM[0].PWM_CPRD = 10000-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
  PWM->PWM_CH_NUM[0].PWM_CDTY = 10-1; // Set PWM duty cycle

  PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel

  Serial.begin(115200);
  PMC->PMC_PCER0 |= PMC_PCER0_PID28; // Timer Counter 0 channel 1 IS TC1, TC1 power ON 
  TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 // capture mode, MCK/2 = 42 MHz
                            | TC_CMR_ABETRG // TIOA is used as the external trigger
                            | TC_CMR_LDRA_RISING// load RA on rising edge of TIOA 
                            | TC_CMR_ETRGEDG_RISING; // Trigger on rising edge
  TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Reset TC counter and enable
  TC0->TC_CHANNEL[1].TC_IER |= TC_IER_LDRAS; // Trigger interrupt on Load RA 
  NVIC_EnableIRQ(TC1_IRQn); // Enable TC1 interrupts
}
void loop(){
  if (CaptureFlag) {
    CaptureFlag = 0; //Reset the flag,
    printf("L3, Group2: %f msec \n", CaptureCountA/42000.0);
  } //the .0 is required to type casting.
}
void TC1_Handler() {
  uint32_t status = TC0->TC_CHANNEL[1].TC_SR; //Read status register, Clear status 
  if (status & TC_SR_LDRAS) { // If ISR is fired by LDRAS then ....
    CaptureCountA = TC0->TC_CHANNEL[1].TC_RA; //read TC_RA
    if (CaptureFlag > 50)
    {
      CaptureFlag = 1; //Inform the main loop of an update.
    }
  }
}
