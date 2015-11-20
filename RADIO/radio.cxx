#include "radio.hxx"
#include <iostream>
#include <fstream>
#include <glog/logging.h>
#include <QThread>
#include "../DSP/decimate.hxx"
#include "../IO/csv.hxx"
using namespace std;

radio::radio(shared_ptr<radioSignal> signal)
	:signal(signal),mainWindow(new MainWindow()),oWFMdecoder(new WFMdecoder<double>(10240)),
	oFFT(new fft(1024)){
	DLOG(INFO) << "created constructor";
	mainWindow->show();
	signalSamplingRate = signal->getSamplingRate();
	signalFrequency = signal->getSignalFrequency();
	// shiftFrequency = 178000;
    shiftFrequency = 978000;
	calculateShiftSine();
}

void radio::calculateFrequencyValues(){
	maxTuneOffset = signalSamplingRate * 0.5;
	maxFrequency = signalFrequency + maxTuneOffset;
	minFrequency = signalFrequency - maxTuneOffset;
	cout << "Sig freq " << signalFrequency << endl;
	cout << "Max freq " << maxFrequency << endl;
	cout << "Min freq " << minFrequency << endl;
	cout << "Max offset " << maxTuneOffset << endl;
	mainWindow->setMinMaxFrequency(minFrequency,maxFrequency);
	currentFrequency = signalFrequency + shiftFrequency;
	cout << "Cur freq " << currentFrequency << endl;
	mainWindow->setSelectedFrequency(currentFrequency,300000);
	maxSinePhase = 1024;

}

radio::~radio(){
	DLOG(INFO) << "dectructor";

}

void radio::calculateShiftSine(){
	shiftSine.clear();
	// TODO: get size of sine
	for (int i=0;i< (signalSamplingRate) ; i++ ){
			shiftSine.push_back(exp(complex<double>(0,-2*M_PI*(double)(shiftFrequency)*double(i)/signalSamplingRate)));	
	}

}


void radio::processRadio(){
	calculateFrequencyValues();

	benchmark_timer t;
	bool quit = false;
	
	int downSampleFactor = 8;
	decimate::segment_decimate<complex<double>> oDecimate(downSampleFactor);
	vector<complex<double>> signalDecimated;
	vector<complex<double>> signalSpectrum;
	vector<complex<double>> signalAfterDecimation;
	vector<double> demodulatedSignal;

	int sinePhase =0;

	vector<double> audio;
	vector<complex<double>> signalInput;
	
	signalInput.reserve(1024 * downSampleFactor);
	signalAfterDecimation.reserve(1024);
	signalDecimated.reserve(10240);
	signalSpectrum.reserve(1024);

	t.reset();
	while(!quit)
	{
		
		while (signalDecimated.size() < 10240){
			signalInput.clear();
			signal->getSignal(signalInput);
			if (signalInput.size() == 0) {
				quit = true;
				break;
			}	
		
	

			//do frequency shift
			for (int i = 0;i < (int) signalInput.size() ; ++i)
			{
				signalInput[i] *= (shiftSine[sinePhase++]);
				if (sinePhase >= (int) shiftSine.size()) sinePhase = 0;
			}

		
		
			oDecimate.decimate(signalInput,signalAfterDecimation);
			signalDecimated.insert(signalDecimated.end(),signalAfterDecimation.begin(),signalAfterDecimation.end());
			signalAfterDecimation.clear();
		}

		oWFMdecoder->decode(signalDecimated,audio);
		
		oFFT->do_fft(audio,signalSpectrum);
		mainWindow->updateSpectrum(signalSpectrum);

		saveRawDataToFile("data.bin",audio);
		signalDecimated.clear();
		signalSpectrum.clear();

	}
	t.print();
	cout << "end of radio processing" << endl;


}

void radio::saveRawDataToFile(string filename,vector<double> data){
			ofstream data_file;      // pay attention here! ofstream
			data_file.open(filename, ios::in | ios::out | ios::binary);
			data_file.seekp(0, ios::end); 

			size_t size = data.size();

			for (int i = 0; i < size; ++i)
			{
				data_file.write(reinterpret_cast<char*>(&data[i]), sizeof(double));
			}

			data_file.close();
}


