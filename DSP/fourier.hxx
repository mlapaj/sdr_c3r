#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
using namespace log4cplus;

class fourier{
	private:
		int nPoints;
		Logger logger = Logger::getInstance("fourier");
	public:
		fourier(int nPoints);
};
