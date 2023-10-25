#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <RtcDS1302.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
float maVariable;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
ThreeWire myWire(3,2,4);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
    Serial.begin(115600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    while (!Serial);
    SPI.begin();
    Rtc.Begin();
    //RtcDateTime currentTime = RtcDateTime(__DATE__ , __TIME__);
    //Rtc.SetDateTime(currentTime);
  }

void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    display.clearDisplay();
    display.setCursor(0,1);
    display.println("Date :");
    display.print(now.Day());
    display.print("/");
    display.print(now.Month());
    display.print("/");
    display.println(now.Year());

    display.println("Time :");
    display.print(now.Hour());
    display.print(":");
    display.print(now.Minute());
    display.print(":");
    display.print(now.Second());
    display.display();
}