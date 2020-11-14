#include <stdio.h>
#include "mpu_esp32_driver.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"

#define I2C_MASTER_PORT I2C_NUM_1
#define I2C_TIMEOUT 1000 / portTICK_RATE_MS

esp_err_t esp_i2c_init() {
    i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_NUM_19,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = GPIO_NUM_18,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    i2c_param_config(I2C_MASTER_PORT, &config);
    return i2c_driver_install(I2C_MASTER_PORT, config.mode, 0, 0, 0);
}   

int i2c_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const *data) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_write_byte(handle, slave_addr, true);
    i2c_master_write_byte(handle, reg_addr, true);
    i2c_master_write(handle, data, length, true);
    i2c_master_stop(handle);
    esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_PORT, handle, I2C_TIMEOUT);
    ESP_ERROR_CHECK(err);
    i2c_cmd_link_delete(handle);
    return 0;
}

int i2c_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char *data) {
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    i2c_master_write_byte(handle, slave_addr, true);
    i2c_master_write_byte(handle, reg_addr, true);
    i2c_master_write(handle, data, length, true);
    i2c_master_read(handle, data, length, true);
    i2c_master_stop(handle);
    esp_err_t err = i2c_master_cmd_begin(I2C_MASTER_PORT, handle, I2C_TIMEOUT);
    ESP_ERROR_CHECK(err);
    i2c_cmd_link_delete(handle);
    return 0;
}

void delay_ms(unsigned long num_ms) {
    vTaskDelay(num_ms / portTICK_PERIOD_MS);
}

void get_ms(unsigned long *count) {
    *count = (unsigned long) esp_timer_get_time();
}

void reg_int_cb(void* cb) {
    // ¯\_(ツ)_/¯
}