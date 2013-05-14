/* 
    SAT_Accel.cpp - Library to write arduino application data from arduino->supervisor.
    Copyright (C) 2013 Jorge Ortiz for NanoSatisfi

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
  
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "SAT_Accel.h"
#include "I2C_add.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_Accel::SAT_Accel(){}

/******************************************************************************
 * Private functions 
 ******************************************************************************/
void SAT_Accel::init(uint8_t id){
    Serial.println("accel.init()");
    _local_address = id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);
    acc.init(I2C_ADD_ACC,_commLayer);
    //acc.init(I2C_ADD_ACC);
    _xyz_buff[0]=0;
    _xyz_buff[1]=0;
    _xyz_buff[2]=0;
    Serial.println("done");
}

void SAT_Accel::set(){
    Serial.println("setting accel");
    acc.get_Gxyz(_xyz_buff);
}

/******************************************************************************
 * User API
 ******************************************************************************/
float SAT_Accel::getAccelX(){
    return _xyz_buff[0];
}

float SAT_Accel::getAccelY(){
    return _xyz_buff[1];
}

float SAT_Accel::getAccelZ(){
    return _xyz_buff[2];
}


