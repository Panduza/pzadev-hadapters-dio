#include "gpio_file.h"
#include "hardware/gpio.h"
#include "debug_file.h"

void gpioConf_initialization(struct gpioConf* __this)
{
    if (__this->id != 0xff)
        {
            gpio_init(__this->id);
            gpio_set_dir(__this->id, __this->dir);

            if (__this->dir == GPIO_IN)
            {
                if (__this->IN_pull_up)
                {
                    gpio_pull_up(__this->id);   
                }
                else
                {
                    gpio_pull_down(__this->id);
                }
            }
            else if (__this->dir == GPIO_OUT)
            {
                gpio_put(__this->id, __this->OUT_active);
            }
            else
            {
                char str[256];
                sprintf(str, "\n\r DEBUG : GPIO number %d neither in IN nor OUT mode\r\n");
                debug(str);
            }
        }
}

void gpioConf_change_dir(struct gpioConf* __this, bool dir)
{
    if (__this->dir != dir) 
    {
        __this->dir =  (dir == 0) ? GPIO_IN : GPIO_OUT;
        gpio_set_dir(__this->id, __this->dir);
    }
    else
    {
        debug("GPIO already affected in this mode\r\n")
    }
}

void gpioConf_change_output_state(struct gpioConf* __this, bool OUT_active)
{
    if (__this->dir == GPIO_OUT)
    {
        if (__this->OUT_active != OUT_active)
        {
            __this->OUT_active = (OUT_active == 0) ? 0:1;
            gpio_put(__this->id, __this->OUT_active);
        }
        else
        {
            debug("GPIO already in the state asked\r\n");
        }
    }
    else
    {
        debug("GPIO in IN mode, cannot change state\n\r");
    }
}

void gpioConf_change_input_pull(struct gpioConf* __this, bool IN_pull_up)
{
    if (__this->dir == GPIO_IN)
    {
        if (__this->IN_pull_up != IN_pull_up)
        {
            __this->IN_pull_up = (IN_pull_up == 0) ? 0:1;
            if (__this->IN_pull_up)
            {
                gpio_pull_up(__this->id);
            }
            else
            {
                gpio_pull_down(__this->id);
            }
        }
        else
        {
            debug("GPIO already in the pull mode asked\r\n");
        }
    }
    else
    {
        debug("GPIO in OUT mode, cannot change pull\n\r")
    }
}

bool gpioConf_get_state(struct gpioConf* __this)
{
    return gpio_get(__this->id);
}
