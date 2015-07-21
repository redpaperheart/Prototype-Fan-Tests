#define spacing 2500
int val;
int ledPin = 12;

void setup()  {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()  {
   inout();
   //serial();
   if (val == '1'){
      digitalWrite(ledPin, HIGH); 
   }
   else{
      digitalWrite(ledPin, LOW); 
   }
   
} 


void inout(){
  analogWrite(11, 1023);
  analogWrite(10, 0);
  delay(spacing);
  analogWrite(11, 0);
  analogWrite(10, 1023);  
  delay(spacing);
}

void serial(){
   if (Serial.available()){
      val=Serial.read();
   } 
   
}
