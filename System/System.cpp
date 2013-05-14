/* 
    AppStorage.cpp - Library to write arduino application data from arduino->supervisor.
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

