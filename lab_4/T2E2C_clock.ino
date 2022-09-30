volatile uint32_t CaptureCountA;
volatile boolean CaptureFlag;

/*Connect the wheel encoder signal to pin A7 in the Arduino.*/
void setup() {
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
  printf("L3, Group2: %f msec \n", CaptureCountA/42000.0);} //the .0 is required to type casting.
}
void TC1_Handler() {
  uint32_t status = TC0->TC_CHANNEL[1].TC_SR; //Read status register, Clear status 
  if (status & TC_SR_LDRAS) { // If ISR is fired by LDRAS then ....
    CaptureCountA = TC0->TC_CHANNEL[1].TC_RA; //read TC_RA
    CaptureFlag = 1; //Inform the main loop of an update. 
  }
}
