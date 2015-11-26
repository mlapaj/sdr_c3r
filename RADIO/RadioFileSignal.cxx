#include "RadioFileSignal.hxx"
#include <iostream>

#include <glog/logging.h>



RadioFileSignal::RadioFileSignal(string fileName,int bufferSize):
	currentFileName(fileName),
	currentBlockSize(bufferSize),
	iq(new IqDataReader(fileName,bufferSize,true)){
		DLOG(INFO) << "created object";
	timer = 0;
}


int RadioFileSignal::getSignal(vector<complex<double>> &out){
	if (throttle){
		if (dataSent > sampleRate) dataSent = 0;
		int tmpToSent = 0;
		if (timer == 0){
			timer =  clock();
			return 0;
		}
		else
		{
			double val = abs((clock()-timer)/double(CLOCKS_PER_SEC));

			if (val < 1){
				tmpToSent = sampleRate * val;
				dataToSend = abs(tmpToSent - dataSent); 
				dataSent = tmpToSent;
			}
			else
			{
				if (dataSent < sampleRate){
					dataToSend = abs(sampleRate - dataSent);
				}
				// clear and starts from begining
				dataSent = 0;
				timer = clock();
			}
		}
		if (dataToSend){
			return iq->readData(out,dataToSend);
		}
		else
		{
			return 0;
		}
	}
	else
	{
	return iq->readData(out);
	}
}
bool RadioFileSignal::isTunable() {
	return false;
}

RadioFileSignal::~RadioFileSignal(){
	DLOG(INFO) << "dectructor";
}
	
long RadioFileSignal::getSamplingRate(){	
	// temporary hardcoded
	return 2500000;
}

long RadioFileSignal::getSignalFrequency(){
	// temporary hardcoded
	return 100122000;
}

void RadioFileSignal::setThrottle(long sampleRate){
	timer = 0;
	throttle = true;
	iq.reset(new IqDataReader(currentFileName,sampleRate,true));
	this->sampleRate = sampleRate;
	this->dataToSend = sampleRate;
}

