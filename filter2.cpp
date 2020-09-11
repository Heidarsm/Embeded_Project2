#include <Arduino.h>
#include <filter2.h>
// After talking to torfi, this is how the filter should operate, not like the other filter
// use this one!


// Basic constructor. sets filter in unused state and lower and higher boundaries at max.
Filter2::Filter2(){

    Filter2::lastFive = new int[5](); //Inivitalize array with all values as 0.
    Filter2::numberOfSamples = 0;
    

}

int Filter2::sample(int inputValue){

    switch(Filter2::numberOfSamples){
        case 0:
            lastFive[0] = inputValue;
            break;
        case 1:
            lastFive[1] = inputValue;
            break;
        case 2:
            lastFive[2] = inputValue;
            break;
        case 3: 
            lastFive[3] = inputValue;
            break;
        case 4: 
            lastFive[4] = inputValue;
            break;
        case 5:
            lastFive[0] = lastFive[1];
            lastFive[1] = lastFive[2];
            lastFive[2] = lastFive[3];
            lastFive[3] = lastFive[4];
            lastFive[4] = inputValue;
            break;
    }
    if(Filter2::numberOfSamples < 5)
    {
        Filter2::numberOfSamples++;
    }

    int sum = 0;

    for (int i = 0; i <5; i++)
    {
        sum+=lastFive[i];
    } 

    return (sum/numberOfSamples);
    
}

Filter2::~Filter2(){

    if(Filter2::lastFive)
    {
        delete[] Filter2::lastFive;
    }

}

void Filter2::printSamples()
{
    Serial.print("Samples are: ");
    for (int i = 0; i < 5; i++)
    {
        Serial.print(Filter2::lastFive[i]);
        Serial.print(" ");
    }
    Serial.print("\n");
}