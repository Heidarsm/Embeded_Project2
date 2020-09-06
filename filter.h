
#include <arduino.h>

class Filter {

    public:
        Filter();
        void input(char inputChar);
        void setMode();
        int getUpperLevel();
        int getLowerLevel();
        int filterKeepInside(int inputValue);
        int filterZeroOutside(int inputValue);

    private:
        char currState;
        int lowerLevel;
        int upperLevel;

};



