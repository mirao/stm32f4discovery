/**
 * Push user button to toggle LED.
 */

#include "stm32f4xx_hal.h"

/**
 * How push button affects LED(s)
 * 0 - Push button toggles blue LED state
 * 1 - Push button turns blue LED on
 * 2 - Push button turns current LED off and next LED on (starting blue one)
 */
#define PUSH_LED_MODE 2

#define PUSH_BUTTON_GPIO_PORT GPIOA
#define PUSH_BUTTON_PIN GPIO_PIN_0
#define PUSH_GPIO_PORT_CLOCK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

#define LED_GPIO_PORT GPIOD
#define LED_PIN GPIO_PIN_15  // Blue LED LD6 for modes 0/1 (see above). Follow user manual for info about other LED pins
#define LED_GPIO_PORT_CLOCK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()

void Push_Button_Init();
void LED_Init(void);
void Error_Handler(void);
void SystemClock_Config(void);

int main(void) {
    /* Configure the system clock */
    SystemClock_Config();

    HAL_Init();
    LED_Init();
    Push_Button_Init();

#if PUSH_LED_MODE == 1
    uint8_t pinState;
#else
    uint16_t currentLed;
    uint16_t nextLed;
#if PUSH_LED_MODE == 2
    uint16_t leds[] = {GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
    uint8_t ledId = 3;  // ID of blue LED
    nextLed = leds[ledId];
    uint8_t isLEDFirst = 1;
#else
    nextLed = LED_PIN;  // Only one LED is turned on/off
#endif
#endif

    while (1) {
        // Is button pressed?
        if (GPIO_PIN_SET == HAL_GPIO_ReadPin(PUSH_BUTTON_GPIO_PORT, PUSH_BUTTON_PIN)) {
#if PUSH_LED_MODE == 1
            pinState = GPIO_PIN_SET;
        } else {
            pinState = GPIO_PIN_RESET;
        }
        // Turn LED on or off
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, pinState);
#else
            currentLed = nextLed;
            // Toggle LED state
            HAL_GPIO_TogglePin(LED_GPIO_PORT, currentLed);
#if PUSH_LED_MODE == 2
            if (isLEDFirst) {
                isLEDFirst = 0;
            } else {
                ledId = (ledId + 1) % 4;
                nextLed = leds[ledId];
                // Toggle LED state
                HAL_GPIO_TogglePin(LED_GPIO_PORT, nextLed);
            }
#endif
            // Wait a moment to give user chance to release button
            HAL_Delay(100);
        }
#endif
    }
}

/**
 * It handles System tick timer and allows correct working HAL_Delay()
 */
void SysTick_Handler(void) {
    HAL_IncTick();
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

    /** Configure the main internal regulator output voltage */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        Error_Handler();
    }
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
    PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        Error_Handler();
    }
}

void Error_Handler(void) {}

/* Initialize user push button */
void Push_Button_Init(void) {
    PUSH_GPIO_PORT_CLOCK_ENABLE();  // Enable GPIO Port Clock
}

/* Initialize LED */
void LED_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    LED_GPIO_PORT_CLOCK_ENABLE();  // Enable GPIO Port Clock

    // Configure GPIO pins for all user LEDs
    GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}