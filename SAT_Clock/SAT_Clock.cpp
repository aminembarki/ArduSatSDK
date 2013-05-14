/* 
    SAT_Clock.cpp - Library to write arduino application data from arduino->supervisor.
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
#include "SAT_Clock.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
boolean SAT_Clock::_timeFetchDone = true;
uint8_t SAT_Clock::_local_address;
OnboardCommLayer* SAT_Clock::_commLayer=NULL;
float SAT_Clock::_time=0.0;
byte SAT_Clock::_send_buffer[SIZE];

/******************************************************************************
 * Constructors
 ******************************************************************************/
/*
 * Clock constructor.
 * 
 * @param id the unique if (1-16) of this node
 *
 */
SAT_Clock::SAT_Clock(){}


/******************************************************************************
 * Private functions 
 ******************************************************************************/
void SAT_Clock::_onTimeFetchDone(size_t timeSize, boolean isDone){
    _timeFetchDone = true;
}


/******************************************************************************
 * User API
 ******************************************************************************/
void SAT_Clock::init(uint8_t id){
    _local_address = id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);

    //time fetch flag
    _timeFetchDone = true;

    //register the internal response handler from the supervisor
    //triggered when the time value has been received upon request
    _commLayer->onReceive(_onTimeFetchDone, (byte*)&_time, 
            (size_t)sizeof(float), ADD_SUPERVISOR_CLOCK);
}

/**
 * Gets the current time on satellite in milliseconds since Jan 1,1970.
 */
float SAT_Clock::getTime(){
    int waitCycles = 0;
    int cycleTime = 20; //ms

    //populate the message_t and camera-msg payload
    memset(&_send_buffer, 0, SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_send_buffer[0];
    msg->prefix = NODE_COMM_MAX_BUFFER_SIZE;
    msg->type = CLOCK;
    msg->node_addr = _local_address;

    _timeFetchDone = false;
    //send it
    _commLayer->send(msg, ADD_SUPERVISOR_CLOCK);

    //wait until you hear something back
    while(!_timeFetchDone){
        delay(cycleTime);
        waitCycles+=1;
    }

    //adjust the time to be closer to the current time
    _time += ((waitCycles*cycleTime)-(cycleTime/2));
    return _time;
}

SAT_Clock Clock = SAT_Clock();
