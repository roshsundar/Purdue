/**
  ******************************************************************************
  * @file    main.c
  * @author  Weili An
  * @version V1.0
  * @date    Oct 17, 2022
  * @brief   ECE 362 Lab 6 Student template
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include <stdint.h>

void initc();
void initb();
void togglexn(GPIO_TypeDef *port, int n);
void init_exti();
void set_col(int col);
void SysTick_Handler();
void init_systick();
void adjust_priorities();

extern void nano_wait(int);

volatile int current_col = 1;

int main(void) {
    // Uncomment when most things are working
    autotest();
    
    initb();
    initc();
    init_exti();
    init_systick();
    adjust_priorities();

    // Slowly blinkingXTI_PR_PR0 to the EXTI_PR
    for(;;) {
        togglexn(GPIOC, 9);
        nano_wait(500000000);
    }
}

/**
 * @brief Init GPIO port C
 *        PC0-PC3 as input pins with the pull down resistor enabled
 *        PC4-PC9 as output pins
 * 
 */
void initc() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    // bit clears Pin 0-9. sets to 00 which is input
    GPIOC -> MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER1 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3| GPIO_MODER_MODER4
            | GPIO_MODER_MODER5 | GPIO_MODER_MODER6 | GPIO_MODER_MODER7 | GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    // sets Pin 4-9 to 01 or output
    GPIOC -> MODER |= (GPIO_MODER_MODER4_0 | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0
            | GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);

    // bit clears PUPDR Pin 0-3. sets to 00 which is neither pull-up/pull-down
    GPIOC -> PUPDR &= ~(GPIO_PUPDR_PUPDR0 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3);
    // set Pin 0-3 as pull down resistors
    GPIOC -> PUPDR |= (GPIO_PUPDR_PUPDR0_1 | GPIO_PUPDR_PUPDR1_1 | GPIO_PUPDR_PUPDR2_1 | GPIO_PUPDR_PUPDR3_1);
}

/**
 * @brief Init GPIO port B
 *        PB0, PB2, PB3, PB4 as input pins
 *          enable pull down resistor on PB2 and PB3
 *        PB8-PB11 as output pins
 * 
 */
void initb() {
    RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB -> MODER &= ~(GPIO_MODER_MODER0 | GPIO_MODER_MODER2 | GPIO_MODER_MODER3 | GPIO_MODER_MODER4 | GPIO_MODER_MODER8
            | GPIO_MODER_MODER9 |GPIO_MODER_MODER10 | GPIO_MODER_MODER11); // sets to 00 which is input

    // sets to 01 or output
    GPIOB -> MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0);

    // sets to 00 which is neither pull-up/pull-down
    GPIOB -> PUPDR &= ~(GPIO_PUPDR_PUPDR2 | GPIO_PUPDR_PUPDR3);
    // set as pull down resistors
    GPIOB -> PUPDR |= (GPIO_PUPDR_PUPDR2_1 | GPIO_PUPDR_PUPDR3_1);
}

/**
 * @brief Change the ODR value from 0 to 1 or 1 to 0 for a specified 
 *        pin of a port.
 * 
 * @param port : The passed in GPIO Port
 * @param n    : The pin number
 */
void togglexn(GPIO_TypeDef *port, int n) {
    port -> ODR ^= (1 << n);
}

//==========================================================
// Write the EXTI interrupt handler for pins 0 and 1 below.
// Copy the name from startup/startup_stm32.s, create a label
// of that name below, declare it to be global, and declare
// it to be a function.
// It acknowledge the pending bit for pin 0, and it should
// call togglexn(GPIOB, 8).
void EXTI0_1_IRQHandler(){
    EXTI ->PR = EXTI_PR_PR0;
    togglexn(GPIOB, 8);
}

//==========================================================
// Write the EXTI interrupt handler for pins 2-3 below.
// It should acknowledge the pending bit for pin2, and it
// should call togglexn(GPIOB, 9).
void EXTI2_3_IRQHandler(){
    EXTI -> PR = EXTI_PR_PR2;
    togglexn(GPIOB, 9);
}

//==========================================================
// Write the EXTI interrupt handler for pins 4-15 below.
// It should acknowledge the pending bit for pin4, and it
// should call togglxn(GPIOB, 10).
void EXTI4_15_IRQHandler(){
    EXTI -> PR = EXTI_PR_PR4;
    togglexn(GPIOB, 10);
}


/**
 * @brief Follow lab manual section 4.4 to initialize EXTI
 *        (1-2) Enable the SYSCFG subsystem, and select Port B for
 *            pins 0, 2, 3, and 4.
 *        (3) Configure the EXTI_RTSR register so that an EXTI
 *            interrupt is generated on the rising edge of
 *            pins 0, 2, 3, and 4.
 *        (4) Configure the EXTI_IMR register so that the EXTI
 *            interrupts are unmasked for pins 2, 3, and 4.
 *        (5) Enable the three interupts for EXTI pins 0-1, 2-3 and
 *            4-15. Don't enable any other interrupts.
 */
void init_exti() {
    RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGCOMPEN;
    SYSCFG -> EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PB | SYSCFG_EXTICR1_EXTI2_PB | SYSCFG_EXTICR1_EXTI3_PB;
    SYSCFG -> EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PB;

    EXTI -> RTSR |= EXTI_RTSR_TR0 | EXTI_RTSR_TR2 | EXTI_RTSR_TR3 | EXTI_RTSR_TR4;

    EXTI -> IMR |= EXTI_IMR_MR0 | EXTI_IMR_MR2 | EXTI_IMR_MR3 | EXTI_IMR_MR4;

    NVIC_EnableIRQ(EXTI0_1_IRQn);
    NVIC_EnableIRQ(EXTI2_3_IRQn);
    NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/**
 * @brief For the keypad pins, 
 *        Set the specified column level to logic "high.
 *        Set the other three three columns to logic "low".
 * 
 * @param col 
 */
void set_col(int col) {
    GPIOC -> ODR &= ~(GPIO_ODR_4 | GPIO_ODR_5 | GPIO_ODR_6 | GPIO_ODR_7);
    GPIOC -> ODR = (1 << 8) >> col;
}

/**
 * @brief The ISR for the SysTick interrupt.
 * 
 */
void SysTick_Handler() {

    int rows = GPIOC->IDR & 0xF;
    if (current_col == 1 && (rows & 0b1000))
    {
        togglexn(GPIOB, 8);
    }
    if (current_col == 2 && (rows & 0b0100))
    {
        togglexn(GPIOB, 9);
    }
    if (current_col == 3 && (rows & 0b0010))
    {
        togglexn(GPIOB, 10);
    }
    if (current_col == 4 && (rows & 0b0001))
    {
        togglexn(GPIOB, 11);
    }

    if (current_col == 4)
    {
        current_col = 1;
    }
    else
    {
        current_col++;
    }

    set_col(current_col);
}

/**
 * @brief Enable the SysTick interrupt to occur every 1/16 seconds.
 * 
 */
void init_systick() {
    // 6MHz / (RVR + 1) = 16
    SysTick -> LOAD = 375000 - 1;

    SysTick -> CTRL |= 0x3;
}

/**
 * @brief Bonus question
 *        Set the priority for EXTI pins 2-3 interrupt to 192.
 *        Set the priority for EXTI pins 4-15 interrupt to 128.
 *        Do not adjust the priority for any other interrupts.
 * 
 */
void adjust_priorities() {

}
