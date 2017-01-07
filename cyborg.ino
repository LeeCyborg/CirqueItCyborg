/// Chest 0 - 6
// shoulder 7-10
// up arm 11-17
/// lowarm 18-23
// hand 24-20


#include <Adafruit_NeoPixel.h>
#define PIN            12
#define NUMPIXELS      30
int accelX;
int accelY;
int accelZ;
const int xInput = A7;
const int yInput = A9;
const int zInput = A10;
const int sampleSize = 2;
int fadeRate = 0;
int MaxBrightness = 255;
int TotalSteps = 2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  strip.begin();
  for (int i = 0; i < NUMPIXELS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  analogReference(EXTERNAL);
  Serial.begin(9600);
  pinMode(2, INPUT);
}
void loop() {
  printAxis();
  /// Chest 0 - 6
  // shoulder 7-10
  // up arm 11-17
  /// lowarm 18-23
  // hand 24-30
  if (!digitalRead(2)){
    setSection(0, 6 , accelX, accelZ, random(100, 250));
    setSection(7, 10 , accelX, accelY, random(100, 250));
    setSection(11, 17 , accelX, accelZ, random(100, 250));
    setSection(18, 23 , accelX, accelZ, random(100, 250));
    setSection(24, 30 , accelX, accelY, random(100, 250));
  } else {
    setSection(0, 6 , random(100, 250), accelY, accelX);
    setSection(7, 10 , random(100, 250), accelX, accelY);
    setSection(11, 17 , random(100,250), accelY, accelZ);
    setSection(18, 23 , random(100, 250), accelX, accelZ);
    setSection(24, 30 , random(100, 250), accelX, accelZ);
  }
  //
//  if (digitalRead(2)){
//    setSection(0, 6 , accelX, random(0, 20), random(150, 200));
//    setSection(7, 10 , accelX, random(150, 200), accelZ);
//    setSection(11, 17 , random(150, 200), random(0, 20), accelY);
//    setSection(18, 23 , accelX, random(150, 200), accelZ);
//    setSection(24, 30 , random(0, 20), accelY, random(150, 200));
//  } else {
//    setSection(0, 6 , accelZ, accelY, random(0, 20));
//    setSection(7, 10 , accelX, random(0, 20), accelY);
//    setSection(11, 17 , accelZ, accelY, random(0, 20));
//    setSection(18, 23 , accelY, random(0, 20), accelZ);
//    setSection(24, 30 , accelX, random(0, 20), accelZ);
//  }
}
void setSection(int start, int finish, int Nred, int Ngreen, int Nblue) {
  uint32_t c = strip.getPixelColor(start);
  uint8_t  redCur = (c >> 16) & 0xFF;
  uint8_t  greenCur = (c >>  8) & 0xFF;
  uint8_t  blueCur = c & 0xFF;
  uint8_t redNew = Nred;
  uint8_t greenNew = Ngreen;
  uint8_t blueNew = Nblue;
  for (int i = 1; i < TotalSteps; i++)
  {
    uint8_t red = (((redCur * (TotalSteps - i)) + (redNew * i)) / TotalSteps);
    uint8_t green = (((greenCur * (TotalSteps - i)) + (greenNew * i)) / TotalSteps);
    uint8_t blue = (((blueCur * (TotalSteps - i)) + (blueNew * i)) / TotalSteps);
    for (int j = start; j < finish + 1; j++) {
      strip.setPixelColor(j, red, green, blue);
      strip.show();
      delay(fadeRate);
    }
  }
}
void printAxis() {

  accelX = map(ReadAxis(xInput), 300, 700, 0, 255);
  accelY = map(ReadAxis(yInput), 300, 700, 0, 255);
  accelZ = map(ReadAxis(zInput), 300, 700, 0, 255);
  Serial.print(accelX);
  Serial.print(", ");
  Serial.print(accelY);
  Serial.print(", ");
  Serial.println(accelZ);
  delay(500);
}
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}
