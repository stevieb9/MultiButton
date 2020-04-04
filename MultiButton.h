#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include <Arduino.h>

class MultiButton {

    private:
        int counter                 = 0; // how many times we have seen new value
        unsigned long sampleTime    = 0;  // the last time the output pin was sampled
        uint8_t debounce_count      = 75;
        uint16_t current_state      = 0;  // the debounced input value

    public:

        MultiButton () = default;
        //HardwareSerial& ser;
        //MultiButton(HardwareSerial& serial) : ser(serial) {}

        int8_t pressed ();
        static int8_t buttonCheck (uint16_t buttonVal);
};

#endif //_MULTI_BUTTON_H_
