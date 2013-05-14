/* 
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

#ifndef GYRO_H
#define GYRO_H

#include <inttypes.h>
#include <nanosat_message.h>
#include "FIMU_ITG3200_ocl.h"

class SAT_Gyro
{
    private:
        uint8_t _local_address;         //local address of this node
        OnboardCommLayer* _commLayer;
        float _gyroX;
        float _gyroY;
        float _gyroZ;

        ITG3200 gyro;

    public:
        SAT_Gyro();
        float getPitch();
        float getYaw();
        float getRoll();
        void set();
        void init(uint8_t id);

};

#endif
