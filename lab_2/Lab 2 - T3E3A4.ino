#define TRIG_PIN 2
#define ECHO_PIN 3
unsigned long pulse_t;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);

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

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN,HIGH);
  digitalWrite(TRIG_PIN,LOW);
  pulse_t = pulseIn(ECHO_PIN, HIGH, 50000);
  distance = (343 * (pulse_t/2))/10000;
  Serial.print("The pulse width is ");
  Serial.print(pulse_t);
  Serial.print(" >>> The distance is ");
  Serial.print(distance);
  Serial.println("cm >>> Section 3 Group 2");
}
