#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <WiFi.h>
#include <HTTPClient.h>


const uint16_t kRecvPin = 13; //IR reciever pin
IRrecv irrecv(kRecvPin);
decode_results results;

const char* ssid = "SsidOfYourNetwork";
const char* password = "PasswordForYourNetwork";


void setup() {
  Serial.begin(115200);
  delay(4000);

  irrecv.enableIRIn();  // Start the receiver
  while (!Serial) { // Wait for the serial connection to be establised.
    delay(50);
  }
  Serial.println();
  Serial.println("IR reciever is running and waits for IR code");



  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}



void loop() {

  if ((WiFi.status() == WL_CONNECTED)) {

        HTTPClient http;

    if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      if(results.value == 0xFFA25D) {
        http.begin("https://192.168.1.18/httpapi.asp?command=setPlayerCmd:onepause");
        http.GET();
        Serial.println("Button 1 was pressed");

      } else if (results.value == 0xFF629D) {
        http.begin("https://192.168.1.18/httpapi.asp?command=setPlayerCmd:prev");
        http.GET();
        Serial.println("Button 2 was pressed");

      } else if (results.value == 0xFFE21D) {
        http.begin("https://192.168.1.18/httpapi.asp?command=setPlayerCmd:next");
        http.GET();
        Serial.println("Button 3 was pressed");

      } else if (results.value == 0xFF22DD) {
        http.begin("https://192.168.1.18/httpapi.asp?command=setShutdown:0");
        http.GET();
        Serial.println("Button 4 was pressed");
      }
      delay(300);
      irrecv.resume();  // Receive the next value
      http.end(); //Free the resources
    }
  }
}



  
/*
API commands + Buttons with IR codes

Play/pause
https://192.168.1.18/httpapi.asp?command=setPlayerCmd:onepause

1 -> FFA25D
    
Previous   
https://192.168.1.18/httpapi.asp?command=setPlayerCmd:prev

2 -> FF629D

Next
https://192.168.1.18/httpapi.asp?command=setPlayerCmd:next

3 -> FFE21D

Shutdown
https://192.168.1.18/httpapi.asp?command=setShutdown:0

4 -> FF22DD
*/    
  
