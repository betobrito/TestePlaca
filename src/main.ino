// *****************************************************
// MY INSTAGRAM PLAQUE FOLLOWERS COUNTER
// Year: 2020
// Authors: Gabriel Froes & Vanessa Weber
// Youtube / Instagram: @codigofontetv
// *****************************************************

// Required Libs
#include <stdlib.h>
#include <string.h>
#include <Wire.h>
#include <InstagramApi.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "config.h"

// Wifi
WiFiClient client;

// Youtube API
InstagramApi api(INSTAGRAM_URL, client);
unsigned long api_mtbs = 3600000;      // (1 hour) Time between API requests
unsigned long api_lasttime = -3600000; // Last time API request has been hit

// *****************************************************
// Arduino setup function
// *****************************************************
void setup()
{
  Serial.begin(9600);
  // ------------------------
  // 2. CONNECT WIFI
  // ------------------------
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wi-fi network:
  Serial.print("\nConnecting to:");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("Wi-fi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
}
// *****************************************************

// *****************************************************
// Arduino loop function
// *****************************************************
void loop()
{
  if (millis() > api_lasttime + api_mtbs)
  {
    Serial.println("Loading...");
    if (api.getAccountStatistics())
    {
      api_lasttime = millis();
      Serial.println("-----Account Stats-----");
      Serial.print("Followers Count: ");
      Serial.println(api.accountStats.followersCount);
    }
    else
    {
      Serial.println("Oops! Trying again...");
      delay(2000);
      api_lasttime = 0;
    }
  }
}
// *****************************************************