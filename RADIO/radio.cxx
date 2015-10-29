#include "radio.hxx"
#include <iostream>
#include <glog/logging.h>
#include <QThread>

using namespace std;

radio::radio(shared_ptr<radioSignal> signal)
	:signal(signal),mainWindow(new MainWindow()){
	DLOG(INFO) << "created constructor";
	mainWindow->show();
	signalSamplingRate = signal->getSamplingRate();
	signalFrequency = signal->getSignalFrequency();
	oFourier.reset(new fourier(1024));

}

void radio::calculateFrequencyValues(){
	maxTuneOffset = signalSamplingRate * 0.5;
	maxFrequency = signalFrequency + maxTuneOffset;
	minFrequency = signalFrequency - maxTuneOffset;
	currentFrequency = signalFrequency;
	maxSinePhase = 1024;

}

radio::~radio(){
	DLOG(INFO) << "dectructor";

}


void radio::processRadio(){
	vector<complex<double>> signalInput;
	vector<complex<double>> signalSpectrum;
	vector<int> to_display;
	bool quit = false;
	int i = 0;
	while(!quit){
		signal->getSignal(signalInput);

		// tune frequency
		for (auto iter = signalInput.begin();iter!=signalInput.end();++iter)
		{
			(*iter) *= exp(complex<double>(0,-2*M_PI*(double)(178000*sinePhase)/signalFrequency));	

			if (sinePhase<maxSinePhase){
				sinePhase+=1;
			}
			else
			{
				sinePhase = 0;
			}
		}
		i++;
		//if (i>100){
		//	quit = true;
		//}
		oFourier->do_fft(signalInput,signalSpectrum);
		mainWindow->updateSpectrum(signalSpectrum);
		QThread::msleep(30);
	}
}
