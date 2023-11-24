void start_hardware();
void spi_starten();


// SPI pinnen definieren
#define cs_ts  13
#define cs_tft 17
#define cs_sd  12
#define mosi   19
#define miso   16
#define rst    14
#define sck    18
#define dc     15
#define irq    11
#define led    10


#define tf_minX 0
#define tf_maxX 240
#define tf_minY 0
#define tf_maxY 320




// Pinnen 74HC schips benoemen
#define hc_pck 2  // paralelle klok (latch)
#define hc_sck 1  // seriele klok (clock)
#define hc_in  0  // data in
#define hc_uit 3  // data uit
#define hc_ce  4  // chip enable


// Software serial voor de wifi benoemen
SoftwareSerial wifi(20,21);