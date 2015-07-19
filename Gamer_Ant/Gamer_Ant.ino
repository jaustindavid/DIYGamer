/* http://opensource.org/licenses/Artistic-2.0

 An implementation (from memory) of Langston's Ant
 on the DIYGamer.

 (c) Austin David 2015


  up/down will speed up / slow down the animation
  start will reset (clear) the board.
  
*/

#include <Gamer.h>

#define MAX_X 7
#define MAX_Y 7
#undef DEBUGGING

#include "Ant.h"

Gamer gamer;
Ant ant;
int refresh = 32;

void setup() {
  #ifdef DEBUGGING
    Serial.begin(115200);
  #endif
  randomSeed(gamer.ldrValue());
  ant.init();
  gamer.begin();
  resetBoard();
}


void loop() {
  #ifdef DEBUGGING
    Serial.println("step");
  #endif
  
  if (gamer.isPressed(START)) {
    resetBoard();
  }
  
  ant.walk(&gamer);
  gamer.updateDisplay();
  #ifdef DEBUGGING
    printBoard();
  #endif
  
  if (gamer.isPressed(DOWN)) {
    refresh = min(500, refresh * 2);
  } else if (gamer.isPressed(UP)) {
    refresh = max(0, refresh / 2);
  } 
  
  delay(refresh);
}


void resetBoard() {
  for (byte x = 0; x <= MAX_X; x++) {
    for (byte y = 0; y <= MAX_Y; y++) {
      gamer.display[x][y] = 0;// random(0,2);
    }
  }
}


void printBoard() {
  for (byte x = 0; x <= MAX_X; x++) {
    for (byte y = 0; y <= MAX_Y; y++) {
      Serial.print(gamer.display[x][y] ? "|x|" : "| |");
    }
    Serial.println();
  }
}
