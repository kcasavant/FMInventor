#pragma once

#include <QObject>
#include <qqml.h>
#include <QAudioOutput>

#include <exception>
#include <string>

namespace synth
{
    class SetupError : public std::exception
    {
    public:
        SetupError(std::string message) : _message(message) {  }

        const char* what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };

    class PreviewController : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(double frequency READ frequency WRITE frequency NOTIFY frequencyChanged)
        Q_PROPERTY(QIODevice* previewSource READ previewSource WRITE previewSource NOTIFY previewSourceChanged)
        Q_PROPERTY(Status status READ status NOTIFY statusChanged)

    public:
        PreviewController();
        ~PreviewController();

        enum Status
        {
            Playing,
            Stopped
        };
        Q_ENUM(Status);

        double frequency() const
        {
            return _frequency;
        }

        void frequency(double value)
        {
            double prev = _frequency;
            _frequency = value;
            if (prev != value)
                emit frequencyChanged(value);
        }

        Status status() const
        {
            return _status;
        }

        QIODevice* previewSource() const
        {
            return _previewSource;
        }

        void previewSource(QIODevice* source)
        {
            _previewSource = source;
        }

        Q_INVOKABLE void setSource();

    public slots:
        void play();
        void stop();
        
    signals:
        void frequencyChanged(double newFrequency);
        void previewSourceChanged();
        void statusChanged();

    private:
        void status(Status value)
        {
            _status = value;
            emit statusChanged();
        }

        double _frequency;
        Status _status;
        QIODevice *_previewSource;
        QAudioOutput *_audioOutput;
    };
}
