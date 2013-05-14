/* 
    SAT_Control.cpp - Library to write arduino application data from arduino->supervisor.
    Copyright (C) 2013 Jorge Ortiz for NanoSatisfi

   Copyright 2013 NanoSatisfi, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
  
*/

/******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "SAT_Control.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_Control::SAT_Control(uint8_t id){
    _local_address = id;
    _commLayer = OnboardCommLayer::getInstance(MULTIMASTER);
    
}

/******************************************************************************
 * Private functions 
 ******************************************************************************/


/******************************************************************************
 * User API
 ******************************************************************************/
void SAT_Control::changePitch(float degrees){
}

void SAT_Control::changeYaw(float degrees){
}

void SAT_Control::changeRoll(float degrees){
}

