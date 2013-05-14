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


#ifndef ACCEL_H
#define ACCEL_H

#include <inttypes.h>

#include <nanosat_message.h>
//#include <OnboardCommLayer.h>
#include "FIMU_ADXL345_ocl.h"
//#include "FIMU_ADXL345.h"


class SAT_Accel
{
    private:
        uint8_t _local_address;         //local address of this node
        OnboardCommLayer* _commLayer;
        float _xyz_buff[3];

        ADXL345 acc;

    public:
        SAT_Accel();
        void init(uint8_t id);
        void set();
        float getAccelX();
        float getAccelY();
        float getAccelZ();
};

#endif
