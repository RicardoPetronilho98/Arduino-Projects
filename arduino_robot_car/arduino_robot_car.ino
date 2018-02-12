#define UP        765
#define RIGHT     49725
#define DOWN      8925
#define LEFT      45270


#include <IRremote.h>
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

// defines pins numbers
const int trigPin = A3;
const int echoPin = A2;
long duration;
int distance;

// defines pins numbers
const int trigPin2 = A5;
const int echoPin2 = A4;
long duration2;
int distance2;

int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int frontLed = 4;
int vel = 200; // Velocidade dos motores (0-255)
char estado = 's'; // inicia detenido

unsigned long currentMillis, previousMillis; 
unsigned long interval = 500;
//int start = 1;

void setup() { 
  
  Serial.begin(9600);
  
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(frontLed, OUTPUT);
  digitalWrite(frontLed, HIGH);
  
  irrecv.enableIRIn(); // start the receiver

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
} 

void loop() { 

  /*if (irrecv.decode(&results)){

    unsigned int value = results.value;

    Serial.println(value);

    if (value == UP || value == 32924) estado = 'f';
    else if (value == DOWN || value == 65440) estado = 'b';
    else if (value == LEFT || value == 33405) estado = 'l';
    else if (value == RIGHT || value == 1594) estado = 'r';
    else estado = 's';

    irrecv.resume(); //receive the next value
  }*/

  //currentMillis = millis(); 
  
  if (Serial.available() > 0) estado = Serial.read();

  /* girar automaticamente:
  if (estado == 'r' && start == 1){

    previousMillis = 0;
    start = 0;
  }
   */

  //countMillis();
  
  atualizaEstado();  

  atualizaDistancia();
  atualizaDistancia2();
}

void atualizaDistancia(){

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);  
  
  if (distance < 30 && estado == 'f') estado = 's';
}


void atualizaDistancia2(){

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echoPin2, HIGH);
  
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance2: ");
  Serial.println(distance2);  
  
  if (distance2 < 30 && estado == 'f') estado = 's';
}

/*
void countMillis(){

  if(currentMillis - previousMillis > interval){
    
    previousMillis = currentMillis;
    estado = 's';
  }

}
*/

void atualizaEstado(){

  if (estado == 's'){ // stop

    //Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, 0); 
    analogWrite(derA, 0); 
    analogWrite(izqA, 0); 
  
  }
  
  if (estado == 'r'){ // right
    
    //Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, 0); 
    analogWrite(derA, vel); 
    analogWrite(izqA, vel); 
  }
  
  if (estado == 'b'){ // back
    
    //Serial.println(estado);
    analogWrite(derB, vel); 
    analogWrite(izqB, 0); 
    analogWrite(derA, 0); 
    analogWrite(izqA, vel); 
  }
  
  if (estado == 'f'){ // foward
    
    //Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, vel);
    analogWrite(izqA, 0);
    analogWrite(derA, vel); 
  } 
  
  if (estado == 'l'){ // left
    
    //Serial.println(estado);
    analogWrite(derA, 0); 
    analogWrite(izqA, 0);
    analogWrite(derB, vel); 
    analogWrite(izqB, vel); 
  }

  if (estado == 'z'){ // acende led

    digitalWrite(frontLed, HIGH);
    
  }

  if (estado == 'x'){ // apaga led

    digitalWrite(frontLed, LOW);
  }
  
}

