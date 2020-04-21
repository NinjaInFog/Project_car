#include <SPI.h>                                          //  Підключаємо бібліотеку для роботи з шиною SPI
#include <nRF24L01.h>                                     // Підключаємо файл настройок з бібліотеки RF24
#include <RF24.h>                                         // Підключаємо бібліотеку для роботи з nRF24L01 +
int button = 8, button2 = 6;
RF24 radio(9, 10);                                         // Створюємо об'єкт radio для роботи з бібліотекою RF24, вказуючи номери створюємо масив для прийому даних
int  data[2];                                              // створюємо масив для прийому даних
void setup() {
  
  Serial.begin(9600);
  radio.begin();                                        // Почнемо роботу nRF24L01 +
  pinMode(button, OUTPUT);
  pinMode(button2, OUTPUT);
  radio.setChannel(5);                                  // Вказуємо канал передачі даних (від 0 до 127), 5 - значить передача даних здійснюється на частоті 2,405 ГГц (на одному каналі може бути тільки 1 датчик і до 6 передавачів)
  radio.setDataRate     (RF24_1MBPS);                   // Вказуємо швидкість передачі даних (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1 Мбіт / сек
  radio.setPALevel      (RF24_PA_HIGH);                 // Вказуємо потужність передавача (RF24_PA_MIN = -18dBm, RF24_PA_LOW = -12dBm, RF24_PA_HIGH = -6dBm, RF24_PA_MAX = 0dBm)
  radio.openWritingPipe (0x1234567890LL);               // Відкриваємо трубу з ідентифікатором 0x1234567890 для передачі даних (на одному каналі може бути відкрито до 6 різних труб, які повинні відрізнятися тільки останнім байтом ідентифікатора)
  digitalWrite(button, HIGH);
  digitalWrite(button2, HIGH);
}
void loop() {
  data[0] = analogRead(A0);         // перший датчик
  data[0] = map(data[0], 0, 355, 255, 0);
  //if (data[0] < 110)data[0] = 0;  data[0] = data[0] * 10 + 1;
  data[1] = analogRead(A6);          // другий датчик
  data[1] = map(data[1], 0, 129, 255, 0);
  //if (data[1] < 110)data[1] = 0; data[1] = data[1] * 10 + 2;
  radio.write(&data, sizeof(data));
 Serial.print("data[0]=");
 Serial.println(data[0]);
  Serial.print("data[1]=");
 Serial.println(data[1]);  

}
