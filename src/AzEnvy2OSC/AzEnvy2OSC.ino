#include <MQ2.h>
#include <SHT3x.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <PolledTimeout.h>
#include <algorithm> // std::min


#ifndef STASSID
#define STASSID "HOUSE"
#define STAPSK  "wifiwifiwifi1992"
#endif

//Wifi
constexpr int port = 23;
WiFiServer server(port);
WiFiClient client;
constexpr size_t sizes [] = { 0, 512, 384, 256, 128, 64, 16, 8, 4 };
constexpr uint32_t breathMs = 200;
esp8266::polledTimeout::oneShotFastMs enoughMs(breathMs);
esp8266::polledTimeout::periodicFastMs test(2000);
int t = 1; // test (1, 2 or 3, see below)
int s = 0; // sizes[] index

//Sensors
//change this with the pin that you use
int pin = A0;
int lpg, co, smoke;
SHT3x sht3x;
MQ2 mq2(pin);

void setup(){
  Serial.begin(115200);
  Serial.println(ESP.getFullVersion());

  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  Serial.print("\nConnecting to ");
  Serial.println(STASSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("connected, address=");
  Serial.println(WiFi.localIP());

  server.begin();

  MDNS.begin("echo23");

        
  //Sensors
  sht3x.Begin();
  mq2.begin();
}

void loop(){
  
  //Wifi
   MDNS.update();
  
  //Load data
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
