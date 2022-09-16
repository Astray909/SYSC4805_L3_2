#define TRIG_PIN 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode (TRIG_PIN, INPUT); //Sensor input
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(TRIG_PIN) == 1)
    {
      Serial.println("Group 2 >> (Sensor reading is 1)");
    }
  else if (digitalRead(TRIG_PIN) == 0)
    {
      Serial.println("Group 2 >> (Sensor reading is 0)");
    }
  delayMicroseconds (10);
}
