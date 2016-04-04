
#include "IA.h"
#include "RFInterface.h"
#include "eepromanything.h"

void ackCallback()
{
   if(getTXData()->tx_ok)
     Serial.println("\nack received"); 
   else
     Serial.println("\nack not received"); 
}

IA::IA()
{
	m_gainFactor = 0;
	m_impedanceArray = { 0 };
	m_startFreq = 5000;
	m_incFreq = 1000;
	m_incNum = 5;
	m_cyclesNum = 25;
	m_calibImpedance = 10000;
	m_range = AD5933_RANGE_200mVpp;
	m_pga = AD5933_PGA_1;
	m_clock = AD5933_CONTROL_INT_SYSCLK;
	iaIsCalibrated = false;
}

IA::~IA()
{
	
}

void IA::initIA()
{
	if(m_AD5933.Init())
	{
		Serial.println("AD5933 OK");
	}
	else
	{
		Serial.println("AD5933 Error");
	}
	
	m_AD5933.ConfigSweep(m_startFreq, m_incFreq, m_incNum, m_cyclesNum);
	m_AD5933.StartSweep(m_range, m_pga, m_clock);
	EEPROM_readAnything(0x00, iaIsCalibrated);
	if(iaIsCalibrated)
		EEPROM_readAnything(0x01, m_gainFactor);
	else
	{
		m_gainFactor = m_AD5933.CalculateGainFactor(m_calibImpedance, AD5933_FUNCTION_REPEAT_FREQ);
		iaIsCalibrated = true;
		EEPROM_writeAnything(0x00, iaIsCalibrated);
		EEPROM_writeAnything(0x01, m_gainFactor);
	}
}

double IA::calibrateIA(unsigned long calibImpedance)
{
	
}

void IA::configIA(double startFreq, double incFreq, short incNum)
{
	m_startFreq = startFreq;
	m_incFreq = incFreq;
	m_incNum = incNum;
}

void IA::readImpedanceSamples()
{
	// read sweep samples
	unsigned long status = 0;
	unsigned int idx = 0;
	char tempString[10];
	unsigned long currentFreq = m_startFreq;
	double impedance;
	double doubleTemp;
	
	m_AD5933.ConfigSweep(m_startFreq, m_incFreq, m_incNum, m_cyclesNum);
	m_AD5933.StartSweep(m_range, m_pga, m_clock);
	
	do
	{
        impedance = m_AD5933.CalculateImpedance(m_gainFactor, AD5933_FUNCTION_INC_FREQ);
		m_impedanceArray[idx++] = (float)impedance / 1000;
        //! Send the requested value to user 
        sprintf(tempString, "%.3f", (double)impedance / 1000);
        Serial.print("impedance=");
        Serial.print(tempString);
        Serial.print(",");
        
        Serial.print("currentFreq=");
        Serial.print(currentFreq);
        Serial.print(",");
        
        doubleTemp=1/(m_gainFactor*impedance); 
        sprintf(tempString, "%.3f", (double)doubleTemp);
        Serial.print("Mu=");
        Serial.println(tempString);
              
        //! Update the currentFrequency 
        currentFreq = currentFreq + m_incFreq;
		status = m_AD5933.GetRegisterValue(AD5933_REG_STATUS,1);
    }
	while((status & AD5933_STAT_SWEEP_DONE) == 0 && idx < MAX_IMPEDANCE_SAMPLES);
	
	sendImpedance( m_impedanceArray, (unsigned long)m_startFreq, m_incNum, ackCallback );
}