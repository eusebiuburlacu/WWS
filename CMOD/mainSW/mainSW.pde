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

void setup()
{
    Serial.begin(9600);
    Serial.println("word");
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
    initRF();
    ia.initIA();
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
  ia.readImpedanceSamples();
  
  delay(2);
  float temperature = SHT2x.GetTemperature();
  Serial.print("Temperature(C): ");
  Serial.println(temperature);
  sendTemperature(temperature, callback);
  delay(2);
  float humidity = SHT2x.GetHumidity();
  Serial.print("Humidity(%RH): ");
  Serial.println(humidity);
  sendHumidity((unsigned char)humidity, callback);

  delay(200);
}
