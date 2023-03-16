#ifndef APP_RPIPICOUSBMODBUS_H
#define APP_RPIPICOUSBMODBUS_H

#include "debug_file.h"
#include "modbus.h"
#include "gpio_file.h"

struct gpioConf GPIOapp_RpiPicoUsbModbus[28];
struct modbus MODBUSapp_RpiPicoUsbModbus1;
struct modbusRegisters modbusRegisterSlave1;

void app_RpiPicoUsbModbus_init(void);
void app_RpiPicoUsbModbus_run(void);

void declare_all_GPIO(void);
void init_all_GPIO(void);

#endif