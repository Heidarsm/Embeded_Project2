#include <digital_in.h>
#include <digital_out.h>
#include <analog_in.h>
#include <Arduino.h>
#include <debounce.h>
#include <filter.h>
#include <filter2.h>
#include <PWM_out.h>

//********CONNECTIONS****************
//pin12: pull-up Push button
//pin3: LED PWM signal
//A5: Analog Input from sensor
//***********************************



bool configureState = false;

bool firstIterationFilter = true;
bool firstIterationNoFilter = true;


bool ISR_choice = true;
char filterInput = 'u';

int storeData = 0;
int filteredData = 0;
float pwmStrength = 0;



Analog_in testInput(5); //Analog input á A5
Digital_in buttonInput(0, ISR_choice); //Button input on pin 12 (PB4) with ISR set on true.
Debounce testDebounce(500); //debounce set to 500 ms
PWM_out ledTimer;
Filter2 testFilter = Filter2();

void setup() {
  
  Serial.begin(9600);
  testInput.init();
  buttonInput.init();
  ledTimer.init(); // Creates a PWM timer2 for pin 3. 
}

void loop() {

  storeData = testInput.read(); //reads the analog input
  

  if(!configureState)
  {
   
    Serial.write("Analog read: ");
    Serial.println(storeData);

  }
  else
  {
    storeData = testFilter.sample(storeData); //converts storedData to filtered Data
    Serial.write("Filtered Value: ");
    Serial.println(storeData);
    //testOutput.init(filteredData/4);
  }
  testFilter.printSamples();

  
  pwmStrength = map(storeData, 0, 1023, 0, 255);
  ledTimer.set(pwmStrength);

  delay(1000);  // DELAY ONLY USED TO SEE SERIAL EASIER, NOT NEEDED
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

