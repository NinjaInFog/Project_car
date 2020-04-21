#include <SPI.h>                                          // Подключаем библиотеку  для работы с шиной SPI
#include "nRF24L01.h"                                     // Подключаем файл настроек из библиотеки RF24
#include "RF24.h"                                         // Подключаем библиотеку  для работы с nRF24L01+                                     
RF24 radio(9, 10);                                        // Создаём объект radio   для работы с библиотекой RF24                             
int data[2]; 
int input=0,ost;
int r[2];
// визначаємо піни управління правим мотором
int IN1 = 5;  
int IN2 = 4;
// визначаємо піни управління лівим мотором
int IN3 = 7;
int IN4 = 8;
// визначаємо піни управління швидкістю правого мотора
int ENA = 6;
// визначаємо піни управління швидкістю лівого мотора
int ENB = 3;


void setup()
{
Serial.begin(9600);
  delay(1000);                                          // Почнемо роботу індикатора
  radio.begin();                                        // Почнемо роботу nRF24L01 +
  radio.setChannel(5);                                  // Вказуємо канал прийому даних
  radio.setDataRate (RF24_1MBPS);                       // Вказуємо швидкість передачі даних 
  radio.setPALevel (RF24_PA_HIGH);                      // Вказуємо потужність передавача
  radio.openReadingPipe (1,0x1234567890LL);            // Відкриваємо 1 трубу з ідентифікатором 0x1234567890 для прийому даних
  radio.startListening ();                   

  pinMode (IN1, OUTPUT); 
  pinMode (IN2, OUTPUT); 
  pinMode (IN3, OUTPUT); 
  pinMode (IN4, OUTPUT); 
  pinMode (ENA, OUTPUT); 
  pinMode (ENB, OUTPUT); 
  
}

void testA(int i)
{
  digitalWrite (IN2, HIGH);
  digitalWrite (IN1, LOW); 
  analogWrite(ENA, i);
}
void testB(int i)
{
  digitalWrite (IN4, HIGH);
  digitalWrite (IN3, LOW); 
  analogWrite(ENB, i);
}
void loop()
{
  
      if ( radio.available() )
  {
    radio.read( &data, sizeof(data) );
     input = data[0];
     ost = data[1];
     //ost = input%10;
     //input = (input-ost)/10;
     //Serial.print(input);
     //if (ost == 1)
     //testA(input);
        //else 
     // testB(ost);
     if (input<0)
        input*=(-1);
     if (ost<0)
        ost*=(-1);   
     testA(input);
     testB(ost);
 Serial.print("data[0]=");
 Serial.println(data[0]);
  Serial.print("data[1]=");
 Serial.println(data[1]);      
}}
