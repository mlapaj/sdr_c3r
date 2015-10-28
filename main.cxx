#include <iostream>

#include <iomanip>
#include <vector>
#include <limits>
#include <memory>

#include <qapplication.h>
#include <qlabel.h>

#include "DSP/fourier.hxx"
#include "IO/csv.hxx"
#include "IO/iq_data_reader.hxx"
#include "RADIO/radioFileSignal.cxx"
#include "RADIO/radio.hxx"

#include "GUI/QSpectrum.hxx"
#include <QTimer>


using namespace std;

int main(int argc,char **argv){

	int nPoints;
	cout << "Starting app.." << endl;

	shared_ptr<radioSignal> signal(new radioFileSignal("test.txt",1024));
/*
	QApplication app(argc, argv);
	QSpectrum spectrum;
    //QLabel hello("Hello world!");

	//hello.show();
	spectrum.show();

    return app.exec();
*/
	cout << "Ending app.." << endl;
}
