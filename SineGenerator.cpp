#include "SineGenerator.h"
#include <cmath>

namespace synth
{
    const double PI = 3.141592654;
    const double CIRCLE = 2.0 * PI;

    void SineGenerator::generate(unsigned sampleCount, float samples[], unsigned sampleRate)
    {
        double phaseStep = CIRCLE / ((double)sampleRate / _frequency);
        double phase = _phase;

        for (int i = 0; i < sampleCount; i++)
        {
            samples[i] = (float)(_amplitude * std::sin(phase));
            phase = std::fmod(phase + phaseStep, CIRCLE);
        }

        _phase = phase;
    }
}
