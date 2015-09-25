#include <iostream>
#include "fourier.hxx"


using namespace std;
fourier::fourier(int nPoints){
	LOG4CPLUS_DEBUG(logger, "Starting constructor...");
	this->nPoints = nPoints;
}
