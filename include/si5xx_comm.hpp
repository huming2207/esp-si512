#pragma once

#include <esp_err.h>
#include <driver/gpio.h>

class si5xx_comm
{
    virtual esp_err_t init() = 0;
    virtual esp_err_t write(uint8_t reg, const uint8_t *data, size_t len) = 0;
    virtual esp_err_t read(uint8_t reg, uint8_t *data, size_t len) = 0;
};