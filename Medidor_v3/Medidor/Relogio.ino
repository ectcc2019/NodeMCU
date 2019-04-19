#include "medidor.h"


void inicializarRTC()
{
  //Serial - Debug
  Serial.println("\nInicializando RTC"); 
  Wire.begin(); 
  rtc.begin();  //inicializa o rtc
  inicializarNTP();
  atualizaRTC();
}

void inicializarNTP()
{ 
    Serial.println("\nInicializando NTP");
    ntp.begin();     //inicializa ntp
    ntp.update();     //atualiza data e hora do NTP
}

void atualizaRTC()
{
  Serial.print("\nAjustando RTC ");
  
  ntp.update();  //atualiza data e hora do NTP
  
  //Recupera os dados de data e horário usando o client NTP
  char* strdt = (char*)ntp.getFormattedDate().c_str();

  
  sscanf(strdt, 
         "%d-%d-%dT%d:%d:%dZ", 
         &dt_rtc.ano, 
         &dt_rtc.mes, 
         &dt_rtc.dia, 
         &dt_rtc.hr, 
         &dt_rtc.min,
         &dt_rtc.seg
        );

  //definindo a data e hora do RTC, com os dados do NTP
  rtc.adjust(DateTime(dt_rtc.ano, dt_rtc.mes, dt_rtc.dia, dt_rtc.hr, dt_rtc.min, dt_rtc.seg));
  
  Serial.print(dt_rtc.ano);
  Serial.print("/");
  Serial.print(dt_rtc.mes);
  Serial.print("/");
  Serial.print(dt_rtc.dia);
  Serial.print(" ");
  Serial.print(dt_rtc.hr);
  Serial.print(":");
  Serial.print(dt_rtc.min);
  Serial.print(":");
  Serial.print(dt_rtc.seg);
  
  delay(5000);
}
