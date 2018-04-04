#include <LiquidCrystal_I2C.h>// Vorher hinzugefÃ¼gte LiquidCrystal_I2C Bibliothek hochladen
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 7 /* Digitalport Pin 7 definieren Temperatursensor*/

const char* sketchname            =  "SensorControl";
const char* revision              =  "2.9";
const char* creator               =  "Pascal Schmidgen";
const char* date                  =  "04/18";

byte drehrichtung_taster_status = 0;      // In dieser Variablen speichern wir den Status des Eingangs.
byte drehrichtung_taster     = 6;     // An den Pin D6 ist der Taster angeschlossen.
byte drehrichtung_led       = 13;      // Signal für Drehzahlerkennnung. KEINE LED am Pin D9 angeschlossen.
byte tacho_signal_pin       = 5;
byte led_status       = LOW;             // led_status used to set the LED

float T;          //Periodendauer in us
float f;                 //Frequenz in MHz
unsigned int rpm;      // Drehzahl pro Minute



LiquidCrystal_I2C lcd(0x27, 20, 4);   //Hier wird festgelegt um was fÃ¼r einen Display es sich handelt. In diesem Fall einer mit 16 Zeichen in 2 Zeilen.
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  pinMode(drehrichtung_taster, INPUT); // Der Pin des Tasters wird als Eingang initialisiert.
  pinMode(drehrichtung_led, OUTPUT);  // Der Pin der LED wird als Ausgang initialisiert.
  pinMode(tacho_signal_pin, INPUT);

  lcd.begin();
  sensors.begin();
  Serial.begin(38400);               // Serielle Ausgabe

  lcd.setCursor(5, 0);
  lcd.print(sketchname);
  lcd.setCursor(0, 1);
  lcd.print(revision);
  lcd.setCursor(0, 2);
  lcd.print(creator);
  lcd.setCursor(0, 3);
  lcd.print(date);
  delay(2000);
  lcd.clear();

  //*************************************************** Ausgabe der 2. Zeile im Display**********
  lcd.setCursor(9, 0);
  lcd.print("|");
  lcd.setCursor(0, 1);
  lcd.print("Spindel  | Steuerung");
}


//******************************** Ermiteln und Ausgabe der Drehzahl **********************
void drehzahl () {
  long int time = micros();
  double k;
  long int fsum;
  do {
    T = pulseIn(tacho_signal_pin, HIGH) + pulseIn(tacho_signal_pin, LOW);
    if (T == 0) {
      Serial.println("Timeout.");
      lcd.setCursor(0, 0);
      lcd.print("    0");
    }
    else {
      f = 1 / (double)T;    // f=1/T
      k++;
    }
    fsum += f * 1e6;
  } while ( micros() < (time + 1e6)); // 1 Sekunde mitteln
  f = fsum / k * 0.9925;     // Korrekturwert einrechnen
  rpm = f * 30;


  lcd.setCursor(0, 0);
  lcd.print("     ");
  lcd.setCursor(0, 0);
  lcd.print(rpm);
  lcd.setCursor(5, 0);
  lcd.print(" rpm");
  fsum = 0.0;
  time = 0.0;
}
//***************************************************** Erkennung der Drehrichtung*************
void drehrichtung() {
  drehrichtung_taster_status = digitalRead(drehrichtung_taster);

  if (drehrichtung_taster_status == HIGH) {     // Ist der Taster gedrückt,
    digitalWrite(drehrichtung_led, HIGH);    // dann schalte die LED an.

    lcd.setCursor(0, 3);
    lcd.print("<<- GEGENLAUF! links");

  }
  else {                             // Ansonsten
    digitalWrite(drehrichtung_led, LOW);     // schalte die LED wieder aus.
    lcd.setCursor(0, 3);
    lcd.print("->>GLEICHLAUF rechts");
  }
  digitalWrite(drehrichtung_led, led_status);
}

// ************************************************* Ermitteln und Ausgabe der Temperatur***********
void temperatur() {
  sensors.requestTemperatures();

  lcd.setCursor(13, 0);
  lcd.print(sensors.getTempCByIndex(0));
  lcd.setCursor(17, 0);
  lcd.print(" \337C");

}

// ********************************************* Serielle Ausgabe
void seriellausgabe() {
  Serial.println("    ");
  Serial.println("    ");
  Serial.println("    ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" ° C Controler    ");
  Serial.print(f);
  Serial.println(" Hertz BLCD Controler   ");
  Serial.print(rpm);
  Serial.println(" U/ Min Spindelmotor    ");
}

void loop() {
  drehzahl();
  drehrichtung();
  temperatur();
  seriellausgabe();
}
