#define spacing 2750
#define rate 100
#define shortPause 100

int ledPin = 12;

int arrayDelay = 5000;

int val = 0;

byte a[4];

const int fan1In = 10;
const int fan1Out = 11;
const int fan2In = 6;
const int fan2Out = 9;
const int fan3In = 3;
const int fan3Out = 5;

int fanInArray[] = {fan1In, fan2In, fan3In};
int fanOutArray[] = {fan1Out, fan2Out, fan3Out};

//Timing element
long timer;

//set which fan is on
bool input = true;


void setup()  {
  Serial.begin(9600);
  Serial.setTimeout(50);
  pinMode(ledPin, OUTPUT);
  pinMode(fan1In, OUTPUT);
  pinMode(fan1Out, OUTPUT);
  pinMode(fan2In, OUTPUT);
  pinMode(fan2Out, OUTPUT);
  pinMode(fan3In, OUTPUT);
  pinMode(fan3Out, OUTPUT);
}

void loop()  {
  breath();
} 

void serialEvent(){
  val = Serial.read();
  for (int i=0; i < 3; i++){
     a[i] = Serial.read(); 
  }
  int fanSpeed =4 * (a[0] * 100 + a[1] * 10 + a[2]);

  if (val == '1'){
      digitalWrite(ledPin, HIGH);
      for(int j = 0; j < 3; j++){
         analogWrite(fanInArray[j], fanSpeed);
         analogWrite(fanOutArray[j], 0);
      } 
  }
  else if (val == '0'){
      digitalWrite(ledPin, HIGH);
      for(int j = 0; j < 3; j++){
         analogWrite(fanInArray[j], 0);
         analogWrite(fanOutArray[j], fanSpeed);
      } 
  }
  else if (val =='A'){
      digitalWrite(ledPin, LOW);
      for(int j = 0; j < 3; j++){
         analogWrite(fanOutArray[j], 0);
         analogWrite(fanInArray[j], 0);
      } 
  }
}

void breath(){
  if((millis() - timer) > spacing){
     timer = millis();
     if (input){
        in();
     }
     else{
       out();
     }
  } 
}

void in(){
    Serial.println("IN");
    for(int j = 0; j < 3; j++){
         analogWrite(fanOutArray[j], 0);
         analogWrite(fanInArray[j], 1023);
    }
    input = false;
}


void out(){  
    Serial.println("OUT");
    for(int j = 0; j < 3; j++){
         analogWrite(fanOutArray[j], 1023);
         analogWrite(fanInArray[j], 0);
    }
    input = true;    
}
