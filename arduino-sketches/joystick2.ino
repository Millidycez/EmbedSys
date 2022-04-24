#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


#define joyX A0
#define joyY A1

int x, y;
bool LEDON = true;
String disp = "";
String oldDisp = "";


void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
}

int _getIntDir(){
  bool yRange = (y >= 450 && y <= 650);
  bool xRange = (x >= 450 && x <= 650);
  if (x <= 10 && yRange){
      return 1;
  }
  else if (x >= 1010 && yRange){
    return 2;
  }
  else if(y <= 10 && xRange){
    return 3;
  }
  else if(y >= 1010 && xRange){
    return 4;
  }
  else{
    return 0;
  }
}

String _getDir(int dir){
  switch (dir){
     case 1:
     return "Left";
      break;
      
     case 2:
     return "Right";
      break;
      
     case 3:
     return "Up";
      break;
     case 4:
     return "Down";
      break;
     default:
      return "Init";
  }
}
void print(String str){
  Serial.print(str);
}

String printDirection(){
    String output = _getDir(_getIntDir());
    print(output);
    return output;
}
void printValues(int x, int y){
    String output = "";
    output += x;
    output += ", ";
    output += y;
    print(output);
}

void ledOn(){
  if (_getIntDir() == 4){
    if (!LEDON){
     digitalWrite(8, HIGH);
     print("LED turned ON");
     LEDON = true;
    }
    else{
      digitalWrite(8, LOW);
      print("LED turned OFF");
      LEDON = false;
    }
  }
}


void loop() {
  x = analogRead(joyX);
  y = analogRead(joyY);
  disp = printDirection();
  if (disp != oldDisp){
    print("\n ---- DIR CHANGED ----");
    lcd.clear();
    lcd.print(disp);
    oldDisp = disp;
  }
  printValues(x,y);
  ledOn();
  Serial.print("\r\n");
  delay(100);
}