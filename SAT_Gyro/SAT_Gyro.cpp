/* 
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
#include <FIMU_ITG3200_ocl.h>

#include "SAT_Gyro.h"
/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_Gyro::SAT_Gyro(){
}



/******************************************************************************
 * Private functions 
 ******************************************************************************/


/******************************************************************************
 * User API
 ******************************************************************************/

void SAT_Gyro::init(uint8_t id){
    _local_address = id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, id);
    _gyroX=0.0;
    _gyroY=0.0;
    _gyroZ=0.0;

   gyro = ITG3200(); 

   //initialize the gyro
   gyro.init(I2C_ADD_GYR, _commLayer);
   delay(1000);
   gyro.zeroCalibrate(128,5);
}

void SAT_Gyro::set(){
   gyro.readGyro(&_gyroX, &_gyroY, &_gyroZ);
}

float SAT_Gyro::getPitch(){
    return _gyroY;
}

float SAT_Gyro::getYaw(){
    return _gyroZ;
}

float SAT_Gyro::getRoll(){
    return _gyroX;
}

