#include "debug.h"
#include <stdarg.h> // For va_list, va_start, va_end

void debug(const char* message) {
    #if DEBUG == 1
    Serial.print(message);
    #endif
}

void debugf(const char* format, ...) {
    #if DEBUG == 1
    char buf[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    Serial.print(buf);
    #endif
}

void debugln(const char* message) {
    #if DEBUG == 1
    if (message != nullptr) {
        Serial.println(message);
    } else {
        Serial.println();
    }
    #endif
}

void debugIP(const IPAddress& ip) {
    #if DEBUG == 1
    Serial.println(ip);
    #endif
}

