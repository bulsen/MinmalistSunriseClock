#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


// Network prefs
const char *ssid     = SSID_OF_YOUR_NETWORK;
const char *password = PASSWORD_OF_YOUR_NETWORK;

// utc +3 time zone
// CHANGE_THIS = your_utc_time_zone * 3600
// for me: 3* 3600
const long utcOffsetInSeconds = CHANGE_THIS;


// this alarm was set for 6:00
// if you want to change 
const int alarm_hour = 6;
const int alarm_minute = 0;


const int LED_FAILED = 15;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);



void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);

  //error message
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();

  pinMode(LED_BLINK, OUTPUT);
  pinMode(LED_FAILED, OUTPUT);
  digitalWrite(LED_FAILED, LOW);
  digitalWrite(LED_BLINK,LOW);
}



void loop() {
  timeClient.update();

          // alarm light
          digitalWrite(LED_FAILED,LOW);
          //alarm check sequence
          if(timeClient.getHours() == alarm_hour) {
        
            if (timeClient.getMinutes() >= alarm_minute) {
                  digitalWrite(LED_BLINK, HIGH);
                  //delay(120000);
                  //digitalWrite(LED_BLINK,LOW);
              }
    
          }

  Serial.println(timeClient.getFormattedTime());
  // delay 1.5 min
  delay(90000);
}
