#include <LiquidCrystal_I2C.h>// Vorher hinzugefügte LiquidCrystal_I2C Bibliothek hochladen
LiquidCrystal_I2C lcd(0x27, 20, 4);   //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall einer mit 16 Zeichen in 2 Zeilen.

byte VerA = 1;      // Programmversion
byte VerB = 34;      //  Unterversion




byte trigger = 11;
byte echo = 10;
long dauer = 0;
long dauer1 = 0;
long dauer2 = 0;
long dauer3 = 0;
long entfernung = 0;


//Variablen für Zisterne, angaben in Zentimeter!!


byte radius = 40;                  // in cm, Radius vom Schachtring
int MaxWasserstand = 350;           // in cm, entspricht dem Abstand Zisternenboden zu Max. Wasserstand   350 cm,oder 3,5m
int Toleranzhohe = - 40;        // !!!!!!!!! in cm, enspricht der Abstand zw.Messonde und Max. Wasserstand
float PII = 3.1415;
float Grundflache = PII * (radius * radius);              // Angabe in Liter
float Volumen = PII * (radius * radius ) * MaxWasserstand / 1000; //Angabe in Liter, Gesamtes Wasserfüll Volumen der Zisterne



void setup()
{
  Serial.begin (9600);
  lcd.begin();
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  lcd.setCursor(0, 0);                 //Spalte, Zeile
  lcd.print("  >>>Wasserstand<<<");

  lcd.setCursor(3, 1);                 //Spalte, Zeile
  lcd.print("Vers.");
  lcd.setCursor(9, 1);                 //Spalte, Zeile
  lcd.print(VerA);
  lcd.setCursor(11, 1);                 //Spalte, Zeile
  lcd.print(".");
  lcd.setCursor(12, 1);                 //Spalte, Zeile
  lcd.print(VerB);
  lcd.setCursor(14, 1);


  lcd.setCursor(0, 2);                 //Spalte, Zeile
  lcd.print("Pascal(|)Schmidgen");
  lcd.setCursor(0, 3);
  delay(3000);
  lcd.print("Messung beginnt....");

  delay(1000);
  lcd.clear();


}
void loop()
{


  //float Toleranzvolumen = Toleranzhohe * Grundflache  ;
  long  RestWasserVolumen = Volumen - (entfernung + Toleranzhohe) * Grundflache / 1000 ;
  long Prozentvalue = (RestWasserVolumen / Volumen) * 100;


  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);

  digitalWrite(trigger, LOW);
  dauer1 = pulseIn(echo, HIGH);

  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);

  digitalWrite(trigger, LOW);
  dauer2 = pulseIn(echo, HIGH);

  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);

  digitalWrite(trigger, LOW);
  dauer3 = pulseIn(echo, HIGH);

  dauer = (dauer1 + dauer2 + dauer3) / 3;
  entfernung = (dauer / 2) * 0.03432;


  if (entfernung >= 500 || entfernung <= 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("                   ");
    lcd.setCursor(0, 1);
    lcd.print("                   ");
    lcd.setCursor(0, 2);
    lcd.print("                   ");
    lcd.setCursor(0, 3);
    lcd.print("                   ");
    lcd.setCursor(13, 3);
    lcd.print("       ");
    lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
    lcd.print("Kein Messwert");
  }
  else
  {


    lcd.setCursor(0, 0);                 //Spalte, Zeile
    lcd.print(Volumen, 0);
    lcd.setCursor(5, 0);                 //Spalte, Zeile
    lcd.print("L Fassungsmenge");
    lcd.setCursor(0, 1);                 //Spalte, Zeile
    lcd.print("      ");
    lcd.setCursor(0, 1);                 //Spalte, Zeile
    lcd.print(RestWasserVolumen);
    lcd.setCursor(5, 1);
    lcd.print("L Vorhanden");
    lcd.setCursor(0, 3);
    lcd.print("                  ");
    lcd.setCursor(0, 3);
    lcd.print("Fuellstand");


    lcd.setCursor(11, 3);
    lcd.print(Prozentvalue);
    lcd.setCursor(14, 3);
    lcd.print("%");




    ;

    Serial.println(dauer);
    Serial.println(dauer1);
    Serial.println(dauer2);
    Serial.println(dauer3);
    Serial.println("***********************");


  }
  delay(1000);
}
