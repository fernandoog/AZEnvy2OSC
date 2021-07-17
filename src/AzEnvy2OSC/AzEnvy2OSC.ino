#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <MQ2.h>
#include <SHT3x.h>

//Wifi
char ssid[] = "HOUSE";          // your network SSID (name)
char pass[] = "wifiwifiwifi1992";                    // your network password
WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP

//OSC
const IPAddress outIp(192, 168, 43, 1);     // remote IP of your computer
const unsigned int outPort = 8000;          // remote port to receive OSC
const unsigned int localPort = 9000;        // local port to listen for OSC packets (actually not used for sending)

//Sensors
//change this with the pin that you use
int pin = A0;
int lpg, co, smoke;
SHT3x sht3x;
MQ2 mq2(pin);

void setup() {

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
#ifdef ESP32
  Serial.println(localPort);
#else
  Serial.println(Udp.localPort());
#endif


  //Serial
  Serial.begin(115200);

  //Sensors
  sht3x.Begin();
  mq2.begin();
}

void loop() {

  OSCMessage msg("/azenvy/sensors");

  //Load data
  sht3x.UpdateData();
  float* values = mq2.read(false); //set it false if you don't want to print the values in the Serial

  //sht3x
  msg.add(sht3x.GetTemperature()); //Celsius
  msg.add(",");
  msg.add(sht3x.GetRelHumidity()); //
  msg.add(",");
  msg.add(sht3x.GetAbsHumidity()); //Torr by default
  msg.add(",");
  msg.add(sht3x.GetAbsHumidity(SHT3x::psi)); //Torr by default
  msg.add(",");
  msg.add(sht3x.GetAbsHumidity(SHT3x::Pa)); //Torr by default
  msg.add(",");
  msg.add(sht3x.GetAbsHumTolerance(SHT3x::mH2O));
  msg.add(",");

  //MQ2
  msg.add(values[0]); //LPG in ppm
  msg.add(",");
  msg.add(values[1]); //CO in ppm
  msg.add(",");
  msg.add(values[2]); //SMOKE in ppm

  //OSC
  Udp.beginPacket(outIp, outPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();

  delay(500);
}
