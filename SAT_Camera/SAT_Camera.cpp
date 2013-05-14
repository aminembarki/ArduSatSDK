/* 
    SAT_Camera.cpp - Library to write arduino application data from arduino->supervisor.
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
#include "SAT_Camera.h"
#include "Arduino.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

uint8_t SAT_Camera::_local_address=0;
OnboardCommLayer* SAT_Camera::_commLayer=NULL;
byte SAT_Camera::_send_buffer[SIZE];
char SAT_Camera::_picpath[MAX_PATHLEN];
void (*SAT_Camera::_user_function)(size_t);

/******************************************************************************
 * Private functions 
 ******************************************************************************/
void SAT_Camera::_onPictureDone(size_t pathlen, boolean isDone){
    if(_user_function!=NULL)
        _user_function(pathlen);
}

/******************************************************************************
 * Constructors
 ******************************************************************************/
/*
 * Camera constructor.
 * 
 * @param id the unique if (1-16) of this node
 *
 */
SAT_Camera::SAT_Camera(){
}

//register the sensor (power related)
void SAT_Camera::_registerCam(){
    memset(&_send_buffer[0], 0, SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_send_buffer[0];
    msg->prefix = NODE_COMM_MESSAGE_PREFIX;
    msg->type = SENSOR_REG;
    msg->node_addr = _local_address;
    msg->len = 1;
    uint8_t* _data = (uint8_t*)&msg->data;
    _data[0] = ADD_SUPERVISOR_CAM;

    _commLayer->send(msg, (uint8_t)ADD_SUPERVISOR_CAM);
}


/******************************************************************************
 * User API
 ******************************************************************************/

void SAT_Camera::on(uint8_t node_id){
    _local_address = node_id;
    _commLayer = new OnboardCommLayer(MULTIMASTER, _local_address);

    //register the internal response handler from the supervisor
    //triggered when the picture has been taken and stored.
    memset(&_picpath[0], 0, MAX_PATHLEN);
    _user_function=NULL;

    _commLayer->onReceive(_onPictureDone, (byte*)&_picpath[0], 
            (uint8_t)MAX_PATHLEN, ADD_SUPERVISOR_CAM);
    _registerCam();
}

/*
 * Set the given parameters on the camera and takes a picture.
 * 
 * @param compressionRatio the compression ratio
 * @param pictureSize the size of the picture in bytes
 * @param radians 
 * @param latitude
 * @param longitude 
 *
 */
void SAT_Camera::takePicture(byte compressionRatio, 
        unsigned int pictureSize, float radians, float latitude,
        float longitude)
{
    //populate the nanosat_message_t and camera-msg payload
    memset(_send_buffer, 0, SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_send_buffer[0];
    msg->prefix = NODE_COMM_MESSAGE_PREFIX;
    msg->type = CAM;
    msg->node_addr = _local_address;
    nanosat_cammsg_t* cam_msg_t = (nanosat_cammsg_t*)&msg->data;
    cam_msg_t->default_=0;
    cam_msg_t->compressionRatio = compressionRatio;
    cam_msg_t->pictureSize = (uint32_t) pictureSize;
    cam_msg_t->radians = radians;
    cam_msg_t->latitude = latitude;
    cam_msg_t->longitude = longitude;

    //send it
    _commLayer->send(msg, ADD_SUPERVISOR_CAM);
}

/*
 * Takes a picture with the default settings.
 * 
 */
void SAT_Camera::takePictureSimple(){
    //populate the nanosat_message_t and camera-msg payload
    memset(_send_buffer, 0, SIZE);
    nanosat_message_t* msg = (nanosat_message_t*)&_send_buffer[0];
    msg->prefix = NODE_COMM_MESSAGE_PREFIX;
    msg->type = CAM;
    msg->node_addr = _local_address;
    nanosat_cammsg_t* cam_msg_t = (nanosat_cammsg_t*)&msg->data;
    cam_msg_t->default_=1; //keep all default settings

    //send it
    _commLayer->send(msg, ADD_SUPERVISOR_CAM);
}

/*
 * Callback registrant that registers your callback to be triggered 
 * when you invoke either method to take a picture.  The value pointed
 * to by the parameter of the function will be a buffer with the path
 * where the picture was stored.
 * 
 */
void SAT_Camera::onPictureTaken(void (*function)(size_t)){
    if(function!=NULL){
        _user_function = function;}
}

SAT_Camera Camera = SAT_Camera();
