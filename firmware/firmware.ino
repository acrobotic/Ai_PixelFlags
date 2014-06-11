#include <Adafruit_NeoPixel.h>

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

PROGMEM  prog_uchar flagTableR[]  = 
{
  //ARG
  50,50,50,50,50,50,50,50,
  50,50,50,50,50,50,50,50,
  255,255,255,200,200,255,255,255,
  255,255,255,200,200,255,255,255,
  50,50,50,50,50,50,50,50,
  50,50,50,50,50,50,50,50  
};
PROGMEM  prog_uchar flagTableG[]  = 
{
  //ARG
  117,117,117,117,117,117,117,117,
  117,117,117,117,117,117,117,117,
  255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,
  117,117,117,117,117,117,117,117,
  117,117,117,117,117,117,117,117  
};
PROGMEM  prog_uchar flagTableB[]  = 
{
  //ARG
  200,200,200,200,200,200,200,200,
  200,200,200,200,200,200,200,200,
  255,255,255,40,40,255,255,255,
  255,255,255,40,40,255,255,255,
  200,200,200,200,200,200,200,200,
  200,200,200,200,200,200,200,200  
};

enum { 
  ARG };

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(50);
}

void loop() {
  flagCycle(ARG, 50);
}

// Slightly different, this makes the rainbow equally distributed throughout
void flagCycle(uint8_t f, uint8_t wait) {
  uint16_t j;
  for(j=0; j<strip.numPixels(); j++) {
    strip.setPixelColor(j, getFlagColor(f, j));
  }
  strip.show();
  delay(wait);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

uint32_t getFlagColor(uint8_t f, uint8_t idx)
{
  uint8_t idx_mult;
  switch(f)
  {
    case ARG:
      idx_mult = 1;
      break;    
    default:
      break;
  }
  uint8_t r = pgm_read_byte(flagTableR + idx*idx_mult);
  uint8_t g = pgm_read_byte(flagTableG + idx*idx_mult);
  uint8_t b = pgm_read_byte(flagTableB + idx*idx_mult);
  Serial.print(r);
  Serial.print(g);
  Serial.println(b);
  return strip.Color(r, g, b);
}


