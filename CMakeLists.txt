idf_component_register(
        SRCS
            "include/si5xx_comm.hpp"
            "si5xx_comm_i2c.cpp" "include/si5xx_comm_i2c.hpp"
            "si512.cpp" "include/si512.hpp"
        INCLUDE_DIRS
            "include"
        PRIV_REQUIRES
            driver
)
