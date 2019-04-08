#include "energy.h"

#define OLED_RESET LED_BUILTIN 
Adafruit_SSD1306 display(OLED_RESET);

void inicializarDisplay()
{ 
  //Serial - Debug
  Serial.println();
  Serial.print("Inicializando Display");
  
  //inicializa o display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Limpa o buffer do display
  limpaDisplay();
  display.setTextSize(1); //tamanho fonte
  display.setTextColor(WHITE); //cor fonte
  display.setCursor(0,8); //posição
  display.println("Inicializando Display");  //exibe mensagem no display
  display.display();
  delay(2000); //aguarda 2 seg
  limpaDisplay();
  drawrect(); //desenha retangulos na tela para testar display
  delay(3000); //aguarda 3 seg
  limpaDisplay();  

  // Limpa o buffer do display
  limpaDisplay();
}

void limpaDisplay()
{
  display.clearDisplay();
  display.display();
}

void drawrect(void) {
  display.clearDisplay();

  for(int16_t i=0; i<display.height()/2; i+=2) 
  {
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(1);
  }
  delay(2000);
}
