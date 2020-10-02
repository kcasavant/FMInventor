#pragma once

#include <QIODevice>
#include "SineGenerator.h"

namespace synth
{
    class SineSource : public QIODevice
    {
        Q_OBJECT

    public:
        double frequency() const
        {
            return _generator.frequency();
        }

        void frequency(double value)
        {
            _generator.frequency(value);
        }

        double amplitude() const
        {
            return _generator.amplitude();
        }

        void amplitude(double value)
        {
            _generator.amplitude(value);
        }

        bool isSequential() const override
        {
            return true;
        }

    protected:
        qint64 readData(char* data, qint64 maxSize) override;
        qint64 writeData(const char* data, qint64 maxSize) override;

    private:
        SineGenerator _generator;
    };
}
