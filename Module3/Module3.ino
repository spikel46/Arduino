#include "Adafruit_HT1632.h"

#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

#define BUTTON  5
#define LR_IN   5
#define UD_OUT  4

//#define UD_MID 249
//#define RL_MID 10

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

uint8_t target_tlc_x = 6;
uint8_t target_tlc_y = 0;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;
uint8_t buttonState = 0;

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
  /*Serial.print(target_x);
    Serial.print(target_y);*/
  //matrix.clearScreen();
  //matrix.clrPixel(uint8_t(cursor_x/16)+11,uint8_t(cursor_y/16)-7);
  cursor_x = analogRead(5);
  cursor_y = analogRead(4);
  //matrix.setPixel(uint8_t(cursor_x/16)+11,uint8_t(cursor_y/16)-7);
  movement();
  /*
  buttonState = digitalRead(BUTTON);
  if(buttonState == 0)
    Serial.print("True");
  */
  //newTarget();
  matrix.writeScreen();
  delay(1000);
}

void movement() {
  Serial.println(cursor_x);
  Serial.println(cursor_y);
  /*if(cursor_x>UD_MID)
    Serial.print("L");
  else
    Serial.print("R");
  if(cursor_y>RL_MID)
    Serial.println("D");
  else
    Serial.println("U");
  */
}

//clears old target, generates new target.
void newTarget() {

  //clears old
  for (uint8_t x = target_tlc_x; x < (target_tlc_x + 4); x++) {
    if ( (x - target_tlc_x) % 3 == 0 ) {
      for (uint8_t y = target_tlc_y; y < (target_tlc_y + 4); y++) {
        matrix.clrPixel(x, y);
      }
    }
    else {
      matrix.clrPixel(x, target_tlc_y);
      matrix.clrPixel(x, target_tlc_y + 3);
    }
  }
  matrix.writeScreen();

  delay(1000);
  target_tlc_y = random(0,13); //total-targetSize+1
  target_tlc_x = random(0,17);

  for (uint8_t x = target_tlc_x; x < (target_tlc_x + 4); x++) {
    if ( (x - target_tlc_x) % 3 == 0 ) {
      for (uint8_t y = target_tlc_y; y < (target_tlc_y + 4); y++) {
        matrix.setPixel(x, y);
      }
    }
    else {
      matrix.setPixel(x, target_tlc_y);
      matrix.setPixel(x, target_tlc_y + 3);
    }
  }
  matrix.writeScreen();
}

