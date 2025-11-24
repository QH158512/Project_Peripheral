# Project_Peripheral

This project implements a real-time temperature and humidity monitoring system using an ESP32, a DHT22 sensor, and a 20x4 I2C LCD.
The system uses FreeRTOS tasks and binary semaphores to detect abnormal temperature conditions and trigger dedicated warning/critical handler tasks.

This project demonstrates:

Reading temperature & humidity from a DHT22

Displaying live sensor data on an LCD

Using FreeRTOS tasks, semaphores, and task synchronization

Handling three system states:

Normal

Warning (temperature 30–32°C)

Critical (temperature > 32°C)
