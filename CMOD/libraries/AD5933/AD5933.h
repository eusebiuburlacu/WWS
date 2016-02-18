/***************************************************************************//**
 *   @file   AD5933.h
 *   @brief  Header file of AD5933 Driver.
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
#ifndef __AD5933_H__
#define __AD5933_H__

/******************************************************************************/
/***************************** Include Files **********************************/
/******************************************************************************/

/******************************************************************************/
/******************* Macros and Constants Definitions *************************/
/******************************************************************************/

#define pi 3.14159265
/*! AD5933 Registers */
#define AD5933_REG_CONTROL_HB       0x80    /*!< HB of the Control register */
#define AD5933_REG_CONTROL_LB       0x81    /*!< LB of the Control register */
#define AD5933_REG_FREQ_START       0x82    /*!< Start frequency */
#define AD5933_REG_FREQ_INC         0x85    /*!< Frequency increment */
#define AD5933_REG_INC_NUM          0x88    /*!< Number of increments */
#define AD5933_REG_SETTLING_CYCLES  0x8A    /*!< Number of settling time cycles */
#define AD5933_REG_STATUS           0x8F    /*!< Status */
#define AD5933_REG_TEMP_DATA        0x92    /*!< Temperature data */
#define AD5933_REG_REAL_DATA        0x94    /*!< Real data */
#define AD5933_REG_IMAG_DATA        0x96    /*!< Imaginary data */

/*! AD5933_REG_CONTROL_HB Bits */
#define AD5933_CONTROL_FUNCTION(x)  ((x) << 4)     
#define AD5933_CONTROL_RANGE(x)     ((x) << 1)

/*! AD5933_REG_CONTROL_LB Bits */
#define AD5933_CONTROL_RESET        (0x1 << 4)
#define AD5933_CONTROL_INT_SYSCLK   (0x0 << 3)
#define AD5933_CONTROL_EXT_SYSCLK   (0x1 << 3)

/*! AD5933_CONTROL_FUNCTION(x) options */
#define AD5933_FUNCTION_INIT_START_FREQ     0x1
#define AD5933_FUNCTION_START_SWEEP         0x2
#define AD5933_FUNCTION_INC_FREQ            0x3
#define AD5933_FUNCTION_REPEAT_FREQ         0x4
#define AD5933_FUNCTION_MEASURE_TEMP        0x9
#define AD5933_FUNCTION_POWER_DOWN          0xA
#define AD5933_FUNCTION_STANDBY             0xB

/*! AD5933_CONTROL_RANGE(x) options */
#define AD5933_RANGE_2000mVpp   0x0
#define AD5933_RANGE_200mVpp    0x1
#define AD5933_RANGE_400mVpp    0x2
#define AD5933_RANGE_1000mVpp   0x3

/*! AD5933_CONTROL_PGA options */
#define AD5933_PGA_1		    0x1
#define AD5933_PGA_5		    0x0

/*! AD5933_REG_STATUS Bits */
#define AD5933_STAT_TEMP_VALID  (0x1 << 0)
#define AD5933_STAT_DATA_VALID  (0x1 << 1)
#define AD5933_STAT_SWEEP_DONE  (0x1 << 2)

/*! AD5933 Address */
#define AD5933_ADDRESS          0x0D

/*! AD5933 Block Commands */
#define AD5933_BLOCK_WRITE      0xA0
#define AD5933_BLOCK_READ       0xA1
#define AD5933_ADDR_POINTER     0xB0

class AD5933
{
private:
	/*! Constants values specific to this device. */
	static const long  MHZ_4 = 4000000;             /*!< 16MHz / 4 */
	static const long  POW_2_27 = 134217728;        /*!< 2 to the power of 27 */
	static const long  MAX_START_FREQ = 500000;     /*!< 500 KHz maximum frequency */
	static const short MAX_INC_NUM = 511;           /*!< Value is represented by a 9-bit word */

	/*! Writes data to a slave device. */
	void I2C_Write(unsigned char slaveAddress,
                   unsigned char *dataBuffer,
                   unsigned char bytesNumber);
	/*! Reads data from a slave device. */
	void I2C_Read(unsigned char slaveAddress,
                  unsigned char *dataBuffer,
                  unsigned char bytesNumber);

public:
	/*! Writes data into a register. */
	void SetRegisterValue(unsigned char registerAddress,
						  unsigned long registerValue,
						  unsigned char bytesNumber);

	/*! Reads the value of a register. */
	unsigned long GetRegisterValue(unsigned char registerAddress,
						      	   unsigned char bytesNumber);

	/*! Initializes the communication peripheral. */
	unsigned char Init(void);

	/*! Reads the temp. from the part and returns the data in degrees Celsius. */
	char GetTemperature(void);
	
	/*! Configures the sweep parameters. */

	void ConfigSweep(double startFreq,
					 double incFreq,
					 short  incNum,
					 short	cyclesNum);
					 
	/*! Starts the sweep operation. */
	void StartSweep(unsigned char range, unsigned char pga, unsigned char clock);
	

	double CalculateGainFactor(unsigned long calibrationImpedance,
                                   unsigned char freqFunction);
	void  CalculateGainFactorPhase(unsigned long calibrationImpedance,
                                   unsigned char freqFunction, double gFactor,double calibPhase);
	void  CalculateGainFactorPhasePointer(unsigned long calibrationImpedance,
                                   unsigned char freqFunction, double *result, signed short *intrez);

								   
	/*! Reads the real and the imaginary data and calculates the Impedance. */
	double CalculateImpedance(double gainFactor,
							  unsigned char freqFunction);
	void CalculateImpedancePhase(double gainFactor, double sysPhase,
                                  unsigned char freqFunction, double impedance,double zPhase);
	void CalculateImpedancePhasePointer(double gainFactor, double sysPhase,
                                  unsigned char freqFunction, double *uresult,signed short *intrz);
};

#endif	/*__AD5933_H__*/
