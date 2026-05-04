#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);
const byte address[6] = "00001";
int sensorPin = A0;

float filteredSignal = 0;
float prevSignal = 0;
float alpha = 0.3;
float threshold = 25;
unsigned long lastBlink = 0;
int blinkCount = 0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);
  radio.stopListening();
  Serial.println("Neuro ready");
}

void loop() {
  int raw = analogRead(sensorPin);
  float centered = raw - 512;
  filteredSignal = filteredSignal + alpha * (centered - filteredSignal);
  float spike = filteredSignal - prevSignal;
  prevSignal = filteredSignal;
  Serial.print("Signal: ");
  Serial.println(spike);
  delay(40);

  if (spike > threshold && millis() - lastBlink > 400) {
    lastBlink = millis();
    blinkCount++;
    delay(350);
    if (blinkCount == 1) {
      char cmd = 'F';
      radio.write(&cmd, sizeof(cmd));
      Serial.println("FORWARD");
    }
    if (blinkCount == 2) {
      char cmd = 'B';
      radio.write(&cmd, sizeof(cmd));
      Serial.println("BACKWARD");
      blinkCount = 0;
    }
  }
}
