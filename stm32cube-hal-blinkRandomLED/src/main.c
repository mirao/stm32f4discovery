/**
 * Blinks random LED
 */

#include "stm32f4xx_hal.h"

#define LED_GPIO_PORT GPIOD

RNG_HandleTypeDef hrng;  // RNG definition

void Error_Handler(void);
void SystemClock_Config(void);
void LED_Init(void);
void RNG_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();  // Needed for correct working of RNG
    LED_Init();
    RNG_Init();

    uint16_t leds[] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};

    uint16_t nextLed, lastLed = 0;
    while (1) {
        uint32_t randomNum;
        // Select a random LED, different from last one turned on
        while (HAL_RNG_GenerateRandomNumber(&hrng, &randomNum),
               (nextLed = leds[randomNum % 4]) == lastLed) {
        }
        lastLed = nextLed;
        HAL_GPIO_TogglePin(LED_GPIO_PORT, nextLed);  // Turn LED on
        HAL_Delay(1000);                             // Wait 1 sec
        HAL_GPIO_TogglePin(LED_GPIO_PORT, nextLed);  // Turn LED off
        HAL_Delay(1000);                             // Wait 1 sec
    }
}

/* Initialize LED */
void LED_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    __HAL_RCC_GPIOD_CLK_ENABLE();  // Enable GPIO Port Clock

    // Configure GPIO pins for all user LEDs
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

/* Overriden method used by HAL_RNG_Init() */
void HAL_RNG_MspInit(RNG_HandleTypeDef* rngHandle) {
    if (rngHandle->Instance == RNG) {
        __HAL_RCC_RNG_CLK_ENABLE();
    }
}

/* Initialize random generator */
void RNG_Init(void) {
    hrng.Instance = RNG;
    HAL_RNG_Init(&hrng);
}

/**
 * It handles System tick timer
 */
void SysTick_Handler(void) {
    // Feel free to uncomment the next two lines to get 10 times faster blinking

    // extern HAL_TickFreqTypeDef uwTickFreq;
    // uwTickFreq = HAL_TICK_FREQ_100HZ;

    HAL_IncTick();
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 50;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {}
