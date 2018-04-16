/* Version: 1.0.3
 * Copyright (c) 2013 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 * DAC57X4.cpp - Library for the Analog Devices Inc. AD5724/AD5734/AD5754 Quad precision [12/14/16-bit] Digital to Analog Converters.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * modified by Bernd Rilling (brilling@ifsw.uni-stuttgart.de)
 *
 * new:
 * void DAC57X4::ReadDACsRegister(int DACRegister, int DACNumber, byte raw[])
 */

#include "DAC57X4.h"


DAC57X4::DAC57X4(int DACQTY, int dacvolts, int ss_pin){

	// added by Bernd Rilling 12/2013

	sspin = ss_pin;

	if (sspin != SS) {		    //only needed if SS is different

		digitalWrite(sspin,HIGH);   //Put selceted SS high

		pinMode(sspin, OUTPUT);	    //Set pin as output
	}
	// end added...

	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE2);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
	voltage = dacvolts;

	DAC57X4::ConfigDACs(DACQTY); //Must configure before turning the DACs on
	DAC57X4::PowerDACs(DACQTY); //Power up the number of requested DACs

}
void DAC57X4::ConfigDACs(int DACQTY){ //CHECKED OK

	/*

	0x180000 = NOP [for readback operations]
	--------------------------------------------------------
	OR the following together based on the options desired
	0x190000 = CTRL Address
	0x1 = SDO Disable Address
	0x2 = CLR Select Address
	0x4 = Clamp Enable Address
	0x8 = TSD Enable Address
	---------------------------------------------------------
	0x1C0000 = Clear Data Address
	---------------------------------------------------------
	0x1D0000 = Load Data Address
	---------------------------------------------------------

	*/
	unsigned long config = 0x190000 | 0x1 | 0x4; //config = CTRL address | SDO Disable | Clamp Enable
	DAC57X4::SendData(config);

	unsigned long output;

	switch(DACQTY){

		case 4:

			/*
			---------------------------------------------------------
			Output scale values. Must have overhead supply in order to accomodate
			0xB0000 = 5V
			0xB0001 = 10V
			0xB0002 = 10.8V
			0xB0003 = +-5V
			0xB0004 = +-10V
			0xB0005 = +-10.8V
			---------------------------------------------------------

			*/
			switch(voltage){

				case 1: //0-5V

					output = 0xB0000;

				break;

				case 2: //0-10V

					output = 0xB0001;

				break;

				case 3: //0-10.8V

					output = 0xB0002;

				break;

				case 4: //+-5V

					output = 0xB0003;

				break;

				case 5: // +-10V

					output = 0xB0004;

				break;

				case 6: //+-10.8V

					output = 0xB0005;

				break;
			}

			DAC57X4::SendData(output);

		case 3:

       			// fixed typo by Bernd Rilling 12/2013
			// 0x50000 should be 0xA0000
			/*
			---------------------------------------------------------
			Output scale values. Must have overhead supply in order to accomodate
			0xA0000 = 5V
			0xA0001 = 10V
			0xA0002 = 10.8V
			0xA0003 = +-5V
			0xA0004 = +-10V
			0xA0005 = +-10.8V
			---------------------------------------------------------

			*/
			switch(voltage){

				case 1: //0-5V

					output = 0xA0000;

				break;

				case 2: //0-10V

					output = 0xA0001;

				break;

				case 3: //0-10.8V

					output = 0xA0002;

				break;

				case 4: //+-5V

					output = 0xA0003;

				break;

				case 5: //+-10V

					output = 0xA0004;

				break;

				case 6: //+-10.8V

					output = 0xA0005;

				break;
			}

			DAC57X4::SendData(output);

		case 2:

			/*
			---------------------------------------------------------
			Output scale values. Must have overhead supply in order to accomodate
			0x90000 = 5V
			0x90001 = 10V
			0x90002 = 10.8V
			0x90003 = +-5V
			0x90004 = +-10V
			0x90005 = +-10.8V
			---------------------------------------------------------

			*/
			switch(voltage){

				case 1: //0-5V

					output = 0x90000;

				break;

				case 2: //0-10V

					output = 0x90001;

				break;

				case 3: //0-10.8V

					output = 0x90002;

				break;

				case 4: //+-5V

					output = 0x90003;

				break;

				case 5: //+-10V

					output = 0x90004;

				break;

				case 6: //+-10.8V

					output = 0x90005;

				break;
			}

			DAC57X4::SendData(output);

		case 1:

			/*
			---------------------------------------------------------
			Output scale values. Must have overhead supply in order to accomodate
			0x80000 = 5V
			0x80001 = 10V
			0x80002 = 10.8V
			0x80003 = +-5V
			0x80004 = +-10V
			0x80005 = +-10.8V
			---------------------------------------------------------

			*/

			switch(voltage){

				case 1: //0-5V

					output = 0x80000;

				break;

				case 2: //0-10V

					output = 0x80001;

				break;

				case 3: //0-10.8V

					output = 0x80002;

				break;

				case 4: //+-5V

					output = 0x80003;

				break;

				case 5: //+-10V

					output = 0x80004;

				break;

				case 6: //+-10.8V

					output = 0x80005;

				break;
			}

			DAC57X4::SendData(output);

		break;

	}

}
void DAC57X4::PowerDACs(int DACQTY){ //CHECKED OK

	switch(DACQTY){

		case 1:

			DAC57X4::SendData(0x100001); //Send B000100000000000000000001 to initialize only the first DAC

		break;

		case 2:

			DAC57X4::SendData(0x100003); //Send B000100000000000000000011 to initialize 2 DACs

		break;

		case 3:

			DAC57X4::SendData(0x100007); //Send B000100000000000000000111 to initialize 3 DACs

		break;

		case 4:

			DAC57X4::SendData(0x10000F); //Send B000100000000000000001111 to initialize  DACs

		break;
	}
}
void DAC57X4::SetDAC(float DACVoltage, int DACNumber){ //CHECKED OK

	unsigned long DACAddress;
	unsigned long data; //data is the voltage requested from the user application
	unsigned int DACValue;

	/*
	-------------------------------------------------------------------
	The DACValue needs to be calculated from the voltage input by the
	user i.e.

	+4x2.5x(1/65536) = B0000 0000 0000 0000 0000 0001 = 0.000152587890625V
	+4x2.5x(65535/65536) = 9.999847412109375V

	Therefore:

	DACValue = (voltage / 10) * 65536
	-------------------------------------------------------------------
	*/

	switch(voltage){

		case 1: //0-5V

			DACVoltage = constrain(DACVoltage,0.0,4.999923706054688);
			DACValue = (DACVoltage/5) * 65536;

		break;

		case 2: //0-10V

			DACVoltage = constrain(DACVoltage,0.0,9.999847412109375);
			DACValue = (DACVoltage/10) * 65536;

		break;

		case 3: //0-10.8V

			DACVoltage = constrain(DACVoltage,0.0,9.999847412109375);
			DACValue = (DACVoltage/10.8) * 65536;

		break;

		case 4: //+-5V

			DACVoltage = constrain(DACVoltage,-4.999847412109375,4.999847412109375);
			DACValue = (DACVoltage/5) * 32768;

		break;

		case 5: //+-10V

			DACVoltage = constrain(DACVoltage,-9.99969482421875,9.99969482421875);
			DACValue = (DACVoltage/10) * 32768;

		break;

		case 6: //+-10.8

			DACVoltage = constrain(DACVoltage,-10.79967041015625,10.79967041015625);
			DACValue = (DACVoltage/10.8) * 32768;

		break;

	}

	switch(DACNumber){

		case 1:

			DACAddress = 0x00000;
			data = DACAddress | DACValue;

		break;

		case 2:

			DACAddress = 0x10000;
			data = DACAddress | DACValue;

		break;

		case 3:

			DACAddress = 0x20000;
			data = DACAddress | DACValue;

		break;

		case 4:

			DACAddress = 0x30000;
			data = DACAddress | DACValue;

		break;

		case 5:
			//all dacs
			DACAddress = 0x40000;
			data = DACAddress | DACValue;

		break;
	}

	DAC57X4::SendData(data);

	DAC57X4::LoadDACs();

}
void DAC57X4::LoadDACs(){ //CHECKED OK

	unsigned long data = 0x1D0000;

	DAC57X4::SendData(data);
}
void DAC57X4::ClearDACs(){ //CHECKED OK

	unsigned long data = 0x1C0000;

	DAC57X4::SendData(data);

}

// added by Bernd Rilling 12/2013
void DAC57X4::ReadDACsRegister(int DACRegister, int DACNumber, byte raw[]){

	unsigned long DACAddress;
	unsigned long data;
	unsigned long DACValue;

	/*
	-------------------------------------------------------------------
	DACRegister
	1 = DAC register
	2 = Output range select register
	3 = Power control register
	4 = Control register
	-------------------------------------------------------------------
	*/

	switch(DACNumber){

		case 1: //DAC A

			DACAddress = 0x00000;

		break;

		case 2: //DAC B

			DACAddress = 0x10000;

		break;

		case 3: //DAC C

			DACAddress = 0x20000;

		break;

		case 4: //DAC D

			DACAddress = 0x30000;

		break;
	}

	switch(DACRegister){

		case 1:	//DAC register

			DACValue = 0x800000;
			data = DACValue | DACAddress;

		break;

		case 2:	//Output range select register

			DACValue = 0x880000;
			data = DACValue | DACAddress;

		break;

		case 3:	//Power control register
				//DACNumber don't care

			data = 0x900000;

		break;

		case 4:	//Control register
				//DACNumber don't care

			data = 0x990000;

		break;

	}
	//Send read command for the selected register and DACNumber

	DAC57X4::SendData(data);

	digitalWrite(sspin, LOW);

	//Send B0001 8000 0000 0000 0000 0000 = NOP
	//Read 3 bytes

	for (int i=2; i>= 0; i--){

			raw[i] = SPI.transfer(0x180000);

	}

	digitalWrite(sspin, HIGH);

}
// end added...

void DAC57X4::SendData(long data){ //CHECKED OK

	digitalWrite(sspin,LOW);

	unsigned char *p = (unsigned char*)&data;

	for (int i=2; i>= 0; i--){ //MSB first

		SPI.transfer (p[i]);

	}

	digitalWrite(sspin,HIGH);

}
