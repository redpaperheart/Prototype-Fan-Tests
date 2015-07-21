#define spacing 2750
#define rate 100
#define shortPause 100

int ledPin = 12;

int arrayDelay = 5000;

int microphone = A0;

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
  //variety();
  //analogWrite(fan3Out, 1023);
  //analogWrite(fan1In, 1023);
  //demo();
} 

//void serialEvent(){
//  val = Serial.read();
//  for (int i=0; i < 3; i++){
//     a[i] = Serial.read(); 
//  }
//  int fanSpeed =4 * (a[0] * 100 + a[1] * 10 + a[2]);
//
//  if (val == '1'){
//      digitalWrite(ledPin, HIGH);
//      for(int j = 0; j < 3; j++){
//         analogWrite(fanInArray[j], fanSpeed);
//         analogWrite(fanOutArray[j], 0);
//      } 
//  }
//  else if (val == '0'){
//      digitalWrite(ledPin, HIGH);
//      for(int j = 0; j < 3; j++){
//         analogWrite(fanInArray[j], 0);
//         analogWrite(fanOutArray[j], fanSpeed);
//      } 
//  }
//  else if (val =='A'){
//      digitalWrite(ledPin, LOW);
//      for(int j = 0; j < 3; j++){
//         analogWrite(fanOutArray[j], 0);
//         analogWrite(fanInArray[j], 0);
//      } 
//  }
//}

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



//void variety(){
//   for (int i = 0; i < 1001; i = i + rate){
//     for(int j = 0; j < sizeof(fanInArray); j++){
//       analogWrite(fanInArray[j], i);
//       Serial.println(i);
//       delay(shortPause);
//     }
//   }  
//   delay(arrayDelay);
//   
//   for (int i = 1000; i > -1; i = i - rate){
//      for(int j = 0; j < sizeof(fanInArray); j++){
//       analogWrite(fanInArray[j], i);
//       analogWrite(fanOutArray[j], 0);
//       Serial.println(i);
//       delay(shortPause);
//     }
//   }
//  
//   for (int i = 0; i < 1001; i = i + rate){
//     for(int j = 0; j < sizeof(fanOutArray); j++){
//       analogWrite(fanOutArray[j], i);
//       Serial.println(i);
//       delay(shortPause);
//     }
//   }  
//   delay(arrayDelay);
//   
//   
//   for (int i = 1000; i > -1; i = i - rate){
//      for(int j = 0; j < sizeof(fanOutArray); j++){
//       analogWrite(fanInArray[j], 0);
//       analogWrite(fanOutArray[j], i);
//       Serial.println(i);
//       delay(shortPause);
//     }
//   }   
//}
//
//void demo(){
//   for (int i=0; i < sizeof(fanInArray); i++){
//      Serial.print(fanInArray[i]);
//      Serial.println(" : IN");
//      analogWrite(fanInArray[i], 1023);
//      delay (20000);
//      Serial.print(fanOutArray[i]);
//      Serial.println(" : OUT");
//      analogWrite(fanInArray[i], 0);
//      analogWrite(fanOutArray[i], 1023);
//      delay(20000);
//      analogWrite(fanOutArray[i], 0);    
//   } 
//  
//}

