#include <arduino.h>

class Filter2 {

    public:
        Filter2();
        int sample(int inputValue);

    private:
        int* lastFive;
        int numberOfSamples;
};