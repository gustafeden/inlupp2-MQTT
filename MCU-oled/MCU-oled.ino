/*
 Name:		MCU-oled.ino
 Created:	1/16/2019 2:02:09 PM
 Author:	gusta
*/
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

ESP8266WiFiMulti wifiMulti;
static char* APssid = "MCU8266";
static char* APpass = "hejhejhej";

#include "Setup.h"
// the setup function runs once when you press reset or power the board
void setup() {
	initSerial(115200);
	initMultiWifi();

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
