//
// Created by Kok on 3/14/26.
//

#ifndef ESP32S3_BLE_BT_CONFIG_H
#define ESP32S3_BLE_BT_CONFIG_H

#include <stdint.h>

#include "ble.h"

typedef struct {
    uint16_t LedStateChrHandle;
    uint16_t LEDSetStateChrHandle;
    uint16_t LEDCycleChrHandle;
} BLE_AttributesTypeDef;

extern BLE_AttributesTypeDef gBleAttributes;

void BT_Configure(BLE_HandleTypeDef *hble);

#endif //ESP32S3_BLE_BT_CONFIG_H