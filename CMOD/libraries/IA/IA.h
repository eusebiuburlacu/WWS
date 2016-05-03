
#ifndef IA_H
#define IA_H

#include <AD5933.h>
#include <Wire.h>

#define MAX_IMPEDANCE_SAMPLES 25

#define START_FREQ 5000

class IA
{
public:
	IA();
	~IA();
	
	void initIA();
	
	double calibrateIA(unsigned long calibImpedance);

	void configIA(double startFreq, double incFreq, short incNum);
	
	void readImpedanceSamples();
	
	void setFreq(double startFreq);
	
private:

	double m_startFreq;
	
	double m_incFreq;
	
	short m_incNum;
	
	short m_cyclesNum;
	
	long m_calibImpedance;

	double m_gainFactor;
	
	unsigned char m_range;
	
	unsigned char m_pga;
	
	unsigned char m_clock;
	
	bool iaIsCalibrated;
	
	float m_impedanceArray[MAX_IMPEDANCE_SAMPLES];
	
	AD5933 m_AD5933;
};

#endif