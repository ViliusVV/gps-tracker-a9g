#include <Arduino.h>
#include "logging.h"
#include "utils.h"
#include "config.h"

#define SERIAL_BAUDRATE 119200



void xTaskBlink( void *pvParameters );
void xTaskAnalogReadA3( void *pvParameters );

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void setup() {
    Serial.begin(SERIAL_BAUDRATE);
    logLine("=== Setup... ===");

    connectToWifi(WIFI_SSID, WIFI_PASSWORD);

    xTaskCreatePinnedToCore(
    xTaskBlink
    ,  "xTaskBlink"
    ,  1024
    , nullptr
    ,  2
    ,  nullptr
    ,  ARDUINO_RUNNING_CORE);

     xTaskCreatePinnedToCore(
    xTaskAnalogReadA3
    ,  "xTaskHandleA9G"
    ,  CONFIG_ARDUINO_LOOP_STACK_SIZE
    ,  nullptr
    ,  1  
    ,  nullptr
    ,  ARDUINO_RUNNING_CORE);

    logLine("=== Setup done! ===");
}
#pragma clang diagnostic pop



#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
void loop(){ }



/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void xTaskBlink(void *pvParameters) {
    (void) pvParameters;

    pinMode(LED_BUILTIN, OUTPUT);

    for (;;) {
        vTaskDelay(1000);
    }
}

void xTaskAnalogReadA3(void *pvParameters)
{
    (void) pvParameters;

    for (;;) {
        auto n = uxTaskGetStackHighWaterMark(NULL);
        Serial.print("Stack high water mark: " );
        Serial.println(n);
        auto currentTime = xTaskGetTickCount();
        sendTcpMessage("Hello from ESP32! Scheduler ticks: " + String(currentTime) + " Stack high water mark: " + String(n) + "\n");

        vTaskDelay(1000);
    }
}
