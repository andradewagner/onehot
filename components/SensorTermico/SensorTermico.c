#include <stdlib.h>
#include "SensorTermico.h"
#include "onewire_bus.h"
#include "ds18b20.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "SENSOR_TERMICO";

struct sensor_termico_t {
    onewire_bus_handle_t bus;
    ds18b20_device_handle_t device;
};

esp_err_t sensor_termico_create(int gpio_num, sensor_termico_handle_t *out_handle) {
    struct sensor_termico_t *st = malloc(sizeof(struct sensor_termico_t));
    if (!st) return ESP_ERR_NO_MEM;

    // Ajuste: bus_gpio_num
    onewire_bus_config_t bus_config = { .bus_gpio_num = gpio_num };
    // Ajuste: max_rx_bytes
    onewire_bus_rmt_config_t rmt_config = { .max_rx_bytes = 20 }; 
    ESP_ERROR_CHECK(onewire_new_bus_rmt(&bus_config, &rmt_config, &st->bus));

    onewire_device_iter_handle_t iter;
    onewire_new_device_iter(st->bus, &iter);
    onewire_device_t next_device;
    
    if (onewire_device_iter_get_next(iter, &next_device) == ESP_OK) {
        ds18b20_config_t ds_cfg = {}; 
        
        // Ajuste: Chamada para a versão OneWire da função
        ESP_ERROR_CHECK(ds18b20_new_device_from_bus(st->bus, &ds_cfg, &st->device));
        
        // Ajuste: Resolução 12B
        ds18b20_set_resolution(st->device, DS18B20_RESOLUTION_12B);
    } else {
        ESP_LOGE(TAG, "Nenhum sensor DS18B20 encontrado no GPIO %d", gpio_num);
        free(st);
        return ESP_ERR_NOT_FOUND;
    }
    
    onewire_del_device_iter(iter);
    *out_handle = st;
    return ESP_OK;
}

esp_err_t sensor_termico_ler_temperatura(sensor_termico_handle_t handle, float *temp) {
    if (!handle) return ESP_ERR_INVALID_ARG;
    
    ESP_ERROR_CHECK(ds18b20_trigger_temperature_conversion(handle->device));
    // Tempo de conversão para 12 bits
    vTaskDelay(pdMS_TO_TICKS(800)); 
    
    return ds18b20_get_temperature(handle->device, temp);
}

void sensor_termico_delete(sensor_termico_handle_t handle) {
    if (handle) {
        free(handle);
    }
}