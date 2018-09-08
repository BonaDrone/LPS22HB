/* 
   Basic.cpp: LPS22HB basic example

   Copyright (C) 2018 Simon D. Levy

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// in timing.cpp
uint32_t millis(void);

// params
static const  LPS22HB::Rate_t BRATE = LPS22HB::ODR_50Hz;

// Instantiate LPS22HB class
static LPS22HB lps22hb(BRATE);

void setup()
{
    if (!lps22hb.begin(0)) {
        while (true) {
            printf("Unable to connect to LPS22HB\n");
        }
    }
}

void loop()
{  
    static float pressure, temperature;

    // Read from LPS22HB
    if (lps22hb.checkNewData()) {
        pressure = lps22hb.readPressure();
        temperature = lps22hb.readTemperature();
    }

    // Report at 2 Hz
    static uint32_t msec_prev;
    uint32_t msec_curr = millis();

    if (msec_curr-msec_prev > 500) {

        msec_prev = msec_curr;

        printf("Pressure: %f mBar\n", pressure);
        printf("Temperature: %f C\n", temperature);
    }
}


