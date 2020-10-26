#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
// Note: For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

uint32_t Red = pixels.Color(127, 0, 0);
uint32_t RedOrange = pixels.Color(127, 30, 0);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(50);
  pixels.show(); // Initialise all pixels to off
}

void loop() { 
  // This loop starts with a red ring and then fades through to an orange/red colour
  for (int i = 0; i <= 30; i = i + 2) {
    setRingColor(pixels.Color(127, i, 0), 50); // Set the ring colour and wait for 50ms
  }
  // Now go back to the original red colour
  for (int i = 28; i >= 0; i = i - 2){
    setRingColor(pixels.Color(127, i, 0), 50); // Set the ring colour and wait for 50ms
  }
  delay(500);  
  clearPixelRing();
  delay(1000);
  // An alternative to this is to slowly fill the ring with colour using colour wipe
  // with no delay in between each colour wipe as there was between each set ring colour
  for (int i = 0; i <= 30; i = i + 6){
    colorWipe(pixels.Color(127, i, 0), 50);
  }
  for (int i = 28; i >= 0; i = i - 7){
    colorWipe(pixels.Color(127, i, 0), 50);
  }  
  colorWipe(pixels.Color(0, 127, 0), 100); // Wipe to green
  // Fade to black
  for(int i = 128; i > 0; i = i - 4){
    setRingColor(pixels.Color(0, i, 0), 50);
  }
  // Go from black to a medium green colour
  for (int i = 0; i < 127; i = i + 4){
    setRingColor(pixels.Color(0, i ,0), 50);
  }
  // and then back to black
  for(int i = 128; i > 0; i = i - 4){
    setRingColor(pixels.Color(0, i, 0), 50);
  }
  delay(1000);
}

// Fill the dots one after the other with a color and a wait between each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, c);
    pixels.show();
    delay(wait);
  }
}

// Set the entire ring to a particular colour and displays it for wait milliseconds
void setRingColor(uint32_t c, uint8_t wait){
    for(int i =0; i < pixels.numPixels(); i = i + 1){
      pixels.setPixelColor(i, c);
    }
    pixels.show();
    delay(wait);
}
// Clears the pixel ring.
void clearPixelRing(){
  setRingColor(pixels.Color(0, 0, 0), 0);
  pixels.show();
}

