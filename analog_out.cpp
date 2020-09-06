#include <Arduino.h>
#include <analog_out.h>

Analog_out::Analog_out()
{
}

Analog_out::Analog_out(int pin)
{
    //DDRD |= (1<<pin);   //Set pin as output (7 - 0)
    DDRB |= (1<<pin);
}


void Analog_out::init()
{
    // this code sets up timer1 for a 1 s  @ 16Mhz system clock (mode 4)
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0

    OCR1A = 16000000 / 1024 - 1;         // assign target count to compare register A (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer
}

void Analog_out::init(float duty_cycle)
{
    /*// this code sets up timer1 for a 1 s  with the specified duty cycle
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  //initialize counter value to 0

    OCR1A = 16000000 / 1024 - 1;         // assign target count to compare register A (must be less than 65536)
    OCR1B = OCR1A * duty_cycle;          // assign target count to compare register B (must be less than 65536)
    TCCR1B |= (1 << WGM12);              // clear the timer on compare match A (Mode 4, CTC on OCR1A)
    TIMSK1 |= (1 << OCIE1A);             // set interrupt on compare match A
    TIMSK1 |= (1 << OCIE1B);             // set interrupt on compare match B
    TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 and start the timer*/

    //From 0-1023 with mapping
    TCCR1A = 0x20;          //Normal mode for OC1A and B
    //TCCR1B = 0X05;          //F = 16Mhz/1024
    
    OCR1A = map(duty_cycle, 0, 1023, 0, 65535);     //duty cycle for timer 1 is a 16 bit register so we map it to 0-1023
    TIMSK1 = 0X03;          //Enable overflow and compare A interrupts 
    TIFR1 = 0X03;           //Clear Flags
}

void Analog_out::set_hi(){
    PORTB |= (1<<5);
}

void Analog_out::set_lo(){
    PORTB &= ~(1<<5);
}