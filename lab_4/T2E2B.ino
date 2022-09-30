/*Connect the wheel encoder signal to pin 2 in the Arduino.*/
volatile unsigned long t = 0;
volatile unsigned long t_old = 0;
volatile boolean CaptureFlag = 0;
void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), time_ISR, FALLING); //+ve edge in PullUp.
}
void loop() {
  if (CaptureFlag) {
    CaptureFlag = 0; //Reset the flag,
    Serial.println(t-t_old); //Print the time in msec,
    t_old = t;
  } 
}
void time_ISR() {
  if(millis() - t_old > 25){
  t = millis();
  CaptureFlag = 1; //Inform the main loop of an update.
  }
}
