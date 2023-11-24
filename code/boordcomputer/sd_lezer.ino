void start_sd() {
  
  beeld_melding("SD lezen", "Gegevens lezen op de SD kaart", "SD lezen");
  ts.begin();
  delay(10);
  
  SD.begin(cs_sd);
  
  // SD kaart starten
  Serial.println("SD kaart starten");
  SD.begin(cs_sd);
  if (!SD.begin(cs_sd)) {
    SD_connect = false;
    Serial.println("kan SD kaart niet vinden");
    beeld_melding("niet gevonden", "Lezen SD kaart mislukt", "SD lezen");
    delay(2000);
  } else {
    sd_info();
    sd_io();
    sd_wifi();
    sd_app();
    sd_leven();
    sd_startscherm();
    beeld_melding("gereed", "SD lezen gereed", "SD lezen");
  }
  SD.end();

}

void sd_info() {
  // Info gegevens beschikbaar maken
  myFile = SD.open("info/snaam.txt");
  info_snaam = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
  
  myFile = SD.open("info/eigenaar.txt");
  info_eigenaar = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
  
  myFile = SD.open("info/telefoon.txt");
  info_telefoon = SD_string(myFile.readStringUntil('\n'));
  myFile.close();
   
}

void sd_io() {
  // Inladen IO objecten (ingewikkeld)
  myFile = SD.open("io/objecten.txt");
  buffer = myFile.readStringUntil('\n');
  io_cnt = buffer.toInt();
  io_sd_cnt = buffer.toInt();

  Serial.print("io_cnt: ");
  Serial.println(io_cnt);

  io_objecten = new byte[io_cnt];
  io_output = new byte[io_cnt];
  io_input = new bool[io_cnt];
  io_gewijzigd = new bool[io_cnt];
  io_open_alert = new bool[io_cnt];
  io_alert = new byte[io_cnt];
  io_namen = new char*[io_cnt];
  for (int i = 0 ; i < io_cnt ; i++) {
    io_namen[i] = new char[11];
  }
  
  io_sd = new String[io_cnt];

  int object = -6;
  io_knoppen_cnt = 0;
  io_sensoren_cnt = 0;

  // Nodige regels (met toelichting in het txt bestand) overslaan om bij de inhoud aan te komen
  for (int i = 0 ; i < 8 ; i++) {
    Serial.print(io_output[i]);
  }
  

  while (myFile.available()) {
    char buff[1];
    if (object >= 0) {
      buffer = myFile.readStringUntil('\n');
      io_objecten[object] = SD_byte(buffer.substring(0,1));
      io_output[object] = SD_byte(buffer.substring(1,2));
      io_input[object] = SD_byte(buffer.substring(2,3));
      io_alert[object] = SD_byte(buffer.substring(3,4));
      
      io_sd[object] = buffer;
      
      buffer.substring(4).toCharArray(io_namen[object], 11);

      // Bepalen of de invoer een knop of sensor is zodat er later een mapping kan worden gemaakt voor alle knoppen en sensoren
      if ((io_objecten[object] == 1) || (io_objecten[object] == 3)) {
        io_knoppen_cnt++;
      } else if (io_objecten[object] == 2) {
        io_sensoren_cnt++;
      } else if (io_objecten[object] == 4) {
        io_diepcheck_pins_cnt++;
      }


      // tft.print("io_namen[object] : ");
      // tft.println(io_namen[object]);
      // Serial.print("io_namen[object] : ");
      Serial.print(object);
      Serial.print(" - ");
      Serial.print(io_namen[object]);
      Serial.print(" : ");
      Serial.println(io_output[object]);
      if (object > 0) {
        Serial.println(io_output[object-1]);
        if (object > 1) {
          Serial.println(io_output[object-2]);
        }
      }

    } else {
      // randinformatie ophalen om het later makkelijker te maken om het bestand te herschrijven.
      io_handleiding[object + 6] = myFile.readStringUntil('\n');
    }

    object++;

  }
  myFile.close();
}

void sd_wifi() {
  // Inladen wifi gegevens (semi ingewikkeld)
  myFile = SD.open("wifi/login.txt");
  
  buffer = myFile.readStringUntil('\n');
  wifi_cnt_sd = buffer.toInt();
  buffer = myFile.readStringUntil('\n');
  wifi_connectie_modus = buffer.toInt();
  wifi_ssid_sd = new String[wifi_cnt_sd];
  wifi_pass_sd = new String[wifi_cnt_sd];

  // regels (4) met toelichting overslaan
  for (int i = 0; i < 4; i++) {
    buffer = myFile.readStringUntil('\n');
  }

  for (int i = 0; i < wifi_cnt_sd; i++) {
    buffer = myFile.readStringUntil('\n');
    wifi_ssid_sd[i] = buffer.substring(0, buffer.length()-1);
    buffer = myFile.readStringUntil('\n');
    wifi_pass_sd[i] = buffer.substring(0, buffer.length()-1);
  }
  myFile.close();
}

void sd_app() {
  // Inladen signal gegevens (semi ingewikkeld)
  myFile = SD.open("wifi/app.txt");
  
  buffer = myFile.readStringUntil('\n');
  app_cnt = buffer.toInt();
  app_app = new String[app_cnt];
  app_tel = new String[app_cnt];
  app_key = new String[app_cnt];
  

  // regels (2) met toelichting overslaan
  for (int i = 0; i < 2; i++) {
    buffer = myFile.readStringUntil('\n');
  }
  for (int i = 0; i < app_cnt; i++) {
    app_app[i] = SD_string(myFile.readStringUntil('\n'));
    app_tel[i] = SD_string(myFile.readStringUntil('\n'));
    app_key[i] = SD_string(myFile.readStringUntil('\n'));
  }
  myFile.close();
}

void sd_leven() {
  // Inladen van de timers voor een statusupdate (status update)

  Serial.println("LEVEN");

  myFile = SD.open("wifi/leven.txt");

  buffer = myFile.readStringUntil('\n');
  statusupdate_timer_array_cnt = buffer.toInt();
  statusupdate_timer_array = new byte*[statusupdate_timer_array_cnt];
  
  Serial.println(statusupdate_timer_array_cnt);

  // regels (4) met toelichting overslaan
  for (int i = 0; i < 4; i++) {
    buffer = myFile.readStringUntil('\n');
  }

  for (int i = 0; i < statusupdate_timer_array_cnt; i++) {
    Serial.println(i);
    statusupdate_timer_array[i] = new byte[2];
    // buffer = myFile.readStringUntil('\n')
    statusupdate_timer_array[i][0] = SD_byte(myFile.readStringUntil(':'));
    Serial.println(statusupdate_timer_array[i][0]);
    statusupdate_timer_array[i][1] = SD_byte(myFile.readStringUntil('\n'));
    Serial.println(statusupdate_timer_array[i][1]);
  }
  myFile.close();
}

void sd_startscherm() {
  // Inladen van de timers voor een statusupdate (status update)

  myFile = SD.open("io/starten.txt");
  
  opstart_scherm = SD_byte(myFile.readStringUntil('\n'));
  actief_scherm = opstart_scherm;

  myFile.close();
}

byte SD_byte(String invoer) {
  Serial.print("invoer: ");
  Serial.println(invoer);
  
  if (invoer.indexOf('\r') > -1) {
    invoer = invoer.substring(0, invoer.indexOf('\r'));
  }
  if (invoer.indexOf('\n') > -1) {
    invoer = invoer.substring(0, invoer.indexOf('\n'));
  }
  byte uitvoer = invoer.toInt();
  Serial.print("uitvoer: ");
  Serial.println(uitvoer);
  return uitvoer;

  
  // if (invoer == "0") {
  //   return 0;
  // } else if (invoer == "1") {
  //   return 1;
  // } else if (invoer == "2") {
  //   return 2;
  // } else if (invoer == "3") {
  //   return 3;
  // } else if (invoer == "4") {
  //   return 4;
  // } else if (invoer == "5") {
  //   return 5;
  // } else if (invoer == "6") {
  //   return 6;
  // } else if (invoer == "7") {
  //   return 7;SD_byte
  // } else if (invoer == SD_byte
  //   return 8;
  // } else if (invoer == SD_byte
  //   return 9;
  // }
  // Serial.print("ERROR (SD_byte()) !");
  // return 99;
}

String SD_string(String invoer) {
  return invoer.substring(0, invoer.length()-1);
}