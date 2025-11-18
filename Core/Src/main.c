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

    leds led_pwr = {1, 1, 1, 1, 1, 1};
    leds led_frq = {1, 1, 1, 1, 1, 1};

    // Антидребезг для КОНКРЕТНЫХ действий
    uint32_t last_led_change_time = 0;
    uint32_t last_pwr_change_time = 0;
    const uint32_t DEBOUNCE_DELAY = 200000;

    while(1) {
        button_action action = check_action();

        // change_led - вызываем всегда, но запоминаем время только при реальных изменениях
        change_led(action);
        
        // change_pwr - вызываем всегда
        led_pwr = change_pwr(led_pwr, action);
        
        // change_frq - вызываем всегда (без антидребезга)
        led_frq = change_frq(led_frq, led_change, action);

        // Запоминаем время действий ТОЛЬКО если было реальное нажатие
        if (action.button_num != 0) {
            if (action.button_num == 1 || action.button_num == 2) {
                if (action.is_long) {
                    // Длинные нажатия для change_led
                    last_led_change_time = count;
                } else {
                    // Короткие нажатия для change_pwr  
                    last_pwr_change_time = count;
                }
            }
        }

        leds_flash(count, led_frq, led_pwr);
        count++;
        for(volatile int i = 0; i < 10000; i++);
        if (count >= 2000000) count = 0;
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
    // uint8_t last_action = 0;
    
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
    // Тестируем ТОЛЬКО функцию change_led
    
    // Инициализируем глобальную переменную
    led_change = 1;
    
    // ВЫКЛЮЧАЕМ ВСЕ СВЕТОДИОДЫ ПЕРЕД НАЧАЛОМ
    for(int i = 1; i <= 6; i++) {
        led_off(i);
    }
    
    while(1) {
        // Проверяем действие кнопок
        button_action action = check_action();
        
        // ВЫЗЫВАЕМ ФУНКЦИЮ change_led
        change_led(action);
        
        // ОЧИЩАЕМ ВСЕ СВЕТОДИОДЫ
        for(int i = 1; i <= 6; i++) {
            led_off(i);
        }
        
        // ВКЛЮЧАЕМ ТОЛЬКО ВЫБРАННЫЙ СВЕТОДИОД
        led_on(led_change);
        
        // Короткая задержка
        for(volatile int i = 0; i < 10000; i++);
    }
}

void test_leds_flash(void) {
    // Тест исправленной функции leds_flash
    
    leds led_frq = {
        .led1 = 1,  // Медленное мигание
        .led2 = 2,  // Среднее мигание  
        .led3 = 3,  // Быстрое мигание
        .led4 = 0,  // Всегда выключен (через частоту)
        .led5 = 1,  // Медленное мигание
        .led6 = 2   // Среднее мигание
    };
    
    leds led_pwr = {
        .led1 = 1,  // Включен
        .led2 = 1,  // Включен
        .led3 = 1,  // Включен
        .led4 = 1,  // Включен (но частота 0 - должен быть выключен)
        .led5 = 0,  // Выключен (принудительно)
        .led6 = 1   // Включен
    };
    
    uint32_t test_count = 0;
    
    while(1) {
        // ВЫЗЫВАЕМ ИСПРАВЛЕННУЮ ФУНКЦИЮ
        leds_flash(test_count, led_frq, led_pwr);
        
        // Увеличиваем счетчик
        test_count++;
        
        // Задержка для замедления
        for(volatile int i = 0; i < 10000; i++);
        
        // Каждые 50000 циклов меняем режим для демонстрации
        if (test_count % 50000 == 0) {
            // Меняем частоты
            led_frq.led1 = (led_frq.led1 % 3) + 1;
            led_frq.led3 = (led_frq.led3 % 3) + 1;
            led_frq.led6 = (led_frq.led6 % 3) + 1;
        }
        
        // Сбрасываем счетчик чтобы не переполнялся
        if (test_count >= 100000) {
            test_count = 0;
        }
    }
}

void test_change_frq_in_main(void) {
    leds led_frq = {1, 1, 1, 1, 1, 1}; // Все на частоте 1
    leds led_pwr = {1, 1, 1, 1, 1, 1}; // Все включены
    
    while(1) {
        button_action action = check_action();
        
        change_led(action);
        led_frq = change_frq(led_frq, led_change, action);
        
        // Индикация: показываем частоту выбранного светодиода
        for(int i = 1; i <= 6; i++) {
            if (i == led_change) {
                // Выбранный мигает с его частотой
            } else {
                // Остальные горят постоянно или выключены
                if (led_frq.led1 > 0) led_on(i); else led_off(i);
            }
        }
        
        leds_flash(count, led_frq, led_pwr);
        count++;
        for(volatile int i = 0; i < 10000; i++);
        if (count >= 2000000) count = 0;
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