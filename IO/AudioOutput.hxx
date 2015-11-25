#pragma once
#include <memory>
#include <vector>
#include <list>

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
		qint64 readData(char *data, qint64 maxlen){
			long dataSent = 0;
			if (audioBuffer->empty()) return 0;
			vector<qint16> &currentBuffer = audioBuffer->front();
			cout << "currentBufferLen " << currentBuffer.size() << endl;
			if ((int)currentBuffer.size() <= maxlen){
				cout << maxlen << endl;
				for (int i=0;i<currentBuffer.size();i++){
					for (int j=0;j<2;j++){
						cout << "data" << currentBuffer[i] << endl;
						if (dataSent>maxlen) break;
						data[dataSent++] = ((char *)&(currentBuffer[i]))[2-j];
//						data[dataSent++] = 0;
					}
				}
				audioBuffer->pop_front();
				if (audioBuffer->size() > 50){
					audioBuffer->clear();
					cout << "!!@!@!@!" << endl;
				}

			}
			else{
				cout << "error";
				qDebug() << "error";
			}
			return dataSent;
		}
		qint64 writeData(const char *data, qint64 len){ qDebug() << "writeData" << endl;}
		qint64 bytesAvailable() const { qDebug() << "bytesAvailable";}
		~AudioSamples(){
		
		}
//	private:
		list<vector<qint16>> *audioBuffer;
};

class AudioOutput: public QObject
{


public:
	list<vector<qint16>> *audioBuffer;
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
	unique_ptr<AudioSamples> audioSamples;

};
