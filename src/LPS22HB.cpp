/* 
   LPS22HB.h: Header file for LPS22HB class

   Copyright (C) 2018 Simon D. Levy

   Adapted from https://github.com/kriswiner/LPS22HB_LPS22HB_LPS22HB

   This file is part of LPS22HB.

   LPS22HB is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   LPS22HB is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LPS22HB.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "LPS22HB.h"

#include <CrossPlatformI2C_Core.h>

LPS22HB::LPS22HB(Rate_t rate)
{
    _rate = rate;
}

bool LPS22HB::begin(void)
{
    _i2c = cpi2c_open(ADDRESS);

    if (_i2c <= 0) {
        return false;
    }

    delay(100);

    if (readRegister(WHO_AM_I) != ID) {
        return false;
    }

    delay(100); 

    // set sample rate by setting bits 6:4 
    // enable low-pass filter by setting bit 3 to one
    // bit 2 == 0 means bandwidth is odr/9, bit 2 == 1 means bandwidth is odr/20
    // make sure data not updated during read by setting block data udate (bit 1) to 1
    writeRegister(CTRL_REG1, _rate << 4 | 0x08 | 0x02);  
    writeRegister(CTRL_REG3, 0x04);  // enable data ready as interrupt source

    return true;
}

bool LPS22HB::checkNewData(void)
{
    return (bool)readRegister(STATUS);   
}

float LPS22HB::readPressure(void)
{
    uint8_t data[3];  // 24-bit pressure register data stored here
    readRegisters((PRESS_OUT_XL | 0x80), 3, data); // bit 7 must be one to read multiple bytes
    return ((int32_t) data[2] << 16 | (int32_t) data[1] << 8 | data[0]) / 4096.0f;
}

float LPS22HB::readTemperature(void)
{
    uint8_t data[2];  // 16-bit pressure register data stored here
    readRegisters((TEMP_OUT_L | 0x80), 2, data); // bit 7 must be one to read multiple bytes
    return ((int16_t) data[1] << 8 | data[0]) / 100.f;
}

uint8_t LPS22HB::readRegister(uint8_t subAddress)
{
    uint8_t data=0;
    readRegisters(subAddress, 1, &data);
    return data;
}

void LPS22HB::readRegisters(uint8_t subAddress, uint8_t count, uint8_t * dest)
{
    cpi2c_readRegisters(_i2c, subAddress, count, dest);
}

void LPS22HB::writeRegister(uint8_t subAddress, uint8_t data)
{
    cpi2c_writeRegister(_i2c, subAddress, data);
}
