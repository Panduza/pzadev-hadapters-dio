// include config file
#include "app_RpiPicoUsbModbus.h"

#define LED_PIN 25
#define SIZE_GPIO 28
#define GPIO_DIR_VALUE_MEMORY_EMPLACEMENT 10

struct gpioConf GPIOapp_RpiPicoUsbModbus1[SIZE_GPIO] = {0};
struct modbus MODBUSapp_RpiPicoUsbModbus1 = {0};
struct modbusRegisters modbusRegisterSlave1 = {0};

void app_RpiPicoUsbModbus_init(void)
{
    stdio_init_all();
        
    uart_initialization_test();

    // Declare and init all GPIO
    declare_all_GPIO();
    init_all_GPIO();

    // Declare, assign adress, register, callback to a modbus slave
    modbus_init(&MODBUSapp_RpiPicoUsbModbus1);
    modbus_assign_adress(&MODBUSapp_RpiPicoUsbModbus1, 0x01);
    modbus_assign_register(&MODBUSapp_RpiPicoUsbModbus1, &modbusRegisterSlave1);
    modbus_assign_callback(&MODBUSapp_RpiPicoUsbModbus1, modbusMyWriteRegistersCallBack);
    MODBUSapp_RpiPicoUsbModbus1.context = GPIOapp_RpiPicoUsbModbus1; // Link MOBDUSapp_RpiPicoUsbModbus1 with GPIOapp_RpiPicoUsbModbus1
    
    // Initialize the 4 first holding registers to defined values
    update_registers_init(&MODBUSapp_RpiPicoUsbModbus1);

    //Initialize LED in output, active state
    gpioConf_change_dir(&GPIOapp_RpiPicoUsbModbus1[LED_PIN], GPIO_OUT);
    gpioConf_change_output_state(&GPIOapp_RpiPicoUsbModbus1[LED_PIN], 1);

}

void app_RpiPicoUsbModbus_run(void)
{
        update_GPIOdir_registers(&MODBUSapp_RpiPicoUsbModbus1, GPIOapp_RpiPicoUsbModbus1);
        update_modbus_registers_access(&MODBUSapp_RpiPicoUsbModbus1, GPIOapp_RpiPicoUsbModbus1);
        update_GPIO_Registers(&MODBUSapp_RpiPicoUsbModbus1, GPIOapp_RpiPicoUsbModbus1);
        modbus_platform_modbus_usb_cdc_xfer(&MODBUSapp_RpiPicoUsbModbus1);
}

void declare_all_GPIO(void){
    debug("GPIO DECLARATION\r\n");
    for (int i = 0; i< SIZE_GPIO; i++){
        GPIOapp_RpiPicoUsbModbus1[i].id = i;
        GPIOapp_RpiPicoUsbModbus1[i].dir = GPIO_IN;
        GPIOapp_RpiPicoUsbModbus1[i].IN_pull_up = PULL_DOWN;
        GPIOapp_RpiPicoUsbModbus1[i].OUT_active = 0;
        GPIOapp_RpiPicoUsbModbus1[i].access = 0; // 0 = RO, 1 = RW

        if( i == 4 || i == 5 || i ==  23 || i == 24) 
        {
            // Those are not GPIO's
            GPIOapp_RpiPicoUsbModbus1[i].id = 0xff;
            GPIOapp_RpiPicoUsbModbus1[i].access = 0;
        }
    }
}

void init_all_GPIO(void)
{
    debug("GPIO INITIALIZATION\r\n");
    for (int i =0; i< SIZE_GPIO; i++)
    {
        gpioConf_initialization(GPIOapp_RpiPicoUsbModbus1+i);
    }
}

uint16_t gpioConf_coil_return(uint index)
{
    uint16_t result;
    if (index >=0 && index < SIZE_GPIO)
    {
        result = gpioConf_get_state(&GPIOapp_RpiPicoUsbModbus1[index]);
    }
    else
    {
        debug("DEBUG : Coil index not in range\r\n");
        result = 1;
    }
    return result;
}

void update_registers_init(struct modbus* modbusSlaveToUpdate)
{
    // modbusSlaveToUpdate->modbusRegister is a pointer to the modbus registers instance 
    modbusSlaveToUpdate->modbusRegister->holdingRegisters[0] = 0x505A; // "PZ"
    modbusSlaveToUpdate->modbusRegister->holdingRegisters[1] = 0x4121; // "A!""
    modbusSlaveToUpdate->modbusRegister->holdingRegisters[2] = 0x01;
    modbusSlaveToUpdate->modbusRegister->holdingRegisters[3] = number_gpio(); // number of gpio configured
}

void update_GPIOdir_registers(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate)
{
    // modbusSlaveToUpdate->modbusRegister is a pointer to the modbusRegisters instance 
    for (int i=0; i<SIZE_GPIO; i++)
    {
        if ((gpioToEvaluate+i)->id != 0xff)
        {
            if ((gpioToEvaluate+i)->dir == GPIO_IN)
            {
                if((gpioToEvaluate+i)->IN_pull_up == PULL_UP){
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[GPIO_DIR_VALUE_MEMORY_EMPLACEMENT + i] = 0x01;
                }
                else if((gpioToEvaluate+i)->IN_pull_up == PULL_DOWN){
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[GPIO_DIR_VALUE_MEMORY_EMPLACEMENT + i] = 0x02;
                }
                else{
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[GPIO_DIR_VALUE_MEMORY_EMPLACEMENT + i] = 0x03; // IN direction but not pull_in nor pull_down
                }
            }
            else if((gpioToEvaluate+i)->dir == GPIO_OUT){
                modbusSlaveToUpdate->modbusRegister->holdingRegisters[GPIO_DIR_VALUE_MEMORY_EMPLACEMENT + i] = 0x00;
            }
        }
        else
        {
            modbusSlaveToUpdate->modbusRegister->holdingRegisters[GPIO_DIR_VALUE_MEMORY_EMPLACEMENT + i] = 0xFF; // Not a GPIO
        }
    }
}

void update_modbus_registers_access(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate)
{
    for (int i=0; i< SIZE_GPIO; i++)
    {
        if (gpioToEvaluate[i].dir == GPIO_OUT)
        {
            // R/W
            modbusSlaveToUpdate->modbusRegister->access_coils[i>>3] |= (1<<(i&7));
        }
        if (gpioToEvaluate[i].dir == GPIO_IN || gpioToEvaluate[i].id == 0xFF)
        {
            // Read ONLY
            modbusSlaveToUpdate->modbusRegister->access_coils[i>>3] &= ~(1<<(i&7));
        }
    }
}

void update_GPIO_Registers(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate)
{
    for (int i=0; i<SIZE_GPIO; i++)
    {
        if (gpioConf_get_state(gpioToEvaluate+i))
        {
            (modbusSlaveToUpdate->modbusRegister->coils[i>>3]) |= (1<<(i&7));
        }
        else
        {
            modbusSlaveToUpdate->modbusRegister->coils[i>>3] &= ~(1<<(i&7));
        }
    }
}

uint16_t number_gpio(void)
{
    uint16_t IO_count = 0;
    for (int i=0; i<SIZE_GPIO; i++)
    {
        if (GPIOapp_RpiPicoUsbModbus1[i].id != 255) IO_count++; 
    }
    return IO_count;
}

uint8_t modbusMyWriteRegistersCallBack(struct modbus* slave, uint16_t index)
{
    uint8_t error = 0;
    uint8_t coil = index>>3;
    uint8_t mask = (1<<(index&7));
    struct gpioConf* myGPIO = slave->context;
    
    // Changing output state
    gpioConf_change_output_state(myGPIO+index,(slave->modbusRegister->coils[coil]) & mask);
    // Check for output really changed
    error = (gpioConf_get_state(myGPIO+index) != ((slave->modbusRegister->coils[coil]) & mask)) ? 1:0;

    return error;
}