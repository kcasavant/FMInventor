#include "PreviewController.h"
#include "SineSource.h"
#include <iostream>
#include <QAudioFormat>
#include <QAudio>
#include <QString>

namespace synth
{

    QAudioDeviceInfo getDefaultOutputDevice(QString deviceName = "default")
    {
        for (QAudioDeviceInfo &info : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
        {
            if (info.deviceName() == deviceName)
                return info;
        }

        return QAudioDeviceInfo::defaultOutputDevice();
    }

    PreviewController::PreviewController() :
        _frequency(440.0),
        _status(Stopped),
        _previewSource(0L)
    {
        QAudioFormat desiredFormat;
        QAudioDeviceInfo info = QAudioDeviceInfo(getDefaultOutputDevice());
        std::cerr << "defaultOutputDevice: " << info.deviceName().toUtf8().constData() << std::endl;
        desiredFormat.setChannelCount(1);
        desiredFormat.setSampleRate(44100);
        desiredFormat.setSampleType(QAudioFormat::Float);
        desiredFormat.setSampleSize(32);
        desiredFormat.setByteOrder(QAudioFormat::LittleEndian);
        QAudioFormat format = info.nearestFormat(desiredFormat);
        if (!info.isFormatSupported(format))
            throw SetupError("Format not supported by device");
        _audioOutput = new QAudioOutput(info, format, this);

        std::cerr << "sample rate: " << format.sampleRate() << "\n";
        std::cerr << "sample size: " << format.sampleSize() << "\n";
        std::cerr << "sample type: " << format.sampleType() << "\n";
        std::cerr << "channels: " << format.channelCount() << "\n";
        std::cerr << "byte order: " << format.byteOrder() << "\n";

    }

    PreviewController::~PreviewController()
    {
        delete _audioOutput;
    }

    void PreviewController::play()
    {
        std::cout << "PreviewController::start w/ frequency " << _frequency << std::endl;
        if (_previewSource != 0L)
        {
            SineSource* sineSource = static_cast<SineSource*>(_previewSource);
            sineSource->frequency(_frequency);
            sineSource->amplitude(0.3333);
            status(Playing);
            _audioOutput->start(_previewSource);
        }
    }

    void PreviewController::stop()
    {
        std::cout << "PreviewController::stop" << std::endl;
        _audioOutput->stop();
        status(Stopped);
    }

    void PreviewController::setSource()
    {
        if (_previewSource == 0L)
        {
            _previewSource = new SineSource;
            _previewSource->open(QIODevice::ReadOnly);
        }
    }
}
