#include "YoutubeApi.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "LiquidCrystal_I2C.h"
#include <Wire.h>


char ssid[] = "KHome";       // your network SSID (name)
char password[] = "HoangTung";  // your network key
#define API_KEY "AIzaSyB16LFk_ug-KnvgjAUBpBdeHX8aUYk1yes"  // your google apps API Token
#define CHANNEL_ID "UCNM_nBBPeMRft_M4H9Tmwlg" // makes up the url of channel

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 60000; //mean time between api requests
unsigned long api_lasttime = api_mtbs * -1;   //last time api request has been done

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte aSac[8] = {
  0b00010,
  0b00100,
  0b00000,
  0b01111,
  0b00001,
  0b01111,
  0b10001,
  0b01111
};

byte dongHo[8] = {
  0b00000,
  0b00000,
  0b01110,
  0b10101,
  0b10111,
  0b10001,
  0b01110,
  0b00000
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin(D2, D1);
  lcd.begin();
  lcd.createChar(0, heart);
  lcd.createChar(1, aSac);
  lcd.createChar(2, dongHo);
  lcd.home();
  lcd.print("T");
  lcd.write((byte) 1);
  lcd.print("y M");
  lcd.write((byte) 1);
  lcd.print("y Channel");

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop() {
  if (millis() - api_lasttime > api_mtbs)  {      
    Serial.println("---------Stats---------");
    if(api.getChannelStatistics(CHANNEL_ID))
    {
      Serial.print("Subscriber Count: ");
      Serial.println(api.channelStats.subscriberCount);
      Serial.print("View Count: ");
      Serial.println(api.channelStats.viewCount);
      Serial.print("Comment Count: ");
      Serial.println(api.channelStats.commentCount);
      Serial.print("Video Count: ");
      Serial.println(api.channelStats.videoCount);
      // Probably not needed :)
      //Serial.print("hiddenSubscriberCount: ");
      //Serial.println(api.channelStats.hiddenSubscriberCount);
      Serial.println("------------------------");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.write((byte) 0);
      lcd.printf("%d ", (int) api.channelStats.subscriberCount);
      lcd.write((byte) 2);
      lcd.printf("%d", (int) api.channelStats.viewCount);
    }
    else{
      Serial.println("Fail");
    }
    api_lasttime = millis();
  }
}
