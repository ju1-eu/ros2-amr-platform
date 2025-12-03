#include <Arduino.h>

/**
 * @brief  Layer 1 - Hello World
 * @details Testet, ob der ESP32-S3 lebt und über USB kommunizieren kann.
 * Blinkt die User-LED (Pin D10 beim Xiao S3, meist invertiert).
 */

// Die LED auf dem XIAO ESP32S3 ist oft an Pin 21 oder definiert als LED_BUILTIN
// Wir nutzen hier das Standard-Makro.
#ifndef LED_BUILTIN
#define LED_BUILTIN 21
#endif

void setup() {
    // 1. Serielle Kommunikation starten
    Serial.begin(115200);

    // 2. LED Pin konfigurieren
    pinMode(LED_BUILTIN, OUTPUT);

    // Warten, bis der serielle Monitor offen ist (optional, gut zum Debuggen)
    // while(!Serial) { delay(10); }
}

void loop() {
    static int counter = 0;

    // LED einschalten (LOW ist bei manchen Boards AN, bei anderen AUS -
    // ausprobieren!)
    digitalWrite(LED_BUILTIN, LOW);
    delay(100); // Kurz an (Herzschlag)

    // LED ausschalten
    digitalWrite(LED_BUILTIN, HIGH);
    delay(900); // Lang aus

    // Nachricht senden
    Serial.printf("[Layer 1] System alive. Heartbeat: %d\n", counter++);
}
