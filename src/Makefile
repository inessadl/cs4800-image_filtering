all: ppm

ppm: driver.o ppm.o
	g++ driver.o ppm.p -o ppm

driver.o: Driver.cpp
	g++ -c Driver.cpp

ppm.o: PPM.cpp
	g++ -c PPM.cpp

clean:
	rm -rf *o ppm