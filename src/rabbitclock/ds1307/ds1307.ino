// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
// 2010-02-04 <jc@wippler.nl> http://opensource.org/licenses/mit-license.php

#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 RTC;

int ledDay = 12;
int ledNight = 13;
boolean night = true;
int minutes;
boolean debug = false;

void setup () {
    pinMode(ledDay, OUTPUT);
    pinMode(ledNight, OUTPUT);
    digitalWrite(ledNight, LOW); 
    digitalWrite(ledDay, LOW); 
    Serial.begin(57600);
    Wire.begin(); 
    if (! RTC.isrunning()) {
      Serial.println("RTC stopped !");
      RTC.adjust(DateTime(__DATE__, __TIME__));
      // following line sets the RTC to the date & time this sketch was compiled
      RTC.begin();
    } else {
      Serial.println("RTC is running !");
    }
    
}

void loop () {
   //print2SerialDate();
   DateTime now = RTC.now();
   if ( debug) {
     minutes += 20 ; 
     if (minutes > 24 * 60) 
       minutes = 0 ; 
   } else {
     minutes = now.hour() * 60 +  now.minute();
   }

   print2SerialMinutes(minutes);
   night = true;
   if ( minutes >=  7 * 60 + 10 ) 
     night = false;
   if ( minutes >= 13 * 60 + 30 ) 
     night = true; 
   if ( minutes >= 16 * 60 ) 
     night = false ;
   if ( minutes >= 19 * 60 )
     night = true;
   
   if (night) {
      digitalWrite(ledNight, HIGH);   
      digitalWrite(ledDay, LOW);  
   } else {
      digitalWrite(ledDay, HIGH);   
      digitalWrite(ledNight, LOW);  
   }
   delay(1000);
   test();
}

void print2SerialDate(){
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
    Serial.print(' ');
    Serial.print((now.hour() * 60 + now.minute()), DEC);
    Serial.println();
}

void print2SerialMinutes(int minutes){
  Serial.print(minutes / 60, DEC);
  Serial.print(":");
  Serial.print(minutes % 60, DEC);
  Serial.println();
}

void test(){
  DateTime now = RTC.now();
  if ( now.year() == 2000 || now.year() == 2165){
      print2SerialDate();
      for ( int i = 0 ; i < 5 ; i++){
        digitalWrite(ledDay, HIGH);   
        digitalWrite(ledNight, LOW);
        delay(100);  
        digitalWrite(ledDay, LOW);   
        digitalWrite(ledNight, HIGH);
        delay(100);  
     }
  }
}
