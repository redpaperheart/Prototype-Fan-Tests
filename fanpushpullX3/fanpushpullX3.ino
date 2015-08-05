#define spacing 3000
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

//select which behavior the fans are running on
//Breath is a steady in and out, variety has variation in the timing
//and demo ramps up each fan in order, then back down
void loop()  {
  breath();   
  //variety();
  //demo();
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
    analogWrite(fan1Out, 0);
    analogWrite(fan2Out, 0);
    analogWrite(fan3Out, 0);
    analogWrite(fan1In, 1023);
    analogWrite(fan2In, 1023);
    analogWrite(fan3In, 1023);
    input = false;
}


void out(){  
    Serial.println("OUT");
    analogWrite(fan1In, 0);
    analogWrite(fan2In, 0);
    analogWrite(fan3In, 0);
    analogWrite(fan1Out, 500);
    analogWrite(fan2Out, 500);
    analogWrite(fan3Out, 500);
    input = true;    
}



void variety(){
   for (int i = 0; i < 1001; i = i + rate){
     for(int j = 0; j < sizeof(fanInArray); j++){
       analogWrite(fanInArray[j], i);
       Serial.println(i);
       delay(shortPause);
     }
   }  
   delay(arrayDelay);
   
   for (int i = 1000; i > -1; i = i - rate){
      for(int j = 0; j < sizeof(fanInArray); j++){
       analogWrite(fanInArray[j], i);
       analogWrite(fanOutArray[j], 0);
       Serial.println(i);
       delay(shortPause);
     }
   }
  
   for (int i = 0; i < 1001; i = i + rate){
     for(int j = 0; j < sizeof(fanOutArray); j++){
       analogWrite(fanOutArray[j], i);
       Serial.println(i);
       delay(shortPause);
     }
   }  
   delay(arrayDelay);
   
   
   for (int i = 1000; i > -1; i = i - rate){
      for(int j = 0; j < sizeof(fanOutArray); j++){
       analogWrite(fanInArray[j], 0);
       analogWrite(fanOutArray[j], i);
       Serial.println(i);
       delay(shortPause);
     }
   }   
}

void demo(){
   for (int i=0; i < sizeof(fanInArray); i++){
      Serial.print(fanInArray[i]);
      Serial.println(" : IN");
      analogWrite(fanInArray[i], 1023);
      delay (20000);
      Serial.print(fanOutArray[i]);
      Serial.println(" : OUT");
      analogWrite(fanInArray[i], 0);
      analogWrite(fanOutArray[i], 1023);
      delay(20000);
      analogWrite(fanOutArray[i], 0);    
   } 
  
}

