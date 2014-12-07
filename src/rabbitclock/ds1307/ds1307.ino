// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// 2010-02-04 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

int hour_day = 7; 
int minu_day = 0;
int hour_night = 19; 
int minu_night = 30;


void setup () {
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    Serial.begin(57600);
    Wire.begin();
    //RTC.adjust(DateTime(__DATE__, __TIME__));
    RTC.begin();
    
    // following line sets the RTC to the date & time this sketch was compiled
    digitalWrite(13, LOW);  
}

void loop () {
    DateTime now = RTC.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    if ( now.hour() <= hour_day && now.minute() < minu_day ) {
      digitalWrite(12, HIGH);   
      digitalWrite(13, LOW);  
      Serial.print("debug1");     
    } else if ( now.hour() >= hour_day && now.minute() >= minu_day && now.hour() < hour_night && now.minute() < minu_night ) {
      digitalWrite(13, HIGH);   
      digitalWrite(12, LOW);   
      Serial.print("debug2");     
    } else if ( now.hour() >= hour_night && now.minute() >= minu_night ) {
      digitalWrite(12, HIGH);   
      digitalWrite(13, LOW);     
      Serial.print("debug3");     
    }
    
    
    Serial.print(" since 2000 = ");
    Serial.print(now.get());
    Serial.print("s = ");
    Serial.print(now.get() / 86400L);
    Serial.println("d");
    
    Serial.println();
    delay(3000);
}
