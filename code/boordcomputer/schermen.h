#include "keuzescherm.h"
#include "schakelscherm.h"
#include "instellingen.h"
#include "sensorscherm.h"

byte actief_scherm = 0;
byte opstart_scherm = 0;

void (*run_scherm[])() = {run_keuzescherm,
                          run_schakelscherm, run_sensorscherm,
                    run_keuzescherm, run_keuzescherm, run_keuzescherm,
                    run_keuzescherm, run_keuzescherm, run_keuzescherm,

                    run_io_instellingen, run_instellingen_io_poort
};
void (*bouw_scherm[])() = {bouw_keuzescherm,
                           bouw_schakelscherm, bouw_sensorscherm,
                  bouw_keuzescherm, bouw_keuzescherm, bouw_keuzescherm,
                  bouw_keuzescherm, bouw_keuzescherm, bouw_keuzescherm,

                  bouw_io_instellingen, bouw_instellingen_io_poort
};
