#include <Adafruit_NeoPixel.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time
#include <Wire.h>
#define PIN 6
#define NUMPIX 60


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIX, PIN, NEO_GRB + NEO_KHZ800);


// R, G, B, brightness, hours, minutes
unsigned int colors[][6] = {
  {255, 0, 0, 20, 0, 0},
  {255, 0, 0, 18, 1, 0},
  {255, 0, 0, 18, 2, 0},
  {255, 0, 0, 15, 3, 0},
  {255, 0, 0, 15, 4, 0},
  {255, 0, 0, 25, 5, 0},
  {255, 78, 0, 25, 6, 0},
  {255, 128, 0, 105, 7, 0},
  {255, 255, 0, 225, 8, 0},
  {255, 255, 255, 160, 9, 0},
  {0, 255, 255, 150, 10, 0},
  {0, 255, 0, 125, 11, 0},
  {0, 0, 255, 105, 12, 0},
  {0, 255, 0, 91, 13, 0},
  {255, 255, 0, 83, 14, 0},
  {255, 128, 0, 82, 15, 0},
  {128, 0, 255, 81, 16, 0},
  {255, 0, 255, 97, 17, 0},
  {0, 0, 255, 116, 18, 0},
  {255, 0, 255, 90, 19, 0},
  {255, 128, 0, 65, 20, 0},
  {255, 255, 0, 50, 21, 0},
  {255, 128, 0, 35, 22, 0},
  {255, 255, 0, 23, 23, 0},
  {255, 0, 0, 25, 20, 0} //Make sure this is the same as the first line, becauze lazy
};


void setup() {
 // pinMode(A2, OUTPUT); //add these 4 lines back in for plugging 
 // pinMode(A3, OUTPUT); //the RTC directly into the Arduino Uno R3
 // digitalWrite(A2, LOW);
 // digitalWrite(A3, HIGH);
  setSyncProvider(RTC.get);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
   unsigned int color_hour1 ;
   unsigned int color_min1  ;
   unsigned int color_hour2  ;
   unsigned int color_min2 ;
   unsigned int r1;
   unsigned int r2;
   unsigned int g1;
   unsigned int g2;
   unsigned int b1;
   unsigned int b2;
  
  for(int i=0; i<sizeof(colors)-1; i++){
    color_hour1 = colors[i][4];
    color_min1 = colors[i][5];
    color_hour2 = colors[i+1][4];
    color_min2 = colors[i+1][5];
    if(hour() <= color_hour1){
      unsigned int k1 = colors[i][3];
      r1 = colors[i][0] * k1 / 255;
      g1 = colors[i][1] * k1 / 255;
      b1 = colors[i][2] * k1 / 255;
      unsigned int k2 = colors[i+1][3];
      r2 = colors[i+1][0] * k2 / 255;
      g2 = colors[i+1][1] * k2 / 255;
      b2 = colors[i+1][2] * k2 / 255;
      break;
    }
  }
  unsigned int timespan = (color_hour2 - color_hour1) * 60 + (color_min2 - color_min1);
  unsigned int elapsed_time = (hour() - color_hour1) * 60 + (minute() - color_min1);
  unsigned int rout = map(elapsed_time, 0, timespan, r1, r2);
  unsigned int gout = map(elapsed_time, 0, timespan, g1, g2);
  unsigned int bout = map(elapsed_time, 0, timespan, b1, b2);
  solidColor(strip.Color(rout, gout, bout));
  strip.show();
}


void solidColor(uint32_t color){
  for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, color);
}
