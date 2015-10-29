#pragma once
#include <QtGui>
#include <QWidget>
#include <QObject>
#include <memory>
#include <vector>
#include <complex>
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
	virtual ~QSpectrum (){
	}

protected:
	QPainter painter;
	QTimer timer;
    QRgb *pixels;
	QImage *image;
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
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
	/* data */
};
