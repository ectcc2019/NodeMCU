#include "medidor.h"

void InicializarSDCard()
{
  //verifica se o cartão SD está presente
  if (!SD.begin(D8)) 
  {
    Serial.print("\nSD card não inicializado");
    sd_status=0;
    return;
  }
  else
  {
    Serial.print("\nInicializando SD card.");
    sd_status=1;
  }
}

void gravaRegistroSD(String n, float d, String dt)
{
  //verificar se o cartão está inserido, se não retornar
  //verificar se existe wifi para gravar um novo arq. log com os dados a serem enviados posteriormente
  
  if (sd_status == 1) //verifica status do SDCard
  { 
    if(wifi_status == 0) //verifica status do Wifi
    {
      conectarWifi(); //tenta realizar a conexão;
      
      datalog = SD.open("Log.txt", FILE_WRITE); //cria o arquivo
      
      if (datalog) //verifica se o arquivo existe
      {
        Serial.print("\nGravando...");

        
        //Serial.print(data);
        //datalog.println(data); //grava a data
        
        datalog.close(); //fecha o arquivo
        
        Serial.println("\nGravado com sucesso!");
        
      }
      else 
      {
        Serial.println("\nNao foi possivel abrir o arquivo");
      }
    }
    else //aqui não vai fazer nada, vai gravar apenas quando não tiver internet, abaixo testes
    {
      datalog = SD.open("log.txt", FILE_WRITE); //cria o arquivo
      
      if (datalog) //verifica se o arquivo existe
      {
        Serial.print("\nGravando...");
        
        auxsd = n + ";" + dt + ";" + d + "$";
        datalog.println(auxsd); //grava
        datalog.close(); // Terminou de escrever, fecha-se o arquivo
       }
    }
    delay(2000); //aguarda 2 segundos
  }
  else
  {
    InicializarSDCard();
  }
}

void leituraDadosSD() 
{ 
  if(sd_status == 0)
  {
    InicializarSDCard();
  }
  else
  {
    datalog = SD.open("Log.txt");
    Serial.println("Iniciando leitura");
    
    while (datalog.available() > 0)
    {
      character = datalog.read();
      if (bufferposition < buffer_size - 1)
      {
        Buffer[bufferposition++] = character;
        if ((character == '$'))
        {
          //new line function recognises a new line and moves on 
          Buffer[bufferposition] = 0;
          
          //do some action here
          bufferposition = 0;
        }
      }
    }
    Serial.println(Buffer);  
  }
  delay(1000);
}
