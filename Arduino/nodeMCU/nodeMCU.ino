#include <Arduino.h>
#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <string>
ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(9600);
   Serial.setDebugOutput(true);
  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("Mengubungkan %d...\n", t);
//    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
//  WiFiMulti.addAP("OJIK.NET", "ojiklalu07");
  WiFiMulti.addAP("NightCity", "NightCity2077");

}

void loop() {
  // put your main code here, to run repeatedly:
  if((WiFiMulti.run() == WL_CONNECTED)){
    Serial.print("Terhubung!\n"); 
//    membaca data dari Serial 9600
String dataSensor;
String dataSuhu;
    String suhu=String(random(127));
    String debitair=String(random(300));
//String httpRequestData;
//while(Serial.available()>0){
  dataSensor=Serial.readString();
//  dataSensor+=char(Serial.read());
//  }
  Serial.println(dataSensor);
String  httpRequestData = "{\"suhu\": \"" + dataSensor + "\",\"debitair\": \"" + debitair + "\",\"action\": \"setDatas\"}";

     HTTPClient http;
    WiFiClient client;
    http.begin(client,"http://192.168.43.194:3000/api/nodemcu");
    
//    int httpCode=http.GET();
//http.addHeader("Content-Type", "application/json");  
http.addHeader("Content-Type", "text/plain");
http.POST(dataSensor);   
//      http.addHeader("Content-Type", "application/x-www-form-urlencoded");    
      // Send HTTP POST request
      if(dataSensor!=0){
        
//      int httpCode = http.POST(httpRequestData);
        }

      String payload = http.getString();
      Serial.println(payload);
    http.end();
  }
delay(3000);
}
