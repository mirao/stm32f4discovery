/**
 * Blinking LEDs in circle
 */

.syntax unified
.cpu cortex-m4

.EQU RCC_BASE,        0x40023800
.EQU RCC_AHB1ENR,     RCC_BASE + 0x30 // Peripheral clock enable register
.EQU GPIOD_BASE,      0x40020C00
.EQU GPIOD_MODER,     GPIOD_BASE + 0x00 // GPIO port mode register
.EQU GPIOD_ODR,       GPIOD_BASE + 0x14 // GPIOD output data register

.EQU GPIODEN,         1 << 3 // IO port D clock enable
.EQU MODER15_OUT,     1 << 30 // For pin PD15 connected to LD6 Blue
.EQU MODER14_OUT,     1 << 28 // For pin PD14 connected to LD5 Red
.EQU MODER13_OUT,     1 << 26 // For pin PD13 connected to LD3 Orange
.EQU MODER12_OUT,     1 << 24 // For pin PD12 connected to LD4 Green

// Pins
.EQU LED_BLUE,        1 << 15
.EQU LED_RED,         1 << 14
.EQU LED_ORANGE,      1 << 13
.EQU LED_GREEN,       1 << 12
.EQU DELAY,           0x000F // How long LED lights, 15*65536 loop iterations

.global main
.type   main, %function

main:
    BL init
    // GPIOD output data register, storing bits to it turns LED on
    LDR     r2, =GPIOD_ODR
    MOV     r1, LED_GREEN // Initial LED
    MOV     r3, r1
blink:
    STRH    r1, [r2]  // Turn LED on and other LEDs off
    BL      delay     // Wait a moment
    LSL     r1, 1     // Next LED
    CMP     r1, LED_BLUE
    BLE     blink
    MOV     r1, r3    // Go back to the 1st LED
    B       blink

init:
    // Enable IO port D clock
    LDR     r0, =RCC_AHB1ENR    
    LDR     r1, [r0]            
    ORR     r1, GPIODEN
    STR     r1, [r0]

    // Configure GPIOD pins 12-15 as outputs where LEDs are connected to
    LDR     r0, =GPIOD_MODER 
    LDR     r1, =(MODER15_OUT | MODER14_OUT | MODER13_OUT | MODER12_OUT)
    STR     r1, [r0]            
    BX      lr
    
delay:
    MOVT    r0, DELAY // Set DELAY to high halfword to get DELAY*65536 iterations
1:                              
    SUBS    r0, 1 // Decrement unless DELAY is exhausted
    BNE     1b
    BX      lr // Return to blink

    .size   main, . - main
