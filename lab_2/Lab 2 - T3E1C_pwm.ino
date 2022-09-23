/*Sample code to configure the PWM module to generate a PWM signal on pin 35,
which is PC3 - Arduino physical Pin 60.
* Period: 60 msec, Pulse duration: 10 usec. * Register Level Access
*/
void setup()
{
  PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
  PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
  PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module

  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(84);//Set PWM clock 1MHz (Mck/84) 
  PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
                              | PWM_CMR_CPOL; //Set output polarity be high.

  PWM->PWM_CH_NUM[0].PWM_CPRD = 60000-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
  PWM->PWM_CH_NUM[0].PWM_CDTY = 10-1; // Set PWM duty cycle

  PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel
}
void loop() 
{
  
}