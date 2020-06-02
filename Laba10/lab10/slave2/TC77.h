#include <Arduino.h>

class TC77 {
    private:
        int _pin_data;
        int _pin_clock;
        int _pin_cs;

    public:
        TC77(int data, int clk, int cs) : _pin_data(data), _pin_clock(clk), _pin_cs(cs) {}
        void begin();

        float read();
        uint16_t readRaw();
        void sleep();
        void wake();
};
