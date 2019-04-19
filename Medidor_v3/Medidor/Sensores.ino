#include "medidor.h"

float leituraSensorCorrente(int wifi_status)
{  
  
  float sc = analogRead(A0);
  dados.no_fb = "IWwu27rTPzTBWNXHtamGSkGtzD63" ; //no do Firebase
  dados.datahora = ; //recebe a data e hora
  dados.corrente = sc; //recebe valor do sensor de corrente da porta A0
  dados.tensao = 127;
  dados.potencia = calculaPotencia(dados.corrente, dados.tensao);
  
  if(wifi_status == 0)
  {   
    //Serial - Debug
    Serial.println(dados.no_fb); 
    Serial.println(dados.corrente); 
    Serial.println(dados.datahora);     
    
    //gravaRegistroSD(dados.no_fb, dados.corrente, dados.datahora);
  }
  else
  {
     calculaPotencia(dados.corrente, dados.tensao);
    //enviaDadosBanco(dados.no_fb, dados.corrente, dados.datahora); 
  }
  delay(10000);
}

float calculaPotencia(float a, float v)
{
  float w = 0;
  w = a * v;
  
  return w;
}
