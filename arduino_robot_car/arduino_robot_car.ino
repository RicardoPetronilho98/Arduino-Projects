// defines pins numbers
const int trigPin = A2;
const int echoPin = A3;
long duration;
int distance;
unsigned long interval1 = 2;
boolean A_1 = false;
unsigned long interval2 = 10;
boolean A_2 = false;

// defines pins numbers
const int trigPin2 = A5;
const int echoPin2 = A4;
long duration2;
int distance2;
boolean B_1 = false;
boolean B_2 = false;

int izqA = 5;
int izqB = 6;
int derA = 9;
int derB = 10;
int frontLed = 4;
int vel = 255; // Velocidade dos motores (0-255)
char estado = 's'; // inicia detenido

void setup() {

  Serial.begin(9600);

  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(frontLed, OUTPUT);
  digitalWrite(frontLed, LOW);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
}

unsigned long previousMicros;
unsigned long currentMicros;
unsigned long temporaldistance;


void loop() {

  currentMicros = micros();
  temporaldistance = currentMicros - previousMicros;
  
  if ( temporaldistance >= interval1 || temporaldistance >= interval2 ){ // 2 microseconds || 10 microseconds

    if (temporaldistance >= interval1) A_1 = B_1 = true;
    if (temporaldistance >= interval2) A_2 = B_2 = true;
    
    previousMicros = currentMicros;
  }
  
  if (Serial.available() > 0) estado = Serial.read();

  atualizaEstado();

  atualizaDistancia();
  atualizaDistancia2();
}


void atualizaDistancia() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  
  if ( A_1 ){

    A_1 = false;

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);

    if ( A_2 ){

      A_2 = false;
      
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
    }
  }

  // Calculating the distance
  distance = duration * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 30 && estado == 'f') estado = 's';
}


void atualizaDistancia2() {

  // Clears the trigPin
  digitalWrite(trigPin2, LOW);
  
  if ( B_1 ){

    B_1 = false;

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin2, HIGH);
    
    
      if ( B_2 ){

        B_2 = false;
        
        digitalWrite(trigPin2, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration2 = pulseIn(echoPin2, HIGH);
      }
  }

  // Calculating the distance
  distance2 = duration2 * 0.034 / 2;

  // Prints the distance on the Serial Monitor
  Serial.print("Distance2: ");
  Serial.println(distance2);

  if (distance2 < 30 && estado == 'f') estado = 's';
}


void atualizaEstado() {

  if (estado == 's' || estado == 'S') { // stop

    //Serial.println(estado);
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);

  }

  if (estado == 'b' || estado == 'B') { // right

    //Serial.println(estado);
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, vel);
    analogWrite(izqA, vel);
  }

  if (estado == 'r' || estado == 'R') { // back

    //Serial.println(estado);
    analogWrite(derB, vel);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);
    analogWrite(izqA, vel);
  }

  if (estado == 'l' || estado == 'L') { // foward

    //Serial.println(estado);
    analogWrite(derB, 0);
    analogWrite(izqB, vel);
    analogWrite(izqA, 0);
    analogWrite(derA, vel);
  }

  if (estado == 'f' || estado == 'F') { // left

    //Serial.println(estado);
    analogWrite(derA, 0);
    analogWrite(izqA, 0);
    analogWrite(derB, vel);
    analogWrite(izqB, vel);
  }

  if (estado == 'W') { // acende led

    digitalWrite(frontLed, HIGH);

  }

  if (estado == 'w') { // apaga led

    digitalWrite(frontLed, LOW);
  }

}

