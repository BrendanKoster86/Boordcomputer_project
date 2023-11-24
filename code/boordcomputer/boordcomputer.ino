#include "boordcomputer.h"

void setup() {
  Serial.begin(serialCommunicationSpeed);
  start_hardware();
  // start_schakelscherm();
  start_scherm();
  start_sd();
  start_io();
  start_io_instellingen();
  io();
  

  scherm_bouwen = true;
  wifi.begin(serialCommunicationSpeed);
  delay(100);
  wifi_beschikbare_netwerken_vernieuwen();
  statusupdate_set_timer();
  Serial.println("Tijd tot volgend statusupdate: " + tijd_tot_millis(timer_statusupdate));
  scherm_touched = millis();

  if ((wifi__verbonden) & (wifi_connectie_modus != 1)) {
    wifi_verbinding_verbreken();
  } else {
    Serial.print("WiFi connectie modus: ");
    Serial.println(wifi_connectie_modus);
  }
  io();
  io();
  io_reset_alert();
  io_reset_gewijzigd();
}

void loop() {
  // Str  ing invoer;
  io();
  io_alert_check();
  header_alert();
  ts.begin();
  if ((scherm_actief) || (scherm_bouwen)) {
    if ((millis() > scherm_touched + scherm_timer*1000) || (millis() < scherm_touched)) {
      scherm_actief = false;
      digitalWrite(led, LOW);
      bouw_scherm[actief_scherm]();
      waas = false;
      scherm_bouwen = false;
    } else {
      if (scherm_bouwen) {
        bouw_scherm[actief_scherm]();
        ts.begin();
        waas = false;
        scherm_bouwen = false;
        scherm_touched = millis();
      } else {
        io();
        io_check_zekeringen();
        io();
        run_scherm[actief_scherm]();
      }
    }
  } else {
    run_scherm_pauze();
  }

  // Af en toe een diepe check doen waarbij een aantal als check gemaakt schakelingen worden omgezet zodat gezien kan worden of alles functioneerd
  if ((millis() > laatste_diepcheck + diepcheck_timer*60000) || (millis() < laatste_diepcheck)) {
    laatste_diepcheck = millis();
    io_diep_checken();
  }

  // Als er een alert te melden is deze verzenden. Indien het mislukt met enige vertraging opnieuw versturen
  if (io_alert_app > 0) {
    Serial.print("alert! ");

    Serial.print(io_alert_cnt);
    Serial.print(" - ");
    Serial.println(io_alert_app);
    if ((millis() > laatste_alert_app + alert_app_timer*60000) || (millis() < laatste_alert_app) || (laatste_alert_app == 0)) {
      if ((wifi_connectie_modus != 0) & (wifi__aangesloten)) {
        io_alert_appen();
      } else {
        laatste_alert_app = millis();
        beeld_melding("WiFi uitgeschakeld", "Bericht wordt daarom niet veronden", "alert versturen!");
      }
    }
  }

  // Af en toe een statusupdate geven per app zodat bekend is dat er een verbinding is
  if (((millis() > laatste_app + levens_timer*60000) || (millis() < laatste_app) || (millis() > timer_statusupdate)) & (wifi_connectie_modus != 0)) {
    statusupdate();
    statusupdate_set_timer();
    Serial.println("Tijd tot volgend statusupdate: " + tijd_tot_millis(timer_statusupdate));
  }

  if (scherm_actief) {
    if ((millis() > h_klok_millis + 20000) || (millis() < h_klok_millis)) {
      klok_update();
    }
  }

  if (Serial.available()) {
    if (SMODES == 0) {
      while (Serial.available()) {
        wifi.write(Serial.read());
      }
    }
  }
  
  if (wifi.available()) {
    while (wifi.available()) {
      Serial.write(wifi.read());
    }
  }
  
}