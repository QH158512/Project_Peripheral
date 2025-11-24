#include "peripheral.h"

DHTesp dht;

LiquidCrystal_I2C lcd(0x27,20,4);

SemaphoreHandle_t xWarningSemaphore = NULL;
SemaphoreHandle_t xCriticalSemaphore = NULL;


void peripheral (void *pvParameters)
{
  // put your setup code here, to run once:
  Serial.println("Peripheral Task Started");

  dht.setup(GPIO_NUM_26, DHTesp::DHT22);
  Serial.println("TESTING PRINT OUT TERMINAL");
  

  // Init LCD
  lcd.init();          // initialize the lcd 
  lcd.backlight();     // turn on backlight

  // // Optional welcome screen
  lcd.setCursor(2, 0);
  lcd.print("Hello World");
  delay(2000);
  //lcd.clear();

  while (1) {
    TempAndHumidity  data = dht.getTempAndHumidity();
    Serial.println("Temp: " + String(data.temperature, 2) + "°C");
    Serial.println("Humidity: " + String(data.humidity, 2) + "%");
    Serial.println("---");


    int state = 0;      // 0: normal, 1: warning, 2: critical
    if (data.temperature < 31.0) {
      state = 0;  // normal
    } else if (data.temperature >= 31.0 && data.temperature < 32.0) {
      state = 1;  // warning
      xSemaphoreGive(xWarningSemaphore);
    } else {
      state = 2;  // critical
      xSemaphoreGive(xCriticalSemaphore);
    }


    lcd.clear();
    //Row 0: Temperature 
    lcd.setCursor(0, 0);    
    lcd.print("Temp: "); 
    lcd.print(data.temperature, 1); // 1 decimal 
    lcd.print((char)223); // degree symbol 
    lcd.print("C "); // spaces to clear old data 

    // Row 1: Humidity 
    lcd.setCursor(0, 1); 
    lcd.print("Humidity: "); 
    lcd.print(data.humidity, 1); 
    lcd.print("% "); 




    vTaskDelay(2000);
  }

}


void warningTask(void *pvParameters)
{
    Serial.println("Warning Task started");

    while (1) 
    {
        if (xSemaphoreTake(xWarningSemaphore, portMAX_DELAY)) {

            TempAndHumidity data = dht.getTempAndHumidity();

            Serial.println("=== WARNING ===");
            Serial.println("Temp: " + String(data.temperature));

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("!!! WARNING !!!");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(data.temperature,1);
            lcd.print((char)223);
            lcd.print("C");

            // Show warning screen for 3 seconds
            vTaskDelay(2000);
        }
    }
}


void criticalTask(void *pvParameters)
{
    Serial.println("Critical Task started");

    while (1)
    {
        if (xSemaphoreTake(xCriticalSemaphore, portMAX_DELAY)) {

            TempAndHumidity data = dht.getTempAndHumidity();

            Serial.println("=== CRITICAL ===");
            Serial.println("Temp: " + String(data.temperature));

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("!!! CRITICAL !!!");

            lcd.setCursor(0,1);
            lcd.print("Temp: ");
            lcd.print(data.temperature,1);
            lcd.print((char)223);
            lcd.print("C");

            // Show critical warning for 3 seconds
            vTaskDelay(2000);
        }
    }
}