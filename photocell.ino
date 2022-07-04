#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

RTC_DS1307 rtc;

const int chipSelect = 4;

int photocellPin = 0;     
int photocellReading;     
 
void setup(void) {
  Serial.begin(9600); 

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  rtc.adjust(DateTime(2022, 7, 4, 14, 0, 0));
}
 
void loop(void) {
  String dataString = "";
  photocellReading = analogRead(photocellPin);  
 
  if(photocellReading)
  {
    dataString = String(photocellReading);
  }
  else
  {
    dataString = "";
  }
  File dataFile = SD.open("photocell.txt", FILE_WRITE):
  if(dataFile)
  {
    if(dataString != "")
    {
      dataFile.print(dataString);
      dataFile.print(", ");
      if (photocellReading < 10) {
        dataFile.print("Dark");
      } else if (photocellReading < 200) {
        dataFile.print("Dim");
      } else if (photocellReading < 500) {
        dataFile.print("Light");
      } else if (photocellReading < 800) {
        dataFile.print("Bright");
      } else {
        dataFile.print(" - Very bright");
      }
        dataFile.print(", ");
        DateTime now = rtc.now();
        dataFile.print(now.year(), DEC);
        dataFile.print('/');
        dataFile.print(now.month(), DEC);
        dataFile.print('/');
        dataFile.print(now.day(), DEC);
        dataFile.print(", ");
        dataFile.print(now.hour(), DEC);
        dataFile.print(':');
        dataFile.print(now.minute(), DEC);
        dataFile.print(':');
        dataFile.println(now.second(), DEC);
    }
  }
  Serial.print(photocellReading);     
  Serial.print(", ");
  if (photocellReading < 10) {
    Serial.print("Dark");
  } else if (photocellReading < 200) {
    Serial.print("Dim");
  } else if (photocellReading < 500) {
    Serial.print("Light");
  } else if (photocellReading < 800) {
    Serial.print("Bright");
  } else {
    Serial.println("Very bright");
  }
    Serial.print(", ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(", ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC); 
  delay(1000);
}
