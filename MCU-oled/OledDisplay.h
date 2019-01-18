#pragma once
#include <U8g2lib.h>

class Oled {
private:
	U8G2_SSD1306_128X64_NONAME_F_SW_I2C *display;
public:
	Oled() {
		display = new U8G2_SSD1306_128X64_NONAME_F_SW_I2C(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
		display->begin();
	}
	~Oled() {
		delete display;
	}
	void WelcomeScreen() {
		display->setFont(u8g2_font_lucasarts_scumm_subtitle_o_tf);
		display->firstPage();
		do {
			display->drawStr(22, 20, "Welcome");
			display->setFont(u8g2_font_crox1hb_tf);
			display->drawStr(11, 45, "MQTT subscriber");
		} while (display->nextPage());
	}
	void ConnectingWifi(int dots, bool ifdots = false) {
		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(4, 20, "Connecting to WiFi..");
			if (ifdots) {
				display->setFont(u8g2_font_lucasarts_scumm_subtitle_o_tf);
				for (int i = 0; i < dots; i++) {
					display->drawStr(7 + (i * 5), 40, ".");
				}
			}
		} while (display->nextPage());
	}
	void wifiConnected(const char * ssid,const char * ip) {
		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(10, 15, "Connected to:");
			display->drawStr(10, 30, ssid);
			display->drawStr(10, 45, ip);
		} while (display->nextPage());
	}
	void mqttConnecting(const char* serverIP) {
		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(10, 15, "Connecting to");
			display->drawStr(10, 30, "MQTT server:");
			display->drawStr(10, 45, serverIP);
		} while (display->nextPage());
	}
	void ShowData(const char * Temp = nullptr, const char* Humid = nullptr) {
		String writeTemp, writeHumid;
		writeTemp += "Temp: " + (String)Temp + " *C";
		writeHumid += "Humid: " + (String)Humid + " %";

		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(31, 10, "Connected");
			display->drawLine(5,15,123,15);
			display->drawLine(5, 60, 123, 60);
			if (Temp != nullptr) {
				display->drawStr(10, 30, writeTemp.c_str());
				display->drawStr(10, 50, writeHumid.c_str());
			}
		} while (display->nextPage());
	}
};