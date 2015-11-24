#pragma once

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioOutput>
#include <QTimer>
#include <QtGui>


class audioSamples : public QIODevice
{
	public:
		void start(){}
		void stop(){}
		qint64 readData(char *data, qint64 maxlen){}
		qint64 writeData(const char *data, qint64 len){}
		qint64 bytesAvailable() const {}
};

class audioOutput: public QObject
{


public:
	audioOutput ():
		oAudioOutput(0),
		device(QAudioDeviceInfo::defaultOutputDevice()),
		pushTimer(new QTimer()),
		oAudioSamples(new audioSamples())
	{}
	void init();
	virtual ~audioOutput (){}

private slots:
	void pushTimerExpired();

private:
	QAudioFormat format;
	QAudioOutput *oAudioOutput;
	QAudioDeviceInfo device;
	QTimer *pushTimer;
	bool pullMode;
	void createAudioOutput();
	/* data */
	audioSamples *oAudioSamples;

};
