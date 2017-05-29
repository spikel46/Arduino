#include "Adafruit_HT1632.h"

#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

#define BUTTON  5
#define LR_IN   5
#define UD_OUT  4

#define CENTER_X 11
#define CENTER_Y 7

#define UD_MID 504
#define RL_MID 523

Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);

uint8_t target_tlc_x = CENTER_X;
uint8_t target_tlc_y = CENTER_Y;
int16_t cursor_tlc_x = CENTER_X;
int16_t cursor_tlc_y = CENTER_Y;
uint8_t buttonState = 0;

bool reset = true;

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
  
  if(reset){
    newTarget();
    reset = false;
  }
  clrBox();

  cursor_tlc_x = analogRead(5);

  //invert directions
  if(cursor_tlc_x <512)
    cursor_tlc_x = 1024 - cursor_tlc_x; 
  else
    cursor_tlc_x = 1024 - cursor_tlc_x;
  cursor_tlc_x=(cursor_tlc_x/48); 
    
  cursor_tlc_y = analogRead(4);
  cursor_tlc_y=(cursor_tlc_y/48);

  setBox();
  
  buttonState = digitalRead(BUTTON);
  if(buttonState == 0){
    if(cursor_tlc_x == (target_tlc_x+1) && cursor_tlc_y == (target_tlc_y+1))
      reset = true;     
  }

  refresh();
  
  matrix.writeScreen();
  delay(33);
}

void setBox(){
  cursor_tlc_x +=1;
  cursor_tlc_y -=3;
  if(cursor_tlc_x > 18)
    cursor_tlc_x = 18;
  if(cursor_tlc_x < 4)
    cursor_tlc_x = 4;
  if(cursor_tlc_y > 14)
    cursor_tlc_y = 14;
  if(cursor_tlc_y < 0)
    cursor_tlc_y = 0;
  matrix.setPixel(cursor_tlc_x,cursor_tlc_y);
  matrix.setPixel(cursor_tlc_x+1,cursor_tlc_y);
  matrix.setPixel(cursor_tlc_x,cursor_tlc_y+1);
  matrix.setPixel(cursor_tlc_x+1,cursor_tlc_y+1);
}

void clrBox(){
  matrix.clrPixel(cursor_tlc_x,cursor_tlc_y);
  matrix.clrPixel(cursor_tlc_x+1,cursor_tlc_y);
  matrix.clrPixel(cursor_tlc_x,cursor_tlc_y+1);
  matrix.clrPixel(cursor_tlc_x+1,cursor_tlc_y+1);
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

  target_tlc_y = random(0,13); //total-targetSize+1
  target_tlc_x = random(4,17);

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

void refresh(){

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
