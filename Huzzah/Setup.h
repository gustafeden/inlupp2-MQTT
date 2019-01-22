#pragma once

void blink(int amount, int time) {
	for (int i = 0; i <= amount; i++) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(time);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(time);
	}
}

void initMultiWifi() {

	wifiMulti.addAP("iPhone x", "hejhejhej");
	wifiMulti.addAP("Caesar's Palace 2.0", "kingofpop");
	wifiMulti.addAP("IoT", "IoT2018!");

	Serial.println("Connecting");
	while (wifiMulti.run() != WL_CONNECTED) {
		delay(250);
		Serial.print('.');
	}
	Serial.println("\r\n");
	Serial.print("Connected to ");
	Serial.println(WiFi.SSID());
	Serial.print("IP address:\t");
	Serial.print(WiFi.localIP());
	blink(3, 200);
	Serial.println("\r\n");

}

void initSerial(int baud) {
	Serial.begin(baud);
	for (uint8_t i = 4; i > 0; i--) {
		Serial.printf("[SETUP] BOOT WAIT %d...\r\n", i);
		Serial.flush();
		delay(400);
	}
	Serial.println("Serial communication initiated.");
	delay(300);

}

void initBroker(myMQTTBroker & inputbroker, PubClient * set_pub_client) {
	Serial.println("Starting MQTT broker");
	inputbroker.init();
	inputbroker.subscribe("local/broker");
	//inputbroker.set_client(set_pub_client);
}
