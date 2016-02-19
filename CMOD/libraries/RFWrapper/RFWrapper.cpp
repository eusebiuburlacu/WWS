//source code for RF-TX device 
#include "RFWrapper.h"
#include "WProgram.h"

	const int pin_reset = 6;      //chipKIT_CMOD J1-08
	const int pin_cs = 24;        //chipKIT_CMOD J1-01
	const int pin_interrupt = 7;  //chipKIT_CMOD J1-07/INT3
	const int source = 0x6001;
	//const int dest = 0x6002; for receiving RF 
	
RFWrapper::RFWrapper(): Mrf24j(pin_reset, pin_cs, pin_interrupt)
{
	reset();
	init(); //here we set also the channel number 12
	set_pan(0x9249) //identical for the RF_TX & RF-RX devices
	
	address16_write(source); // for receiving set argument to "dest"
	Serial.println(adress16_read(source)); //test if write function went OK
	attachInterrupt(3,interrupt_handler, FALLING); // interrupt 3 equivalent to chipKIT_CMOD pin 7(INT3)
	
}

RFWrapper::~RFWrapper()
{
	
}

bool RFWrapper::sendImpedance( float *samples, unsigned char numOfValues )
{
	for(i=0; i < numOfValues ;i++ )
	{
		check_flags(&rx_handler, &tx_handler);
		Serial.println("Sending impedance...");
        send16(dest, samples[i]);
	}
}

bool RFWrapper::sendPhase( float *samples, unsigned char numOfValues )
{
	for(i=0; i < numOfValues ;i++ )
	{
		check_flags(&rx_handler, &tx_handler);
		Serial.println("Sending phase...");
        send16(dest, samples[i]);
	}
}

bool RFWrapper::sendTemperature( float temperature )
{
		check_flags(&rx_handler, &tx_handler);
		Serial.println("Sending temperature...");
        send16(dest, temperature);
	
}

bool RFWrapper::sendHumidity( unsigned char humidity )
{
	check_flags(&rx_handler, &tx_handler);
		Serial.println("Sending temperature...");
        send16(dest, humidity);
}

bool RFWrapper::sendBatteryVoltage( float batteryVoltage )
{
	check_flags(&rx_handler, &tx_handler);
		Serial.println("Sending temperature...");
        send16(dest, batteryVoltage);
}
void RFWrapper::tx_handler(void) 
{
    if (get_txinfo()->tx_ok) 
	{
        Serial.println("TX went ok, got ack");
    } 
	else 
	{
        Serial.print("TX failed after ");Serial.print(get_txinfo()->retries);Serial.println(" retries\n");
    }
}
void RFWrapper::rx_handler() 
{
    //nothing to receive 
}