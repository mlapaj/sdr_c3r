#include "audioOutput.hxx"
const int DataSampleRateHz = 44100;

void audioOutput::init()
{
    // connect(pushTimer, SIGNAL(timeout()), SLOT(pushTimerExpired()));
	

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

//    m_generator = new Generator(m_format, DurationSeconds*1000000, ToneSampleRateHz, this);
    createAudioOutput();
}


void audioOutput::createAudioOutput()
{
    delete oAudioOutput;
    oAudioOutput = 0;
    oAudioOutput = new QAudioOutput(device, format, this);
    oAudioOutput->start(oAudioSamples);

}
