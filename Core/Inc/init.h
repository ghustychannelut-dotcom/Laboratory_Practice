#include <stdint.h>
#include "../../CMSIS/Devices/Inc/system_stm32f4xx.h"
#include "../../CMSIS/Devices/Inc/stm32f429xx.h"
#include "../../CMSIS/Devices/Inc/stm32f4xx.h"
#include <stdbool.h>

void RCC_init(void);

void leds_init(void);

void buttons_init(void);

int leds_flash(count);

void next_led_on();

button_action check_action(void);

led_states get_led_states(void);











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
