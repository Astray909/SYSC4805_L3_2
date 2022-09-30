/*Connect the wheel encoder signal to pin A7 in the Arduino.*/
void setup() {
  Serial.begin(115200);
  PMC->PMC_PCER0 |= PMC_PCER0_PID28; // Timer Counter 0 channel 1 IS TC1, TC1 power ON 
  TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 // capture mode, MCK/2 = 42 MHz
                            | TC_CMR_ABETRG // TIOA is used as the external trigger
                            | TC_CMR_LDRA_RISING// load RA on rising edge of TIOA 
                            | TC_CMR_ETRGEDG_RISING; // Trigger on rising edge
  TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Reset TC counter and enable
}
void loop(){
  volatile uint32_t CaptureCountA;
  CaptureCountA = TC0->TC_CHANNEL[1].TC_RA;
  printf("L3, Group2: %f msec \n", CaptureCountA/42000.0); //the .0 is required to type casting.
}
