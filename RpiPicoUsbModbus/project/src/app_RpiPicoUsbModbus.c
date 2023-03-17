// include config file
#include "app_RpiPicoUsbModbus.h"

#define LED_PIN 25
#define MAX_MODBUS_SLAVE 1


void app_RpiPicoUsbModbus_init(void)
{
    // struct mobdus mod_unique
    
    stdio_init_all();
        
    // DEBUG
    uart_initialization_test();
    // FIN DEBUG

    // Declare and init all GPIO
    declare_all_GPIO();
    init_all_GPIO();

    // Declare, assign adress and a register to a modbus slave
    modbus_init(&MODBUSapp_RpiPicoUsbModbus1);
    modbus_assign_adress(&MODBUSapp_RpiPicoUsbModbus1, 0x01);
    modbus_assign_register(&MODBUSapp_RpiPicoUsbModbus1, &modbusRegisterSlave1);

    update_registers_init(&MODBUSapp_RpiPicoUsbModbus1);
}

void app_RpiPicoUsbModbus_run(void)
{
        update_registers(&MODBUSapp_RpiPicoUsbModbus1, GPIOapp_RpiPicoUsbModbus1);
        modbus_platform_modbus_usb_cdc_xfer(&MODBUSapp_RpiPicoUsbModbus1);
        
        gpioConf_change_output_state(&GPIOapp_RpiPicoUsbModbus1[LED_PIN], 1);
        sleep_ms(1000);
        gpioConf_change_output_state(&GPIOapp_RpiPicoUsbModbus1[LED_PIN], 0);
        sleep_ms(1000);
}

void declare_all_GPIO(void){
    debug("GPIO DECLARATION\r\n");
    uint8_t sizeGPIO = sizeof(GPIOapp_RpiPicoUsbModbus1)/ sizeof(GPIOapp_RpiPicoUsbModbus1[0]);
    for (int i = 0; i< sizeGPIO; i++){
        GPIOapp_RpiPicoUsbModbus1[i].id = i;
        GPIOapp_RpiPicoUsbModbus1[i].IN_pull_up = 1;
        GPIOapp_RpiPicoUsbModbus1[i].OUT_active = 0;

        if( i == 4 || i == 5 || i ==  23 || i == 24) 
        {
            GPIOapp_RpiPicoUsbModbus1[i].id = 0xff;
        }

        GPIOapp_RpiPicoUsbModbus1[i].dir = (i!=LED_PIN) ? GPIO_IN : GPIO_OUT; // Set LED GPIO in OUT mode, others in IN mode
    }
}

void init_all_GPIO(void)
{
    debug("GPIO INITIALIZATION\r\n");
    uint8_t sizeGPIO = sizeof(GPIOapp_RpiPicoUsbModbus1)/ sizeof(GPIOapp_RpiPicoUsbModbus1[0]);
    for (int i =0; i< sizeGPIO; i++)
    {
        gpioConf_initialization(GPIOapp_RpiPicoUsbModbus1+i);
    }
}

uint16_t gpioConf_coil_return(uint index)
{
    uint16_t result;
    if (index >=0 && index < sizeof(GPIOapp_RpiPicoUsbModbus1)/ sizeof(GPIOapp_RpiPicoUsbModbus1[0]))
    {
        // result = gpio_get(GPIOapp_RpiPicoUsbModbus1[index].id);
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

void update_registers(struct modbus* modbusSlaveToUpdate, struct gpioConf* gpioToEvaluate)
{
    uint16_t sizeGPIO = sizeof(GPIOapp_RpiPicoUsbModbus1)/sizeof(GPIOapp_RpiPicoUsbModbus1[0]);
    uint8_t offset = 10; // The first 4 holding register are preconfigured with other values

    // modbusSlaveToUpdate->modbusRegister is a pointer to the modbus registers instance 
    for (int i=0; i<sizeGPIO; i++)
    {
        if ((gpioToEvaluate+i)->id != 0xff)
        {
            if ((gpioToEvaluate+i)->dir == GPIO_IN)
            {
                if((gpioToEvaluate+i)->IN_pull_up){
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[offset + i] = 0x01;
                }
                else if(!(gpioToEvaluate+i)->IN_pull_up){
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[offset + i] = 0x02;
                }
                else{
                    modbusSlaveToUpdate->modbusRegister->holdingRegisters[offset + i] = 0x03; // IN direction but not pull_in nor pull_down
                }
            }
            else if((gpioToEvaluate+i)->dir == GPIO_OUT){
                modbusSlaveToUpdate->modbusRegister->holdingRegisters[offset + i] = 0x00;
            }
        }
        else
        {
            modbusSlaveToUpdate->modbusRegister->holdingRegisters[offset + i] = 0x04; // Not a GPIO
        }
    }
}

uint16_t number_gpio(void)
{
    uint16_t IO_count = 0;
    for (int i=0; i<sizeof(GPIOapp_RpiPicoUsbModbus1)/sizeof(GPIOapp_RpiPicoUsbModbus1[0]); i++)
    {
        if (GPIOapp_RpiPicoUsbModbus1[i].id != 255) IO_count++; 
    }
    return IO_count;
}