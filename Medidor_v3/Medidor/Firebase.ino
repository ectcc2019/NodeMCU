#include "medidor.h"

void inicializarFirebase()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.print("\nInicializando Firebase");
   
  //verificar como fazer para verificar a falha de conexão
  //talvez criar variavel auxiliar para pegar o status
  
}

void enviaDadosBanco(String no, float d, String dt)
{
  //Serial 
  Serial.println(no);
  Serial.println(d);
  Serial.println(dt);
  
  delay(2000); //aguarda 2 seg
  
  if (Firebase.failed()) {
      Serial.print("\nFalha ao enviar os dados ao Firebase: ");
      Serial.println(Firebase.error()); 
      
      gravaRegistroSD(no, d, dt);
      
      return;
  }
  else
  {
    //Envia os dados para o Firebase
    Firebase.pushFloat(no, d);
    Firebase.pushString(no, dt);
     
    delay(5000); // aguarda 5 segundos  
  }
}

void enviaDadosSD()
{
    
}
