#ifndef SENSOR_TERMICO_H
#define SENSOR_TERMICO_H

#include "esp_err.h"

// Define o tipo do handle (ponteiro opaco) para manter o baixo acoplamento
typedef struct sensor_termico_t* sensor_termico_handle_t;

/**
 * @brief Inicializa o sensor DS18B20 em um pino específico.
 */
esp_err_t sensor_termico_create(int gpio_num, sensor_termico_handle_t *out_handle);

/**
 * @brief Realiza a leitura da temperatura.
 */
esp_err_t sensor_termico_ler_temperatura(sensor_termico_handle_t handle, float *temp);

/**
 * @brief Libera os recursos do sensor.
 */
void sensor_termico_delete(sensor_termico_handle_t handle);

#endif