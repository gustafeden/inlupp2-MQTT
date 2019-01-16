#pragma once
void initMultiWifi() {
	WiFi.softAP(APssid, APpass);
	Serial.print("Access Point \"");
	Serial.print(APssid);
	Serial.println("\" started\r\n");

	wifiMulti.addAP("iPhone x", "hejhejhej");
	wifiMulti.addAP("Caesar's Palace 2.0", "kingofpop");
	wifiMulti.addAP("IoT", "IoT2018!");

	Serial.println("Connecting");
	while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {
		delay(250);
		Serial.print('.');
	}
	Serial.println("\r\n");
	if (WiFi.softAPgetStationNum() == 0) {
		Serial.print("Connected to ");
		Serial.println(WiFi.SSID());
		Serial.print("IP address:\t");
		Serial.print(WiFi.localIP());
	}
	else {
		Serial.print("Station connected to ESP8266 AP");
	}
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