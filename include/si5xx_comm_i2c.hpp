#pragma once

#include "si5xx_comm.hpp"
#include <driver/i2c.h>

class si5xx_comm_i2c : public si5xx_comm
{
public:
    explicit si5xx_comm_i2c(uint8_t _addr, gpio_num_t _sda, gpio_num_t _scl, uint32_t _clk_speed_hz = 100000, i2c_port_t _port = I2C_NUM_0)
                    : addr(_addr), port(_port), sda(_sda), scl(_scl), clk_speed_hz(_clk_speed_hz) {};
    esp_err_t init() override;
    esp_err_t write(uint8_t reg, const uint8_t *data, size_t len) override;
    esp_err_t read(uint8_t reg, uint8_t *data, size_t len) override;

private:
    uint8_t addr;
    i2c_port_t port;
    gpio_num_t sda;
    gpio_num_t scl;
    uint32_t clk_speed_hz;
};