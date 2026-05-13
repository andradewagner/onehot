# 🔥 OneHot — Controle Térmico com ESP32‑S3

Sistema embarcado desenvolvido para leitura de temperatura via **DS18B20 (OneWire)**, acionamento de **SSR**, controle de **válvulas** e monitoramento de **fluxo de água**, utilizando **ESP‑IDF 6.x** no ESP32‑S3.

---

## 📡 Funcionalidades

- 📏 Leitura de temperatura com **DS18B20**
- 🔥 Acionamento de **SSR** para controle de aquecimento
- 💧 Controle de válvula de água quente e fria
- 🚰 Leitura de sensores de fluxo
- 🧵 Execução em **FreeRTOS**
- 🧩 Arquitetura modular com componentes separados
- 🛠 Configuração via `menuconfig`

---

## 🧱 Estrutura do Projeto

onehot/
├── main/
│    └── onehot.c
├── components/
│    └── SensorTermico/
│         ├── SensorTermico.c
│         └── include/SensorTermico.h
├── managed_components/
│    ├── espressif__ds18b20
│    └── espressif__onewire_bus
├── sdkconfig
└── README.md

---

## 🔌 Ligações do Hardware

### 📍 DS18B20 (Modo Normal — Alimentado)

| DS18B20 | ESP32‑S3 |
|--------|----------|
| VDD    | 3V3      |
| GND    | GND      |
| DQ     | GPIO configurado em `CONFIG_TEMP_SENSOR_ONEWIRE_GPIO` |
| Pull‑up | **4.7kΩ entre DQ e 3V3** |

> ⚠ Sem o resistor de 4.7kΩ, o ESP‑IDF retorna:  
> *“reset bus failed: no devices found”*

---

## ⚙️ Configurações via `menuconfig`

Execute: idf.py menuconfig

OneHot Configuration  --->
GPIO do Sensor DS18B20 (OneWire)
GPIO do SSR
GPIO da Válvula de Água Quente
GPIO da Válvula de Água Fria
GPIO do Sensor de Fluxo Quente
GPIO do Sensor de Fluxo Frio


---

## 🧪 Exemplo de Uso (main)

```c
sensor_termico_handle_t sensor_agua;
float temp = 0;

if (sensor_termico_create(CONFIG_TEMP_SENSOR_ONEWIRE_GPIO, &sensor_agua) == ESP_OK) {
    while (1) {
        if (sensor_termico_ler_temperatura(sensor_agua, &temp) == ESP_OK) {
            printf("Temperatura da Água: %.2f °C\n", temp);
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

🧩 Componente SensorTermico
Criar o sensor
c

sensor_termico_create(gpio, &handle);

Ler temperatura
c

sensor_termico_ler_temperatura(handle, &temp);

Deletar
c

sensor_termico_delete(handle);

🚀 Compilação e Upload
Código

idf.py build
idf.py flash monitor

📝 Logs de Diagnóstico

O projeto usa:

    ESP_LOGI

    ESP_LOGW

    ESP_LOGE

    ESP_DRAM_LOGE

Para ativar logs verbosos:
Código

idf.py menuconfig
Component config → Log output → Default log level → Verbose

🛡 Dependências

Instaladas automaticamente via idf.py add-dependency:

    espressif/ds18b20

    espressif/onewire_bus

📄 Licença

MIT — livre para uso pessoal e comercial.
👨‍💻 Autor

Wagner — Projeto OneHot
Desenvolvido com ESP‑IDF 6.x e ESP32‑S3.