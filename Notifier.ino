/*
 * Если темпиратура находится в диапазоне от 16 до 25 градусов
 * То всё ок.
 * В противном случае включить сирену и светодиод
 * 
 * СанПиН 2.2.4.548-96
*/

//*******Library*******
#include <TroykaDHT.h>
#include <TroykaMQ.h>
#include <QuadDisplay2.h>
//*******Library*******

//*******Pins*******
#define PIN_MQ135 A0
#define LED_PIN 4
#define BUZZER_PIN 3
//*******Pins*******

//*******Object*******
DHT dht(2, DHT11);
MQ135 mq135(PIN_MQ135);
QuadDisplay qd(9);
//*******Object*******

int dhtTC, dhtHU, mqCO; //*******Variables*******

void setup()
{
  dht.begin();
  qd.begin();
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
  mq135.calibrate(25.11);
  dht.read();
  //*******ReadingData*******
  dhtTC = dht.getTemperatureC();
  dhtHU = dht.getHumidity();
  mqCO = mq135.readCO2();
  //*******ReadingData*******
  
  if(dhtTC < 16 && dhtHU < 15)
  {
    digitalWrite(LED_PIN, HIGH);
    qd.displayTemperatureC(dhtTC);
    delay(3000);
    digitalWrite(LED_PIN, LOW);
    qd.displayHumidity(dhtHU);
    delay(3000);
  }
  else if (dhtTC >25 && dhtHU > 75)
  {
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
    
    if(mqCO>1199)
    {
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
  }
  else
  {
    //*******OutputOfVariablesToTheDisplay*******
    qd.displayTemperatureC(dhtTC);
    delay(3000);
    qd.displayHumidity(dhtHU);
    delay(3000);
    qd.displayInt(mqCO);
    delay(3000);
    //*******OutputOfVariablesToTheDisplay*******
  }
}
