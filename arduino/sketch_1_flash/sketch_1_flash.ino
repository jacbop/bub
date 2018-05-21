// A simple flashing LED test program to make sure we
// can program the NodeMCU 1.0 (ESP-12E) properly

void setup() {
  pinMode(D4, OUTPUT); // GPIO 2
  pinMode(D0, OUTPUT); // GPIO 16
}

void loop() {
  digitalWrite(D4, !digitalRead(D4));
  digitalWrite(D0, !digitalRead(D0));
  delay(1000);
}
