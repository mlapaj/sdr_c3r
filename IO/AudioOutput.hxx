#pragma once

#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioOutput>
#include <QTimer>
#include <QtGui>

#include <iostream>
using namespace std;

class AudioSamples : public QIODevice
{
	public:
		void start(){
			open(QIODevice::ReadOnly);
		}
		void stop(){}
		qint64 readData(char *data, qint64 maxlen){qDebug() << "read data" << endl;}
		qint64 writeData(const char *data, qint64 len){ qDebug() << "writeData" << endl;}
		qint64 bytesAvailable() const { qDebug() << "bytesAvailable";}
		~AudioSamples(){

		}
};

class AudioOutput: public QObject
{


public:
	AudioOutput ():
		audioOutput(0),
		device(QAudioDeviceInfo::defaultOutputDevice()),
		pushTimer(new QTimer()),
		audioSamples(new AudioSamples())
	{
		cout << "!!!!!!!" << endl;
	}
	void init();
	virtual ~AudioOutput (){}

private slots:
	void pushTimerExpired();

private:
	QAudioFormat format;
	QAudioOutput *audioOutput;
	QAudioDeviceInfo device;
	QTimer *pushTimer;
	bool pullMode;
	void createAudioOutput();
	/* data */
	AudioSamples *audioSamples;

};
