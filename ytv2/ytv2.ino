#include "YoutubeApi.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "ST7565_homephone_esp8266.h"

char ssid[] = "KHome";                         // your network SSID (name)
char password[] = "HoangTung";                             // your network key
#define API_KEY "AIzaSyB16LFk_ug-KnvgjAUBpBdeHX8aUYk1yes" // your google apps API Token
#define CHANNEL_ID "UCNM_nBBPeMRft_M4H9Tmwlg"             // makes up the url of channel

WiFiClientSecure client;
YoutubeApi api(API_KEY, client);

unsigned long api_mtbs = 60000;             //mean time between api requests
unsigned long api_lasttime = api_mtbs * -1; //last time api request has been done

ST7565 lcd(D0, D1, D2, D3);

void setup()
{
  Serial.begin(115200);

  lcd.ON();
  lcd.SET(20, 0, 0, 0, 4);

  lcd.Clear();
  lcd.Uni_String(10, 7, u"T\x00e1y M\x00e1y Channel", BLACK);
  lcd.Uni_String(10, 30, u"Loading...", BLACK);
  lcd.Display();

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}

void loop()
{
  if (millis() - api_lasttime > api_mtbs)
  {
    Serial.println("---------Stats---------");
    if (api.getChannelStatistics(CHANNEL_ID))
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

      lcd.Clear();
      lcd.Uni_String(10, 7, u"T\x00e1y M\x00e1y Channel", BLACK);
      lcd.Number_Long(10, 28, (int)api.channelStats.subscriberCount, STYLE_NUMBER, BLACK);
      lcd.Number_Long(10, 50, (int)api.channelStats.viewCount, ASCII_NUMBER, BLACK);
      lcd.Number_Long(100, 50, (int)api.channelStats.videoCount, ASCII_NUMBER, BLACK);
      lcd.Display();
    }
    else
    {
      Serial.println("Fail");
    }
    api_lasttime = millis();
  }
}
