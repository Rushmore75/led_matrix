#include <FAB_LED.h>

// Note that the platformio.ini file re-defines the serial rx buffer size.

const int NUM_LEDS = 144;
const int BUF_SIZE = NUM_LEDS * 3;

ws2812b<D,6> strip;
grb pixels[NUM_LEDS] = {};

void setup() {
  Serial.begin(9600);
  Serial.println("\nResetting!");
  
  strip.clear(NUM_LEDS);
}

// !! IMPORTANT !!
// Make sure this is fast enough that it can
// clear the 64 byte buffer faster than it is filled!
void on_serial() 
{
    
  // How many times have we read?
  static int read = 0;
  // should be non blocking
  int read_byte = Serial.read();
  
  int index = (int) read / 3;
  // the first, second, or third byte
  switch (read % 3)
  {
  case 0: // first
    pixels[index].r = read_byte;
    break;
  case 1: // second
    pixels[index].g = read_byte;
    break;
  default: // third
    pixels[index].b = read_byte;
    break;
  }
  
 // increment or loop
  if (read < BUF_SIZE-1) {
    read++;
  } else {
    strip.sendPixels(NUM_LEDS, pixels);
    read=0;
  }
}

void loop() {
  
  Serial.println(Serial.available());
  if (Serial.available() > 0) {
    // on_serial();
  }
  
}

