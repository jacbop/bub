//#include "Setpoint.h"
//#include "Arduino.h"
//
//#include <Encoder.h>
//
//#define MIN_CELSIUS -10
//#define MAX_CELSIUS 120
//#define TICK_RESOLUTION 4
//#define MIN_TICKS 0
//#define MAX_TICKS (MAX_CELSIUS - MIN_CELSIUS) * TICK_RESOLUTION
//#define START_TICKS (MIN_TICKS + ((MAX_TICKS - MIN_TICKS) * .20))
//
//Encoder encoder(D1, D2);
//
//// ticks always runs from 0 to MAX_TICKS
//long ticks_ = START_TICKS;
//long ticks = START_TICKS;
//boolean isButtonPressed = false;
//long buttonDebounceStartTime = 0;
//boolean needToCommit = false;
//long commitDebounceStartTime = 0;
//
//Setpoint::Setpoint(void (*onSetpointCallback)(long tempInDeciCelcius)){
//  onSetpoint = onSetpointCallback;
//}
//
//long ticksToCelsiusTenths(long tickObservation) {
//  long x = tickObservation;
//  long m = ((MAX_CELSIUS - MIN_CELSIUS) * TICK_RESOLUTION) / (MAX_TICKS - MIN_TICKS);
//  long b = MIN_CELSIUS * TICK_RESOLUTION;
//  long y = (m * x) + b;
//  return y;
//}
//
//
//long getValue(long tickObservation) {
//  long temperatureDeciCelsius = ticksToCelsiusTenths(tickObservation);
//  return temperatureDeciCelsius;
//}
//
//String getTempString(long tickObservation) {
//  long temperatureDeciCelsius = getValue(tickObservation);
//  String result =  "Temp is ";
//  double temperatureInC = temperatureDeciCelsius / 1.0 / TICK_RESOLUTION;
//  result = result + temperatureInC + "C";
//  return result;
//}
//
//void handleCommit(long ticks) {
//    needToCommit = false;
//    commitDebounceStartTime = millis();
//    Serial.print("COMMIT: ");
//    Serial.println(getTempString(ticks));
//  //  onSetpoint(getValue(ticks));
//}
//
//void handleKey() {
//  isButtonPressed = true;
//  Serial.println("PRESS.");
//  handleCommit(ticks);
//}
//
//long checkBounds(long tickObservation) {
//  if (tickObservation < MIN_TICKS) {
//    encoder.write(MIN_TICKS);
//    return MIN_TICKS;
//  }
//  if (tickObservation > MAX_TICKS) {
//    encoder.write(MAX_TICKS);
//    return MAX_TICKS;
//  }
//  return tickObservation;
//}
//
//void Setpoint::start(void) {
//   pinMode(D3, INPUT_PULLUP);
//   attachInterrupt(D3, handleKey, RISING);
//   encoder.write(START_TICKS);
//}
//
//void Setpoint::poll(void){
//  ticks = checkBounds(encoder.read());
//  if (ticks != ticks_) {
//    ticks_ = ticks;
//    commitDebounceStartTime = millis();
//    needToCommit = true;
//    Serial.print(ticks);
//    Serial.print("==> ");
//    Serial.println(getTempString(ticks));
//  }
//  if (needToCommit && ((millis() - commitDebounceStartTime) > 3000)) {
//    handleCommit(ticks);
//    needToCommit = false;
//    commitDebounceStartTime = millis();
//  }
//  if (isButtonPressed && ((millis() - buttonDebounceStartTime) > 150)) {
//    isButtonPressed = false;
//    buttonDebounceStartTime = millis();
//  }
//}
