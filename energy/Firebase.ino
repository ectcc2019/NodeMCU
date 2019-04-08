#include "energy.h"

#define FIREBASE_HOST "monitor-14d3b.firebaseio.com"
#define FIREBASE_AUTH "lXx80vSiHcRtGdv5h3PzUnmAXRewrjWVTivSJ27L"

void inicializarFirebase()
{
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void enviaDadosFirebase(String no, float val)
{
  Serial.println("Teste:");
  Serial.println(no);
  Serial.println(val);
  delay(2000);

  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  else
  {
    Firebase.pushFloat(no, val); // Envia o valor para a variavel no Firebase
    delay(5000); // Espera 5 segundos  
  }
  
}
