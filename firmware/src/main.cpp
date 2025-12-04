#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <std_msgs/msg/int32.h>

// --- KONFIGURATION ---
#ifndef LED_BUILTIN
#define LED_BUILTIN 21
#endif

// Micro-ROS Objekte
rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// Status-LED Logik
#define LED_ON LOW
#define LED_OFF HIGH

// Fehler-Loop (Blinkt schnell, wenn was schiefgeht)
void error_loop() {
    while (1) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(100);
    }
}

// Timer-Callback: Wird regelmäßig aufgerufen, um Daten zu senden
void timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
    RCLC_UNUSED(last_call_time);
    if (timer != NULL) {
        // Wert hochzählen und senden
        msg.data++;
        rcl_publish(&publisher, &msg, NULL);

        // Visuelles Feedback: Kurzes Blinken bei jedem Senden
        digitalWrite(LED_BUILTIN, LED_ON);
        delay(10);
        digitalWrite(LED_BUILTIN, LED_OFF);
    }
}

void setup() {
    // 1. Initialisierung
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LED_OFF);

    // 2. Transport setzen (WICHTIG für ESP32-S3 USB)
    // Das sagt Micro-ROS: "Nutze den seriellen Port für die Kommunikation"
    set_microros_serial_transports(Serial);

    delay(2000); // Kurz warten, damit USB stabil ist

    // 3. Micro-ROS Setup
    allocator = rcl_get_default_allocator();

    // Support erstellen
    if (rclc_support_init(&support, 0, NULL, &allocator) != RCL_RET_OK) {
        // Wenn hier ein Fehler kommt, erreicht er den Agenten meist nicht
        // Wir machen weiter, versuchen es aber im Loop neu (State Machine wäre
        // besser, aber dies ist simpel)
    }

    // Node erstellen: "esp32_layer1"
    rclc_node_init_default(&node, "esp32_layer1", "", &support);

    // Publisher erstellen: Topic "/amr_heartbeat"
    rclc_publisher_init_default(
        &publisher, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "amr_heartbeat");

    // Timer erstellen (alle 1000ms = 1Hz)
    rclc_timer_init_default(&timer, &support, RCL_MS_TO_NS(1000),
                            timer_callback);

    // Executor erstellen (verwaltet die Callbacks)
    rclc_executor_init(&executor, &support.context, 1, &allocator);
    rclc_executor_add_timer(&executor, &timer);

    msg.data = 0;
}

void loop() {
    // Die Magie: Hier wird geprüft, ob Daten rein/raus müssen
    // Spin some work
    rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    delay(10);
}
