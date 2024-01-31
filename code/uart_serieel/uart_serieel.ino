/*
 * Middels deze code kan je een ATtiny44 of ATtiny84 gebruiken om uitbreidingsmodules aan te sturen.
 * poort ^ = tx
 * poort v = rx
 * Dit heb ik uitgedacht om een ESP32-2432S028R aka CYD (Cheap Yellow Display) te kunnen gebruiken als boordcomputer
 *
 * Als de code op de ATtiny44 of ATtiny84 vervangt deze de eerste 74HC14 chip zoals aangegeven andersom geplaatst.
 *
 * Getest op:
 * schakelmodule 2.0
 */

#include <SoftwareSerial.h>
//#include <string.h>

// Communicatie met de computer
#define srx  5
#define stx  2

// Communicatie met het systeem
#define hc_pck  9
#define hc_sck  8
#define hc_in   3
#define hc_uit  4
//#define hc_id   1

SoftwareSerial s_Serial(srx, stx);

void setup() {
  // put your setup code here, to run once:
  pinMode(hc_pck, OUTPUT);
  pinMode(hc_sck, OUTPUT);
  pinMode(hc_uit, OUTPUT);
  pinMode(hc_in, INPUT);
//  pinMode(hc_id, INPUT);
  
  s_Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (s_Serial.available()) {
    digitalWrite(hc_pck, LOW);
    delay(10);
    digitalWrite(hc_pck, HIGH);
    unsigned long timout = millis() + 50;
    while ((s_Serial.available()) || (millis() < timout)) {
      if (s_Serial.available()) {
        char c = s_Serial.read();
        if ((c == '/r') || (c == '/n')) {
          digitalWrite(hc_pck, LOW);
          delay(10);
          digitalWrite(hc_pck, HIGH);
          s_Serial.print(c);
        } else if ((c == '1') || (c == '0')) {
          digitalWrite(hc_sck, LOW);
          if (c == '1') {
            digitalWrite(hc_uit, HIGH);
          } else {
            digitalWrite(hc_uit, LOW);
          }
          if (digitalRead(hc_in)) {
            s_Serial.print('1');
          } else {
            s_Serial.print('0');
          }
          digitalWrite(hc_sck, HIGH);
        timout = millis() + 50;
        }
      }
    }
    digitalWrite(hc_pck, LOW);
    delay(10);
    digitalWrite(hc_pck, HIGH);
  }
}
