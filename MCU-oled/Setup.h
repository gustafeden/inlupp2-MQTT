#pragma once

struct DATA {
	float Temp;
	float Humidity;
};

void blink(int amount, int time_delay, uint8_t LED) {
	for (int i = 0; i <= amount; i++) {
		digitalWrite(LED, HIGH);
		delay(time_delay);
		digitalWrite(LED, LOW);
		delay(time_delay);
	}
}

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

String getTempString(String msg) {
	//String return_str = msg.substring(0,msg.indexOf('h'));
	return  msg.substring(0, msg.indexOf('h'));
}
String getHumidString(String msg) {
	//String return_str = msg.substring(0,msg.indexOf('h'));
	return  msg.substring(msg.indexOf('h'), msg.length());
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
	StaticJsonBuffer<300> JSONBuffer;
	JsonObject&  parsed = JSONBuffer.parseObject(message);

	display.ShowData(parsed["Temp"], parsed["Humid"]);
	blink(4,100,5);

}
void reconnect() {
	// Loop until we're reconnected
	while (!client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Create a random client ID
		display.mqttConnecting(mqtt_server);
		blink(2,100, BUILTIN_LED);
		delay(1300);
		String clientId = "ESP8266Client-";
		clientId += String(random(0xffff), HEX);
		// Attempt to connect
		if (client.connect(clientId.c_str())) {
			Serial.println("Client connected");
			client.subscribe(mqtt_topic);
			Serial.print(" My client id: ");
			Serial.println(clientId);
			//display.showSuccess();
			//display.mqttConnected(mqtt_topic);
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