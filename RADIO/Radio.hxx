#include <memory>
#include <iostream>


#include "RadioSignal.hxx"
#include "WFMdecoder.hxx"

#include "../GUI/mainwindow.h"
#include "../DSP/fft.hxx"
#include "../DSP/filter.hxx"
#include "../DSP/convolution.hxx"



#include <QtCore>
class Radio: public QThread
{
	public:
		Radio (shared_ptr<RadioSignal> signal);
		virtual ~Radio ();
		list<vector<float>> audioBuffer;
	private:
		void run(){
			processRadio();
		}
		void test(long jeden, long dwa){
			shiftFrequency = jeden - signalFrequency;
			qDebug() << "!!shift" << shiftFrequency << endl;
		calculateFrequencyValues();
		calculateShiftSine();
		}
		void processRadio();
		long signalSamplingRate = 0; // Radio sampling rate
		long signalFrequency = 0;
		long maxTuneOffset = 0;
		long maxFrequency = 0;
		long minFrequency = 0;
		void calculateFrequencyValues();
		long currentFrequency = 0;
		long sinePhase = 0;
		long maxSinePhase = 0;
		long shiftFrequency = 0;

		// Radio object
		shared_ptr<RadioSignal> signal;
		shared_ptr<MainWindow> mainWindow;
		shared_ptr<fft> oFFT;
		shared_ptr<WFMdecoder<double>> oWFMdecoder;
		vector<complex<double>> shiftSine;
		// list<vector<double>> audioBuffer;
		
		void calculateShiftSine();
		
		// misc functions
		void saveRawDataToFile(string filename,vector<double> data);

		
		
};
