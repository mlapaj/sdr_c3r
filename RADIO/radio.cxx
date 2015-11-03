#include "radio.hxx"
#include <iostream>
#include <glog/logging.h>
#include <QThread>
#include "../DSP/decimate.hxx"
#include "../IO/csv.hxx"
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
	vector<complex<double>> signalDecimated;
	vector<complex<double>> signalSpectrum;
	vector<complex<double>> signalAfterDecimation;
	signalSpectrum.reserve(1024);
	signalAfterDecimation.reserve(1024);
	bool quit = false;
	while(!quit)
	{
		vector<complex<double>> signalInput;
		decimate::segment_decimate<complex<double>> oDecimate(8);
		signalDecimated.reserve(1024);
/*
		for (int i=0;i<500;i++){
			signal->getSignal(signalInput);
		}
*/
		while (signalDecimated.size() < 1024){
			signalInput.clear();
			signal->getSignal(signalInput);
			signalInput.resize(1024);
			bool pusty = true;

			for (auto iter = signalInput.begin();iter!=signalInput.end();++iter)
			{
				(*iter) *= exp(complex<double>(0,-2*M_PI*(double)(178000*sinePhase)/signalSamplingRate));	
				sinePhase+=1; // todo:  add max phase value
			}
			
			oDecimate.decimate(signalInput,signalAfterDecimation);
			signalDecimated.insert(signalDecimated.end(),signalAfterDecimation.begin(),signalAfterDecimation.end());
		}
		vector<double> demodulatedSignal;
		for (complex<double> sample: signalDecimated)
		{
			vector<double> b;
			csv::read("test_data/firls.txt",b);
			complex<double> d = sample / abs(sample);
			double rd = d.real();
			double id = d.imag();
			//double demodulated = (rd)
		}
		oFourier->do_fft(signalDecimated,signalSpectrum);
		
		mainWindow->updateSpectrum(signalSpectrum);
		signalDecimated.clear();
		signalSpectrum.clear();
		signalAfterDecimation.clear();
		QThread::msleep(30);
	}

		
}
