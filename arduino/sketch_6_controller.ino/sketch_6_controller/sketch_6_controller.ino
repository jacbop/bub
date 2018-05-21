// Basic operation of rotary encoder controlling OLED with Wifi and thermometer and controller logic

#include "Wifi.h"
#include "Display.h"
#include "Thermometer.h"
#include "Setpoint.h"
#include "Controller.h"

// pins
uint8_t pin_controller_relay_heat = D0; // GPIO16, NodeMCU LED, flashes during boot
uint8_t pin_display_i2c_slc = D1; // GPIO5
uint8_t pin_display_12c_sda = D2; // GPIO4
uint8_t pin_thermomemter_ds18B20_dq = D3; // GPIO0, must be in specific state during boot and flash
uint8_t pin_controller_relay_cool = D4; // D4 - ESP12 LED, // GPIO2 must be in specific state during boot and flash
uint8_t pin_encoder_clk = D5; // GPIO14, SPI
uint8_t pin_encoder_dt = D6; // GPIO12, SPI
uint8_t pin_encoder_sw = D7; // GPIO13, SPI
// D8 - GPIO15, SPI, must be in specific state during boot and flash
// D9 - RX, Needed for programming // GPIO3
// D10 - TX, Needed for programming // GPIO1
// D11 - SDD2, not usable // GPIO9
// D12 - SDD3, not usable, maybe digital read? // GPIO10

// defaults and paramters
double defaultSetpoint = 20.0; // C
double setpointDifferential = 0.75; // C
long compressorDelayTime = 2 * 60 * 1000; // msec
long setpointWaitTime = 3 * 1000; // msec
long temperatureSamplePeriod = 3 * 1000; // msec
double minimumTemperature = 0.0; // C
double maximumTemperature = 50.0; // C

// callback declarations

void onIpAddress(String ipAddress);
void onCool(bool isCalling);
void onHeat(bool isCalling);
void onWaitingForCompressor(bool isWaiting);
void onTemperature(double temperature);
void onValue(double value);
void onSetpoint(double setpoint);

// components
Wifi wifi(WIFI_SSID, WIFI_PASSWD, onIpAddress);
Display display(defaultSetpoint); // pin_display_i2c_slc, pin_display_12c_sda
Thermometer thermometer(pin_thermomemter_ds18B20_dq, temperatureSamplePeriod, onTemperature);
Setpoint setpoint(pin_encoder_clk, pin_encoder_dt, pin_encoder_sw, minimumTemperature, maximumTemperature, defaultSetpoint, setpointWaitTime, onSetpoint, onValue);
Controller controller(pin_controller_relay_cool, pin_controller_relay_heat, setpointDifferential, compressorDelayTime, defaultSetpoint, onCool, onHeat, onWaitingForCompressor);

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder + OLED + Wifi + Thermometer + Controller Test:");
  wifi.start(false);
  display.start(false);
  thermometer.start(false);
  setpoint.start(false);
  controller.start(false);
}

void loop() {
  long now = millis();
  setpoint.poll(now);
  thermometer.poll(now);
}

// callbacks
void onIpAddress(String ipAddress) {
  display.setBanner(ipAddress);  
}

void onCool(bool isCalling) {
  display.setCool(isCalling);
}

void onHeat(bool isCalling) {
  display.setHeat(isCalling);
}

void onWaitingForCompressor(bool isWaiting) {
  display.setWaitingForCompressor(isWaiting);
}

void onTemperature(double temperature) {
  controller.setTemperature(temperature);
  display.setTemperature(temperature);
}

void onValue(double value) {
  display.setValue(value);
}

void onSetpoint(double setpoint) {
  controller.setSetpoint(setpoint);
  display.setSetpoint(setpoint);
}


