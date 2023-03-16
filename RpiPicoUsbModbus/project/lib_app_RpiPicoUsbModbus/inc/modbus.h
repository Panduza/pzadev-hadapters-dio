#ifndef MODBUS_H
#define MODBUS_H

#define LIGHTMODBUS_SLAVE

#ifndef REG_COUNT
#define REG_COUNT 250
#endif

struct modbusRegisters
{
    uint16_t holdingRegisters[REG_COUNT];
    uint16_t inputRegisters[REG_COUNT];
    uint8_t coils[REG_COUNT / 8];
    uint8_t discreteInputs[REG_COUNT / 8];
};

struct modbus
{
    void* handle;
    uint8_t adress;
    void* modbusRegister;
};

void modbus_assign_adress(struct modbus* __this, uint8_t adress);
void modbus_init(struct modbus* __this);
void printErrorInfo(void* err);

// void platform_modbus_usb_cdc_xfer(void);
void platform_modbus_usb_cdc_xfer(struct modbus* __this);
#endif