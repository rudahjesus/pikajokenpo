#include <Servo.h>
#include <Ultrasonic.h>

// Definindo os pinos
const int trigPin = 5;
const int echoPin = 6;
const int servo1Pin = 9;
const int servo2Pin = 10;
const int servo3Pin = 11;

// Criando objetos para os servos
Servo servo1; //papel
Servo servo2; //pedra
Servo servo3; //tesoura

// Posições originais dos servos (0 graus)
int originalPos = 0;

void setup() {
  // Inicializando a comunicação serial
  Serial.begin(9600);
  
  // Configurando os pinos do sensor ultrassônico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Anexando os servos aos pinos
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  
  // Posicionando os servos na posição inicial
  servo1.write(originalPos);
  servo2.write(originalPos);
  servo3.write(originalPos);
  
  // Espera para estabilização
  delay(1000);
}

void loop() {
  // Medindo a distância
  long duration, distance;
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2; // Convertendo para cm
  
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Verificando se um objeto está a 7 cm ou menos
  if (distance <= 15 && distance > 10) {
    // Selecionando um servo aleatório
    int randomServo = random(1, 4); // Gera número entre 1 e 3
    
    Serial.print("Acionando servo ");
    Serial.println(randomServo);
    
    // Movendo o servo selecionado para 30 graus
    switch(randomServo) {
      case 1:
        servo1.write(45);
        break;
      case 2:
        servo2.write(45);
        break;
      case 3:
        servo3.write(60);
        break;
    }
    
    // Espera de 2 segundos
    delay(2000);
    
    // Retornando o servo para a posição original
    switch(randomServo) {
      case 1:
        servo1.write(originalPos);
        break;
      case 2:
        servo2.write(originalPos);
        break;
      case 3:
        servo3.write(originalPos);
        break;
    }
    
    // Pequena pausa para evitar múltiplas leituras do mesmo objeto
    delay(500);
  }
  
  // Pequeno atraso entre leituras
  delay(100);
}
