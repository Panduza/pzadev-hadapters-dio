#ifndef APP_RPIPICOUSBMODBUS_H
#define APP_RPIPICOUSBMODBUS_H

#include "debug_file.h"
#include "modbus.h"
#include "gpio_file.h"

void app_RpiPicoUsbModbus_init(void);
void app_RpiPicoUsbModbus_run(void);

void declare_all_GPIO(void);
void init_all_GPIO(void);

void update_registers_init(struct modbus* modbusSlaveToUpdate);
void update_GPIOdir_registers(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate);
void update_modbus_registers_access(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate);
void update_GPIO_Registers(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate);

uint8_t modbusMyWriteRegistersCallBack(struct modbus *slave, uint16_t index);

uint16_t number_gpio(void);

#endif