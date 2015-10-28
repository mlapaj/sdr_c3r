// #define NDEBUG
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <memory>

#include <qapplication.h>
#include <qlabel.h>
#include <QTimer>

#include "DSP/fourier.hxx"
#include "IO/csv.hxx"
#include "IO/iq_data_reader.hxx"
#include "RADIO/radioFileSignal.cxx"
#include "RADIO/radio.hxx"
#include "GUI/QSpectrum.hxx"

#include <glog/logging.h>



using namespace std;

int main(int argc,char **argv){
	google::InitGoogleLogging(argv[0]);
	int nPoints;
	LOG(INFO) << "Starting app..";
	shared_ptr<radioSignal> oSignal(new radioFileSignal("test.txt",1024));
	unique_ptr<radio> oRadio(new radio(oSignal));
	
/*
	QApplication app(argc, argv);
	QSpectrum spectrum;
    //QLabel hello("Hello world!");

	//hello.show();
	spectrum.show();

    return app.exec();
*/
	DLOG(INFO) << "Ending app..";
}
