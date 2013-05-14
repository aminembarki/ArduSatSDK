/* 
    SAT_InfraTherm.cpp - Library for Arduino returns data on temperature from MLX90614 sensor
    Copyright (C) 2012  Lara Booth for NanoSatisfi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
////////////////////////////////////////////////////////////////////////////////    
          Notes:
          Designed for use with Melexis (C) MLX90614 Infrared Thermometer
   
          Library gathers temperature data over I2C Bus/SM Bus
   
          Tested with MLX90614 from Sparkfun, 4.7k Ohm pull-up resistors, .1uF capacitor, and Arduino Uno
////////////////////////////////////////////////////////////////////////////////   
   
*/

#include <I2C_add.h>
#include "SAT_InfraTherm.h"

//constructor
SAT_InfraTherm::SAT_InfraTherm(){
   //sets common values
   factor = 0.02; // MLX90614 has a resolution of .02
   tempData = 0x0000; //zero out the data
   
   }

void SAT_InfraTherm::init(uint8_t node_id){
    _local_address = node_id;
    _ocl = new OnboardCommLayer(MULTIMASTER, _local_address);
}
   
//modifies tempData into temperature in Kelvin
void SAT_InfraTherm::rawTemperature(unsigned char r)
{
     int data_low, data_high, pec;
     
     _ocl->send((uint8_t*)&r, 1, I2C_ADD_MLX);//sends register address to read

     _ocl->requestFrom(I2C_ADD_MLX, 3, _buff, 3); //request three bytes from device

     data_low = _buff[0];   //read first byte
     data_high = _buff[1];  //read second byte
     pec = _buff[2];        //read checksum 

     // This masks off the error bit of the high byte, then moves it left 8 bits and adds the low byte.
     // Taken from bildr forum on MLX90614
     tempData =(double)(((data_high & 0x007F) << 8) + data_low);
     tempData = (tempData * factor)-0.01; //multiply by resolution and account for error to convert to Kelvin
}

//returns temperature in degrees Celsius
float SAT_InfraTherm::getTemp()
{
      rawTemperature(0x07); //modify tempData
      return (float) tempData - 273.15; //convert from Kelvin to Celsius
}
    
     
     
