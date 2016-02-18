/***************************************************************************//**
 *   @file   AD5933 sketch.
 *   @brief  Demo project for AD5933 using MPIDE Serial Monitor.
 *   @author Dan Nechita
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
#include <AD5933.h>
#include <Wire.h>

//SEL=0 Rfb=100 kohm, Sel=1 Rfb=20 ohm
/******************************************************************************/
/************************ Constants Definitions *******************************/
/******************************************************************************/
/*! List of available commands */
const char* commandsList[] = {"help?",
                              "temperature?",
                              "startFreq=",
                              "incFreq=",
                              "incNum=",
                              "sweepParam?",
                              "calibImpedance=",
                              "impedance?",
                              "currentFreq?",
                              "range=",
                              "pga="};
const char* commandsDescription[] = {
    "  -  Displays all available commands.",
    "  -  Displays the ambient device temperature.",
    "  -  Start frequency parameter. Accepted values: 0 - 500000Hz. ",
    "  -  Frequency increment parameter. Accepted values: 0 - 500000Hz.",
    "  -  Number of increments parameter. Accepted values: 1 - 511.",
    "  -  Displays all four sweep parameters.",
    "  -  Calibration impedance value.Accepted values: 1 - 1000000[Ohm].",
    "  -  Displays the measured impedance.",
    "  -  Displays the current frequency.",
    "  -  Test voltage range parameter.Accepted values:1 - 4",
    "  -  PGA gain.Accepted values:0 for pga=5,1 for pga=1"};

/******************************************************************************/
/************************ Variables Definitions *******************************/
/******************************************************************************/
AD5933 myAD5933;
/*! Variables used for console operations */
char   commandsNumber = (sizeof(commandsList) / sizeof(const char*));
char   receivedCommand[30];
char   invalidCommand = 0;
char   commandType = 0;
char   command = 0;
char   displayCommand = 0;
double commandParam = 0;
/*! Variables holding information about the device */
short  temperature = 0;         /*!< Last temperature read from the device */

double startFreq = 5000;        /*!< Start frequency sweep */
double incFreq = 100;            /*!< Increment frequency */
short  incNum = 10;             /*!< Number of increments */
short  cyclesNum = 25;
//unsigned char range=AD5933_RANGE_2000mVpp; //test Rfb=100 kohm
//unsigned char range=AD5933_RANGE_1000mVpp;
//unsigned char range=AD5933_RANGE_400mVpp;
unsigned char range=AD5933_RANGE_200mVpp;   //test Rfb=20 ohm

unsigned char pga=AD5933_PGA_1;
unsigned char clock=AD5933_CONTROL_INT_SYSCLK;

long   calibImped = 98200;            //Rcalib for Rfb=100 kohm
//long   calibImped = 22;            //Rcalib for Rfb=20 ohm

double gainFactor = 0;          /*!< Stores the value of the gain factor */
double impedance = 0;           /*!< Measured impedance */
double currentFreq = startFreq; /*!< Signal frequency used during a measurement */

//macros definition
#define  Test_Param  range, pga, clock
#define  Sweep_Param  startFreq, incFreq, incNum, cyclesNum  

//! Temporary variables 
char   tempString [10]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned short temp=0;
unsigned char status = 0;
double  doubleTemp=0;
double  MultiplyGain=0;
/***************************************************************************//**
 * @brief Reads one command from UART.
 *
 * @param command - Read command.
 *
 * @return None.
*******************************************************************************/
void CONSOLE_GetCommand(char* command)

{
    unsigned char receivedChar = 0;
    
    unsigned char charNumber = 0;
    
    while(receivedChar != 0x0D)
    
    {
      if (Serial.available() > 0)
      {
        
        receivedChar = Serial.read();
        command[charNumber++] = receivedChar; 
      }
    }
    command[charNumber] = 0;
}

/***************************************************************************//** 
 * @param receivedCommand - Received command.
 * @param expectedCommand - Expected command.
 * @param commandParameter - Command parameter.
 *
 * @return commandType - Type of the command.
 *                       Example: 0 - Commands don't match.
 *                                1 - Write command.
 *                                2 - Read command.
*******************************************************************************/
unsigned char CONSOLE_CheckCommands(char* receivedCommand,
                                    const char* expectedCommand,
                                    double* commandParameter)
{
    unsigned char commandType = 1;
    unsigned char charIndex = 0;

    unsigned char parameterString[10] = {0, 0, 0, 0, 0};
    unsigned char parameterIndex = 0;

    while((expectedCommand[charIndex] != '?') &&
          (expectedCommand[charIndex] != '=') &&
          
          (commandType != 0))
    {
        if(expectedCommand[charIndex] != receivedCommand[charIndex])
        {
            commandType = 0;
        }
        charIndex++;
    }
    if(commandType != 0)
    {
        if(expectedCommand[charIndex] == '=')
        {
            if(receivedCommand[charIndex] == '=')
            {
                charIndex++;
     
                while(receivedCommand[charIndex] != 0x0D)
                {
                    parameterString[parameterIndex] = receivedCommand[charIndex];
                    charIndex++;
                    parameterIndex++;
                    
                }
                *commandParameter = atof((const char*)parameterString);
            }
            else
            {
                commandType = 0;
            }
        }
        if(expectedCommand[charIndex] == '?')
        {
            if(receivedCommand[charIndex] == '?')
            {
                    commandType = 2;
            }
            else
            {
                    commandType = 0;
            }
        }
    }

    return commandType;
}

/***************************************************************************//**
 * @brief Setup function.
 *
 * @return none.
*******************************************************************************/    
void setup()
{
  Serial.begin(9600);
  if(myAD5933.Init())
  {
      Serial.println("AD5933 OK");
  }
  else
  {
      Serial.println("AD5933 Error");
  }
   myAD5933.ConfigSweep(Sweep_Param);
  /*! Start the sweep operation */

  myAD5933.StartSweep(Test_Param);
  temp=myAD5933.GetRegisterValue(AD5933_REG_CONTROL_HB,2);
  Serial.print("AD5933_REG_CONTROL_HB_LB=");
  Serial.println(temp,HEX);
 
  gainFactor = myAD5933.CalculateGainFactor(calibImped,
                                            AD5933_FUNCTION_REPEAT_FREQ);
  MultiplyGain=1000000*gainFactor;                                          
  doubleTemp=1/(gainFactor*calibImped); 
  sprintf(tempString, "%.3f", (double)doubleTemp);
  Serial.print("Mcal=");
  Serial.println(tempString);
  
  sprintf(tempString, "%f", (double)MultiplyGain);
  Serial.print("Multiply Gain (^6)=");
  Serial.println(tempString);
}

/***************************************************************************//**
 * @brief Loop function.
 *
 * @return none.
*******************************************************************************/
void loop()
{
 double currentFreq = startFreq;   //!< Signal frequency used during a measurement 
  
  /*! Configure the sweep parameters */
  myAD5933.ConfigSweep(Sweep_Param);
  /*! Start the sweep operation */
  myAD5933.StartSweep(Test_Param);

  Serial.println("Send a command!!");
  /*! Wait a command from the user. */
  CONSOLE_GetCommand(receivedCommand);
  invalidCommand = 0;
  /*! Check if the received command identifies as one of the command list.  */
  for(command = 0; command < commandsNumber; command++)
  {
      commandType = CONSOLE_CheckCommands(receivedCommand,
                                          commandsList[command],
                                          (double*)&commandParam);
      /*! Count the commands that are invalid. */
      if(commandType == 0)
      {
          invalidCommand++;
      }
      else
      {
        switch(command)
        {
          case 0:                                        /*!< "help?" command */
              Serial.println("Available commands:");
              for(displayCommand = 0; displayCommand < commandsNumber;
                  displayCommand++)
              {
                  Serial.print(commandsList[displayCommand]);
                  Serial.println(commandsDescription[displayCommand]);
              }
              break;
          case 1:
              /*!< "temperature?" command */
              /*! Read the temperature from the device */
              temperature = myAD5933.GetTemperature();
              /*! Send the requested value to user */
              Serial.print("temperature=");
              itoa(temperature, tempString, 10);
              Serial.print(tempString);
              Serial.println(" degrees Celsius");
              break;
          case 2:                                        /*!< "startFreq=" command */
              /*! Validate parameter */
              commandParam = constrain(commandParam, 0, 500000);
              startFreq = commandParam;
              /*! Configure the sweep parameters */
              myAD5933.ConfigSweep(Sweep_Param);
              /*! Start the sweep operation */
              myAD5933.StartSweep(Test_Param);
              /*! Send feedback to user */
              Serial.print(commandsList[command]);
              sprintf(tempString, "%.1f", startFreq);
              Serial.print(tempString);
              Serial.println(" Hz");
              /*! Update the currentFrequency */
              currentFreq = startFreq;
              break;
          case 3:                                        /*!< "incFreq=" command */
              /*! Validate parameter */
              commandParam = constrain(commandParam, 0, 500000);
              incFreq = commandParam;
              /*! Configure the sweep parameters */
              myAD5933.ConfigSweep(Sweep_Param);
              /*! Start the sweep operation */
              myAD5933.StartSweep(Test_Param);
              /*! Send feedback to user */
              Serial.print(commandsList[command]);
              sprintf(tempString, "%.1f", incFreq);
              Serial.print(tempString);
              Serial.println(" Hz");
              break;
          case 4:                                       /*!< "incNum=?" command */
              /*! Validate parameter */
              commandParam = constrain(commandParam, 1, 511);
              incNum = (short)commandParam;
              /*! Configure the sweep parameters */
              myAD5933.ConfigSweep(Sweep_Param);
              /*! Start the sweep operation */
              myAD5933.StartSweep(Test_Param);
              /*! Send feedback to user */
              Serial.print(commandsList[command]);
              sprintf(tempString, "%d", incNum);
              Serial.println(tempString);
              break;
          case 5:                                       /*!< "sweepParam?" command */
              /*! Send the requested value to user */
              Serial.print(commandsList[2]);
              sprintf(tempString, "%.1f", startFreq);
              Serial.print(tempString);
              Serial.println(" Hz");
              Serial.print(commandsList[3]);
              sprintf(tempString, "%.1f", incFreq);
              Serial.print(tempString);
              Serial.println(" Hz");
              Serial.print(commandsList[4]);
              sprintf(tempString, "%d", incNum);
              Serial.println(tempString);
              Serial.print("cyclesNum=");
              sprintf(tempString, "%d", cyclesNum);
              Serial.println(tempString);
              break;
          case 6:                                       /*!< "calibImpedance=" command */
              /*! Validate parameter */
              commandParam = constrain(commandParam, 0, 1000000);
              calibImped = (long)commandParam;
              /*! Calculate the gain factor for the selected impedance */
              gainFactor = myAD5933.CalculateGainFactor(calibImped,
                                                        AD5933_FUNCTION_REPEAT_FREQ);                                                        
              /*! Send feedback to user */
              Serial.print("Gain was calculated for Z=");
              itoa(calibImped, tempString, 10);
              Serial.print(tempString);
              Serial.println(" [Ohm]");
              break;
          case 7:                                       
              //!< "impedance?" command 
              //! Calculates the impedance between the VOUT and VIN pins. 
              
              do{
              status = myAD5933.GetRegisterValue(AD5933_REG_STATUS,1);
              impedance = myAD5933.CalculateImpedance(gainFactor,
                                                      AD5933_FUNCTION_INC_FREQ);
              //! Send the requested value to user 
              sprintf(tempString, "%.3f", (double)impedance / 1000);
              Serial.print("impedance=");
              Serial.print(tempString);
              Serial.print(",");
              
              Serial.print("currentFreq=");
              Serial.print(currentFreq);
              Serial.print(",");
              
             doubleTemp=1/(gainFactor*impedance); 
             sprintf(tempString, "%.3f", (double)doubleTemp);
             Serial.print("Mu=");
             Serial.println(tempString);
              
              //! Update the currentFrequency 
              currentFreq = currentFreq + incFreq;
              }while((status & AD5933_STAT_SWEEP_DONE) == 0);
              
              break;
          case 8:                                       /*!< "currentFreq?" command */
              /*! Send the requested value to user */
              sprintf(tempString, "%.1f", currentFreq);
              Serial.print(tempString);
              Serial.println(" [Hz]");
              break;
          case 9:                                       
              //!< "range=" command */
              Serial.print("range=");
              commandParam = constrain(commandParam, 1, 4);
              if(commandParam==1){
              range=AD5933_RANGE_2000mVpp;
              Serial.println("AD5933_RANGE_2000mVpp");}
              if(commandParam==2){
              range=AD5933_RANGE_1000mVpp;
              Serial.println("AD5933_RANGE_1000mVpp");}
              if(commandParam==3){
              range=AD5933_RANGE_400mVpp;
              Serial.println("AD5933_RANGE_400mVpp");}
              if(commandParam==4){
              range=AD5933_RANGE_200mVpp;
              Serial.println("AD5933_RANGE_200mVpp");}
              /*! Configure the sweep parameters */
              myAD5933.ConfigSweep(Sweep_Param);
              /*! Start the sweep operation */
              myAD5933.StartSweep(Test_Param);
              break; 
              
            case 10:                                       
              //!< "pga=" command */
              Serial.print("pga=");
              commandParam = constrain(commandParam, 0, 1);
              if(commandParam==0){
              pga=AD5933_PGA_5;
              Serial.println("AD5933_PGA_5");}
              if(commandParam==1){
              pga=AD5933_PGA_1;
              Serial.println("AD5933_PGA_1");}
              myAD5933.ConfigSweep(Sweep_Param);
              /*! Start the sweep operation */
              myAD5933.StartSweep(Test_Param);
              break;      
              
                        
         default:
              break;   
        }/*!< End switch */   
    }/*!< End else */
  }/*!< End for */
  if(invalidCommand == commandsNumber)
  {
      /*! Send feedback to user */
       Serial.println("Invalid command");
  }
}
