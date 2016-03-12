/************************************************************************/
/*																		*/
/*	OledDriver.c	-- Graphics Driver Library for OLED Display			*/
/*																		*/
/************************************************************************/
/*	Author: 	Gene Apperson											*/
/*	Copyright 2011, Digilent Inc.										*/
/************************************************************************/
/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*	This is part of the device driver software for the OLED bit mapped	*/
/*	display on the Digilent Basic I/O Shield. This module contains the	*/
/*	initialization functions and basic display control functions.		*/
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	04/29/2011(GeneA): Created											*/
/*	08/03/2011(GeneA): added functions to shut down the display and to	*/
/*		turn the display on and off.	
/*	22/02/2016(EusebiuB): adapted library to work on Zybo				*/
/*																		*/
/************************************************************************/


/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */


extern "C" {
	#include <inttypes.h>
}

#include "OLED/OledDriver.h"
#include "OLED/OledChar.h"
#include "OLED/OledGrph.h"
#include <stddef.h>
#include <stdio.h>
#include <xil_io.h>
#include <xil_types.h>
#include <xspi.h>		/* SPI device driver */
#include <xspi_l.h>
#include <xstatus.h>
#include <xgpio.h>
#include "sleep.h"

/* ------------------------------------------------------------ */
/*				Local Symbol Definitions						*/
/* ------------------------------------------------------------ */

#define	cmdOledDisplayOn	0xAF
#define	cmdOledDisplayOff	0xAE
#define	cmdOledSegRemap		0xA1	//map column 127 to SEG0
#define	cmdOledComDir		0xC8	//scan from COM[N-1] to COM0
#define	cmdOledComConfig	0xDA	//set COM hardware configuration

/* ------------------------------------------------------------ */
/*				Global Variables								*/
/* ------------------------------------------------------------ */

extern const uint8_t	rgbOledFont0[];
extern uint8_t		rgbOledFontUser[];
extern const uint8_t	rgbFillPat[];

extern int		xchOledMax;
extern int		ychOledMax;

/* Coordinates of current pixel location on the display. The origin
** is at the upper left of the display. X increases to the right
** and y increases going down.
*/
int		xcoOledCur;
int		ycoOledCur;

uint8_t *	pbOledCur;			//address of byte corresponding to current location
int			bnOledCur;			//bit number of bit corresponding to current location
uint8_t		clrOledCur;			//drawing color to use
uint8_t *	pbOledPatCur;		//current fill pattern
int			fOledCharUpdate;

int		dxcoOledFontCur;
int		dycoOledFontCur;

uint8_t *	pbOledFontCur;
uint8_t *	pbOledFontUser;

// Spi 0 Controller object instantiation
//DSPI0 spiCon;

/* Setting pins based on DSPI_SS pin plus offset to get to lower 4 pins
** on pmod connector
*/
/*#if defined (_BOARD_CMOD_)
	const int DataCmd	= 7;	//Pin J1-07
	const int Reset		= 6;	//Pin J1-08
	const int VbatCtrl	= 30;	//Pin J1-09
	const int VddCtrl	= 8;	//Pin J1-10
#else
	const int DataCmd	= PIN_DSPI0_SS + 4;
	const int Reset		= PIN_DSPI0_SS + 5;
	const int VbatCtrl	= PIN_DSPI0_SS + 6;
	const int VddCtrl	= PIN_DSPI0_SS + 7;
#endif*/

#define DATA_CMD_MASK	0x01
#define RESET_MASK		0x02
#define VBAT_CTRL_MASK	0x04
#define VDD_CTRL_MASK	0x08

/* ------------------------------------------------------------ */
/*				Local Variables									*/
/* ------------------------------------------------------------ */

/* This array is the offscreen frame buffer used for rendering.
** It isn't possible to read back frome the OLED display device,
** so display data is rendered into this offscreen buffer and then
** copied to the display.
*/
uint8_t	rgbOledBmp[cbOledDispMax];

 XSpi SpiInstance;

static XGpio gpioInstance;

/* ------------------------------------------------------------ */
/*				Forward Declarations							*/
/* ------------------------------------------------------------ */

void	OledHostInit();
void	OledHostTerm();
void	OledDevInit();
void	OledDevTerm();
void	OledDvrInit();

void	OledPutBuffer(int cb, uint8_t * rgbTx);
uint8_t	Spi2PutByte(uint8_t bVal);

/* ------------------------------------------------------------ */
/*				Procedure Definitions							*/
/* ------------------------------------------------------------ */
/***	OledInit
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the OLED display subsystem.
*/

void OledInit()
{

	/* Init the PIC32 peripherals used to talk to the display.
	*/
	OledHostInit();

	/* Init the memory variables used to control access to the
	** display.
	*/
	OledDvrInit();

	/* Init the OLED display hardware.
	*/
	OledDevInit();

	/* Clear the display.
	*/
	OledClear();
}

/* ------------------------------------------------------------ */
/***	OledTerm
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Shut down the OLED display.
*/

void OledTerm()
{
	/* Shut down the OLED display hardware.
	*/
	OledDevTerm();

	/* Release the PIC32 peripherals being used.
	*/
	OledHostTerm();
}

/* ------------------------------------------------------------ */
/***	OledHostInit
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Perform PIC32 device initialization to prepare for use
**		of the OLED display.
**		This is currently hard coded for the Cerebot 32MX4 and
**		SPI2. This needs to be generalized.
*/

void OledHostInit()
{
	XSpi_Config *SPIConfigPtr;

	XGpio_Config *GPIOConfigPtr;
	int status;
	/*
	* Initialize the SPI driver so that it is  ready to use.
	*/
	SPIConfigPtr = XSpi_LookupConfig(XPAR_SPI_1_DEVICE_ID);
	if (SPIConfigPtr == NULL)
	{
		printf("OledHostInit: ERROR: SPI device not found");
	}

	status = XSpi_CfgInitialize(&SpiInstance, SPIConfigPtr, SPIConfigPtr->BaseAddress);
	if (status != XST_SUCCESS)
	{
		printf("OledHostInit: ERROR: cannot init SPI");
	}

	/*
	 * Set the Spi device as a master.
	 */
	status = XSpi_SetOptions( &SpiInstance, XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION |
			XSP_CLK_ACTIVE_LOW_OPTION | XSP_CLK_PHASE_1_OPTION);
	if (status != XST_SUCCESS)
	{
		printf("OledHostInit: ERROR: set SPI options");
	}


	/*
	* Start the SPI driver so that the device is enabled.
	*/
	XSpi_Start(&SpiInstance);

	/*
	* Disable Global interrupt to use polled mode operation
	*/
	XSpi_IntrGlobalDisable(&SpiInstance);

	u32 slaveReg = XSpi_GetSlaveSelectReg(&SpiInstance);

	XSpi_SetSlaveSelectReg(&SpiInstance, 0x00);

	slaveReg = XSpi_GetSlaveSelectReg(&SpiInstance);

	//GPIO config
	GPIOConfigPtr = XGpio_LookupConfig(XPAR_GPIO_0_DEVICE_ID);
	if (GPIOConfigPtr == NULL)
	{
		printf("OledHostInit: ERROR: GPIO device not found");
	}

	status = XGpio_CfgInitialize(&gpioInstance, GPIOConfigPtr, GPIOConfigPtr->BaseAddress);
	if (status != XST_SUCCESS)
	{
		printf("OledHostInit: ERROR: cannot init GPIO");
	}

	XGpio_SetDataDirection(&gpioInstance, 1, 0xf0);

	XGpio_DiscreteWrite(&gpioInstance, 1, 0x0F);

}

/* ------------------------------------------------------------ */
/***	OledHostTerm
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Release processor resources used by the library
*/

void OledHostTerm()
{
	XGpio_DiscreteWrite(&gpioInstance, 1, 0x0f);
	XGpio_SetDataDirection(&gpioInstance, 1, 0x0f);
}

/* ------------------------------------------------------------ */
/***	OledDvrInit
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the OLED software system
*/

void OledDvrInit()
{
	int		ib;

	/* Init the parameters for the default font
	*/
	dxcoOledFontCur = cbOledChar;
	dycoOledFontCur = 8;
	pbOledFontCur = (uint8_t*)rgbOledFont0;
	pbOledFontUser = rgbOledFontUser;

	for (ib = 0; ib < cbOledFontUser; ib++) {
		rgbOledFontUser[ib] = 0;
	}

	xchOledMax = ccolOledMax / dxcoOledFontCur;
	ychOledMax = crowOledMax / dycoOledFontCur;

	/* Set the default character cursor position.
	*/
	OledSetCursor(0, 0);

	/* Set the default foreground draw color and fill pattern
	*/
	clrOledCur = 0x01;
	pbOledPatCur = (uint8_t*)rgbFillPat;
	OledSetDrawMode(modOledSet);

	/* Default the character routines to automaticall
	** update the display.
	*/
	fOledCharUpdate = 1;
}

/* ------------------------------------------------------------ */
/***	OledDevInit
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Initialize the OLED display controller and turn the display on.
*/

void OledDevInit()
{
	int gpioReg = 0;
	/* We're going to be sending commands, so clear the Data/Cmd bit
	*/
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);

	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & (RESET_MASK | VBAT_CTRL_MASK));
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	printf("OledDevInit: d/cmd, vdd set to 0, gpioReg: %X", gpioReg);
	usleep(1000);

	/* Display off command
	*/
	Spi2PutByte(cmdOledDisplayOff);

	/* Bring Reset low and then high
	*/

	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( VBAT_CTRL_MASK | VDD_CTRL_MASK | DATA_CMD_MASK));
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	printf("OledDevInit: reset set to 0, gpioReg: %X", gpioReg);
	usleep(1000);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg | RESET_MASK);
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	printf("OledDevInit: reset set to 1, gpioReg: %X", gpioReg);

	/* Send the Set Charge Pump and Set Pre-Charge Period commands
	*/
	Spi2PutByte(0x8D);		//From Univision data sheet, not in SSD1306 data sheet
	Spi2PutByte(0x14);

	Spi2PutByte(0xD9);		//From Univision data sheet, not in SSD1306 data sheet
	Spi2PutByte(0xF1);

	/* Turn on VCC and wait 100ms
	*/
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( RESET_MASK | VDD_CTRL_MASK | DATA_CMD_MASK));
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	printf("OledDevInit: vbat set to 0, gpioReg: %X", gpioReg);
	usleep(100000);

	/* Send the commands to invert the display.
	*/
	Spi2PutByte(cmdOledSegRemap);		//remap columns
	Spi2PutByte(cmdOledComDir);			//remap the rows

	/* Send the commands to select sequential COM configuration
	*/
	Spi2PutByte(cmdOledComConfig);		//set COM configuration command
	Spi2PutByte(0x20);					//sequential COM, left/right remap enabled

	/* Send Display On command
	*/
	Spi2PutByte(cmdOledDisplayOn);
}

/* ------------------------------------------------------------ */
/***	OledDevTerm
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Shut down the OLED display hardware
*/

void OledDevTerm()
{
	int gpioReg = 0;
	/* Send the Display Off command.
	*/
	Spi2PutByte(cmdOledDisplayOff);

	/* Turn off VCC
	*/
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg | VBAT_CTRL_MASK);
	
	usleep(100000);

	/* Turn off VDD
	*/
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( RESET_MASK | VDD_CTRL_MASK | DATA_CMD_MASK));
}

/* ------------------------------------------------------------ */
/***	OledDisplayOn
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Turn the display on. This assumes that the display has
**		already been powered on and initialized. All it does
**		is send the display on command.
*/

void OledDisplayOn()
{
	int gpioReg = 0;
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( RESET_MASK | VDD_CTRL_MASK | VBAT_CTRL_MASK ));
	Spi2PutByte(cmdOledDisplayOn);
}

/* ------------------------------------------------------------ */
/***	OledDisplayOff
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Turn the display off. This does not power the display
**		down. All it does is send the display off command.
*/

void OledDisplayOff()
{
	int gpioReg = 0;
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);
	XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( RESET_MASK | VDD_CTRL_MASK | VBAT_CTRL_MASK ));
	Spi2PutByte(cmdOledDisplayOff);
}

/* ------------------------------------------------------------ */
/***	OledClear
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Clear the display. This clears the memory buffer and then
**		updates the display.
*/

void OledClear()
{
	OledClearBuffer();
	OledUpdate();
}

/* ------------------------------------------------------------ */
/***	OledClearBuffer
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Clear the display memory buffer.
*/

void OledClearBuffer()
{
	int			ib;
	uint8_t 	*pb;

	pb = rgbOledBmp;

	/* Fill the memory buffer with 0.
	*/
	for (ib = 0; ib < cbOledDispMax; ib++) 
	{
		*pb++ = 0x00;
	}
}

/* ------------------------------------------------------------ */
/***	OledUpdate
**
**	Parameters:
**		none
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Update the OLED display with the contents of the memory buffer
*/

void OledUpdate()
{
	int gpioReg = 0;
	int		ipag;
	uint8_t *	pb;

	pb = rgbOledBmp;
	
	gpioReg = XGpio_DiscreteRead(&gpioInstance, 1);

	for (ipag = 0; ipag < cpagOledMax; ipag++) 
	{
		XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg & ( RESET_MASK | VDD_CTRL_MASK | VBAT_CTRL_MASK ));

		/* Set the page address
		*/
		Spi2PutByte(0x22);		//Set page command
		Spi2PutByte(ipag);		//page number

		/* Start at the left column
		*/
		Spi2PutByte(0x00);		//set low nybble of column
		Spi2PutByte(0x10);		//set high nybble of column

		XGpio_DiscreteWrite(&gpioInstance, 1, gpioReg | DATA_CMD_MASK);

		/* Copy this memory page of display data.
		*/
		OledPutBuffer(ccolOledMax, pb);
		pb += ccolOledMax;

	}
}

/* ------------------------------------------------------------ */
/***	OledPutBuffer
**
**	Parameters:
**		cb		- number of bytes to send/receive
**		rgbTx	- pointer to the buffer to send
**
**	Return Value:
**		none
**
**	Errors:
**		none
**
**	Description:
**		Send the bytes specified in rgbTx to the slave and return
**		the bytes read from the slave in rgbRx
*/
void OledPutBuffer(int cb, uint8_t *rgbTx)
{
	int status = 0;
	uint8_t rgbRx[cb]; //dummy read buffer
	
	SpiInstance.SlaveSelectReg = XSpi_GetSlaveSelectReg(&SpiInstance);
	status = XSpi_Transfer(&SpiInstance, rgbTx, rgbRx, cb);
	if (status != XST_SUCCESS)
	{
		printf("OledPutBuffer: ERROR: transfer failed. staus: %d", status);
	}

	/* Write/Read the data
	*/
	/*for (ib = 0; ib < cb; ib++) 
	{
		bTmp = spiCon.transfer(*rgbTx++);
	}*/

}

/* ------------------------------------------------------------ */
/***	Spi2PutByte
**
**	Parameters:
**		bVal		- byte value to write
**
**	Return Value:
**		Returns byte read
**
**	Errors:
**		none
**
**	Description:
**		Write/Read a byte on SPI port 2
*/
uint8_t Spi2PutByte(uint8_t bVal)
{
	int status = 0;
	uint8_t	bRx;

	SpiInstance.SlaveSelectReg = XSpi_GetSlaveSelectReg(&SpiInstance);
	status = XSpi_Transfer(&SpiInstance, &bVal, &bRx, sizeof(uint8_t) );
	if (status != XST_SUCCESS)
	{
		printf("Spi2PutByte: ERROR: transfer failed. staus: %d", status);
	}
	//bRx = spiCon.transfer(bVal);
	
	return bRx;
}

/* ------------------------------------------------------------ */
/***	ProcName
**
**	Parameters:
**
**	Return Value:
**
**	Errors:
**
**	Description:
**
*/

/* ------------------------------------------------------------ */

/************************************************************************/

