#define v_aref 3.3
#define analog_in A0

int analoginput = 0; // our analog pin
int analogamount = 0; // stores incoming value
float percentage = 0; // used to store our percentage value
float voltage =0; // used to store voltage value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT_PULLUP);
  analogReference(EXTERNAL);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("L3, Group 2, ");
  Serial.print(analog_in);
  voltage=(analog_in/1023) * v_aref;
  Serial.print(voltage);
  Serial.println("");
  delay(500);
}
