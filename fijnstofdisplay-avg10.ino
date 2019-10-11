#include "SdsDustSensor.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float arraypm25[10];
float arraypm10[10];
int rxPin = 0;
int txPin = 1;
SdsDustSensor sds(rxPin, txPin);
int i = 0;
int j = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  sds.begin();
  lcd.init();
  lcd.backlight();

}

void loop() {

  PmResult pm = sds.readPm();
  Serial.println ("load data from sensor");

  if (pm.isOk()) {
    Serial.println ("data in from sensor");

    arraypm25 [i] = pm.pm25;
    arraypm10 [i] = pm.pm10;


    Serial.println(arraypm25[i]);
    Serial.println(i);
    delay(1000);

    Serial.print ("data into arrays \n");
    i++;
    // if you want to just print the measured values, you can use toString() method as well
    // Serial.println(pm.toString());

    if (i == 10) {
      Serial.print ("into average calculation loop \n");

      float sumpm25 = 0;
      float sumpm10 = 0;
      float averagepm25 = 0;
      float averagepm10 = 0;

      for ( j = 0; j < 10 ; j++) {
        Serial.println("inside for loop");
        sumpm25 += arraypm25[j];
        sumpm10 += arraypm10[j];
      }
      averagepm25 = sumpm25 / 10;
      averagepm10 = sumpm10 / 10;
      Serial.print("PM2.5 = ");
      Serial.print(averagepm25);
      Serial.print(", PM10 = ");
      Serial.println(averagepm10);
      lcd.clear();
      lcd.backlight();
      lcd.setCursor(0, 0);
      lcd.print("PM 2.5:");
      lcd.setCursor(8, 0);
      lcd.print(averagepm25, 2);
      lcd.setCursor(0, 1);
      lcd.print("PM  10:");
      lcd.setCursor(8, 1);
      lcd.print(averagepm10, 2);
      lcd.setCursor(0, 2);
      i = 0;
    }


  } else {
    // notice that loop delay is set to 5s (sensor sends data every 3 minutes) and some reads are not available
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }




  //lcd.init();
  // initialize the lcd
  // Print a message to the LCD.
}
