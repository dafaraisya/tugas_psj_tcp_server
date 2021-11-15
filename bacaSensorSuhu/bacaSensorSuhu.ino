#define USE_SERIAL Serial
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4 //pin D2 nodemcu
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire); // Pass the oneWire reference to Dallas Temperature.

int getSensor(){
  int Celcius=0;
  sensors.requestTemperatures();
  Celcius=sensors.getTempCByIndex(0);
  return Celcius;
}

void setup() {
  USE_SERIAL.begin(115200);
  for(uint8_t t = 3; t > 0; t--) {
    USE_SERIAL.flush();
    delay(500);
  }

}

void loop() {
  Serial.write(1);
  Serial.write(getSensor());
  delay(1000);
}
