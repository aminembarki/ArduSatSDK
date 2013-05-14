/* 
    AppStorage.cpp - Library to write arduino application data from arduino->supervisor.
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

#include <Wire.h>
#include <nanosat_message.h>
#include "System.h"


/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/
System::System(uint8_t id){
    _set = false;
    _local_address = id;
}

/******************************************************************************
 * User API
 ******************************************************************************/
void System::exit(uint8_t status)
{
    _set = true;
    _exit_status = status;
}

void System::onRequestEvent(){
    if(_set){
        message_t msg;

        //set the message type
        msg.t = EXIT;
        msg.addr = _local_address;

        //set the length and populate the buffer
        nano_exitmsg_t* datamsg = (nano_exitmsg_t*)&msg.data;
        datamsg->exit_status = _exit_status;

        //write it to the wire
        Wire.write((const uint8_t*)&msg, (size_t)sizeof(message_t));
    }
}

