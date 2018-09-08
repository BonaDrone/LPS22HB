/* 
   LPS22HB.h: Header file for LPS22HB class

   Copyright (C) 2018 Simon D. Levy

   Adapted from https://github.com/kriswiner/LPS22HB_LIS2MDL_LPS22HB

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

#pragma once

#include <stdint.h>
#include <stdbool.h>

// One ifdef needed to support delay() cross-platform
#if defined(ARDUINO)
#include <Arduino.h>

#elif defined(__arm__) 
#if defined(STM32F303)  || defined(STM32F405xx)
extern "C" { void delay(uint32_t msec); }
#else
#include <wiringPi.h>
#endif

#else
void delay(uint32_t msec);
#endif

class LPS22HB {

    public: 

        // Altimeter output data rate
        typedef enum {

            ODR_1shot, 
            ODR_1Hz, 
            ODR_10Hz, 
            ODR_25Hz, 
            ODR_50Hz, 
            ODR_75Hz 

        } Rate_t;

        LPS22HB(Rate_t rate);

        bool begin(uint8_t bus=1);

        bool checkNewData(void);

        float readPressure(void);

        float readTemperature(void);

    private:

        // Register map
        // http://www.st.com/content/ccc/resource/technical/document/datasheet/bf/c1/4f/23/61/17/44/8a/DM00140895.pdf/files/DM00140895.pdf/jcr:content/translations/en.DM00140895.pdf
        static const uint8_t INTERRUPT_CFG = 0x0B;
        static const uint8_t THS_P_L       = 0x0C;
        static const uint8_t THS_P_H       = 0x0D;
        static const uint8_t WHO_AM_I      = 0x0F;
        static const uint8_t CTRL_REG1     = 0x10;
        static const uint8_t CTRL_REG2     = 0x11;
        static const uint8_t CTRL_REG3     = 0x12;
        static const uint8_t FIFO_CTRL     = 0x14;
        static const uint8_t REF_P_XL      = 0x15;
        static const uint8_t REF_P_L       = 0x16;
        static const uint8_t REF_P_H       = 0x17;
        static const uint8_t RPDS_L        = 0x18;
        static const uint8_t RPDS_H        = 0x19;
        static const uint8_t RES_CONF      = 0x1A;
        static const uint8_t INT_SOURCE    = 0x25;
        static const uint8_t FIFO_STATUS   = 0x26;
        static const uint8_t STATUS        = 0x27;
        static const uint8_t PRESS_OUT_XL  = 0x28;
        static const uint8_t PRESS_OUT_L   = 0x29;
        static const uint8_t PRESS_OUT_H   = 0x2A;
        static const uint8_t TEMP_OUT_L    = 0x2B;
        static const uint8_t TEMP_OUT_H    = 0x2C;
        static const uint8_t LPFP_RES      = 0x33;

        static const uint8_t ADDRESS = 0x5C;
        static const uint8_t ID      = 0xB1;

        Rate_t _rate;

        uint8_t _i2c; // cross-platform support

        uint8_t readRegister(uint8_t subAddress);
        void    readRegisters(uint8_t subAddress, uint8_t count, uint8_t * dest);
        void    writeRegister(uint8_t subAddress, uint8_t data);
};
