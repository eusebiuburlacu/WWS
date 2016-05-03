/***************************************************************************//**
 *   @file   AD5933.c
 *   @brief  Implementation of AD5933 Driver.
 *   @author DBogdan (dragos.bogdan@analog.com)
 *           Ported to Arduino by Dan Nechita
********************************************************************************
 * Copyright 2012(c) Analog Devices, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *  - The use of this software may or may not infringe the patent rights
 *    of one or more patent holders.  This license does not release you
 *    from the requirement that you obtain separate licenses from these
 *    patent holders to use this software.
 *  - Use of the software either in source or binary form, must be run
 *    on or directly connected to an Analog Devices Inc. component.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANALOG DEVICES BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
********************************************************************************
 *   SVN Revision: 699
*******************************************************************************/

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/
#include "AD5933.h"
#include <Wire.h>
#include <math.h>
#include "WProgram.h"

/******************************************************************************/
/************************ Functions Definitions *******************************/
/******************************************************************************/

/***************************************************************************//**
 * @brief Writes data to a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer storing the transmission data.
 * @param bytesNumber - Number of bytes to write.
 *
 * @return None.
*******************************************************************************/
void  AD5933::I2C_Write(unsigned char slaveAddress,
						unsigned char *dataBuffer,
						unsigned char bytesNumber)
{
	unsigned char byte = 0;
	
	Wire.beginTransmission(slaveAddress);
	for(byte = 0; byte < bytesNumber; byte++)
	{
		Wire.send(dataBuffer[byte]);
	}
	Wire.endTransmission();
}

/***************************************************************************//**
 * @brief Reads data from a slave device.
 *
 * @param slaveAddress - Adress of the slave device.
 * @param dataBuffer - Pointer to a buffer that will store the received data.
 * @param bytesNumber - Number of bytes to read.
 *
 * @return None.
*******************************************************************************/
void AD5933::I2C_Read(unsigned char slaveAddress,
					  unsigned char *dataBuffer,
					  unsigned char bytesNumber)
{
	unsigned char byte = 0;
	
	Wire.beginTransmission(slaveAddress);
	Wire.requestFrom(slaveAddress, bytesNumber);
	while(Wire.available())
	{
		dataBuffer[byte] = Wire.receive();
		byte++;
	}
	Wire.endTransmission();
}

/***************************************************************************//**
 * @brief Writes data into a register.
 *
 * @param registerAddress - Address of the register.
 * @param registerValue - Data value to write.
 * @param bytesNumber - Number of bytes.
 *
 * @return None.
*******************************************************************************/
void AD5933::SetRegisterValue(unsigned char registerAddress,
                              unsigned long registerValue,
                              unsigned char bytesNumber)
{
    unsigned char byte         = 0;
    unsigned char writeData[2] = {0, 0};

    for(byte = 0;byte < bytesNumber;byte++)
    {
        writeData[0] = registerAddress + bytesNumber - byte - 1;
        writeData[1] = (unsigned char)((registerValue >> (byte * 8)) & 0xFF);
        I2C_Write(AD5933_ADDRESS, writeData, 2);
    }
}

/***************************************************************************//**
 * @brief Reads the value of a register.
 *
 * @param registerAddress - Address of the register.
 * @param bytesNumber - Number of bytes.
 *
 * @return registerValue - Value of the register.
*******************************************************************************/
unsigned long AD5933::GetRegisterValue(unsigned char registerAddress,
                                       unsigned char bytesNumber)
{
    unsigned long registerValue = 0;
    unsigned char byte          = 0;
    unsigned char writeData[2]  = {0, 0};
    unsigned char readData[2]   = {0, 0};
    
    for(byte = 0;byte < bytesNumber;byte ++)
    {
        /*! Set the register pointer. */
        writeData[0] = AD5933_ADDR_POINTER;
        writeData[1] = registerAddress + byte;
        I2C_Write(AD5933_ADDRESS, writeData, 2);
        /*! Read Register Data. */
        readData[0] = AD5933_ADDRESS;
        readData[1] = 0xFF;
        I2C_Read(AD5933_ADDRESS, readData, 1);
        registerValue = registerValue << 8;
        registerValue += readData[0];
    }
    
    return(registerValue);
}

/***************************************************************************//**
 * @brief Initializes the communication peripheral.
 *
 * @return 1.
*******************************************************************************/
unsigned char AD5933::Init(void)
{
    Wire.begin();
    
	return(1);
}

/***************************************************************************//**
 * @brief Reads the temperature from the part and returns the data in
 *        degrees Celsius.
 *
 * @return temperature - Temperature.
*******************************************************************************/

char AD5933::GetTemperature(void)
{
    short           temperature = 0;
    unsigned char   status      = 0;
	unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);   
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(AD5933_FUNCTION_MEASURE_TEMP)|temp,	
                          1);
    while((status & AD5933_STAT_TEMP_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    
    temperature = GetRegisterValue(AD5933_REG_TEMP_DATA,2);
    if(temperature < 8192)
    {
        temperature /= 32;
    }
    else
    {
        temperature -= 16384;
        temperature /= 32;
    }
    
    return((char)temperature);
}
/***************************************************************************//**
 * @brief Configures the sweep parameters: Start frequency, Frequency increment
 *        and Number of increments.
 *
 * @param startFreq - Start frequency;
 * @param incFreq - Frequency increment;
 * @param incNum - Number of increments.
 *
 * @return None.
*******************************************************************************/

void AD5933::ConfigSweep(double startFreq,
                         double incFreq,
                         short  incNum, 
						 short cyclesNum)
{
	unsigned long startFreqReg = 0;		//!< Start frequency register value. 
	unsigned long incFreqReg = 0;		//!< Increment frequency register value 
	
	startFreqReg = (unsigned long)((startFreq / MHZ_4) * POW_2_27);
	incFreqReg = (unsigned long)((incFreq / MHZ_4) * POW_2_27);
	Serial.println("Freq Start");
    SetRegisterValue(AD5933_REG_FREQ_START,
                     startFreqReg,
                     3);
	Serial.println("Freq inc");
    SetRegisterValue(AD5933_REG_FREQ_INC,
                     incFreqReg,
                     3);
    SetRegisterValue(AD5933_REG_INC_NUM,
                     incNum,
                     2);
	SetRegisterValue(AD5933_REG_SETTLING_CYCLES,
                     cyclesNum,
                     2);				 
}

/***************************************************************************//**
 * @brief Starts the sweep operation.
 *
 * @return None.
*******************************************************************************/

void AD5933::StartSweep(unsigned char range, unsigned char pga, unsigned char clock)
{
    unsigned char status = 0;
    
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(AD5933_FUNCTION_STANDBY),	
                     1); 
    SetRegisterValue(AD5933_REG_CONTROL_LB,
                     clock,
                     1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(AD5933_FUNCTION_INIT_START_FREQ)|AD5933_CONTROL_RANGE(range)|pga,	
                     1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(AD5933_FUNCTION_START_SWEEP)|AD5933_CONTROL_RANGE(range)|pga,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
}


/***************************************************************************//**
 * @brief Reads the real and the imaginary data and calculates the Gain Factor.
 *
 * @param calibrationImpedance - The calibration impedance value.
 * @param freqFunction - Frequency function.
 *                       Example: AD5933_FUNCTION_INC_FREQ - Increment freq.;
 *                                AD5933_FUNCTION_REPEAT_FREQ - Repeat freq..
 *
 * @return gainFactor - Calculated gain factor.
*******************************************************************************/

double AD5933::CalculateGainFactor(unsigned long calibrationImpedance,
                                   unsigned char freqFunction)
{
    double gainFactor = 0;
    double magnitude = 0;
    unsigned char status = 0;
    signed short realData = 0;
    signed short imagData = 0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
    magnitude = sqrt((realData * realData) + (imagData * imagData));
    gainFactor = 1 / (magnitude * calibrationImpedance);

    return(gainFactor);
}

void AD5933::CalculateGainFactorPhase(unsigned long calibrationImpedance,
                                   unsigned char freqFunction, double gFactor,double calibPhase)
{
    double magnitude = 0;
    unsigned char status = 0;
    signed short realData = 0;
    signed short imagData = 0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
    magnitude = sqrt((realData * realData) + (imagData * imagData));
    gFactor = 1 / (magnitude * calibrationImpedance);
	calibPhase=(180/pi)*atan(imagData/realData);
	if((realData<0)&&(imagData>0))
	calibPhase=calibPhase+180;
	if((realData<0)&&(imagData<0))
	calibPhase=calibPhase+180;
	if((realData>0)&&(imagData<0))
	calibPhase=calibPhase+360;   
}

void AD5933::CalculateGainFactorPhasePointer(unsigned long calibrationImpedance,
                                   unsigned char freqFunction, double *result, signed short *intrez)
{
    double magnitude = 0;
	double	gFactor=0;
	double	calibPhase=0;
	unsigned char charNumber = 0;
    unsigned char status = 0;
    signed short realData = 0;
    signed short imagData = 0;
	double frealData=0.0;
	double fimagData=0.0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
	frealData=realData;
	intrez[0]=realData;
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
	fimagData=imagData;
	intrez[1]=imagData;
    magnitude = sqrt((realData * realData) + (imagData * imagData));
    gFactor = 1 / (magnitude * calibrationImpedance);
	result[charNumber++]=gFactor;
	calibPhase=(180.0/pi)*atan(fimagData/frealData);
	if((realData<0)&&(imagData>0))
	calibPhase=calibPhase+180.0;
	if((realData<0)&&(imagData<0))
	calibPhase=calibPhase+180.0;
	if((realData>0)&&(imagData<0))
	calibPhase=calibPhase+360.0;   
	result[charNumber++]=calibPhase;
	result[charNumber]=0;
}
/***************************************************************************//**
 * @brief Reads the real and the imaginary data and calculates the Impedance.
 *
 * @param gainFactor - The gain factor.
 * @param freqFunction - Frequency function.
 *                       Example: AD5933_FUNCTION_INC_FREQ - Increment freq.;
 *                                AD5933_FUNCTION_REPEAT_FREQ - Repeat freq..
 *
 * @return impedance - Calculated impedance.
*******************************************************************************/

double AD5933::CalculateImpedance(double gainFactor, unsigned char freqFunction)
{
    signed short realData = 0;
    signed short imagData = 0;
    double magnitude = 0;
    double impedance = 0;
    unsigned char status = 0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
    magnitude = sqrt((realData * realData) + (imagData * imagData));
    impedance = 1 / (magnitude * gainFactor);
    
    return(impedance);    
}

void AD5933::CalculateImpedancePhase(double gainFactor, double sysPhase,
                                  unsigned char freqFunction, double impedance,double zPhase)
{
    signed short realData = 0;
    signed short imagData = 0;
    double magnitude = 0.0;
	double uPhase = 0.0;
    unsigned char status = 0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
    magnitude = sqrt((realData * realData) + (imagData * imagData));
	
    impedance = 1 / (magnitude * gainFactor);
    
	uPhase=(180/pi)*atan(imagData/realData);
	if((realData<0)&&(imagData>0))
	uPhase=uPhase+180;
	if((realData<0)&&(imagData<0))
	uPhase=uPhase+180;
	if((realData>0)&&(imagData<0))
	uPhase=uPhase+360;  
	
    zPhase=uPhase-sysPhase;    
}

void AD5933::CalculateImpedancePhasePointer(double gainFactor, double sysPhase,
                                  unsigned char freqFunction, double *uresult, signed short *intrz)
{
    signed short realData = 0;
    signed short imagData = 0;
	double frealData=0.0;
	double fimagData=0.0;
	unsigned char unumber=0;
    double magnitude = 0.0;
	double impedance=0.0;
	double uPhase = 0.0;
    unsigned char status = 0;
    unsigned char temp = 0;
	
	temp=0x0F & GetRegisterValue(AD5933_REG_CONTROL_HB,1);
    SetRegisterValue(AD5933_REG_CONTROL_HB,
                     AD5933_CONTROL_FUNCTION(freqFunction)|temp,		
                     1);
    status = 0;
    while((status & AD5933_STAT_DATA_VALID) == 0)
    {
        status = GetRegisterValue(AD5933_REG_STATUS,1);
    }
    realData = GetRegisterValue(AD5933_REG_REAL_DATA,2);
	frealData=realData;
	intrz[0]=realData;
    imagData = GetRegisterValue(AD5933_REG_IMAG_DATA,2);
	fimagData=imagData;
	intrz[1]=imagData;
    magnitude = sqrt((realData * realData) + (imagData * imagData));
	
    impedance = 1 / (magnitude * gainFactor);
    uresult[unumber++]=impedance;
	uPhase=(180.0/pi)*atan(fimagData/frealData);
	if((realData<0)&&(imagData>0))
	uPhase=uPhase+180.0;
	if((realData<0)&&(imagData<0))
	uPhase=uPhase+180.0;
	if((realData>0)&&(imagData<0))
	uPhase=uPhase+360.0; 	
	if((realData>0)&&(imagData>0))
	uPhase=uPhase+360.0; 
    uPhase=uPhase-sysPhase;
    uresult[unumber++]=uPhase;
	uresult[unumber]=0;
}