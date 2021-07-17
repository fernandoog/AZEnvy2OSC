#include <MQ2.h>
#include <SHT3x.h>

//change this with the pin that you use
int pin = A0;
int lpg, co, smoke;

SHT3x sht3x;
MQ2 mq2(pin);

void setup(){
  Serial.begin(9600);
  sht3x.Begin();
  mq2.begin();
}

void loop(){
  
  sht3x.UpdateData();
  float* values= mq2.read(false); //set it false if you don't want to print the values in the Serial

  //sht3x
  Serial.print(sht3x.GetTemperature()); //Celsius
  Serial.print(",");
  Serial.print(sht3x.GetRelHumidity()); //
  Serial.print(",");
  Serial.print(sht3x.GetAbsHumidity()); //Torr by default
  Serial.print(",");
  Serial.print(sht3x.GetAbsHumidity(SHT3x::psi)); //Torr by default
  Serial.print(",");
  Serial.print(sht3x.GetAbsHumidity(SHT3x::Pa)); //Torr by default
  Serial.print(",");
  Serial.print(sht3x.GetAbsHumTolerance(SHT3x::mH2O));
  Serial.print(",");

  //MQ2
  Serial.print(values[0]); //LPG in ppm
  Serial.print(",");
  Serial.print(values[1]); //CO in ppm
  Serial.print(",");
  Serial.print(values[2]); //SMOKE in ppm
  Serial.println();
  
  delay(1000);
}
