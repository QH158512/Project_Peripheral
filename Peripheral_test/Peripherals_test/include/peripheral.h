#ifndef __PERIPHERAL_H__
#define __PERIPHERAL_H__
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"
#include "DHTesp.h"


extern SemaphoreHandle_t xWarningSemaphore;
extern SemaphoreHandle_t xCriticalSemaphore;

void peripheral(void *pvParameters);
void warningTask(void *pvParameters);
void criticalTask(void *pvParameters);

#endif