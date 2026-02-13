//
// Created by Kok on 2/13/26.
//

#ifndef ESP32S3_BLE_BLE_H
#define ESP32S3_BLE_BLE_H

#include "task_scheduler.h"

typedef enum {
    BLE_ERROR_OK,
    BLE_ERROR_NVS,
    BLE_ERROR_INIT,
    BLE_ERROR_GAP_NAME,
    BLE_ERROR_GAP_APPEARANCE
} BLE_ErrorTypeDef;

typedef struct {
    SCHEDULER_TaskTypeDef *BLE_Task;
    char *DeviceName;
    uint16_t GapAppearance;
} BLE_HandleTypeDef;

BLE_ErrorTypeDef BLE_Init(BLE_HandleTypeDef *hble);

#endif //ESP32S3_BLE_BLE_H