class Analog_out
{
private:
    
public:
    Analog_out();
    Analog_out(int pin);
    void init();
    void init(float duty_cycle);
    void set_hi();
    void set_lo();
};


