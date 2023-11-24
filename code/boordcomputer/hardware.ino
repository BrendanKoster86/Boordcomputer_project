void start_hardware() {
  // laten weten wat de 74HC pinnen moeten zijn
  pinMode(hc_pck, OUTPUT);  // paralelle klok (latch)
  pinMode(hc_sck, OUTPUT);  // seriele klok (clock)
  pinMode(hc_in , INPUT);   // data in
  pinMode(hc_uit, OUTPUT);  // data uit
  pinMode(hc_ce , OUTPUT);  // chip enable

  // sd kaart voorlopig uit zetten
  pinMode(cs_tft, OUTPUT);
  pinMode(cs_ts, OUTPUT);
  pinMode(cs_sd, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(cs_tft, HIGH);
  digitalWrite(cs_ts, HIGH);
  digitalWrite(cs_sd, HIGH);
  Serial.print("PWM : ");
  Serial.println(round(255*(scherm_helderheid/100)));
  digitalWrite(led, HIGH);
  // if (scherm_helderheid < 100) {
  //   analogWrite(led, round(255*(scherm_helderheid/100)));
  // }
  // analogWrite(led, 127);
  
  spi_starten();



}

void spi_starten() {
  Serial.println("SPI instellingen doen");
  // spi starten
  SPI.setRX(miso);
  SPI.setTX(mosi);
  SPI.setSCK(sck);
}