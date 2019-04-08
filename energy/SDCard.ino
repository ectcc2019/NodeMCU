#include "energy.h"

//criar um objeto File para manipular um arquivo
File datalog;
 
void InicializarSDCard()
{
  //Serial - Debug
  Serial.println();
  Serial.print("Inicializando SD card.");
  
  //Display
  display.setTextSize(1); //tamanho fonte
  display.setCursor(0,8); //posição
  display.println("Inicializando SD Card");  //exibe string no display
  display.display();
  delay(5000);
  limpaDisplay();
}

void gravaSD()
{
  datalog = SD.open("Log.txt", FILE_WRITE);

  //Se o arquivo foi aberto sucesso, escreve nele
  if (datalog) 
  {
    Serial.print("Gravando...");
    
    //grava 
    datalog.println(ldr);

    // Terminou de escrever, fecha-se o arquivo
    datalog.close();
    
    Serial.println("Gravado com sucesso!");
  }
  else 
  {
    Serial.println("Nao foi possivel abrir o arquivo");
  }
  
  //aguarda 2 segundos
  delay(2000);
  limpaDisplay();
}
