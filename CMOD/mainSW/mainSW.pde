#include "SPI.h"
#include "WProgram.h"
#include "mrf24j.h"
#include "RFWrapper.h"
#include "RFInterface.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("word");
    initRF();
}

float imp[] = {0.1, 0.2, 0.3, 0.45};

void callback()
{
   if(getTXData()->tx_ok)
     Serial.println("\nack received"); 
   else
     Serial.println("\nack not received"); 
}

void loop()
{
  sendImpedance( imp, 4, callback );
  delay(2000);
}
