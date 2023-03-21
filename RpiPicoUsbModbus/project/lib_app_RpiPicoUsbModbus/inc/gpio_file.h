#ifndef GPIO_H
#define GPIO_H

#include "pico/types.h"

#define PULL_DOWN 0
#define PULL_UP 1

struct gpioConf {
    uint8_t id;     // # 255 if invalid
    uint8_t dir; // IN or OUT
    bool IN_pull_up; // 1 = pull_up, 0 = pull_down (default)
    bool OUT_active; // 1 = OUT is active, 0 = OUT is inactive (default)
    bool access; // 0 = Read only, 1 = Read and write
};

void gpioConf_initialization(struct gpioConf* __this);
void gpioConf_change_dir(struct gpioConf* __this, bool dir);
void gpioConf_change_output_state(struct gpioConf* __this, bool OUT_active);
void gpioConf_change_input_pull(struct gpioConf* __this, bool IN_pull_up);
bool gpioConf_get_state(struct gpioConf* __this);

#endif