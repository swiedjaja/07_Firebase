/*
Google Firebase demo: how to send data to google firebase, and receive data from realtime database
*/
#include <Arduino.h>
#include <Ticker.h>
#if defined(ESP32)  
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include "firebase.h"
#include "device.h"

const char* ssid = "Steff-IoT";
const char* password = "steffiot123";
void WifiConnect();

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  WifiConnect();
  Firebase_Init("cmd");
  Serial.println("System ready.");
}

int nMsgCount=0;
void loop() {
  if (digitalRead(PIN_SW)==0)
  {
    Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, "/data/MsgCount", ++nMsgCount) ? "ok" : fbdo.errorReason().c_str());
  }
}

void onFirebaseStream(FirebaseStream data)
{
  Serial.printf("onFirebaseStream: %s %s %s %s\n", data.streamPath().c_str(),
    data.dataPath().c_str(), data.dataType().c_str(), data.stringData().c_str());

  // if (data.stringData()=="reload")  
  // {
  //   Firebase.RTDB.set(&fbdo, data.streamPath().c_str(), "*");
  // }
}

void WifiConnect()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }  
  Serial.print("System connected with IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("RSSI: %d\n", WiFi.RSSI());
}
