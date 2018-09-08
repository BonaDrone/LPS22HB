# 
# Makefile for LPS22HB WiringPi example
#
# Copyright (c) 2018 Simon D. Levy
#
# This file is part of LPS22HB.
#
# LPS22HB is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LPS22HB is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with LPS22HB.  If not, see <http://www.gnu.org/licenses/>.

  
# Change this to whereever you installed CrossPlatformDataBus
CPDB = $(HOME)/CrossPlatformDataBus

ALL = Basic

LPS22HBSRC = ../../src

I2CINC = $(CPDB)/src
I2CSRC = $(CPDB)/extras/i2c/wiringpi/src

all: $(ALL)

Basic: Basic.o LPS22HB.o WiringPiI2C.o main.o
	g++ -std=c++11 -o Basic Basic.o LPS22HB.o WiringPiI2C.o main.o -lwiringPi

Basic.o: Basic.cpp 
	g++ -std=c++11 -Wall -I$(I2CINC) -I$(LPS22HBSRC) -c Basic.cpp

LPS22HB.o:  $(LPS22HBSRC)/LPS22HB.cpp  $(LPS22HBSRC)/LPS22HB.h
	g++ -std=c++11 -Wall -I$(I2CINC) -I$(LPS22HBSRC) -c $(LPS22HBSRC)/LPS22HB.cpp

WiringPiI2C.o: $(I2CSRC)/WiringPiI2C.cpp 
	g++ -std=c++11 -Wall -I$(I2CINC) -c $(I2CSRC)/WiringPiI2C.cpp

main.o: ../main.cpp 
	g++ -std=c++11 -Wall -c ../main.cpp

run: Basic
	./Basic

edit:
	vim Basic.cpp

clean:
	rm -f $(ALL) *.o *~
