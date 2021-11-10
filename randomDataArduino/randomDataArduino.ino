long randomHeight;
long randomMoist1;
long randomMoist2;
long randomLight;

void setup()
{
  // initialize the serial port
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  randomHeight = random(0x20,0x29);
  Serial.write(101);
  Serial.write(0x82);
  Serial.write(randomHeight);
  delay(1000);
  
  randomMoist1 = random(0x60,0x69);
  randomMoist2 = random(0x0,0x9);
  Serial.write(102);
  Serial.write(randomMoist1);
  Serial.write(randomMoist2);
  delay(1000);
  
  randomLight = random(0x40,0x49);
  Serial.write(103);
  Serial.write(randomLight);
  Serial.write(0x00);
  delay(1000);
}
