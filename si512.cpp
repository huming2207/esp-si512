#include "si512.hpp"

#include <esp_log.h>

esp_err_t si512::init()
{
    auto ret = comm.init();
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Comm init failed: 0x%x %s", ret, esp_err_to_name(ret));
        return ret;
    }



    return ret;
}
