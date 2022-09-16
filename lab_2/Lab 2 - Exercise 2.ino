#define LFS_L;
#define LFS_M;
#define LFS_R;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("L3, Group 2, Left:");
  if(digitalRead(2) == 1)
  {
    Serial.print(" B ");
  }
  else
  {
    Serial.print(" W ");
  }
  Serial.print("Middle:");
  if(digitalRead(3) == 1)
  {
    Serial.print(" B ");
  }
  else
  {
    Serial.print(" W ");
  }
  Serial.print("Right:");
  if(digitalRead(4) == 1)
  {
    Serial.print(" B ");
  }
  else
  {
    Serial.print(" W ");
  }
  Serial.println("");
  delay(500);
}
