#define TRIG_PIN 2
#define ECHO_PIN 3
unsigned long pulse_t;
float distance;

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
  pulse_t = pulseIn(ECHO_PIN, HIGH, 50000);
  distance = (343 * (pulse_t/2))/10000;
  Serial.print("The pulse width is ");
  Serial.print(pulse_t);
  Serial.print(" >>> The distance is ");
  Serial.print(distance);
  Serial.println("cm >>> Section 3 Group 2");
  delay(60);
}
