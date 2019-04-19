#include "medidor.h"

void inicializarWifiManager() 
{     
  //define o tempo (seg) de configuração do portal 
  wifiManager.setTimeout(30); 
  
  //Teste - reseta as configurações
  //wifiManager.resetSettings();  

  //define um endereço ip customizado para o portal
  //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
  
  //Serial
  Serial.print("\nInicializando Wifi");
  Serial.print("\nConectando-se ao Wi-fi...");
  
  display.drawString(60, 20, "Conectando-se ao Wi-fi...");
  display.display();
  
  delay(5000);
  
  conectarWifi();
  
  if (wifi_status == 0)
  {
    display.drawString(50, 30, "Falha ao se conectar!");
    display.display();
    delay(5000);
  }
  else
  {
    display.drawString(64, 30, "Conectado!");
    display.display();
  }
  delay(3000);
  display.clear(); //limpa a tela
}

int verificaWifi()
{
  if (WiFi.status() != WL_CONNECTED) //verifica se está conectado
  {
    Serial.print("\nSem conexão Wi-fi");
    wifi_status = 0;
  }
  else 
  {
    Serial.print("\nConectado ao Wi-fi");
    wifi_status = 1;
  }

  return wifi_status; //retorna o status
}

void conectarWifi()
{
  wifi_status = verificaWifi(); //verifica status do wifi
  
  if (wifi_status == 0) //se não existir conexão
  {
    // inicializa o pino digital do LED como saída
    pinMode(PIN_LED, OUTPUT);

    // Liga o LED como LOW para informar que entrou em modo de configuração
    digitalWrite(PIN_LED, LOW);
    
    display.drawString(60, 30, "Acesse 192.168.4.1 para conectar.");
    display.display();
    
    //Cria o Access Point com os dados abaixo
    if(!wifiManager.autoConnect("AP", "12345678")) 
    {
      Serial.println("\nTempo de Configuração esgotado");
      display.drawString(60, 30, "Tempo de Configuração esgotado");
      display.display();
      delay(5000);
    } 
  }
  else //se estiver conectado
  {
    //define como estação
    WiFi.mode(WIFI_STA); 
    
    // Desliga o led para informar que não está mais em modo de configuração
    digitalWrite(PIN_LED, HIGH);
  }  
}
