#include <Arduino.h>
#include <PWM_out.h>

PWM_out::PWM_out()
{

}

void PWM_out::init(float duty_cycle)
{
   // this code sets up timer1 for a 1 s  with the specified duty cycle
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0

    OCR1A = 16000000 / 1024 - 1;         // assign target count to compare register A (must be less than 65536)
    OCR1B = OCR1A * duty_cycle;          // assign target count to compare register B (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B);             // set interrupt on compare match B
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
}
