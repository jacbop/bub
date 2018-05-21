// A simple flashing LED test program to make sure we
// can program the NodeMCU 1.0 (ESP-12E) properly

void setup() {
//  pinMode(D4, OUTPUT);
  pinMode(D8, OUTPUT);
}

void loop() {
//  digitalWrite(D4, !digitalRead(D4));
  digitalWrite(D8, !digitalRead(D8));
  delay(1000);
}
