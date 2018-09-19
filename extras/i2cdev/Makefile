# 
# Makefile for LPS22HB I2CDEV example
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

CPSRC  = $(CPDB)/src
CPEXT  = $(CPDB)/extras
CPCMN  = $(CPEXT)/common
I2CSRC = $(CPEXT)/i2c/i2cdev/src

ALL = Basic

LPS22HBSRC = ../../src

all: $(ALL)

Basic: Basic.o LPS22HB.o I2CDevI2C.o main.o timing.o
	g++ -std=c++11 -o Basic Basic.o LPS22HB.o I2CDevI2C.o main.o timing.o

Basic.o: Basic.cpp 
	g++ -std=c++11 -Wall -I$(CPCMN) -I$(CPSRC) -I$(LPS22HBSRC) -c Basic.cpp

LPS22HB.o:  $(LPS22HBSRC)/LPS22HB.cpp  $(LPS22HBSRC)/LPS22HB.h
	g++ -std=c++11 -Wall -I$(CPSRC) -I$(LPS22HBSRC) -c $(LPS22HBSRC)/LPS22HB.cpp

I2CDevI2C.o: $(I2CSRC)/I2CDevI2C.cpp 
	g++ -std=c++11 -Wall -I$(CPSRC) -c $(I2CSRC)/I2CDevI2C.cpp

main.o: $(CPCMN)/main.cpp 
	g++ -std=c++11 -Wall -c $(CPCMN)/main.cpp

timing.o: $(CPCMN)/timing.cpp 
	g++ -std=c++11 -Wall -I$(CPCMN) -c $(CPCMN)/timing.cpp


run: Basic
	./Basic

edit:
	vim Basic.cpp

clean:
	rm -f $(ALL) *.o *~
