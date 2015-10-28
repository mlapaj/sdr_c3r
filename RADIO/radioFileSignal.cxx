#include "radioFileSignal.hxx"
#include <iostream>

#include <glog/logging.h>



radioFileSignal::radioFileSignal(string fileName,int bufferSize):
	iq(new iq_data_reader("test_data/FMcapture1.dat",bufferSize)){
		DLOG(INFO) << "created object";
}


void radioFileSignal::getSignal(vector<complex<double>> &out){
	iq->read_data(out);
}

bool radioFileSignal::isTunable() {
	return false;
}

radioFileSignal::~radioFileSignal(){
}
