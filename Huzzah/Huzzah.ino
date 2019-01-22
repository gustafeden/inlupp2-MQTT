/*
 Name:		Huzzah.ino
 Created:	1/16/2019 11:08:36 PM
 Author:	gusta
*/
#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "uMQTTBroker.h"

const char* RF_KEY = "gug";
const char* mqtt_server = "192.168.1.124";
const char* mqtt_topic = "temp/humid";
ESP8266WiFiMulti wifiMulti;
#include "PubClient.h"
PubClient *pubclient;

#include "Broker.h"
#include "Radio.h"
#include "Setup.h"


RFradio *radiomodule;
myMQTTBroker myBroker;
unsigned long currentMillis;
unsigned long LastRecievedRF;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(5, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	initSerial(115200);
	radiomodule = new RFradio(new RH_ASK(2000, 15, 16, 12));
	initMultiWifi();
	initBroker(myBroker, pubclient);
	pubclient = new PubClient(mqtt_topic, mqtt_server);
	digitalWrite(LED_BUILTIN, HIGH);
}
void loop() {
	currentMillis = millis();
	if (wifiMulti.run() != WL_CONNECTED) {
		Serial.println("WiFi not connected!");
		delay(1000);
	}
	if (radiomodule->recieve()) {
		digitalWrite(BUILTIN_LED, LOW);
		LastRecievedRF = currentMillis;
		if (radiomodule->getMessage() != myBroker.getLastMessage()) {
			digitalWrite(5, HIGH);
			myBroker.publish("local/broker", radiomodule->getMessage());
			myBroker.setLastMessage(radiomodule->getMessage());
			
		}
		digitalWrite(BUILTIN_LED, HIGH);
	}
	if (!pubclient->isConnected()) {
		pubclient->reconnect();
	}
	if (currentMillis - LastRecievedRF > 30000) {
		digitalWrite(BUILTIN_LED, LOW);
		LastRecievedRF = currentMillis;
		StaticJsonBuffer<300> JSONbuffer;
		JsonObject& JSONencoder = JSONbuffer.createObject();

		JSONencoder["Temp"] = "No Signal";
		JSONencoder["Humid"] = "To Sensor";
		String toSend;
		JSONencoder.printTo(toSend);

		myBroker.publish("local/broker", toSend);
	}

	pubclient->doLoop();
}
