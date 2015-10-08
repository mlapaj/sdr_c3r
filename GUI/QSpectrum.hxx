#include <QtGui>
#include <QWidget>
#include <QObject>
#include <memory>
// http://www.kuqin.com/qtdocument/designer-manual-6.html

using namespace std;

class QSpectrum: public QWidget
{
	Q_OBJECT
public:
	QSpectrum ();
	virtual ~QSpectrum (){
	}

protected:
	QTimer timer;
	QRgb *pixels;
	QImage *image;
	void paintEvent(QPaintEvent *event);

signals:


public slots:
	void changeT();

private:
	/* data */
};
