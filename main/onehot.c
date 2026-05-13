#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "SensorTermico.h"
#include "driver/ledc.h"

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"


int temp_sensor_onewire_gpio = CONFIG_TEMP_SENSOR_ONEWIRE_GPIO; // int "GPIO do Barramento OneWire (P4)"
int ssr_heater_gpio = CONFIG_SSR_HEATER_GPIO;
int valve_cold_gpio = CONFIG_VALVE_COLD_GPIO;
int valve_hot_gpio = CONFIG_VALVE_HOT_GPIO;
int flow_sensor_cold_gpio = CONFIG_FLOW_SENSOR_COLD_GPIO;
int flow_sensor_hot_gpio = CONFIG_FLOW_SENSOR_HOT_GPIO;

static const char *TAG = "OneHot_Scanner";

void app_main(void) {
    sensor_termico_handle_t sensor_agua;
    float temp = 0;

    ESP_LOGI(TAG, "Método app_main()");
    ESP_EARLY_LOGW(TAG, "Early log message before Wi-Fi initialization");
    ESP_DRAM_LOGE(DRAM_STR("TAG_IN_DRAM"), "DRAM log message"); // Use DRAM_STR macro to put in DRAM if needed

    // temp_sensor_onewire_gpio vem do seu Kconfig
    if (sensor_termico_create(temp_sensor_onewire_gpio, &sensor_agua) == ESP_OK) {
        while (1) {
            if (sensor_termico_ler_temperatura(sensor_agua, &temp) == ESP_OK) {
                printf("Temperatura da Água: %.2f °C\n", temp);
            }
            vTaskDelay(pdMS_TO_TICKS(2000));
        }
    } else {
        printf("Falha ao inicializar o sensor térmico no GPIO %d\n", temp_sensor_onewire_gpio);
    }
}
