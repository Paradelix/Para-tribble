/*

* IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv

* An IR detector/demodulator must be connected to the input RECV_PIN.

* Version 0.1 July, 2009

* Copyright 2009 Ken Shirriff

* http://arcfn.com

*/

#include <IRremote.h>                                 // Einbinden der Bibliothek
#include <LiquidCrystal_I2C.h>                    // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen
LiquidCrystal_I2C lcd(0x27, 20, 4);                 //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall einer mit 16 Zeichen in 2 Zeilen.
int RECV_PIN = 3;                                   // Digitales Signal von Pin 3 abgreifen

IRrecv irrecv(RECV_PIN);  // Bibliothek den Eingangs Pin mitteilen

decode_results results; // Die Ergebnisse decodieren

void setup(){



Serial.begin(9600);                           // Serielle Verbindung aktivieren

pinMode (13, OUTPUT);                                // Pin 13 (LED) als Ausgang festlegen

irrecv.enableIRIn();                                        // Eingang auf Pin 11 aktivieren
  lcd.begin();
}

void loop() {

  if (irrecv.decode(&results)) { // Wenn die IR Bibliothek ein decodiertes Signal liefert ...
  





Serial.println(results.value, DEC  ); // ... dann soll dieses auf der Seriellen Schnittstelle ausgegeben werden

lcd.setCursor(0, 0);                 //Spalte, Zeile
    lcd.print("FB Code lesen      ");
    lcd.setCursor(1, 1);                 //Spalte, Zeile
    lcd.print(results.value, DEC); 
     lcd.setCursor(13, 1);                 //Spalte, Zeile
    lcd.print("Dezimal");   
    
    
    lcd.setCursor(0, 2);                 //Spalte, Zeile
    lcd.print(results.value, HEX); 
     lcd.setCursor(13, 2);                 //Spalte, Zeile
    lcd.print("Hexadez."); 
    
    
    

irrecv.resume(); // neue Messung durchführen

}

}
