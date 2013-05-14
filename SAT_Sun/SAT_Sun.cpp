/* 
    SAT_Sun.cpp - Library to write arduino application data from arduino->supervisor.
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
#include "SAT_Sun.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
extern float SAT_Sun::_val=-1.0;
extern boolean SAT_Sun::_valFetchDone = true;


/******************************************************************************
 * Constructors
 ******************************************************************************/
/*
 * Sun constructor.
 * 
 * @param id the unique if (1-16) of this node
 *
 */
SAT_Sun::SAT_Sun(uint8_t id){

    _local_address = id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);

    //time fetch flag
    SAT_Sun::_valFetchDone = true;

    //register the internal response handler from the supervisor
    //triggered when the time value has been received upon request
    _commLayer->onReceive(_onSunValueFetchDone, (byte*)&_val, 
            (uint8_t)sizeof(float), ADD_SUPERVISOR_SUN);
}


/******************************************************************************
 * Private functions 
 ******************************************************************************/
void SAT_Sun::_onSunValueFetchDone(size_t valSize, boolean isDone){
    SAT_Sun::_valFetchDone = true;
}


/******************************************************************************
 * User API
 ******************************************************************************/
/**
 * Gets the current time on satellite in milliseconds since Jan 1,1970.
 */
float SAT_Sun::getValue(uint8_t sun_id){
    int cycleTime = 100; //ms

    //populate the nanosat_message_t and camera-msg payload
    memset(&msg, 0, sizeof(nanosat_message_t));
    msg.prefix = NODE_COMM_MESSAGE_PREFIX;
    msg.type = SUN;
    msg.node_addr = _local_address;
    uint8_t* data_id_buf = (uint8_t*)&msg.data;
    data_id_buf[0] = sun_id;

    //send it
    SAT_Sun::_valFetchDone = false;
    _commLayer->send(&msg, ADD_SUPERVISOR_SUN);

    //wait until you hear something back
    while(!SAT_Sun::_valFetchDone){
        //Serial.println("w");
        delay(cycleTime);
    }
    Serial.println("broke out!");
    Serial.println((float)_val);
    
    return _val;
}
