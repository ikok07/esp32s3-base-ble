//
// Created by Kok on 2/13/26.
//

#include "ble.h"

#include "nvs_flash.h"
#include "task_scheduler.h"

#include "host/ble_hs.h"

#include "nimble/nimble_port.h"
#include "nimble/ble.h"
#include "services/gap/ble_svc_gap.h"

/* ------ Private methods ------ */

static BLE_ErrorTypeDef gap_init(BLE_HandleTypeDef *hble);

/* ------ Callbacks ------ */

static void on_stack_reset_cb(int reason);
static void on_stack_sync_cb(void);

/* ------ Tasks ------ */

static void ble_task(void *arg);

BLE_ErrorTypeDef BLE_Init(BLE_HandleTypeDef *hble) {
    BLE_ErrorTypeDef ble_err = BLE_ERROR_OK;
    esp_err_t err = ESP_OK;

    uint8_t nvs_ready = 0;
    while (!nvs_ready) {
        // Initialize the flash memory
        if ((err = nvs_flash_init()) != ESP_OK) {
            if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                nvs_flash_erase();
            }
            return BLE_ERROR_NVS;
        }
        nvs_ready = 1;
    }

    // Initialize the NimBLE stack
    if ((err = nimble_port_init()) != ESP_OK) {
        return BLE_ERROR_INIT;
    }

    ble_hs_cfg.reset_cb = on_stack_reset_cb;
    ble_hs_cfg.sync_cb = on_stack_sync_cb;

    // Initialize GAP
    if ((ble_err = gap_init(hble)) != BLE_ERROR_OK) return ble_err;

    hble->BLE_Task->Function = ble_task;
    SCHEDULER_Create(hble->BLE_Task);

    return BLE_ERROR_OK;
}

BLE_ErrorTypeDef gap_init(BLE_HandleTypeDef *hble) {
    uint8_t err = 0;

    // Initialize GAP service
    ble_svc_gap_init();

    // Set device name
    if ((err = ble_svc_gap_device_name_set(hble->DeviceName)) != 0) return BLE_ERROR_GAP_NAME;

    // Set GAP appearance
    if ((err = ble_svc_gap_device_appearance_set(hble->GapAppearance)) != 0) return BLE_ERROR_GAP_APPEARANCE;

    return BLE_ERROR_OK;
}