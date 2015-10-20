#include <iostream>

#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <vector>
#include <limits>

#include <qapplication.h>
#include <qlabel.h>

#include "DSP/fourier.hxx"
#include "IO/csv.hxx"
#include "IO/iq_data_reader.hxx"

#include "GUI/QSpectrum.hxx"
#include <QTimer>


using namespace std;
using namespace log4cplus;

int main(int argc,char **argv){
	// log configuration
	SharedAppenderPtr append(new FileAppender("sdr_c3r.log"));
	auto_ptr<Layout> layout(new log4cplus::PatternLayout("%p [%d{%H:%M:%S}] [%c] - %m%n"));
	append->setLayout(layout);
	Logger log = Logger::getRoot();
	log.addAppender(append);
	// end of log configuration

	int nPoints;
	cout << "Starting app.." << endl;


	QApplication app(argc, argv);
	QSpectrum spectrum;
    //QLabel hello("Hello world!");

	//hello.show();
	spectrum.show();

    return app.exec();

	cout << "Ending app.." << endl;
}
