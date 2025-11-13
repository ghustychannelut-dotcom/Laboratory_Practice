#include <stdint.h>
#include "../../CMSIS/Devices/Inc/system_stm32f4xx.h"
#include "../../CMSIS/Devices/Inc/stm32f429xx.h"
#include "../../CMSIS/Devices/Inc/stm32f4xx.h"


#define GPIOB_MODER                             *(uint32_t *)(0x40020400UL + 0x00UL)
#define GPIOB_OTYPER                            *(uint32_t *)(0x40020400UL + 0x04UL)
#define GPIOB_OSPEEDR                           *(uint32_t *)(0x40020400UL + 0x08UL)
#define GPIOB_BSRR                              *(uint32_t *)(0x40020400UL + 0x18UL)
#define GPIOB_PUPDR                             *(uint32_t*)(0x40020400UL + 0x0CUL)

#define GPIOB_PIN_14_GPOut                      0x10000000UL
#define GPIOB_PIN_14_PushPull                   0x4000UL
#define GPIOB_PIN_14_MEDspd                     0x10000000UL
#define GPIOB_PIN_14_NoPullUpPullDown           0x10000000UL
#define GPIOB_PIN_14_ResetOut                   0x40000000UL

#define BIT_SET(REG, BIT)                       ((REG) |= (BIT))
#define BIT_RESET(REG, BIT)                     ((REG) &= ~(BIT))
#define BIT_READ(REG, BIT)                      ((REG) & (BIT))


void RCC_init (void);

void Onboard_leds_init (void);

void Button1_input (void);
void Button2_input (void);
void ButtonAndLed_input (void);

void ButtonAndLed_output (void);