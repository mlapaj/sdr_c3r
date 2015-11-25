#include "AudioOutput.hxx"
using namespace std;
const int DataSampleRateHz = 44100;

void AudioOutput::init()
{
    // connect(pushTimer, SIGNAL(timeout()), SLOT(pushTimerExpired()));
	cout << "!!!!!!!" << endl;

    pullMode = true;

    format.setSampleRate(DataSampleRateHz);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = info.nearestFormat(format);
    }
	qDebug() << "!!" << endl;

//    m_generator = new Generator(m_format, DurationSeconds*1000000, ToneSampleRateHz, this);
    createAudioOutput();
}


void AudioOutput::createAudioOutput()
{
    delete audioOutput;
    audioOutput = 0;
    audioOutput = new QAudioOutput(device, format, this);
    audioOutput->start(audioSamples);

}
