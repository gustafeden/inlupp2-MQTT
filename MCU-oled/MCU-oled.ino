/*
 Name:		MCU-oled.ino
 Created:	1/16/2019 2:02:09 PM
 Author:	gusta
*/
/*
TODO::
change from string to json
*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <PubSubClient.h>
//#include <U8x8lib.h>


#define UseOled true
#include "OledDisplay.h"

WiFiMulti wifiMulti;
Oled display;

const char* mqtt_server = "192.168.1.124";
const char* mqtt_topic = "temp/humid";
WiFiClient wificlient;
PubSubClient client(wificlient);
long lastMsg = 0;
char msg[50];
int value = 0;
#include "Setup.h"
// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(BUILTIN_LED, OUTPUT);
	pinMode(5, OUTPUT);
	initSerial(115200);
	display.WelcomeScreen();
	delay(1000);
	initMultiWifi();
	randomSeed(micros());
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}


// the loop function runs over and over again until power down or reset
void loop() {
	
	if (wifiMulti.run() != WL_CONNECTED) {
		Serial.println("WiFi not connected!");
		display.ConnectingWifi(0);
		delay(1000);
	}
	if (!client.connected()) {
		reconnect();
	}
	client.loop();


}
