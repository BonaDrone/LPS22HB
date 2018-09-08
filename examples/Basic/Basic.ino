/* 
   Basic.ino: Example sketch for LPS22HB

   Copyright (C) 2018 Simon D. Levy

   Additional dependencies:

       https://github.com/simondlevy/CrossPlatformDataBus

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

#include <LPS22HB.h>

#ifdef __MK20DX256__
#include <i2c_t3.h>
#define NOSTOP I2C_NOSTOP
#else
#include <Wire.h>
#define NOSTOP false
#endif

// params
static const  LPS22HB::Rate_t BRATE = LPS22HB::ODR_50Hz;

// Instantiate LPS22HB class
static LPS22HB lps22hb(BRATE);

void setup()
{
    Serial.begin(115200);

#ifdef __MK20DX256__
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
#else
    Wire.begin();
#endif

    delay(100);

    // Start the LPS22HB
    if (!lps22hb.begin()) {
        while (true)  {
            Serial.println("Unable to connect to LPS22HB");
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

        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" mBar");

        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C\n");
    }
}


