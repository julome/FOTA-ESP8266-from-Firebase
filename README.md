# FOTA-ESP8266-from-Firebase
Self-updating OTA firmware for ESP8266 from Firebase
With this script you will be able to self-update all your ESP8266 in your red from Firebase Storage

Steps:
1- Configure a Storage Firebase server as public access.
 -Rules:
  service firebase.storage {
    match /b/{bucket}/o {
      match /{allPaths=**} {
        allow read, write;
      }
    }
  }
  
2- You will upload two files to your Storage Firebase account: version.txt and update.bin
 -version.txt just will content the number version of your new firmware. E.g. 1001
 -update.bin is your new firmware .bin compile from arduino
 -First you must upload update.bin and after that upload version.txt just for a safe updating
 
3- The operation consist on ESP8266 check in version.txt if there is a new firmware. It is done through comparing the actual version from FW_VERSION const.
 If it is an upper version then ESP8266 will run the updating from update.bin image.
 
4- Since you ESP8266 will have to access to a secure server https you need the fingerprint of Storage Firebase Storage. For that you can extract the fingerprint from https://www.grc.com/fingerprints.htm.
   Just copy and paste the https address of version.txt in the box. Then just copy and paste the fingerprint on fingerprint const.
   
5- You wiil have to charge fwVersionURL const with the https addres of your version.txt file and charge fwImageURL const with https address of your update.bin file.

Enjoy!!!

