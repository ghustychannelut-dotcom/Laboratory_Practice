/* Доп задание ЛБ 1:

3 кнопки, 6 светодиодов, у каждой кнопки 2 функции.

Кнопка 1:
1) Короткое нажатие включает светодиоды последовательно
2) Удержание меняет порядковый номер диода для которого будет настр частота в +1

Кнопка 2:  
1) Короткое нажатие выключает диоды циклично и включ
2) Удержание изм порядк номер диода в -1

Кнопка 3:
1) Короткое нажатие изменяет частоту мигания диода в диапазоне 4 разных частот в +
3) Удержание изменяет частоту мигания диода в диапазоне 4 разных частот в -

*/

/*
инит
дефолт значения
обработка нажатия
изменение структуры
	
	изменение частоты
	вкл/выкл диодов
leds_flash
count++
*/

#include "init.c"

uint8_t led_num = 0;
uint32_t count = 0;


int main(void) {

    RCC_init();
    leds_init();
    buttons_init();

    leds led_pwr = { // leds on/off memory
        .led1 = 0,
        .led2 = 0,
        .led3 = 0,
        .led4 = 0,
        .led5 = 0,
        .led6 = 0,
    };

    leds led_frq = { // leds frequences memory
        .led1 = 0,
        .led2 = 0,
        .led3 = 0,
        .led4 = 0,
        .led5 = 0,
        .led6 = 0,
    };



    while(1) {

        button_action action = check_action(); // checking what if any button nas been pressed and for how long

        change_led(led_num, action);
        led_frq = change_frq(led_frq, action);
        led_pwr = change_pwr(led_pwr, action);
        

        leds_flash(count);

        count++;
    }
}








            /* 1 часть ЛБ 1

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

*/