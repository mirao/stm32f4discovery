/**
 * Blinks LED6 every second
 */

#include "stm32f4xx_hal.h"

#define LED_GPIO_PORT GPIOD
#define LED_PIN GPIO_PIN_15 // Blue LED LD6. Follow user manual for info about other LED pins
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

/* Initialize LED */
void LED_Init() {

    GPIO_InitTypeDef GPIO_InitStruct;
    
    LED_GPIO_CLK_ENABLE(); // Enable GPIO Port Clock

    // Configure GPIO pins for all user LEDs
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct); 
}

int main(void) {
    HAL_Init();
    LED_Init();

    while (1) {
        HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN); // Toggle LED state
        HAL_Delay(1000); // Wait 1 sec
    }
}


/**
 * It handles System tick timer
 */
void SysTick_Handler(void)
{
    // Feel free to uncomment the next two lines to get 10 times faster blinking

    // extern HAL_TickFreqTypeDef uwTickFreq;
    // uwTickFreq = HAL_TICK_FREQ_100HZ;
    
    HAL_IncTick();
}