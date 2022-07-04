#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#include <RTClib.h>

RTC_DS1307 rtc;

#define DHTPIN 2 
#define DHTTYPE DHT11

#define USE_ARDUINO_INTERRUPTS true    

const int chipSelect = 4;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  while (!Serial) {
    ; 
  }


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

  Serial.print("humidity");
  Serial.print(", ");
  Serial.print("tempreture");
  Serial.println("");
}


void loop() {
   delay(2000);
  String hum = "";
  String temp = "";

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  if(h)
  {
    hum = String(h);
  }

  if(t)
  {
    temp = String(t);
  }

  File dataFile = SD.open("temp.txt", FILE_WRITE);

  if (dataFile) {
    {
      
        dataFile.print(hum);
        dataFile.print(", ");
        dataFile.print(temp);
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
    dataFile.close();

    Serial.print(hum);
    Serial.print(", ");
    Serial.print(temp);
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
  }

  else {
    Serial.println("error opening datalog.txt"); 
  }

}
