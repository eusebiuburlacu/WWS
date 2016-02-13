
#ifndef IA_H
#define IA_H

#define MAX_IMPEDANCE_SAMPLES 30

#define START_FREQ 5000

class IA
{
public:
	IA();
	~IA();
	
	double calibrateIA(unsigned long calibImpedance);
	
	double getEEPROMGainFactor(int address);
	
	void configIA();
	
	void readImpedanceSamples();
	
private:

	double m_gainFactor;
	
	float m_impedanceArray[MAX_IMPEDANCE_SAMPLES];
};

#endif