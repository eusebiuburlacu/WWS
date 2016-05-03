#include "SPI.h"
#include "WProgram.h"
#include "mrf24j.h"
#include "RFWrapper.h"
#include "RFInterface.h"
#include "Wire.h"
#include "AD5933.h"
#include <EEPROM.h>
#include <WProgram.h>
#include "IA.h"
#include "eepromanything.h"
#include <SHT2x.h>

IA ia;
unsigned long updateInt = 100;
unsigned long freqSet = 5000;

void RxCallback()
{
  int dataLen;
  rx_info *RXInfo =  getRXData(dataLen);
  if(0==RXInfo)
    Serial.println(0);
    else
     Serial.println(1);
    
  uint8_t msgType = RXInfo->rx_data[0];
  
  if(1 == msgType)
  {
    uint8_t *valFPtr = (uint8_t*)(void *)&updateInt;
    *valFPtr++ = RXInfo->rx_data[1];
    *valFPtr++ = RXInfo->rx_data[2];
    *valFPtr++ = RXInfo->rx_data[3];
    *valFPtr++ = RXInfo->rx_data[4];
    
    Serial.print("update Int");
    Serial.println(updateInt);
  }
  else if(2 == msgType)
  {
    uint8_t *valFPtr = (uint8_t*)(void *)&freqSet;
    *valFPtr++ = RXInfo->rx_data[1];
    *valFPtr++ = RXInfo->rx_data[2];
    *valFPtr++ = RXInfo->rx_data[3];
    *valFPtr++ = RXInfo->rx_data[4];
    
    ia.setFreq(freqSet);
    Serial.print("Frequ SET:");
    Serial.println(freqSet);
  }
}

void setup()
{
    Serial.begin(9600);
    Serial.println("word");
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
    initRF();
    ia.initIA();
    Serial.println("InitIA");
    registerRXCallback(RxCallback);
    Serial.println("registerRX");
}

float imp[] = {11.1, 23.2, 23.3, 24.45};

float pha[] = {0.3, 12.2, 23.3, 43.45};

void callback()
{
   if(getTXData()->tx_ok)
     Serial.println("\nack received"); 
   else
     Serial.println("\nack not received"); 
}

void loop()
{
  if(0==digitalRead(7))
    interruptRoutine();
  //Serial.println("Test");
  ia.readImpedanceSamples();
  //void interruptRoutine();
  delay(2);
  //float temperature = SHT2x.GetTemperature();
  //Serial.print("Temperature(C): ");
  //Serial.println(temperature);
  //sendTemperature(temperature, callback);
  delay(2);
  //void interruptRoutine();
  //float humidity = SHT2x.GetHumidity();
  //Serial.print("Humidity(%RH): ");
  //Serial.println(humidity);
  //sendHumidity((unsigned char)humidity, callback);
  //void interruptRoutine();
  delay(200);
}
