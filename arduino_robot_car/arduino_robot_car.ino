int izqA = 5; 
int izqB = 6; 
int derA = 9; 
int derB = 10; 
int frontLed = 3;
int vel = 175; // Velocidad de los motores (0-255)
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
} 

void loop() { 

  currentMillis = millis(); 
  
  if (Serial.available() > 0) estado = Serial.read();

  /* girar automaticamente:
  if (estado == 'r' && start == 1){

    previousMillis = 0;
    start = 0;
  }
   */

  //countMillis();
  
  atualizaEstado();  
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

    Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, 0); 
    analogWrite(derA, 0); 
    analogWrite(izqA, 0); 
  
  }
  
  if (estado == 'r'){ // right
    
    Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, 0); 
    analogWrite(derA, vel); 
    analogWrite(izqA, vel); 
  }
  
  if (estado == 'b'){ // back
    
    Serial.println(estado);
    analogWrite(derB, vel); 
    analogWrite(izqB, 0); 
    analogWrite(derA, 0); 
    analogWrite(izqA, vel); 
  }
  
  if (estado == 'f'){ // foward
    
    Serial.println(estado);
    analogWrite(derB, 0); 
    analogWrite(izqB, vel);
    analogWrite(izqA, 0);
    analogWrite(derA, vel); 
  } 
  
  if (estado == 'l'){ // left
    Serial.println(estado);
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

