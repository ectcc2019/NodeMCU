/**
    Medidor de Energia 
    
**/

#ifndef MEDIDOR_H
#define MEDIDOR_H

//Bibliotecas

//Wifi
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

//NTP
#include <NTPClient.h> 

//UDP
#include <WiFiUDP.h> 

//RTC
#include <RTClib.h> 

//Comunicação com dispositivos I2C
#include <Wire.h> 

//Interface Periférica Serial
#include <SPI.h>

//SDCard  
#include <SD.h> 

//Firebase
#include <FirebaseArduino.h>

//Display
#include <brzo_i2c.h> 
#include "SSD1306Brzo.h"

// Inicializa o display usando BRZO_I2c
SSD1306Brzo display(0x3c, D1, D2);

#define SERIAL_VEL 115200 //velocidade da serial


#define FIREBASE_HOST "monitor-14d3b.firebaseio.com"
#define FIREBASE_AUTH "lXx80vSiHcRtGdv5h3PzUnmAXRewrjWVTivSJ27L"

//#define FIREBASE_HOST "energymonitor-2eb6a.firebaseio.com"
//#define FIREBASE_AUTH "4HD6hM9NABvNzbpIGvFvRwfKlSUH3z7JX8uhGzTp"

// D4 do NodeMCU controla o LED da placa
const int PIN_LED = 2; 

//definição dos nós do Firebase
String no_fb_sc = "Corrente";
String no_fb_st = "Tensão";
String no_fb_p = "Potência";

//declaração do objeto wifiManager
WiFiManager wifiManager;

//variavel auxiliar para receber status da conexão do Wifi
int wifi_status = -1;

//variavel auxilar para receber status do SDCard
int sd_status = -1;

//criar um objeto File para manipular um arquivo
File datalog;

//estrutura para guardar a data e hora
struct dt_rtc{
    String datahora;
    String data;
    String hora;
    int ds;
    int dia;
    int mes;
    int ano;
    int hr;
    int min;
    int seg;
} dt_rtc;

//Váriaveis que armazenarão a data e horario do NTP.
int splitT = 0;
String ntp_dt, ntp_d, ntp_t;

WiFiUDP ntpUDP;

//construindo o objeto rtc da classe DS3231
RTC_DS3231 rtc;

//Fuso horário UTC -3:00 Brasil
int16_t utc = -3;

//objeto UDP, servidor, fuzo_horário, tempo_update
NTPClient ntp(ntpUDP, "a.st1.ntp.br", utc*3600, 10000);

int counter = 1;
  
struct dados{
    String no_fb;
    String datahora;
    float corrente;
    float tensao;
    float potencia;
} dados;

String medidor_id;

char character;
int linenumber = 0;
const int buffer_size = 54;
int bufferposition=0;
char Buffer[buffer_size];
String txt, aux, auxsd;

//Funções
float leituraSensorCorrente(struct dados, String no_fb_sc, float sc);
void formataTextoDisplay(int size, int x, int y, String texto);
void gravaRegistroSD(String n, float d, String dt);


#endif
