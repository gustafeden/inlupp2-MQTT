#pragma once

class PubClient {
private:
	const char* topic;
	const char* server;
	WiFiClient wificlient;
	PubSubClient client;
public:
	PubClient(const char* topic, const char* setserver) {
		this->topic = topic;
		client = PubSubClient(wificlient);
		randomSeed(micros());
		server = setserver;
		client.setServer(setserver, 1883);
	}
	PubSubClient & getClient() {
		return client;
	}
	void publish(const char* pub_msg) {
		client.publish(topic, pub_msg, true);
	}
	bool doLoop() {
		return client.loop();
	}
	bool isConnected() {
		return client.connected();
	}
	void reconnect() {
		while (!client.connected()) {
			Serial.print("Attempting MQTT connection...");
			String clientId = "ESP8266Client-";
			clientId += String(random(0xffff), HEX);
			if (client.connect(clientId.c_str())) {
				Serial.println("Client connected");
				//client.subscribe(mqtt_topic);
				client.publish("handshake", "connected");
				Serial.print(" My client id: ");
				Serial.println(clientId);
			}
			else {
				Serial.print("failed, rc=");
				Serial.print(client.state());
				Serial.println(" try again in 5 seconds");
				delay(5000);
			}
		}
	}
};