#ifndef CONF_H
#define CONF_H

/**
 * config file of 
 * firmware
 */


// LIB
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "tusb_config.h"


// MACROS
#define LIGHTMODBUS_SLAVE_FULL
#define LIGHTMODBUS_DEBUG
#define LIGHTMODBUS_IMPL

// LIGTHMODBUS LIB
#include "lightmodbus/lightmodbus.h"

#ifndef REG_COUNT
#define REG_COUNT 250
#endif


// CONSTANTS
#define UART_ID uart1
#define BAUDRATE 115200
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// DEBUG
#define debug(...) uart_puts(UART_ID, __VA_ARGS__);


static uint16_t registers[REG_COUNT];
static uint16_t inputRegisters[REG_COUNT];
static uint8_t coils[REG_COUNT / 8];
static uint8_t discreteInputs[REG_COUNT / 8];

static uint16_t registers[REG_COUNT];
static uint16_t inputRegisters[REG_COUNT];
static uint8_t coils[REG_COUNT / 8];
static uint8_t discreteInputs[REG_COUNT / 8];


// GPIO'S DECLERATION
const uint16_t GPIO_0 = 0;
const uint16_t GPIO_1 = 1;
const uint16_t GPIO_2 = 2;
const uint16_t GPIO_3 = 3;
const uint16_t GPIO_6 = 6;
const uint16_t GPIO_7 = 7;
const uint16_t GPIO_8 = 8;
const uint16_t GPIO_9 = 9;
const uint16_t GPIO_10 = 10;
const uint16_t GPIO_11 = 11;
const uint16_t GPIO_12 = 12;
const uint16_t GPIO_13 = 13;
const uint16_t GPIO_14 = 14;
const uint16_t GPIO_15 = 15;
const uint16_t GPIO_16 = 16;
const uint16_t GPIO_17 = 17;
const uint16_t GPIO_18 = 18;
const uint16_t GPIO_19 = 19;
const uint16_t GPIO_20 = 20;
const uint16_t GPIO_21 = 21;
const uint16_t GPIO_22 = 22;
const uint16_t GPIO_26 = 26;
const uint16_t GPIO_27 = 27;
const uint16_t GPIO_28 = 28;


#endif