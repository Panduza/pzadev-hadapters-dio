#include "app_RpiPicoUsbModbus.h"

int main() {
    
    app_RpiPicoUsbModbus_init();

    while(1)
    {
        app_RpiPicoUsbModbus_run();
    }

    return 0;
}