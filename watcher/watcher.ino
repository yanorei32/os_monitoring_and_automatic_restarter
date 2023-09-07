#include <stdint.h>
#define MACHINE_STARTUP_DELAY_S 60
#define MACHINE_TIMEOUT_MS 5000
#define BUTTON_PRESS_TIME_MS 500
#define LED_PIN 13
#define TRANSISTOR_PIN 2

uint32_t last_message_at = 0;

void wait_for_machine_startup() {
  for (uint8_t n = 0; n < MACHINE_STARTUP_DELAY_S * 2; ++n) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
  last_message_at = millis();
}

inline void press_the_reset_button() {  
  pinMode(TRANSISTOR_PIN, OUTPUT);
  delay(BUTTON_PRESS_TIME_MS);
  pinMode(TRANSISTOR_PIN, INPUT);
}

void serialEvent() {
  last_message_at = millis();
  while (Serial.peek() != -1) Serial.read();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  wait_for_machine_startup();
  Serial.begin(9600);
}

void loop() {
  if (millis() - MACHINE_TIMEOUT_MS > last_message_at) {
    press_the_reset_button();
    wait_for_machine_startup();
  }
}
