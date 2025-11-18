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

#include "init.h"


int main(void) {

    RCC_init();
    leds_init();
    buttons_init();

    //test_leds();
    //test_read_button_fixed();
    //test_check_action();
    //test_change_led();

    leds led_pwr = { // leds on/off memory
        .led1 = 1,
        .led2 = 1,
        .led3 = 1,
        .led4 = 1,
        .led5 = 1,
        .led6 = 1,
    };

    leds led_frq = { // leds frequences memory
        .led1 = 1,
        .led2 = 1,
        .led3 = 1,
        .led4 = 1,
        .led5 = 1,
        .led6 = 1,
    };

    while(1) {

        button_action action = check_action(); // checking what if any button nas been pressed and for how long

        change_led(led_change, action); // changing the number of LED, that is set to change its frq
        
        led_frq = change_frq(led_frq, led_change, action); //changing frq of the LED chosen
        led_pwr = change_pwr(led_pwr, action); // turning on / off an LED if needed

        leds_flash(count, led_frq, led_pwr); // Turning on the needed LEDs according to the pwr structure, frq structure and current count (flashing)

        count++;
    }
}

void test_leds(void) { // testing LEDs and led_on led_off
    // Поочередно включаем все светодиоды с задержкой
    for(int i = 1; i <= 6; i++) {
        led_on(i);
        for(volatile int j = 0; j < 1000000; j++);
        led_off(i);
    }
    
    // Включаем все светодиоды одновременно
    for(int i = 1; i <= 6; i++) {
        led_on(i);
    }
    for(volatile int j = 0; j < 2000000; j++);
    
    // Выключаем все
    for(int i = 1; i <= 6; i++) {
        led_off(i);
    }
}

void test_read_button_fixed(void) { // testing read_button, led_on and led_off
    // Тестируем функцию read_button с визуальной индикацией на светодиодах
    
    while(1) {
        // Тестируем кнопку 1 (PB1) - используем LED1 (PB15)
        bool btn1 = read_button(1);
        if (btn1) {
            led_on(1);  // LED1 горит когда кнопка 1 нажата
        } else {
            led_off(1); // LED1 выключен когда кнопка 1 отпущена
        }
        
        // Тестируем кнопку 2 (PB6) - используем LED2 (PB13)  
        bool btn2 = read_button(2);
        if (btn2) {
            led_on(2);  // LED2 горит когда кнопка 2 нажата
        } else {
            led_off(2); // LED2 выключен когда кнопка 2 отпущена
        }
        
        // Тестируем кнопку 3 (PB2) - используем LED3 (PB12)
        bool btn3 = read_button(3);
        if (btn3) {
            led_on(3);  // LED3 горит когда кнопка 3 нажата
        } else {
            led_off(3); // LED3 выключен когда кнопка 3 отпущена
        }
        
        // Небольшая задержка для стабильности
        for(volatile int i = 0; i < 10000; i++);
    }
}

void test_check_action(void) { // testing check_action (is.long for instance)
    // Тестируем функцию check_action с визуальной индикацией
    
    uint32_t counter = 0;
    uint8_t last_action = 0;
    
    while(1) {
        counter++;
        
        // Проверяем действие кнопок
        button_action action = check_action();
        
        // Визуальная индикация на светодиодах:
        // LED1 - короткое нажатие кнопки 1
        // LED2 - длинное нажатие кнопки 1  
        // LED3 - короткое нажатие кнопки 2
        // LED4 - длинное нажатие кнопки 2
        // LED5 - короткое нажатие кнопки 3
        // LED6 - длинное нажатие кнопки 3
        
        // Сначала выключаем все светодиоды
        for(int i = 1; i <= 6; i++) {
            led_off(i);
        }
        
        // Включаем соответствующий светодиод в зависимости от действия
        switch(action.button_num) {
            case 1: // Кнопка 1
                if(action.is_long) {
                    led_on(2); // Длинное нажатие - LED2
                } else {
                    led_on(1); // Короткое нажатие - LED1
                }
                break;
                
            case 2: // Кнопка 2
                if(action.is_long) {
                    led_on(4); // Длинное нажатие - LED4
                } else {
                    led_on(3); // Короткое нажатие - LED3
                }
                break;
                
            case 3: // Кнопка 3
                if(action.is_long) {
                    led_on(6); // Длинное нажатие - LED6
                } else {
                    led_on(5); // Короткое нажатие - LED5
                }
                break;
                
        }
        
        // Задержка для стабильности
        for(volatile int i = 0; i < 300000; i++);
    }
}

void test_change_led(void) {
    // Простой тест change_led - все диоды выключены, только выбранный включен
    
    uint8_t test_led_change = 1; // Начинаем с LED1
    
    while(1) {
        // Проверяем действие кнопок
        button_action action = check_action();
        
        // Изменяем выбранный светодиод по длинному нажатию
        if (action.button_num == 1 && action.is_long == true) {
            test_led_change++;
            if (test_led_change > 6) test_led_change = 6;
            
            // Короткая задержка для предотвращения множественных срабатываний
            for(volatile int i = 0; i < 100000; i++);
        }
        else if (action.button_num == 2 && action.is_long == true) {
            test_led_change--;
            if (test_led_change < 1) test_led_change = 1;
            
            // Короткая задержка для предотвращения множественных срабатываний
            for(volatile int i = 0; i < 100000; i++);
        }
        
        // ВКЛЮЧАЕМ ТОЛЬКО ВЫБРАННЫЙ СВЕТОДИОД, ОСТАЛЬНЫЕ ВЫКЛЮЧАЕМ
        for(int i = 1; i <= 6; i++) {
            if (i == test_led_change) {
                led_on(i);  // Включаем только выбранный
            } else {
                led_off(i); // Выключаем все остальные
            }
        }
        
        // Минимальная задержка для стабильности
        for(volatile int i = 0; i < 1000; i++);
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