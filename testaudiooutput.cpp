#include <iostream>
#include <QCoreApplication>
#include <QAudio>
#include <QAudioFormat>
#include <QAudioDeviceInfo>

std::string strEndian(QAudioFormat::Endian e)
{
    if (e == QAudioFormat::BigEndian)
        return "BigEndian";
    else if (e == QAudioFormat::LittleEndian)
        return "LittleEndian";
    else
        return "(unknown)";
}

std::string strSampleType(QAudioFormat::SampleType st)
{
    if (st == QAudioFormat::Unknown)
        return "literally unknown";
    else if (st == QAudioFormat::SignedInt)
        return "SignedInt";
    else if (st == QAudioFormat::UnSignedInt)
        return "UnSignedInt";
    else if (st == QAudioFormat::Float)
        return "Float";
    else
        return "(unknown)";
}

void displayDeviceInfo(const QAudioDeviceInfo &info)
{
    std::cout << ">> " << info.deviceName().toUtf8().constData() << " <<" << "\n\n";
    // QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    std::cout << "Supported byte orders:\n";
    for (QAudioFormat::Endian e : info.supportedByteOrders())
        std::cout << "\t" << strEndian(e) << "\n";

    std::cout << "\nSupported channel count:\n";
    for (int c : info.supportedChannelCounts())
        std::cout << "\t" << c << "\n";

    std::cout << "\nSupported sample rates:\n";
    for (int sr : info.supportedSampleRates())
        std::cout << "\t" << sr << "\n";

    std::cout << "\nSupported sample types:\n";
    for (QAudioFormat::SampleType st : info.supportedSampleTypes())
        std::cout << "\t" << strSampleType(st) << "\n";

    std::cout << "\n\n";
}

int main(int argc, char *argv[])
{
    // QCoreApplication app(argc, argv);

    for (const QAudioDeviceInfo& info : QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
    {
        displayDeviceInfo(info);
    }

    return 0;
}
