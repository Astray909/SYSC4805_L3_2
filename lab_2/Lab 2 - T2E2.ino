void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  double AREF = 3.3;
  double analogReader = analogRead(A0);
  Serial.print("L3, Group 2, voltage = ");
  double voltage=(analogReader/1023)*AREF;
  double distance_1 = pow (0.08, voltage);
  double distance = 38*distance_1;
  Serial.print(voltage);
  Serial.print(", distance is ");
  Serial.print(distance);
  Serial.print("cm");
  Serial.println("");

}
