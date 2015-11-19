#include <memory>

#include <vector>
#include <complex>
#include "../DSP/convolution.hxx"
#include "../DSP/decimate.hxx"

using namespace std;
template <class T>
class WFMdecoder
{
	public:
		WFMdecoder(int blockSize):
			blockSize(blockSize),oDemodulatedDecimate(new decimate::segment_decimate<double>(10)){
				// initialise vector sizes
				id.resize(blockSize);
				rd.resize(blockSize);
				brd.resize(blockSize);
				bid.resize(blockSize);
				demodulated.reserve(blockSize);

				b.push_back(1);
				b.push_back(-1);
			}
		void decode(vector<complex<T>> &input,vector<T> &output){
			demodulated.clear();
			for (int i=0;i<(int)input.size();++i){
				complex<T> val = input[i] / abs(input[i]);
				rd[i] = val.real();
				id[i] = val.imag();
			}


			convolution::do_segment_conv(bid_overlap,id,b,bid);
			convolution::do_segment_conv(brd_overlap,rd,b,brd);
			for (int i=0;i< (int)bid.size();i++){
				demodulated.insert(demodulated.end(),
						((id[i] * brd[i]) - (rd[i] * bid[i]) ) / ((rd[i] * rd[i]) + (id[i] * id[i])));
			}

			if (demodulated.size() >= 10240){
				oDemodulatedDecimate->decimate(demodulated,output);
			}
		}
		virtual ~WFMdecoder (){
		};

	private:
		vector <double> demodulated;
		int blockSize;
		vector<T> b;	
		vector<T> bid_overlap;
		vector<T> brd_overlap;

		vector<T> rd;
		vector<T> id;

		vector<T> brd;
		vector<T> bid;
		/* data */	
		shared_ptr<decimate::segment_decimate<double>> oDemodulatedDecimate;;
};
