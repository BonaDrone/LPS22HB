/* 
   Interrupt.ino: LPS22HB interrupt-driven example

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

#include <Wire.h>

#include "LPS22HB.h"

static const uint8_t LED_PIN = 38;

// LPS22H definitions
static const int8_t INTERRUPT_PIN = A5;

/* Specify sensor parameters (sample rate is twice the bandwidth) 
   Choices are P_1Hz, P_10Hz P_25 Hz, P_50Hz, and P_75Hz
 */
static LPS22HB::Rate_t ODR = LPS22HB::P_25Hz;     

static LPS22HB lps22hb = LPS22HB(ODR);

static bool gotNewData;

static void interruptHandler()
{
    gotNewData = true;
}

static void error(const char * msg)
{
    while (true) {
        Serial.print("Error: ");
        Serial.println(msg);
    }
}
void setup() 
{
    Serial.begin(115200);

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // start with led off

    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(INTERRUPT_PIN, interruptHandler, RISING);  

    Wire.begin(TWI_PINS_20_21); // set master mode 
    Wire.setClock(400000); // I2C frequency at 400 kHz  
    delay(100);

    switch (lps22hb.begin()) {

        case LPS22HB::ERROR_CONNECT:
            error("no connection");
            break;

        case LPS22HB::ERROR_ID:
            error("bad ID");
            break;

        default:
            break;

    }

    // Read from sensor to enable interrupts
    lps22hb.readPressure();
    lps22hb.readTemperature();

}

void loop() 
{
    if (gotNewData) {

        gotNewData = false;

        float pressure = lps22hb.readPressure();
        float temperature = lps22hb.readTemperature();

        Serial.print("Temperature = ");
        Serial.print(temperature, 2);
        Serial.println(" C");
        Serial.print("Pressure = ");
        Serial.print(pressure, 2);  
        Serial.println(" mbar\n");
    }
}
