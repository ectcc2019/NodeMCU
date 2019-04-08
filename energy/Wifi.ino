#include "energy.h"

#define WIFI_TENTATIVAS 5 //Tentativas para realizar a conexão

const char* ssid = "Juninho 2Ghz";
const char* senha = "26041988";

void inicializarWifi()
{ 
 
  //Definindo como modo estação (Station)
  WiFi.mode(WIFI_STA);  
  
  //Serial - Debug
  Serial.println();
  Serial.print("Inicializando Wifi");

  //Display
  display.setTextSize(1); //tamanho fonte
  display.setCursor(8,8); //posição
  display.println("Inicializando WiFi");  //exibe string no display
  display.display();
  delay(2000);
  
  for(int i = 0; i < WIFI_TENTATIVAS ; i++)
  { 
       
    //Serial - Debug
    Serial.println();
    Serial.print("Conectando...");
  
    //Display
    limpaDisplay();
    display.setTextSize(1);
    display.setCursor(10,10);
    display.println("Conectando...");
    display.display();
    delay(2000); 

    //inicializa a conexão com os dados
    WiFi.begin(ssid, senha);
      
    delay(2000); //aguarda 2 segundas

    if (WiFi.status() != WL_CONNECTED) 
    {
      //Serial - Debug 
      Serial.println();
      Serial.print("Falha na conexão");

      //Display
      display.setTextSize(1);
      display.setCursor(20,18);
      display.println("Falha na conexao");
      display.display();
      delay(2000);     
    }  
    else
    {
      limpaDisplay();
      
      //Serial - Debug
      Serial.println();
      Serial.print("Conectado a rede: ");
      Serial.println(ssid);
      //Serial.println(WiFi.localIP());

      //Display
      display.setTextSize(1);
      display.setCursor(30,8);
      display.println("Conectado: ");
      display.setTextSize(1);
      display.setCursor(15,16);
      display.println(ssid);
      display.display();
      delay(5000);
      limpaDisplay();
      return;
    }
  }
  limpaDisplay();
}
