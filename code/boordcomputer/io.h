int io_cnt;
int io_knoppen_cnt;
int io_sensoren_cnt;

int io_alert_cnt;
int io_alert_app;
int io_diepcheck_cnt = 0;
int* io_diepcheck_pins;
int io_diepcheck_pins_cnt = 0;
bool io_diepcheck = true;

byte* io_objecten;   // Wat zit er aangesloten op de poorten 0: niks, 1: knop, 2: sensor
byte* io_output;  // Wat is de gewenste output 0: uit, 1: aan, 2: inv uit (hoog), 3: inv aan (laag), 4: geblokeerd (laag), 5: inv geblokeerd (hoog)
bool* io_input;   // Gemete status 0: laag, 1: hoog
bool* io_gewijzigd;   // Gemete status 0: laag, 1: hoog
byte* io_alert;   // Wanneer moet er een alert uit? 0: bij passief worden, 1: bij actief worden, 2: bij alle verandering, 3: nooit
char** io_namen; // Namen van de aangesloten objecten
bool* io_open_alert;

int* io_knoppen;  // Mapping voor de knoppen
int* io_sensoren; // Mapping voor de sensoren

String io_handleiding[6];

void start_io();
void io_reset_gewijzigd();
void io_reset_alert();
void io();
void io_schakel();
void io_check_zekeringen();
void io_alert_check();
void io_diep_checken();
String alert_bouwen();
void io_alert_appen();

long laatste_diepcheck = 0;
int diepcheck_timer = 5;

long laatste_alert_app = 0;
int alert_app_timer = 5;