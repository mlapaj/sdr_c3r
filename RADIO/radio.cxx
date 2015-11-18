#include "radio.hxx"
#include <iostream>
#include <fstream>
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
	oFFT.reset(new fft(1024));
	shiftFrequency = 178000;
	calculateShiftSine();
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

void radio::calculateShiftSine(){
	shiftSine.clear();
	for (int i=0;i< (signalSamplingRate / shiftFrequency) * 20; i++ ){
			shiftSine.push_back(exp(complex<double>(0,-2*M_PI*(double)(shiftFrequency)*double(i)/signalSamplingRate)));	
	}

}

void radio::processRadio(){
	benchmark_timer t;
	vector<complex<double>> signalDecimated;
	vector<complex<double>> signalSpectrum;
	vector<complex<double>> signalAfterDecimation;

	vector<double> demodulatedSignal;


	signalSpectrum.reserve(1024);
	bool quit = false;


	vector<double> beforeDecimation;
	beforeDecimation.reserve(10240);

	vector<double> rd;
	vector<double> id;
	id.resize(1024);
	rd.resize(1024);
	vector<double> brd;
	vector<double> bid;
	brd.resize(1024);
	bid.resize(1024);

	vector<double> bid_overlap;
	vector<double> brd_overlap;

	vector<double> fmSignal;
	decimate::segment_decimate<complex<double>> oDecimate(8);
	decimate::segment_decimate<double> oDemodulatedDecimate(10);
	
	vector<double> b;		
	//csv::read("test_data/firls.txt",b);
	b.push_back(1);
	b.push_back(0);
	b.push_back(-1);

	int sinePhase =0;
	
	vector<double> demodulated;
	vector<double> afterFMdecimate;
	vector<complex<double>> signalInput;

	signalInput.reserve(8192);
	signalDecimated.reserve(1024);
	signalAfterDecimation.reserve(1024);

	while(!quit)
	{
	//	cout << "************" << endl;
		t.reset();
	//	t.print();

		while (signalDecimated.size() < 1024){
		// t.print();
			signalInput.clear();
			signal->getSignal(signalInput);
			if (signalInput.size() == 0) break;
	//	t.print();
			for (int i = 0;i < signalInput.size() ; ++i)
			{
				signalInput[i] *= (shiftSine[sinePhase++]);
			    if (sinePhase>=shiftSine.size()) sinePhase = 0;
			}
			
	//	t.print();
			oDecimate.decimate(signalInput,signalAfterDecimation);
			signalDecimated.insert(signalDecimated.end(),signalAfterDecimation.begin(),signalAfterDecimation.end());
		}
		// t.print();
	//	cout << " after decimation" << endl;
		long beforFMsize = signalDecimated.size();



		for (int i=0;i<signalDecimated.size();++i){
			complex<double> val = signalDecimated[i] / abs(signalDecimated[i]);
			rd[i] = val.real();
			id[i] = val.imag();
		}
		signalDecimated.clear();

		convolution::do_segment_conv_same(bid_overlap,id,b,bid);
		convolution::do_segment_conv_same(brd_overlap,rd,b,brd);
		
		demodulated.resize(beforFMsize);
		for (int i=0;i<bid.size();i++){
			demodulated[i] = ( (id[i] * brd[i]) - (rd[i] * bid[i]) ) / ((rd[i] * rd[i]) + (id[i] * id[i]));
		}

		//t.print();
		beforeDecimation.insert(beforeDecimation.end(),demodulated.begin(),demodulated.end());
		//t.print();
		if (beforeDecimation.size() >= 10240){
			afterFMdecimate.clear();
			oDemodulatedDecimate.decimate(beforeDecimation,afterFMdecimate);
			beforeDecimation.clear();


			ofstream data_file;      // pay attention here! ofstream
			data_file.open("data.bin", ios::in | ios::out | ios::binary);
			data_file.seekp(0, ios::end); 

			size_t size = afterFMdecimate.size();

			for (int i = 0; i < size; ++i)
			{
				data_file.write(reinterpret_cast<char*>(&afterFMdecimate[i]), sizeof(double));
			}

			data_file.close();
			//cout << "decimated size" << afterFMdecimate.size() << endl;

			oFFT->do_fft(afterFMdecimate,signalSpectrum);
			mainWindow->updateSpectrum(signalSpectrum);
			signalSpectrum.clear();
		}
		
		signalAfterDecimation.clear();
		// t.print();
		// return;
		
	}

		
}
