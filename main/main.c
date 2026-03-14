#include "app_state.h"
#include "ble.h"
#include "power.h"
#include "led_strip.h"

#include "bt.h"
#include "led.h"
#include "log.h"
#include "log-config.h"

void app_main(void) {
    esp_err_t esp_err;

    // Initialize app state
    APP_Init();

    // Configure logger
    LOG_Configure();

    // Configure power
    if ((esp_err = POWER_Config())!= ESP_OK) {
        LOGGER_LogF(LOGGER_LEVEL_FATAL, "Failed to configure board power! Error code: %d", esp_err);
        return;
    }
    POWER_FreqControl(pdTRUE);

    // Disable MCU sleep during configuration
    POWER_LightSleepControl(pdFALSE);

    // Configure and start LED task
    LED_Init();

    // Configure and start BLE task
    BT_Init();

    // Wait for all tasks to start
    while (
        !gAppState.Tasks->LedTask.Active ||
        !gAppState.Tasks->BleTask.Active ||
        !gAppState.Tasks->LedNotifyTask.Active
    ) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    // Allow MCU to sleep
    POWER_LightSleepControl(pdTRUE);
}