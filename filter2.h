#include <arduino.h>

class Filter2 {

    public:
        Filter2();
        ~Filter2();
        int sample(int inputValue);
        void printSamples();

    private:
        int* lastFive;
        int numberOfSamples;
};