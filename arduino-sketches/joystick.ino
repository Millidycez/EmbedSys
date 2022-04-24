#define joyX A0
#define joyY A1
int x, y;
void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
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

void printDirection(){
    print(_getDir(_getIntDir()));
}
void printValues(int x, int y){
    String output = "";
    output += x;
    output += ", ";
    output += y;
    print(output);
}

void ledOn(){
  if (_getIntDir() == 3){
     digitalWrite(8, HIGH);
     print("LED turned ON");
  }
}

void ledOff(){
  if (_getIntDir() == 4){
     digitalWrite(8, LOW);
     print("LED turned OFF");
  }
}


void loop() {
  x = analogRead(joyX);
  y = analogRead(joyY);
  printDirection();
  printValues(x,y);
  ledOn();
  ledOff();
  Serial.print("\r\n");
  delay(100);
}