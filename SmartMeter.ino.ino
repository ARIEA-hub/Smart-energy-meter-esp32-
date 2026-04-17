#include <PZEM004Tv30.h>

#define ESP32_RX_PIN 27  
#define ESP32_TX_PIN 26  

PZEM004Tv30 pzem(Serial2, ESP32_RX_PIN, ESP32_TX_PIN);


float calculateBill(float units) {
  float bill = 0.0;
  if (units <= 100) bill = units * 4.43;
  else if (units <= 300) bill = (100 * 4.43) + ((units - 100) * 9.64);
  else if (units <= 500) bill = (100 * 4.43) + (200 * 9.64) + ((units - 300) * 12.83);
  else bill = (100 * 4.43) + (200 * 9.64) + (200 * 12.83) + ((units - 500) * 14.33);
  return bill;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  float v = pzem.voltage(); if(isnan(v)) v = 0;
  float c = pzem.current(); if(isnan(c)) c = 0;
  float p = pzem.power();   if(isnan(p)) p = 0;
  float e = pzem.energy();  if(isnan(e)) e = 0;
  float b = calculateBill(e);
  

  Serial.print("{\"voltage\":"); Serial.print(v);
  Serial.print(",\"current\":"); Serial.print(c);
  Serial.print(",\"power\":"); Serial.print(p);
  Serial.print(",\"energy\":"); Serial.print(e, 3);
  Serial.print(",\"bill\":"); Serial.print(b);
  Serial.println("}");
  
  delay(2000); 
}