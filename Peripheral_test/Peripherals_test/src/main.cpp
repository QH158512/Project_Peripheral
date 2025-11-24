#include "peripheral.h"


void setup()
{
  Serial.begin(115200);

  xWarningSemaphore = xSemaphoreCreateBinary();
  xCriticalSemaphore = xSemaphoreCreateBinary();

  xTaskCreate(peripheral, "Task peripheral", 2048, NULL, 2, NULL);
  xTaskCreate(warningTask, "Warning", 2048, NULL, 1, NULL);
  xTaskCreate(criticalTask, "Critical", 2048, NULL, 1, NULL);

}

void loop()
{
  
}




