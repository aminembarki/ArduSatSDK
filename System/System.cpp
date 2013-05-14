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
    _local_address = id;
    _ocl = new OnboardCommLayer(MULTIMASTER, _local_address);
}

/******************************************************************************
 * User API
 ******************************************************************************/

void System::exit()
{
    memset(_buff, 0, NODE_COMM_MAX_I2C_BUFFER_SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_buff[0];
    msg->prefix = NODE_COMM_MESSAGE_PREFIX;
    msg->type = EXIT;
    msg->node_addr = _local_address;
    _ocl->send(msg);
}

