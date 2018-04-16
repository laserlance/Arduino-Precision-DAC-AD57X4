/* Version: 1.0.2
 * Copyright (c) 2013 by Laser-Lance Fordham <Lance.Fordham@gmail.com>
 * DAC57X4.ino - Library for the Analog Devices Inc. AD5724/AD5734/AD5754 Quad precision [12/14/16-bit] Digital to Analog Converters.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */
#include <SPI.h> //MUST include the SPI library or this won't work.
#include <DAC57X4.h> //MUST include this library or this will not work.

DAC57X4 DAC(2,1,SS); ///Setup the DACs as DAC(NumberOfDACSYouAreUsing,VoltageSelection, TheSSPinOnYourShield);

/*
     Because in this example I'm only using two DACs, I initialize the DAC object with 2 and select the desired
     voltage range.
     
     Voltage selections are:
     
          1 = 0-5V
          2 = 0-10V
          3 = 0-10.8V
          4 = -5-5V
          5 = -10-10V
          6 = -10.8-10.8V
          
           ******************************IMPORTANT NOTE******************************************
          
          You need to make provisions on your shield for the LDAC pin and the CLR pin. You can tie the LDAC pin to permanant low if you
          wish for the DAC outputs to be updated as soon as their values are received, or you can tie the LDAC pin to a digital output on
          the Arduino. This library assumes that this pin is tied low permanantly and, as such, does not have provisions for it. For the CLR pin, 
          you will need to tie it to a pullup resistor if you never wish to clear the DAC outputs via hardware. You could also tie this to a digital 
          output on the Arduino if you wished to control this through hardware. Please see the data sheet for the actual pin numbers of the DAC chip 
          you are using.
*/
char com1data[] = {
     '\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}; // Receive up to 16 bytes;
void setup(){
  //Does my hair look okay?
  Serial.begin(9600);
}

boolean setit = false;

void loop(){

  if(!setit){
    
     /*
     
          When you want to set the voltage of the dac, simply do so as: DAC.SetDAC(Voltage,DACNumber). Where voltage is within the range you have selected during the DAC setup
          and DACNumber is one of four channels.
          Note: A DACNumber of 5 will set all dac values to the value you have entered.
          
     */
      DAC.SetDAC(3.72,1);
      //DAC.LoadDACs();  //Updates the DAC registers and, consequently, the DAC outputs. 
      //DAC.ClearDACs();  //Sets the DAC registers to the clear code and updates the outputs.
      setit = true;
      
  }
      
}

void serialEvent() {

     if(Serial.available() > 0) {

         if(Serial.readBytesUntil('\n', com1data, 16)){
               
               float val = atof(com1data);
               
               DAC.SetDAC(val,1);
               
               for (int i=0;i<16;i++){

                    com1data[i] = '\0'; 
               }
          }
     }
}
