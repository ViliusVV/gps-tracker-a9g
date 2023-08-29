#ifndef A9G_BIKE_TRACKER_LOGGING_H
#define A9G_BIKE_TRACKER_LOGGING_H

#include <Arduino.h>
#include "config.h"

void logLine(const char msg[]) {
#if LOGGING_ENABLED
    Serial.println(msg);
#endif
}

void log(const char msg[]) {
#if LOGGING_ENABLED
    Serial.print(msg);
#endif
}


#endif //A9G_BIKE_TRACKER_LOGGING_H
