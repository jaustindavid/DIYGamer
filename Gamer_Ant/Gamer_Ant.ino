/* http://opensource.org/licenses/Artistic-2.0

 An implementation (from memory) of Langston's Ant
 on the DIYGamer.

 (c) Austin David 2015


  up/down will speed up / slow down the animation
  start will reset (clear) the board.
  
*/


#define refresh 16

#undef DEBUGGING

#include <Gamer.h>

#define BM_SIDE 32
#include "BitMatrix.h"

#include "Ant.h"



Gamer gamer;
Ant ant;
BitMatrix board;

void setup() {
  #ifdef DEBUGGING
    Serial.begin(115200);
  #endif
  
  randomSeed(gamer.ldrValue());
  ant.init();
  gamer.begin();
  board.reset();
  board.print();
}


void loop() {
  #ifdef DEBUGGING
    Serial.println("step");
  #endif
  
  if (gamer.isPressed(START)) {
    board.reset();
  }
  
  for (byte i = 0; i < 4; i++) {
    if (checkViewport())
      updateDisplay();
    delay(refresh);
  }
  ant.walk(&board);
  updateDisplay();
  
  #ifdef DEBUGGING
    board.print();
  #endif
}


void printViewport(byte x, byte y) {
  #ifdef DEBUGGING
  Serial.print("Viewport: (");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.println(")");
  #endif
}


static int x = 0;
static int y = 0;
#define VIEWPORT 8 // i can see this many pixels


bool checkViewport() {
  bool updateMe = false;
  
  // (x, y) is the real offset of the viewport into the board
  
  if (gamer.isPressed(DOWN)) {
    y++;
    if (y >= BM_SIDE - VIEWPORT) { y = 0; }
    printViewport(x,y);
    updateMe = true;
  } else if (gamer.isPressed(UP)) {
    y--;
    if (y < 0) { y = BM_SIDE - VIEWPORT; } 
    printViewport(x,y);
    updateMe = true;
  } else if (gamer.isPressed(LEFT)) {
    x--;
    if (x < 0) { x = BM_SIDE - VIEWPORT; }
    printViewport(x,y);
    updateMe = true;
  } else if (gamer.isPressed(RIGHT)) {
    x++;
    if (x >= BM_SIDE - VIEWPORT) { x = 0; }
    printViewport(x,y);
    updateMe = true;
  }
  
  return updateMe;
} // void checkViewport(bool board[BOARD_SIZE][BOARD_SIZE]) 


void updateDisplay() {
  for (byte gamerX = 0; gamerX < VIEWPORT; gamerX ++) {
    for (byte gamerY = 0; gamerY < VIEWPORT; gamerY ++) {
      gamer.display[gamerX][gamerY] = board.get(x + gamerX, y + gamerY); 
    }
  }
  gamer.updateDisplay();
}
