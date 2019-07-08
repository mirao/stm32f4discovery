/**
 * Turn blue LED on when push button is pressed
 */

.syntax unified
.cpu cortex-m4

.EQU PERIPH_BITBAND_REGION_START, 0x40000000
.EQU PERIPH_BITBAND_ALIAS_START, 0x42000000

.EQU RCC_BASE,        0x40023800
.EQU RCC_AHB1ENR,     RCC_BASE + 0x30 // Peripheral clock enable register

.EQU GPIOAEN_BIT,     0 // IO port A clock enable to allow push button 
.EQU GPIODEN_BIT,     3 // IO port D clock enable to allow user LEDs

.EQU RCC_AHB1ENR_GPIOAEN, PERIPH_BITBAND_ALIAS_START + (RCC_AHB1ENR - PERIPH_BITBAND_REGION_START) * 32 + GPIOAEN_BIT * 4 // Bit-band alias to GPIOAEN bit
.EQU RCC_AHB1ENR_GPIODEN, PERIPH_BITBAND_ALIAS_START + (RCC_AHB1ENR - PERIPH_BITBAND_REGION_START) * 32 + GPIODEN_BIT * 4 // Bit-band alias to GPIODEN bit

.EQU GPIOA_BASE,      0x40020000
.EQU GPIOA_IDR,       GPIOA_BASE + 0x10 // GPIOA input data register

.EQU GPIOD_BASE,      0x40020C00
.EQU GPIOD_MODER,     GPIOD_BASE + 0x00 // GPIOD port mode register
.EQU GPIOD_ODR,       GPIOD_BASE + 0x14 // GPIOD output data register

.EQU MODER15_OUT,     1 << (LED_BLUE * 2) // Configure output (1) for pin PD15 connected to blue LED
.EQU LED_BLUE,        15 // Blue LED data output bit

.global main
.type   main, %function

main:
    BL init

    LDR     r0, =GPIOA_IDR // Push button input register
    LDR     r1, =GPIOD_ODR // GPIOD output data register, storing bit 0/1 turns LED off/on

// Poll push button state    
readButton:
    // Read state of push button
    LDR     r2, [r0]
    AND     r2, 1

    LSL     r2, LED_BLUE // Set LED's output bit off/on depending of push button state
    STRH    r2, [r1] // Turn LED off/on
    B readButton

init:
    MOV     r1, 1
    // Enable IO port A clock
    LDR     r0, =RCC_AHB1ENR_GPIOAEN
    STR     r1, [r0]
    // Enable IO port D clock
    LDR     r0, =RCC_AHB1ENR_GPIODEN
    STR     r1, [r0]

    // Configure GPIOD pin 15 as output for blue LED
    LDR     r0, =GPIOD_MODER 
    LDR     r1, =MODER15_OUT
    STR     r1, [r0]            
    BX      lr
    
    .size   main, . - main
