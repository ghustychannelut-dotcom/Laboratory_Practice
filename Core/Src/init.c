#include "init.h"

/*

LED pins: 
    1 - PB15
    2 - PB13
    3 - PB12
    4 - PB5
    5 - PB3
    6 - PB4

Button pins:
    1 - PB1
    2 - PB6
    3 - PB2

*/


// global variables

extern uint32_t long_press = 0;
extern uint8_t frq_levels = 3;
extern uint32_t frq_step = 10000;

// Actual initialization

void RCC_init(void) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
}

void leds_init(void) {
    
}

void buttons_init(void) {
    
}

// Structures 
typedef struct {

    uint8_t button_num;
    bool is_long;

} button_action;

typedef struct {

    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
    uint8_t led4;
    uint8_t led5;
    uint8_t led6;

} leds;

// functions

void led_on(uint8_t num) {
    switch (num) {
        case 1:
            SET_BIT(GPIOB)
    }
}

void led_off(uint8_t num) {

}

bool read_button(uint8_t num) {

}


button_action check_action(void) {

    button_action action;

    if (read_button(1) == true) { // if button 1 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(1) == false) {
                break;
            }
        }

        action.button_num = 1;
        action.is_long = (i >= long_press);
    }

    else if (read_button(2) == true) { // if button 2 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(2) == false) {
                break;
            }
        }

        action.button_num = 2;
        action.is_long = (i >= long_press);
    }

    else if (read_button(3) == true) { // if button 3 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(3) == false) {
                break;
            }
        }

        action.button_num = 3;
        action.is_long = (i >= long_press);
    }

    else { //if no buttons pressed 

        action.button_num = 0;
        action.is_long = false;
    }

    return action;
}

leds change_led (uint8_t led_change, button_action action) {

    if (action.button_num == 1 && action.is_long == true) {
        led_change++;
    }

    else if (action.button_num == 2 && action.is_long == true) {
        led_change--;
    }
}

leds change_frq (leds led_frq, uint8_t led_change, button_action action) {

    if (action.button_num == 3 && action.is_long == false) {
        
        switch(led_change) {
            case 1:
                led_frq.led1++;
                if (led_frq.led1 >= frq_levels) {
                    led_frq.led1 = frq_levels; 
                }
                break;

            case 2:
                led_frq.led2++;
                if (led_frq.led2 >= frq_levels) {
                    led_frq.led2 = frq_levels; 
                }
                break;

            case 3:
                led_frq.led3++;
                if (led_frq.led3 >= frq_levels) {
                    led_frq.led3 = frq_levels; 
                }
                break;

            case 4:
                led_frq.led4++;
                if (led_frq.led4 >= frq_levels) {
                    led_frq.led4 = frq_levels; 
                }
                break;
                
            case 5:
                led_frq.led5++;
                if (led_frq.led5 >= frq_levels) {
                    led_frq.led5 = frq_levels; 
                }
                break;

            case 6:
                led_frq.led6++;
                if (led_frq.led6 >= frq_levels) {
                    led_frq.led6 = frq_levels; 
                }
                break;
        }
    }

    else if (action.button_num == 3 && action.is_long == true) {
        switch(led_change) {
            case 1:
                led_frq.led1--;
                if (led_frq.led1 <= 0) {
                    led_frq.led1 = 0; 
                }
                break;

            case 2:
                led_frq.led2--;
                if (led_frq.led2 <= 0) {
                    led_frq.led2 = 0; 
                }
                break;

            case 3:
                led_frq.led3--;
                if (led_frq.led3 <= 0) {
                    led_frq.led3 = 0; 
                }
                break;

            case 4:
                led_frq.led4--;
                if (led_frq.led4 <= 0) {
                    led_frq.led4 = 0; 
                }
                break;
                
            case 5:
                led_frq.led5--;
                if (led_frq.led5 <= 0) {
                    led_frq.led5 = 0; 
                }
                break;

            case 6:
                led_frq.led6--;
                if (led_frq.led6 <= 0) {
                    led_frq.led6 = 0; 
                }
                break;
        }
    }
}

leds change_pwr (leds led_pwr, button_action action) {

    if (action.button_num == 1 && action.is_long == false) {
        led_num++;
        if (led_num >= 6) {
            led_num = 6;
        }
    }

    else if (action.button_num == 2 && action.is_long == false) {
        if (led_num <= 1) {
            led_num = 1;
        }
    }

    switch (led_num) {
        case 1: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 0;
                new_pwr.led3 = 0;
                new_pwr.led4 = 0;
                new_pwr.led5 = 0;
                new_pwr.led6 = 0;
            }
            break;
        case 2: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 1;
                new_pwr.led3 = 0;
                new_pwr.led4 = 0;
                new_pwr.led5 = 0;
                new_pwr.led6 = 0;
            }
            break;
        case 3: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 1;
                new_pwr.led3 = 1;
                new_pwr.led4 = 0;
                new_pwr.led5 = 0;
                new_pwr.led6 = 0;
            }
            break;
        case 4: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 1;
                new_pwr.led3 = 1;
                new_pwr.led4 = 1;
                new_pwr.led5 = 0;
                new_pwr.led6 = 0;
            }
            break;
        case 5: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 1;
                new_pwr.led3 = 1;
                new_pwr.led4 = 1;
                new_pwr.led5 = 1;
                new_pwr.led6 = 0;
            }
            break;
        case 6: 
            leds new_pwr {
                new_pwr.led1 = 1;
                new_pwr.led2 = 1;
                new_pwr.led3 = 1;
                new_pwr.led4 = 1;
                new_pwr.led5 = 1;
                new_pwr.led6 = 1;
            }
            break;

        return new_pwr;
    }
}

void leds_flash(uint32_t count, leds led_frq, leds led_pwr) {
    
    leds final_states = led_frq;

    // combining pwr and frq

    if (led_pwr.led1 = 0) {
        final_states.led1 = 0;
    }

    if (led_pwr.led2 = 0) {
        final_states.led2 = 0;
    }

    if (led_pwr.led3 = 0) {
        final_states.led3 = 0;
    }

    if (led_pwr.led4 = 0) {
        final_states.led4 = 0;
    }

    if (led_pwr.led5 = 0) {
        final_states.led5 = 0;
    }

    if (led_pwr.led6 = 0) {
        final_states.led6 = 0;
    }

    // actually flashing LEDs

    if (final_states.led1 == 0) {
        led_off(1);
    }
    else if ((count % final_states.led1) == 0) {
        led_on(1);
    }
    else {
        led_off(1);
    }

    if (final_states.led2 == 0) {
        led_off(2);
    }
    else if ((count % final_states.led2) == 0) {
        led_on(2);
    }
    else {
        led_off(2);
    }

    if (final_states.led3 == 0) {
        led_off(3);
    }
    else if ((count % final_states.led3) == 0) {
        led_on(3);
    }
    else {
        led_off(3);
    }

    if (final_states.led4 == 0) {
        led_off(4);
    }
    else if ((count % final_states.led4) == 0) {
        led_on(4);
    }
    else {
        led_off(4);
    }

    if (final_states.led5 == 0) {
        led_off(5);
    }
    else if ((count % final_states.led5) == 0) {
        led_on(5);
    }
    else {
        led_off(5);
    }

    if (final_states.led6 == 0) {
        led_off(6);
    }
    else if ((count % final_states.led6) == 0) {
        led_on(6);
    }
    else {
        led_off(6);
    }
};




      
/* 
1 часть ЛБ 1

#include "init.h"

void RCC_init(void) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
}

void Onboard_leds_init(void) {

    // green led PB0 ручками
    *(uint32_t*)(0x40020400UL + 0x00UL) |= 0x01UL; // Moder 0_1
    *(uint32_t*)(0x40020400UL + 0x00UL) &= ~0x02UL; // Moder 1_0

    *(uint32_t*)(0x40020400UL + 0x04UL) |= 0x00UL; // OTYPER 0_0

    *(uint32_t*)(0x40020400UL + 0x08UL) |= 0x01UL; // SPEED 0_1
    *(uint32_t*)(0x40020400UL + 0x08UL) &= ~0x02UL; // SPEED 1_0

    *(uint32_t*)(0x40020400UL + 0x0CUL) &= ~0x00UL; // PUPDR 0_0 
    *(uint32_t*)(0x40020400UL + 0x0CUL) &= ~0x01UL; // PUPDR 1_0

    *(uint32_t*)(0x40020400UL + 0x18) |= 0x10000UL; // BSRR reser PB0 output

    // blue led PB7 через CMSIS
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE7_0); // Moder 14_1
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE7_1); // Moder 15_0

    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT7); // OTYPER 7_0

    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR7_0); // SPEED 14_1
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR7_1); // SPEED 15_0

    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD7_0); // PUPDR 14_0
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD7_1); // PUPDR 15_0

    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_7); // // BSRR reset PB7 output

    // red led PB14 через собственные директивы
    BIT_SET(GPIOB_MODER, GPIOB_PIN_14_GPOut);        // MODER14: General-purpose Output
    BIT_RESET(GPIOB_OTYPER, GPIOB_PIN_14_PushPull);  // OTYPER14: Push-pull (0)
    BIT_SET(GPIOB_OSPEEDR, GPIOB_PIN_14_MEDspd);     // OSPEEDR14: Medium speed
    BIT_RESET(GPIOB_PUPDR, GPIOB_PIN_14_NoPullUpPullDown); // PUPDR14: No pull
    BIT_SET(GPIOB_BSRR, GPIOB_PIN_14_ResetOut);
}

// Button 1 PB12
void Button1_input (void) {
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE12_0); 
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE12_1); 
    
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD12_0); 
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD12_1); 
    SET_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD12_0); 
}

// Button 2 PB15
void Button2_input (void) {
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE15_0); 
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE15_1); 
    
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD15_0); 
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD15_1); 
    SET_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD15_0); 
}

// Button 3 PB9
void ButtonAndLed_input (void) {
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE9_0); 
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE9_1); 
    
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD9_0); 
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD9_1); 
    SET_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD9_1); 
}

void ButtonAndLed_output (void) {
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE9_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE9_1);
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE9_0); // MODER9: 01 (Output)

    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT9); // OTYPER9: 0 (Push-pull)

    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR9_0); 
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR9_1); 
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR9_0); // OSPEEDR9: 01 (Medium)

    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD9_0); // PUPDR9: 00 (No pull)
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD9_1); // PUPDR9: 00 (No pull)
}

*/