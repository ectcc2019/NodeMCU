#include "energy.h"

float ldr = analogRead(A0);
String n = "LDR";

void Ldr()
{  
  enviaDadosFirebase(n, ldr);
  
  //Serial - Debug
  Serial.println();
  Serial.println(ldr);   

  //Display
  display.setTextSize(3);
  display.setCursor(0,8);
  display.println(ldr);
  delay(5000);
  limpaDisplay();
}
