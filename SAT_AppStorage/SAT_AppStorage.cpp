/* 
    SAT_AppStorage.cpp - Library to write arduino application data from arduino->supervisor.
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
#include <I2C_add.h>
#include "SAT_AppStorage.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/


/******************************************************************************
 * Constructors
 ******************************************************************************/
SAT_AppStorage::SAT_AppStorage(uint8_t id){
    _local_address = id;
    commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);
}


/******************************************************************************
 * Private functions 
 ******************************************************************************/


/******************************************************************************
 * User API
 ******************************************************************************/
/*
   Passes the experiment data to the comm layer; the comm layer enqueues if for sending
   upon request from master;
*/
void SAT_AppStorage::store_exp_data(SAT_ExperimentData* edata){
    if(edata!=NULL){
        exp_data_t* data = edata->get_exp_data();
        message_t msg;
        msg.t = APPEND;
        msg.node_addr = _local_address;
        nano_datamsg_t* datamsg = (nano_datamsg_t*)&msg.data;
        datamsg->len = sizeof(exp_data_t);
        memcpy(datamsg->buf, data, sizeof(exp_data_t));
        commLayer->send(&msg, I2C_ADD_SUPERVISOR);
    }
}

/*
   Passes the experiment data to the comm layer; the comm layer enqueues if for sending
   upon request from master;  The data comes in raw form.
*/
void SAT_AppStorage::store_exp_data(const uint8_t* buf, size_t len){
    if(buf!=NULL){
        message_t msg;
        msg.t = APPEND;
        msg.node_addr = _local_address;
        nano_datamsg_t* datamsg = (nano_datamsg_t*)&msg.data;
        datamsg->len = len;
        memcpy(datamsg->buf, buf, len);
        commLayer->send(&msg, I2C_ADD_SUPERVISOR);
    }
}
