#include <SPI.h>
#include <SD.h>
#include <Ultrasonic.h>
#include <RTClib.h>

RTC_DS1307 rtc;

const int chipSelect = 4;
Ultrasonic ultrasonic(2,3);
void setup() {

  Serial.begin(9600);
  Serial.println(F("ultxx test!"));

  while (!Serial) {
    ; 
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  rtc.adjust(DateTime(2022, 7, 4, 14, 0, 0));
  Serial.print("distance \n");


}


void loop() {
   delay(500);
  String distance = "";
  
  float d = ultrasonic.read(CM);
  

  if (isnan(d)) {
    Serial.println(F("Failed to read from UltraSonic sensor!"));
    return;
  }

  
  if(d)
  {
    distance = String(d);
  }

  File dataFile = SD.open("ultrasonic.txt", FILE_WRITE);

  if (dataFile) {
    {
      
        dataFile.println(distance);
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

    Serial.println(distance);
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
