#include <vector>
using namespace std;
namespace filter{
	vector<double> fir_lowpass(int length,long fs,long cutoff);
	vector<double> hamming(int length);
};

