/* FLASH SETTINGS
Board: LOLIN D32
Flash Frequency: 80MHz
Partition Scheme: Minimal SPIFFS
https://www.online-utility.org/image/convert/to/XBM
*/

#include <WiFi.h>
#include <Wire.h>
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <Arduino.h>

#include "Display.h"
#include "WiFiScan.h"
#include "MenuFunctions.h"
#include "Web.h"
//#include "icons.h"

Display display_obj;
WiFiScan wifi_scan_obj;
MenuFunctions menu_function_obj;
Web web_obj;

uint32_t currentTime  = 0;

void setup()
{

  pinMode(FLASH_BUTTON, INPUT);
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);
  
  Serial.begin(115200);
  Serial.println("\n\n--------------------------------\n");
  Serial.println("         ESP32 Marauder      \n");
  Serial.println("            " + display_obj.version_number + "\n");
  Serial.println("       By: justcallmekoko\n");
  Serial.println("--------------------------------\n\n");

  // Run display setup
  display_obj.RunSetup();

  // Build menus
  menu_function_obj.RunSetup();
}


void loop()
{
  
  // get the current time
  //if ((wifi_scan_obj.currentScanMode != WIFI_ATTACK_BEACON_SPAM))
  currentTime = millis();

  // Update all of our objects
  //if ((!display_obj.draw_tft) &&
  //    (wifi_scan_obj.currentScanMode != OTA_UPDATE))
  if (!display_obj.draw_tft)
  {
    display_obj.main(); 
    wifi_scan_obj.main(currentTime);
    //if ((wifi_scan_obj.currentScanMode != WIFI_ATTACK_BEACON_SPAM))
    if (wifi_scan_obj.currentScanMode != WIFI_PACKET_MONITOR)
      menu_function_obj.main();
      if (wifi_scan_obj.currentScanMode == OTA_UPDATE)
        web_obj.main();
    delay(1);
  }
  else if ((display_obj.draw_tft) &&
           (wifi_scan_obj.currentScanMode != OTA_UPDATE))
  {
    display_obj.drawStylus();
  }
  //else
  //{
  //  web_obj.main();
  //}

  //Serial.println(wifi_scan_obj.currentScanMode);

  //Serial.print("Run Time: ");
  //Serial.print(millis() - currentTime);
  //Serial.println("ms");
}
