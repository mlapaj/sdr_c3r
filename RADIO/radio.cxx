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
	vector<double> filter_10Khz = filter::fir_lowpass(40,signalSamplingRate,10000);
	vector<complex<double>> signalInput;
	vector<complex<double>> signalInputAfterConvolution;
	vector<complex<double>> signalInputAfterDecimation;
	vector<complex<double>> signalSpectrum;
	vector<int> to_display;
	bool quit = false;
	int i = 0;
	while(!quit){
		signalInputAfterDecimation.clear();
		signalInputAfterDecimation.reserve(1024);
		while(signalInputAfterDecimation.size()<1024)
		{

			signal->getSignal(signalInput);
			convolution::do_conv(signalInput,filter_10Khz,signalInputAfterConvolution);
			int step = 10;
			for (int i=0;i<signalInputAfterConvolution.size();i+=step){
				signalInputAfterDecimation.push_back(signalInputAfterConvolution[i]);
			}

		}
		// tune frequency
		
		for (auto iter = signalInputAfterDecimation.begin();iter!=signalInputAfterDecimation.end();++iter)
		{
			(*iter) *= exp(complex<double>(0,-2*M_PI*(double)(178000*sinePhase)/signalSamplingRate));	
			sinePhase+=1;
/*
			if (sinePhase<maxSinePhase){
				sinePhase+=1;
			}
			else
			{
				sinePhase = 0;
			}
*/
		}
		i++;
		//if (i>100){
		//	quit = true;
		//}
		oFourier->do_fft(signalInputAfterDecimation,signalSpectrum);
		mainWindow->updateSpectrum(signalSpectrum);
		QThread::msleep(30);
	}
}
