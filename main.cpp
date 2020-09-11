#include <digital_in.h>
#include <digital_out.h>
#include <analog_in.h>
#include <Arduino.h>
#include <debounce.h>
#include <filter.h>
#include <filter2.h>
#include <PWM_out.h>

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


float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void setup() {
  
  Serial.begin(9600);
  testInput.init();
  buttonInput.init();
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

  
  pwmStrength = mapfloat(storeData, 0, 1023, 0, 1);
  // We can't get this part to work properly with the code. 
  // Everytime We try to use TIMER1 in the PWM class, debounce,
  // serial and analog read stop working.
  // We tried changing to use the PWM on a different timer, but then
  // the PWM class stoped working. 

  //ledTimer.init(pwmStrength);

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

