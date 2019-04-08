#include "energy.h"

#define SERIAL_VEL 115200 //velocidade da serial

void setup() 
{
  Serial.begin(SERIAL_VEL);
  delay(3000); // wait for console opening
  
  inicializarDisplay();
  InicializarSDCard();
  inicializarWifi();
  inicializarNTP();
  inicializarRTC();
  inicializarFirebase();
}

void loop() 
{
  updateNTP();
  atualizaRTC();
  exibeRTC();
  exibeNTP();
  Ldr();
  delay(2000);
}
