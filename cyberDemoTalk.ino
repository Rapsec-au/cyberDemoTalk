#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include "secrets.h"

#include "firebase_connection.h"
#include "debug.h"
#include "wifi_connection.h"

#define RELAY_ONE_PIN  26
#define RELAY_TWO_PIN  25

// Path to the integer values in the Realtime Database
const String relayOnePath = "/device/relayOne";
const String relayTwoPath = "/device/relayTwo";

// Function to initialize GPIO pins
void setupGPIO() {
    pinMode(RELAY_ONE_PIN, OUTPUT);
    pinMode(RELAY_TWO_PIN, OUTPUT);
    digitalWrite(RELAY_ONE_PIN, HIGH); // Start with the relays off (active LOW)
    digitalWrite(RELAY_TWO_PIN, HIGH); // Start with the relays off (active LOW)
}

void setup() {
    Serial.begin(115200);
    setupWiFi();           // Set up WiFi connection
    setupFirebase();       // Setup Firebase connection
    setupGPIO();           // Initialize GPIO pins
}

void loop() {
    // Check the value of relayOne
    if (Firebase.getInt(firebaseData, relayOnePath)) {
        if (firebaseData.dataType() == "int") {
            int relayOneState = firebaseData.intData();
            digitalWrite(RELAY_ONE_PIN, relayOneState == 1 ? HIGH : LOW); // Active High logic
            Serial.print("relayOne: ");
            Serial.println(relayOneState);
        }
    } else {
        Serial.println("Failed to get relayOne value");
        Serial.println(firebaseData.errorReason());
    }

    // Check the value of relayTwo
    if (Firebase.getInt(firebaseData, relayTwoPath)) {
        if (firebaseData.dataType() == "int") {
            int relayTwoState = firebaseData.intData();
            digitalWrite(RELAY_TWO_PIN, relayTwoState == 1 ? HIGH : LOW); // Active High  logic
            Serial.print("relayTwo: ");
            Serial.println(relayTwoState);
        }
    } else {
        Serial.println("Failed to get relayTwo value");
        Serial.println(firebaseData.errorReason());
    }

    delay(1000); // Delay for 1 seconds before checking again
}
