#define MOTION_DRIVER_TARGET_ESP32
#define MPU9250

#include "esp_err.h"

esp_err_t esp_i2c_init();

int i2c_write(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char const *data);

int i2c_read(unsigned char slave_addr, unsigned char reg_addr,
     unsigned char length, unsigned char *data);

void delay_ms(unsigned long num_ms);
void get_ms(unsigned long *count);

void reg_int_cb(void* cb);