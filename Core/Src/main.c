#include "init.h"
#include <stdbool.h>

bool Button1State = 0; // button 1 PB12 
bool Button1Prev = 0;

bool Button2State = 0; // button 2 PB15
bool Button2Prev = 0;

bool Button3State = 0; // button 3 PB9
bool Button3Prev = 0;

bool mode = 0; // "0" = input, "1" = output


int main(void) {
    
    // Initialization
    RCC_init(); 
    Onboard_leds_init(); 

    while (1) {
        Button1State = (READ_BIT(GPIOB -> IDR, GPIO_IDR_IDR))
    }
}
