#define rotation 0

bool scherm_actief = true;
int scherm_helderheid = 100;
int scherm_timer = 20;
long scherm_touched = 0;


int xfactor = -15;
int xcorrectie = 3855;
int yfactor = -11;
int ycorrectie = 3962;

bool waas = false;

Adafruit_ILI9341 tft = Adafruit_ILI9341(cs_tft, dc, mosi, sck, rst, miso);
XPT2046_Touchscreen ts(cs_ts, irq);

void start_scherm();
void beeld_melding(String hoofdmelding);
void beeld_melding(String hoofdmelding , String submelding);
void beeld_melding(String hoofdmelding , String submelding, String titel);
void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10]);
void beeld_melding(String hoofdmelding, String submelding, String titel, String sec_icon[10], bool sec_icon_bool);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4);
byte beeld_vraag(String hoofdmelding, String submelding, String optie1, String optie2, String optie3, String optie4, String optie5);
byte beeld_vraag(String hoofdmelding, String submelding, byte opties_cnt, String optie1, String optie2, String optie3, String optie4, String optie5);
void gewaasd_scherm();
void center_tekst(int16_t x, int16_t y, String tekst, int tekst_grootte, uint16_t tekst_kleur);
void run_scherm_pauze();

int touch_x();
int touch_y();

