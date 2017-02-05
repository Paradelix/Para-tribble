#include <IRremote.h>

const byte Blau = 6;     // Blaue LED an Pin 6
const byte Rot = 9;      // Rote LED an Pin 9
const byte Gelb = 11;    // Gelbe LED an Pin 11
const byte IRpin = 3; // Pin fr den IR Empfaenger

IRrecv irrecv(IRpin);
decode_results results;

const byte R = 255;
const byte  B = 3;
const byte  G = 255;

byte LED_OFF = 0;


const byte Muster1_BlauLED[14]   =  {B, B, B, B, B, 0, 0, 0, B, 0, 0, 0, 0, 0};
const byte Muster1_RotLED[14]    =  {0, 0, 0, 0, R, R, R, R, R, 0, 0, 0, R, 0};
const byte Muster1_GelbLED[14]   =  {G, G, G, G, G, 0, 0, 0, G, 0, 0, 0, 0, 0};
const byte laenge_Muster1 = sizeof(Muster1_BlauLED) / sizeof(Muster1_BlauLED[0]);

const byte Muster2_BlauLED[16]   =  {B, 0, B, 0, B, B, B, B, B, B, B, B, B, B, 0, 0};
const byte Muster2_RotLED[16]    =  {R, R, R, R, R, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0};
const byte Muster2_GelbLED[16]   =  {G, 0, G, 0, G, 0, G, G, G, G, G, 0, 0, 0, 0, 0};
const byte laenge_Muster2 = sizeof(Muster2_BlauLED) / sizeof(Muster2_BlauLED[0]);

const uint32_t intervall = 40;
uint32_t aktMillis;
byte muster = 1;
bool blauEIN = true, rotEIN = true, gelbEIN = true;

void setup()
{
  Serial.begin(9600);
  pinMode(Blau, OUTPUT);    // Setzt Pin für Linke Blaue LED als Ausgang
  pinMode(Rot, OUTPUT);    // Setzt Pin für Linke Rote LED als Ausgang
  pinMode(Gelb, OUTPUT);     // Setzt Pin für Gelbe  LED als Ausgang

  analogWrite(Blau, LED_OFF);       // erstmal alle LED aus
  analogWrite(Rot, LED_OFF);
  analogWrite(Gelb, LED_OFF);

  irrecv.enableIRIn();           // IR Empfaenger starten
  Serial.println("Anfang");
  Serial.println();
}

void loop()
{
  aktMillis = millis();

  if (irrecv.decode(&results))
  {
    uint32_t taste = results.value;
    switch (taste)
    {                                                        // Codes der Fernbedienung Carmp3
      case 2152211969:    // Taste 1
        muster = 1;
        break;
        
      case 2152244738:    // Taste 2
        muster = 2;
        break;
        
      case 2152212080:    // Taste Blau
        blauEIN = !blauEIN;
        break;
        
      case 2152244845:    // Taste Rot
        rotEIN = !rotEIN;
        break;

        
      case 2152244847:    // Taste Gelb
        gelbEIN = !gelbEIN;
        break;

        
    }
    Serial.print(taste, DEC);
    Serial.print("\t");
    Serial.println(muster);
    irrecv.resume();
  }
  ausgabe(muster, blauEIN, rotEIN, gelbEIN);
}

void ausgabe(byte ledmuster, bool blau, bool rot, bool gelb)
{
  static uint32_t ausgabeMillis = 0;
  static byte j = 255;
  if (aktMillis - ausgabeMillis >= intervall)
  {
    ausgabeMillis = aktMillis;
    j++;
    if (ledmuster == 1)
    {
      j = j % laenge_Muster1;
      blau ? analogWrite(Blau, Muster1_BlauLED[j]) : analogWrite(Blau, 0);
      rot ? analogWrite(Rot, Muster1_RotLED[j]) : analogWrite(Rot, 0);
      gelb ? analogWrite(Gelb, Muster1_GelbLED[j]) : analogWrite(Gelb, 0);
    }
    if (ledmuster == 2)
    {
      j = j % laenge_Muster2;
      blau ? analogWrite(Blau, Muster2_BlauLED[j]) : analogWrite(Blau, 0);
      rot ? analogWrite(Rot, Muster2_RotLED[j]) : analogWrite(Rot, 0);
      gelb ? analogWrite(Gelb, Muster2_GelbLED[j]) : analogWrite(Gelb, 0);
    }
  }
}
