#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2020-12-04 22:41:53

#include "Arduino.h"
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <Wire.h>
#include <FastLED.h>

byte * Wheel(byte WheelPos) ;
void showStrip() ;
void setPixel(int Pixel, byte red, byte green, byte blue) ;
void setAll(byte red, byte green, byte blue) ;
void RGBLoop();
void led_run();
void rainbowCycle(int SpeedDelay) ;
void handleRoot() ;
void handleNotFound() ;
void setup() ;
void loop() ;

#include "LEDworx_v01.ino"

#include "LED_ctrl.ino"

#endif
