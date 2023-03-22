// MACROS
#define LIGHTMODBUS_SLAVE_FULL
#define LIGHTMODBUS_DEBUG
#define LIGHTMODBUS_IMPL

#ifndef MAX_MODBUS_SLAVE
#define MAX_MODBUS_SLAVE 5
#endif

#define MODBUS_PORT 0

#include "debug_file.h"
#include "modbus.h"
#include "lightmodbus/lightmodbus.h"
#include "tusb_config.h"
#include "tusb.h"

static ModbusSlave slave;

//goes in this callback when a frame is received
ModbusError registerCallback(const ModbusSlave *slaveID, const ModbusRegisterCallbackArgs *args, ModbusRegisterCallbackResult *result){

    struct modbus* myModbusSlave = slaveID->context;
    struct modbusRegisters* myCallBackRegister = myModbusSlave->modbusRegister;

    result->exceptionCode = MODBUS_EXCEP_NONE;

    switch (args->query)
    {
        // R/W access check
        case MODBUS_REGQ_W_CHECK:
            if (args->index < 0 && args->index >= REG_COUNT )
            {
                result->exceptionCode = MODBUS_EXCEP_ILLEGAL_ADDRESS;
            }
            // Access to coil 
            else if ((modbusMaskRead(myCallBackRegister->access_coils, args->index) == READ_ONLY) && (args->type == MODBUS_COIL) )
            {
                result->exceptionCode = MODBUS_EXCEP_ILLEGAL_VALUE;
            }
            // Access to holding
            else if ((modbusMaskRead(myCallBackRegister->access_holding, args->index) == READ_ONLY) && (args->type == MODBUS_HOLDING_REGISTER))
            {
                result->exceptionCode = MODBUS_EXCEP_ILLEGAL_ADDRESS;
            }
            
            break;
        case MODBUS_REGQ_R_CHECK:
            if (args->index < 0 && args->index >= REG_COUNT )
            {
                result->exceptionCode = MODBUS_EXCEP_ILLEGAL_ADDRESS;
            }
            break;
 
        // Read register        
        case MODBUS_REGQ_R:
            switch (args->type)
            {
                case MODBUS_HOLDING_REGISTER: 
                    // result->value = gpioConf_info_return(args->index);
                    if (args->index >= 0 && args->index < REG_COUNT)
                    {
                        result->value = myCallBackRegister->holdingRegisters[args->index];
                    }
                    break;

                case MODBUS_INPUT_REGISTER:   
                    if (args->index >= 0 && args->index < REG_COUNT)
                    {
                        result->value = myCallBackRegister->inputRegisters[args->index];
                    }
                    break;

                case MODBUS_COIL:
                    if (args->index >= 0 && args->index < REG_COUNT/8)
                    {
                        result->value = modbusMaskRead(myCallBackRegister->coils, args->index);
                    }
                    break;

                case MODBUS_DISCRETE_INPUT:   
                    result->value = modbusMaskRead((uint8_t*)myCallBackRegister->inputRegisters, args->index);
                    break;

                default:
                    debug("DEBUG : Type of register to read not recognized\r\n");
                    break;
            }
            break;
 
        // Write register
        case MODBUS_REGQ_W:
            switch (args->type)
            {
                case MODBUS_HOLDING_REGISTER: 
                    myCallBackRegister->holdingRegisters[args->index] = args->value; 
                    result->exceptionCode = myModbusSlave->modbusWriteHoldingRegisterCallback(myModbusSlave, args->index);
                    break;
                case MODBUS_COIL: 
                    if (args->index >= 0 && args->index < REG_COUNT/8)
                    {
                        modbusMaskWrite((uint8_t*)myCallBackRegister->coils, args->index, args->value); 
                        // Callback to writecoilregister 
                        result -> exceptionCode =  myModbusSlave->modbusWriteCoilRegisterCallback(myModbusSlave, args->index);
                    }
                    break;
                default:            
                    debug("DEBUG : Type of register to write not recognized \r\n")       
                    break;
            }
            break;

        default:
            debug("DEBUG: Type of query not recognized \r\n");
            break;
    }
    return MODBUS_OK;
}

ModbusError exceptionCallback(const ModbusSlave *slave,  uint8_t function, ModbusExceptionCode code){
    debug(modbusExceptionCodeStr(code)); // send the error cause to the debug
    debug("\n\r");
	return MODBUS_OK;

}

// Declaration of ModbusSlave
void modbus_init(struct modbus* __this)
{
        __this->handle = &slave;
        ModbusErrorInfo err = modbusSlaveInit(
                                &slave,
                                registerCallback,
                                exceptionCallback,
                                modbusDefaultAllocator,
                                modbusSlaveDefaultFunctions,
                                modbusSlaveDefaultFunctionCount);
    if (modbusIsOk(err))
    {
        debug("MODBUS INITIALIZATION OK\r\n");
    }
    else
    {
        debug("MODBUS INITIALIZATION NOK\r\n");
        debug(modbusErrorSourceStr(modbusGetErrorSource(err)));
        debug(modbusErrorStr(modbusGetErrorCode(err)));
    }
}

// Assign adress to a ModbusSlave
void modbus_assign_adress(struct modbus* __this, uint8_t adress)
{
    __this->adress = adress;
}

void modbus_platform_modbus_usb_cdc_xfer(struct modbus* __this)
{
    uint8_t itf;
    uint32_t count;
    static char in[256];
    static int idx = 0;
    ModbusErrorInfo err;

    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    if (tud_cdc_n_connected(MODBUS_PORT))
    {
        if (tud_cdc_n_available(MODBUS_PORT))
        {
            count = tud_cdc_n_read(MODBUS_PORT, in + idx, 256 - idx);
            idx += count;

            // modbusRegisters adress of the modbus slave pass to the Parse instruction using 
            // the *void context pointer of ModbusSlave struct
            slave.context = __this; 
            
            err = modbusParseRequestRTU(__this->handle, __this->adress, in, idx);

            if (modbusIsOk(err))
            {
                tud_cdc_n_write(
                    MODBUS_PORT,
                    modbusSlaveGetResponse(__this->handle),
                    modbusSlaveGetResponseLength(__this->handle));
                tud_cdc_n_write_flush(MODBUS_PORT);
                memset(in, 0, 256);
                idx = 0;
            }
        }
    }
}

void modbus_assign_register(struct modbus* __this, struct modbusRegisters* slaveRegister)
{
    __this->modbusRegister = slaveRegister;
}

void modbus_assign_writeCoilRegistercallback(struct modbus* __this, writeCoilRegisterCb registerWriteCoilCallBack)
{
    __this->modbusWriteCoilRegisterCallback = registerWriteCoilCallBack;
}

void modbus_assign_writeHoldingRegistercallback(struct modbus* __this, writeHoldingRegisterCb registerWriteHoldingCallBack)
{
    __this->modbusWriteHoldingRegisterCallback = registerWriteHoldingCallBack;
}

