#pragma once

#ifdef USE_ESP32

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/log.h"

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

#define EVENT_MESSAGE "{\"evt\":\"%s\",\"key\":%02d}"
#define MAX_SIM_KEYS 6

namespace esphome {
namespace key_press_event_sensor {

class KeyPressEventSensor : public text_sensor::TextSensor, public Component {
 private:
  class elapsedMillis {
   private:
    unsigned long ms;

   public:
    elapsedMillis(void) { ms = millis(); }
    elapsedMillis(unsigned long val) { ms = millis() - val; }
    elapsedMillis(const elapsedMillis &orig) { ms = orig.ms; }
    operator unsigned long() const { return millis() - ms; }
    elapsedMillis &operator=(const elapsedMillis &rhs) {
      ms = rhs.ms;
      return *this;
    }
    elapsedMillis &operator=(unsigned long val) {
      ms = millis() - val;
      return *this;
    }
    elapsedMillis &operator-=(unsigned long val) {
      ms += val;
      return *this;
    }
    elapsedMillis &operator+=(unsigned long val) {
      ms -= val;
      return *this;
    }
    elapsedMillis operator-(int val) const {
      elapsedMillis r(*this);
      r.ms += val;
      return r;
    }
    elapsedMillis operator-(unsigned int val) const {
      elapsedMillis r(*this);
      r.ms += val;
      return r;
    }
    elapsedMillis operator-(long val) const {
      elapsedMillis r(*this);
      r.ms += val;
      return r;
    }
    elapsedMillis operator-(unsigned long val) const {
      elapsedMillis r(*this);
      r.ms += val;
      return r;
    }
    elapsedMillis operator+(int val) const {
      elapsedMillis r(*this);
      r.ms -= val;
      return r;
    }
    elapsedMillis operator+(unsigned int val) const {
      elapsedMillis r(*this);
      r.ms -= val;
      return r;
    }
    elapsedMillis operator+(long val) const {
      elapsedMillis r(*this);
      r.ms -= val;
      return r;
    }
    elapsedMillis operator+(unsigned long val) const {
      elapsedMillis r(*this);
      r.ms -= val;
      return r;
    }
  };
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
  void show_config_desc_full(const usb_config_desc_t *config_desc);

 public:
  void setup() override;
  void loop() override;
};

}  // namespace key_press_event_sensor
}  // namespace esphome

#endif