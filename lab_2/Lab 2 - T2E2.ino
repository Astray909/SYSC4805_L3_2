void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  double AREF = 3.3;
  double analogReader = analogRead(A0);
  delay(500);
  Serial.print("L3, Group 2, ");
  double voltage=(analogReader/1023)*AREF;
  Serial.print(voltage);
  Serial.println("");
  if(voltage = )

}
