#include "radio.hxx"
#include <glog/logging.h>

radio::radio(shared_ptr<radioSignal> signal)
	:oMainWindow(new MainWindow()){
	DLOG(INFO) << "created constructor";
	oMainWindow->show();	
}

radio::~radio(){

}
