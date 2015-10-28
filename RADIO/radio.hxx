#include <memory>
#include "radioSignal.hxx"

class radio
{
public:
	radio (shared_ptr<radioSignal> signal);
	virtual ~radio ();
private:
	long fs = 2500000; // radio sampling rate
	long frequency;
	shared_ptr<radioSignal> signal;
	/* data */
};
