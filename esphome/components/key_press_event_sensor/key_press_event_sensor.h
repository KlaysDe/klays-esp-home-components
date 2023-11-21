#pragma once

#ifdef USE_ESP32

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/log.h"

#include "elapsedMillis.h"
#include <usb/usb_host.h>
#include "show_desc.hpp"
#include "usbhhelp.hpp"

/*#include "esp_log.h"
#include <WiFi.h>
extern "C" {
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>*/

#define MAX_SIM_KEYS 6

namespace esphome {
namespace key_press_event_sensor {

class KeyPressEventSensor : public text_sensor::TextSensor, public Component {
 private:
  bool isKeyboard = false;
  bool isKeyboardReady = false;
  uint8_t KeyboardInterval;
  bool isKeyboardPolling = false;
  elapsedMillis KeyboardTimer;
  char sendBuffer[100];

  const size_t KEYBOARD_IN_BUFFER_SIZE = 8;
  usb_transfer_t *KeyboardIn = NULL;
  uint8_t pressedKeys[MAX_SIM_KEYS];
  uint8_t lastPressedKeys[MAX_SIM_KEYS];

  void keyboard_transfer_cb(usb_transfer_t *transfer);
  void check_interface_desc_boot_keyboard(const void *p);
  void prepare_endpoint(const void *p);
  static void show_config_desc_full(const usb_config_desc_t *config_desc);

 public:
  void setup() override;
  void loop() override;
};

}  // namespace key_press_event_sensor
}  // namespace esphome

#endif