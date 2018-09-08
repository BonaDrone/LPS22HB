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

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// params
static const  LPS22HB::Rate_t MRATE = LPS22HB::ODR_50Hz;

// Instantiate LPS22HB class
static LPS22HB lps22hb(MRATE);

void setup()
{
    // Set up the wiringPi library
    if (wiringPiSetup () < 0) {
        fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
        exit(1);
    }

    delay(100);

    if (!lps22hb.begin()) {
        while (true) {
            printf("Unable to connect to LPS22HB");
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
        printf("Temperature: %f C\n\n", temperature);
    }
}


