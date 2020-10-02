#include "SineSource.h"
#include <iostream>

namespace synth
{
    qint64 SineSource::readData(char* data, qint64 maxSize)
    {
        static bool once = true;
        _generator.generate(maxSize / 4, (float*)data, 44100);
        if (once == true)
        {
            float *fdata = (float*)data;
            once = false;
            for(uint_fast32_t i = 0; i < maxSize / 4; i++)
                std::cerr << fdata[i] << " ";
            std::cerr << std::endl;
        }
        return maxSize;
    }

    qint64 SineSource::writeData(const char* data, qint64 maxSize)
    {
        return -1;
    }
}
