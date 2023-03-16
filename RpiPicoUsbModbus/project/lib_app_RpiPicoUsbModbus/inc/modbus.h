#ifndef MODBUS_H
#define MODBUS_H

#define LIGHTMODBUS_SLAVE

struct modbus
{
    void* handle;
    int buff_in[255];
    int idx_buff_int;
};

void* get_modbus_slave(void);
// void modbus_init(void* slaveName);
void modbus_init(struct modbus* __this);
void printErrorInfo(void* err);
void platform_modbus_usb_cdc_xfer(void);
#endif