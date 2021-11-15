#define USE_SERIAL Serial
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_BUS 4 //pin D2 nodemcu
//#define rainAnalog A0
//#define lightAnalog A0
//#define rainDigital D0
//int Value_D7;
//int Value_D8;
//int Pin_D7 = D7;
//int Pin_D8 = D8;

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
  //delay(1000);
//  Serial.print("nilai sensor suhu = ");
  //USE_SERIAL.println(getSensor());
  Serial.write(1);
  Serial.write(getSensor());
  delay(1000);
}
