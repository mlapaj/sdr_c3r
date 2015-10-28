#include "radioFileSignal.hxx"
#include <iostream>

#include <glog/logging.h>

radioFileSignal::radioFileSignal(string fileName,int bufferSize):
	iq(new iq_data_reader("test_data/FMcapture1.dat",bufferSize)){
		DLOG(INFO) << "created object";
}


vector<complex<double>> radioFileSignal::getSignal(){
	
}

bool radioFileSignal::isTunable() {
	return false;
}

radioFileSignal::~radioFileSignal(){
}
