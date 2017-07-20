// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>
#define PIN 0
#define NUM_PIXELS 4

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, PIN);
uint8_t  mode   = 0, // Current animation effect
         offset = 0; // Position of lights
uint32_t color  = 0xff0000; // Start red
uint32_t prevTime;
uint32_t brightness;

void setup() {
  pixels.begin();
  pixels.setBrightness(60); // 1/3 brightness
  prevTime = millis();
}

void loop() {
  uint8_t  i;
  uint32_t t;
  
  switch(mode) {
   case 0: // sparkles
    twinkleRand();
    break;
   case 1: // Spinny
    spinny();
    break;
   case 2: // get slowly brighter
    fade();
    break;
   case 3: //
    randomSpark(); // Random sparks - just one LED on at a time!
    break;
   case 4:
    powerup(); // turn the lights on one at a time in a row
    break;
  }
  t = millis();
  if((t - prevTime) > 4000) {      // Every 4 seconds...
    mode++;                        // Next mode
    if(mode > 4) {                 // End of modes?
      mode = 0;                    // Start modes over
      color >>= 8;                 // Next color R->G->B
      if(!color) color = 0xff0000; // Reset to red
      brightness = 0;
    }
    for(i=0; i<8; i++) pixels.setPixelColor(i, 0);
    prevTime = t;
  }
}

void randomSpark(){
  pixels.setBrightness(40); // 1/3 brightness
    int i = random(7);
    pixels.setPixelColor(i, color);
    pixels.show();
    delay(100);
    pixels.setPixelColor(i, 0);
}

void spinny(){
  for(int i=0; i<8; i++) {
      uint32_t c = 0;
      if(((offset + i) & 7) < 2) c = color;
      pixels.setPixelColor(i, c);
    }
    pixels.show();
    offset++;
    delay(100);
}

void fade(){

  for(int i=0; i<8; i++){

      pixels.setPixelColor(i, color);

    }

    pixels.setBrightness(brightness);

    brightness += 1;

    pixels.show();

    delay(16);

    for(int i=0; i<8; i++){

      pixels.setPixelColor(i, 0);

    }
}

void powerup(){ // one LED turns on at a time until they're all on.
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, color);
      pixels.show();
      delay(100);
  }
  for(int i=pixels.numPixels(); i>=0; i--) {
      pixels.setPixelColor(i, 0);
      pixels.show();
      delay(100);
  }
}

void twinkleRand() {
                // set background
                stripSet(0,0);
                // for each num
                for (int i=0; i<7; i++) {
                   pixels.setPixelColor(random(7),color);
                }
                pixels.show();
                delay(100);
}
 
// quickly set the entire strip a color
void stripSet(uint32_t c, uint8_t wait) {
  pixels.setBrightness(40);
  for(uint16_t i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, c);
  }
  // move the show outside the loop
  pixels.show();
  delay(wait);
}
