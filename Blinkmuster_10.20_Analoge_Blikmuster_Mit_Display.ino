// Pin 13 has an ledL connected on most Arduino boards.
// give it a name:

#include <Wire.h> // Wire Bibliothek hochladen
#include <LiquidCrystal_I2C.h>// Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen
LiquidCrystal_I2C lcd(0x27, 20, 4);   //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall einer mit 16 Zeichen in 2 Zeilen.

int VerA = 10;      // Programmversion
int VerB = 20;      //  Unterversion
   


// Konstanten
const byte BlauR = 5;  //   GRÜNES KABEL****** Blaue Led RECHTE Seite an Pin 6 angeschlossen
const byte BlauL = 6;    // BLAUES KABEL****** Blaue Led LINKE Seite an Pin 5 angeschlossen
const byte RotR = 10;   // ROTES KABEL ******* Rote Led RECHTE Seite an Pin 10 angeschlossen
const byte RotL = 9;   // ORANGENES KABEL***** Rote Led LINKE Seite an Pin 9 angeschlossen
const byte Gelb = 11;   // GELBES KABEL******* Gelbe Led an Pin 11 angeschlossen


long randOn = 0;                  // Initialize a variable for the ON time
long randOff = 0;                 // Initialize a variable for the OFF time

               

int MesswertPinMuster = A0;               //  Musterauswahl über Analog A1
int SensorwertMuster = 0;                // Sensor Wert 0 - 1023 von Musterauswahl
int WertMuster = 0;                     // Muster Nr.

int MesswertPinHelligkeit_Blau = A1;    //    Helligkeitssteuerung Blau über Anqalog A0
int SensorwertHellBlau = 0;           // Sensor Wert 0 - 1023 Blau
int B = 0; // Messwert 0 - 255 Blau
int ProzentBlau = 0;                  // Prozentwert der Helligkeit 0 - 100  Blau

int MesswertPinHelligkeit_Rot = A2;       //    Helligkeitssteuerung über Anqalog A0
int SensorwertHellRot = 0;                // Sensor Wert 0 - 1023 Rot
int R = 0;                                // Messwert 0 - 255 Rot
int ProzentRot = 0;                       // Prozentwert der Helligkeit 0 - 100  Rot

int MesswertPinHelligkeit_Gelb = A3;      //    Helligkeitssteuerung über Anqalog A0
int SensorwertHellGelb = 0;              // Sensor Wert 0 - 1023 Gelb
int G = 0;                               // Messwert 0 - 255 Gelb
int ProzentGelb = 0;                       // Prozentwert der Helligkeit 0 - 100  Gelb

void setup() {    
              
    pinMode(BlauL, OUTPUT);    // Setzt Pin für Linke Blaue LED als Ausgang
   pinMode(BlauR, OUTPUT);    // Setzt Pin für Rechte Blaue LED als Ausgang
   pinMode(RotL, OUTPUT);    // Setzt Pin für Linke Rote LED als Ausgang
  pinMode(RotR, OUTPUT);     // Setzt Pin für Rechte Rote LED als Ausgang
  pinMode(Gelb, OUTPUT);     // Setzt Pin für Gelbe  LED als Ausgang
lcd.begin();
 lcd.clear();
}


void loop(){
// Definition des Musterwahl Knopfes
  SensorwertMuster = analogRead(MesswertPinMuster);
  WertMuster = map(SensorwertMuster, 0, 1023, 0, 10);// **!!!!!! Letze Ziffer definiert die Muster-Anzahl **

  // Definition des Helligkeitspoti
  SensorwertHellBlau = analogRead(MesswertPinHelligkeit_Blau);
  B = map(SensorwertHellBlau, 0, 1023, 0, 255);
  ProzentBlau = map(B, 0, 255, 0, 100);

  SensorwertHellRot = analogRead(MesswertPinHelligkeit_Rot);
  R = map (SensorwertHellRot, 0, 1023, 0, 180);       // ** letze Ziffer, DigitalWert auf entsprechende max. mA der Power LEDS's begrenzen
  ProzentRot = map(R, 0, 180, 0, 100);

  SensorwertHellGelb = analogRead(MesswertPinHelligkeit_Gelb);
  G = map (SensorwertHellGelb, 0, 1023, 0, 195);       // ** letze Ziffer, DigitalWert auf entsprechende max. mA der Power LEDS's begrenzen
  ProzentGelb = map(G, 0, 195, 0, 100);



   if (WertMuster  == 0)  { 
    if ((ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)){
    analogWrite(BlauL, B);
    analogWrite(BlauR, B);
    analogWrite(RotL, R);
    analogWrite(RotR, R);
    analogWrite(Gelb, G);

    lcd.setCursor(0, 0);                 //Spalte, Zeile
    lcd.print("           ");
    lcd.setCursor(0, 1);                 //Spalte, Zeile
    lcd.print("          ");

    lcd.setCursor(10,0);   
lcd.print("     ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("      ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(0,2);  
lcd.print("           ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
lcd.print("                    ");
  lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
  lcd.print(">>Konstant LED AN<<");
  lcd.setCursor(11, 0);
  
    
    }

   }  


 if (WertMuster  == 0)  { 
    if ((ProzentBlau < 3)| (ProzentRot <3) | (ProzentGelb <3)){
    analogWrite(BlauL, LOW);
    analogWrite(BlauR, LOW);
    analogWrite(RotL, LOW);
    analogWrite(RotR, LOW);
    analogWrite(Gelb, LOW);
   
    lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
  lcd.print(" >>> LED's AUS <<<");
  lcd.setCursor(11, 0);
delay(100);
      
    }}
else    if ((WertMuster  == 1) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 



 
 // Hella FWL
{

byte Muster1_BlauLEDre[] = {B,B,B,B,B,0,0,0,B,0,0,0,0,0};
byte Muster1_BlauLEDli[] = {B,B,B,B,B,0,0,0,B,0,0,0,0,0};
byte Muster1_RotLEDre[] =  {0,0,0,0,R,R,R,R,R,0,0,0,R,0};
byte Muster1_RotLEDli[] =  {0,0,0,0,R,R,R,R,R,0,0,0,R,0};
byte Muster1_GelbLED[]  =  {G,G,G,G,G,0,0,0,G,0,0,0,0,0};

analogWrite(BlauL, Muster1_BlauLEDli[0]);   
analogWrite(BlauR, Muster1_BlauLEDre[0]);  
analogWrite(RotL, Muster1_RotLEDli[0]);
analogWrite(RotR, Muster1_RotLEDre[0]);
analogWrite(Gelb, Muster1_GelbLED[0]);
 delay (40);         

analogWrite(BlauL, Muster1_BlauLEDli[1]);   
analogWrite(BlauR, Muster1_BlauLEDre[1]);  
analogWrite(RotL, Muster1_RotLEDli[1]);
analogWrite(RotR, Muster1_RotLEDre[1]);
analogWrite(Gelb, Muster1_GelbLED[1]);
 delay(40);

analogWrite(BlauL, Muster1_BlauLEDli[2]);   
analogWrite(BlauR, Muster1_BlauLEDre[2]);  
analogWrite(RotL, Muster1_RotLEDli[2]);
analogWrite(RotR, Muster1_RotLEDre[2]);
analogWrite(Gelb, Muster1_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster1_BlauLEDli[3]);   
analogWrite(BlauR, Muster1_BlauLEDre[3]);  
analogWrite(RotL, Muster1_RotLEDli[3]);
analogWrite(RotR, Muster1_RotLEDre[3]);
analogWrite(Gelb, Muster1_GelbLED[3]);
 delay(40);
 
analogWrite(BlauL, Muster1_BlauLEDli[4]);   
analogWrite(BlauR, Muster1_BlauLEDre[4]);  
analogWrite(RotL, Muster1_RotLEDli[4]);
analogWrite(RotR, Muster1_RotLEDre[4]);
analogWrite(Gelb, Muster1_GelbLED[4]);
 delay(40);
 
analogWrite(BlauL, Muster1_BlauLEDli[5]);   
analogWrite(BlauR, Muster1_BlauLEDre[5]);  
analogWrite(RotL, Muster1_RotLEDli[5]);
analogWrite(RotR, Muster1_RotLEDre[5]);
analogWrite(Gelb, Muster1_GelbLED[5]);
 delay(40);

analogWrite(BlauL, Muster1_BlauLEDli[6]);   
analogWrite(BlauR, Muster1_BlauLEDre[6]);  
analogWrite(RotL, Muster1_RotLEDli[6]);
analogWrite(RotR, Muster1_RotLEDre[6]);
analogWrite(Gelb, Muster1_GelbLED[6]);
 delay(40);

analogWrite(BlauL, Muster1_BlauLEDli[7]);   
analogWrite(BlauR, Muster1_BlauLEDre[7]);  
analogWrite(RotL, Muster1_RotLEDli[7]);
analogWrite(RotR, Muster1_RotLEDre[7]);
analogWrite(Gelb, Muster1_GelbLED[7]);
 delay(40);

analogWrite(BlauL, Muster1_BlauLEDli[8]);   
analogWrite(BlauR, Muster1_BlauLEDre[8]);  
analogWrite(RotL, Muster1_RotLEDli[8]);
analogWrite(RotR, Muster1_RotLEDre[8]);
analogWrite(Gelb, Muster1_GelbLED[8]);
 delay(40);

 analogWrite(BlauL, Muster1_BlauLEDli[9]);   
analogWrite(BlauR, Muster1_BlauLEDre[9]);  
analogWrite(RotL, Muster1_RotLEDli[9]);
analogWrite(RotR, Muster1_RotLEDre[9]);
analogWrite(Gelb, Muster1_GelbLED[9]);
  delay(40);


 analogWrite(BlauL, Muster1_BlauLEDli[10]);   
analogWrite(BlauR, Muster1_BlauLEDre[10]);  
analogWrite(RotL, Muster1_RotLEDli[10]);
analogWrite(RotR, Muster1_RotLEDre[10]);
analogWrite(Gelb, Muster1_GelbLED[10]);
  delay(40);



 analogWrite(BlauL, Muster1_BlauLEDli[11]);   
analogWrite(BlauR, Muster1_BlauLEDre[11]);  
analogWrite(RotL, Muster1_RotLEDli[11]);
analogWrite(RotR, Muster1_RotLEDre[11]);
analogWrite(Gelb, Muster1_GelbLED[11]);
  delay(40);



 analogWrite(BlauL, Muster1_BlauLEDli[12]);   
analogWrite(BlauR, Muster1_BlauLEDre[12]);  
analogWrite(RotL, Muster1_RotLEDli[12]);
analogWrite(RotR, Muster1_RotLEDre[12]);
analogWrite(Gelb, Muster1_GelbLED[12]);
  delay(40);




 analogWrite(BlauL, Muster1_BlauLEDli[13]);   
analogWrite(BlauR, Muster1_BlauLEDre[13]);  
analogWrite(RotL, Muster1_RotLEDli[13]);
analogWrite(RotR, Muster1_RotLEDre[13]);
analogWrite(Gelb, Muster1_GelbLED[13]);
  delay(40);

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");

 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("      ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("HELA FWL");
    //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);

lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);

lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
}  
}

else    if ((WertMuster  == 2) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 
  // 3 Fachblitz, danach leuchtend, synchron
byte Muster2_BlauLEDre[] = {B,0,B,0,B,0,B,B,B,B,B,0,0,0,0,0};  
byte Muster2_BlauLEDli[] = {B,0,B,0,B,0,B,B,B,B,B,0,0,0,0,0};  

byte Muster2_RotLEDre[]=   {R,R,R,R,R,0,0,0,0,0,R,0,R,0,R,0};
byte Muster2_RotLEDli[]=   {R,R,R,R,R,0,0,0,0,0,R,0,R,0,R,0};
byte Muster2_GelbLED[] =   {G,0,G,0,G,0,G,G,G,G,G,0,0,0,0,0};  
 analogWrite(BlauL, Muster2_BlauLEDli[0]);   
 analogWrite(BlauR, Muster2_BlauLEDre[0]);  
 analogWrite(RotL, Muster2_RotLEDli[0]);
 analogWrite(RotR, Muster2_RotLEDre[0]);
 analogWrite(Gelb, Muster2_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster2_BlauLEDli[1]);   
 analogWrite(BlauR, Muster2_BlauLEDre[1]);  
 analogWrite(RotL, Muster2_RotLEDli[1]);
 analogWrite(RotR, Muster2_RotLEDre[1]);
 analogWrite(Gelb, Muster2_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster2_BlauLEDli[2]);   
 analogWrite(BlauR, Muster2_BlauLEDre[2]);  
 analogWrite(RotL, Muster2_RotLEDli[2]);
 analogWrite(RotR, Muster2_RotLEDre[2]);
 analogWrite(Gelb, Muster2_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster2_BlauLEDli[3]);   
 analogWrite(BlauR, Muster2_BlauLEDre[3]);  
 analogWrite(RotL, Muster2_RotLEDli[3]);
 analogWrite(RotR, Muster2_RotLEDre[3]);
 analogWrite(Gelb, Muster2_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster2_BlauLEDli[4]);   
 analogWrite(BlauR, Muster2_BlauLEDre[4]);  
 analogWrite(RotL, Muster2_RotLEDli[4]);
 analogWrite(RotR, Muster2_RotLEDre[4]);
 analogWrite(Gelb, Muster2_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster2_BlauLEDli[5]);   
 analogWrite(BlauR, Muster2_BlauLEDre[5]);  
 analogWrite(RotL, Muster2_RotLEDli[5]);
 analogWrite(RotR, Muster2_RotLEDre[5]);
 analogWrite(Gelb, Muster2_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster2_BlauLEDli[6]);   
 analogWrite(BlauR, Muster2_BlauLEDre[6]);  
 analogWrite(RotL, Muster2_RotLEDli[6]);
 analogWrite(RotR, Muster2_RotLEDre[6]);
 analogWrite(Gelb, Muster2_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster2_BlauLEDli[7]);   
 analogWrite(BlauR, Muster2_BlauLEDre[7]);  
 analogWrite(RotL, Muster2_RotLEDli[7]);
 analogWrite(RotR, Muster2_RotLEDre[7]);
 analogWrite(Gelb, Muster2_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster2_BlauLEDli[8]);   
 analogWrite(BlauR, Muster2_BlauLEDre[8]);  
 analogWrite(RotL, Muster2_RotLEDli[8]);
 analogWrite(RotR, Muster2_RotLEDre[8]);
 analogWrite(Gelb, Muster2_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[9]);   
 analogWrite(BlauR, Muster2_BlauLEDre[9]);  
 analogWrite(RotL, Muster2_RotLEDli[9]);
 analogWrite(RotR, Muster2_RotLEDre[9]);
 analogWrite(Gelb, Muster2_GelbLED[9]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[10]);   
 analogWrite(BlauR, Muster2_BlauLEDre[10]);  
 analogWrite(RotL, Muster2_RotLEDli[10]);
 analogWrite(RotR, Muster2_RotLEDre[10]);
 analogWrite(Gelb, Muster2_GelbLED[10]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[11]);   
 analogWrite(BlauR, Muster2_BlauLEDre[11]);  
 analogWrite(RotL, Muster2_RotLEDli[11]);
 analogWrite(RotR, Muster2_RotLEDre[11]);
 analogWrite(Gelb, Muster2_GelbLED[11]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[12]);   
 analogWrite(BlauR, Muster2_BlauLEDre[12]);  
 analogWrite(RotL, Muster2_RotLEDli[12]);
 analogWrite(RotR, Muster2_RotLEDre[12]);
 analogWrite(Gelb, Muster2_GelbLED[12]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[13]);   
 analogWrite(BlauR, Muster2_BlauLEDre[13]);  
 analogWrite(RotL, Muster2_RotLEDli[13]);
 analogWrite(RotR, Muster2_RotLEDre[13]);
 analogWrite(Gelb, Muster2_GelbLED[13]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[14]);   
 analogWrite(BlauR, Muster2_BlauLEDre[14]);  
 analogWrite(RotL, Muster2_RotLEDli[14]);
 analogWrite(RotR, Muster2_RotLEDre[14]);
 analogWrite(Gelb, Muster2_GelbLED[14]);
  delay(40);

  analogWrite(BlauL, Muster2_BlauLEDli[15]);   
 analogWrite(BlauR, Muster2_BlauLEDre[15]);  
 analogWrite(RotL, Muster2_RotLEDli[15]);
 analogWrite(RotR, Muster2_RotLEDre[15]);
 analogWrite(Gelb, Muster2_GelbLED[15]);
  delay(40);


  lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");

 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("3er Blitz->blinken");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
}

 
else    if ((WertMuster  == 3) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

  // 3 Fachblitz, synchron
byte Muster3_BlauLEDre[] = {B,0,B,0,B,0,0,0,0,0,0,0};
byte Muster3_BlauLEDli[] = {B,0,B,0,B,0,0,0,0,0,0,0};
byte Muster3_RotLEDre[]=   {0,0,0,0,0,0,R,0,R,0,R,0};
byte Muster3_RotLEDli[]=   {0,0,0,0,0,0,R,0,R,0,R,0};
byte Muster3_GelbLED[] =   {0,G,0,G,0,G,0,0,0,0,0,0};

 analogWrite(BlauL, Muster3_BlauLEDli[0]);   
 analogWrite(BlauR, Muster3_BlauLEDre[0]);  
 analogWrite(RotL, Muster3_RotLEDli[0]);
 analogWrite(RotR, Muster3_RotLEDre[0]);
 analogWrite(Gelb, Muster3_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster3_BlauLEDli[1]);   
 analogWrite(BlauR, Muster3_BlauLEDre[1]);  
 analogWrite(RotL, Muster3_RotLEDli[1]);
 analogWrite(RotR, Muster3_RotLEDre[1]);
 analogWrite(Gelb, Muster3_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster3_BlauLEDli[2]);   
 analogWrite(BlauR, Muster3_BlauLEDre[2]);  
 analogWrite(RotL, Muster3_RotLEDli[2]);
 analogWrite(RotR, Muster3_RotLEDre[2]);
 analogWrite(Gelb, Muster3_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster3_BlauLEDli[3]);   
 analogWrite(BlauR, Muster3_BlauLEDre[3]);  
 analogWrite(RotL, Muster3_RotLEDli[3]);
 analogWrite(RotR, Muster3_RotLEDre[3]);
 analogWrite(Gelb, Muster3_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster3_BlauLEDli[4]);   
 analogWrite(BlauR, Muster3_BlauLEDre[4]);  
 analogWrite(RotL, Muster3_RotLEDli[4]);
 analogWrite(RotR, Muster3_RotLEDre[4]);
 analogWrite(Gelb, Muster3_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster3_BlauLEDli[5]);   
 analogWrite(BlauR, Muster3_BlauLEDre[5]);  
 analogWrite(RotL, Muster3_RotLEDli[5]);
 analogWrite(RotR, Muster3_RotLEDre[5]);
 analogWrite(Gelb, Muster3_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster3_BlauLEDli[6]);   
 analogWrite(BlauR, Muster3_BlauLEDre[6]);  
 analogWrite(RotL, Muster3_RotLEDli[6]);
 analogWrite(RotR, Muster3_RotLEDre[6]);
 analogWrite(Gelb, Muster3_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster3_BlauLEDli[7]);   
 analogWrite(BlauR, Muster3_BlauLEDre[7]);  
 analogWrite(RotL, Muster3_RotLEDli[7]);
 analogWrite(RotR, Muster3_RotLEDre[7]);
 analogWrite(Gelb, Muster3_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster3_BlauLEDli[8]);   
 analogWrite(BlauR, Muster3_BlauLEDre[8]);  
 analogWrite(RotL, Muster3_RotLEDli[8]);
 analogWrite(RotR, Muster3_RotLEDre[8]);
 analogWrite(Gelb, Muster3_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster3_BlauLEDli[9]);   
 analogWrite(BlauR, Muster3_BlauLEDre[9]);  
 analogWrite(RotL, Muster3_RotLEDli[9]);
 analogWrite(RotR, Muster3_RotLEDre[9]);
 analogWrite(Gelb, Muster3_GelbLED[9]);
  delay(40);


  analogWrite(BlauL, Muster3_BlauLEDli[10]);   
 analogWrite(BlauR, Muster3_BlauLEDre[10]);  
 analogWrite(RotL, Muster3_RotLEDli[10]);
 analogWrite(RotR, Muster3_RotLEDre[10]);
 analogWrite(Gelb, Muster3_GelbLED[10]);
  delay(40);



  analogWrite(BlauL, Muster3_BlauLEDli[11]);   
 analogWrite(BlauR, Muster3_BlauLEDre[11]);  
 analogWrite(RotL, Muster3_RotLEDli[11]);
 analogWrite(RotR, Muster3_RotLEDre[11]);
 analogWrite(Gelb, Muster3_GelbLED[11]);
  delay(40);

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
  
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("3 Fach Blitz");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
 }

else  if ((WertMuster  == 4) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

  // 4 Fachblitz, synchron
byte Muster4_BlauLEDre[] = {B,0,B,0,B,0,B,0,0,0,0,0,0,0};
byte Muster4_BlauLEDli[] = {B,0,B,0,B,0,B,0,0,0,0,0,0,0};
byte Muster4_RotLEDre[]=   {0,0,0,0,0,0,0,R,0,R,0,R,0,R};
byte Muster4_RotLEDli[]=   {0,0,0,0,0,0,0,R,0,R,0,R,0,R};
byte Muster4_GelbLED[] =   {0,0,0,0,0,G,0,G,0,G,0,G,0,0};

   analogWrite(BlauL, Muster4_BlauLEDli[0]);   
 analogWrite(BlauR, Muster4_BlauLEDre[0]);  
 analogWrite(RotL, Muster4_RotLEDli[0]);
 analogWrite(RotR, Muster4_RotLEDre[0]);
 analogWrite(Gelb, Muster4_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster4_BlauLEDli[1]);   
 analogWrite(BlauR, Muster4_BlauLEDre[1]);  
 analogWrite(RotL, Muster4_RotLEDli[1]);
 analogWrite(RotR, Muster4_RotLEDre[1]);
 analogWrite(Gelb, Muster4_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster4_BlauLEDli[2]);   
 analogWrite(BlauR, Muster4_BlauLEDre[2]);  
 analogWrite(RotL, Muster4_RotLEDli[2]);
 analogWrite(RotR, Muster4_RotLEDre[2]);
 analogWrite(Gelb, Muster4_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster4_BlauLEDli[3]);   
 analogWrite(BlauR, Muster4_BlauLEDre[3]);  
 analogWrite(RotL, Muster4_RotLEDli[3]);
 analogWrite(RotR, Muster4_RotLEDre[3]);
 analogWrite(Gelb, Muster4_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster4_BlauLEDli[4]);   
 analogWrite(BlauR, Muster4_BlauLEDre[4]);  
 analogWrite(RotL, Muster4_RotLEDli[4]);
 analogWrite(RotR, Muster4_RotLEDre[4]);
 analogWrite(Gelb, Muster4_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster4_BlauLEDli[5]);   
 analogWrite(BlauR, Muster4_BlauLEDre[5]);  
 analogWrite(RotL, Muster4_RotLEDli[5]);
 analogWrite(RotR, Muster4_RotLEDre[5]);
 analogWrite(Gelb, Muster4_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster4_BlauLEDli[6]);   
 analogWrite(BlauR, Muster4_BlauLEDre[6]);  
 analogWrite(RotL, Muster4_RotLEDli[6]);
 analogWrite(RotR, Muster4_RotLEDre[6]);
 analogWrite(Gelb, Muster4_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster4_BlauLEDli[7]);   
 analogWrite(BlauR, Muster4_BlauLEDre[7]);  
 analogWrite(RotL, Muster4_RotLEDli[7]);
 analogWrite(RotR, Muster4_RotLEDre[7]);
 analogWrite(Gelb, Muster4_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster4_BlauLEDli[8]);   
 analogWrite(BlauR, Muster4_BlauLEDre[8]);  
 analogWrite(RotL, Muster4_RotLEDli[8]);
 analogWrite(RotR, Muster4_RotLEDre[8]);
 analogWrite(Gelb, Muster4_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster4_BlauLEDli[9]);   
 analogWrite(BlauR, Muster4_BlauLEDre[9]);  
 analogWrite(RotL, Muster4_RotLEDli[9]);
 analogWrite(RotR, Muster4_RotLEDre[9]);
 analogWrite(Gelb, Muster4_GelbLED[9]);
  delay(40);


  analogWrite(BlauL, Muster4_BlauLEDli[10]);   
 analogWrite(BlauR, Muster4_BlauLEDre[10]);  
 analogWrite(RotL, Muster4_RotLEDli[10]);
 analogWrite(RotR, Muster4_RotLEDre[10]);
 analogWrite(Gelb, Muster4_GelbLED[10]);
  delay(40);



  analogWrite(BlauL, Muster4_BlauLEDli[11]);   
 analogWrite(BlauR, Muster4_BlauLEDre[11]);  
 analogWrite(RotL, Muster4_RotLEDli[11]);
 analogWrite(RotR, Muster4_RotLEDre[11]);
 analogWrite(Gelb, Muster4_GelbLED[11]);
  delay(40);



  analogWrite(BlauL, Muster4_BlauLEDli[12]);   
 analogWrite(BlauR, Muster4_BlauLEDre[12]);  
 analogWrite(RotL, Muster4_RotLEDli[12]);
 analogWrite(RotR, Muster4_RotLEDre[12]);
 analogWrite(Gelb, Muster4_GelbLED[12]);
  delay(40);

  lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("4 Fach Blitz");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
 }
 

else  if ((WertMuster  == 5) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

  // 2 Fachblitz, synchron
byte Muster5_BlauLEDre[] = {B,0,B,0,0,0,0,0};
byte Muster5_BlauLEDli[] = {B,0,B,0,0,0,0,0};
byte Muster5_RotLEDre[]=   {0,0,0,0,R,0,R,0};
byte Muster5_RotLEDli[]=   {0,0,0,0,R,0,R,0};
byte Muster5_GelbLED[] =   {0,G,0,G,0,0,0,0};
  
   analogWrite(BlauL, Muster5_BlauLEDli[0]);   
 analogWrite(BlauR, Muster5_BlauLEDre[0]);  
 analogWrite(RotL, Muster5_RotLEDli[0]);
 analogWrite(RotR, Muster5_RotLEDre[0]);
 analogWrite(Gelb, Muster5_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster5_BlauLEDli[1]);   
 analogWrite(BlauR, Muster5_BlauLEDre[1]);  
 analogWrite(RotL, Muster5_RotLEDli[1]);
 analogWrite(RotR, Muster5_RotLEDre[1]);
 analogWrite(Gelb, Muster5_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster5_BlauLEDli[2]);   
 analogWrite(BlauR, Muster5_BlauLEDre[2]);  
 analogWrite(RotL, Muster5_RotLEDli[2]);
 analogWrite(RotR, Muster5_RotLEDre[2]);
 analogWrite(Gelb, Muster5_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster5_BlauLEDli[3]);   
 analogWrite(BlauR, Muster5_BlauLEDre[3]);  
 analogWrite(RotL, Muster5_RotLEDli[3]);
 analogWrite(RotR, Muster5_RotLEDre[3]);
 analogWrite(Gelb, Muster5_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster5_BlauLEDli[4]);   
 analogWrite(BlauR, Muster5_BlauLEDre[4]);  
 analogWrite(RotL, Muster5_RotLEDli[4]);
 analogWrite(RotR, Muster5_RotLEDre[4]);
 analogWrite(Gelb, Muster5_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster5_BlauLEDli[5]);   
 analogWrite(BlauR, Muster5_BlauLEDre[5]);  
 analogWrite(RotL, Muster5_RotLEDli[5]);
 analogWrite(RotR, Muster5_RotLEDre[5]);
 analogWrite(Gelb, Muster5_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster5_BlauLEDli[6]);   
 analogWrite(BlauR, Muster5_BlauLEDre[6]);  
 analogWrite(RotL, Muster5_RotLEDli[6]);
 analogWrite(RotR, Muster5_RotLEDre[6]);
 analogWrite(Gelb, Muster5_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster5_BlauLEDli[7]);   
 analogWrite(BlauR, Muster5_BlauLEDre[7]);  
 analogWrite(RotL, Muster5_RotLEDli[7]);
 analogWrite(RotR, Muster5_RotLEDre[7]);
 analogWrite(Gelb, Muster5_GelbLED[7]);
 delay(40);
 
lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("    ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("2 Fach Blitz     ");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
 }

 else  if ((WertMuster  == 6) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

    // 2 mal Blinken, synchron / wechsel
byte Muster6_BlauLEDre[] = {B,B,B,0,0,0,B,B,B,0,0,0,B,B,B,0,0,0,0,0,0,0,0,0};
byte Muster6_BlauLEDli[] = {B,B,B,0,0,0,B,B,B,0,0,0,0,0,0,0,0,0,B,B,B,0,0,0};
byte Muster6_RotLEDre[]=   {0,0,0,R,R,R,0,0,0,R,R,R,0,0,0,0,0,0,0,0,0,R,R,R};
byte Muster6_RotLEDli[]=   {0,0,0,R,R,R,0,0,0,R,R,R,0,0,0,R,R,R,0,0,0,0,0,0};
byte Muster6_GelbLED[] =   {0,G,G,G,0,0,0,G,G,G,0,0,0,G,G,G,0,0,0,G,G,G,0,0};

  analogWrite(BlauL, Muster6_BlauLEDli[0]);   
 analogWrite(BlauR, Muster6_BlauLEDre[0]);  
 analogWrite(RotL, Muster6_RotLEDli[0]);
 analogWrite(RotR, Muster6_RotLEDre[0]);
 analogWrite(Gelb, Muster6_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster6_BlauLEDli[1]);   
 analogWrite(BlauR, Muster6_BlauLEDre[1]);  
 analogWrite(RotL, Muster6_RotLEDli[1]);
 analogWrite(RotR, Muster6_RotLEDre[1]);
 analogWrite(Gelb, Muster6_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster6_BlauLEDli[2]);   
 analogWrite(BlauR, Muster6_BlauLEDre[2]);  
 analogWrite(RotL, Muster6_RotLEDli[2]);
 analogWrite(RotR, Muster6_RotLEDre[2]);
 analogWrite(Gelb, Muster6_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster6_BlauLEDli[3]);   
 analogWrite(BlauR, Muster6_BlauLEDre[3]);  
 analogWrite(RotL, Muster6_RotLEDli[3]);
 analogWrite(RotR, Muster6_RotLEDre[3]);
 analogWrite(Gelb, Muster6_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster6_BlauLEDli[4]);   
 analogWrite(BlauR, Muster6_BlauLEDre[4]);  
 analogWrite(RotL, Muster6_RotLEDli[4]);
 analogWrite(RotR, Muster6_RotLEDre[4]);
 analogWrite(Gelb, Muster6_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster6_BlauLEDli[5]);   
 analogWrite(BlauR, Muster6_BlauLEDre[5]);  
 analogWrite(RotL, Muster6_RotLEDli[5]);
 analogWrite(RotR, Muster6_RotLEDre[5]);
 analogWrite(Gelb, Muster6_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster6_BlauLEDli[6]);   
 analogWrite(BlauR, Muster6_BlauLEDre[6]);  
 analogWrite(RotL, Muster6_RotLEDli[6]);
 analogWrite(RotR, Muster6_RotLEDre[6]);
 analogWrite(Gelb, Muster6_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster6_BlauLEDli[7]);   
 analogWrite(BlauR, Muster6_BlauLEDre[7]);  
 analogWrite(RotL, Muster6_RotLEDli[7]);
 analogWrite(RotR, Muster6_RotLEDre[7]);
 analogWrite(Gelb, Muster6_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster6_BlauLEDli[8]);   
 analogWrite(BlauR, Muster6_BlauLEDre[8]);  
 analogWrite(RotL, Muster6_RotLEDli[8]);
 analogWrite(RotR, Muster6_RotLEDre[8]);
 analogWrite(Gelb, Muster6_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster6_BlauLEDli[9]);   
 analogWrite(BlauR, Muster6_BlauLEDre[9]);  
 analogWrite(RotL, Muster6_RotLEDli[9]);
 analogWrite(RotR, Muster6_RotLEDre[9]);
 analogWrite(Gelb, Muster6_GelbLED[9]);
  delay(40);


  analogWrite(BlauL, Muster6_BlauLEDli[10]);   
 analogWrite(BlauR, Muster6_BlauLEDre[10]);  
 analogWrite(RotL, Muster6_RotLEDli[10]);
 analogWrite(RotR, Muster6_RotLEDre[10]);
 analogWrite(Gelb, Muster6_GelbLED[10]);
  delay(40);



  analogWrite(BlauL, Muster6_BlauLEDli[11]);   
 analogWrite(BlauR, Muster6_BlauLEDre[11]);  
 analogWrite(RotL, Muster6_RotLEDli[11]);
 analogWrite(RotR, Muster6_RotLEDre[11]);
 analogWrite(Gelb, Muster6_GelbLED[11]);
  delay(40);



  analogWrite(BlauL, Muster6_BlauLEDli[12]);   
 analogWrite(BlauR, Muster6_BlauLEDre[12]);  
 analogWrite(RotL, Muster6_RotLEDli[12]);
 analogWrite(RotR, Muster6_RotLEDre[12]);
 analogWrite(Gelb, Muster6_GelbLED[12]);
  delay(40);




  analogWrite(BlauL, Muster6_BlauLEDli[13]);   
 analogWrite(BlauR, Muster6_BlauLEDre[13]);  
 analogWrite(RotL, Muster6_RotLEDli[13]);
 analogWrite(RotR, Muster6_RotLEDre[13]);
 analogWrite(Gelb, Muster6_GelbLED[13]);
  delay(40);



  analogWrite(BlauL, Muster6_BlauLEDli[14]);   
 analogWrite(BlauR, Muster6_BlauLEDre[14]);  
 analogWrite(RotL, Muster6_RotLEDli[14]);
 analogWrite(RotR, Muster6_RotLEDre[14]);
 analogWrite(Gelb, Muster6_GelbLED[14]);
  delay(40);


  analogWrite(BlauL, Muster6_BlauLEDli[15]);   
 analogWrite(BlauR, Muster6_BlauLEDre[15]);  
 analogWrite(RotL, Muster6_RotLEDli[15]);
 analogWrite(RotR, Muster6_RotLEDre[15]);
 analogWrite(Gelb, Muster6_GelbLED[15]);
  delay(40);


  analogWrite(BlauL, Muster6_BlauLEDli[16]);   
 analogWrite(BlauR, Muster6_BlauLEDre[16]);  
 analogWrite(RotL, Muster6_RotLEDli[16]);
 analogWrite(RotR, Muster6_RotLEDre[16]);
 analogWrite(Gelb, Muster6_GelbLED[16]);
  delay(40);


analogWrite(BlauL, Muster6_BlauLEDli[17]);   
 analogWrite(BlauR, Muster6_BlauLEDre[17]);  
 analogWrite(RotL, Muster6_RotLEDli[17]);
 analogWrite(RotR, Muster6_RotLEDre[17]);
 analogWrite(Gelb, Muster6_GelbLED[17]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[18]);   
 analogWrite(BlauR, Muster6_BlauLEDre[18]);  
 analogWrite(RotL, Muster6_RotLEDli[18]);
 analogWrite(RotR, Muster6_RotLEDre[18]);
 analogWrite(Gelb, Muster6_GelbLED[18]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[19]);   
 analogWrite(BlauR, Muster6_BlauLEDre[19]);  
 analogWrite(RotL, Muster6_RotLEDli[19]);
 analogWrite(RotR, Muster6_RotLEDre[19]);
 analogWrite(Gelb, Muster6_GelbLED[19]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[20]);   
 analogWrite(BlauR, Muster6_BlauLEDre[20]);  
 analogWrite(RotL, Muster6_RotLEDli[20]);
 analogWrite(RotR, Muster6_RotLEDre[20]);
 analogWrite(Gelb, Muster6_GelbLED[20]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[21]);   
 analogWrite(BlauR, Muster6_BlauLEDre[21]);  
 analogWrite(RotL, Muster6_RotLEDli[21]);
 analogWrite(RotR, Muster6_RotLEDre[21]);
 analogWrite(Gelb, Muster6_GelbLED[21]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[22]);   
 analogWrite(BlauR, Muster6_BlauLEDre[22]);  
 analogWrite(RotL, Muster6_RotLEDli[22]);
 analogWrite(RotR, Muster6_RotLEDre[22]);
 analogWrite(Gelb, Muster6_GelbLED[22]);
 delay(40);

analogWrite(BlauL, Muster6_BlauLEDli[23]);   
 analogWrite(BlauR, Muster6_BlauLEDre[23]);  
 analogWrite(RotL, Muster6_RotLEDli[23]);
 analogWrite(RotR, Muster6_RotLEDre[23]);
 analogWrite(Gelb, Muster6_GelbLED[23]);
 delay(40);

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("2xBlink async");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
 }

else  if ((WertMuster  == 7) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 
  // 2 mal blinken, wechsel
  
byte Muster7_BlauLEDre[] = {B,0,B,0,0,0,0,0};
byte Muster7_BlauLEDli[] = {0,0,0,0,B,0,B,0};
byte Muster7_RotLEDre[]=   {0,R,0,R,0,0,0,0};
byte Muster7_RotLEDli[]=   {0,0,0,0,0,R,0,R};
byte Muster7_GelbLED[] =   {G,G,0,G,G,0,G,0};

  analogWrite(BlauL, Muster7_BlauLEDli[0]);   
 analogWrite(BlauR, Muster7_BlauLEDre[0]);  
 analogWrite(RotL, Muster7_RotLEDli[0]);
 analogWrite(RotR, Muster7_RotLEDre[0]);
 analogWrite(Gelb, Muster7_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster7_BlauLEDli[1]);   
 analogWrite(BlauR, Muster7_BlauLEDre[1]);  
 analogWrite(RotL, Muster7_RotLEDli[1]);
 analogWrite(RotR, Muster7_RotLEDre[1]);
 analogWrite(Gelb, Muster7_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster7_BlauLEDli[2]);   
 analogWrite(BlauR, Muster7_BlauLEDre[2]);  
 analogWrite(RotL, Muster7_RotLEDli[2]);
 analogWrite(RotR, Muster7_RotLEDre[2]);
 analogWrite(Gelb, Muster7_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster7_BlauLEDli[3]);   
 analogWrite(BlauR, Muster7_BlauLEDre[3]);  
 analogWrite(RotL, Muster7_RotLEDli[3]);
 analogWrite(RotR, Muster7_RotLEDre[3]);
 analogWrite(Gelb, Muster7_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster7_BlauLEDli[4]);   
 analogWrite(BlauR, Muster7_BlauLEDre[4]);  
 analogWrite(RotL, Muster7_RotLEDli[4]);
 analogWrite(RotR, Muster7_RotLEDre[4]);
 analogWrite(Gelb, Muster7_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster7_BlauLEDli[5]);   
 analogWrite(BlauR, Muster7_BlauLEDre[5]);  
 analogWrite(RotL, Muster7_RotLEDli[5]);
 analogWrite(RotR, Muster7_RotLEDre[5]);
 analogWrite(Gelb, Muster7_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster7_BlauLEDli[6]);   
 analogWrite(BlauR, Muster7_BlauLEDre[6]);  
 analogWrite(RotL, Muster7_RotLEDli[6]);
 analogWrite(RotR, Muster7_RotLEDre[6]);
 analogWrite(Gelb, Muster7_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster7_BlauLEDli[7]);   
 analogWrite(BlauR, Muster7_BlauLEDre[7]);  
 analogWrite(RotL, Muster7_RotLEDli[7]);
 analogWrite(RotR, Muster7_RotLEDre[7]);
 analogWrite(Gelb, Muster7_GelbLED[7]);
 delay(40);

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("2er Blinken, wechsel");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");

 }

else  if ((WertMuster  == 8) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

 // 4 Fachblitz und 1 Fachblitz, wechsel
byte Muster8_BlauLEDre[] = {B,0,B,0,B,0,B,0,0,0,0,0,0,0,0,0,B,0,B,0,B,0,B,0,0,0,B,0,0,0,B,0,0,0,B,0};
byte Muster8_BlauLEDli[] = {0,0,0,0,0,0,0,0,B,0,B,0,B,0,B,0,0,0,0,0,0,0,0,0,B,0,0,0,B,0,0,0,B,0,0,0};
byte Muster8_RotLEDre[]=   {0,0,0,0,0,0,0,0,R,0,R,0,R,0,R,0,0,0,0,0,0,0,0,0,R,0,0,0,R,0,0,0,R,0,0,0};
byte Muster8_RotLEDli[]=   {R,0,R,0,R,0,R,0,0,0,0,0,0,0,0,0,R,0,R,0,R,0,R,0,0,0,R,0,0,0,R,0,0,0,R,0};
byte Muster8_GelbLED[] =   {G,0,G,0,G,0,G,0,0,0,0,0,0,0,0,0,G,0,G,0,G,0,G,0,0,0,G,0,0,0,G,0,0,0,G,0};


 analogWrite(BlauL, Muster8_BlauLEDli[0]);   
 analogWrite(BlauR, Muster8_BlauLEDre[0]);  
 analogWrite(RotL, Muster8_RotLEDli[0]);
 analogWrite(RotR, Muster8_RotLEDre[0]);
 analogWrite(Gelb, Muster8_GelbLED[0]);
  delay(40);        

 analogWrite(BlauL, Muster8_BlauLEDli[1]);   
 analogWrite(BlauR, Muster8_BlauLEDre[1]);  
 analogWrite(RotL, Muster8_RotLEDli[1]);
 analogWrite(RotR, Muster8_RotLEDre[1]);
 analogWrite(Gelb, Muster8_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster8_BlauLEDli[2]);   
 analogWrite(BlauR, Muster8_BlauLEDre[2]);  
 analogWrite(RotL, Muster8_RotLEDli[2]);
 analogWrite(RotR, Muster8_RotLEDre[2]);
 analogWrite(Gelb, Muster8_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster8_BlauLEDli[3]);   
 analogWrite(BlauR, Muster8_BlauLEDre[3]);  
 analogWrite(RotL, Muster8_RotLEDli[3]);
 analogWrite(RotR, Muster8_RotLEDre[3]);
 analogWrite(Gelb, Muster8_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster8_BlauLEDli[4]);   
 analogWrite(BlauR, Muster8_BlauLEDre[4]);  
 analogWrite(RotL, Muster8_RotLEDli[4]);
 analogWrite(RotR, Muster8_RotLEDre[4]);
 analogWrite(Gelb, Muster8_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster8_BlauLEDli[5]);   
 analogWrite(BlauR, Muster8_BlauLEDre[5]);  
 analogWrite(RotL, Muster8_RotLEDli[5]);
 analogWrite(RotR, Muster8_RotLEDre[5]);
 analogWrite(Gelb, Muster8_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster8_BlauLEDli[6]);   
 analogWrite(BlauR, Muster8_BlauLEDre[6]);  
 analogWrite(RotL, Muster8_RotLEDli[6]);
 analogWrite(RotR, Muster8_RotLEDre[6]);
 analogWrite(Gelb, Muster8_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster8_BlauLEDli[7]);   
 analogWrite(BlauR, Muster8_BlauLEDre[7]);  
 analogWrite(RotL, Muster8_RotLEDli[7]);
 analogWrite(RotR, Muster8_RotLEDre[7]);
 analogWrite(Gelb, Muster8_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster8_BlauLEDli[8]);   
 analogWrite(BlauR, Muster8_BlauLEDre[8]);  
 analogWrite(RotL, Muster8_RotLEDli[8]);
 analogWrite(RotR, Muster8_RotLEDre[8]);
 analogWrite(Gelb, Muster8_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster8_BlauLEDli[9]);   
 analogWrite(BlauR, Muster8_BlauLEDre[9]);  
 analogWrite(RotL, Muster8_RotLEDli[9]);
 analogWrite(RotR, Muster8_RotLEDre[9]);
 analogWrite(Gelb, Muster8_GelbLED[9]);
  delay(40);


  analogWrite(BlauL, Muster8_BlauLEDli[10]);   
 analogWrite(BlauR, Muster8_BlauLEDre[10]);  
 analogWrite(RotL, Muster8_RotLEDli[10]);
 analogWrite(RotR, Muster8_RotLEDre[10]);
 analogWrite(Gelb, Muster8_GelbLED[10]);
  delay(40);



  analogWrite(BlauL, Muster8_BlauLEDli[11]);   
 analogWrite(BlauR, Muster8_BlauLEDre[11]);  
 analogWrite(RotL, Muster8_RotLEDli[11]);
 analogWrite(RotR, Muster8_RotLEDre[11]);
 analogWrite(Gelb, Muster8_GelbLED[11]);
  delay(40);



  analogWrite(BlauL, Muster8_BlauLEDli[12]);   
 analogWrite(BlauR, Muster8_BlauLEDre[12]);  
 analogWrite(RotL, Muster8_RotLEDli[12]);
 analogWrite(RotR, Muster8_RotLEDre[12]);
 analogWrite(Gelb, Muster8_GelbLED[12]);
  delay(40);




  analogWrite(BlauL, Muster8_BlauLEDli[13]);   
 analogWrite(BlauR, Muster8_BlauLEDre[13]);  
 analogWrite(RotL, Muster8_RotLEDli[13]);
 analogWrite(RotR, Muster8_RotLEDre[13]);
 analogWrite(Gelb, Muster8_GelbLED[13]);
  delay(40);



  analogWrite(BlauL, Muster8_BlauLEDli[14]);   
 analogWrite(BlauR, Muster8_BlauLEDre[14]);  
 analogWrite(RotL, Muster8_RotLEDli[14]);
 analogWrite(RotR, Muster8_RotLEDre[14]);
 analogWrite(Gelb, Muster8_GelbLED[14]);
  delay(40);


  analogWrite(BlauL, Muster8_BlauLEDli[15]);   
 analogWrite(BlauR, Muster8_BlauLEDre[15]);  
 analogWrite(RotL, Muster8_RotLEDli[15]);
 analogWrite(RotR, Muster8_RotLEDre[15]);
 analogWrite(Gelb, Muster8_GelbLED[15]);
  delay(40);


  analogWrite(BlauL, Muster8_BlauLEDli[16]);   
 analogWrite(BlauR, Muster8_BlauLEDre[16]);  
 analogWrite(RotL, Muster8_RotLEDli[16]);
 analogWrite(RotR, Muster8_RotLEDre[16]);
 analogWrite(Gelb, Muster8_GelbLED[16]);
  delay(40);


analogWrite(BlauL, Muster8_BlauLEDli[17]);   
 analogWrite(BlauR, Muster8_BlauLEDre[17]);  
 analogWrite(RotL, Muster8_RotLEDli[17]);
 analogWrite(RotR, Muster8_RotLEDre[17]);
 analogWrite(Gelb, Muster8_GelbLED[17]);
 delay(40);

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("4er & 1er Blitz");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");
 }

else  if((WertMuster  == 9) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 

{ void Muster9();

byte Muster9_BlauLEDre[] = {B,B,0,B,0,B,0,0,0,0,0,0};
byte Muster9_BlauLEDli[] = {0,0,0,0,0,0,B,B,0,B,0,B};
byte Muster9_RotLEDre[]=   {0,0,0,R,R,0,R,0,R,0,0,0};
byte Muster9_RotLEDli[]=   {R,0,R,0,0,0,0,0,0,R,R,0};
byte Muster9_GelbLED[] =   {G,G,G,G,0,G,G,G,0,G,G,0};

 
 
    analogWrite(BlauL, Muster9_BlauLEDli[0]);   
 analogWrite(BlauR, Muster9_BlauLEDre[0]);  
 analogWrite(RotL, Muster9_RotLEDli[0]);
 analogWrite(RotR, Muster9_RotLEDre[0]);
 analogWrite(Gelb, Muster9_GelbLED[0]);
 delay(40);              

 analogWrite(BlauL, Muster9_BlauLEDli[1]);   
 analogWrite(BlauR, Muster9_BlauLEDre[1]);  
 analogWrite(RotL, Muster9_RotLEDli[1]);
 analogWrite(RotR, Muster9_RotLEDre[1]);
 analogWrite(Gelb, Muster9_GelbLED[1]);
 delay(40);

 analogWrite(BlauL, Muster9_BlauLEDli[2]);   
 analogWrite(BlauR, Muster9_BlauLEDre[2]);  
 analogWrite(RotL, Muster9_RotLEDli[2]);
 analogWrite(RotR, Muster9_RotLEDre[2]);
 analogWrite(Gelb, Muster9_GelbLED[2]);
 delay(40);
 
analogWrite(BlauL,  Muster9_BlauLEDli[3]);   
 analogWrite(BlauR, Muster9_BlauLEDre[3]);  
 analogWrite(RotL, Muster9_RotLEDli[3]);
 analogWrite(RotR, Muster9_RotLEDre[3]);
 analogWrite(Gelb, Muster9_GelbLED[3]);
 delay(40);
 
 analogWrite(BlauL, Muster9_BlauLEDli[4]);   
 analogWrite(BlauR, Muster9_BlauLEDre[4]);  
 analogWrite(RotL, Muster9_RotLEDli[4]);
 analogWrite(RotR, Muster9_RotLEDre[4]);
 analogWrite(Gelb, Muster9_GelbLED[4]);
 delay(40);
 
 analogWrite(BlauL, Muster9_BlauLEDli[5]);   
 analogWrite(BlauR, Muster9_BlauLEDre[5]);  
 analogWrite(RotL, Muster9_RotLEDli[5]);
 analogWrite(RotR, Muster9_RotLEDre[5]);
 analogWrite(Gelb, Muster9_GelbLED[5]);
 delay(40);

 analogWrite(BlauL, Muster9_BlauLEDli[6]);   
 analogWrite(BlauR, Muster9_BlauLEDre[6]);  
 analogWrite(RotL, Muster9_RotLEDli[6]);
 analogWrite(RotR, Muster9_RotLEDre[6]);
 analogWrite(Gelb, Muster9_GelbLED[6]);
 delay(40);

 analogWrite(BlauL, Muster9_BlauLEDli[7]);   
 analogWrite(BlauR, Muster9_BlauLEDre[7]);  
 analogWrite(RotL, Muster9_RotLEDli[7]);
 analogWrite(RotR, Muster9_RotLEDre[7]);
 analogWrite(Gelb, Muster9_GelbLED[7]);
 delay(40);

 analogWrite(BlauL, Muster9_BlauLEDli[8]);   
 analogWrite(BlauR, Muster9_BlauLEDre[8]);  
 analogWrite(RotL, Muster9_RotLEDli[8]);
 analogWrite(RotR, Muster9_RotLEDre[8]);
 analogWrite(Gelb, Muster9_GelbLED[8]);
 delay(40);

  analogWrite(BlauL, Muster9_BlauLEDli[9]);   
 analogWrite(BlauR, Muster9_BlauLEDre[9]);  
 analogWrite(RotL, Muster9_RotLEDli[9]);
 analogWrite(RotR, Muster9_RotLEDre[9]);
 analogWrite(Gelb, Muster9_GelbLED[9]);
 delay(40);


  analogWrite(BlauL, Muster9_BlauLEDli[10]);   
 analogWrite(BlauR, Muster9_BlauLEDre[10]);  
 analogWrite(RotL, Muster9_RotLEDli[10]);
 analogWrite(RotR, Muster9_RotLEDre[10]);
 analogWrite(Gelb, Muster9_GelbLED[10]);
 delay(40);



  analogWrite(BlauL, Muster9_BlauLEDli[11]);   
 analogWrite(BlauR, Muster9_BlauLEDre[11]);  
 analogWrite(RotL, Muster9_RotLEDli[11]);
 analogWrite(RotR, Muster9_RotLEDre[11]);
 analogWrite(Gelb, Muster9_GelbLED[11]);
 delay(2);

 lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("Polizei Deutsch 1");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");

}
}
else  if ((WertMuster  == 10) & (ProzentBlau >= 3)| (ProzentRot >=3) | (ProzentGelb >=3)) { 
 
 {void Muster10();

 for(int x=0; x < 2; x++){  //Nested for structure. It makes the whole light flashing loop cycle 3 times.
  for(int x=0; x < 4; x++){  //First LED's flash 3x
   analogWrite(BlauL, B);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, R);
  analogWrite(RotL, LOW);
   delay(40);
 }
 
  //Makes the other LED's flash 3x
  for(int x=0; x < 4; x++){
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, B);
  analogWrite(RotR, LOW);
  analogWrite(RotL, R);
 
  delay(40);
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
  // delay(40);
  }
  }
  //Beginning the alternating flashes
  for(int x=0; x < 8; x++){
   analogWrite(BlauL, B);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, R);
  analogWrite(RotL, LOW);
    delay(40);
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
 
   analogWrite(BlauL, LOW);
  analogWrite(BlauR, B);
  analogWrite(RotR, LOW);
  analogWrite(RotL, R);
 
  delay(40);
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
 
 
 // delay(40);
  }
 
  for(int x=0; x < 5; x++){
   
  for(int x=0; x < 2; x++){
   analogWrite(BlauL, B);
  analogWrite(BlauR, B);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
  
  delay(40);
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
 
  // delay(40);
}
  for(int x=0; x < 2; x++){
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, R);
  analogWrite(RotL, R);
 
  delay(40);//Changed from 50ms because it was too fast, and hard to see.
  analogWrite(BlauL, LOW);
  analogWrite(BlauR, LOW);
  analogWrite(RotR, LOW);
  analogWrite(RotL, LOW);
   //delay(40);//Changed from 50ms as well.

lcd.setCursor(11,0);   
lcd.print("   ");  
lcd.setCursor(0,1); 
lcd.print("           ");     
lcd.setCursor(0,2);  
lcd.print("           ");
 lcd.setCursor(0,0);                  //Spalte, Zeile
lcd.print("Muster");
lcd.setCursor(6,0);     
lcd.print("     ");
lcd.setCursor(7,0);                   //Spalte, Zeile
lcd.print(WertMuster);
lcd.setCursor(0,3);
lcd.print("                    ");
lcd.setCursor(0,3);// lcd.setCursor um Zeichen und Zeile anzugeben
lcd.print("Polizei USA");
lcd.setCursor(11,0);   
lcd.print("   ");         //Spalte, Zeile
lcd.setCursor(11,0);   
lcd.print(ProzentBlau);
lcd.setCursor(11,1); 
lcd.print("   ");  
lcd.setCursor(11,1); //Spalte, Zeile
lcd.print(ProzentRot);
lcd.setCursor(11,2);  
lcd.print("   ");
lcd.setCursor(11,2);   //Spalte, Zeile
lcd.print(ProzentGelb);
lcd.setCursor(14,0);                  //Spalte, Zeile
lcd.print("% Blau");
lcd.setCursor(14,1);                  //Spalte, Zeile
lcd.print("% Rot");
lcd.setCursor(14,2);                  //Spalte, Zeile
lcd.print("% Gelb");

 }
  }   }}
  else {

    void low();
   analogWrite(BlauL, LOW);
    analogWrite(BlauR, LOW);
    analogWrite(RotL, LOW);
    analogWrite(RotR, LOW);
    analogWrite(Gelb, LOW);
   
    lcd.setCursor(0, 0);                 //Spalte, Zeile
    lcd.print("                    ");
    lcd.setCursor(0, 0);                 //Spalte, Zeile
    lcd.print("SIGNALLICHTMUSTER");

           lcd.setCursor(0, 1);                 //Spalte, Zeile
    lcd.print("                    ");
                      lcd.setCursor(0, 2);                 //Spalte, Zeile
    lcd.print("                    ");
     lcd.setCursor(0, 1);                 //Spalte, Zeile
    lcd.print("Vers.");
     lcd.setCursor(6, 1);                 //Spalte, Zeile
    lcd.print(VerA);

 lcd.setCursor(8, 1);                 //Spalte, Zeile
    lcd.print(".");

lcd.setCursor(9, 1);                 //Spalte, Zeile
    lcd.print(VerB);

    
 lcd.setCursor(0, 2);                 //Spalte, Zeile
    lcd.print("(c)paradelix ");
   lcd.setCursor(0, 3);  
lcd.print("                    ");
  lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
  lcd.print(" >>> LED's AUS <<<");
  lcd.setCursor(11, 0);

       delay(50);
    
   
}}

