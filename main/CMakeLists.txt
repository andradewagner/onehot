idf_component_register(SRCS "onehot.c"
                    INCLUDE_DIRS "."
                    REQUIRES SensorTermico esp_driver_ledc driver esp_timer)

target_compile_definitions(${COMPONENT_LIB} PUBLIC "-DLOG_LOCAL_LEVEL=ESP_LOG_VERBOSE")
