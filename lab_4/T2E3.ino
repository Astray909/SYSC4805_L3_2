/*Connect the wheel encoder signal to pin 2 in the Arduino.*/

/*Sample code to configure the PWM module to generate a PWM signal on pin 35,
which is PC3 - Arduino physical Pin 60.
* Period: 60 msec, Pulse duration: 10 usec. * Register Level Access
*/

volatile unsigned long t = 0;
volatile unsigned long t_old = 0;
volatile unsigned long speed = 0;
volatile boolean CaptureFlag = 0;
void setup() {
  PMC->PMC_PCER1 |= PMC_PCER1_PID36; // Enable Clock to PWM module
  PIOC->PIO_ABSR |= PIO_PC3B_PWMH0; // Assign C3 to PWM module (Periph_B)
  PIOC->PIO_PDR |= PIO_PDR_P3; // Release C3 from the PIO module

  REG_PWM_CLK = PWM_CLK_PREA(0) | PWM_CLK_DIVA(168);//Set PWM clock 1MHz (Mck/168) 
  PWM->PWM_CH_NUM[0].PWM_CMR |= PWM_CMR_CPRE_CLKA // Set the clock source as CLKA
                              | PWM_CMR_CPOL; //Set output polarity be high.

  PWM->PWM_CH_NUM[0].PWM_CPRD = 500-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
  PWM->PWM_CH_NUM[0].PWM_CDTY = 500-1; // Set PWM duty cycle

  PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel

  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), time_ISR, FALLING); //+ve edge in PullUp.
}
void loop() {
  if (CaptureFlag) {
    CaptureFlag = 0; //Reset the flag,
    // Serial.println(t-t_old); //Print the time in msec,
    speed = 1000*(18.85/((t-t_old)*10));
    printf("L3, Group2: %f cm/s \n", speed); //the .0 is required to type casting.
    t_old = t;
  } 
}
void time_ISR() {
  if(millis() - t_old > 25){
    t = millis();
    CaptureFlag = 1; //Inform the main loop of an update.
  }
}
