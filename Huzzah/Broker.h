#pragma once

class myMQTTBroker : public uMQTTBroker
{
private:
	String lastMessageSent;
public:
	
	void setLastMessage(String msg) {
		lastMessageSent = msg;
	}
	String getLastMessage() {
		return lastMessageSent;
	}
	virtual bool onConnect(IPAddress addr, uint16_t client_count) {
		Serial.println(addr.toString() + " connected");
		return true;
	}

	virtual bool onAuth(String username, String password) {
		Serial.println("Username/Password: " + username + "/" + password);
		return true;
	}

	virtual void onData(String topic, const char *data, uint32_t length) {
		char data_str[length + 1];
		os_memcpy(data_str, data, length);
		data_str[length] = '\0';

		Serial.println("received topic '" + topic + "' with data '" + (String)data_str + "'");
		pubclient->publish(data_str);
		digitalWrite(5, LOW);
	}
};