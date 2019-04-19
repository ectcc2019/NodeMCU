#include "medidor.h"

void setup() 
{
  //Inicializa a Serial
  Serial.begin(SERIAL_VEL); 
  delay(3000);
  
  //Inicialização dos componentes e funções
  
  InicializarSDCard();
  inicializarRTC();
  delay(5000);
  
  inicializarDisplay();
  inicializarWifiManager();
  inicializarFirebase();
}

void loop() 
{   
  //limpa display
  display.clear();
  display.display();
  
  //recebe o status da conexão wifi
  wifi_status = verificaWifi(); 

 
  //exibe as informações no display
  tela();
  
  if (wifi_status == 0) //verifica o status do wifi
  {
    conectarWifi(); //tenta realizar a conexão
  }

  leituraSensorCorrente(wifi_status); //realiza leitura do sensor
  
  delay(5000); //aguarda 2 segundos
}
