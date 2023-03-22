#ifndef MODBUS_H
#define MODBUS_H

#define LIGHTMODBUS_SLAVE

#ifndef REG_COUNT
#define REG_COUNT 250
#endif

#define READ_ONLY 0
#define READ_WRITE 1

struct modbus;

typedef uint8_t (*writeCoilRegisterCb)(struct modbus* slave, uint16_t index);
typedef uint8_t (*writeHoldingRegisterCb)(struct modbus* slave, uint16_t index);

struct modbusRegisters
{
    uint16_t holdingRegisters[REG_COUNT];
    uint16_t inputRegisters[REG_COUNT];
    uint8_t coils[REG_COUNT / 8];
    uint8_t discreteInputs[REG_COUNT / 8];
    uint8_t access_coils[REG_COUNT / 8]; // 0 = RO, 1 = RW
    uint8_t access_holding[REG_COUNT/8]; // 0 = RO, 1 = RW
};

struct modbus
{
    void* handle;
    uint8_t adress;
    struct modbusRegisters* modbusRegister;
    writeCoilRegisterCb modbusWriteCoilRegisterCallback; 
    writeHoldingRegisterCb modbusWriteHoldingRegisterCallback;

    void* context;
};

void modbus_assign_adress(struct modbus* __this, uint8_t adress);
void modbus_assign_register(struct modbus* __this, struct modbusRegisters* slaveRegister);
void modbus_init(struct modbus* __this);
void modbus_platform_modbus_usb_cdc_xfer(struct modbus* __this);
void modbus_assign_writeCoilRegistercallback(struct modbus* __this, writeCoilRegisterCb registercallback);
void modbus_assign_writeHoldingRegistercallback(struct modbus* __this, writeHoldingRegisterCb registerWriteHoldingCallBack);
#endif