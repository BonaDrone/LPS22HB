/* 
   LPS22HBB.cpp: Implementation of LPS22HBB class

   Copyright (C) 2018 Simon D. Levy

   Adapted from https://github.com/kriswiner/LPS22HBB_LIS2MDL_LPS22HBB

   This file is part of LPS22HBB.

   LPS22HBB is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   LPS22HBB is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with LPS22HBB.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "LPS22HB.h"

#include <CrossPlatformI2C_Core.h>

LPS22HB::LPS22HB(Rate_t odr)
{
    _odr = odr;
}

bool LPS22HB::checkNewData()
{
    return (bool)readRegister(STATUS);   
}

float LPS22HB::readPressure()
{
    uint8_t rawData[3];  // 24-bit pressure register data stored here
    readRegisters((PRESS_OUT_XL | 0x80), 3, &rawData[0]); // bit 7 must be one to read multiple bytes
    return ((int32_t) ((int32_t) rawData[2] << 16 | (int32_t) rawData[1] << 8 | rawData[0])) / 4096.f;
}

float LPS22HB::readTemperature()
{
    uint8_t rawData[2];  // 16-bit pressure register data stored here
    readRegisters((TEMP_OUT_L | 0x80), 2, &rawData[0]); // bit 7 must be one to read multiple bytes
    return ((int16_t)((int16_t) rawData[1] << 8 | rawData[0])) / 100.f;
}


LPS22HB::Error_t LPS22HB::begin(uint8_t bus)
{
    // Set up cross-platform I^2C support
    _i2c = cpi2c_open(ADDRESS, bus);

    if (readRegister(WHOAMI) != 0xB1) {
        return ERROR_ID;
    }

    // set sample rate by setting bits 6:4 
    // enable low-pass filter by setting bit 3 to one
    // bit 2 == 0 means bandwidth is odr/9, bit 2 == 1 means bandwidth is odr/20
    // make sure data not updated during read by setting block data udate (bit 1) to 1
    writeRegister(CTRL_REG1, _odr << 4 | 0x08 | 0x02);  
    writeRegister(CTRL_REG3, 0x04);  // enable data ready as interrupt source

    return ERROR_NONE;
}

void LPS22HB::clearInterrupt(void)
{
    readPressure();
    readTemperature();
}

uint8_t LPS22HB::readRegister(uint8_t subAddress) {
    uint8_t data;
    readRegisters(subAddress, 1, &data);
    return data;
}

void LPS22HB::writeRegister(uint8_t subAddress, uint8_t data) {
    cpi2c_writeRegister(_i2c, subAddress, data);
}

void LPS22HB::readRegisters(uint8_t subAddress, uint8_t count, uint8_t * dest) {
    cpi2c_readRegisters(_i2c, subAddress, count, dest);
}
