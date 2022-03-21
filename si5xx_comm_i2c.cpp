#include "si5xx_comm_i2c.hpp"

#define I2C_WRITE_BIT 0
#define I2C_READ_BIT 1

esp_err_t si5xx_comm_i2c::write(uint8_t reg, const uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    auto ret = i2c_master_start(cmd);
    ret = ret ?: i2c_master_write_byte(cmd, (addr << 1) | I2C_WRITE_BIT, true);
    ret = ret ?: i2c_master_write_byte(cmd, reg, true);
    ret = ret ?: i2c_master_write(cmd, data, len, true);
    ret = ret ?: i2c_master_stop(cmd);

    ret = ret ?: i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t si5xx_comm_i2c::read(uint8_t reg, uint8_t *data, size_t len)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    auto ret = i2c_master_start(cmd);
    ret = ret ?: i2c_master_write_byte(cmd, (addr << 1) | I2C_WRITE_BIT, true);
    ret = ret ?: i2c_master_write_byte(cmd, reg, true);

    ret = ret ?: i2c_master_start(cmd);
    ret = ret ?: i2c_master_write_byte(cmd, (addr << 1) | I2C_READ_BIT, true);
    ret = ret ?: i2c_master_read(cmd, data, len, I2C_MASTER_LAST_NACK);
    ret = ret ?: i2c_master_stop(cmd);

    ret = ret ?: i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t si5xx_comm_i2c::init()
{
    i2c_config_t config = {};
    config.mode = I2C_MODE_MASTER;
    config.sda_io_num = sda;
    config.sda_pullup_en = GPIO_PULLUP_ENABLE;
    config.scl_io_num = scl;
    config.scl_pullup_en = GPIO_PULLUP_ENABLE;
    config.master.clk_speed = clk_speed_hz;
    auto ret = i2c_param_config(port, &config);
    ret = ret ?: i2c_driver_install(port, config.mode, 0, 0, 0);
    return ret;
}
