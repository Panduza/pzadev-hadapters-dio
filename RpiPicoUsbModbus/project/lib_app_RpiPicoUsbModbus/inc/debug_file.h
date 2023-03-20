#ifndef DEBUG_FILE_H
#define DEBUG_FILE_H

#include "pico/stdlib.h"
#include <stdlib.h>
#include <stdio.h>

// CONSTANTS
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define BAUDRATE 115200
#define UART_ID uart1

// DEBUG
#define debug(...) uart_puts(UART_ID, __VA_ARGS__);
// #define debug(...);

void uart_initialization_test(void);

#endif