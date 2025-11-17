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

    test_all_working_leds();
    //test_led4_only();
    //test_leds();
    //test_buttons_direct();
    //test_read_button_fixed();

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

void test_led5_blink(void) {
    // Используем LED5 (PB3) вместо LED4
    
    while(1) {
        // Включаем LED5
        GPIOB->BSRR = GPIO_BSRR_BS_3;
        for(volatile int i = 0; i < 1000000; i++);
        
        // Выключаем LED5
        GPIOB->BSRR = GPIO_BSRR_BR_3;
        for(volatile int i = 0; i < 1000000; i++);
    }
}

void test_all_working_leds(void) {
    // Тестируем все рабочие светодиоды (1,2,3,5,6)
    
    uint8_t working_leds[] = {1, 2, 3, 5, 6};
    uint8_t current_led = 0;
    
    while(1) {
        // Включаем текущий светодиод
        led_on(working_leds[current_led]);
        
        // Ждем 1.5 секунды
        for(volatile int i = 0; i < 1500000; i++);
        
        // Выключаем
        led_off(working_leds[current_led]);
        
        // Следующий светодиод
        current_led++;
        if (current_led >= 5) current_led = 0;
        
        // Короткая пауза 0.5 секунды
        for(volatile int i = 0; i < 500000; i++);
    }
}

void test_leds(void) {
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

void test_simple_guaranteed(void) {
    // Максимально простой тест с гарантированным миганием
    
    uint32_t counter = 0;
    
    while(1) {
        counter++;
        
        // ОЧЕНЬ ПРОСТАЯ логика мигания LED4
        if (counter < 500000) {
            led_on(4);  // Горит
        } else {
            led_off(4); // Не горит
        }
        
        // Сбрасываем счетчик чтобы мигать
        if (counter >= 1000000) {
            counter = 0;
        }
        
        // Кнопки управляют LED1-3
        if (read_button(1)) led_on(1); else led_off(1);
        if (read_button(2)) led_on(2); else led_off(2);
        if (read_button(3)) led_on(3); else led_off(3);
        
        // Минимальная задержка
        for(volatile int i = 0; i < 1000; i++);
    }
}

void test_buttons_direct(void) {
    // Настраиваем светодиоды как выходы (если еще не настроены)
    // LED1: PB15, LED2: PB13, LED3: PB12, LED4: PB5, LED5: PB3, LED6: PB4
    
    // Бесконечный цикл проверки кнопок
    while(1) {
        // Читаем состояние кнопок напрямую из регистра IDR
        
        // Кнопка 1: PB1 - при нажатии = 0 (pull-up)
        if ((GPIOB->IDR & GPIO_IDR_ID1) == 0) {
            // Кнопка нажата - включаем LED1 (PB15)
            GPIOB->BSRR = GPIO_BSRR_BS_15;
        } else {
            // Кнопка отпущена - выключаем LED1 (PB15)
            GPIOB->BSRR = GPIO_BSRR_BR_15;
        }
        
        // Кнопка 2: PB6 - при нажатии = 0 (pull-up)
        if ((GPIOB->IDR & GPIO_IDR_ID6) == 0) {
            // Кнопка нажата - включаем LED2 (PB13)
            GPIOB->BSRR = GPIO_BSRR_BS_13;
        } else {
            // Кнопка отпущена - выключаем LED2 (PB13)
            GPIOB->BSRR = GPIO_BSRR_BR_13;
        }
        
        // Кнопка 3: PB2 - при нажатии = 0 (pull-up)
        if ((GPIOB->IDR & GPIO_IDR_ID2) == 0) {
            // Кнопка нажата - включаем LED3 (PB12)
            GPIOB->BSRR = GPIO_BSRR_BS_12;
        } else {
            // Кнопка отпущена - выключаем LED3 (PB12)
            GPIOB->BSRR = GPIO_BSRR_BR_12;
        }
        
        // LED4 (PB3) мигает как индикатор работы программы
        static uint32_t counter = 0;
        counter++;
        if ((counter % 1000000) == 0) {
            GPIOB->BSRR = GPIO_BSRR_BS_3;  // Включить LED4
        } else if ((counter % 1000000) == 500000) {
            GPIOB->BSRR = GPIO_BSRR_BR_3;  // Выключить LED4
        }
        
        // Небольшая задержка
        for(volatile int i = 0; i < 10000; i++);
    }
}

void test_read_button(void) {
    // Тестируем функцию read_button с визуальной индикацией
    
    while(1) {
        // Тестируем кнопку 1 (PB1)
        bool btn1 = read_button(1);
        if (btn1) {
            led_on(1);  // LED1 горит когда кнопка 1 нажата
        } else {
            led_off(1); // LED1 выключен когда кнопка 1 отпущена
        }
        
        // Тестируем кнопку 2 (PB6)  
        bool btn2 = read_button(2);
        if (btn2) {
            led_on(2);  // LED2 горит когда кнопка 2 нажата
        } else {
            led_off(2); // LED2 выключен когда кнопка 2 отпущена
        }
        
        // Тестируем кнопку 3 (PB2)
        bool btn3 = read_button(3);
        if (btn3) {
            led_on(3);  // LED3 горит когда кнопка 3 нажата
        } else {
            led_off(3); // LED3 выключен когда кнопка 3 отпущена
        }
        
        // LED4 мигает - индикатор что программа работает
        static uint32_t counter = 0;
        counter++;
        if ((counter % 1000000) == 0) {
            led_on(4);
        } else if ((counter % 1000000) == 500000) {
            led_off(4);
        }
        
        // Небольшая задержка
        for(volatile int i = 0; i < 10000; i++);
    }
}


void test_led4_only(void) {
    // Тестируем только LED4 (PB5)
    
    while(1) {
        // Включаем LED4
        led_on(4);
        for(volatile int i = 0; i < 1000000; i++);
        
        // Выключаем LED4  
        led_off(4);
        for(volatile int i = 0; i < 1000000; i++);
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