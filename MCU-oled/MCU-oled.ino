/*
 Name:		MCU-oled.ino
 Created:	1/16/2019 2:02:09 PM
 Author:	gusta
*/
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <PubSubClient.h>

#include "OledDisplay.h"

WiFiMulti wifiMulti;
Oled display;

const char* mqtt_server = "192.168.1.124";
const char* mqtt_topic = "temp/humid";
WiFiClient wificlient;
PubSubClient client(wificlient);
#include "Setup.h"

void setup() {
	pinMode(BUILTIN_LED, OUTPUT);
	pinMode(22, OUTPUT);
	digitalWrite(22, HIGH);
	initSerial(115200);
	display.WelcomeScreen();
	delay(1000);
	initMultiWifi();
	randomSeed(micros());
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);
}

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
