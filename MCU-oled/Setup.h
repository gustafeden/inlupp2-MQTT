#pragma once


void initMultiWifi() {
	wifiMulti.addAP("iPhone x", "hejhejhej");
	wifiMulti.addAP("Caesar's Palace 2.0", "kingofpop");
	wifiMulti.addAP("IoT", "IoT2018!");

	Serial.println("Connecting to WiFi");
	int temp = 0;
	display.ConnectingWifi(temp);
	while (wifiMulti.run() != WL_CONNECTED) {
		temp++;
		delay(250);
		Serial.print('.');
		display.ConnectingWifi(temp, true);
	}
	
	Serial.print("Connected to ");
	Serial.println(WiFi.SSID());
	Serial.print("IP address:\t");
	Serial.print(WiFi.localIP());
	display.wifiConnected(WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
	delay(1000);
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

}

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	String message;
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
		message += (char)payload[i];
	}
	display.mqttConnected(mqtt_topic, message.c_str());

	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '1') {
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
		// but actually the LED is on; this is because
		// it is active low on the ESP-01)
	}
	else {
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}

}
void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Create a random client ID
		display.mqttConnecting(mqtt_server);
		delay(1500);
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (client.connect(clientId.c_str())) {
			Serial.println("Client connected");
			client.subscribe(mqtt_topic);
			Serial.print(" My client id: ");
			Serial.println(clientId);
			display.showSuccess();
			delay(100);
			display.mqttConnected(mqtt_topic);
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}