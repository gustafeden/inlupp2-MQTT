#pragma once

#include <RH_ASK.h>
#include <SPI.h>
#include <Wire.h>

class RFradio {
private:
	RH_ASK *radio;
	uint8_t buf[32];
	uint8_t buflen;
	void sendf(const char* messageToSend) {
		String StringToSend = (String)RFKEY + ',' + (String)messageToSend;
		radio->send((uint8_t *)StringToSend.c_str(), 32);
		if (!radio->waitPacketSent())
			Serial.println("WaitPacketSent failed");
		Serial.print("Message Sent: ");
		Serial.println(StringToSend);
	}
public:

	RFradio(RH_ASK *radioin) {
		this->radio = radioin;
		buflen = sizeof(buf);
		if (!radio->init())
			Serial.println("init failed");
		radio->setThisAddress(33);
		radio->setHeaderFrom(44);
		radio->setHeaderTo(44);
	}
	~RFradio() {
		delete radio;
	}
	void sendTextMessage(String msg) {
		sendf(msg.c_str());
	}
};