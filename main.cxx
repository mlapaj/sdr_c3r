// #define NDEBUG
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <memory>

#include <qapplication.h>
#include <qlabel.h>
#include <QTimer>

#include "DSP/filter.hxx"
#include "DSP/fourier.hxx"

#include "IO/CSV.hxx"
#include "IO/IqDataReader.hxx"
#include "IO/AudioOutput.hxx"

#include "RADIO/RadioFileSignal.cxx"
#include "RADIO/Radio.hxx"

#include "GUI/QSpectrum.hxx"
#include "GUI/mainwindow.h"

#include <glog/logging.h>



using namespace std;

int main(int argc,char **argv){
//	vector<double> filter_coeff = filter::fir_lowpass(21,1/(double)16);
//	csv::save("filtr",filter_coeff,filter_coeff.size());

	

	QApplication app(argc, argv);
	google::InitGoogleLogging(argv[0]);
	int nPoints;
	LOG(INFO) << "Starting app..";

	shared_ptr<RadioFileSignal> signal(new RadioFileSignal("test_data/FMcapture2.dat",8192));
	signal->setThrottle(2500000);
	unique_ptr<Radio> radio(new Radio(signal));
	// unique_ptr<AudioOutput> audioOutput(new AudioOutput());
	//audioOutput->init();
    radio->start();	
	return app.exec();

	DLOG(INFO) << "Ending app..";
}
