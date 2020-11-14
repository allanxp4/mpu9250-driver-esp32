#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "i2c.h"
#include "esp32_driver.h"
#include "inv_mpu.h"


void app_main(void)
{
    printf("Hello world!\n");
    esp_i2c_init();
    struct int_param_s int_param;
    int result = mpu_init(&int_param);
    ESP_ERROR_CHECK(result);
    mpu_set_sensors(INV_XYZ_ACCEL | INV_XYZ_GYRO | INV_XYZ_COMPASS);
    mpu_set_gyro_fsr(500);
    mpu_set_accel_fsr(2);
    mpu_set_lpf(5);
    mpu_set_sample_rate(10);
    mpu_set_compass_sample_rate(10);

    while(true) {
        short data[3];
        if(!mpu_get_accel_reg(data, NULL)){
            printf("mpu_get_accel_reg failed");
        }
        else {
            short gx = data[0];
            short gy = data[1];
            short gz = data[2];

            printf("x: %h, y: %h, z: %h", gx, gy, gz);
        }
    }

    vTaskDelay(1000);
    esp_restart();
}

