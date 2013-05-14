/* 
    AppStorage.h - Library that signals, to the supervisor, the end of
    an experimental instance.

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

#ifndef DSTORE_H
#define DSTORE_H

#include <inttypes.h>
#include <stdlib.h>
#include <Arduino.h>
#include <OnboardCommLayer.h>

class System
{
    private:
        uint8_t _local_address;
        OnboardCommLayer* _ocl;
        byte _buff[NODE_COMM_MAX_I2C_BUFFER_SIZE];
    public:
        System(uint8_t nodeid);
        void exit();
};

#endif
