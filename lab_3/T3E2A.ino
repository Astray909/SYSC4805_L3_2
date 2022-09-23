#include <Wire.h>
#include <LIS3MDL.h>
LIS3MDL mag;
char report[80];
void setup()
{
  Serial.begin(9600);
  Wire.begin();
  if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }
  mag.enableDefault();
}
void loop() {
  float Mx,My,Mz;
  mag.read();
  Mx = ((float)mag.m.x) / 6842;
  My = ((float)mag.m.y) / 6842;
  Mz = ((float)mag.m.z) / 6842;
  Serial.println("Scaled Values of Magnetometer (+- 4 gauss)");
  snprintf(report, sizeof(report), "X-axis:%.3f Y-axis:%.3f Z-axis:%.3f", Mx, My, Mz);
  Serial.println(report);
  delay(500);
}