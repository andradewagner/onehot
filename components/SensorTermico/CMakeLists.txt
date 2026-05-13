idf_component_register(SRCS "SensorTermico.c"
                    INCLUDE_DIRS "include"
                    PRIV_REQUIRES espressif__ds18b20 espressif__onewire_bus log)