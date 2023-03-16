// MACROS
#define LIGHTMODBUS_SLAVE_FULL
#define LIGHTMODBUS_DEBUG
#define LIGHTMODBUS_IMPL

#ifndef REG_COUNT
#define REG_COUNT 250
#endif
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
// static ModbusSlave slave[5];
static ModbusSlave slave;
static int INSTANCE_COUNTER = 0;

static uint16_t registers[REG_COUNT];
static uint16_t inputRegisters[REG_COUNT];
static uint8_t coils[REG_COUNT / 8];
static uint8_t discreteInputs[REG_COUNT / 8];

static uint16_t registers[REG_COUNT];
static uint16_t inputRegisters[REG_COUNT];
static uint8_t coils[REG_COUNT / 8];
static uint8_t discreteInputs[REG_COUNT / 8];

//goes in this callback when a frame is received
ModbusError registerCallback(const ModbusSlave *slaveID, const ModbusRegisterCallbackArgs *args, ModbusRegisterCallbackResult *result){

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
                    break;
                case MODBUS_INPUT_REGISTER:   
                    result->value = inputRegisters[args->index]; 
                    break;
                case MODBUS_COIL:
                    debug("inside coil case\r\n");
                    char str1[100];
                    sprintf(str1, "GPIO number %d\r\n", args->index);
                    debug(str1);
                        // result->value = gpioConf_coil_return(args->index);
                    break;
                case MODBUS_DISCRETE_INPUT:   
                    result->value = modbusMaskRead(discreteInputs, args->index);
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
                    registers[args->index] = args->value; 
                    break;
                case MODBUS_COIL:             
                    modbusMaskWrite(coils, args->index, args->value); 
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
    if (INSTANCE_COUNTER < MAX_MODBUS_SLAVE)
    {
        __this->handle = &slave;//[INSTANCE_COUNTER];
        INSTANCE_COUNTER++;
         ModbusErrorInfo err = modbusSlaveInit(
                                (ModbusSlave*)&slave,
                                registerCallback,
                                exceptionCallback,
                                modbusDefaultAllocator,
                                modbusSlaveDefaultFunctions,
                                modbusSlaveDefaultFunctionCount);
    }
    else
    {
        debug("Cannot define another ModbusSlave\n\r");
    }
}

void* get_modbus_slave(void)
{
    return &slave;
}

void platform_modbus_usb_cdc_xfer(void)
{
    uint8_t itf;
    uint32_t count;
    static char in[256];
    static int idx = 0;
    ModbusErrorInfo err, err2;

    // connected() check for DTR bit
    // Most but not all terminal client set this when making connection
    if (tud_cdc_n_connected(MODBUS_PORT))
    {
        if (tud_cdc_n_available(MODBUS_PORT))
        {
            count = tud_cdc_n_read(MODBUS_PORT, in + idx, 256 - idx);
            idx += count;
            debug("\r\nparse");
            err = modbusParseRequestRTU(get_modbus_slave(), 0x01, in, idx);
            char str[20];
            sprintf(str, "\r\nerr=%d", err.source);
            debug(str);
            if (modbusIsOk(err))
            {
                tud_cdc_n_write(
                    MODBUS_PORT,
                    modbusSlaveGetResponse(get_modbus_slave()),
                    modbusSlaveGetResponseLength(get_modbus_slave()));
                tud_cdc_n_write_flush(MODBUS_PORT);
                memset(in, 0, 256);
                idx = 0;
            }
            err2 = modbusParseRequestRTU(get_modbus_slave(), 0x02, in, idx);
            sprintf(str, "\r\nerr2=%d", err2.source);
            debug(str);
            if (modbusIsOk(err2))
            {
                tud_cdc_n_write(
                    MODBUS_PORT,
                    modbusSlaveGetResponse(get_modbus_slave()),
                    modbusSlaveGetResponseLength(get_modbus_slave()));
                tud_cdc_n_write_flush(MODBUS_PORT);
                memset(in, 0, 256);
                idx = 0;
            }
            debug("\r\n\n\n");
        }
    }
}

