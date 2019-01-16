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
	void showSuccess() {
		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(20, 40, "Success!");
		} while (display->nextPage());
		delay(500);
	}
	void mqttConnected(const char* sub_topic,const char * TempHumid = nullptr) {
		display->setFont(u8g2_font_crox1hb_tf);
		display->firstPage();
		do {
			display->drawStr(5, 10, "Subscribed to:");
			display->drawStr(5, 25, sub_topic);
			if (TempHumid != nullptr) {
				display->drawStr(5, 40, "Recieved:");
				display->drawStr(5, 55, TempHumid);
			}
		} while (display->nextPage());
	}
	U8G2_SSD1306_128X64_NONAME_F_SW_I2C * display_custom() {
		return display;
	}
};