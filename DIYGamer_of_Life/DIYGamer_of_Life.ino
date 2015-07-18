/* http://opensource.org/licenses/Artistic-2.0

https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

Any live cell with fewer than two live neighbours dies, as if caused by under-population.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overcrowding.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.


  (c) Austin & Drew David, 2015
*/


// Include the DIY Gamer library
#include <Gamer.h>

// Make a copy of the library
Gamer gamer;

#define STARTING_CELLS 10
#define MAX_X 7
#define MAX_Y 7

// Animation code copied from our Animation Generator app.
#define NUMFRAMESIMAGES 4
byte images[NUMFRAMESIMAGES][8] = {
  {
    B00011000,
    B00111100,
    B01111110,
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000  }
  ,

  {
    B00010000,
    B00110000,
    B01110000,
    B11111111,
    B11111111,
    B01110000,
    B00110000,
    B00010000  }
  ,

  {
    B00001000,
    B00001100,
    B00001110,
    B11111111,
    B11111111,
    B00001110,
    B00001100,
    B00001000  }
  ,

  {
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11111111,
    B01111110,
    B00111100,
    B00011000  }
};


byte neighbors[MAX_X+1][MAX_Y+1];


void setup() {
  Serial.begin(115200);
  
  // Start Gamer!
  gamer.begin();
  
  seedLife();
}


void loop() {
  if(gamer.isPressed(START)) {
    reset();
  }

  live(true);
  checkKeypad();
  
  // blink the cursor
  for (byte i = 0; i < 5; i++) {
    intervene(-1);
    
    gamer.updateDisplay();
    delay(100);
  }
}


void reset() {
  gamer.clear();
  seedLife();
}


void seedLife() {
  int i;
  
  randomSeed(gamer.ldrValue());
  for (i = 0; i < STARTING_CELLS; i++) {
    gamer.display[random(0,MAX_X+1)][random(0,MAX_Y+1)] = HIGH;
  }
}


void checkKeypad() {
  byte dir;
  // this is stupid
  for (dir = UP; dir <= DOWN; dir++) {
    if (gamer.isPressed(dir)) {
      Serial.print("press: ");
      Serial.println(dir);
      intervene(dir);
      return;
    }
  }
}


void intervene(int dir) {
  static int x = 3;
  static int y = 3;
  
  if (dir == -1) {
    // secret "blink"
    for (byte i = 0; i < 2; i++) {
      gamer.display[x][y] = !gamer.display[x][y];
      gamer.updateDisplay();
      delay(50);
    }
    return;
  } 
  
  if (dir == UP) {
    y = max(0, y - 1);
  } else if (dir == DOWN) {
    y = min(y+1, MAX_Y);
  } else if (dir == LEFT) {
    x = max(0, x - 1);
  } else if (dir == RIGHT) {
    x = min(x+1, MAX_X);
  }
  
  Serial.print("intervening: ");
  Serial.print(x);
  Serial.print(",");
  Serial.println(y);
  
  gamer.display[x][y] = HIGH;
}


void live(bool freals) {
  countNeighbors();
  
  int x, y;
  for (x = 0; x <= MAX_X; x++) {
    for (y = 0; y <= MAX_Y; y++) {
      liveAt(x, y, freals);
    }
  }
}


void liveAt(int x, int y, bool freals) {
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  
  Serial.print(gamer.display[x][y] ? " (live)" : " (dead)");
//  gamer.display[x][y] = !gamer.display[x][y];
  Serial.print(" has ");
  Serial.print(neighbors[x][y]);
  Serial.print(" neighbors;");
  
  if (gamer.display[x][y] == HIGH) {
    if (neighbors[x][y] < 2 || neighbors[x][y] > 3) {
      if (freals) gamer.display[x][y] = LOW;
      Serial.print(" dies.");
    }      
  } else { // LOW
    if (neighbors[x][y] == 3) {
      if (freals) gamer.display[x][y] = HIGH;
      Serial.print(" born.");
    }
  }
  Serial.println();
}


bool cellIsActive(int x, int y) {
  if (x >= 0 && y >= 0 && x <= MAX_X && y <= MAX_Y) {
    return (gamer.display[x][y] == HIGH);
  } 
    
  // FALLTHROUGH
  return 0;
}


void countNeighbors() {
  int x, y;
  for (x = 0; x <= MAX_X; x++) {
    for (y = 0; y <= MAX_Y; y++) {
      neighbors[x][y] = numNeighbors(x,y);
      Serial.print(neighbors[x][y]);
      Serial.print(",");
    }
    Serial.println();
  }
}


// returns the number of neighbors to cell (x,y)
byte numNeighbors(int x, int y) {
  int ecks, why;
  byte myNeighbors = 0;
  
  for (ecks = x-1; ecks <= x+1; ecks ++) {
    for (why = y-1; why <= y+1; why ++) {
      if (cellIsActive(ecks,why)) {
        myNeighbors ++;
      }
    }
  }
  
  // uncount myself
  if (cellIsActive(x,y)) {
    myNeighbors --;
  }
  
  return myNeighbors;
}

