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
#include "gpio_file.h"
#include "lightmodbus/lightmodbus.h"
#include "tusb_config.h"
#include "tusb.h"

// // Faire en sorte de pouvoir allouer 5 modbus slave
static ModbusSlave slave;

//goes in this callback when a frame is received
ModbusError registerCallback(const ModbusSlave *slaveID, const ModbusRegisterCallbackArgs *args, ModbusRegisterCallbackResult *result){

    struct modbusRegisters* myCallBackRegister = slaveID->context;

    // DEBUG
    char str[1024];
    sprintf(str,"Register query: %s\r\nType query: %s\r\n@: %d\r\nValue: %d\r\nFunction: %d\r\n\n",
        modbusRegisterQueryStr(args->query),
        modbusDataTypeStr(args->type),
		args->index,
		(uint)args->value,
		args->function
	);
    debug(str);

    switch (args->query)
    {
        // R/W access check
        case MODBUS_REGQ_R_CHECK:
            result->exceptionCode = ( args->index >= 0 && args->index < REG_COUNT ) ? MODBUS_EXCEP_NONE : MODBUS_EXCEP_ILLEGAL_ADDRESS;
            break;
        case MODBUS_REGQ_W_CHECK:
            result->exceptionCode = ( args->index >= 0 && args->index < REG_COUNT ) ? MODBUS_EXCEP_NONE : MODBUS_EXCEP_ILLEGAL_ADDRESS;
            break;
 
        // Read register        
        case MODBUS_REGQ_R:
            switch (args->type)
            {
                case MODBUS_HOLDING_REGISTER: 
                    // result->value = gpioConf_info_return(args->index);
                    if (args->index >= 0 && args->index < REG_COUNT)
                    {
                        result->value = *(myCallBackRegister->holdingRegisters + args->index); 
                    }
                    break;

                case MODBUS_INPUT_REGISTER:   
                    if (args->index >= 0 && args->index < REG_COUNT)
                    {
                        result->value = *(myCallBackRegister->inputRegisters + args->index); 
                    }
                    break;

                case MODBUS_COIL:
                    debug("inside coil case\r\n");
                    char str1[100];
                    sprintf(str1, "GPIO number %d\r\n", args->index);
                    debug(str1);
                        result->value = *(myCallBackRegister->coils + args->index); 
                    break;

                case MODBUS_DISCRETE_INPUT:   
                    // result->value = modbusMaskRead(discreteInputs, args->index);
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
                    *(myCallBackRegister->holdingRegisters + args->index) = args->value; 
                    break;
                case MODBUS_COIL:             
                    // modbusMaskWrite(coils, args->index, args->value); 
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
    char exceptionInfo[15];
    debug("in error register callback\r\n");
    debug(modbusExceptionCodeStr(code)); // send the error cause to the debug
	return MODBUS_OK;

}

// Check if modbus is initialized
void printErrorInfo(void* error)
{
    ModbusErrorInfo* err = (ModbusErrorInfo*)error;
    if (modbusIsOk(*err))
    {
        debug("MODBUS INITIALIZATION OK\r\n");
    }
    else
    {
        debug("MODBUS INITIALIZATION NOK\r\n");
        debug(modbusErrorSourceStr(modbusGetErrorSource(*err)));
        debug(modbusErrorStr(modbusGetErrorCode(*err)));
    }
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
        printErrorInfo(&err);
}

// Assign adress to a ModbusSlave
void modbus_assign_adress(struct modbus* __this, uint8_t adress)
{
    __this->adress = adress;
}

// void platform_modbus_usb_cdc_xfer(void)
// {
//     uint8_t itf;
//     uint32_t count;
//     static char in[256];
//     static int idx = 0;
//     ModbusErrorInfo err;

//     // connected() check for DTR bit
//     // Most but not all terminal client set this when making connection
//     if (tud_cdc_n_connected(MODBUS_PORT))
//     {
//         if (tud_cdc_n_available(MODBUS_PORT))
//         {
//             count = tud_cdc_n_read(MODBUS_PORT, in + idx, 256 - idx);
//             idx += count;
//             err = modbusParseRequestRTU(&slave, 0x01, in, idx);

//             if (modbusIsOk(err))
//             {
//                 tud_cdc_n_write(
//                     MODBUS_PORT,
//                     modbusSlaveGetResponse(&slave),
//                     modbusSlaveGetResponseLength(&slave));
//                 tud_cdc_n_write_flush(MODBUS_PORT);
//                 memset(in, 0, 256);
//                 idx = 0;
//             }
//         }
//     }
// }

void platform_modbus_usb_cdc_xfer(struct modbus* __this)
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
            slave.context = __this->modbusRegister;
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

void modbus_assign_register(struct modbus* __this, struct modbusRegisters* registre)
{
    __this->modbusRegister = registre;
}

