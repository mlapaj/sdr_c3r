#include <memory>
#include "radioSignal.hxx"
#include "../GUI/mainwindow.h"
class radio
{
	public:
		radio (shared_ptr<radioSignal> signal);
		void processRadio();
		virtual ~radio ();
	private:
		long fs = 2500000; // radio sampling rate
		long frequency;

		// radio object
		shared_ptr<radioSignal> signal;
		shared_ptr<MainWindow> oMainWindow;
		
};
