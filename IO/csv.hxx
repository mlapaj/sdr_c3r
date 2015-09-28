#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>
#include <iomanip>
#include <string>
#include <iostream>

using namespace log4cplus;
using namespace std;

class csv{
	private:
		static Logger logger;
		static const int blockSize = 1024;
		static char block[blockSize];
	public:
		static int read_int(string filename,vector<int> &array);
		static int read_double(string filename,vector<double> &array);
};
