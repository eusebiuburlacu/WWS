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
    sendImpedance( 0, 0 );
}

float imp[] = {0.1, 0.2, 0.3, 0.45};

void loop()
{
  sendImpedance( imp, 4 );
  delay(2000);
}
