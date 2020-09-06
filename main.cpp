#include <digital_in.h>
#include <digital_out.h>
#include <analog_in.h>
#include <Arduino.h>
#include <debounce.h>
#include <filter.h>
#include <analog_out.h>

bool configureState = false;
bool firstIteration = true;
bool ISR_choice = true;
char filterInput = 'u';

int storeData = 0;
int filteredData = 0;

int lowerLevel = 0;
int upperLevel = 0;


Analog_in testInput(5); //Analog input á A5
Digital_in buttonInput(0, ISR_choice); //Button input on pin 12 (PB4) with ISR set on true.
Debounce testDebounce(500); //debounce set to 500 ms
Filter testFilter = Filter();    // New Filter, currently set to 0-1023
Analog_out testOutput(5);


void setup() {
  
  Serial.begin(9600);
  testInput.init();
  buttonInput.init();
  testFilter.input('l');
}

void loop() {
  
  if(configureState)
  {
    if(firstIteration)
    {
      Serial.write("You are in configuration mode \n");
      Serial.println("********************************");
      Serial.println("* h * High filter (768-1024)   *");
      Serial.println("* l * Low filter (0-255        *");
      Serial.println("* b * Band filter (255-768)    *");
      Serial.println("* u * Unused filter (0 - 1024) *");
      Serial.println("********************************");

      firstIteration = false;
    }

    while(Serial.available()){
      filterInput = Serial.read();
    }

  }
  else{
    firstIteration = true;
    testFilter.input(filterInput);
    Serial.write("Analog read:");

    storeData = testInput.read(); //reads the analog input
    filteredData = testFilter.filterKeepInside(storeData); //converts storedData to filtered Data
    Serial.println(storeData);
    Serial.write("Filtered Value: ");
    Serial.println(filteredData);
    //testOutput.init(filteredData);

    delay(1000);  // DELAY ONLY USED TO SEE SERIAL EASIER, NOT NEEDED
  }
}

ISR(PCINT0_vect){
  
  if(testDebounce.check())
  {
    if(configureState)
    {
      configureState = false;
    }
    else
    {
      configureState = true;
    }
  }
  testDebounce.updateLast();
}

