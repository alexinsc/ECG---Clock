/*
Branchement :
/!\ Attention, bien penser à alimenter l'écran OLED
/!\ Attention, bien penser à alimenter l'horloge RTC (A minima brancher la broche GRD)
Clock :
  RST: D4
  DAT: D3
  CLK: D2
Ecran OLED :
  SCL : A5
  SDA : A4  
*/


//Déclaration des bibliothèques
#include <Arduino.h> //Bibliothèque Arduino
#include <Wire.h> //Bibliothèque pour l'écran OLED et l'horloge RTC
#include <Adafruit_SSD1306.h> //Bibliothèque pour l'écran OLED
#include <Adafruit_GFX.h> //Bibliothèque pour l'écran OLED
#include <RtcDS1302.h> //Bibliothèque pour l'horloge RTC

//Déclaration des variables
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); //Définition de l'écran OLED
ThreeWire myWire(3,2,4); //Définition des broches de l'horloge RTC
RtcDS1302<ThreeWire> Rtc(myWire); //Définition de l'horloge RTC

//Déclaration de la boucle setup()
void setup() {
  Serial.begin(9600);     //Initialisation de la communication série et taux de raffraichissement
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);      //Initialisation de l'écran OLED
  display.setTextSize(2);      //Définition de la taille du texte
  display.setTextColor(WHITE);      //Définition de la couleur du texte
  Rtc.Begin();      //Initialisation de l'horloge RTC
}

//Déclaration de la boucle loop() (instruction répétée en boucle)
void loop() {
    RtcDateTime now = Rtc.GetDateTime(); //Récupération de la date et de l'heure à chaque début de boucle
    display.clearDisplay();  //Effacement de l'écran OLED
    display.setCursor(0,1);

    //Affichage de la date sur l'écrna OLED
    display.println("Date: ");
    display.print(now.Day()); //Affichage du jour
    display.print("/");
    display.print(now.Month()); //Affichage du mois
    display.print("/");
    display.println(now.Year()); //Affichage de l'année

    //Affichage de l'heure sur l'écran OLED
    display.println("Time: ");
    display.print(now.Hour()); //Affichage de l'heure
    display.print(":");
    display.print(now.Minute()); //Affichage des minutes
    display.print(":");
    display.print(now.Second()); //Affichage des secondes
    display.display(); //Affichage de l'écran OLED
}

