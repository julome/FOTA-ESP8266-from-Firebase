/*
You need two files in your folder server:
update.bin    // Compiled bin new firmware
version.txt   // TXT with the new version number ej: 1001
Version for Firebase
On Firebase upload version.txt and update.bin !!!Never erase just update¡¡¡
Firebase storage without rules (public)
Cut and paste https address on fwVersionURL and fwImageURL
fwVersionURL Version.txt = Firebase https address
fwImageURL update.bin = Firebase https address
you need fingerptint Firebase from https://www.grc.com/fingerprints.htm (paste version.txt https from Firebase)
*/

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>

const char* fingerprint = "F4:1C:FC:1D:D4:14:AD:18:9C:5D:26:EF:44:07:CA:77:BE:2F:C4:5B"; //Catch with https://www.grc.com/fingerprints.htm
const char* fwVersionURL = "https://firebasestorage.googleapis.com/xxxxxxx/version.txt";
const char* fwImageURL = "https://firebasestorage.googleapis.com/v0/b/xxxxxx/update.bin";

const int FW_VERSION = 1007;                              //New Firmware version
const char* ssid = "SSID";                       //SSID RED
const char* password = "password";                        //Password RED

void checkForUpdates() {      // FOTA Function
  
  // Just for debug you may erase
  Serial.println( "Checking for firmware updates." );
  //Serial.print( "Firmware version URL: " );
  //Serial.println( fwVersionURL );

  HTTPClient http;
  http.begin(fwVersionURL, fingerprint); //for https   
  int httpCode = http.GET();
  if( httpCode == 200 ) {     // 200 == Code http ok
    String newFWVersion = http.getString();   // Read new firmware version on file version.txt
  
    // Just for debug you may erase
    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );  
    int newVersion = newFWVersion.toInt();
    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );  // Just for debug    
      t_httpUpdate_return ret = ESPhttpUpdate.update(fwImageURL, "", fingerprint); //Update firmware https
           
      //*****Just for debug******
      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;
        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES"); 
          break;
      }      
    }
    else {
      Serial.println( "Already on latest version" ); //Just for debug
    }
  }
  else {
    //Just for debug
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
  }  
  http.end();  
}
void setup() 
{
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) 
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

//  ArduinoOTA.setPassword((const char *)"123");
  
//  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(2, OUTPUT);
  
}

void loop() 
{  
  checkForUpdates();   
  digitalWrite(2, HIGH);  
  delay(3000);  
  digitalWrite(2, LOW);
  delay(3000);     
}
  
