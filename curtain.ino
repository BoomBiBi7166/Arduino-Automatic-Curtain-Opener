#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>

RTC_DS3231 rtc;
Servo curtainServo;

int stopSignal = 90;
int openSpeed = 120;
int closeSpeed = 70; 

unsigned long openDuration =6000;
unsigned long closeDuration = 8000;

bool openedToday = false;
bool closedToday = false;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  curtainServo.attach(9);
  curtainServo.write(stopSignal);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  int hour = now.hour();int minute = now.minute();int second = now.second();
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);
  if (hour == 7 && minute == 30 && second == 00 && !openedToday) {
    openCurtain();
    openedToday = true;
    closedToday = false;
  }
  if (hour == 19 && minute == 00 && second == 00 && !closedToday) {
    closeCurtain();
    closedToday = true;
    openedToday = false;
  }

  delay(1000);
}

void openCurtain() {
  curtainServo.write(openSpeed);
  delay(openDuration);
  curtainServo.write(stopSignal);
}

void closeCurtain() {
  curtainServo.write(closeSpeed);
  delay(closeDuration);
  curtainServo.write(stopSignal);
}
