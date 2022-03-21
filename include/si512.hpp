#pragma once

#include "si5xx_comm.hpp"

class si512
{
public:
    explicit si512(si5xx_comm &_comm) : comm(_comm) {};
    esp_err_t init();

private:
    static const constexpr char *TAG = "si512";
    si5xx_comm &comm;
};