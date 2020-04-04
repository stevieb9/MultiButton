#include <Arduino.h>
#include <MultiButton.h>
#include "MultiButton.h"

#define ANALOG_PIN A0
#define NUM_BUTTONS 9
#define BUTTON_NOISE 100

// Button number, min analog reading, max analog reading

uint16_t button[NUM_BUTTONS][3] = {
        {0, 943, 948}, // button 0  // R1
        {1, 859, 865}, // button 1  // R1
        {2, 745, 755}, // button 2  // R2
        {3, 440, 451}, // button 3  // R2
        {4, 265, 275}, // button 4  // sys1
        {5, 143, 155}, // button 5  // sys2
        {6, 988, 997}, // button 0 + button 1 // R1 Set mode
        {7, 802, 813}, // button 2 + button 3 // R2 Set mode
        {8, 345, 358}, // button 4 + button 5 // sys1+sys2
};

int8_t MultiButton::pressed () {

    int8_t pressed = -1;

    if (millis() != sampleTime) {
        uint16_t buttonVal = analogRead(ANALOG_PIN);

        if (buttonVal == current_state && counter > 0) {
            counter--;
        }
        if (buttonVal != current_state) {
            counter++;
        }

        // If buttonVal has shown the same value for long enough let's switch it
        if (counter >= debounce_count) {
            counter = 0;
            current_state = buttonVal;
            //Checks which button or button combo has been pressed
            if (buttonVal > BUTTON_NOISE) {
                pressed = buttonCheck(buttonVal);
            }
        }

        sampleTime = millis();
    }

    return pressed;
}

int8_t MultiButton::buttonCheck(uint16_t buttonVal) {
    int8_t pressed = -1;

    for (auto & i : button) {
        /* For debugging with serial
            ser.print("Val: ");
            ser.print(buttonVal);
            ser.print(" But: ");
            ser.print(i[0]);
            ser.print(" Min: ");
            ser.print(i[1]);
            ser.print(" Max: ");
            ser.print(i[2]);
        */
        if (buttonVal >= i[1] && buttonVal <= i[2]) {
            pressed = i[0];
            break;
        }
    }

    /* For debugging with serial
        ser.print(" Pressed: ");
        ser.println(pressed);
    */

    return pressed;
}
