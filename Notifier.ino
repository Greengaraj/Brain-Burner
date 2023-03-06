// Library
#include <TroykaDHT.h>
#include <TroykaMQ.h>
#include <QuadDisplay2.h>

// Pins
constexpr int MQ135_PIN = A0;
constexpr int LED_PIN = 4;
constexpr int BUZZER_PIN = 3;
constexpr int DHT_PIN = 2;
constexpr int QD_PIN = 9;

// Object
DHT dht(DHT_PIN, DHT11);
MQ135 mq135(MQ135_PIN);
QuadDisplay qd(QD_PIN);

// Variables
int dhtTC, dhtHU, mqCO;

void setup() {
  dht.begin();
  qd.begin();
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  mq135.calibrate(25.11);
  dht.read();
  // ReadingData
  dhtTC = dht.getTemperatureC();
  dhtHU = dht.getHumidity();
  mqCO = mq135.readCO2();
  
  if (dhtTC < 16 && dhtHU < 15) {
    digitalWrite(LED_PIN, HIGH);
    qd.displayTemperatureC(dhtTC);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    qd.displayHumidity(dhtHU);
    delay(3000);
  } else if (dhtTC > 25 && dhtHU > 75) {
    digitalWrite(LED_PIN, HIGH);
    qd.displayTemperatureC(dhtTC);
    tone(BUZZER_PIN, 4000);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    qd.displayHumidity(dhtHU);
    tone(BUZZER_PIN, 4000);
    delay(3000);
    digitalWrite(LED_PIN, HIGH);
    qd.displayInt(mqCO);
    tone(BUZZER_PIN, 4000);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    qd.displayClear();
    tone(BUZZER_PIN, 4000);
    delay(3000);
    
    if (mqCO > 1199) {
      digitalWrite(LED_PIN, HIGH);
      qd.displayTemperatureC(dhtTC);
      tone(BUZZER_PIN, 4000);
      delay(3000);
      digitalWrite(LED_PIN, LOW);
      qd.displayHumidity(dhtHU);
      tone(BUZZER_PIN, 4000);
      delay(3000);
      digitalWrite(LED_PIN, HIGH);
      qd.displayInt(mqCO);
      tone(BUZZER_PIN, 4000);
      delay(3000);
      digitalWrite(LED_PIN, LOW);
      qd.displayClear();
      tone(BUZZER_PIN, 4000);
      delay(3000);
    }
  } else {
    //OutputOfVariablesToTheDisplay
    qd.displayTemperatureC(dhtTC);
    delay(3000);
    qd.displayHumidity(dhtHU);
    delay(3000);
    qd.displayInt(mqCO);
    delay(3000);
  }
}
