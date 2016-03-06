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

IA ia;

void setup()
{
    Serial.begin(9600);
    Serial.println("word");
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
  sendImpedance( imp, 4, callback );
  delay(2);
  sendPhase(pha, 4, callback);
  delay(2);
  sendTemperature(23.21, callback);
  delay(2);
  sendHumidity(46, callback);
  delay(2);
  sendBatteryVoltage(3.76, callback);
  delay(2000);
}
