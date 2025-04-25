Project converting IR signal into HTTP request for Wiim audio streamer products so that you can control wiim with ir remote (e.g. Harmony remotes)

Wiim API commands:
https://www.wiimhome.com/pdf/HTTP%20API%20for%20WiiM%20Products.pdf

Needed Libraries:
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

#include <WiFi.h>
#include <HTTPClient.h>
