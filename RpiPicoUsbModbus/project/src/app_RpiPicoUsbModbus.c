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

    modbus_init(get_modbus_slave());
}

void app_RpiPicoUsbModbus_run(void)
{
        platform_modbus_usb_cdc_xfer();
        
        gpioConf_change_output_state(&GPIOapp_RpiPicoUsbModbus[LED_PIN], 1);
        sleep_ms(1000);
        gpioConf_change_output_state(&GPIOapp_RpiPicoUsbModbus[LED_PIN], 0);
        sleep_ms(1000);
}

void declare_all_GPIO(void){
    debug("GPIO DECLARATION\r\n");
    for (int i = 0; i< 28; i++){
        GPIOapp_RpiPicoUsbModbus[i].id = i;
        GPIOapp_RpiPicoUsbModbus[i].IN_pull_up = 1;
        GPIOapp_RpiPicoUsbModbus[i].OUT_active = 0;

        if( i == 4 || i == 5 || i ==  23 || i == 24) 
        {
            GPIOapp_RpiPicoUsbModbus[i].id = 0xff;
        }

        GPIOapp_RpiPicoUsbModbus[i].dir = (i!=LED_PIN) ? GPIO_IN : GPIO_OUT; // Set LED GPIO in OUT mode, others in IN mode
    }
}

void init_all_GPIO(void)
{
    debug("GPIO INITIALIZATION\r\n");
    for (int i =0; i< 28; i++)
    {
        gpioConf_initialization(GPIOapp_RpiPicoUsbModbus+i);
    }
}

uint16_t gpioConf_info_return(uint index){

    uint16_t result = 0;
    uint16_t IO_count = 0;

    if (index == 0)
    {
        result = 0x505A; // "PZ"
    }
    else if (index == 1)
    {
        result = 0x4121; // "A!"
    }
    else if (index == 2)
    {
        result = 0x01;
    }
    else if (index == 3)
    {
        for (int i=0; i<sizeof(GPIOapp_RpiPicoUsbModbus)/sizeof(GPIOapp_RpiPicoUsbModbus[0]); i++)
        {
            if (GPIOapp_RpiPicoUsbModbus[i].id != 255) IO_count++; 
        }
        result = IO_count;
    }
    else if (index >= 4 && index < sizeof(GPIOapp_RpiPicoUsbModbus)/ sizeof(GPIOapp_RpiPicoUsbModbus[0]) && GPIOapp_RpiPicoUsbModbus[index].id != 0xff)
    {
        if(GPIOapp_RpiPicoUsbModbus[index].dir == GPIO_IN)
        {
            if(GPIOapp_RpiPicoUsbModbus[index].IN_pull_up){
                result=0x01;
            }
            else if(!GPIOapp_RpiPicoUsbModbus[index].IN_pull_up){
                result=0x02;
            }
            else{
                result=0x03;
            }
        }
        else if(GPIOapp_RpiPicoUsbModbus[index].dir == GPIO_OUT){
            result=0x00;
        }
    }
    else
    {
        debug("DEBUG : Holding register index not in range\r\n");
        result = 1;
    }
    return result;
}

uint16_t gpioConf_coil_return(uint index)
{
    uint16_t result;
    if (index >=0 && index < sizeof(GPIOapp_RpiPicoUsbModbus)/ sizeof(GPIOapp_RpiPicoUsbModbus[0]))
    {
        // result = gpio_get(GPIOapp_RpiPicoUsbModbus[index].id);
        result = gpioConf_get_state(&GPIOapp_RpiPicoUsbModbus[index]);
    }
    else
    {
        debug("DEBUG : Coil index not in range\r\n");
        result = 1;
    }
    return result;
}