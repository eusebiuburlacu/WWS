#include "RFInterface.h"
#include "RFWrapper.h"
#include "IA.h"

IA ia;
void setup()
{
     Serial.begin(9600);
     ia.readImpedanceSamples();
}

void loop()
{

}
