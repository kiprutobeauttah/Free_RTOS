#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Define LED pins (adjust these to match your hardware setup)
#define LED1_PIN D0  // Built-in LED on ESP32-S3
#define LED2_PIN D1  // Example external LED pin

// Task handles
TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;

// Task 1: Blink LED1 every 500ms
void blinkLED1Task(void *parameter) {
  pinMode(LED1_PIN, OUTPUT);
  
  while(1) {
    digitalWrite(LED1_PIN, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(LED1_PIN, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

// Task 2: Blink LED2 every 1000ms
void blinkLED2Task(void *parameter) {
  pinMode(LED2_PIN, OUTPUT);
  
  while(1) {
    digitalWrite(LED2_PIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED2_PIN, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Creating tasks...");
  
  // Create tasks
  xTaskCreate(
    blinkLED1Task,      // Task function
    "BlinkLED1",        // Task name
    2048,               // Stack size (bytes)
    NULL,               // Task parameters
    1,                  // Task priority (0-24, higher number = higher priority)
    &Task1Handle        // Task handle
  );
  
  xTaskCreate(
    blinkLED2Task,      // Task function
    "BlinkLED2",        // Task name
    2048,               // Stack size (bytes)
    NULL,               // Task parameters
    1,                  // Task priority
    &Task2Handle        // Task handle
  );
  
  Serial.println("Tasks created successfully");
}

void loop() {
  // Empty loop - tasks are handled by FreeRTOS scheduler
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}