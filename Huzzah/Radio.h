#pragma once

class RFradio {
private:
	String message;
	RH_ASK *radio;
	uint8_t buf[32];
	uint8_t buflen;
	void sendf(const char* messageToSend) {
		String StringToSend = (String)RF_KEY + ',' + (String)messageToSend;
		radio->send((uint8_t *)StringToSend.c_str(), 32);
		radio->waitPacketSent();
		Serial.print("Message Sent: ");
		Serial.println(StringToSend);
	}
public:

	RFradio(RH_ASK *radioin) {
		this->radio = radioin;
		buflen = sizeof(buf);
		if (!radio->init())
			Serial.println("init failed");
		radio->setThisAddress(44);
		radio->setHeaderFrom(33);
		radio->setHeaderTo(33);
	}
	~RFradio() {
		delete radio;
	}
	String getMessage() {
		return message;
	}
	bool recieve() {
		if (radio->recv(buf, &buflen)) {
			Serial.print("something has been recieved: ");
			Serial.println((char*)buf);
			if (checkKey((char*)buf)) {
				Serial.print("Message: ");
				Serial.println((char*)buf);
				message = splitkey((char*)buf);
				return true;
			}
			else
				return false;

		}
		return false;
	}
	bool checkKey(char * msgin) {
		String msgincmp = (String)msgin;
		if (msgincmp.substring(0, 3) == RF_KEY)
			return true;
		return false;
	}
	String splitkey(char * msgin) {
		String sendback = msgin;
		return sendback.substring(4, strlen(msgin));
	}
};