//
// Created by Kok on 2/12/26.
//

#ifndef ESP32S3_TASK_SCHEDULER_H
#define ESP32S3_TASK_SCHEDULER_H

#include "esp_task.h"

typedef struct {
    volatile uint8_t Active;
    TaskHandle_t OsTask;
    TaskFunction_t Function;
    char *Name;
    void *Args;
    uint8_t CoreID;
    uint8_t Priority;
    uint32_t StackDepth;
} SCHEDULER_TaskTypeDef;

void SCHEDULER_Create(SCHEDULER_TaskTypeDef *Task);
void SCHEDULER_Remove(SCHEDULER_TaskTypeDef *Task);

#endif //ESP32S3_TASK_SCHEDULER_H
