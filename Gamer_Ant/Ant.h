
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
      init(random(0, BM_SIDE), random(0, BM_SIDE), random(0,4));
    }

    void walk(BitMatrix *board) {

      #ifdef DEBUGGING
        Serial.print("ant: ");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print("; dir=");
        Serial.println(dir);
      #endif
      
      if (board->get(x,y)) {
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
      
      board->set(x,y,!board->get(x,y));
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
          y = (y == 0 ? BM_SIDE - 1 : y - 1);
          break;
        case LEFT:
          x = (x == 0 ? BM_SIDE - 1 : x - 1);
          break;
        case DOWN:
          y = (y == BM_SIDE - 1 ? 0 : y + 1);
          break;
        case RIGHT:
          x = (x == BM_SIDE - 1 ? 0 : x + 1);
      }
    } // step()
};
