#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <RtcDS1302.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
ThreeWire myWire(3,2,4);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(115600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!Rtc.IsDateTimeValid()) 
  {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing
    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected())
  {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning())
  {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) 
  {
    Rtc.SetDateTime(compiled);
  }
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    display.clearDisplay();
    display.setCursor(0,1);

    display.println("Date: ");
    display.print(now.Day());
    display.print("/");
    display.print(now.Month());
    display.print("/");
    display.println(now.Year());

    display.println("Time: ");
    display.print(now.Hour());
    display.print(":");
    display.print(now.Minute());
    display.print(":");
    display.print(now.Second());
    display.display();
}

