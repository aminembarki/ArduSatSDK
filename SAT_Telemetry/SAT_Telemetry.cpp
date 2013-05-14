/* 
    SAT_Telemetry.cpp - Library to write arduino application data from arduino->supervisor.
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
#include "SAT_Telemetry.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
extern boolean SAT_Telemetry::_valFetchDone = true;

/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_Telemetry::SAT_Telemetry(uint8_t id){
    _local_address = id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);

    _valFetchDone = true;

    _commLayer->onReceive(_onTelemetryFetchDone, _buff, sizeof(uint32_t)*2,
            ADD_SUPERVISOR_TELEMETRY);
    
}

/******************************************************************************
 * Private functions 
 ******************************************************************************/
void SAT_Telemetry::_onTelemetryFetchDone(size_t bytesRxd, boolean done){
    _valFetchDone = true;
}


/******************************************************************************
 * User API
 ******************************************************************************/
void SAT_Telemetry::set(){

    int cycleTime = 100;

    memset(_send_buffer, 0, SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_send_buffer[0];
    msg->prefix=NODE_COMM_MESSAGE_PREFIX;
    msg->type = TELEMETRY;
    msg->node_addr = _local_address;
    msg->len = 0;

    _valFetchDone = false;
    _commLayer->send(msg, (uint8_t)ADD_SUPERVISOR_TELEMETRY);

    while(!SAT_Telemetry::_valFetchDone)
        delay(cycleTime);
    _5V_current = _buff[0];
    _3_3V_current = _buff[1];

}

uint32_t SAT_Telemetry::get3_3V_Current(){
    return _3_3V_current;
}

uint32_t SAT_Telemetry::get5V_Current(){
    return _5V_current;
}


