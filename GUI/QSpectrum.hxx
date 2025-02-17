#pragma once
#include <QtGui>
#include <QWidget>
#include <QObject>
#include <memory>
#include <vector>
#include <complex>

#include <iostream>
using namespace std;
// http://www.kuqin.com/qtdocument/designer-manual-6.html

using namespace std;

class QSpectrum: public QWidget
{
	Q_OBJECT
public:
	QSpectrum (QWidget *parent);
	void setZeroAtCenter(bool param);
	void addSpectrumData(vector<complex<double>> spectrumData);
	void setSelectedFrequencyAndWidth(long freq,long width){
		selectedFreq = freq;
		selectedFreqWidth = width;
		updateFreqPos();
	}

	void updateFreqPos(){
		selectedFreqWidthSize = abs(((selectedFreqWidth) / (double) bandWidth) * 1024);
		if ((selectedFreq > minFrequency) && (selectedFreq < maxFrequency))
		{
			selectedFreqPos = (((selectedFreq - minFrequency) / (double) bandWidth) * (double) 1024) 
				- selectedFreqWidthSize/(double)2;
		}
		qDebug() << "selectedFreqPos" << selectedFreqPos;
	}
	void setMinMaxFrequency(long min,long max){
		minFrequency = min;
		maxFrequency = max;
		bandWidth = abs(max-min);
	}
	void subscribeFrequencyChange(function<void(long,long)> callback){
		freqChangeCallback = callback;
	}

	long getSelectedWidth(){

	}

	virtual ~QSpectrum (){
	}

protected:
	QPainter painter;
	QTimer timer;
    QRgb *pixels;
	QImage *image;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void CreatePalete();
	QRgb getColor(unsigned char val);
	list<vector<int>> data;
	QMutex dataMutex;

signals:


public slots:
	void changeT();

private:
	std::array<QRgb, 255> palette;
	void prepareDisplay(QRgb *pixels);
	void drawLine(QRgb *pixels,vector<int> data);
	bool zeroAtCenter;
	long minFrequency;
	long maxFrequency;
	long bandWidth;

	long selectedFreq;
	long selectedFreqPos;
	long selectedFreqWidth;
	long selectedFreqWidthSize;
	function<void(long,long)> freqChangeCallback;
	bool canChangeSelectedFrequency;
	
	// TODO: fix this
	int dupa;
	vector<int> ppp_data;
	vector<int> pp_data;
	vector<int> p_data;
};
