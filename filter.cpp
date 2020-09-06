#include <Arduino.h>
#include <filter.h>

// Basic constructor. sets filter in unused state and lower and higher boundaries at max.
Filter::Filter()
{
    Filter::currState = 'u'; //unused to begin with
    Filter::lowerLevel = 0;
    Filter::upperLevel = 1023;
}

// Takes in chars u, l, h or b to save in currState and then send into the setMode function.
void Filter::input(char inputChar)
{
    if(inputChar == 'u' || inputChar == 'l' || inputChar == 'h' || inputChar == 'b')
    {
        Filter::currState = inputChar;
        Filter::setMode();
    }
    
}

//sets the mode of the filter according to the character the function recives
void Filter::setMode()
{
    switch(Filter::currState)
    {
        case 'l':   //low Filter
            Filter::lowerLevel = 0;
            Filter::upperLevel = 255;
            break;
        case 'h': //High filter
            Filter::lowerLevel = 768;
            Filter::upperLevel = 1023;
            break;
        case 'b': //band filter
            Filter::lowerLevel = 255;
            Filter::upperLevel = 768;
            break;
        case 'u': // unused filter
            Filter::lowerLevel = 0;
            Filter::upperLevel = 1023;
            break;
    }

}

//return the lower value of the filter *NOT COMPLETED SINCE IT WAS NOT NEEDED
int Filter::getLowerLevel()
{
    return lowerLevel;
}
//returns the upper value of the filter *NOT COMPLETED SINCE IT WAS NOT NEEDED
int Filter::getUpperLevel()
{
    return upperLevel;
}

// converts and incoming int value onto the selected filter mode.
int Filter::filterKeepInside(int inputValue)
{
    if (inputValue > Filter::upperLevel)
    {
        return Filter::upperLevel;
    }
    else if (inputValue < Filter::lowerLevel)
    {
        return Filter::lowerLevel;
    }
    else
    {
        return inputValue;
    }
}

// Filter everything to 0 if its outside the band of the filter.
int Filter::filterZeroOutside(int inputValue)
{
    if (inputValue > Filter::upperLevel || inputValue < Filter::lowerLevel)
    {
        return 0;
    }
    else
    {
        return inputValue;
    }
    
}