#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(64, PIN, NEO_GRB + NEO_KHZ800);


byte heart[] = {
  B00011000, 
  B00111100, 
  B01111110, 
  B11111111, 
  B11111111, 
  B11111111, 
  B11111111, 
  B01100110};




void setup() {
  pixels.begin();
  pixels.setBrightness(75); //To reduce power consumption
}

void clear() {
  for(int i=0;i<64;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
  }
}



void setPixelForColor(int row, int col, uint32_t color) {
  if ((row % 2) == 1){
    pixels.setPixelColor(row*8+(7-col), color); 
  } else {
    pixels.setPixelColor(row*8+col, color); 
  }
}


void drawShape(byte shape[], uint32_t color, boolean flash, int cycles, int delayTime) {
  for(int c = 0; c < cycles; c++) {
    for(int i=0;i<8;i++) {
      for(int j=0; j<8; j++) {
        if(bitRead(shape[i], j) == 1) {
          setPixelForColor(i, j, color);
        }
      }
    }
  
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayTime); // Delay for a period of time (in milliseconds).
  
    if (flash) {
      clear();
      pixels.show();
      delay(delayTime); 
    }
  }

  clear();
  pixels.show();
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}




void loop() {
  drawShape(heart, pixels.Color(255,0,0), true, 1, 150);
  drawShape(heart, pixels.Color(255,0,0), true, 1, 300);
  drawShape(heart, pixels.Color(255,0,0), true, 1, 150);
  drawShape(heart, pixels.Color(255,0,0), true, 1, 300);

}
