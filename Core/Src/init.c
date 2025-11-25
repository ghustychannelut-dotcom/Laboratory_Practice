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

uint32_t long_press = 500000;
uint8_t frq_levels = 4;
uint16_t frq_step = 10000;
uint16_t count = 0;
uint8_t led_change = 2;
uint8_t led_num = 2;


// Actual initialization

void RCC_init(void) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN);
}

void leds_init(void) {
    
    // LED 1: PB15 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE15_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE15_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT15);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR15_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR15_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD15_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD15_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_15);

    // LED 2: PB13 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE13_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE13_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT13);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR13_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR13_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD13_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD13_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_13);

    // LED 3: PB12 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE12_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE12_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT12);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR12_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR12_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD12_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD12_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_12);

    // LED 4: PB5 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE5_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE5_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT5);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR5_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR5_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD5_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD5_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_5);

    // LED 5: PB3 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE3_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE3_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT3);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR3_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR3_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD3_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD3_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_3); // LED reset to 0

    // LED 6: PB4 General purpose output, push-pull, medium speed, no pull-up/pull-down
    SET_BIT(GPIOB -> MODER, GPIO_MODER_MODE4_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE4_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT4);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR4_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR4_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD4_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD4_0);
    SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_4); // LED reset to 0

}

void buttons_init(void) {
    // Button 1: PB1 - Input mode, Pull-down, Medium speed
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE1_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE1_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT1);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR1_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR1_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD1_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD1_1);
    SET_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD1_1);

    // Button 2: PB6 - Input mode, Pull-down, Medium speed
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE6_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE6_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT6);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR6_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR6_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD6_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD6_1);
    SET_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD6_1);

    // Button 3: PB2 - Input mode, Pull-down, Medium speed
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE2_0);
    CLEAR_BIT(GPIOB -> MODER, GPIO_MODER_MODE2_1);
    CLEAR_BIT(GPIOB -> OTYPER, GPIO_OTYPER_OT2);
    SET_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR2_0);
    CLEAR_BIT(GPIOB -> OSPEEDR, GPIO_OSPEEDER_OSPEEDR2_1);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD2_0);
    CLEAR_BIT(GPIOB -> PUPDR, GPIO_PUPDR_PUPD2_1);
    SET_BIT(GPIOB-> PUPDR, GPIO_PUPDR_PUPD2_1);
}

// functions

void led_on(uint8_t num) {
    switch (num) {
        case 1:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_15);
            break;

        case 2:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_13);
            break;
        
        case 3:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_12);
            break;

        case 4:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_5);
            break;

        case 5:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_3);
            break;

        case 6:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BS_4);
            break;
    }
}

void led_off(uint8_t num) {
    switch (num) {
        case 1:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_15);
            break;

        case 2:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_13);
            break;
        
        case 3:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_12);
            break;

        case 4:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_5);
            break;

        case 5:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_3);
            break;

        case 6:
            SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_4);
            break;
    }

}

bool read_button(uint8_t num) {
    
    switch (num) {
        case 1:
            return (GPIOB->IDR & GPIO_IDR_ID1) != 0;
        case 2:
            return (GPIOB->IDR & GPIO_IDR_ID6) != 0;
        case 3:
            return (GPIOB->IDR & GPIO_IDR_ID2) != 0;
        default:
            return false;
    }
}

button_action check_action(void) {

    button_action action;

    if (read_button(1) == true) {
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(1) == false) {
                break;
            }
        }

        action.button_num = 1;
        action.is_long = (i >= long_press);
    }

    else if (read_button(2) == true) {
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(2) == false) {
                break;
            }
        }

        action.button_num = 2;
        action.is_long = (i >= long_press);
    }

    else if (read_button(3) == true) {
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button(3) == false) {
                break;
            }
        }

        action.button_num = 3;
        action.is_long = (i >= long_press);
    }

    else {

        action.button_num = 0;
        action.is_long = false;
    }

    return action;
}

void change_led(button_action action) {
    if (action.button_num == 1 && action.is_long == true) {
        led_change++;
        if (led_change > 6) led_change = 6;
        
        for(volatile int i = 0; i < 100000; i++);
    }
    else if (action.button_num == 2 && action.is_long == true) {
        led_change--;
        if (led_change < 1) led_change = 1;
        
        for(volatile int i = 0; i < 100000; i++);
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
    return led_frq;
}

leds change_pwr(leds led_pwr, button_action action) {
    leds new_pwr = led_pwr;
    
    static uint8_t led_state = 0;

    if (action.button_num == 1 && !action.is_long) {
        if (led_state < 6) {
            led_state++;
        }
    }
    else if (action.button_num == 2 && !action.is_long) {
        if (led_state > 0) {
            led_state--;
        }
    }

    new_pwr.led1 = (led_state >= 1) ? 1 : 0;
    new_pwr.led2 = (led_state >= 2) ? 1 : 0;
    new_pwr.led3 = (led_state >= 3) ? 1 : 0;
    new_pwr.led4 = (led_state >= 4) ? 1 : 0;
    new_pwr.led5 = (led_state >= 5) ? 1 : 0;
    new_pwr.led6 = (led_state >= 6) ? 1 : 0;

    return new_pwr;
}

void leds_flash(uint16_t count, leds led_frq, leds led_pwr) {
    
    leds final_states;
    final_states.led1 = (led_pwr.led1 == 0) ? 0 : led_frq.led1;
    final_states.led2 = (led_pwr.led2 == 0) ? 0 : led_frq.led2;
    final_states.led3 = (led_pwr.led3 == 0) ? 0 : led_frq.led3;
    final_states.led4 = (led_pwr.led4 == 0) ? 0 : led_frq.led4;
    final_states.led5 = (led_pwr.led5 == 0) ? 0 : led_frq.led5;
    final_states.led6 = (led_pwr.led6 == 0) ? 0 : led_frq.led6;

    if (final_states.led1 == 0) {
        led_off(1);
    } else {
        uint16_t period = final_states.led1 * 100;
        if ((count % period) < (period / 2)) {
            led_on(1);
        } else {
            led_off(1);
        }
    }

    if (final_states.led2 == 0) {
        led_off(2);
    } else {
        uint16_t period = final_states.led2 * 100;
        if ((count % period) < (period / 2)) {
            led_on(2);
        } else {
            led_off(2);
        }
    }

    if (final_states.led3 == 0) {
        led_off(3);
    } else {
        uint16_t period = final_states.led3 * 100;
        if ((count % period) < (period / 2)) {
            led_on(3);
        } else {
            led_off(3);
        }
    }

    if (final_states.led4 == 0) {
        led_off(4);
    } else {
        uint16_t period = final_states.led4 * 100;
        if ((count % period) < (period / 2)) {
            led_on(4);
        } else {
            led_off(4);
        }
    }

    if (final_states.led5 == 0) {
        led_off(5);
    } else {
        uint16_t period = final_states.led5 * 100;
        if ((count % period) < (period / 2)) {
            led_on(5);
        } else {
            led_off(5);
        }
    }

    if (final_states.led6 == 0) {
        led_off(6);
    } else {
        uint16_t period = final_states.led6 * 100;
        if ((count % period) < (period / 2)) {
            led_on(6);
        } else {
            led_off(6);
        }
    }
}

      

















































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

    *(uint32_t*)(0x40020400UL + 0x18) |= 0x10000UL; // BSRR reset PB0 output

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