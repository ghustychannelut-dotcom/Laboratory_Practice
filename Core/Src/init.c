#include "init.h"

typedef struct {

    uint8_t button_num;

    bool is_long;

} button_action;

typedef struct {

    uint8_t led1_state;

    uint8_t led2_state;

    uint8_t led3_state;

    uint8_t led4_state;

    uint8_t led5_state;

    uint8_t led6_state;

} led_states;


led_states get_led_states(void) {
    led_states states;
    
    states.led1_state = 0;

    states.led2_state = 0;

    states.led3_state = 0;

    states.led4_state = 0;

    states.led5_state = 0;

    states.led6_state = 0;

    return states;
}

button_action check_action(void) {

    button_action action;

    if (read_button1 == true) { // if button 1 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button1 == false) {
                break;
            }
        }

        action.button_num = 1;
        action.is_long = (i >= long_press));
    }

    else if (read_button2 == true) { // if button 2 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button1 == false) {
                break;
            }
        }

        action.button_num = 2;
        action.is_long = (i >= long_press));
    }

    else if (read_button3 == true) { // if button 3 pressed
        int i;

        for (i = 0; i < long_press; i++) {
            if (read_button1 == false) {
                break;
            }
        }

        action.button_num = 3;
        action.is_long = (i >= long_press));
    }

    else { //if no buttons pressed 

        action.button_num = 0;
        action.is_long = false;
    }

    return action;
}

void next_led_on(void);

void RCC_init(void);

void leds_init(void);

void buttons_init(void);

int leds_flash(uint32_t count);










      
      /* 1 часть ЛБ 1

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