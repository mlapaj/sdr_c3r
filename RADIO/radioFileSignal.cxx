#include "radioFileSignal.hxx"
#include <iostream>

#include <glog/logging.h>



radioFileSignal::radioFileSignal(string fileName,int bufferSize):
	iq(new iq_data_reader(fileName,bufferSize)){
		DLOG(INFO) << "created object";
}


int radioFileSignal::getSignal(vector<complex<double>> &out){
	return iq->read_data(out);
}

bool radioFileSignal::isTunable() {
	return false;
}

radioFileSignal::~radioFileSignal(){
	DLOG(INFO) << "dectructor";
}
	
long radioFileSignal::getSamplingRate(){	
	// temporary hardcoded
	return 2500000;
}

long radioFileSignal::getSignalFrequency(){
	// temporary hardcoded
	return 100122000;
}
