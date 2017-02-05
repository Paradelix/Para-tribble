#include <IRremote.h>
#include <IRremoteInt.h>

// Pin 13 has an ledL connected on most Arduino boards.
// give it a name:




// Konstanten
const byte BlauR = 5;  //   GRÜNES KABEL****** Blaue Led RECHTE Seite an Pin 6 angeschlossen
const byte BlauL = 6;    // BLAUES KABEL****** Blaue Led LINKE Seite an Pin 5 angeschlossen
const byte RotR = 10;   // ROTES KABEL ******* Rote Led RECHTE Seite an Pin 10 angeschlossen
const byte RotL = 9;   // ORANGENES KABEL***** Rote Led LINKE Seite an Pin 9 angeschlossen
const byte Gelb = 11;   // GELBES KABEL******* Gelbe Led an Pin 11 angeschlossen
const byte IRpin = 3; // Pin fr den IR Empfaenger

IRrecv irrecv(IRpin);
decode_results results;


// Max. PWM Signal, Abgleich zur Strombegrenzung
const byte R = 180;
const byte B = 255;
const byte G = 195;


byte LED_OFF = 0;

const byte Muster1_BlauLEDre[14]   = {B, B, B, B, B, 0, 0, 0, B, 0, 0, 0, 0, 0};
const byte Muster1_BlauLEDli[14]   = {B, B, B, B, B, 0, 0, 0, B, 0, 0, 0, 0, 0};
const byte Muster1_RotLEDre[14]    = {0, 0, 0, 0, R, R, R, R, R, 0, 0, 0, R, 0};
const byte Muster1_RotLEDli[14]    = {0, 0, 0, 0, R, R, R, R, R, 0, 0, 0, R, 0};
const byte Muster1_GelbLED[14]     = {G, G, G, G, G, 0, 0, 0, G, 0, 0, 0, 0, 0};
const byte laenge_Muster1 = sizeof(Muster1_BlauLEDre) / sizeof(Muster1_BlauLEDre[0]);

const byte Muster2_BlauLEDre[16]     = {B, 0, B, 0, B, 0, B, B, B, B, B, 0, 0, 0, 0, 0};
const byte Muster2_BlauLEDli[16]     = {B, 0, B, 0, B, 0, B, B, B, B, B, 0, 0, 0, 0, 0};
const byte Muster2_RotLEDre[16]      = {R, R, R, R, R, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0};
const byte Muster2_RotLEDli[16]      = {R, R, R, R, R, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0};
const byte Muster2_GelbLED[16]       = {G, 0, G, 0, G, 0, G, G, G, G, G, 0, 0, 0, 0, 0};
const byte laenge_Muster2 = sizeof(Muster2_BlauLEDre) / sizeof(Muster2_BlauLEDre[0]);
/*
const byte Muster3_BlauLEDre[12] = {B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0};
const byte Muster3_BlauLEDli[12] = {B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0};
const byte Muster3_RotLEDre[12]  = {0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0};
const byte Muster3_RotLEDli[12]  = {0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0};
const byte Muster3_GelbLED[12]   = {0, G, 0, G, 0, G, 0, 0, 0, 0, 0, 0};
const byte laenge_Muster3 = sizeof(Muster3_BlauLEDre) / sizeof(Muster3_BlauLEDre[0]);

const byte Muster4_BlauLEDre[14] = {B, 0, B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0};
const byte Muster4_BlauLEDli[14] = {B, 0, B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0};
const byte Muster4_RotLEDre[14]  = {0, 0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0, R};
const byte Muster4_RotLEDli[14]  = {0, 0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0, R};
const byte Muster4_GelbLED[14]   = {0, 0, 0, 0, 0, G, 0, G, 0, G, 0, G, 0, 0};
const byte laenge_Muster4 = sizeof(Muster4_BlauLEDre) / sizeof(Muster4_BlauLEDre[0]);

const byte Muster5_BlauLEDre[8] = {B, 0, B, 0, 0, 0, 0, 0};
const byte Muster5_BlauLEDli[8] = {B, 0, B, 0, 0, 0, 0, 0};
const byte Muster5_RotLEDre[8]  = {0, 0, 0, 0, R, 0, R, 0};
const byte Muster5_RotLEDli[8]  = {0, 0, 0, 0, R, 0, R, 0};
const byte Muster5_GelbLED[8]   = {0, G, 0, G, 0, 0, 0, 0};
const byte laenge_Muster5 = sizeof(Muster5_BlauLEDre) / sizeof(Muster5_BlauLEDre[0]);

const byte Muster6_BlauLEDre[24] = {B, B, B, 0, 0, 0, B, B, B, 0, 0, 0, B, B, B, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte Muster6_BlauLEDli[24] = {B, B, B, 0, 0, 0, B, B, B, 0, 0, 0, 0, 0, 0, 0, 0, 0, B, B, B, 0, 0, 0};
const byte Muster6_RotLEDre[24]  = {0, 0, 0, G, G, G, 0, 0, 0, G, G, G, 0, 0, 0, 0, 0, 0, 0, 0, 0, G, G, R};
const byte Muster6_RotLEDli[24]  = {0, 0, 0, G, G, G, 0, 0, 0, G, G, G, 0, 0, 0, G, G, G, 0, 0, 0, 0, 0, 0};
const byte Muster6_GelbLED[24]   = {0, G, G, G, 0, 0, 0, G, G, G, 0, 0, 0, G, G, G, 0, 0, 0, G, G, G, 0, 0};
const byte laenge_Muster6 = sizeof(Muster6_BlauLEDre) / sizeof(Muster6_BlauLEDre[0]);

const byte Muster7_BlauLEDre[8] = {B, 0, B, 0, 0, 0, 0, 0};
const byte Muster7_BlauLEDli[8] = {0, 0, 0, 0, B, 0, B, 0};
const byte Muster7_RotLEDre[8]  = {0, R, 0, R, 0, 0, 0, 0};
const byte Muster7_RotLEDli[8]  = {0, 0, 0, 0, 0, R, 0, R};
const byte Muster7_GelbLED[8]   = {G, G, 0, G, G, 0, G, 0};
const byte laenge_Muster7 = sizeof(Muster7_BlauLEDre) / sizeof(Muster7_BlauLEDre[0]);

const byte Muster8_BlauLEDre[36] = {0, B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0, 0, 0, B, 0, B, 0, B, 0, B, 0, 0, 0, B, 0, 0, 0, B, 0, 0, 0, B, 0, 0};
const byte Muster8_BlauLEDli[36] = {0, 0, 0, 0, 0, 0, 0, 0, B, 0, B, 0, B, 0, B, 0, 0, 0, 0, 0, 0, 0, 0, 0, B, 0, 0, 0, B, 0, 0, 0, B, 0, 0, 0};
const byte Muster8_RotLEDre[36]  = {0, 0, 0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0, R, 0, 0, 0, 0, 0, 0, 0, 0, 0, R, 0, 0, 0, R, 0, 0, 0, R, 0, 0, 0};
const byte Muster8_RotLEDli[36]  = {R, 0, R, 0, R, 0, R, 0, 0, 0, 0, 0, 0, 0, 0, 0, R, 0, R, 0, R, 0, R, 0, 0, 0, R, 0, 0, 0, R, 0, 0, 0, R, 0};
const byte Muster8_GelbLED[36]   = {G, 0, G, 0, G, 0, G, 0, 0, 0, 0, 0, 0, 0, 0, 0, G, 0, G, 0, G, 0, G, 0, 0, 0, G, 0, 0, 0, G, 0, 0, 0, G, 0};
const byte laenge_Muster8 = sizeof(Muster8_BlauLEDre) / sizeof(Muster8_BlauLEDre[0]);

const byte Muster9_BlauLEDre[12] = {B, B, 0, B, 0, B, 0, 0, 0, 0, 0, 0};
const byte Muster9_BlauLEDli[12] = {0, 0, 0, 0, 0, 0, B, B, 0, B, 0, B};
const byte Muster9_RotLEDre[12]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte Muster9_RotLEDli[12]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte Muster9_GelbLED[12]   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte laenge_Muster9 = sizeof(Muster9_BlauLEDre) / sizeof(Muster9_BlauLEDre[0]);

const byte Muster10_BlauLEDre[24] = {B, B, B, B, B, 0, 0, 0, 0, 0, B, B, B, 0, 0, 0, B, B, 0, 0, B, 0, B, 0};
const byte Muster10_BlauLEDli[24] = {0, 0, 0, 0, 0, B, B, B, B, B, 0, 0, 0, B, B, B, 0, 0, B, B, 0, B, 0, B};
const byte Muster10_RotLEDre[24]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte Muster10_RotLEDli[24]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte Muster10_GelbLED[24]   = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
const byte laenge_Muster10 = sizeof(Muster10_BlauLEDre) / sizeof(Muster10_BlauLEDre[0]);
*/
const uint32_t intervall = 40;        // ************Zeitintervall für den Wechsel aus das nächste BIT im Array
uint32_t aktMillis;
byte muster = 1;
bool blauEIN = true, rotEIN = true, gelbEIN = true;

void setup() {
  Serial.begin(9600);
  pinMode(BlauL, OUTPUT);    // Setzt Pin für Linke Blaue LED als Ausgang
  pinMode(BlauR, OUTPUT);    // Setzt Pin für Rechte Blaue LED als Ausgang
  pinMode(RotL, OUTPUT);    // Setzt Pin für Linke Rote LED als Ausgang
  pinMode(RotR, OUTPUT);     // Setzt Pin für Rechte Rote LED als Ausgang
  pinMode(Gelb, OUTPUT);     // Setzt Pin für Gelbe  LED als Ausgang

  analogWrite(BlauL, LED_OFF);
  analogWrite(BlauR, LED_OFF);  // erstmal alle LED aus
  analogWrite(RotL, LED_OFF);
  analogWrite(RotR, LED_OFF);
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
    { // Codes der SKY Fernbedienung

   //   case 4294967295:      //Taste1
      case  2152211969:    //Taste1
        muster = 1;
        break;

    //  case 4294967295:    // Taste 2
      case 2152211970:    // Taste 2
        muster = 2;
        break;
/*
    //  case 4294967295:   // Taste 3
      case 2152211971:   // Taste 3
        muster = 3;
        break;

      case 2152244740:  //Taste 4
      case 2152211972:  //Taste 4
        muster = 4;
        break;

      case 2152244741: //Taste 5
      case 2152211973: //Taste  5
        muster = 5;
        break;

      case  2152244742: //Taste 6
      case 2152211974: //Taste 6
        muster = 6;
        break;

      case 2152244743:   //Taste 7
      case 2152211975:  //Taste 7
        muster = 7;
        break;

      case 2152244744: //Taste 8
      case 2152211976: //Taste 8
        muster = 8;
        break;

      case 2152244745: //Taste 9
      case 2152211977: //Taste 9
        muster = 9;
        break;

      case 2152244736: //Taste 0
      case 2152211968: //Taste 0
        muster = 10;
        break;

      /*     case 2152212184:  // Taste Zoom
           case 2152244952: // Taste Zoom
             muster = 11zoom;
             break;
      */
      case 2152244845:   //Taste Rot
      case 2152212077:
        muster = rotEIN = !rotEIN;
        break;

      case 2152212079:   // Taste Gelb
      case 2152244847:
        muster = gelbEIN = !gelbEIN;
        break;

      case 2152212080:    // Taste Blau
      case 2152244848:
        muster = blauEIN = !blauEIN;
        break;

    }
    Serial.print(taste, HEX);
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




    if (ledmuster == 1)            // HELA FWL Rettungswagen
    {
      j = j % laenge_Muster1;
      blau ?  analogWrite(BlauL, Muster1_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster1_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster1_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster1_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster1_GelbLED[j]) : analogWrite(Gelb, 0);
    }




    if (ledmuster == 2)            // 3 Fachblitz, danach leuchtend, synchron
    {
      j = j % laenge_Muster2;
      blau ?  analogWrite(BlauL, Muster2_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster2_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster2_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster2_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster2_GelbLED[j]) : analogWrite(Gelb, 0);
    }

/*



    if (ledmuster == 3)             // 3 Fachblitz, synchron
    {
      j = j % laenge_Muster3;
      blau ?  analogWrite(BlauL, Muster3_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster3_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster3_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster3_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster3_GelbLED[j]) : analogWrite(Gelb, 0);
    }

    if (ledmuster == 4)            // 4 Fachblitz, synchron
    {
      j = j % laenge_Muster4;
      blau ?  analogWrite(BlauL, Muster4_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster4_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster4_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster4_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster4_GelbLED[j]) : analogWrite(Gelb, 0);
    }


    if (ledmuster == 5)            // 2 Fachblitz, synchron
    {
      j = j % laenge_Muster5;
      blau ?  analogWrite(BlauL, Muster5_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster5_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster5_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster5_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster5_GelbLED[j]) : analogWrite(Gelb, 0);
    }


    if (ledmuster == 6)         // 2 mal Blinken, synchron / wechsel
    {
      j = j % laenge_Muster6;
      blau ?  analogWrite(BlauL, Muster6_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster6_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster6_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster6_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster6_GelbLED[j]) : analogWrite(Gelb, 0);
    }

    if (ledmuster == 7)         // 2 mal Blinken,  wechsel
    {
      j = j % laenge_Muster7;
      blau ?  analogWrite(BlauL, Muster7_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster7_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster7_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster7_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster7_GelbLED[j]) : analogWrite(Gelb, 0);
    }

    if (ledmuster == 8)       // 4 Fachblitz und 1 Fachblitz, wechsel
    {
      j = j % laenge_Muster8;
      blau ?  analogWrite(BlauL, Muster8_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster8_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster8_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster8_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster8_GelbLED[j]) : analogWrite(Gelb, 0);
    }



    if (ledmuster == 9)       // Poilizei Deutschland Links Rechts wechsel
    {
      j = j % laenge_Muster9;
      blau ?  analogWrite(BlauL, Muster9_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster9_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster9_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster9_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster9_GelbLED[j]) : analogWrite(Gelb, 0);
    }

    if (ledmuster == 10)       // Poilizei Deutschland Links Rechts wechsel
    {
      j = j % laenge_Muster10;
      blau ?  analogWrite(BlauL, Muster10_BlauLEDli[j])  : analogWrite(BlauL, 0);
      blau ?  analogWrite(BlauR, Muster10_BlauLEDre[j]) : analogWrite(BlauR, 0);
      rot ?   analogWrite(RotL, Muster10_RotLEDli[j]) : analogWrite(RotL, 0);
      rot ?   analogWrite(RotR, Muster10_RotLEDre[j]) : analogWrite(RotR, 0);
      gelb ?   analogWrite(Gelb, Muster10_GelbLED[j]) : analogWrite(Gelb, 0);


     
    }
 */

 
  }
}



/*
  if (ledmuster == 11)
  {

   for (int x = 0; x < 2; x++) { //Nested for structure. It makes the whole light flashing loop cycle 3 times.
     for (int x = 0; x < 4; x++) { //First LED's flash 3x
       analogWrite(BlauL, B);
       analogWrite(BlauR, LOW);
       analogWrite(RotR, R);
       analogWrite(RotL, LOW);
       delay(40);
     }

     //Makes the other LED's flash 3x
     for (int x = 0; x < 4; x++) {
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
   for (int x = 0; x < 8; x++) {
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

   for (int x = 0; x < 5; x++) {

     for (int x = 0; x < 2; x++) {
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
     for (int x = 0; x < 2; x++) {
       analogWrite(BlauL, LOW);
       analogWrite(BlauR, LOW);
       analogWrite(RotR, R);
       analogWrite(RotL, R);

       delay(40);//Changed from 50ms because it was too fast, and hard to see.
       analogWrite(BlauL, LOW);
       analogWrite(BlauR, LOW);
       analogWrite(RotR, LOW);
       analogWrite(RotL, LOW);

     }
   }




  }*/
/*
     lcd.clear();
     lcd.setCursor(0, 0);                 //Spalte, Zeile
     lcd.print("Muster");
     lcd.setCursor(7, 0);                   //Spalte, Zeile
     lcd.print(WertMuster);
     lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
     lcd.print("Polizei Deutsch 2");
     lcd.setCursor(11, 0);                 //Spalte, Zeile
     lcd.print(ProzentBlau);
     lcd.setCursor(11, 1);                 //Spalte, Zeile
     lcd.print(ProzentRot);
     lcd.setCursor(11, 2);                 //Spalte, Zeile
     lcd.print(ProzentGelb);
     lcd.setCursor(14, 0);                 //Spalte, Zeile
     lcd.print("% Blau");
     lcd.setCursor(14, 1);                 //Spalte, Zeile
     lcd.print("% Rot");
     lcd.setCursor(14, 2);                 //Spalte, Zeile
     lcd.print("% Gelb");

   }
  }

  if (WertMuster == 12){

  void Muster12();

   lcd.clear();
   lcd.setCursor(0, 0);                 //Spalte, Zeile
   lcd.print("Muster");
   lcd.setCursor(7, 0);                   //Spalte, Zeile
   lcd.print(WertMuster);
   lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
   lcd.print("xxxxxxxxxxxxxxxxxxxx");
   lcd.setCursor(11, 0);                 //Spalte, Zeile
   lcd.print(ProzentBlau);
   lcd.setCursor(11, 1);                 //Spalte, Zeile
   lcd.print(ProzentRot);
   lcd.setCursor(11, 2);                 //Spalte, Zeile
   lcd.print(ProzentGelb);
   lcd.setCursor(14, 0);                 //Spalte, Zeile
   lcd.print("% Blau");
   lcd.setCursor(14, 1);                 //Spalte, Zeile
   lcd.print("% Rot");
   lcd.setCursor(14, 2);                 //Spalte, Zeile
   lcd.print("% Gelb");

  }


  if (WertMuster == 13)

  { void Muster13();

  lcd.clear();
  lcd.setCursor(0, 0);                 //Spalte, Zeile
  lcd.print("Muster");
  lcd.setCursor(7, 0);                   //Spalte, Zeile
  lcd.print(WertMuster);
  lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
  lcd.print("xxxxxxxxxxxxxxxxxxxx");
  lcd.setCursor(11, 0);                 //Spalte, Zeile
  lcd.print(ProzentBlau);
  lcd.setCursor(11, 1);                 //Spalte, Zeile
  lcd.print(ProzentRot);
  lcd.setCursor(11, 2);                 //Spalte, Zeile
  lcd.print(ProzentGelb);
  lcd.setCursor(14, 0);                 //Spalte, Zeile
  lcd.print("% Blau");
  lcd.setCursor(14, 1);                 //Spalte, Zeile
  lcd.print("% Rot");
  lcd.setCursor(14, 2);                 //Spalte, Zeile
  lcd.print("% Gelb");

  }


  if (WertMuster == 14)

  { void Muster14();

  lcd.clear();
  lcd.setCursor(0, 0);                 //Spalte, Zeile
  lcd.print("Muster");
  lcd.setCursor(7, 0);                   //Spalte, Zeile
  lcd.print(WertMuster);
  lcd.setCursor(0, 3); // lcd.setCursor um Zeichen und Zeile anzugeben
  lcd.print("xxxxxxxxxxxxxxxxxxxx");
  lcd.setCursor(11, 0);                 //Spalte, Zeile
  lcd.print(ProzentBlau);
  lcd.setCursor(11, 1);                 //Spalte, Zeile
  lcd.print(ProzentRot);
  lcd.setCursor(11, 2);                 //Spalte, Zeile
  lcd.print(ProzentGelb);
  lcd.setCursor(14, 0);                 //Spalte, Zeile
  lcd.print("% Blau");
  lcd.setCursor(14, 1);                 //Spalte, Zeile
  lcd.print("% Rot");
  lcd.setCursor(14, 2);                 //Spalte, Zeile
  lcd.print("% Gelb");


*/













