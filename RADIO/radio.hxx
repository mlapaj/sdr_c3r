#include <memory>
#include "../DSP/fourier.hxx"
#include "radioSignal.hxx"
#include "../GUI/mainwindow.h"
#include <QtCore>
#include <iostream>
class radio: public QThread
{
	public:
		radio (shared_ptr<radioSignal> signal);
		virtual ~radio ();
	private:
		void run(){
			processRadio();
		}
		void processRadio();
		long signalSamplingRate = 0; // radio sampling rate
		long signalFrequency = 0;
		long maxTuneOffset = 0;
		long maxFrequency = 0;
		long minFrequency = 0;
		void calculateFrequencyValues();
		long currentFrequency = 0;
		long sinePhase = 0;
		long maxSinePhase = 0;

		// radio object
		shared_ptr<radioSignal> signal;
		shared_ptr<MainWindow> mainWindow;
		shared_ptr<fourier> oFourier;
		
		
};
