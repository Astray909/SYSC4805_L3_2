#include <VL53L1X.h>
#include <Wire.h>

/*Connect the wheel encoder signal to pin 2 in the Arduino.*/

/*Sample code to configure the PWM module to generate a PWM signal on pin 35,
which is PC3 - Arduino physical Pin 60.
* Period: 60 msec, Pulse duration: 10 usec. * Register Level Access
*/

VL53L1X sensor;

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

  PWM->PWM_CH_NUM[0].PWM_CPRD = 5000-1; //Set PWM freq 1MHz/(60000) = 66.667Hz
  PWM->PWM_CH_NUM[0].PWM_CDTY = 5000-1; // Set PWM duty cycle

  PWM->PWM_ENA = PWM_ENA_CHID0; // Enable the PWM channel

  /*
  pinMode(2, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), time_ISR, FALLING); //+ve edge in PullUp.
  attachInterrupt(digitalPingToInterrupt(5), time_ISR, FALLING);
  */

  Serial.begin (9600);
  /*
  Wire.begin();
  Wire.setClock(4000000);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while(1);
  }

  sensor.setDistanceMode(VL53L1X::Short);
  sensor.setMeasurementTimingBudget(50000);
  */
  pinMode(2, INPUT); //Sensor input
  pinMode(5, INPUT); //Sensor 2 input 
  pinMode(13, OUTPUT); // LED output
  pinMode(3, OUTPUT);//DIR output
  pinMode(4, OUTPUT);//DIR output

  //sensor.startContinuous(50);
}
void loop() {
  // if (CaptureFlag) {
  //   CaptureFlag = 0; //Reset the flag,
  //   // Serial.println(t-t_old); //Print the time in msec,
  //   speed = 1000*(18.85/((t-t_old)*10));
  //   printf("L3, Group2: %f cm/s \n", speed); //the .0 is required to type casting.
  //   t_old = t;
  // } 
  /*
  Serial.print(sensor.read());
  if(sensor.timeoutOccurred()) 
  {
    Serial.print("TIMEOUT");
  }
  Serial.println();
  */
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == 1 & digitalRead(5) == 1)
    { 
      Serial.println("Group 2 >> No obstacles (Sensor reading is 1)");
      digitalWrite(13,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
    }
  //turn 90 degrees right
  else if (digitalRead(2) == 0 & digitalRead(5) == 1)
    {
      Serial.println("Group 2 >> Yes obstacles (Sensor reading is 0)");
      digitalWrite(13,HIGH);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      delay(500);
    }

  //turn 90 degrees left
  else if (digitalRead(2) == 1 & digitalRead(5) == 0)
    {
      Serial.println("Group 2 >> Yes obstacles (Sensor reading is 0)");
      digitalWrite(13,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      delay(500);
    }

  //turn 180 degrees
  else if (digitalRead(2) == 0 & digitalRead(5) == 0)
    {
      Serial.println("Group 2 >> Yes obstacles (Sensor reading is 0)");
      digitalWrite(13,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      delay(2000);
    }
  delay (500); //wait half a second
}
void time_ISR() {
  // if(millis() - t_old > 25){
  //   t = millis();
  //   CaptureFlag = 1; //Inform the main loop of an update.
  // }
}