#include "energy.h"

WiFiUDP ntpUDP;

//construindo o objeto rtc da classe DS3231
RTC_DS3231 rtc;

//Fuso horário UTC -3:00 Brasil
int16_t utc = -3;
 
//Váriaveis que armazenarão a data e horario do NTP.

String ntp_dt, ntp_d, ntp_t; 
int splitT=0, ano=0, mes=0, dia=0, hora=0, minuto=0, segundo=0;

//objeto UDP, servidor, fuzo_horário, tempo_update
NTPClient ntp(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);

struct Date{
    int dayOfWeek;
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    int seconds;
} date;
    
void inicializarNTP()
{
  //Serial - Debug
  Serial.println("NTP inicializado!");

   //Display
  display.setTextSize(1); //definição do tamanho fonte
  display.setCursor(0,8); //definição da posição x,y 
  display.println("Inicializando NTP");  //exibe string no display
  display.display(); //exibe no display
  delay(2000); //aguarda 2 seg
  limpaDisplay(); //limpa display
  
  ntp.begin(); //Inicia o npt
  updateNTP(); //atualiza data e hora
  limpaDisplay(); //limpa display
}

void updateNTP()
{
  //tratar isso quando estiver sem internet
  ntp.update(); //força o update
  ntp_dt = ntp.getFormattedDate(); //obtém a data e hora
  splitT = ntp_dt.indexOf("T"); //divide a string, usando o indice do "T" como referência
  ntp_d  = ntp_dt.substring(0, splitT); //obtém a data
  ntp_t  = ntp_dt.substring(splitT+1, ntp_dt.length()-1); //obtém a hora

  /**
  //Serial - Debug
  Serial.println();
  Serial.println("NTP Atualizado! ");
  Serial.println(ntp_dt);
  Serial.println(ntp_d);
  Serial.println(ntp_t);   
    
  //Display
  display.setTextSize(1);
  display.setCursor(25,4);
  display.println("NTP Atualizado!");
  
  display.setCursor(35,14);
  display.println(ntp_d);
  
  display.setCursor(40,24);
  display.println(ntp_t);
  
  display.display();
  delay(10000); //aguarda 10 seg
  **/
  limpaDisplay();
}

void inicializarRTC()
{
  //Serial - Debug
  Serial.println("Inicializando RTC"); 

  //Display
  display.setTextSize(1); //tamanho fonte
  display.setCursor(0,8); //posição
  display.println("Inicializando RTC");  //exibe string no display
  display.display();
  delay(5000);
  
  Wire.begin();
  rtc.begin(); 
  atualizaRTC();
  limpaDisplay();
}

void exibeNTP()
{
  //Serial - Debug
  Serial.println();
  Serial.print("NTP:");
  Serial.println(ntp_d);
  Serial.println(ntp_t);
  
  //Display
  display.setTextSize(1);
  display.setCursor(25,4);
  display.println("NTP Atualizado!");
  
  display.setCursor(35,14);
  display.println(ntp_d);
  
  display.setCursor(40,24);
  display.println(ntp_t);
  display.display();
  
  delay(5000); //aguarda 10 seg
  limpaDisplay();
}

void atualizaRTC()
{
  //Recupera os dados de data e horário usando o client NTP
  char* strdt = (char*)ntp.getFormattedDate().c_str();
       
  sscanf(strdt, 
         "%d-%d-%dT%d:%d:%dZ", 
         &date.year, 
         &date.month, 
         &date.day, 
         &date.hours, 
         &date.minutes,
         &date.seconds
        );

  //definindo a data e hora do RTC, com os dados do NTP
  rtc.adjust(DateTime(date.year, date.month, date.day, date.hours, date.minutes, date.seconds));
 
  //Display
  delay(2000);
}

void exibeRTC()
{
  //Serial - Debug
  Serial.print("RTC:");
  Serial.print(date.year);     //Imprimindo o Ano   
  Serial.print("-");
  Serial.print(date.month);    //Imprimindo o Mês
  Serial.print("-");
  Serial.print(date.day);      //Imprimindo o Dia
  Serial.print(" ");
  Serial.print(date.hours);     //Imprimindo a Hora
  Serial.print(":");
  Serial.print(date.minutes);   //Imprimindo o Minuto
  Serial.print(":");
  Serial.print(date.seconds);   //Imprimindo o Segundo
  Serial.println("");

  //Display
  display.setCursor(0,4);
  display.printf("          RTC\n      %02d/%02d/%d\n       %02d:%02d:%02d",
                  date.day, 
                  date.month,
                  date.year, 
                  date.hours,
                  date.minutes, 
                  date.seconds);
  display.display();
  delay(5000); //aguarda 10 seg
  limpaDisplay();
}
