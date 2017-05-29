#include "Adafruit_HT1632.h"

#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

#define LR_IN   5
#define UD_OUT  4

#define UD_MID 511
#define RL_MID 511

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

uint16_t cursor_tlc_x = 7;
uint16_t cursor_tlc_y = 7;
float conv_x = 0;
float conv_y = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);

  for (uint8_t y = 0; y < matrix.height(); y++) {
    for (uint8_t x = 0; x < (matrix.width() / 6); x++) {
      matrix.setPixel(x, y);
    }
  }
  for (uint8_t y = 0; y < matrix.height(); y++) {
    for (uint8_t x = (5 * matrix.width() / 6); x < matrix.width(); x++) {
      matrix.setPixel(x, y);
    }
  }
  matrix.writeScreen();

  //function for target
}

void loop() {
  // put your main code here, to run repeatedly:

  //matrix.clearScreen();
  //matrix.clrPixel(uint8_t(cursor_x/16)+11,uint8_t(cursor_y/16)-7);
  matrix.clrPixel(float(cursor_tlc_x/48),float(cursor_tlc_y/48));
  
  cursor_tlc_x = analogRead(5);

  cursor_tlc_y = analogRead(4);
  Serial.print("L/R: " );
  Serial.println(float(cursor_tlc_x/48));
  Serial.print("U/D: ");
  Serial.println(float(cursor_tlc_y/48));
  
  matrix.setPixel(float(cursor_tlc_x/48),float(cursor_tlc_y/48));
  //newTarget();
  matrix.writeScreen();
  delay(33);
}

