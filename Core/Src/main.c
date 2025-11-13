#include "init.h"
#include <stdbool.h>


bool Button1State = 0; // button 1 PB12 (pull-up)
bool Button2State = 0; // button 2 PB15 (pull-up)
bool Button3State = 0; // button 3 PB9  (pull-down)

bool mode = 0; // "0" = input, "1" = output

int main(void) {
    
    // Initialization
    RCC_init(); 
    Onboard_leds_init(); // onboards: green PB0, blue PB7, red PB14; external: led 4 PB7
    Button1_input();
    Button2_input();

    while (1) {

        // reading buttons states and managing their LEDs
        Button1State = !(READ_BIT(GPIOB -> IDR, GPIO_IDR_IDR_12));
        if (Button1State == 1) {
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_14);
        }
        else {
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_14);
        }

        Button2State = !(READ_BIT(GPIOB -> IDR, GPIO_IDR_IDR_15));
        if ((Button2State) == 1) {
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_7);
        }
        else {
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_7);
        }

        // changing modes 
        if (Button1State && !Button2State) { 
            mode = 0;
        }
        else if (!Button1State && Button2State) {
            mode = 1;
        }

        // modes
        if (mode == 0) {
            // turning off external LED and setting pin as input
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_9);
            ButtonAndLed_input();

            Button3State = (READ_BIT(GPIOB -> IDR, GPIO_IDR_IDR_9));
            if (Button3State == 1) {
                SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_0);
            }
            else {
                SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_0);
            }
        }
        else {
            // turning on external LED and setting pin as output
            ButtonAndLed_output();
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_9);
        }
    }
}