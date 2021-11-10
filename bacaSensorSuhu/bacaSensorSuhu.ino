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

  delay(500); // Let the module self-initialize
  USE_SERIAL.begin(115200);
  //pinMode(Pin_D7,OUTPUT);
  //pinMode(Pin_D8,OUTPUT);
//  pinMode(A0,INPUT);
  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(500);
  }

}

void loop() {
  delay(1000);
  
//  digitalWrite(Pin_D7, HIGH); //Turn D7 On
//  delay(100); //Wait for sensor
//  Value_D7 = analogRead(0); //Read Analog pin as D7
//  digitalWrite(Pin_D7, LOW); //Turn D7 Off
  
  //Repeat for D8
//  digitalWrite(Pin_D8, HIGH); //Turn D8 On
//  delay(100); //Wait for sensor
//  Value_D8 = analogRead(0); //Read Analog pin as D8
//  digitalWrite(Pin_D8, LOW); //Turn D8 Off
//  delay(100); //Wait for sensor
  
  //Print the results to the serial monitor
//  Serial.print("nilai sensor hujan = ");
//  Serial.println(Value_D7);
//  Serial.print(" Nilai sensor cahaya = ");
//  Serial.println(Value_D8);
  Serial.print("nilai sensor suhu = ");
  USE_SERIAL.println(getSensor());
  Serial.write(101);
  Serial.write(getSensor());
  delay(1000);
}
