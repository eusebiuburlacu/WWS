
#include "IA.h"
#include "RFInterface.h"+


IA::IA()
{
	m_gainFactor = 0;
	
	m_impedanceArray = { 0 };
}

IA::~IA()
{
	
}

double IA::calibrateIA(unsigned long calibImpedance)
{
	
}

double IA::getEEPROMGainFactor(int address)
{
	
}

void IA::configIA()
{
	
}

void IA::readImpedanceSamples()
{
	// read sweep samples
	
	sendImpedance( m_impedanceArray, 30 );
}