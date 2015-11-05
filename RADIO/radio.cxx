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
	vector<double> bid_overlap;
	vector<double> brd_overlap;

	vector<double> beforeDecimation;
	vector<double> fmSignal;
	decimate::segment_decimate<complex<double>> oDecimate(8);
	decimate::segment_decimate<double> oDemodulatedDecimate(10);
	
	vector<double> b;		
	csv::read("test_data/firls.txt",b);

	while(!quit)
	{
		vector<complex<double>> signalInput;
		signalDecimated.reserve(1024);
/*
		for (int i=0;i<500;i++){
			signal->getSignal(signalInput);
		}
*/
		while (signalDecimated.size() < 1024){
			signalInput.clear();
			signal->getSignal(signalInput);
			// signalInput.resize(1024);
			bool pusty = true;

			for (auto iter = signalInput.begin();iter!=signalInput.end();++iter)
			{
				(*iter) *= exp(complex<double>(0,-2*M_PI*(double)(178000)*double(sinePhase)/signalSamplingRate));	
				sinePhase+=1; // todo:  add max phase value
			}
			
			oDecimate.decimate(signalInput,signalAfterDecimation);
			signalDecimated.insert(signalDecimated.end(),signalAfterDecimation.begin(),signalAfterDecimation.end());
		}

//		csv::save("shifted",signalDecimated,16250);
//		cout << "done" << endl;

//		return;



		vector<double> demodulatedSignal;
		vector<double> rd;
		rd.resize(signalDecimated.size());
		vector<double> id;
		id.resize(signalDecimated.size());

		cout << "signal decimated" << signalDecimated.size() << endl;
		for (int i=0;i<signalDecimated.size();++i){
			complex<double> val = signalDecimated[i] / abs(signalDecimated[i]);
			rd[i] = val.real();
			id[i] = val.imag();
		}



		vector<double> bid_tmp;
		vector<double> bid;
		convolution::do_segment_conv(bid_overlap,id,b,bid_tmp);
		int toDel = abs((bid_tmp.size() + bid_overlap.size()) - id.size());
		cout << "to del:" << toDel << endl;
		//return;
		bid.insert(bid.end(),bid_tmp.begin(),bid_tmp.end());
		bid.insert(bid.end(),bid_overlap.begin(),bid_overlap.end());
	    bid.erase(bid.begin(),bid.begin()+(toDel/2)+1);
		bid.erase(bid.end()-(toDel/2),bid.end());
		vector<double> down;
		down.resize(bid.size());
		vector<double> demodulated;

		demodulated.resize(bid.size());
		
		vector<double> brd;
		vector<double> brd_tmp;
		convolution::do_segment_conv(brd_overlap,rd,b,brd_tmp);
		toDel = (brd_tmp.size() + brd_overlap.size()) - rd.size();
		brd.insert(brd.end(),brd_tmp.begin(),brd_tmp.end());
		brd.insert(brd.end(),brd_overlap.begin(),brd_overlap.end());
	    brd.erase(brd.begin(),brd.begin()+(toDel/2)+1);
		brd.erase(brd.end()-(toDel/2),brd.end());

		for (int i=0;i<bid.size();i++){
			brd[i] = id[i] * brd[i];

			bid[i] = rd[i] * bid[i];

			down[i] = (rd[i] * rd[i]) + (id[i] * id[i]);
			demodulated[i] = (bid[i] - brd[i]) / down[i];
		}

		beforeDecimation.insert(beforeDecimation.end(),demodulated.begin(),demodulated.end());
		if (beforeDecimation.size() > 10240){
	    vector<double> dataForDecimation;
		dataForDecimation.insert(dataForDecimation.end(),beforeDecimation.begin(),beforeDecimation.begin() + 10240);
		beforeDecimation.erase(beforeDecimation.begin(),beforeDecimation.begin() + 10240);

		
		vector<double> afterFMdecimate;
		oDemodulatedDecimate.decimate(dataForDecimation,afterFMdecimate);

		ofstream data_file;      // pay attention here! ofstream
		data_file.open("data.bin", ios::in | ios::out | ios::binary);
		data_file.seekp(0, ios::end); 

		size_t size = afterFMdecimate.size();

		for (int i = 0; i < size; ++i)
		{
				data_file.write(reinterpret_cast<char*>(&afterFMdecimate[i]), sizeof(double));
		}

		data_file.close();

		cout << "decimated size" << afterFMdecimate.size() << endl;
		oFourier->do_fft(afterFMdecimate,signalSpectrum);
		mainWindow->updateSpectrum(signalSpectrum);
		}
		signalDecimated.clear();
		signalSpectrum.clear();
		signalAfterDecimation.clear();
		
	}

		
}
