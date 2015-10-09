#include <string>
#include <iostream>
#include <memory>

using namespace std;

class iq_data
{
public:
	iq_data (string fileName);
	virtual ~iq_data ();

private:
	unique_ptr<ifstream> file;
	/* data */
};
