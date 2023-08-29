#ifndef A9G_BIKE_TRACKER_UTILS_H
#define A9G_BIKE_TRACKER_UTILS_H

#include <Arduino.h>
#include "WiFi.h"
#include "logging.h"

void connectToWifi(const char *ssid, const char *password) {
    log("Connecting to ");
    logLine(ssid);

    auto timeoutAt = millis() + 10000;
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        if (timeoutAt - millis() < 0) {
            logLine("Failed to connect to WiFi! Restarting...");
            ESP.restart();
        }

        delay(500);
        log(".");
    }
    logLine("");

    log("Connected to ");
    logLine(ssid);
    log("IP address: ");
    logLine(WiFi.localIP().toString().c_str());
}

void sendTcpMessage(const char *message) {
    WiFiClient client = WiFiClient();
    logLine("Connecting to TCP server...");
    if (!client.connect(BACKEND_HOST, BACKEND_PORT)) {
        logLine("Failed to connect to TCP server!");
        return;
    }

    logLine("Sending TCP message...");
    auto n = client.write(message);
    if (n != strlen(message)) {
        logLine("Failed to send TCP message!");
        return;
    }
}

#endif //A9G_BIKE_TRACKER_UTILS_H
