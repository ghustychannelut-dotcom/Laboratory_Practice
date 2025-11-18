#pragma once

#include <stdint.h>
#include "../../CMSIS/Devices/Inc/system_stm32f4xx.h"
#include "../../CMSIS/Devices/Inc/stm32f429xx.h"
#include "../../CMSIS/Devices/Inc/stm32f4xx.h"
#include <stdbool.h>


// test functions
void test_leds(void); // testing LEDs and led_on led_off
void test_read_button_fixed(void); // testing read_button, led_on and led_off
void test_check_action(void); // testing check_action
void test_change_led(void);

// init functions
void RCC_init(void);
void leds_init(void);
void buttons_init(void);


extern uint32_t long_press;
extern uint8_t frq_levels;
extern uint32_t frq_step;
extern uint32_t count;
extern uint8_t led_change;
extern uint8_t led_num;

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
void led_on(uint8_t num); // работает
void led_off(uint8_t num); // работает
bool read_button(uint8_t num); // работает
button_action check_action(void); // работает
void change_led (uint8_t led_change, button_action action);
leds change_frq (leds led_frq, uint8_t led_change, button_action action);
leds change_pwr (leds led_pwr, button_action action);
void leds_flash(uint32_t count, leds led_frq, leds led_pwr);


            /* 1 часть ЛБ 1


#include <stdint.h>
#include "../../CMSIS/Devices/Inc/system_stm32f4xx.h"
#include "../../CMSIS/Devices/Inc/stm32f429xx.h"
#include "../../CMSIS/Devices/Inc/stm32f4xx.h"

#include <stdbool.h>

#define GPIOB_MODER                             *(uint32_t *)(0x40020400UL + 0x00UL)
#define GPIOB_OTYPER                            *(uint32_t *)(0x40020400UL + 0x04UL)
#define GPIOB_OSPEEDR                           *(uint32_t *)(0x40020400UL + 0x08UL)
#define GPIOB_BSRR                              *(uint32_t *)(0x40020400UL + 0x18UL)
#define GPIOB_PUPDR                             *(uint32_t*)(0x40020400UL + 0x0CUL)

#define GPIOB_PIN_14_GPOut                      0x10000000UL  // MODER14: 01 (Output)
#define GPIOB_PIN_14_PushPull                   0x00000000UL  // OTYPER14: 0 (Push-pull)
#define GPIOB_PIN_14_MEDspd                     0x01000000UL  // OSPEEDR14: 01 (Medium)
#define GPIOB_PIN_14_NoPullUpPullDown           0x00000000UL  // PUPDR14: 00 (No pull)
#define GPIOB_PIN_14_ResetOut                   0x40000000UL  // BSRR: BR14

#define BIT_SET(REG, BIT)                       ((REG) |= (BIT))
#define BIT_RESET(REG, BIT)                     ((REG) &= ~(BIT))
#define BIT_READ(REG, BIT)                      ((REG) & (BIT))


void RCC_init (void);

void Onboard_leds_init (void);

void Button1_input (void);
void Button2_input (void);
void ButtonAndLed_input (void);

void ButtonAndLed_output (void);

*/