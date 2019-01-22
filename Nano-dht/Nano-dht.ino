/*
 Name:		Nano_dht.ino
 Created:	1/16/2019 2:02:55 PM
 Author:	gusta
*/
#include <Arduino.h>
#include <ArduinoJson.h>

const char* RF_KEY = "gug";
#define DHTPIN 2 

#include "Radio.h"
#include "dht11.h"

RFradio *radio;
DHT11sensor *dht;
unsigned long currentMillis;
unsigned long lastSent;

void setup() {
	pinMode(3, OUTPUT);
	digitalWrite(3, HIGH);
	Serial.begin(9600);
	radio = new RFradio(new RH_ASK());
	dht = new DHT11sensor(DHTPIN);
	delay(1000);
	digitalWrite(3, LOW);
}

void loop() {
	currentMillis = millis();
	if (currentMillis - lastSent > 4000) {
		digitalWrite(3, HIGH);
		StaticJsonBuffer<300> JSONbuffer;
		JsonObject& JSONencoder = JSONbuffer.createObject();

		lastSent = currentMillis;
		float lasttemp = dht->getTemp();
		float lasthumid = dht->getHumid();
		dht->readTemp();
		dht->ReadHumid();
		JSONencoder["Temp"] = dht->getTemp();
		JSONencoder["Humid"] = dht->getHumid();
		String toSend;
		JSONencoder.printTo(toSend);
		for (int i = 0; i < 2; i++) {
			radio->sendTextMessage(toSend);
		}
		digitalWrite(3, LOW);

	}
}
