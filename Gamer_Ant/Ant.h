
class Ant {
  private:
    byte x, y, dir;
    void turn();
    
  public:
    Ant() {
      init();
    }
    
    void init(byte _x, byte _y, byte _dir) {
      x = _x;
      y = _y;
      dir = _dir;
    }
    
    void init() {
      init(random(0, MAX_X+1), random(0, MAX_Y+1), random(0,4));
    }

    void walk(Gamer* gamer) {
      // blink(gamer);

      #ifdef DEBUGGING
        Serial.print("ant: ");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print("; dir=");
        Serial.println(dir);
      #endif
      
      if (gamer->display[x][y]) {
        #ifdef DEBUGGING
          Serial.println("high");
        #endif
        turn(LEFT);
      } else {
        #ifdef DEBUGGING
          Serial.println("low");
        #endif
        turn(RIGHT);
      }
      
      gamer->display[x][y] = !gamer->display[x][y];
      step();
    }
    
    
  private:
  
    void turn(byte _dir) {
      if (_dir == LEFT) {
        switch(dir) {
          case UP: 
            dir = LEFT;
            break;
          case LEFT:
            dir = DOWN;
            break;
          case DOWN:
            dir = RIGHT;
            break;
          case RIGHT:
            dir = UP;
            break;
        }
      } else {
        switch(dir) {
          case UP: 
            dir = RIGHT;
            break;
          case RIGHT:
            dir = DOWN;
            break;
          case DOWN:
            dir = LEFT;
            break;
          case LEFT:
            dir = UP;
            break;
        }
      }
    } // turn(_dir)

    
    void step() {
      switch (dir) {
        case UP:
          y = (y == 0 ? MAX_Y : y - 1);
          break;
        case LEFT:
          x = (x == 0 ? MAX_X : x - 1);
          break;
        case DOWN:
          y = (y == MAX_Y ? 0 : y + 1);
          break;
        case RIGHT:
          x = (x == MAX_Y ? 0 : x + 1);
      }
    } // step()
    
    
    void blink(Gamer* gamer) {
      // byte color = gamer->display[x][y];
      
      // gamer->display[x][y] = LOW;
      for (byte i = 0; i < 4; i++) {
        gamer->display[x][y] = !gamer->display[x][y];
        gamer->updateDisplay();
        delay(100);
      }
      
      // gamer->display[x][y] = color;
    }
};
