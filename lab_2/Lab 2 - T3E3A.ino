#define TRIG_PIN 2
#define ECHO_PIN 3
unsigned long output;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(ECHO_PIN,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);
  pulseIn(ECHO_PIN, HIGH, 50000);
  Serial.print(output);
  Serial.println(" Section 3 Group 2");
  delay(60);
}
