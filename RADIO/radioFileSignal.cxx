#include "radioFileSignal.hxx"
#include <iostream>

radioFileSignal::radioFileSignal(string fileName,int bufferSize):
	iq(new iq_data_reader("test_data/FMcapture1.dat",bufferSize)){
}


vector<complex<double>> radioFileSignal::getSignal(){
	
}

bool radioFileSignal::isTunable() {
	return false;
}

radioFileSignal::~radioFileSignal(){
	cout << "bla bla bla";
}
