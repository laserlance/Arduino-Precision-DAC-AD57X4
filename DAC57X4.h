/* Version: 2.0.0b
 * Copyright (c) 2019 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 * DAC57X4.h - Library for the Analog Devices Inc. AD5724/AD5734/AD5754 Quad precision [12/14/16-bit] Digital to Analog Converters.
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

#ifndef DAC57X4_h
#define DAC57X4_h

#include "Arduino.h"
#include <SPI.h>
#include "pins_arduino.h"

class DAC57X4{

		public:

			DAC57X4(int DACQTY, int dacvolts, int ss_pin, int ChipNumber);
			void SetDAC(float DACVoltage, int DACNumber, int ChipNumber);
			void LoadDACs(int ChipNumber);
			void ClearDACs(int ChipNumber);
			void ConfigDACs(int DACQTY, int ChipNumber);
			void PowerDACs(int DACQTY, int ChipNumber);
			void ReadDACsRegister(int DACRegister, int DACNumber, byte raw[], int ChipNumber);
			void SendData(long data, int ChipNumber);
			int voltage;
			int sspin;

		private:
			int DACQTY;

};

#endif
