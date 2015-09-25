#include <iostream>
#include "DSP/fourier.hxx"

#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>

using namespace std;
using namespace log4cplus;

int main(){
	// log configuration
	SharedAppenderPtr append(new FileAppender("sdr_c3r.log"));
	auto_ptr<Layout> layout(new log4cplus::PatternLayout("%p [%d{%H:%M:%S}] [%c] - %m%n"));
	append->setLayout(layout);
	Logger log = Logger::getRoot();
	log.addAppender(append);
	// end of log configuration

	cout << "Starting app.." << endl;
	fourier oFourier(64);
	LOG4CPLUS_DEBUG(log, "This is a bool: " << true);

	cout << "Ending app.." << endl;
}
