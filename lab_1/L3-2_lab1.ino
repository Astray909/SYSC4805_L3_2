void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (2, INPUT); //Sensor input
  pinMode(13, OUTPUT); // LED output
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == 1)
    {
      Serial.println("Group 2 >> No obstacles (Sensor reading is 1)");
      digitalWrite(13,LOW);
    }
  else if (digitalRead(2) == 0)
    {
      Serial.println("Group 2 >> Yes obstacles (Sensor reading is 0)");
      digitalWrite(13,HIGH);
    }
  delay (500); //wait half a second
}
