
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

RTC_DS1307 rtc;

#define USE_ARDUINO_INTERRUPTS true    
#include <PulseSensorPlayground.h>

const int chipSelect = 4;

const int PulseWire = 0;
int Threshold = 550;           
                               
PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");

  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  
  }

   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1);
  }

  rtc.adjust(DateTime(2022, 7, 4, 14, 0, 0));
  Serial
}
void loop() {
  String dataString = "";

  int myBPM = pulseSensor.getBeatsPerMinute(); 
  if(myBPM)
  {
      dataString = String(myBPM);
  }
  else
  {
    dataString = "";
  }
  
  File dataFile = SD.open("pulse.txt", FILE_WRITE);

  if (dataFile) {
    if(dataString != "")
    {
        dataFile.print(dataString);
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
    Serial.println(dataString);
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
  delay(1000);
}
