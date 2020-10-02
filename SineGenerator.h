#pragma once

#include "Signal.h"

namespace synth
{
    class SineGenerator : public SignalOut
    {
    public:
        double frequency() const
        {
            return _frequency;
        }

        void frequency(double value)
        {
            _frequency = value;
        }

        double phase() const
        {
            return _phase;
        }

        void phase(double value)
        {
            _phase = value;
        }

        double amplitude() const
        {
            return _amplitude;
        }

        void amplitude(double value)
        {
            _amplitude = value;
        }

        void generate(unsigned sampleCount, float samples[], unsigned sampleRate);

    private:
        double _frequency;
        double _phase;
        double _amplitude;
    };
}
