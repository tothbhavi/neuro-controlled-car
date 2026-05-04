#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";

int ENA = 5, ENB = 6;
int IN1 = 8, IN2 = 7, IN3 = 4, IN4 = 3;
int speedVal = 120;
unsigned long moveStart = 0;
int moveDuration = 5000;
char state = 'S';

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, address);
  radio.startListening();
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  Serial.println("Car Ready");
}

void loop() {
  if (radio.available()) {
    char cmd;
    radio.read(&cmd, sizeof(cmd));
    state = cmd;
    moveStart = millis();
    Serial.print("Received: ");
    Serial.println(state);
  }
  if (state == 'F') forward();
  if (state == 'B') backward();
  if (millis() - moveStart >= moveDuration) {
    stopCar();
    state = 'S';
  }
}

void forward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
