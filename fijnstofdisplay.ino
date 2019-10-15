#include "SdsDustSensor.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int rxPin = 0;
int txPin = 1;
SdsDustSensor sds(rxPin, txPin);

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  sds.begin();
  lcd.init();
  lcd.backlight();

  Serial.println(sds.queryFirmwareVersion().toString()); // prints firmware version
  Serial.println(sds.setActiveReportingMode().toString()); // ensures sensor is in 'active' reporting mode
  Serial.println(sds.setCustomWorkingPeriod(3).toString()); // sensor sends data every 3 minutes

}

void loop() {
  PmResult pm = sds.readPm();
  if (pm.isOk()) {
  Serial.print("PM2.5 = ");
  Serial.print(pm.pm25);
  Serial.print(", PM10 = ");
  Serial.println(pm.pm10);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0,0);
   lcd.print("PM 2.5:");
  lcd.setCursor(8,0);
  lcd.print(pm.pm25,1);
  lcd.setCursor(0,1);
  lcd.print("PM  10:");
   lcd.setCursor(8,1);
  lcd.print(pm.pm10,1);
  lcd.setCursor(0,2);
    
  } 
  else {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }



    delay(500);
}
