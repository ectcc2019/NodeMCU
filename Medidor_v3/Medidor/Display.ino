#include "medidor.h"

void inicializarDisplay()
{
  display.init(); //inicializa display
  display.flipScreenVertically(); //muda pra vertical
  display.setFont(ArialMT_Plain_10); //define o tamanho da fonte
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  //barraProgresso(); //função da barra de progesso inicial
  display.clear(); //limpa a tela
}

void barraProgresso() 
{   
  for(counter=1; counter <= 100; counter++)
  {
    display.drawString(64, 0, "Iniciando");
    
    //desenha a barra de progresso
    display.drawProgressBar(0, 32, 120, 10, counter);
   
    //desenha a porcentagem e numero
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawString(64, 15, String(counter) + "%");
    display.display();
    delay(100);
    display.clear();
  }
} 

void tela()
{
  if(wifi_status == 1) //verifica status do wifi, se estiver conectado
  {
    display.drawString(7, 0, "WF");
    display.display();
  }

  
  if(sd_status == 1) //verifia status do cartão, se estiver presente
  {
    display.drawString(25, 0, "SD");
    display.display();
  }
  //atualizaRTC(); //atualiza a data e hora do NTP e depois o DS3201 
  
  //exibe a data e hora
  String a = String(dt_rtc.ano);
  String me = String(dt_rtc.mes);
  String di = String(dt_rtc.dia);
  
  String h = String(dt_rtc.hr);
  String mi = String(dt_rtc.min);
  
  String d = di+"/"+me+"/"+a;
  String t = h+":"+mi;
  
  display.drawString(65, 0, String(d));
  display.drawString(110, 0, String(t));

  String eid = getEspId();
  display.drawString(5, 50, "N.:");
  display.drawString(32, 50, eid);
  
  display.display();
  delay(5000);
}

String getEspId()
{
  String esp_id = String(ESP.getChipId());
  return esp_id;
}
