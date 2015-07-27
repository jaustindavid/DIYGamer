#define BM_SIZE (BM_SIDE/8 * BM_SIDE)

class BitMatrix {
  private:
    byte width, height;
    byte data[BM_SIZE];
    bool printing;
    
    byte indexOf(byte x, byte y) {
      byte index;
      
      index = x/8 + y*(width/8);
      
      if (printing) {
        Serial.print("index(");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(") = ");
        Serial.println(index);
      }     
      return index;
    } // byte indexOf(x,y)
    
    
  public:
  
    void test(void) {
      printing = true;
      byte r = indexOf(0,0);
      r = indexOf(0,15);
      r = indexOf(15,0);
      r = indexOf(7,7);
      
      set(0,0, 1);
      get(0,0);
      set(0,0, 0);

      set(10,10, 1);
      get(10,10);
      
      set(10,10, 0);
      get(10,10);
      
      printing = false;
    }
    
    
    BitMatrix(void) {
      width = BM_SIDE;
      height = BM_SIDE;
      printing = false;
    }
    
    
    void reset(void) {
      for (byte i = 0; i < BM_SIZE; i++) {
        data[i] = 0;
      }
    }
    
   
    bool get(byte x, byte y) {
      byte b = data[indexOf(x,y)];
      byte pos = x % 8;
      bool value = bitRead(b, pos);
      
      if (printing) {
        Serial.print("get(");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(") = ");
        Serial.print(b);
        Serial.print(" <- ");
        Serial.println(value);
      }
      
      return value;
    }
    
    void set(byte x, byte y, bool value) {
      byte b = data[indexOf(x,y)];
      byte pos = x % 8;
      bitWrite(b, pos, value);
      
      if (printing) {
        Serial.print("set(");
        Serial.print(x);
        Serial.print(",");
        Serial.print(y);
        Serial.print(") = ");
        Serial.print(data[indexOf(x,y)]);
        Serial.print(" -> ");
        Serial.println(b);
      }
      
      data[indexOf(x,y)] = b;
    }
    
    void print() {
      for (byte j = 0; j < height; j++) {
        Serial.print("|");
        for (byte i = 0; i < width; i++) {
          Serial.print(get(i,j));
          Serial.print("|");
        }
        Serial.println();
      }
    }
};
