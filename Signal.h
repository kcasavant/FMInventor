#pragma once

namespace synth
{
    class SignalOut;

    class SignalIn 
    {
    public:
        SignalOut *generator() const
        {
            return _generator;
        }

        void generator(SignalOut *instance)
        {
            _generator = instance;
        }

    private:
        SignalOut *_generator;
    };

    class SignalOut
    {
    public:
        virtual void generate(unsigned sampleCount, float samples[], unsigned sampleRate) = 0;
    };
}
