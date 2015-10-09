#include <string>
#include <iostream>
#include <memory>

using namespace std;

class iq_data_reader
{
public:
	iq_data_reader(string fileName,int block_size());
	virtual ~iq_data_reader ();

private:
	unique_ptr<ifstream> file;
	/* data */
};
