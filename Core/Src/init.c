#include "init.h"

void RCC_init (void) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN)
}

// green PB0 blue PB7 red PB14



void onboard_leds_init (void) {

// green PB0 ручками

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

SET_BIT(GPIOB -> BSRR, GPIO_BSRR_BR_7); // // BSRR reser PB7 output


// red led PB14 через собственные директивы

BIT_SET(GPIOB_MODER, GPIOB_PIN_14_GPOut);
BIT_SET(GPIOB_OTYPER, GPIOB_PIN_14_PushPull);
BIT_SET(GPIOB_OSPEEDR, GPIOB_PIN_14_MEDspd);
BIT_RESET(GPIOB_PUPDR, GPIOB_PIN_14_NoPullUpPullDown);
BIT_RESET(GPIOB_BSRR, GPIOB_PIN_14_ResetOut);

}




void button1_input (void);
void button2_input (void);
void button3_input (void);

void led4_output (void);





















void GPIO_init (void) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN);
}

void GPIO_init_led_pb7_blue (void)
{
    *(uint32_t *)(0x40020400UL + 0x00UL) |= 0x4000UL;
    *(uint32_t *)(0x40020400UL + 0x04UL) |= 0x00UL;
    *(uint32_t *)(0x40020400UL + 0x08UL) |= 0x4000UL;
    *(uint32_t *)(0x40020400UL + 0x18UL) |= 0x800000UL;
}

void GPIO_init_led_pb14_red (void)
{
    BIT_SET(GPIOB_MODER, GPIO_PIN_OUT_14);
    BIT_SET(GPIOB_OTYPER, GPIO_OFF);
    BIT_SET(GPIOB_OSPEEDR, GPIO_PIN_MED_14);
    BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);
}

void GPIO_init_led_pb0_green (void)
{
   SET_BIT(GPIOB->MODER, GPIO_MODER_MODE0_0);
   CLEAR_BIT(GPIOB->OTYPER,GPIO_OTYPER_OT_0);
   SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDER_OSPEEDR0_0);
   SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);
}

