#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define WIFI_SSID "bssm_free"
#define WIFI_PASSWORD "bssm_free"
#define API_KEY "AIzaSyCAyyN5ieS-01h0Vrf49UwWBSIgY-CmfOw"
#define DATABASE_URL "https://hackerton-d5e87-default-rtdb.firebaseio.com/"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
int Vo = A0;
int RLED = D2;
int fire_frog = D5;
int speakerpin = D7;
int LLED = D10;

float Gas_value = 0;
float Gas = 0;
int sec = 0;

void setup() {
Serial.begin(115200);
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("Connecting to Wi-Fi");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(300);
}
Serial.println();
Serial.print("Connected with IP: ");
Serial.println(WiFi.localIP());
Serial.println();
config.api_key = API_KEY;
config.database_url = DATABASE_URL;
if (Firebase.signUp(&config, &auth, "", "")) {
Serial.println("ok");
}
else {
Serial.printf("%s\n", config.signer.signupError.message.c_str());
}
config.token_status_callback = tokenStatusCallback;
Firebase.begin(&config, &auth);
Firebase.reconnectWiFi(true);
pinMode(RLED, OUTPUT);
pinMode(D6, OUTPUT);
pinMode(D8, OUTPUT);
pinMode(D9, OUTPUT);
}
float count = 0.1;
void loop() {
fire_frog = digitalRead(D5);
digitalWrite(D6, 1);
delay(100);

Gas_value = analogRead(Vo);

Serial.println(Gas_value);
digitalWrite(D9, 0);
if(Gas_value >= 40){
  sec = 0;
  Firebase.RTDB.setString(&fbdo, "/event", "1");
  digitalWrite(RLED, 1);
  digitalWrite(LLED, 1);
  digitalWrite(D8, 1);
  while(sec != 20){
    tone(speakerpin, 500, 1000);
    sec++;
    delay(1000);
  }
}
//else if(fire_frog == 1){
//sec = 0;
//Firebase.RTDB.setString(&fbdo, "/event", "1");
//digitalWrite(RLED, 1);
//digitalWrite(LLED, 1);
//digitalWrite(D8, 1);
//while(sec != 60){
//tone(speakerpin, 500, 1000);
//sec++;
//delay(1000);
//}
//}
else{
  Firebase.RTDB.setString(&fbdo, "/event", "0");
  digitalWrite(LLED, 0);
  digitalWrite(RLED, 0);
  digitalWrite(D8, 0);
}

}
