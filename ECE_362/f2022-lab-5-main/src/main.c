/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An
  * @version V1.0
  * @date    Oct 10, 2022
  * @brief   ECE 362 Lab 5 Solution
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include <stdint.h>

void initb();
void initc();
void setn(int32_t pin_num, int32_t val);
int32_t readpin(int32_t pin_num);
void buttons(void);
void keypad(void);

void mysleep(void) {
    for(int n = 0; n < 1000; n++);
}

int main(void) {
    // Uncomment when most things are working
    autotest();
    
    initb();
    initc();

    // uncomment one of the loops, below, when ready
    while(1) {
        buttons();
    }

    while(1) {
        keypad();
    }

    for(;;);
}

/**
 * @brief Init GPIO port B
 *        Pin 0: input
 *        Pin 4: input
 *        Pin 8-11: output
 *
 */
void initb() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
    GPIOB -> MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER4 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9
            | GPIO_MODER_MODER10 | GPIO_MODER_MODER11); // bit clears Pin0, Pin4, Pin 8-11. sets to 00 which is input

    // sets Pin 8-11 to 01 or output
    GPIOB -> MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0);
}

/**
 * @brief Init GPIO port C
 *        Pin 0-3: inputs with internal pull down resistors
 *        Pin 4-7: outputs
 *
 */
void initc() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    // bit clears Pin 0-7. sets to 00 which is input
    GPIOC -> MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3
            | GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7);
    // sets Pin 4-7 to 01 or output
    GPIOC -> MODER |= (GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);

    // bit clears PUPDR Pin 0-3. sets to 00 which is neither pull-up/pull-down
    GPIOC -> PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3);
    // set Pin 0-3 as pull down resistors
    GPIOC -> PUPDR |= (GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1 | GPIO_PUPDR_PUPDR2_1 | GPIO_PUPDR_PUPDR3_1);
}

/**
 * @brief Set GPIO port B pin to some value
 *
 * @param pin_num: Pin number in GPIO B
 * @param val    : Pin value, if 0 then the
 *                 pin is set low, else set high
 */
void setn(int32_t pin_num, int32_t val) {
    if (val == 0)
    {
        // Turn pin_num off
        GPIOB-> BRR |= (1 << pin_num);
    }
    else
    {
        // Turn pin_num on
        GPIOB-> BSRR |= (1 << pin_num);
    }
}

/**
 * @brief Read GPIO port B pin values
 *
 * @param pin_num   : Pin number in GPIO B to be read
 * @return int32_t  : 1: the pin is high; 0: the pin is low
 */
int32_t readpin(int32_t pin_num) {
    return (GPIOB -> IDR >> pin_num) & 0x1;
}

/**
 * @brief Control LEDs with buttons
 *        Use PB0 value for PB8
 *        Use PB4 value for PB9
 *
 */
void buttons(void) {
    setn(8, readpin(0));
    setn(9, readpin(4));
}

/**
 * @brief Control LEDs with keypad
 *
 */
void keypad(void) {
    for(int i = 4; i <= 7; i++)
    {
        GPIOC -> ODR = (1 << i);
        mysleep();

        if (i == 4)
        {
            setn(11, (GPIOC->IDR & 0b1));
        }
        if (i == 5)
        {
            setn(10, GPIOC->IDR & 0b10);
        }
        if (i == 6)
        {
            setn(9, GPIOC->IDR & 0b100);
        }
        if (i == 7)
        {
            setn(8, GPIOC->IDR & 0b1000);
        }
    }
}
